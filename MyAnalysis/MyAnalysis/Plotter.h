#ifndef SusyAna_Plotter_h
#define SusyAna_Plotter_h

// Plotter - filling histogram for each selection region and systematics

#include<string>
#include<TObject.h>
#include"AsgTools/MsgLevel.h"

#include"MyAnalysis/EventSelector.h"

class TFile;
class TH1F;
class TH2F;

#define nChan 5

class Plotter : public TObject
{
 public:
  Plotter(std::string sel="none", std::string sys="none", MSG::Level dbg=MSG::ERROR);
  virtual ~Plotter(){};

  virtual void initialize(const char* path, int dsid, double XS=0.);
  virtual void finalize();

  bool FillHistograms(EventSelector *EveSelec, double weight);
  bool FillNEvent(double weight);

  ClassDef(Plotter, 1);

 protected:
  MSG::Level m_dbg; // debug level
  std::string m_sel;
  std::string m_sys;
  std::string m_filename;
  double m_crossSection;
  Bool_t m_isMC;
  TFile *m_rootfile;

  bool BookHistograms();

  // Declaration of histograms
  TH1F *h_xsec; //cross section for the processed sample (for data, 0. is filled.)
  TH1F *h_nEve; //#processed events to make histograms (not #events for whole dataset)
  TH1F *h_lepChan[nChan]; //count entries for each final state
  //Lepton kinematics
  TH1F *h_lep1Pt [nChan]; //1st lepton Pt
  TH1F *h_lep2Pt [nChan]; //2nd lepton Pt
  TH1F *h_lep3Pt [nChan]; //3rd lepton Pt
  TH1F *h_el1Pt  [nChan]; //1st electron Pt
  TH1F *h_el2Pt  [nChan]; //2nd electron Pt
  TH1F *h_el3Pt  [nChan]; //3rd electron Pt
  TH1F *h_mu1Pt  [nChan]; //1st muon Pt
  TH1F *h_mu2Pt  [nChan]; //2nd muon Pt
  TH1F *h_mu3Pt  [nChan]; //3rd muon Pt
  TH1F *h_lep1Eta[nChan]; //1st lepton Eta
  TH1F *h_lep2Eta[nChan]; //2nd lepton Eta
  TH1F *h_lep3Eta[nChan]; //3rd lepton Eta
  TH1F *h_el1Eta [nChan]; //1st electron Eta
  TH1F *h_el2Eta [nChan]; //2nd electron Eta
  TH1F *h_el3Eta [nChan]; //3rd electron Eta
  TH1F *h_mu1Eta [nChan]; //1st muon Eta
  TH1F *h_mu2Eta [nChan]; //2nd muon Eta
  TH1F *h_mu3Eta [nChan]; //3rd muon Eta

  TH1F *h_llPt[nChan]; //Dilepton system Pt

  TH1F *h_sumLepPt   [nChan]; // Scalar sum of lepton pt
  TH1F *h_sumLepPtMet[nChan]; // Scalar sum of lepton pt and MET
  TH1F *h_dPhiWZ     [nChan]; // dPhi between W and Z leptons
  TH1F *h_nMuComb    [nChan]; // number of combined muons

  // Isolation
  TH1F *h_elPtcone30[nChan]; // electron ptcone30
  TH1F *h_elEtcone30[nChan]; // electron etcone30
  TH1F *h_muPtcone30[nChan]; // muon ptcone30
  TH1F *h_muEtcone30[nChan]; // muon etcone30

  // impact parameter histograms
  TH1F *h_lepD0 [nChan]; // all lepton d0
  TH1F *h_lep1D0[nChan]; // lepton d0
  TH1F *h_lep2D0[nChan]; // lepton d0
  TH1F *h_lep3D0[nChan]; // lepton d0
  TH1F *h_lepZ0 [nChan]; // all lepton z0
  TH1F *h_lep1Z0[nChan]; // lepton z0
  TH1F *h_lep2Z0[nChan]; // lepton z0
  TH1F *h_lep3Z0[nChan]; // lepton z0
  TH1F *h_lepD0Sig [nChan]; // all lepton d0 significance
  TH1F *h_lep1D0Sig[nChan]; // lepton d0 significance
  TH1F *h_lep2D0Sig[nChan]; // lepton d0 significance
  TH1F *h_lep3D0Sig[nChan]; // lepton d0 significance
  TH1F *h_lepZ0SinTheta [nChan]; // all lepton z0 sin theta
  TH1F *h_lep1Z0SinTheta[nChan]; // lepton z0 sin theta
  TH1F *h_lep2Z0SinTheta[nChan]; // lepton z0 sin theta
  TH1F *h_lep3Z0SinTheta[nChan]; // lepton z0 sin theta

  // Lepton truth classification
  TH1F *h_lepOrigin [nChan];// Lepton origin from McTruthClassifier
  TH1F *h_lep1Origin[nChan];// Lepton origin from McTruthClassifier
  TH1F *h_lep2Origin[nChan];// Lepton origin from McTruthClassifier
  TH1F *h_lep3Origin[nChan];// Lepton origin from McTruthClassifier
  TH1F *h_lepClass [nChan]; // truth classifcation from LeptonTruthTools
  TH1F *h_lep1Class[nChan]; // truth classifcation from LeptonTruthTools
  TH1F *h_lep2Class[nChan]; // truth classifcation from LeptonTruthTools
  TH1F *h_lep3Class[nChan]; // truth classifcation from LeptonTruthTools

  TH1F *h_hasSS[nChan];     // event has SS leptons

  // Tau kinematics
  TH1F *h_nTau      [nChan]; // number of signal taus
  TH1F *h_tauPt     [nChan]; // all tau pt
  TH1F *h_tau1Pt    [nChan]; // leading tau pt
  TH1F *h_tau2Pt    [nChan]; // second tau pt
  TH1F *h_tau1Eta   [nChan]; // leading tau eta
  TH1F *h_tau2Eta   [nChan]; // second tau eta
  TH1F *h_tauProng  [nChan]; // number of tracks
  TH1F *h_dPhiTauTau[nChan]; // dPhi(tau1,tau2)
  TH1F *h_tauClass  [nChan]; // truth classification from LeptonTruthTools
  TH1F *h_tau1Class [nChan]; // truth classification from LeptonTruthTools
  TH1F *h_tau2Class [nChan]; // truth classification from LeptonTruthTools

  // Angular histos
  TH1F *h_minDRLepLep  [nChan]; // min dR(lep, lep)
  TH1F *h_dPhiLep1Met  [nChan]; // dPhi(lep1, met)
  TH1F *h_dPhiLep2Met  [nChan]; // dPhi(lep2, met)
  TH1F *h_dPhiLep3Met  [nChan]; // dPhi(lep3, met)
  TH1F *h_dPhiLLMet    [nChan]; // dPhi(lep1+lep2, met)
  TH1F *h_dPhiJet1Met  [nChan]; // dPhi(jet1, met)
  TH1F *h_dPhiJet2Met  [nChan]; // dPhi(jet2, met)
  TH1F *h_dPhiJJMet    [nChan]; // dPhi(jet1+jet2, met)
  TH1F *h_minDPhiLepLep[nChan]; // min dPhi(lep, lep) 
  TH1F *h_minDPhiLepMet[nChan]; // min dPhi(lep, met) 
  TH1F *h_minDPhiJetJet[nChan]; // min dPhi(jet, jet)
  TH1F *h_minDPhiJetMet[nChan]; // min dPhi(jet, met)
  TH1F *h_minDPhiTauMet[nChan]; // min dPhi(tau, met)
  TH1F *h_minDRLepJet  [nChan]; // min dR(lep, jet)
  TH1F *h_maxDPhiLepLep[nChan]; // max dPhi(lep, lep) 
  TH1F *h_maxDPhiLepMet[nChan]; // max dPhi(lep, met) 
  TH1F *h_maxDPhiJetJet[nChan]; // max dPhi(jet, jet)
  TH1F *h_maxDPhiJetMet[nChan]; // max dPhi(jet, met)
  TH1F *h_maxDRLepJet  [nChan]; // max dR(lep, jet)
  TH1F *h_dEtaLL       [nChan]; // dEta(lep, lep)
  TH1F *h_dEtaJetJet   [nChan]; // dEta(jet, jet)
  TH1F *h_maxDEtaJetJet[nChan]; // max dEta(jet, jet)
  TH1F *h_minDEtaJetJet[nChan]; // max dEta(jet, jet)

  // Missing ET hists
  TH1F *h_met      [nChan]; // Missing Et
  TH1F *h_meff     [nChan]; // M effective
  TH1F *h_meffNoMet[nChan]; // M effective without met
  TH1F *h_metEle   [nChan]; // Ref electron term
  TH1F *h_metMuo   [nChan]; // Muon total term
  TH1F *h_metJet   [nChan]; // Ref jet term
  TH1F *h_metCell  [nChan]; // Cell out term
  TH1F *h_metRel   [nChan]; // MET rel

  // Jet hists
  TH1F *h_nJet    [nChan]; // Jet multiplicity
  TH1F *h_nBJet   [nChan]; // b-jet multiplicity
  TH1F *h_jetPt   [nChan]; // all jet pt
  TH1F *h_jet1Pt  [nChan]; // leading jet pt
  TH1F *h_jet2Pt  [nChan]; // second jet pt
  TH1F *h_jet3Pt  [nChan]; // third jet pt
  TH1F *h_bJetPt  [nChan]; // all b jet pt
  TH1F *h_bJet1Pt [nChan]; // b jet pt
  TH1F *h_bJet2Pt [nChan]; // b jet pt
  TH1F *h_bJet3Pt [nChan]; // b jet pt
  TH1F *h_jetEta  [nChan]; // jet eta
  TH1F *h_bJetEta [nChan]; // all b jet eta
  TH1F *h_bJet1Eta[nChan]; // b jet eta
  TH1F *h_bJet2Eta[nChan]; // b jet eta
  TH1F *h_bJet3Eta[nChan]; // b jet eta
  TH1F *h_jetPhi  [nChan]; // jet phi
  TH1F *h_jetMV1  [nChan]; // jet mv1 weight
  TH1F *h_jetJVF  [nChan]; // jet JVF
  TH1F *h_bJetJVF [nChan]; // b jet JVF
  TH1F *h_dijetM  [nChan]; // Mass(jet1+jet2)
  TH1F *h_productEta1Eta2[nChan]; // Eta1*Eta2

  // Mass hists
  TH1F *h_mll       [nChan]; // leading dilepton mass, no charge/flav requirement
  TH1F *h_msfos     [nChan]; // sfos inv mass closest to Z
  TH1F *h_minMsfos  [nChan]; // minimum sfos inv mass
  TH1F *h_msfss     [nChan]; // sfss inv mass, all pairs
  TH1F *h_mlll      [nChan]; // trilepton mass
  TH1F *h_mt        [nChan]; // transverse mass from best non-Z lepton and MET
  TH1F *h_mtL1      [nChan]; // transverse using leading lepton
  TH1F *h_mtL2      [nChan]; // transverse using sub-leading lepton
  TH1F *h_mt2       [nChan]; // maximum MT2 of all object combinations
  TH1F *h_mjj       [nChan]; // dijet mass closest to the W
  TH1F *h_mlljj     [nChan]; // inv mass of sfos leptons and 2 jets closest to ZZ
  TH1F *h_mlt       [nChan]; // inv mass of OS lepton+tau
  TH1F *h_mtt       [nChan]; // inv mass of OS tau+tau
  TH1F *h_mbb       [nChan]; // inv mass of leading b-jets

  TH1F *h_mljj    [nChan]; // inv mass of ljj
  TH1F *h_mljjFine[nChan]; // inv mass of ljj, fine binning
  TH1F *h_mtll    [nChan]; // transverse mass of ll and MET
  TH2F *h_mtll_mt [nChan]; // mtll vs. max mt

  // Pileup  hists
  TH1F *h_nVtx[nChan]; // number of vtx with at least 5 tracks
  TH1F *h_mu  [nChan]; // average interactions per bunch crossing

};
#endif
