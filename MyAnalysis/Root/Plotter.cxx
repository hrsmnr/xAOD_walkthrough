#define APP_NAME "Plotter"
#define MyVerbose(a,b) if(m_dbg<=MSG::VERBOSE) std::cout<<"Verbose in <Plotter::"<<(a)<<">: "<< m_sel.c_str() << "," << m_sys << " : "<<(b)<<std::endl;
#define MyDebug(a,b) if(m_dbg<=MSG::DEBUG) std::cout<<"Debug in <Plotter::"<<(a)<<">: "<< m_sel.c_str() << "," << m_sys << " : "<<(b)<<std::endl;
#define MyInfo(a,b) if(m_dbg<=MSG::INFO) std::cout<<"Info in <Plotter::"<<(a)<<">: "<< m_sel.c_str() << "," << m_sys << " : "<<(b)<<std::endl;
#define MyError(a,b) if(m_dbg<=MSG::ERROR) std::cout<<"Error in <Plotter::"<<(a)<<">: "<< m_sel.c_str() << "," << m_sys << " : "<<(b)<<std::endl;
#define MyAlways(a,b) if(m_dbg<=MSG::ALWAYS) std::cout<<"In <Plotter::"<<(a)<<">: "<< m_sel.c_str() << "," << m_sys << " : "<<(b)<<std::endl;

#include<iostream>
#include"MyAnalysis/Plotter.h"
#include"../MCTruthClassifier/MCTruthClassifier/MCTruthClassifierDefs.h"//not prepared for rootcore

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
    h_msfss[iCh]->Write();
    h_mlll[iCh]->Write();
    h_mt[iCh]->Write();
    h_mtFine[iCh]->Write();
    h_mtCoarse[iCh]->Write();
    h_mtLow[iCh]->Write();
    h_mtL1[iCh]->Write();
    h_mtL2[iCh]->Write();
    h_mt2Max[iCh]->Write();
    h_mt2MaxFine[iCh]->Write();
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
    NEWHIST( lepD0Sig, "Lepton |d0/#sigma_{d0}|;Events", 20, 0, 0.5 );
    NEWHIST( lep1D0Sig, "Leading lepton |d0/#sigma_{d0}|;Events", 20, 0, 0.5 );
    NEWHIST( lep2D0Sig, "Second lepton |d0/#sigma_{d0}|;Events", 20, 0, 0.5 );
    NEWHIST( lep3D0Sig, "Third lepton |d0/#sigma_{d0}|;Events", 20, 0, 0.5 );
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
    NEWHIST( msfss, "M_{SFSS} [GeV];SFSS lepton pairs", 50, 0, 500 );
    NEWVARHIST( mlll, "M_{lll} [GeV];Events", nMassBins, massBins );
    //NEWHIST( mlll, "M_{lll} [GeV];Events", 50, 0, 1000 );
    NEWVARHIST( mt, "M_{T} [GeV];Events", nMassBins, massBins );
    NEWHIST( mtFine, "M_{T} [GEV];Events", 50, 0, 500 );
    NEWVARHIST( mtCoarse, "M_{T} [GeV];Events", nMtCoarseBins, mtCoarseBins );
    NEWVARHIST( mtLow, "M_{T} [GeV];Events", nMtLowBins, mtLowBins );
    NEWVARHIST( mtL1, "M_{T}(lep1, MET) [GeV];Events", nMassBins, massBins );
    NEWVARHIST( mtL2, "M_{T}(lep2, MET) [GeV];Events", nMassBins, massBins );
    NEWVARHIST( mt2Max, "maximum M_{T2} [GeV];Events", nMassBins, massBins );
    NEWHIST( mt2MaxFine, "maximum M_{T2} [GeV];Events", 50, 0, 500 );
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
  FillElHist( 0, h_el1Eta, vec_signalElectron->at(leadLepIndex[0]).eta(), w );
  FillMuHist( 0, h_mu1Eta, vec_signalMuon    ->at(leadLepIndex[0]).eta(), w );
  FillElHist( 1, h_el2Eta, vec_signalElectron->at(leadLepIndex[1]).eta(), w );
  FillMuHist( 1, h_mu2Eta, vec_signalMuon    ->at(leadLepIndex[1]).eta(), w );
  FillElHist( 2, h_el3Eta, vec_signalElectron->at(leadLepIndex[2]).eta(), w );
  FillMuHist( 2, h_mu3Eta, vec_signalMuon    ->at(leadLepIndex[2]).eta(), w );

  //Fill lepton system, sum Pt
  FillChanHist( h_llPt, (leadLep[0]+leadLep[1]).Pt()/1000., w );
  FillChanHist( h_sumLepPt, (leadLep[0].Pt()+leadLep[1].Pt()+leadLep[2].Pt())/1000., w );
  FillChanHist( h_sumLepPtMet, (leadLep[0].Pt()+leadLep[1].Pt()+leadLep[2].Pt()+met.Mod())/1000., w );

  // h_dPhiWZ[iCh]->Write();
  // h_nMuComb[iCh]->Write();
  // h_elPtcone30[iCh]->Write();
  // h_elEtcone30[iCh]->Write();
  // h_muPtcone30[iCh]->Write();
  // h_muEtcone30[iCh]->Write();
  // h_lepD0[iCh]->Write();
  // h_lep1D0[iCh]->Write();
  // h_lep2D0[iCh]->Write();
  // h_lep3D0[iCh]->Write();
  // h_lepZ0[iCh]->Write();
  // h_lep1Z0[iCh]->Write();
  // h_lep2Z0[iCh]->Write();
  // h_lep3Z0[iCh]->Write();
  // h_lepD0Sig[iCh]->Write();
  // h_lep1D0Sig[iCh]->Write();
  // h_lep2D0Sig[iCh]->Write();
  // h_lep3D0Sig[iCh]->Write();
  // h_lepZ0SinTheta[iCh]->Write();
  // h_lep1Z0SinTheta[iCh]->Write();
  // h_lep2Z0SinTheta[iCh]->Write();
  // h_lep3Z0SinTheta[iCh]->Write();
  // h_lepOrigin[iCh]->Write();
  // h_lep1Origin[iCh]->Write();
  // h_lep2Origin[iCh]->Write();
  // h_lep3Origin[iCh]->Write();
  // h_lepClass[iCh]->Write();
  // h_lep1Class[iCh]->Write();
  // h_lep2Class[iCh]->Write();
  // h_lep3Class[iCh]->Write();
  // h_hasSS[iCh]->Write();
  // h_nTau[iCh]->Write();
  // h_tauPt[iCh]->Write();
  // h_tau1Pt[iCh]->Write();
  // h_tau2Pt[iCh]->Write();
  // h_tau1Eta[iCh]->Write();
  // h_tau2Eta[iCh]->Write();
  // h_tauProng[iCh]->Write();
  // h_dPhiTauTau[iCh]->Write();
  // h_tauClass[iCh]->Write();
  // h_tau1Class[iCh]->Write();
  // h_tau2Class[iCh]->Write();
  // h_minDRLepLep[iCh]->Write();
  // h_dPhiLep1Met[iCh]->Write();
  // h_dPhiLep2Met[iCh]->Write();
  // h_dPhiLep3Met[iCh]->Write();
  // h_dPhiLLMet[iCh]->Write();
  // h_dPhiJet1Met[iCh]->Write();
  // h_dPhiJet2Met[iCh]->Write();
  // h_dPhiJJMet[iCh]->Write();
  // h_minDPhiLepLep[iCh]->Write();
  // h_minDPhiLepMet[iCh]->Write();
  // h_minDPhiJetJet[iCh]->Write();
  // h_minDPhiJetMet[iCh]->Write();
  // h_minDPhiTauMet[iCh]->Write();
  // h_minDRLepJet[iCh]->Write();
  // h_maxDPhiLepLep[iCh]->Write();
  // h_maxDPhiLepMet[iCh]->Write();
  // h_maxDPhiJetJet[iCh]->Write();
  // h_maxDPhiJetMet[iCh]->Write();
  // h_maxDRLepJet[iCh]->Write();
  // h_dEtaLL[iCh]->Write();
  // h_dEtaJetJet[iCh]->Write();
  // h_maxDEtaJetJet[iCh]->Write();
  // h_minDEtaJetJet[iCh]->Write();
  // h_met[iCh]->Write();
  // h_meff[iCh]->Write();
  // h_meffNoMet[iCh]->Write();
  // h_metEle[iCh]->Write();
  // h_metMuo[iCh]->Write();
  // h_metJet[iCh]->Write();
  // h_metCell[iCh]->Write();
  // h_metRel[iCh]->Write();
  // h_nJet[iCh]->Write();
  // h_nBJet[iCh]->Write();
  // h_jetPt[iCh]->Write();
  // h_jet1Pt[iCh]->Write();
  // h_jet2Pt[iCh]->Write();
  // h_jet3Pt[iCh]->Write();
  // h_bJetPt[iCh]->Write();
  // h_bJet1Pt[iCh]->Write();
  // h_bJet2Pt[iCh]->Write();
  // h_bJet3Pt[iCh]->Write();
  // h_jetEta[iCh]->Write();
  // h_bJetEta[iCh]->Write();
  // h_bJet1Eta[iCh]->Write();
  // h_bJet2Eta[iCh]->Write();
  // h_bJet3Eta[iCh]->Write();
  // h_jetPhi[iCh]->Write();
  // h_jetMV1[iCh]->Write();
  // h_jetJVF[iCh]->Write();
  // h_bJetJVF[iCh]->Write();
  // h_dijetM[iCh]->Write();
  // h_productEta1Eta2[iCh]->Write();
  // h_mll[iCh]->Write();
  // h_msfos[iCh]->Write();
  // h_msfss[iCh]->Write();
  // h_mlll[iCh]->Write();
  // h_mt[iCh]->Write();
  // h_mtFine[iCh]->Write();
  // h_mtCoarse[iCh]->Write();
  // h_mtLow[iCh]->Write();
  // h_mtL1[iCh]->Write();
  // h_mtL2[iCh]->Write();
  // h_mt2Max[iCh]->Write();
  // h_mt2MaxFine[iCh]->Write();
  // h_mjj[iCh]->Write();
  // h_mlljj[iCh]->Write();
  // h_mlt[iCh]->Write();
  // h_mtt[iCh]->Write();
  // h_mbb[iCh]->Write();
  // h_mljj[iCh]->Write();
  // h_mljjFine[iCh]->Write();
  // h_mtll[iCh]->Write();
  // h_mtll_mt[iCh]->Write();
  // h_nVtx[iCh]->Write();
  // h_mu[iCh]->Write();

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
