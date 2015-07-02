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
  Plotter(const std::string& sel="none", const std::string& sys="none", const MSG::Level& dbg=MSG::ERROR);
  virtual ~Plotter(){};

  virtual void initialize(const char* path, int dsid, double XS=0., TFile* file=NULL);
  virtual void finalize();

  bool FillHistoPreSelec(EventSelector *EveSelec, double weight);
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
  TH2F *h_nSigBaseLep; // #signal vs #baseline leptons
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
  
  // Fake signal lepton
  TH1F *h_PRlep1Pt [nChan]; // 1st PR lepton Pt
  TH1F *h_PRlep2Pt [nChan]; // 2nd PR lepton Pt
  TH1F *h_PRlep3Pt [nChan]; // 3nd PR lepton Pt
  TH1F *h_COlep1Pt [nChan]; // 1st CO lepton Pt
  TH1F *h_COlep2Pt [nChan]; // 2nd CO lepton Pt
  TH1F *h_COlep3Pt [nChan]; // 3nd CO lepton Pt
  TH1F *h_HFlep1Pt [nChan]; // 1st HF lepton Pt
  TH1F *h_HFlep2Pt [nChan]; // 2nd HF lepton Pt
  TH1F *h_HFlep3Pt [nChan]; // 3nd HF lepton Pt
  TH1F *h_LFlep1Pt [nChan]; // 1st LF lepton Pt
  TH1F *h_LFlep2Pt [nChan]; // 2nd LF lepton Pt
  TH1F *h_LFlep3Pt [nChan]; // 3nd LF lepton Pt
  TH1F *h_UKlep1Pt [nChan]; // 1st UK lepton Pt
  TH1F *h_UKlep2Pt [nChan]; // 2nd UK lepton Pt
  TH1F *h_UKlep3Pt [nChan]; // 3nd UK lepton Pt
  TH1F *h_PRlep1Eta[nChan]; // 1st PR lepton Eta
  TH1F *h_PRlep2Eta[nChan]; // 2nd PR lepton Eta
  TH1F *h_PRlep3Eta[nChan]; // 3nd PR lepton Eta
  TH1F *h_COlep1Eta[nChan]; // 1st CO lepton Eta
  TH1F *h_COlep2Eta[nChan]; // 2nd CO lepton Eta
  TH1F *h_COlep3Eta[nChan]; // 3nd CO lepton Eta
  TH1F *h_HFlep1Eta[nChan]; // 1st HF lepton Eta
  TH1F *h_HFlep2Eta[nChan]; // 2nd HF lepton Eta
  TH1F *h_HFlep3Eta[nChan]; // 3nd HF lepton Eta
  TH1F *h_LFlep1Eta[nChan]; // 1st LF lepton Eta
  TH1F *h_LFlep2Eta[nChan]; // 2nd LF lepton Eta
  TH1F *h_LFlep3Eta[nChan]; // 3nd LF lepton Eta
  TH1F *h_UKlep1Eta[nChan]; // 1st UK lepton Eta
  TH1F *h_UKlep2Eta[nChan]; // 2nd UK lepton Eta
  TH1F *h_UKlep3Eta[nChan]; // 3nd UK lepton Eta

  // Fake signal lepton for matrix method
  TH1F *h_PRlep2and3Pt [nChan]; // 2nd and 3rd PR lepton Pt
  TH1F *h_COlep2and3Pt [nChan]; // 2nd and 3rd CO lepton Pt
  TH1F *h_HFlep2and3Pt [nChan]; // 2nd and 3rd HF lepton Pt
  TH1F *h_LFlep2and3Pt [nChan]; // 2nd and 3rd LF lepton Pt
  TH1F *h_UKlep2and3Pt [nChan]; // 2nd and 3rd UK lepton Pt
  TH1F *h_PRlep2and3Eta[nChan]; // 2nd and 3rd PR lepton Eta
  TH1F *h_COlep2and3Eta[nChan]; // 2nd and 3rd CO lepton Eta
  TH1F *h_HFlep2and3Eta[nChan]; // 2nd and 3rd HF lepton Eta
  TH1F *h_LFlep2and3Eta[nChan]; // 2nd and 3rd LF lepton Eta
  TH1F *h_UKlep2and3Eta[nChan]; // 2nd and 3rd UK lepton Eta

  // Fake baseline lepton
  TH1F *h_PRbaselep1Pt [nChan]; // 1st PR base lepton Pt
  TH1F *h_PRbaselep2Pt [nChan]; // 2nd PR base lepton Pt
  TH1F *h_PRbaselep3Pt [nChan]; // 3nd PR base lepton Pt
  TH1F *h_CObaselep1Pt [nChan]; // 1st CO base lepton Pt
  TH1F *h_CObaselep2Pt [nChan]; // 2nd CO base lepton Pt
  TH1F *h_CObaselep3Pt [nChan]; // 3nd CO base lepton Pt
  TH1F *h_HFbaselep1Pt [nChan]; // 1st HF base lepton Pt
  TH1F *h_HFbaselep2Pt [nChan]; // 2nd HF base lepton Pt
  TH1F *h_HFbaselep3Pt [nChan]; // 3nd HF base lepton Pt
  TH1F *h_LFbaselep1Pt [nChan]; // 1st LF base lepton Pt
  TH1F *h_LFbaselep2Pt [nChan]; // 2nd LF base lepton Pt
  TH1F *h_LFbaselep3Pt [nChan]; // 3nd LF base lepton Pt
  TH1F *h_UKbaselep1Pt [nChan]; // 1st UK base lepton Pt
  TH1F *h_UKbaselep2Pt [nChan]; // 2nd UK base lepton Pt
  TH1F *h_UKbaselep3Pt [nChan]; // 3nd UK base lepton Pt
  TH1F *h_PRbaselep1Eta[nChan]; // 1st PR base lepton Eta
  TH1F *h_PRbaselep2Eta[nChan]; // 2nd PR base lepton Eta
  TH1F *h_PRbaselep3Eta[nChan]; // 3nd PR base lepton Eta
  TH1F *h_CObaselep1Eta[nChan]; // 1st CO base lepton Eta
  TH1F *h_CObaselep2Eta[nChan]; // 2nd CO base lepton Eta
  TH1F *h_CObaselep3Eta[nChan]; // 3nd CO base lepton Eta
  TH1F *h_HFbaselep1Eta[nChan]; // 1st HF base lepton Eta
  TH1F *h_HFbaselep2Eta[nChan]; // 2nd HF base lepton Eta
  TH1F *h_HFbaselep3Eta[nChan]; // 3nd HF base lepton Eta
  TH1F *h_LFbaselep1Eta[nChan]; // 1st LF base lepton Eta
  TH1F *h_LFbaselep2Eta[nChan]; // 2nd LF base lepton Eta
  TH1F *h_LFbaselep3Eta[nChan]; // 3nd LF base lepton Eta
  TH1F *h_UKbaselep1Eta[nChan]; // 1st UK base lepton Eta
  TH1F *h_UKbaselep2Eta[nChan]; // 2nd UK base lepton Eta
  TH1F *h_UKbaselep3Eta[nChan]; // 3nd UK base lepton Eta

  // Fake signal lepton for matrix method
  TH1F *h_PRbaselep2and3Pt [nChan]; // 2nd and 3rd PR base lepton Pt
  TH1F *h_CObaselep2and3Pt [nChan]; // 2nd and 3rd CO base lepton Pt
  TH1F *h_HFbaselep2and3Pt [nChan]; // 2nd and 3rd HF base lepton Pt
  TH1F *h_LFbaselep2and3Pt [nChan]; // 2nd and 3rd LF base lepton Pt
  TH1F *h_UKbaselep2and3Pt [nChan]; // 2nd and 3rd UK base lepton Pt
  TH1F *h_PRbaselep2and3Eta[nChan]; // 2nd and 3rd PR base lepton Eta
  TH1F *h_CObaselep2and3Eta[nChan]; // 2nd and 3rd CO base lepton Eta
  TH1F *h_HFbaselep2and3Eta[nChan]; // 2nd and 3rd HF base lepton Eta
  TH1F *h_LFbaselep2and3Eta[nChan]; // 2nd and 3rd LF base lepton Eta
  TH1F *h_UKbaselep2and3Eta[nChan]; // 2nd and 3rd UK base lepton Eta

  // Fake signal lepton
  TH1F *h_PRlepPt [nChan]; // PR lepton Pt
  TH1F *h_COlepPt [nChan]; // CO lepton Pt
  TH1F *h_HFlepPt [nChan]; // HF lepton Pt
  TH1F *h_LFlepPt [nChan]; // LF lepton Pt
  TH1F *h_UKlepPt [nChan]; // UK lepton Pt
  TH1F *h_PRlepEta[nChan]; // PR lepton Eta
  TH1F *h_COlepEta[nChan]; // CO lepton Eta
  TH1F *h_HFlepEta[nChan]; // HF lepton Eta
  TH1F *h_LFlepEta[nChan]; // LF lepton Eta
  TH1F *h_UKlepEta[nChan]; // UK lepton Eta

  // Fake base lepton
  TH1F *h_PRbaselepPt [nChan]; // PR base lepton Pt
  TH1F *h_CObaselepPt [nChan]; // CO base lepton Pt
  TH1F *h_HFbaselepPt [nChan]; // HF base lepton Pt
  TH1F *h_LFbaselepPt [nChan]; // LF base lepton Pt
  TH1F *h_UKbaselepPt [nChan]; // UK base lepton Pt
  TH1F *h_PRbaselepEta[nChan]; // PR base lepton Eta
  TH1F *h_CObaselepEta[nChan]; // CO base lepton Eta
  TH1F *h_HFbaselepEta[nChan]; // HF base lepton Eta
  TH1F *h_LFbaselepEta[nChan]; // LF base lepton Eta
  TH1F *h_UKbaselepEta[nChan]; // UK base lepton Eta

  // base lepton kinematics
  TH1F *h_baselepChan[nChan];
  TH1F *h_baselep1Pt[nChan];
  TH1F *h_baselep2Pt[nChan];
  TH1F *h_baselep3Pt[nChan];
  TH1F *h_baseel1Pt[nChan];
  TH1F *h_baseel2Pt[nChan];
  TH1F *h_baseel3Pt[nChan];
  TH1F *h_basemu1Pt[nChan];
  TH1F *h_basemu2Pt[nChan];
  TH1F *h_basemu3Pt[nChan];
  TH1F *h_baselep1Eta[nChan];
  TH1F *h_baselep2Eta[nChan];
  TH1F *h_baselep3Eta[nChan];

  TH1F *h_llPt[nChan]; //Dilepton system Pt

  TH1F *h_sumLepPt   [nChan]; // Scalar sum of lepton pt
  TH1F *h_sumLepPtMet[nChan]; // Scalar sum of lepton pt and MET
  TH1F *h_dPhiWZ     [nChan]; // dPhi between W and Z leptons
  TH1F *h_nMuComb    [nChan]; // number of combined muons

  // Isolation
  TH1F *h_elTrackIso[nChan]; // electron track iso.
  TH1F *h_elCaloIso [nChan]; // electron calo iso.
  TH1F *h_muTrackIso[nChan]; // muon track iso.
  TH1F *h_muCaloIso [nChan]; // muon calo iso.
  TH1F *h_el1TrackIso[nChan]; // electron track iso.
  TH1F *h_el1CaloIso [nChan]; // electron calo iso.
  TH1F *h_mu1TrackIso[nChan]; // muon track iso.
  TH1F *h_mu1CaloIso [nChan]; // muon calo iso.
  TH1F *h_el2TrackIso[nChan]; // electron track iso.
  TH1F *h_el2CaloIso [nChan]; // electron calo iso.
  TH1F *h_mu2TrackIso[nChan]; // muon track iso.
  TH1F *h_mu2CaloIso [nChan]; // muon calo iso.
  TH1F *h_el3TrackIso[nChan]; // electron track iso.
  TH1F *h_el3CaloIso [nChan]; // electron calo iso.
  TH1F *h_mu3TrackIso[nChan]; // muon track iso.
  TH1F *h_mu3CaloIso [nChan]; // muon calo iso.

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

  // Base lepton truth classification
  TH1F *h_baselepOrigin [nChan];// Lepton origin from McTruthClassifier
  TH1F *h_baselep1Origin[nChan];// Lepton origin from McTruthClassifier
  TH1F *h_baselep2Origin[nChan];// Lepton origin from McTruthClassifier
  TH1F *h_baselep3Origin[nChan];// Lepton origin from McTruthClassifier
  TH1F *h_baselepClass [nChan]; // truth classifcation from LeptonTruthTools
  TH1F *h_baselep1Class[nChan]; // truth classifcation from LeptonTruthTools
  TH1F *h_baselep2Class[nChan]; // truth classifcation from LeptonTruthTools
  TH1F *h_baselep3Class[nChan]; // truth classifcation from LeptonTruthTools

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
  TH1F *h_dPhiLLJet    [nChan]; // dPhi(lep1+lep2, leading jet)
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
