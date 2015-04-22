#define APP_NAME "MyxAODAnalysis"
#define MyInfo if(m_debugMode<=MSG::INFO) Info
#define MyError if(m_debugMode<=MSG::ERROR) Error
#define MyDebug(a,b) if(m_debugMode<=MSG::DEBUG) std::cout<<"Debug in <MyxAODAnalysis::"<<(a)<<">: "<<(b)<<std::endl;
#define MyAlways(a,b) if(m_debugMode<=MSG::ALWAYS) std::cout<<"In <MyxAODAnalysis::"<<(a)<<">: "<<(b)<<std::endl;

#include <EventLoop/Job.h>
#include <EventLoop/StatusCode.h>
#include <EventLoop/Worker.h>
#include <MyAnalysis/MyxAODAnalysis.h>

//added by minoru
#include"GoodRunsLists/GoodRunsListSelectionTool.h"
#include"SUSYTools/SUSYObjDef_xAOD.h"
#include"SUSYTools/SUSYCrossSection.h"

#include"MyAnalysis/EventSelector.h"

//end adding

// this is needed to distribute the algorithm to the workers
ClassImp(MyxAODAnalysis)

/////////////////////////////
// Histogram bins
/////////////////////////////
// My binning choices
double lep1PtBins[] = {0, 10, 20, 30, 50, 75, 100, 125, 150, 200, 300, 400, 500};
uint nLep1PtBins = 12;
double lep2PtBins[] = {0, 10, 20, 30, 40, 50, 60, 80, 100, 120, 150, 200};
uint nLep2PtBins = 11;
double lep3PtBins[] = {0, 10, 20, 30, 40, 50, 60, 80, 100, 120, 150};
uint nLep3PtBins = 10;
double massBins[] = {0, 20, 40, 60, 80, 100, 120, 140, 160, 180, 200, 225, 250, 275, 300, 325, 350, 375, 400, 425, 450, 475, 500};
uint nMassBins = 22;
double meffBins[] = {0, 50, 100, 150, 200, 250, 300, 350, 400, 450, 500, 550, 600, 700, 800, 900, 1000, 1100, 1200, 1300, 1400};
uint nMeffBins = 20; 
double mljjFineBins[] = {10, 30, 50, 70, 90, 110, 130, 150, 170, 200, 230, 260, 300, 340, 380, 420, 460, 500};
uint nMljjFineBins = 17;
double jetPtBins[] = {0, 20, 30, 40, 50, 65, 80, 100, 120, 140, 165, 190, 220, 250, 285, 320, 360, 400, 450, 500};
uint nJetPtBins = 19;

// New Mt binnings for the SRs
double mtCoarseBins[] = {110, 150, 200, 300};
uint nMtCoarseBins = 3;
double mtLowBins[] = {0, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110};
uint nMtLowBins = 10;

// dR bins
double dRBins[] = {0, 0.1, 0.2, 0.3, 0.4, 0.6, 0.8, 1.0, 1.3, 1.6, 2.0, 2.5, 3., 3.5, 4., 5., 6.};
uint nDRBins = 16;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////


MyxAODAnalysis :: MyxAODAnalysis ()
{
  // Here you put any code for the base initialization of variables,
  // e.g. initialize all pointers to 0.  Note that you should only put
  // the most basic initialization here, since this method will be
  // called on both the submission and the worker node.  Most of your
  // initialization code will go into histInitialize() and
  // initialize().

  // Event selection list
  m_vec_eveSelec = new std::vector<std::string>();
  m_vec_eveSelec->clear();

}



EL::StatusCode MyxAODAnalysis :: setupJob (EL::Job& job)
{
  // Here you put code that sets up the job on the submission object
  // so that it is ready to work with your algorithm, e.g. you can
  // request the D3PDReader service or add output files.  Any code you
  // put here could instead also go into the submission script.  The
  // sole advantage of putting it here is that it gets automatically
  // activated/deactivated when you add/remove the algorithm from your
  // job, which may or may not be of value to you.

  //Added by minoru
  job.useXAOD();
  xAOD::Init("MyxAODAnalysis").ignore(); //call before opening first file
  //end adding

  return EL::StatusCode::SUCCESS;
}

EL::StatusCode MyxAODAnalysis :: histInitialize ()
{
  // Here you do everything that needs to be done at the very
  // beginning on each worker node, e.g. create histograms and output
  // trees.  This method gets called before any input files are
  // connected.

  return EL::StatusCode::SUCCESS;
}



EL::StatusCode MyxAODAnalysis :: fileExecute ()
{
  // Here you do everything that needs to be done exactly once for every
  // single file, e.g. collect a list of all lumi-blocks processed

  return EL::StatusCode::SUCCESS;
}



EL::StatusCode MyxAODAnalysis :: changeInput (bool firstFile)
{
  // Here you do everything you need to do when we change input files,
  // e.g. resetting branch addresses on trees.  If you are using
  // D3PDReader or a similar service this method is not needed.
  return EL::StatusCode::SUCCESS;
}



EL::StatusCode MyxAODAnalysis :: initialize ()
{
  // Here you do everything that you need to do after the first input
  // file has been connected and before the first event is processed,
  // e.g. create additional histograms based on which variables are
  // available in the input files.  You can also create all of your
  // histograms and trees in here, but be aware that this method
  // doesn't get called if no events are processed.  So any objects
  // you create here won't be available in the output if you have no
  // input events.

  //Added by minoru
  m_event = wk()->xaodEvent();
  m_sysId = 0;

  //as a check, let's see the number of events in our xAOD
  MyInfo("initialize()", "Number of events = %lli. %lli events will be processed.", m_event->getEntries(), m_maxEvent); //print in long long int

  m_eventCounter = 0;
  m_processedEvents = 0;
  m_numCleanEvents = 0;
  m_eventWeight = 1.;

  // GRL tool initialization
  m_grl = new GoodRunsListSelectionTool("GoodRunsListSelectionTool");
  std::vector<std::string> vecStringGRL;
  vecStringGRL.push_back("./share/data12_8TeV.periodAllYear_DetStatus-v61-pro14-02_DQDefects-00-01-00_PHYS_StandardGRL_All_Good.xml");
  CHECK(m_grl->setProperty("GoodRunsListVec", vecStringGRL));
  CHECK(m_grl->setProperty("PassThrough", false)); // if true (default) will ignore result of GRL and will just pass all events
  if (!m_grl->initialize().isSuccess()) { // check this isSuccess
    MyError("initialize()", "Failed to properly initialize the GRL. Exiting.");
    return EL::StatusCode::FAILURE;
  }

  //Get meta-data from Sample Handler
  TFile *file = wk()->inputFile();
  TString sample_name = file->GetName();
  MyInfo( "initialize()", "We will process the events in the dataset : %s", sample_name.Data());
  int posAOD = sample_name.First("AOD");
  int posLastSlash = sample_name.Last('/');
  TString dstag = sample_name(posAOD+3,posLastSlash-posAOD-3);
  TString tmpname = sample_name(0,posLastSlash);
  int posSecondLastSlash = tmpname.Last('/');
  TString dsname = tmpname(posSecondLastSlash+1,tmpname.Length()-posSecondLastSlash-1);
  MyInfo( "initialize()", "Dataset Name : %s", dsname.Data());

  int isData = 0;
  int isAtlFast = 0;
  if(dsname.BeginsWith("data")){
    isData    = 1;
    isAtlFast = 0;
  }else if(dsname.BeginsWith("mc")){
    isData    = 0;
    if(dstag.Contains("_a")) isAtlFast = 1;
    else                     isAtlFast = 0;
  }else{
    MyError("initialize()", "Dataset seems not like any expected categories. Exiting.");
    return EL::StatusCode::FAILURE;
  }

  int datasource = isData ? ST::Data : (isAtlFast ? ST::AtlfastII : ST::FullSim);

  //  Create the tool(s) to test:
  m_susyObjTool = new ST::SUSYObjDef_xAOD("SUSYObjDef_xAOD");
  //  Configure the SUSYObjDef instance
  m_susyObjTool->msg().setLevel( m_debugMode );

  CHECK(m_susyObjTool->setProperty("DataSource",datasource) ) ;

  CHECK(m_susyObjTool->setProperty("IsDerived",true) ) ; //??? need to check
  CHECK(m_susyObjTool->setProperty("Is8TeV", false) ) ;
  
  CHECK(m_susyObjTool->setProperty("EleId","TightLLH") );
  CHECK(m_susyObjTool->setProperty("EleIdBaseline","LooseLLH") );
  // CHECK(m_susyObjTool->setProperty("EleId","Tight") );
  // CHECK(m_susyObjTool->setProperty("EleIdBaseline","Medium") );
  CHECK(m_susyObjTool->setProperty("TauId","Tight") );

  // Set to true for DxAOD, false for primary xAOD
  CHECK(m_susyObjTool->setProperty("DoJetAreaCalib",true) );
  // Set to false if not doing JetAreaCalib
  CHECK(m_susyObjTool->setProperty("DoJetGSCCalib",true) );
  
  // Set 0 for 14NP, 1,2,3,4 for 3NP sets
  CHECK(m_susyObjTool->setProperty("JESNuisanceParameterSet",1) );
  /////////////////////////////////////////////
  if( m_susyObjTool->SUSYToolsInit().isFailure() ) {
    MyError( "initialize()", "Failed to initialise tools in SUSYToolsInit()..." );
    MyError( "initialize()", "Exiting..." );
    return EL::StatusCode::FAILURE;
  }
  if( m_susyObjTool->initialize() != StatusCode::SUCCESS){
    MyError( "initialize()", "Cannot intialize SUSYObjDef_xAOD..." );
    MyError( "initialize()", "Exiting... " );
    return EL::StatusCode::FAILURE;
  }else{
    MyInfo( "initialize()", "SUSYObjDef_xAOD initialized... " );
  }

  m_XSDB = new SUSY::CrossSectionDB("susy_crosssections_13TeV.txt");
  if(isData) m_crossSection = 0.;
  else       m_crossSection = m_XSDB->xsectTimesEff(m_dsid);
  MyInfo("initialize()", Form("Cross section times filter efficiency for DSID #%i: %f pb", m_dsid, m_crossSection));
  if(m_crossSection<0.){
    MyError("initialize()","Failed to obtain the cross section for DSID=%i.",m_dsid);
    return EL::StatusCode::FAILURE;
  }

  // Now we can look at systematics:
  const CP::SystematicRegistry& registry = CP::SystematicRegistry::getInstance();
  const CP::SystematicSet& recommendedSystematics = registry.recommendedSystematics();
  // this is the nominal set
  m_sysList.push_back(CP::SystematicSet());
  for(CP::SystematicSet::const_iterator sysItr = recommendedSystematics.begin();
      sysItr != recommendedSystematics.end(); ++sysItr){
    
    MyInfo("initialize()", "Found syst in global registry: %s", (sysItr->basename()).c_str());
    
    TString tmpSysName = sysItr->basename();
    if(IsConsideredSyst(tmpSysName)){
      if (*sysItr == CP::SystematicVariation (sysItr->basename(), CP::SystematicVariation::CONTINUOUS)){
        // for continuous systematics just evaluate +/-1 sigma
        m_sysList.push_back(CP::SystematicSet());
        m_sysList.back().insert(CP::SystematicVariation (sysItr->basename(), 1));
        m_sysList.push_back(CP::SystematicSet());
        m_sysList.back().insert(CP::SystematicVariation (sysItr->basename(), -1));
      }else{
        // otherwise just add it flat
        m_sysList.push_back(CP::SystematicSet());
        m_sysList.back().insert(*sysItr);
      }
    }
  }
  MyDebug("initialize()", Form("========================================= Considered #systematics = %d", (int)m_sysList.size()) );

  for(int eve=0; eve<nEveSelec; eve++){
    for(int syst=0; syst<nSyst; syst++){
      n_initial[eve][syst] = 0;
      n_pass_hotSpot[eve][syst] = 0;
      n_pass_badJet[eve][syst] = 0;
      n_pass_feb[eve][syst] = 0;
      n_pass_badMu[eve][syst] = 0;
      n_pass_cosmic[eve][syst] = 0;
      n_pass_clean[eve][syst] = 0;
      n_pass_nBLep[eve][syst] = 0;
      n_pass_mllBase[eve][syst] = 0;
      n_pass_nLep[eve][syst] = 0;
      n_pass_nTau[eve][syst] = 0;
      n_pass_ssEmul[eve][syst] = 0;
      n_pass_trig[eve][syst] = 0;
      n_pass_truth[eve][syst] = 0;
      n_pass_sfos[eve][syst] = 0;
      n_pass_lz[eve][syst] = 0;
      n_pass_z[eve][syst] = 0;
      n_pass_met[eve][syst] = 0;
      n_pass_vbf[eve][syst] = 0;
      n_pass_jet[eve][syst] = 0;
      n_pass_mt[eve][syst] = 0;
      n_pass_mljj[eve][syst] = 0;
      n_pass_meff[eve][syst] = 0;
      n_pass_lepPt[eve][syst] = 0;
      n_pass_lepDR[eve][syst] = 0;
      n_pass_other[eve][syst] = 0;
    }
  }

  BookHistograms(); //This has to be called after m_sysList has been set.

  //end adding

  return EL::StatusCode::SUCCESS;
}



EL::StatusCode MyxAODAnalysis :: execute ()
{
  // Here you do everything that needs to be done on every single
  // events, e.g. read input variables, apply cuts, and fill
  // histograms and trees.  This is where most of your actual analysis
  // code will go.

  //Added by minoru
  if(m_eventCounter==0) MyInfo("execute()", "Starting event by event processing.");
  // print every 100 events, so we know where we are:
  if(m_eventCounter%5000==0) MyAlways("execute()", Form("Event number = %lli", m_eventCounter));
  m_eventCounter++; //Incrementing here since event might be rejected by some quality checks below.
  if( m_maxEvent>=0 && 
      ( m_eventCounter<=m_nSkipNum || (m_maxEvent+m_nSkipNum)<m_eventCounter ) ) return EL::StatusCode::SUCCESS;
  m_processedEvents++;

  //----------------------------
  // Event information
  //--------------------------- 
  const xAOD::EventInfo *eventInfo = 0;
  if(!m_event->retrieve(eventInfo, "EventInfo").isSuccess()){
    MyError("execute()", "Failed to retrieve event info collection. Exiting.");
    return EL::StatusCode::FAILURE;
  }

  // check if the event is data or MC
  m_isMC = eventInfo->eventType(xAOD::EventInfo::IS_SIMULATION) ? true : false;

  // check run number and luminosity block in data
  Int_t RunNumber   = -999;
  Int_t LumiBlock   = -999;
  Int_t EventNumber = -999;
  Int_t mcChannelNumber = -999; //DSID
  Int_t mcEventNumber   = -999; //Event number in generator?
  m_eventWeight = -999.;
  if(!m_isMC){ //For data
    RunNumber   = eventInfo->runNumber();
    LumiBlock   = eventInfo->lumiBlock();
    EventNumber = eventInfo->eventNumber();
    m_eventWeight = 1.;
    MyInfo("execute()", "RunNumber : %i, LumiBlock : %i, EventNumber : %i", RunNumber, LumiBlock, EventNumber);
  }else{ //For MC, check DSID and 
    mcChannelNumber = eventInfo->mcChannelNumber(); //DSID
    mcEventNumber   = eventInfo->mcEventNumber(); //Event number in generator?
    m_eventWeight   = eventInfo->mcEventWeight();
    MyInfo("execute()", "ChannelNumber : %i, EventNumber : %i, EventWeight : %f", mcChannelNumber, mcEventNumber, m_eventWeight);
    if(m_dsid!=mcChannelNumber){
      MyError("execute()",Form("mcChannelNumber(%d) by EventInfo is different from the one in testRun arugument(%d).",mcChannelNumber,m_dsid));
    }
  }
  h_nEve->Fill(0.,m_eventWeight);

  if(not PassPreSelection(eventInfo)) return EL::StatusCode::SUCCESS;
  MyInfo( "initialize()", "Preselection : Done.");

  ///////////////////////////////////////////////////////////////////////////
  // End of preselection
  ///////////////////////////////////////////////////////////////////////////
  if(m_debugMode<=MSG::DEBUG) m_store.print();

  /////////////////////////////////////////////////////////////////////////
  // Now loop over all the systematic variations and event selections
  /////////////////////////////////////////////////////////////////////////
  size_t isys=0;
  m_sysId = 0;
  std::vector<CP::SystematicSet>::const_iterator sysListItr;
  for(UInt_t eveSelec=0; eveSelec<m_vec_eveSelec->size(); eveSelec++){
    std::string eveSelecName = m_vec_eveSelec->at(eveSelec);
    //Systematic loop should be nested in the event selection loop.
    //This is due to the fact that we have to clear m_store after executing one set of systematic loop.
    ////////////////////////////
    for(sysListItr = m_sysList.begin(); sysListItr != m_sysList.end(); ++sysListItr){
      MyInfo("execute()", ">>>> Working on variation: sys=%i, \"%s\"", (int)isys, (sysListItr->name()).c_str());
      // Tell the SUSYObjDef_xAOD which variation to apply
      if(m_susyObjTool->applySystematicVariation(*sysListItr) != CP::SystematicCode::Ok){
        MyError("execute()", "Cannot configure SUSYTools for systematic var. %s", (sysListItr->name()).c_str() );
      }else{
        MyInfo("execute()", "Variation \"%s\" configured...", (sysListItr->name()).c_str() );
      }

      EventSelector* myEveSelec = 
        new EventSelector(m_susyObjTool, eveSelecName.c_str(), (sysListItr->name()).c_str(), (m_isMC?1:0), m_debugMode);
      myEveSelec->initialize();
      myEveSelec->setStore(&m_store);
      myEveSelec->selectObject();
      Bool_t passSelec = myEveSelec->selectEvent();
      if(passSelec) FillHistograms(myEveSelec);
      SetEventCounter(myEveSelec,eveSelec,isys);
      myEveSelec->finalize();
      delete myEveSelec;

      m_susyObjTool->resetSystematics();
      if(m_noSyst) break; //break if NoSyst flag is true;
      ++isys;
      m_sysId = isys;
    }

    
    MyDebug("execute()", "Store before .clear()");
    if(m_debugMode<=MSG::DEBUG) m_store.print();
    m_store.clear();
    MyDebug("execute()", "Store after .clear()");
    if(m_debugMode<=MSG::DEBUG) m_store.print();

  }
    
  if(m_debugMode<=MSG::VERBOSE){
    std::cout<<"Hit enter to proceed to the next event."<<std::endl;
    getchar();
  }
  //end adding

  return EL::StatusCode::SUCCESS;
}



EL::StatusCode MyxAODAnalysis :: postExecute ()
{
  // Here you do everything that needs to be done after the main event
  // processing.  This is typically very rare, particularly in user
  // code.  It is mainly used in implementing the NTupleSvc.

  //Added by minoru
  //Here, executed just after execute(). (i.e. event by event)
  //end adding

  return EL::StatusCode::SUCCESS;
}



EL::StatusCode MyxAODAnalysis :: finalize ()
{
  // This method is the mirror image of initialize(), meaning it gets
  // called after the last event has been processed on the worker node
  // and allows you to finish up any objects you created in
  // initialize() before they are written to disk.  This is actually
  // fairly rare, since this happens separately for each worker node.
  // Most of the time you want to do your post-processing on the
  // submission node after all your histogram outputs have been
  // merged.  This is different from histFinalize() in that it only
  // gets called on worker nodes that processed input events.

  //Added by minoru
  MyAlways("finalize()", Form("Total #Events in the sample dataset : %lli", m_eventCounter) );
  MyAlways("finalize()", Form("#(Used Events) : %lli, #(Healthy events) : %lli", m_processedEvents, m_numCleanEvents) );
  dumpEventCounters();

  if(m_susyObjTool){
    delete m_susyObjTool;
    m_susyObjTool = 0;
  }
  if(m_grl){
    delete m_grl;
    m_grl = 0;
  }
  //end adding

  return EL::StatusCode::SUCCESS;
}


EL::StatusCode MyxAODAnalysis :: histFinalize ()
{
  // This method is the mirror image of histInitialize(), meaning it
  // gets called after the last event has been processed on the worker
  // node and allows you to finish up any objects you created in
  // histInitialize() before they are written to disk.  This is
  // actually fairly rare, since this happens separately for each
  // worker node.  Most of the time you want to do your
  // post-processing on the submission node after all your histogram
  // outputs have been merged.  This is different from finalize() in
  // that it gets called on all worker nodes regardless of whether
  // they processed input events.
  return EL::StatusCode::SUCCESS;
}


//Added by minoru
bool MyxAODAnalysis::PassPreSelection(const xAOD::EventInfo* eventInfo){
  //------------------------------------------------------------
  // if data check if event passes GRL
  //------------------------------------------------------------
  if(!m_isMC){ // it's data!
    if(!m_grl->passRunLB(*eventInfo)){
      MyInfo("EventPreSelection()", "The event is not in the GRL!! going to next event...");
      return false;
    }
  } // end if not MC

  //------------------------------------------------------------
  // Apply event cleaning to remove events due to 
  // problematic regions of the detector, and incomplete events.
  // Apply to data.
  //------------------------------------------------------------
  // reject event if:
  if(!m_isMC){
    if((eventInfo->errorState(xAOD::EventInfo::LAr )==xAOD::EventInfo::Error) ||
       (eventInfo->errorState(xAOD::EventInfo::Tile)==xAOD::EventInfo::Error) ||
       (eventInfo->isEventFlagBitSet(xAOD::EventInfo::Core, 18)) ){
      MyInfo("EventPreSelection()", "Event is rejected due to detector imperfections.");
      return false;
    } // end if event flags check
  } // end if the event is data
  m_numCleanEvents++;

  return true;
}


bool MyxAODAnalysis::IsConsideredSyst(TString sysBasename){
  bool retval = false;

  if(sysBasename.Contains("EG_RESOLUTION_ALL") ||
     sysBasename.Contains("EG_RESOLUTION_NOMINAL") ||
     sysBasename.Contains("EG_SCALE_ALL") ||
     sysBasename.Contains("EG_SCALE_NOMINAL") ||
     sysBasename.Contains("EG_SCALE_NONE") ||
     sysBasename.Contains("EL_EFF_CorrUncertainty") ||
     sysBasename.Contains("EL_EFF_UncorrUncertainty") ||
     sysBasename.Contains("JER") ||
     sysBasename.Contains("MUONS_SCALE") ||
     sysBasename.Contains("MUONSF") ||
     sysBasename.Contains("JET_BJES_Response") ||
     sysBasename.Contains("MET_SoftCalo_Scale") ||
     sysBasename.Contains("MET_SoftTrk_Scale")
     ) retval = true;
  
  return retval;
}

bool MyxAODAnalysis::BookHistograms(){

  if(m_sysList.size()!=nSyst){
    MyError("BookHistograms()", "The number of considered systematics is not the expected value!! Exiting.");
    exit(1);
  }

  std::vector<std::string> vec_chan; vec_chan.clear();
  vec_chan.push_back("all");
  vec_chan.push_back("eee");
  vec_chan.push_back("eem");
  vec_chan.push_back("emm");
  vec_chan.push_back("mmm");

  // Preprocessor convenience                                                                                 
  // make a histogram by name (leave off the "h_") and binning
#define NEWHIST(name, xLbl, nbin, min, max)                             \
  h_ ## name[iCh][wSys] = new TH1F((chanName+"_"+#name).c_str(), #name ";" xLbl, nbin, min, max); \
  wk()->addOutput(h_ ## name[iCh][wSys])
#define NEWVARHIST(name, xLbl, nbin, bins)                              \
  h_ ## name[iCh][wSys] = new TH1F((chanName+"_"+#name).c_str(), #name ";" xLbl, nbin, bins); \
  wk()->addOutput(h_ ## name[iCh][wSys])
  // shorthand way to set bin labels, since it is kind of gross                                               
#define SETBINLABEL(name, bin, label)                         \
  h_ ## name[iCh][wSys]->GetXaxis()->SetBinLabel(bin, label)
  // Variable binning for lep1Pt
#define PT1HIST(name, xLbl) NEWVARHIST(name, xLbl, nLep1PtBins, lep1PtBins)
  // MY choice of binnings                                                                                    
#define ETAHIST(name, xLbl) NEWHIST(name, xLbl, 10, -2.5, 2.5)
#define PTHIST(name, xLbl) NEWHIST(name, xLbl, 25, 0., 500.)
#define DRHIST(name, xLbl) NEWVARHIST(name, xLbl, nDRBins, dRBins)
#define DPHIHIST(name, xLbl) NEWHIST(name, xLbl, 10, 0., 3.1416)
#define MASSHIST(name, xLbl) NEWHIST(name, xLbl, 25, 0., 500.)
#define ZMASSHIST(name, xLbl) NEWHIST(name, xLbl, 25, 1.2, 501.2) // shifted for Z window 

  ///////////////////////////////////////////////////////////////
  //Defining histograms
  ///////////////////////////////////////////////////////////////

  // Histogram to store the MC cross section
  h_xsec = new TH1F("h_xsec","h_xsec;;MC cross-section[pb]",1,0.,1.);
  h_nEve = new TH1F("h_nEve","h_nEve;;Events"              ,1,0.,1.);
  wk()->addOutput(h_xsec);
  wk()->addOutput(h_nEve);
  h_xsec->SetBinContent(h_xsec->FindBin(0.),m_crossSection); //set cross-section

  // lepton channel / systematics loop
  for(uint wSys=0; wSys<nSyst; wSys++){
    // Lepton channel histo, only defined for the 'all' channel
    h_lepChan       [Ch_all][wSys] = new TH1F("all_lepChan"       ,
                                              "all_lepChan;Unordered lepton channel;Events", nChan, 0, nChan);
    wk()->addOutput(h_lepChan       [Ch_all][wSys]);
    for(uint iCh=0; iCh<nChan; iCh++){
      std::string chanName = vec_chan.at(iCh);
      h_lepChan[Ch_all][wSys]->GetXaxis()->SetBinLabel(iCh+1, chanName.c_str());
      // Single bin event count                                                                                   
      NEWHIST( all, ";Events", 1, 0, 1 );
      // lep pt - my choice of binning                                                                            
      NEWVARHIST( lep1Pt, "Leading lepton_{} P_{T} [GeV];Events", nLep1PtBins, lep1PtBins );
      NEWVARHIST( lep2Pt, "Second lepton_{} P_{T} [GeV];Events", nLep2PtBins, lep2PtBins );
      NEWVARHIST( lep3Pt, "Third lepton_{} P_{T} [GeV];Events", nLep3PtBins, lep3PtBins );
      NEWVARHIST( el1Pt, "Leading lepton_{} P_{T} [GeV];Events", nLep1PtBins, lep1PtBins );
      NEWVARHIST( el2Pt, "Second lepton_{} P_{T} [GeV];Events", nLep2PtBins, lep2PtBins );
      NEWVARHIST( el3Pt, "Third lepton_{} P_{T} [GeV];Events", nLep3PtBins, lep3PtBins );
      NEWVARHIST( mu1Pt, "Leading lepton_{} P_{T} [GeV];Events", nLep1PtBins, lep1PtBins );
      NEWVARHIST( mu2Pt, "Second lepton_{} P_{T} [GeV];Events", nLep2PtBins, lep2PtBins );
      NEWVARHIST( mu3Pt, "Third lepton_{} P_{T} [GeV];Events", nLep3PtBins, lep3PtBins );

      ETAHIST( lep1Eta, "Leading lepton #eta;Events" );
      ETAHIST( lep2Eta, "Second lepton #eta;Events" );
      ETAHIST( lep3Eta, "Third lepton #eta;Events" );
    }
  }
  //  h_jetPt = new TH1F("h_jetPt", "h_jetPt", 100, 0, 500); // jet pt [GeV]
  //  wk()->addOutput(h_jetPt);

#undef PT1HIST
#undef ETAHIST
#undef PTHIST
#undef DRHIST
#undef DPHIHIST
#undef MASSHIST
#undef ZMASSHIST
#undef NEWHIST
#undef NEWVARHIST
#undef SETBINLABEL
  
  return true;
}

bool MyxAODAnalysis::FillHistograms(EventSelector *EveSelec){

  MyDebug("FillHistograms()", "Filling histogram ...");

  //Retrieving objects via EventSelector
  std::vector< xAOD::Electron >* vec_signalElectron = EveSelec->GetSignalElectron();
  // std::vector< xAOD::Electron >* vec_baseElectron   = EveSelec->GetBaseElectron  ();
  std::vector< xAOD::Muon >*     vec_signalMuon     = EveSelec->GetSignalMuon    ();
  // std::vector< xAOD::Muon >*     vec_baseMuon       = EveSelec->GetBaseMuon      ();
  // std::vector< xAOD::Jet >*      vec_signalJet      = EveSelec->GetSignalJet     ();
  // std::vector< xAOD::Jet >*      vec_baseJet        = EveSelec->GetBaseJet       ();
  // std::vector< xAOD::Jet >*      vec_preJet         = EveSelec->GetPreJet        ();
  //  TVector2                       met                = EveSelec->GetMEt           ();
  
  // std::cout<<"elSize="<<vec_signalElectron->size()<<", muSize="<<vec_signalMuon->size()<<std::endl;
  // for(UInt_t el=0; el<vec_signalElectron->size(); el++){
  //   std::cout<<"el="<<el<<", address ="<<&(vec_signalElectron->at(el))<<std::endl;
  //   std::cout<<"pt ="<<vec_signalElectron->at(el).pt()<<std::endl;
  //   std::cout<<"eta="<<vec_signalElectron->at(el).eta()<<std::endl;
  //   std::cout<<"phi="<<vec_signalElectron->at(el).phi()<<std::endl;
  //   const xAOD::TrackParticle* track = vec_signalElectron->at(el).trackParticle();
  //   double el_d0 = track->d0();
  //   std::cout<<"d0="<<el_d0<<std::endl;
  // }
  // for(UInt_t mu=0; mu<vec_signalMuon->size(); mu++){
  //   std::cout<<"mu="<<mu<<", address ="<<&(vec_signalMuon->at(mu))<<std::endl;
  //   std::cout<<"pt ="<<vec_signalMuon->at(mu).pt()<<std::endl;
  //   std::cout<<"eta="<<vec_signalMuon->at(mu).eta()<<std::endl;
  //   std::cout<<"phi="<<vec_signalMuon->at(mu).phi()<<std::endl;
  //   const xAOD::TrackParticle* track = vec_signalMuon->at(mu).primaryTrackParticle();
  //   double mu_d0 = track->d0();
  //   std::cout<<"d0="<<mu_d0<<std::endl;
  // }

  Int_t chan = EveSelec->getChan();
  //  std::cout<<"Analized channel : "<<chan<<std::endl;

  //Prepare 1st-3rd leading lepton's four-vector
  Int_t leadLepIndex[3];
  Int_t leadLepFlavor[3];
  TLorentzVector leadLep[3];
  for(Int_t id=0; id<3; id++){
    leadLepIndex [id] = EveSelec->getLeadLepIndex (id);
    leadLepFlavor[id] = EveSelec->getLeadLepFlavor(id);
    leadLep      [id] = EveSelec->getLeadLep      (id);
  }

  //===========================================================================
  Double_t weight=m_eventWeight*EveSelec->getTotalSF();

  // Preprocessor convenience
  // All this does is append the corrent indices to the histo for sys and channel
  // It also fills the all-channel histo 
#define FillChanHist( h, val, weight )          \
  do{                                           \
    h[Ch_all][m_sysId]->Fill(val,weight);       \
    h[chan][m_sysId]->Fill(val,weight);         \
  } while(0)
#define FillChanHist2D( h, xVal, yVal, weight )   \
  do{                                             \
    h[Ch_all][m_sysId]->Fill(xVal, yVal, weight); \
    h[chan][m_sysId]->Fill(xVal, yVal, weight);   \
  } while(0)
#define FillElHist( index, h, val, weight )                           \
  do{                                                                 \
    if(leadLepFlavor[index]==0) h[Ch_all][m_sysId]->Fill(val,weight); \
    if(leadLepFlavor[index]==0) h[chan][m_sysId]->Fill(val,weight);   \
  } while(0)
#define FillMuHist( index, h, val, weight )                           \
  do{                                                                 \
    if(leadLepFlavor[index]==1) h[Ch_all][m_sysId]->Fill(val,weight); \
    if(leadLepFlavor[index]==1) h[chan][m_sysId]->Fill(val,weight);   \
  } while(0)
  //Fill lepChan histograms
  h_lepChan       [Ch_all][m_sysId]->Fill(Ch_all,weight);
  h_lepChan       [Ch_all][m_sysId]->Fill(chan,weight);

  //Fill lepton Pt
  FillChanHist( h_lep1Pt, leadLep[0].Pt()/1000., weight );
  FillChanHist( h_lep2Pt, leadLep[1].Pt()/1000., weight );
  FillChanHist( h_lep3Pt, leadLep[2].Pt()/1000., weight );
  FillElHist( 0, h_el1Pt, vec_signalElectron->at(leadLepIndex[0]).pt()/1000., weight );
  FillMuHist( 0, h_mu1Pt, vec_signalMuon    ->at(leadLepIndex[0]).pt()/1000., weight );
  FillElHist( 1, h_el2Pt, vec_signalElectron->at(leadLepIndex[1]).pt()/1000., weight );
  FillMuHist( 1, h_mu2Pt, vec_signalMuon    ->at(leadLepIndex[1]).pt()/1000., weight );
  FillElHist( 2, h_el3Pt, vec_signalElectron->at(leadLepIndex[2]).pt()/1000., weight );
  FillMuHist( 2, h_mu3Pt, vec_signalMuon    ->at(leadLepIndex[2]).pt()/1000., weight );

  //Fill lepton Eta
  FillChanHist( h_lep1Eta, leadLep[0].Eta(), weight );
  FillChanHist( h_lep2Eta, leadLep[1].Eta(), weight );
  FillChanHist( h_lep3Eta, leadLep[2].Eta(), weight );

  // getchar();
  // std::cout<<"MEt="<<met.Mod()<<", Phi="<<met.Phi()<<std::endl;
  // std::cout<<"Px="<<met.Px()<<", Py="<<met.Py()<<std::endl;
  // std::cout<<"End: event selection ..."<<std::endl;

#undef FillChanHist
#undef FillChanHist2D
#undef FillElHist
#undef FillMuHist

  return true;
}

/*--------------------------------------------------------------------------------*/
void MyxAODAnalysis::SetEventCounter(EventSelector *EveSelec, int eveSelec, int sys){
  n_initial     [eveSelec][sys] += EveSelec->Get_initial     ();
  n_pass_hotSpot[eveSelec][sys] += EveSelec->Get_pass_hotSpot();
  n_pass_badJet [eveSelec][sys] += EveSelec->Get_pass_badJet ();
  n_pass_feb    [eveSelec][sys] += EveSelec->Get_pass_feb    ();
  n_pass_badMu  [eveSelec][sys] += EveSelec->Get_pass_badMu  ();
  n_pass_cosmic [eveSelec][sys] += EveSelec->Get_pass_cosmic ();
  n_pass_clean  [eveSelec][sys] += EveSelec->Get_pass_clean  ();
  n_pass_nBLep  [eveSelec][sys] += EveSelec->Get_pass_nBLep  ();
  n_pass_mllBase[eveSelec][sys] += EveSelec->Get_pass_mllBase();
  n_pass_nLep   [eveSelec][sys] += EveSelec->Get_pass_nLep   ();
  n_pass_nTau   [eveSelec][sys] += EveSelec->Get_pass_nTau   ();
  n_pass_ssEmul [eveSelec][sys] += EveSelec->Get_pass_ssEmul ();
  n_pass_trig   [eveSelec][sys] += EveSelec->Get_pass_trig   ();
  n_pass_truth  [eveSelec][sys] += EveSelec->Get_pass_truth  ();
  n_pass_sfos   [eveSelec][sys] += EveSelec->Get_pass_sfos   ();
  n_pass_lz     [eveSelec][sys] += EveSelec->Get_pass_lz     ();
  n_pass_z      [eveSelec][sys] += EveSelec->Get_pass_z      ();
  n_pass_met    [eveSelec][sys] += EveSelec->Get_pass_met    ();
  n_pass_vbf    [eveSelec][sys] += EveSelec->Get_pass_vbf    ();
  n_pass_jet    [eveSelec][sys] += EveSelec->Get_pass_jet    ();
  n_pass_mt     [eveSelec][sys] += EveSelec->Get_pass_mt     ();
  n_pass_mljj   [eveSelec][sys] += EveSelec->Get_pass_mljj   ();
  n_pass_meff   [eveSelec][sys] += EveSelec->Get_pass_meff   ();
  n_pass_lepPt  [eveSelec][sys] += EveSelec->Get_pass_lepPt  ();
  n_pass_lepDR  [eveSelec][sys] += EveSelec->Get_pass_lepDR  ();
  n_pass_other  [eveSelec][sys] += EveSelec->Get_pass_other  ();

  return;
}

/*--------------------------------------------------------------------------------*/
// Event counters
/*--------------------------------------------------------------------------------*/
void MyxAODAnalysis::dumpEventCounters()
{
  for(UInt_t eveSelec=0; eveSelec<m_vec_eveSelec->size(); eveSelec++){
    std::string eveSelecName = m_vec_eveSelec->at(eveSelec);
    std::cout << std::endl;
    std::cout << "Event selection counters for " << eveSelecName.c_str() << std::endl;

    std::cout << "  initial:      " << n_initial      [eveSelec][0]<< std::endl;
    std::cout << "  pass hotSpot: " << n_pass_hotSpot [eveSelec][0]<< std::endl;
    std::cout << "  pass badJet:  " << n_pass_badJet  [eveSelec][0]<< std::endl;
    std::cout << "  pass FEB:     " << n_pass_feb     [eveSelec][0]<< std::endl;
    std::cout << "  pass badMu:   " << n_pass_badMu   [eveSelec][0]<< std::endl;
    std::cout << "  pass cosmic:  " << n_pass_cosmic  [eveSelec][0]<< std::endl;
    std::cout << "  pass clean:   " << n_pass_clean   [eveSelec][0]<< std::endl;
    std::cout << "  pass nBLep:   " << n_pass_nBLep   [eveSelec][0]<< std::endl;
    std::cout << "  pass mllBase: " << n_pass_mllBase [eveSelec][0]<< std::endl;
    std::cout << "  pass nLep:    " << n_pass_nLep    [eveSelec][0]<< std::endl;
    std::cout << "  pass nTau:    " << n_pass_nTau    [eveSelec][0]<< std::endl;
    std::cout << "  pass trig:    " << n_pass_trig    [eveSelec][0]<< std::endl;
    std::cout << "  pass truth:   " << n_pass_truth   [eveSelec][0]<< std::endl;
    std::cout << "  pass flavQ:   " << n_pass_sfos    [eveSelec][0]<< std::endl;
    //std::cout << "  pass loose Z: " << n_pass_lz      [eveSelec][0]<< std::endl;
    std::cout << "  pass jet:     " << n_pass_jet     [eveSelec][0]<< std::endl;
    std::cout << "  pass vbf:     " << n_pass_vbf     [eveSelec][0]<< std::endl;
    std::cout << "  pass lepPt:   " << n_pass_lepPt   [eveSelec][0]<< std::endl;
    std::cout << "  pass z:       " << n_pass_z       [eveSelec][0]<< std::endl;
    std::cout << "  pass lep dR:  " << n_pass_lepDR   [eveSelec][0]<< std::endl;
    std::cout << "  pass met:     " << n_pass_met     [eveSelec][0]<< std::endl;
    std::cout << "  pass mt:      " << n_pass_mt      [eveSelec][0]<< std::endl;
    std::cout << "  pass meff:    " << n_pass_meff    [eveSelec][0]<< std::endl;
    //std::cout << "  pass mljj:    " << n_pass_mljj    [eveSelec][0]<< std::endl;
    //std::cout << "  pass other:   " << n_pass_other   [eveSelec][0]<< std::endl;
  }

}
