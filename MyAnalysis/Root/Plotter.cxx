#define APP_NAME "Plotter"
#define MyVerbose(a,b) if(m_dbg<=MSG::VERBOSE) std::cout<<"Verbose in <Plotter::"<<(a)<<">: "<< m_sel.c_str() << "," << m_sys << " : "<<(b)<<std::endl;
#define MyDebug(a,b) if(m_dbg<=MSG::DEBUG) std::cout<<"Debug in <Plotter::"<<(a)<<">: "<< m_sel.c_str() << "," << m_sys << " : "<<(b)<<std::endl;
#define MyInfo(a,b) if(m_dbg<=MSG::INFO) std::cout<<"Info in <Plotter::"<<(a)<<">: "<< m_sel.c_str() << "," << m_sys << " : "<<(b)<<std::endl;
#define MyError(a,b) if(m_dbg<=MSG::ERROR) std::cout<<"Error in <Plotter::"<<(a)<<">: "<< m_sel.c_str() << "," << m_sys << " : "<<(b)<<std::endl;
#define MyAlways(a,b) if(m_dbg<=MSG::ALWAYS) std::cout<<"In <Plotter::"<<(a)<<">: "<< m_sel.c_str() << "," << m_sys << " : "<<(b)<<std::endl;

#include<iostream>
#include"MyAnalysis/Plotter.h"
#include"SUSYTools/SUSYObjDef_xAOD.h"
#include"xAODEgamma/EgammaxAODHelpers.h"
#include"MyAnalysis/MCTruthClassifierDefs.h"

#include"TFile.h"
#include"TH1F.h"
#include"TH2F.h"

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
Plotter::Plotter(const std::string& sel, const std::string& sys, const MSG::Level& dbg) : 
  m_dbg(dbg),
  m_sel(sel),
  m_sys(sys),
  m_filename(""),
  m_crossSection(0.),
  m_isMC(kFALSE)
{}

/*--------------------------------------------------------------------------------*/
// Initialize the plotter
/*--------------------------------------------------------------------------------*/
void Plotter::initialize(const char* path, int dsid, double XS, TFile* file)
{
  MyDebug("initialize()","Plotter::initialize()");

  m_crossSection = XS;
  if(m_crossSection>0.) m_isMC = kTRUE;

  // Preparing TFile
  if(file==NULL){
    m_filename = Form("%s/%d.%s.%s.AnaHists.root",path,dsid,m_sel.c_str(),m_sys.c_str());
    m_rootfile = new TFile(m_filename.c_str(),"RECREATE");
  }else{
    m_filename = file->GetName();
    m_rootfile = file;
  }
  m_rootfile->cd();
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
  h_nSigBaseLep->Write();
  h_lepChan[Ch_all]->Write();
  h_baselepChan[Ch_all]->Write();
  for(uint iCh=0; iCh<nChan; iCh++){
    h_lep1Pt[iCh]->Write();
    h_lep2Pt[iCh]->Write();
    h_lep3Pt[iCh]->Write();
    h_el1Pt[iCh]->Write();
    h_el2Pt[iCh]->Write();
    h_el3Pt[iCh]->Write();
    h_mu1Pt[iCh]->Write();
    h_mu2Pt[iCh]->Write();
    h_mu3Pt[iCh]->Write();
    h_lep1Eta[iCh]->Write();
    h_lep2Eta[iCh]->Write();
    h_lep3Eta[iCh]->Write();
    h_el1Eta[iCh]->Write();
    h_el2Eta[iCh]->Write();
    h_el3Eta[iCh]->Write();
    h_mu1Eta[iCh]->Write();
    h_mu2Eta[iCh]->Write();
    h_mu3Eta[iCh]->Write();
    h_PRlep1Pt[iCh]->Write();
    h_PRlep2Pt[iCh]->Write();
    h_PRlep3Pt[iCh]->Write();
    h_COlep1Pt[iCh]->Write();
    h_COlep2Pt[iCh]->Write();
    h_COlep3Pt[iCh]->Write();
    h_HFlep1Pt[iCh]->Write();
    h_HFlep2Pt[iCh]->Write();
    h_HFlep3Pt[iCh]->Write();
    h_LFlep1Pt[iCh]->Write();
    h_LFlep2Pt[iCh]->Write();
    h_LFlep3Pt[iCh]->Write();
    h_UKlep1Pt[iCh]->Write();
    h_UKlep2Pt[iCh]->Write();
    h_UKlep3Pt[iCh]->Write();
    h_baselep1Pt[iCh]->Write();
    h_baselep2Pt[iCh]->Write();
    h_baselep3Pt[iCh]->Write();
    h_baseel1Pt[iCh]->Write();
    h_baseel2Pt[iCh]->Write();
    h_baseel3Pt[iCh]->Write();
    h_basemu1Pt[iCh]->Write();
    h_basemu2Pt[iCh]->Write();
    h_basemu3Pt[iCh]->Write();
    h_baselep1Eta[iCh]->Write();
    h_baselep2Eta[iCh]->Write();
    h_baselep3Eta[iCh]->Write();
    h_llPt[iCh]->Write();
    h_sumLepPt[iCh]->Write();
    h_sumLepPtMet[iCh]->Write();
    h_dPhiWZ[iCh]->Write();
    h_nMuComb[iCh]->Write();
    h_elPtcone30[iCh]->Write();
    h_elEtcone30[iCh]->Write();
    h_muPtcone30[iCh]->Write();
    h_muEtcone30[iCh]->Write();
    h_lepD0[iCh]->Write();
    h_lep1D0[iCh]->Write();
    h_lep2D0[iCh]->Write();
    h_lep3D0[iCh]->Write();
    h_lepZ0[iCh]->Write();
    h_lep1Z0[iCh]->Write();
    h_lep2Z0[iCh]->Write();
    h_lep3Z0[iCh]->Write();
    h_lepD0Sig[iCh]->Write();
    h_lep1D0Sig[iCh]->Write();
    h_lep2D0Sig[iCh]->Write();
    h_lep3D0Sig[iCh]->Write();
    h_lepZ0SinTheta[iCh]->Write();
    h_lep1Z0SinTheta[iCh]->Write();
    h_lep2Z0SinTheta[iCh]->Write();
    h_lep3Z0SinTheta[iCh]->Write();
    h_lepOrigin[iCh]->Write();
    h_lep1Origin[iCh]->Write();
    h_lep2Origin[iCh]->Write();
    h_lep3Origin[iCh]->Write();
    h_lepClass[iCh]->Write();
    h_lep1Class[iCh]->Write();
    h_lep2Class[iCh]->Write();
    h_lep3Class[iCh]->Write();
    h_hasSS[iCh]->Write();
    h_baselepOrigin[iCh]->Write();
    h_baselep1Origin[iCh]->Write();
    h_baselep2Origin[iCh]->Write();
    h_baselep3Origin[iCh]->Write();
    h_baselepClass[iCh]->Write();
    h_baselep1Class[iCh]->Write();
    h_baselep2Class[iCh]->Write();
    h_baselep3Class[iCh]->Write();
    h_nTau[iCh]->Write();
    h_tauPt[iCh]->Write();
    h_tau1Pt[iCh]->Write();
    h_tau2Pt[iCh]->Write();
    h_tau1Eta[iCh]->Write();
    h_tau2Eta[iCh]->Write();
    h_tauProng[iCh]->Write();
    h_dPhiTauTau[iCh]->Write();
    h_tauClass[iCh]->Write();
    h_tau1Class[iCh]->Write();
    h_tau2Class[iCh]->Write();
    h_minDRLepLep[iCh]->Write();
    h_dPhiLep1Met[iCh]->Write();
    h_dPhiLep2Met[iCh]->Write();
    h_dPhiLep3Met[iCh]->Write();
    h_dPhiLLMet[iCh]->Write();
    h_dPhiJet1Met[iCh]->Write();
    h_dPhiJet2Met[iCh]->Write();
    h_dPhiJJMet[iCh]->Write();
    h_minDPhiLepLep[iCh]->Write();
    h_minDPhiLepMet[iCh]->Write();
    h_minDPhiJetJet[iCh]->Write();
    h_minDPhiJetMet[iCh]->Write();
    h_minDPhiTauMet[iCh]->Write();
    h_minDRLepJet[iCh]->Write();
    h_maxDPhiLepLep[iCh]->Write();
    h_maxDPhiLepMet[iCh]->Write();
    h_maxDPhiJetJet[iCh]->Write();
    h_maxDPhiJetMet[iCh]->Write();
    h_maxDRLepJet[iCh]->Write();
    h_dEtaLL[iCh]->Write();
    h_dEtaJetJet[iCh]->Write();
    h_maxDEtaJetJet[iCh]->Write();
    h_minDEtaJetJet[iCh]->Write();
    h_met[iCh]->Write();
    h_meff[iCh]->Write();
    h_meffNoMet[iCh]->Write();
    h_metEle[iCh]->Write();
    h_metMuo[iCh]->Write();
    h_metJet[iCh]->Write();
    h_metCell[iCh]->Write();
    h_metRel[iCh]->Write();
    h_nJet[iCh]->Write();
    h_nBJet[iCh]->Write();
    h_jetPt[iCh]->Write();
    h_jet1Pt[iCh]->Write();
    h_jet2Pt[iCh]->Write();
    h_jet3Pt[iCh]->Write();
    h_bJetPt[iCh]->Write();
    h_bJet1Pt[iCh]->Write();
    h_bJet2Pt[iCh]->Write();
    h_bJet3Pt[iCh]->Write();
    h_jetEta[iCh]->Write();
    h_bJetEta[iCh]->Write();
    h_bJet1Eta[iCh]->Write();
    h_bJet2Eta[iCh]->Write();
    h_bJet3Eta[iCh]->Write();
    h_jetPhi[iCh]->Write();
    h_jetMV1[iCh]->Write();
    h_jetJVF[iCh]->Write();
    h_bJetJVF[iCh]->Write();
    h_dijetM[iCh]->Write();
    h_productEta1Eta2[iCh]->Write();
    h_mll[iCh]->Write();
    h_msfos[iCh]->Write();
    h_minMsfos[iCh]->Write();
    h_msfss[iCh]->Write();
    h_mlll[iCh]->Write();
    h_mt[iCh]->Write();
    h_mtL1[iCh]->Write();
    h_mtL2[iCh]->Write();
    h_mt2[iCh]->Write();
    h_mjj[iCh]->Write();
    h_mlljj[iCh]->Write();
    h_mlt[iCh]->Write();
    h_mtt[iCh]->Write();
    h_mbb[iCh]->Write();
    h_mljj[iCh]->Write();
    h_mljjFine[iCh]->Write();
    h_mtll[iCh]->Write();
    h_mtll_mt[iCh]->Write();
    h_nVtx[iCh]->Write();
    h_mu[iCh]->Write();
  }

  MyAlways("finalize()",Form("Finalizing TFile: %s",m_rootfile->GetName()));
  if(m_sys!=""){
    m_rootfile->Close();
    delete m_rootfile;
  }
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
#define NEWVARHIST2D(name, lbl, nXbin, xBins, nYBin, yBins) \
  h_ ## name[iCh] = new TH2F((chanName+"_"+#name).c_str(), #name ";" lbl, nXbin, xBins, nYBin, yBins);
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
  h_nSigBaseLep = new TH2F("h_nSigBaseLep","h_nSigBaseLep;#Baseline Lep.;#Signal Lep.;Events",8,0.-0.5,8.-0.5,8,0.-0.5,8.-0.5);

  // Lepton channel histo, only defined for the 'all' channel
  h_lepChan    [Ch_all] = new TH1F("all_lepChan"    ,"all_lepChan;Unordered lepton channel;Events", nChan, 0, nChan);
  h_baselepChan[Ch_all] = new TH1F("all_baselepChan","all_baselepChan;Unordered lepton channel;Events", nChan, 0, nChan);
  // lepton channel loop
  for(uint iCh=0; iCh<nChan; iCh++){
    std::string chanName = vec_chan.at(iCh);
    h_lepChan[Ch_all]->GetXaxis()->SetBinLabel(iCh+1, chanName.c_str());
    h_baselepChan[Ch_all]->GetXaxis()->SetBinLabel(iCh+1, chanName.c_str());
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

    NEWVARHIST( PRlep1Pt, "Leading PR lepton_{} P_{T} [GeV];Events", nLep1PtBins, lep1PtBins );
    NEWVARHIST( PRlep2Pt,  "Second PR lepton_{} P_{T} [GeV];Events", nLep2PtBins, lep2PtBins );
    NEWVARHIST( PRlep3Pt,   "Third PR lepton_{} P_{T} [GeV];Events", nLep3PtBins, lep3PtBins );
    NEWVARHIST( COlep1Pt, "Leading CO lepton_{} P_{T} [GeV];Events", nLep1PtBins, lep1PtBins );
    NEWVARHIST( COlep2Pt,  "Second CO lepton_{} P_{T} [GeV];Events", nLep2PtBins, lep2PtBins );
    NEWVARHIST( COlep3Pt,   "Third CO lepton_{} P_{T} [GeV];Events", nLep3PtBins, lep3PtBins );
    NEWVARHIST( HFlep1Pt, "Leading HF lepton_{} P_{T} [GeV];Events", nLep1PtBins, lep1PtBins );
    NEWVARHIST( HFlep2Pt,  "Second HF lepton_{} P_{T} [GeV];Events", nLep2PtBins, lep2PtBins );
    NEWVARHIST( HFlep3Pt,   "Third HF lepton_{} P_{T} [GeV];Events", nLep3PtBins, lep3PtBins );
    NEWVARHIST( LFlep1Pt, "Leading LF lepton_{} P_{T} [GeV];Events", nLep1PtBins, lep1PtBins );
    NEWVARHIST( LFlep2Pt,  "Second LF lepton_{} P_{T} [GeV];Events", nLep2PtBins, lep2PtBins );
    NEWVARHIST( LFlep3Pt,   "Third LF lepton_{} P_{T} [GeV];Events", nLep3PtBins, lep3PtBins );
    NEWVARHIST( UKlep1Pt, "Leading UK lepton_{} P_{T} [GeV];Events", nLep1PtBins, lep1PtBins );
    NEWVARHIST( UKlep2Pt,  "Second UK lepton_{} P_{T} [GeV];Events", nLep2PtBins, lep2PtBins );
    NEWVARHIST( UKlep3Pt,   "Third UK lepton_{} P_{T} [GeV];Events", nLep3PtBins, lep3PtBins );

    // lep eta
    ETAHIST( lep1Eta, "Leading lepton #eta;Events" );
    ETAHIST( lep2Eta, "Second lepton #eta;Events" );
    ETAHIST( lep3Eta, "Third lepton #eta;Events" );
    ETAHIST( el1Eta, "Leading electron #eta;Events" );
    ETAHIST( el2Eta, "Second electron #eta;Events" );
    ETAHIST( el3Eta, "Third electron #eta;Events" );
    ETAHIST( mu1Eta, "Leading muon #eta;Events" );
    ETAHIST( mu2Eta, "Second muon #eta;Events" );
    ETAHIST( mu3Eta, "Third muon #eta;Events" );

    // baseline lep pt
    NEWVARHIST( baselep1Pt, "Leading baseline lepton_{} P_{T} [GeV];Events", nLep1PtBins, lep1PtBins );
    NEWVARHIST( baselep2Pt, "Second baseline lepton_{} P_{T} [GeV];Events", nLep2PtBins, lep2PtBins );
    NEWVARHIST( baselep3Pt, "Third baseline lepton_{} P_{T} [GeV];Events", nLep3PtBins, lep3PtBins );
    NEWVARHIST( baseel1Pt, "Leading baseline electron_{} P_{T} [GeV];Events", nLep1PtBins, lep1PtBins );
    NEWVARHIST( baseel2Pt, "Second baseline electron_{} P_{T} [GeV];Events", nLep2PtBins, lep2PtBins );
    NEWVARHIST( baseel3Pt, "Third baseline electron_{} P_{T} [GeV];Events", nLep3PtBins, lep3PtBins );
    NEWVARHIST( basemu1Pt, "Leading baseline muon_{} P_{T} [GeV];Events", nLep1PtBins, lep1PtBins );
    NEWVARHIST( basemu2Pt, "Second baseline muon_{} P_{T} [GeV];Events", nLep2PtBins, lep2PtBins );
    NEWVARHIST( basemu3Pt, "Third baseline muon_{} P_{T} [GeV];Events", nLep3PtBins, lep3PtBins );

    // baseline lep eta
    ETAHIST( baselep1Eta, "Leading baseline lepton #eta;Events" );
    ETAHIST( baselep2Eta, "Second baseline lepton #eta;Events" );
    ETAHIST( baselep3Eta, "Third baseline lepton #eta;Events" );

    // lepton system pt
    NEWVARHIST( llPt, "P_{T}(lep,lep) [GeV];Events", nLep1PtBins, lep1PtBins );

    // sum of lepton pt and MET
    NEWVARHIST( sumLepPt, "#Sigma |lepton P_{T}| [GeV];Events", nMeffBins, meffBins );
    NEWVARHIST( sumLepPtMet, "#Sigma |lepton_{} P_{T}| + |MET| [GeV];Events", nMeffBins, meffBins );

    // dPhi WZ
    DPHIHIST( dPhiWZ, "dPhi(SFOS,l);Events" );

    // combined muons
    NEWHIST( nMuComb, "Number of combined muons;Events", 4, -0.5, 3.5 );

    // isolation vars
    NEWHIST( elPtcone30, "Electron ptcone30 [GeV];Events", 50, 0, 50 );
    NEWHIST( elEtcone30, "Electron topo etcone30 [GeV];Events", 50, 0, 50 );
    NEWHIST( muPtcone30, "Muon ptcone30 [GeV];Events", 50, 0, 50 );
    NEWHIST( muEtcone30, "Muon etcone30 [GeV];Events", 50, 0, 50 );

    // impact parameters
    NEWHIST( lepD0, "Lepton |d0| [mm];Events", 20, 0, 0.5 );
    NEWHIST( lep1D0, "Leading lepton |d0| [mm];Events", 20, 0, 0.5 );
    NEWHIST( lep2D0, "Second lepton |d0| [mm];Events", 20, 0, 0.5 );
    NEWHIST( lep3D0, "Third lepton |d0| [mm];Events", 20, 0, 0.5 );
    NEWHIST( lepZ0, "Lepton |z0| [mm];Events", 20, 0, 0.5 );
    NEWHIST( lep1Z0, "Leading lepton |z0| [mm];Events", 20, 0, 0.5 );
    NEWHIST( lep2Z0, "Second lepton |z0| [mm];Events", 20, 0, 0.5 );
    NEWHIST( lep3Z0, "Third lepton |z0| [mm];Events", 20, 0, 0.5 );
    NEWHIST( lepD0Sig, "Lepton |d0/#sigma_{d0}|;Events", 20, 0, 3.0 );
    NEWHIST( lep1D0Sig, "Leading lepton |d0/#sigma_{d0}|;Events", 20, 0, 3.0 );
    NEWHIST( lep2D0Sig, "Second lepton |d0/#sigma_{d0}|;Events", 20, 0, 3.0 );
    NEWHIST( lep3D0Sig, "Third lepton |d0/#sigma_{d0}|;Events", 20, 0, 3.0 );
    NEWHIST( lepZ0SinTheta, "Lepton |z0sin#theta| [mm];Events", 20, 0, 0.5 );
    NEWHIST( lep1Z0SinTheta, "Leading lepton |z0sin#theta| [mm];Events", 20, 0, 0.5 );
    NEWHIST( lep2Z0SinTheta, "Second lepton |z0sin#theta| [mm];Events", 20, 0, 0.5 );
    NEWHIST( lep3Z0SinTheta, "Third lepton |z0sin#theta| [mm];Events", 20, 0, 0.5 );

    // lepton truth matching
    NEWHIST( lepOrigin, "Lepton truth origin;Leptons", PARTICLETYPES, 0, PARTICLETYPES );
    NEWHIST( lep1Origin, "Leading lepton truth origin;Events", PARTICLETYPES, 0, PARTICLETYPES );
    NEWHIST( lep2Origin, "Second lepton truth origin;Events", PARTICLETYPES, 0, PARTICLETYPES );
    NEWHIST( lep3Origin, "Third lepton truth origin;Events", PARTICLETYPES, 0, PARTICLETYPES );
    NEWHIST( lepClass, "Lepton truth classification;Leptons", 5, 0, 5 );
    NEWHIST( lep1Class, "Leading lepton truth classification;Events", 5, 0, 5 );
    NEWHIST( lep2Class, "Second lepton truth classification;Events", 5, 0, 5 );
    NEWHIST( lep3Class, "Third lepton truth classification;Events", 5, 0, 5 );
    SETBINLABEL( lepClass, 1, "PR" ); 
    SETBINLABEL( lep1Class, 1, "PR" ); 
    SETBINLABEL( lep2Class, 1, "PR" );
    SETBINLABEL( lep3Class, 1, "PR" );
    SETBINLABEL( lepClass, 2, "CO" ); 
    SETBINLABEL( lep1Class, 2, "CO" ); 
    SETBINLABEL( lep2Class, 2, "CO" );
    SETBINLABEL( lep3Class, 2, "CO" );
    SETBINLABEL( lepClass, 3, "HF" ); 
    SETBINLABEL( lep1Class, 3, "HF" ); 
    SETBINLABEL( lep2Class, 3, "HF" );
    SETBINLABEL( lep3Class, 3, "HF" );
    SETBINLABEL( lepClass, 4, "LF" ); 
    SETBINLABEL( lep1Class, 4, "LF" ); 
    SETBINLABEL( lep2Class, 4, "LF" );
    SETBINLABEL( lep3Class, 4, "LF" );
    SETBINLABEL( lepClass, 5, "UK" ); 
    SETBINLABEL( lep1Class, 5, "UK" ); 
    SETBINLABEL( lep2Class, 5, "UK" );
    SETBINLABEL( lep3Class, 5, "UK" );

    NEWHIST( hasSS, "has SS light leptons;Events", 2, 0, 2 );

    // lepton truth matching
    NEWHIST( baselepOrigin, "Base lepton truth origin;Leptons", PARTICLETYPES, 0, PARTICLETYPES );
    NEWHIST( baselep1Origin, "Leading base lepton truth origin;Events", PARTICLETYPES, 0, PARTICLETYPES );
    NEWHIST( baselep2Origin, "Second base lepton truth origin;Events", PARTICLETYPES, 0, PARTICLETYPES );
    NEWHIST( baselep3Origin, "Third base lepton truth origin;Events", PARTICLETYPES, 0, PARTICLETYPES );
    NEWHIST( baselepClass, "Base lepton truth classification;Leptons", 5, 0, 5 );
    NEWHIST( baselep1Class, "Leading base lepton truth classification;Events", 5, 0, 5 );
    NEWHIST( baselep2Class, "Second base lepton truth classification;Events", 5, 0, 5 );
    NEWHIST( baselep3Class, "Third base lepton truth classification;Events", 5, 0, 5 );
    SETBINLABEL( baselepClass, 1, "PR" ); 
    SETBINLABEL( baselep1Class, 1, "PR" ); 
    SETBINLABEL( baselep2Class, 1, "PR" );
    SETBINLABEL( baselep3Class, 1, "PR" );
    SETBINLABEL( baselepClass, 2, "CO" ); 
    SETBINLABEL( baselep1Class, 2, "CO" ); 
    SETBINLABEL( baselep2Class, 2, "CO" );
    SETBINLABEL( baselep3Class, 2, "CO" );
    SETBINLABEL( baselepClass, 3, "HF" ); 
    SETBINLABEL( baselep1Class, 3, "HF" ); 
    SETBINLABEL( baselep2Class, 3, "HF" );
    SETBINLABEL( baselep3Class, 3, "HF" );
    SETBINLABEL( baselepClass, 4, "LF" ); 
    SETBINLABEL( baselep1Class, 4, "LF" ); 
    SETBINLABEL( baselep2Class, 4, "LF" );
    SETBINLABEL( baselep3Class, 4, "LF" );
    SETBINLABEL( baselepClass, 5, "UK" ); 
    SETBINLABEL( baselep1Class, 5, "UK" ); 
    SETBINLABEL( baselep2Class, 5, "UK" );
    SETBINLABEL( baselep3Class, 5, "UK" );

    // tau kinematics
    NEWHIST( nTau, "Number of taus;Events", 6, -0.5, 5.5 );
    NEWVARHIST( tauPt, "Tau P_{T} [GeV];Taus", nLep1PtBins, lep1PtBins );
    NEWVARHIST( tau1Pt, "Leading tau_{} P_{T} [GeV];Events", nLep1PtBins, lep1PtBins );
    NEWVARHIST( tau2Pt, "Second tau_{} P_{T} [GeV];Events", nLep2PtBins, lep2PtBins );
    ETAHIST( tau1Eta, "Leading tau #eta;Events" );
    ETAHIST( tau2Eta, "Second tau #eta;Events" );
    DPHIHIST( dPhiTauTau, "dPhi(tau1, tau2);Events" );
    NEWHIST( tauProng, "Tau prong;Taus", 2, 0, 2 );
    SETBINLABEL( tauProng, 1, "1" );
    SETBINLABEL( tauProng, 2, "3" );
    NEWHIST( tauClass, "Tau truth classification;Taus", 5, 0, 5 );
    NEWHIST( tau1Class, "Leading tau truth classification;Taus", 5, 0, 5 );
    NEWHIST( tau2Class, "Second tau truth classification;Taus", 5, 0, 5 );
    SETBINLABEL( tauClass, 1, "PR" ); 
    SETBINLABEL( tau1Class, 1, "PR" ); 
    SETBINLABEL( tau2Class, 1, "PR" );
    SETBINLABEL( tauClass, 2, "CO" ); 
    SETBINLABEL( tau1Class, 2, "CO" ); 
    SETBINLABEL( tau2Class, 2, "CO" );
    SETBINLABEL( tauClass, 3, "HF" ); 
    SETBINLABEL( tau1Class, 3, "HF" ); 
    SETBINLABEL( tau2Class, 3, "HF" );
    SETBINLABEL( tauClass, 4, "LF" ); 
    SETBINLABEL( tau1Class, 4, "LF" ); 
    SETBINLABEL( tau2Class, 4, "LF" );
    SETBINLABEL( tauClass, 5, "UK" ); 
    SETBINLABEL( tau1Class, 5, "UK" ); 
    SETBINLABEL( tau2Class, 5, "UK" );

    // dR, dPhi plots
    DRHIST( minDRLepLep, "min dR(lep, lep);Events" );
    DPHIHIST( dPhiLep1Met, "dPhi(lep1, MET);Events" );
    DPHIHIST( dPhiLep2Met, "dPhi(lep2, MET);Events" );
    DPHIHIST( dPhiLep3Met, "dPhi(lep3, MET);Events" );
    DPHIHIST( dPhiLLMet, "dPhi(lep1+lep2, MET);Events" );
    DPHIHIST( dPhiJet1Met, "dPhi(jet1, MET);Events" );
    DPHIHIST( dPhiJet2Met, "dPhi(jet2, MET);Events" );
    DPHIHIST( dPhiJJMet, "dPhi(jet1+jet2, MET);Events" );
    DPHIHIST( minDPhiLepLep, "min dPhi(lep, lep);Events" );
    DPHIHIST( minDPhiLepMet, "min dPhi(lep, MET);Events" );
    DPHIHIST( minDPhiJetJet, "min dPhi(jet, jet);Events" );
    DPHIHIST( minDPhiJetMet, "min dPhi(jet, MET);Events" );
    DPHIHIST( minDPhiTauMet, "min dPhi(tau, MET);Events" );
    DRHIST( minDRLepJet, "min dR(lep, Jet);Events" );
    DPHIHIST( maxDPhiLepLep, "max dPhi(lep, lep);Events" );
    DPHIHIST( maxDPhiLepMet, "max dPhi(lep, MET);Events" );
    DPHIHIST( maxDPhiJetJet, "max dPhi(jet, jet);Events" );
    DPHIHIST( maxDPhiJetMet, "max dPhi(jet, MET);Events" );
    DRHIST( maxDRLepJet, "max dR(lep, Jet);Events" );
    NEWHIST( dEtaLL, "#Delta#eta(lep, lep);Events", 30, 0, 3 );
    NEWHIST( dEtaJetJet, "#Delta#eta(jet, jet);Events", 20, 0, 8 );
    NEWHIST( maxDEtaJetJet, "max #Delta#eta(jet, jet);Events", 20, 0, 8 );
    NEWHIST( minDEtaJetJet, "min #Delta#eta(jet, jet);Events", 20, 0, 8 );

    // mass plots
    NEWHIST( mll, "M_{ll} [GeV];Events", 50, 50, 150 );
    ZMASSHIST( msfos, "M_{SFOS} [GeV];Events" );
    NEWHIST( minMsfos, "min M_{SFOS} [GeV];Events", 50, 0., 150 );
    NEWHIST( msfss, "M_{SFSS} [GeV];SFSS lepton pairs", 50, 0, 500 );
    NEWVARHIST( mlll, "M_{lll} [GeV];Events", nMassBins, massBins );
    //NEWHIST( mlll, "M_{lll} [GeV];Events", 50, 0, 1000 );
    NEWVARHIST( mt, "M_{T} [GeV];Events", nMassBins, massBins );
    NEWVARHIST( mtL1, "M_{T}(lep1, MET) [GeV];Events", nMassBins, massBins );
    NEWVARHIST( mtL2, "M_{T}(lep2, MET) [GeV];Events", nMassBins, massBins );
    NEWVARHIST( mt2, "M_{T2} [GeV];Events", nMassBins, massBins );
    NEWVARHIST( meff, "M_{eff} [GeV];Events", nMeffBins, meffBins );
    NEWVARHIST( meffNoMet, "M_{eff} (No MET) [GeV];Events", nMeffBins, meffBins );
    NEWVARHIST( mjj, "M_{jj} [GeV];Events", nMassBins, massBins );
    NEWHIST( mlljj, "M_{lljj} [GeV];Events", 40, 0, 1000 );
    NEWVARHIST( mlt, "M_{l#tau} [GeV];Lepton-tau pairs", nMassBins, massBins );
    NEWVARHIST( mtt, "M_{#tau#tau} [GeV];Events", nMassBins, massBins );
    NEWVARHIST( mbb, "M_{bb} [GeV];Events", nMassBins, massBins );
    NEWVARHIST( mljj, "M_{ljj} [GeV];Events", nMeffBins, meffBins );
    NEWVARHIST( mljjFine, "M_{ljj} [GeV];Events", nMljjFineBins, mljjFineBins );
    NEWVARHIST( mtll, "M_{T}^{WW} [GeV];Events", nMassBins, massBins );
    NEWVARHIST2D( mtll_mt, "M_{T}^{WW} [GeV];M_{T} [GeV];Events", nMassBins, massBins, nMassBins, massBins );

    // MET
    //NEWVARHIST( met, "MET [GeV];Events", nMetBins, metBins );
    NEWHIST( met, "MET [GeV];Events", 30, 0, 450 );
    NEWHIST( metEle, "MET RefElectron [GeV];Events", 20, 0, 200 );
    NEWHIST( metMuo, "MET Muon [GeV];Events", 20, 0, 200 );
    NEWHIST( metJet, "MET RefJet [GeV];Events", 20, 0, 200 );
    NEWHIST( metCell, "MET CellOut [GeV];Events", 20, 0, 200 );
    NEWHIST( metRel, "MET rel [GeV];Events", 30, 0, 450 );

    // Jets
    NEWHIST( nJet, "Number of jets;Events", 17, -0.5, 16.5 );
    NEWHIST( nBJet, "Number of b jets;Events", 17, -0.5, 16.5 );

    PTHIST( jet1Pt, "Leading jet_{} P_{T} [GeV];Events" );
    PTHIST( jet2Pt, "Second jet_{} P_{T} [GeV];Events" );
    PTHIST( jet3Pt, "Third jet_{} P_{T} [GeV];Events" );
    NEWVARHIST( jetPt, "Jet P_{T} [GeV];Jets", nJetPtBins, jetPtBins );
    NEWVARHIST( bJetPt, "B Jet P_{T} [GeV];Jets", nJetPtBins, jetPtBins );
    NEWVARHIST( bJet1Pt, "Leading B Jet P_{T} [GeV];Events", nJetPtBins, jetPtBins );
    NEWVARHIST( bJet2Pt, "Second B Jet P_{T} [GeV];Events", nJetPtBins, jetPtBins );
    NEWVARHIST( bJet3Pt, "Third B Jet P_{T} [GeV];Events", nJetPtBins, jetPtBins );
    ETAHIST( jetEta, "Jet #eta;Jets" );
    ETAHIST( bJetEta, "B Jet #eta;Jets" );
    ETAHIST( bJet1Eta, "Leading B Jet #eta;Events" );
    ETAHIST( bJet2Eta, "Second B Jet #eta;Events" );
    ETAHIST( bJet3Eta, "Third B Jet #eta;Events" );
    NEWHIST( jetPhi, "Jet phi;Jets", 10, -3.1416, 3.1416 );
    NEWHIST( jetMV1, "Jet MV1;Jets", 20, 0., 1. );
    NEWHIST( jetJVF, "Jet JVF;Jets", 20, -1., 1. );
    NEWHIST( bJetJVF, "B Jet JVF;B Jets", 20, -1., 1. );
    NEWHIST( dijetM, "Mjj [GeV];Events", 20, 0, 1200 );
    NEWHIST( productEta1Eta2, "Eta1*Eta2;Events", 30, -10, 5. );

    // Pileup hists
    NEWHIST( nVtx, "Number of good vertices;Events", 40, 0, 40 );
    NEWHIST( mu, "Avg interactions per bunch crossing;Events", 40, 0, 40 );

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
bool Plotter::FillHistoPreSelec(EventSelector *EveSelec, double weight)
{
  MyDebug("FillHistoPreSelec()","Plotter::FillHistoPreSelec()");

  Double_t w = weight*EveSelec->getTotalSF();

  h_nSigBaseLep->Fill(EveSelec->nBaselineLeps(),EveSelec->nSignalLeps(),w);

  return true;
}
/*--------------------------------------------------------------------------------*/
bool Plotter::FillHistograms(EventSelector *EveSelec, double weight)
{
  MyDebug("FillHistograms()","Plotter::FillHistograms()");

  //Retrieving objects via EventSelector
  std::vector< xAOD::Electron >* vec_signalElectron = EveSelec->GetSignalElectron();
  std::vector< xAOD::Electron >* vec_baseElectron   = EveSelec->GetBaseElectron  ();
  std::vector< xAOD::Muon >*     vec_signalMuon     = EveSelec->GetSignalMuon    ();
  std::vector< xAOD::Muon >*     vec_baseMuon       = EveSelec->GetBaseMuon      ();
  std::vector< xAOD::Jet >*      vec_signalJet      = EveSelec->GetSignalJet     ();
  // std::vector< xAOD::Jet >*      vec_baseJet        = EveSelec->GetBaseJet       ();
  // std::vector< xAOD::Jet >*      vec_preJet         = EveSelec->GetPreJet        ();
  TVector2                       met                = EveSelec->GetMEt           ();

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

  //Prepare 1st-3rd leading signal lepton's four-vector
  Int_t leadLepIndex[3];
  Int_t leadLepFlavor[3];
  TLorentzVector leadLep[3];
  for(Int_t id=0; id<3; id++){
    leadLepIndex [id] = EveSelec->getLeadLepIndex (id);
    leadLepFlavor[id] = EveSelec->getLeadLepFlavor(id);
    leadLep      [id] = EveSelec->getLeadLep      (id);
  }

  //Prepare 1st-3rd leading baseline lepton's four-vector
  Int_t baseLepIndex[3];
  Int_t baseLepFlavor[3];
  TLorentzVector baseLep[3];
  for(Int_t id=0; id<3; id++){
    baseLepIndex [id] = EveSelec->getBaseLepIndex (id);
    baseLepFlavor[id] = EveSelec->getBaseLepFlavor(id);
    baseLep      [id] = EveSelec->getBaseLep      (id);
  }

  //Prepare 1st-3rd lepton's used for the analysis (can treat events with less than three signal lepton region)
  Int_t lepIndex[3];
  Int_t lepFlavor[3];
  TLorentzVector lep[3];
  for(Int_t id=0; id<3; id++){
    lepIndex [id] = EveSelec->is3SigLepSel() ? EveSelec->getLeadLepIndex (id) : EveSelec->getBaseLepIndex (id);
    lepFlavor[id] = EveSelec->is3SigLepSel() ? EveSelec->getLeadLepFlavor(id) : EveSelec->getBaseLepFlavor(id);
    lep      [id] = EveSelec->is3SigLepSel() ? EveSelec->getLeadLep      (id) : EveSelec->getBaseLep      (id);
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
#define FillBaseElHist( index, h, val, w )                  \
  do{                                                   \
    if(baseLepFlavor[index]==0) h[Ch_all]->Fill(val,w); \
    if(baseLepFlavor[index]==0) h[chan]->Fill(val,w);   \
  } while(0)
#define FillBaseMuHist( index, h, val, w )                  \
  do{                                                   \
    if(baseLepFlavor[index]==1) h[Ch_all]->Fill(val,w); \
    if(baseLepFlavor[index]==1) h[chan]->Fill(val,w);   \
  } while(0)
  //Fill lepChan histograms
  h_lepChan    [Ch_all]->Fill(Ch_all,w);
  h_lepChan    [Ch_all]->Fill(chan,w);
  h_baselepChan[Ch_all]->Fill(Ch_all,w);
  h_baselepChan[Ch_all]->Fill(chan,w);

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
  FillElHist( 0, h_el1Eta, vec_signalElectron->at(leadLepIndex[0]).eta(), w );
  FillMuHist( 0, h_mu1Eta, vec_signalMuon    ->at(leadLepIndex[0]).eta(), w );
  FillElHist( 1, h_el2Eta, vec_signalElectron->at(leadLepIndex[1]).eta(), w );
  FillMuHist( 1, h_mu2Eta, vec_signalMuon    ->at(leadLepIndex[1]).eta(), w );
  FillElHist( 2, h_el3Eta, vec_signalElectron->at(leadLepIndex[2]).eta(), w );
  FillMuHist( 2, h_mu3Eta, vec_signalMuon    ->at(leadLepIndex[2]).eta(), w );

  //Fill base lepton Pt
  FillChanHist( h_baselep1Pt, baseLep[0].Pt()/1000., w );
  FillChanHist( h_baselep2Pt, baseLep[1].Pt()/1000., w );
  FillChanHist( h_baselep3Pt, baseLep[2].Pt()/1000., w );
  FillBaseElHist( 0, h_baseel1Pt, vec_baseElectron->at(baseLepIndex[0]).pt()/1000., w );
  FillBaseMuHist( 0, h_basemu1Pt, vec_baseMuon    ->at(baseLepIndex[0]).pt()/1000., w );
  FillBaseElHist( 1, h_baseel2Pt, vec_baseElectron->at(baseLepIndex[1]).pt()/1000., w );
  FillBaseMuHist( 1, h_basemu2Pt, vec_baseMuon    ->at(baseLepIndex[1]).pt()/1000., w );
  FillBaseElHist( 2, h_baseel3Pt, vec_baseElectron->at(baseLepIndex[2]).pt()/1000., w );
  FillBaseMuHist( 2, h_basemu3Pt, vec_baseMuon    ->at(baseLepIndex[2]).pt()/1000., w );

  // Fill base lepton Eta
  FillChanHist( h_baselep1Eta, baseLep[0].Eta(), w );
  FillChanHist( h_baselep2Eta, baseLep[1].Eta(), w );
  FillChanHist( h_baselep3Eta, baseLep[2].Eta(), w );

  //Fill lepton system, sum Pt
  FillChanHist( h_llPt, (lep[0]+lep[1]).Pt()/1000., w );
  FillChanHist( h_sumLepPt, (lep[0].Pt()+lep[1].Pt()+lep[2].Pt())/1000., w );
  FillChanHist( h_sumLepPtMet, (lep[0].Pt()+lep[1].Pt()+lep[2].Pt()+met.Mod())/1000., w );

  // FillChanHist( h_dPhiWZ, , w);
  // FillChanHist( h_nMuComb, , w);

  //Fill isolation values
  for(Int_t id=0; id<3; id++){
    if(lepIndex[id]==-1) continue;
    float ptcone30 = EveSelec->getIsolationValue(lepIndex[id], lepFlavor[id], xAOD::Iso::ptcone30);
    float etcone30 = EveSelec->getIsolationValue(lepIndex[id], lepFlavor[id], xAOD::Iso::etcone30);
    if(lepFlavor[id]==0){
      FillChanHist( h_elPtcone30, ptcone30/1000., w);
      FillChanHist( h_elEtcone30, etcone30/1000., w);
    }else{
      FillChanHist( h_muPtcone30, ptcone30/1000., w);
      FillChanHist( h_muEtcone30, etcone30/1000., w);
    }
  }

  //Fill lepton track variables
  for(Int_t id=0; id<3; id++){
    if(lepIndex[id]==-1) continue;
    const xAOD::TrackParticle* track = EveSelec->getTrack(lepIndex[id], lepFlavor[id]);
    Double_t d0         = 0.;
    Double_t d0sig      = 0.;
    Double_t z0         = 0.;
    Double_t z0sinTheta = 0.;
    if(track){
      //track d0
      d0 = TMath::Abs(track->d0());
      FillChanHist( h_lepD0, d0, w);
      if     (lepIndex[id]==0) FillChanHist( h_lep1D0, d0, w);
      else if(lepIndex[id]==1) FillChanHist( h_lep2D0, d0, w);
      else if(lepIndex[id]==2) FillChanHist( h_lep3D0, d0, w);
      //track z0
      const xAOD::Vertex* pv = EveSelec->getSUSYTools()->GetPrimVtx();
      double primvertex_z = pv ? pv->z() : 0;
      z0 = TMath::Abs(track->z0() + track->vz() - primvertex_z);
      FillChanHist( h_lepZ0, z0, w);
      if     (lepIndex[id]==0) FillChanHist( h_lep1Z0, z0, w);
      else if(lepIndex[id]==1) FillChanHist( h_lep2Z0, z0, w);
      else if(lepIndex[id]==2) FillChanHist( h_lep3Z0, z0, w);
      //track d0/sigma(d0)
      Double_t vard0 = track->definingParametersCovMatrix()(0,0);
      if(vard0 > 0){
        Double_t d0error = 0.;
        d0error=TMath::Sqrt(vard0);
        d0sig  = d0/d0error;
        FillChanHist( h_lepD0Sig, d0sig, w);
        if     (lepIndex[id]==0) FillChanHist( h_lep1D0Sig, d0sig, w);
        else if(lepIndex[id]==1) FillChanHist( h_lep2D0Sig, d0sig, w);
        else if(lepIndex[id]==2) FillChanHist( h_lep3D0Sig, d0sig, w);
      }
      //track z0*sinTheta
      Double_t theta = track->theta();
      z0sinTheta = z0*TMath::Sin(theta);
      FillChanHist( h_lepZ0SinTheta, z0sinTheta, w);
      if     (lepIndex[id]==0) FillChanHist( h_lep1Z0SinTheta, z0sinTheta, w);
      else if(lepIndex[id]==1) FillChanHist( h_lep2Z0SinTheta, z0sinTheta, w);
      else if(lepIndex[id]==2) FillChanHist( h_lep3Z0SinTheta, z0sinTheta, w);
    }
  }

  //Fill lepton truth infomation
  if(m_isMC){
    for(Int_t id=0; id<3; id++){
      if(lepIndex[id]==-1) continue;
      Int_t type   = -1;
      Int_t origin = -1;
      std::vector< xAOD::Electron >* vec_electron = EveSelec->is3SigLepSel() ? vec_signalElectron : vec_baseElectron;
      std::vector< xAOD::Muon >*     vec_muon     = EveSelec->is3SigLepSel() ? vec_signalMuon     : vec_baseMuon;
      if(lepFlavor[id]==0){
        type   = xAOD::EgammaHelpers::getParticleTruthType  (&(vec_electron->at(lepIndex[id])));
        origin = xAOD::EgammaHelpers::getParticleTruthOrigin(&(vec_electron->at(lepIndex[id])));
      }else{
        const xAOD::TrackParticle* trackParticle = (&(vec_muon->at(lepIndex[id])))->primaryTrackParticle();
        if(trackParticle){
          static SG::AuxElement::Accessor<int> acc_truthType  ("truthType"  );
          static SG::AuxElement::Accessor<int> acc_truthOrigin("truthOrigin");
          if(acc_truthType  .isAvailable(*trackParticle)) type   = acc_truthType  (*trackParticle);
          if(acc_truthOrigin.isAvailable(*trackParticle)) origin = acc_truthOrigin(*trackParticle);
        }
      }
      //For origin
      FillChanHist( h_lepOrigin, type, w);
      if     (id==0) FillChanHist( h_lep1Origin, type, w);
      else if(id==1) FillChanHist( h_lep2Origin, type, w);
      else if(id==2) FillChanHist( h_lep3Origin, type, w);
      //Classification of Primary/Comversion/HeavyFlavor/LightFlavor/Unknown
      // Primary
      if(origin==12 || origin==13 || origin==22){
        FillChanHist( h_lepClass, 0., w);
        if     (id==0){ FillChanHist( h_lep1Class, 0., w); FillChanHist( h_PRlep1Pt, lep[0].Pt()/1000., w );}
        else if(id==1){ FillChanHist( h_lep2Class, 0., w); FillChanHist( h_PRlep2Pt, lep[1].Pt()/1000., w );}
        else if(id==2){ FillChanHist( h_lep3Class, 0., w); FillChanHist( h_PRlep3Pt, lep[2].Pt()/1000., w );}
      }
      // Conversion
      else if(origin==5){
        FillChanHist( h_lepClass, 1., w);
        if     (id==0){ FillChanHist( h_lep1Class, 1., w); FillChanHist( h_COlep1Pt, lep[0].Pt()/1000., w );}
        else if(id==1){ FillChanHist( h_lep2Class, 1., w); FillChanHist( h_COlep2Pt, lep[1].Pt()/1000., w );}
        else if(id==2){ FillChanHist( h_lep3Class, 1., w); FillChanHist( h_COlep3Pt, lep[2].Pt()/1000., w );}
      }
      // Heavy Flavor
      else if(origin==25 || origin==26 || origin==27 ||
              origin==29 || origin==32 || origin==33 ){
        FillChanHist( h_lepClass, 2., w);
        if     (id==0){ FillChanHist( h_lep1Class, 2., w); FillChanHist( h_HFlep1Pt, lep[0].Pt()/1000., w );}
        else if(id==1){ FillChanHist( h_lep2Class, 2., w); FillChanHist( h_HFlep2Pt, lep[1].Pt()/1000., w );}
        else if(id==2){ FillChanHist( h_lep3Class, 2., w); FillChanHist( h_HFlep3Pt, lep[2].Pt()/1000., w );}
      }
      // LightFlavor
      else if(origin==23 || origin==24 || origin==30 ||
              origin==31 || origin==34 || origin==35 || 
              origin==41 || origin==45 ){
        FillChanHist( h_lepClass, 3., w);
        if     (id==0){ FillChanHist( h_lep1Class, 3., w); FillChanHist( h_LFlep1Pt, lep[0].Pt()/1000., w );}
        else if(id==1){ FillChanHist( h_lep2Class, 3., w); FillChanHist( h_LFlep2Pt, lep[1].Pt()/1000., w );}
        else if(id==2){ FillChanHist( h_lep3Class, 3., w); FillChanHist( h_LFlep3Pt, lep[2].Pt()/1000., w );}
        // Unknown
      }else{
        FillChanHist( h_lepClass, 4., w);
        if     (id==0){ FillChanHist( h_lep1Class, 4., w); FillChanHist( h_UKlep1Pt, lep[0].Pt()/1000., w );}
        else if(id==1){ FillChanHist( h_lep2Class, 4., w); FillChanHist( h_UKlep2Pt, lep[1].Pt()/1000., w );}
        else if(id==2){ FillChanHist( h_lep3Class, 4., w); FillChanHist( h_UKlep3Pt, lep[2].Pt()/1000., w );}
      }
    }
  }
  //Fill base lepton truth information
  if(m_isMC){
    for(Int_t id=0; id<3; id++){
      if(baseLepIndex[id]==-1) continue;
      Int_t type   = -1;
      Int_t origin = -1;
      if(baseLepFlavor[id]==0){
        type   = xAOD::EgammaHelpers::getParticleTruthType  (&(vec_baseElectron->at(baseLepIndex[id])));
        origin = xAOD::EgammaHelpers::getParticleTruthOrigin(&(vec_baseElectron->at(baseLepIndex[id])));
      }else{
        const xAOD::TrackParticle* trackParticle = (&(vec_baseMuon->at(baseLepIndex[id])))->primaryTrackParticle();
        if(trackParticle){
          static SG::AuxElement::Accessor<int> acc_truthType  ("truthType"  );
          static SG::AuxElement::Accessor<int> acc_truthOrigin("truthOrigin");
          if(acc_truthType  .isAvailable(*trackParticle)) type   = acc_truthType  (*trackParticle);
          if(acc_truthOrigin.isAvailable(*trackParticle)) origin = acc_truthOrigin(*trackParticle);
        }
      }
      //For origin
      FillChanHist( h_baselepOrigin, type, w);
      if     (id==0) FillChanHist( h_baselep1Origin, type, w);
      else if(id==1) FillChanHist( h_baselep2Origin, type, w);
      else if(id==2) FillChanHist( h_baselep3Origin, type, w);
      //Classification of Primary/Comversion/HeavyFlavor/LightFlavor/Unknown
      if(origin==12 || origin==13 || origin==22){
        FillChanHist( h_baselepClass, 0., w);
        if     (id==0) FillChanHist( h_baselep1Class, 0., w);
        else if(id==1) FillChanHist( h_baselep2Class, 0., w);
        else if(id==2) FillChanHist( h_baselep3Class, 0., w);
      }
      else if(origin==5){
        FillChanHist( h_baselepClass, 1., w);
        if     (id==0) FillChanHist( h_baselep1Class, 1., w);
        else if(id==1) FillChanHist( h_baselep2Class, 1., w);
        else if(id==2) FillChanHist( h_baselep3Class, 1., w);
      }
      else if(origin==25 || origin==26 || origin==27 ||
              origin==29 || origin==32 || origin==33 ){
        FillChanHist( h_baselepClass, 2., w);
        if     (id==0) FillChanHist( h_baselep1Class, 2., w);
        else if(id==1) FillChanHist( h_baselep2Class, 2., w);
        else if(id==2) FillChanHist( h_baselep3Class, 2., w);
      }
      else if(origin==23 || origin==24 || origin==30 ||
              origin==31 || origin==34 || origin==35 || 
              origin==41 || origin==45 ){
        FillChanHist( h_baselepClass, 3., w);
        if     (id==0) FillChanHist( h_baselep1Class, 3., w);
        else if(id==1) FillChanHist( h_baselep2Class, 3., w);
        else if(id==2) FillChanHist( h_baselep3Class, 3., w);
      }else{
        FillChanHist( h_baselepClass, 4., w);
        if     (id==0) FillChanHist( h_baselep1Class, 4., w);
        else if(id==1) FillChanHist( h_baselep2Class, 4., w);
        else if(id==2) FillChanHist( h_baselep3Class, 4., w);
      }
    }
  }

  FillChanHist( h_hasSS, (EveSelec->hasSS()?1.:0.), w);
  // FillChanHist( h_nTau, , w);
  // FillChanHist( h_tauPt, , w);
  // FillChanHist( h_tau1Pt, , w);
  // FillChanHist( h_tau2Pt, , w);
  // FillChanHist( h_tau1Eta, , w);
  // FillChanHist( h_tau2Eta, , w);
  // FillChanHist( h_tauProng, , w);
  // FillChanHist( h_dPhiTauTau, , w);
  // FillChanHist( h_tauClass, , w);
  // FillChanHist( h_tau1Class, , w);
  // FillChanHist( h_tau2Class, , w);
  // FillChanHist( h_minDRLepLep, , w);
  // FillChanHist( h_dPhiLep1Met, , w);
  // FillChanHist( h_dPhiLep2Met, , w);
  // FillChanHist( h_dPhiLep3Met, , w);
  // FillChanHist( h_dPhiLLMet, , w);
  // FillChanHist( h_dPhiJet1Met, , w);
  // FillChanHist( h_dPhiJet2Met, , w);
  // FillChanHist( h_dPhiJJMet, , w);
  // FillChanHist( h_minDPhiLepLep, , w);
  // FillChanHist( h_minDPhiLepMet, , w);
  // FillChanHist( h_minDPhiJetJet, , w);
  // FillChanHist( h_minDPhiJetMet, , w);
  // FillChanHist( h_minDPhiTauMet, , w);
  // FillChanHist( h_minDRLepJet, , w);
  // FillChanHist( h_maxDPhiLepLep, , w);
  // FillChanHist( h_maxDPhiLepMet, , w);
  // FillChanHist( h_maxDPhiJetJet, , w);
  // FillChanHist( h_maxDPhiJetMet, , w);
  // FillChanHist( h_maxDRLepJet, , w);
  // FillChanHist( h_dEtaLL, , w);
  // FillChanHist( h_dEtaJetJet, , w);
  // FillChanHist( h_maxDEtaJetJet, , w);
  // FillChanHist( h_minDEtaJetJet, , w);
  FillChanHist( h_met      , met.Mod()/1000., w);
  FillChanHist( h_meff     , EveSelec->getMeff(40.,true )/1000., w);
  FillChanHist( h_meffNoMet, EveSelec->getMeff(40.,false)/1000., w);
  // FillChanHist( h_metEle, , w);
  // FillChanHist( h_metMuo, , w);
  // FillChanHist( h_metJet, , w);
  // FillChanHist( h_metCell, , w);
  FillChanHist( h_metRel, EveSelec->getMetRel()/1000., w);
  FillChanHist( h_nJet , vec_signalJet->size(), w);
  FillChanHist( h_nBJet, EveSelec->numBJets(), w);
  for(uint ij=0; ij<vec_signalJet->size(); ++ij){
    FillChanHist( h_jetPt , vec_signalJet->at(ij).p4().Pt()/1000., w);
    FillChanHist( h_jetEta, vec_signalJet->at(ij).p4().Eta()     , w);
    FillChanHist( h_jetPhi, vec_signalJet->at(ij).p4().Phi()     , w);
    if((vec_signalJet->at(ij)).auxdata<char>("bjet")){
      FillChanHist( h_bJetPt , vec_signalJet->at(ij).p4().Pt ()/1000., w);
      FillChanHist( h_bJetEta, vec_signalJet->at(ij).p4().Eta()      , w);
    }
  }
  // FillChanHist( h_jet1Pt, , w);
  // FillChanHist( h_jet2Pt, , w);
  // FillChanHist( h_jet3Pt, , w);
  // FillChanHist( h_bJet1Pt, , w);
  // FillChanHist( h_bJet2Pt, , w);
  // FillChanHist( h_bJet3Pt, , w);
  // FillChanHist( h_bJet1Eta, , w);
  // FillChanHist( h_bJet2Eta, , w);
  // FillChanHist( h_bJet3Eta, , w);
  // FillChanHist( h_jetMV1, , w);
  // FillChanHist( h_jetJVF, , w);
  // FillChanHist( h_bJetJVF, , w);
  // FillChanHist( h_dijetM, , w);
  // FillChanHist( h_productEta1Eta2, , w);
  // FillChanHist( h_mll, , w);
  Int_t sfosIndex[2]={-1,-1};
  Int_t sfosFlav=-1;
  Double_t msfos = EveSelec->findBestMSFOS(sfosIndex[0],sfosIndex[1],sfosFlav,MZ);
  FillChanHist( h_msfos, msfos/1000., w);
  Int_t minSfosIndex[2]={-1,-1};
  Int_t minSfosFlav=-1;
  Double_t minMsfos = EveSelec->findBestMSFOS(minSfosIndex[0],minSfosIndex[1],minSfosFlav,-1.);
  FillChanHist( h_minMsfos, minMsfos/1000., w);
  // FillChanHist( h_msfss, , w);
  // FillChanHist( h_mlll, , w);
  // FillChanHist( h_mt, , w);
  // FillChanHist( h_mtL1, , w);
  // FillChanHist( h_mtL2, , w);
  FillChanHist( h_mt2, EveSelec->getMaxMT2()/1000., w);
  // FillChanHist( h_mjj, , w);
  // FillChanHist( h_mlljj, , w);
  // FillChanHist( h_mlt, , w);
  // FillChanHist( h_mtt, , w);
  // FillChanHist( h_mbb, , w);
  FillChanHist( h_mljj, EveSelec->getMljj()/1000., w);
  // FillChanHist( h_mljjFine, , w);
  // FillChanHist( h_mtll, , w);
  // FillChanHist( h_mtll_mt, , w);
  // FillChanHist( h_nVtx, , w);
  // FillChanHist( h_mu, , w);

#undef FillChanHist
#undef FillChanHist2D
#undef FillElHist
#undef FillMuHist

  MyDebug("FillHistograms()","Filling finished");
  return true;
}
/*--------------------------------------------------------------------------------*/
bool Plotter::FillNEvent(double weight)
{
  MyDebug("FillNEvent()","Plotter::FillNEvent()");
  h_nEve->Fill(0., weight);
  return true;
}
