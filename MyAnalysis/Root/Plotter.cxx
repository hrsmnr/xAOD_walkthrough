#define APP_NAME "Plotter"
#define MyVerbose(a,b) if(m_dbg<=MSG::VERBOSE) std::cout<<"Verbose in <Plotter::"<<(a)<<">: "<< m_sel.c_str() << "," << m_sys << " : "<<(b)<<std::endl;
#define MyDebug(a,b) if(m_dbg<=MSG::DEBUG) std::cout<<"Debug in <Plotter::"<<(a)<<">: "<< m_sel.c_str() << "," << m_sys << " : "<<(b)<<std::endl;
#define MyInfo(a,b) if(m_dbg<=MSG::INFO) std::cout<<"Info in <Plotter::"<<(a)<<">: "<< m_sel.c_str() << "," << m_sys << " : "<<(b)<<std::endl;
#define MyError(a,b) if(m_dbg<=MSG::ERROR) std::cout<<"Error in <Plotter::"<<(a)<<">: "<< m_sel.c_str() << "," << m_sys << " : "<<(b)<<std::endl;
#define MyAlways(a,b) if(m_dbg<=MSG::ALWAYS) std::cout<<"In <Plotter::"<<(a)<<">: "<< m_sel.c_str() << "," << m_sys << " : "<<(b)<<std::endl;

#include<iostream>
#include"MyAnalysis/Plotter.h"

#include"TFile.h"
#include"TH1F.h"

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

/*--------------------------------------------------------------------------------*/
// Plotter Constructor
/*--------------------------------------------------------------------------------*/
Plotter::Plotter(std::string sel, std::string sys, MSG::Level dbg) : 
  m_dbg(dbg),
  m_sel(sel),
  m_sys(sys),
  m_filename(""),
  m_crossSection(0.)
{}

/*--------------------------------------------------------------------------------*/
// Initialize the plotter
/*--------------------------------------------------------------------------------*/
void Plotter::initialize(const char* path, int dsid, double XS)
{
  MyDebug("initialize()","Plotter::initialize()");

  m_crossSection = XS;

  // Preparing TFile
  m_filename = Form("%s/%d.%s.%s.AnaHists.root",path,dsid,m_sel.c_str(),m_sys.c_str());
  m_rootfile = new TFile(m_filename.c_str(),"RECREATE");
  MyInfo("initialize()",Form("Output TFile for \"%s\", \"%s\" was created at %s.",
                             m_sel.c_str(), m_sys.c_str(), m_filename.c_str()) );

  // Booking histograms
  BookHistograms();

}

/*--------------------------------------------------------------------------------*/
// Finalize event selection
/*--------------------------------------------------------------------------------*/
void Plotter::finalize()
{
  MyDebug("finalize()","Plotter::finalize()");

  m_rootfile->cd();
  h_xsec->Write();
  h_nEve->Write();
  h_lepChan[Ch_all]->Write();
  for(uint iCh=0; iCh<nChan; iCh++){
    h_lep1Pt [iCh]->Write();
    h_lep2Pt [iCh]->Write();
    h_lep3Pt [iCh]->Write();
    h_el1Pt  [iCh]->Write();
    h_el2Pt  [iCh]->Write();
    h_el3Pt  [iCh]->Write();
    h_mu1Pt  [iCh]->Write();
    h_mu2Pt  [iCh]->Write();
    h_mu3Pt  [iCh]->Write();
    h_lep1Eta[iCh]->Write();
    h_lep2Eta[iCh]->Write();
    h_lep3Eta[iCh]->Write();
  }

  m_rootfile->Close();
  delete m_rootfile;
}

/*--------------------------------------------------------------------------------*/
bool Plotter::BookHistograms()
{
  MyDebug("BookHistograms()","Plotter::BookHistograms()");

  std::vector<std::string> vec_chan; vec_chan.clear();
  vec_chan.push_back("all");
  vec_chan.push_back("eee");
  vec_chan.push_back("eem");
  vec_chan.push_back("emm");
  vec_chan.push_back("mmm");

  // Preprocessor convenience                                                                                 
  // make a histogram by name (leave off the "h_") and binning
#define NEWHIST(name, xLbl, nbin, min, max)                             \
  h_ ## name[iCh] = new TH1F((chanName+"_"+#name).c_str(), #name ";" xLbl, nbin, min, max);
#define NEWVARHIST(name, xLbl, nbin, bins)                              \
  h_ ## name[iCh] = new TH1F((chanName+"_"+#name).c_str(), #name ";" xLbl, nbin, bins);
  // shorthand way to set bin labels, since it is kind of gross                                               
#define SETBINLABEL(name, bin, label)                         \
  h_ ## name[iCh]->GetXaxis()->SetBinLabel(bin, label)
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
  h_xsec->SetBinContent(h_xsec->FindBin(0.),m_crossSection); //set cross-section

  // Lepton channel histo, only defined for the 'all' channel
  h_lepChan       [Ch_all] = new TH1F("all_lepChan"       ,"all_lepChan;Unordered lepton channel;Events", nChan, 0, nChan);
  // lepton channel loop
  for(uint iCh=0; iCh<nChan; iCh++){
    std::string chanName = vec_chan.at(iCh);
    h_lepChan[Ch_all]->GetXaxis()->SetBinLabel(iCh+1, chanName.c_str());
    // lep pt - my choice of binning                                                                            
    NEWVARHIST( lep1Pt, "Leading lepton_{} P_{T} [GeV];Events", nLep1PtBins, lep1PtBins );
    NEWVARHIST( lep2Pt, "Second lepton_{} P_{T} [GeV];Events", nLep2PtBins, lep2PtBins );
    NEWVARHIST( lep3Pt, "Third lepton_{} P_{T} [GeV];Events", nLep3PtBins, lep3PtBins );
    NEWVARHIST( el1Pt, "Leading electron_{} P_{T} [GeV];Events", nLep1PtBins, lep1PtBins );
    NEWVARHIST( el2Pt, "Second electron_{} P_{T} [GeV];Events", nLep2PtBins, lep2PtBins );
    NEWVARHIST( el3Pt, "Third electron_{} P_{T} [GeV];Events", nLep3PtBins, lep3PtBins );
    NEWVARHIST( mu1Pt, "Leading muon_{} P_{T} [GeV];Events", nLep1PtBins, lep1PtBins );
    NEWVARHIST( mu2Pt, "Second muon_{} P_{T} [GeV];Events", nLep2PtBins, lep2PtBins );
    NEWVARHIST( mu3Pt, "Third muon_{} P_{T} [GeV];Events", nLep3PtBins, lep3PtBins );

    ETAHIST( lep1Eta, "Leading lepton #eta;Events" );
    ETAHIST( lep2Eta, "Second lepton #eta;Events" );
    ETAHIST( lep3Eta, "Third lepton #eta;Events" );
  }

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
/*--------------------------------------------------------------------------------*/
bool Plotter::FillHistograms(EventSelector *EveSelec, double weight)
{
  MyDebug("FillHistograms()","Plotter::FillHistograms()");

  //Retrieving objects via EventSelector
  std::vector< xAOD::Electron >* vec_signalElectron = EveSelec->GetSignalElectron();
  // std::vector< xAOD::Electron >* vec_baseElectron   = EveSelec->GetBaseElectron  ();
  std::vector< xAOD::Muon >*     vec_signalMuon     = EveSelec->GetSignalMuon    ();
  // std::vector< xAOD::Muon >*     vec_baseMuon       = EveSelec->GetBaseMuon      ();
  // std::vector< xAOD::Jet >*      vec_signalJet      = EveSelec->GetSignalJet     ();
  // std::vector< xAOD::Jet >*      vec_baseJet        = EveSelec->GetBaseJet       ();
  // std::vector< xAOD::Jet >*      vec_preJet         = EveSelec->GetPreJet        ();
  // TVector2                       met                = EveSelec->GetMEt           ();

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
  MyDebug("FillHistograms()",Form("Analized channel : %d",chan));
  if(chan<0) return false;

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
  Double_t w = weight*EveSelec->getTotalSF();

  // Preprocessor convenience
  // All this does is append the corrent indices to the histo for sys and channel
  // It also fills the all-channel histo 
#define FillChanHist( h, val, w )               \
  do{                                           \
    h[Ch_all]->Fill(val,w);                     \
    h[chan]->Fill(val,w);                       \
  } while(0)
#define FillChanHist2D( h, xVal, yVal, w )      \
  do{                                           \
    h[Ch_all]->Fill(xVal, yVal, w);             \
    h[chan]->Fill(xVal, yVal, w);               \
  } while(0)
#define FillElHist( index, h, val, w )                  \
  do{                                                   \
    if(leadLepFlavor[index]==0) h[Ch_all]->Fill(val,w); \
    if(leadLepFlavor[index]==0) h[chan]->Fill(val,w);   \
  } while(0)
#define FillMuHist( index, h, val, w )                  \
  do{                                                   \
    if(leadLepFlavor[index]==1) h[Ch_all]->Fill(val,w); \
    if(leadLepFlavor[index]==1) h[chan]->Fill(val,w);   \
  } while(0)
  //Fill lepChan histograms
  h_lepChan       [Ch_all]->Fill(Ch_all,w);
  h_lepChan       [Ch_all]->Fill(chan,w);

  //Fill lepton Pt
  FillChanHist( h_lep1Pt, leadLep[0].Pt()/1000., w );
  FillChanHist( h_lep2Pt, leadLep[1].Pt()/1000., w );
  FillChanHist( h_lep3Pt, leadLep[2].Pt()/1000., w );
  FillElHist( 0, h_el1Pt, vec_signalElectron->at(leadLepIndex[0]).pt()/1000., w );
  FillMuHist( 0, h_mu1Pt, vec_signalMuon    ->at(leadLepIndex[0]).pt()/1000., w );
  FillElHist( 1, h_el2Pt, vec_signalElectron->at(leadLepIndex[1]).pt()/1000., w );
  FillMuHist( 1, h_mu2Pt, vec_signalMuon    ->at(leadLepIndex[1]).pt()/1000., w );
  FillElHist( 2, h_el3Pt, vec_signalElectron->at(leadLepIndex[2]).pt()/1000., w );
  FillMuHist( 2, h_mu3Pt, vec_signalMuon    ->at(leadLepIndex[2]).pt()/1000., w );

  //Fill lepton Eta
  FillChanHist( h_lep1Eta, leadLep[0].Eta(), w );
  FillChanHist( h_lep2Eta, leadLep[1].Eta(), w );
  FillChanHist( h_lep3Eta, leadLep[2].Eta(), w );

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
bool Plotter::FillNEvent(double weight)
{
  MyDebug("FillNEvent()","Plotter::FillNEvent()");
  h_nEve->Fill(0., weight);
  return true;
}
