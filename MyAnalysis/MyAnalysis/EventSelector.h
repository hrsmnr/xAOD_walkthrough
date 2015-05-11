#ifndef SusyAna_EventSelector_h
#define SusyAna_EventSelector_h

// EventSelector - event selection for SUSY ana

#include<string>
#include<TObject.h>
#include"TVector2.h"
#include"TLorentzVector.h"
#include"xAODEgamma/Electron.h"
#include"xAODMuon/Muon.h"
#include"xAODJet/Jet.h"
#include"xAODPrimitives/IsolationType.h"
#include"AsgTools/MsgLevel.h"

namespace ST{
  class SUSYObjDef_xAOD;
}

namespace xAOD{
  class TStore;
}

#define nAnaLep 4
enum ChIndex{Ch_all,Ch_eee,Ch_eem,Ch_emm,Ch_mmm,nChannels};

// Signal Requirements
const float MZ                          = 91.2;
const float MUPSILON                    = 9.4;
const float MUON_D0SIG_CUT              = 3.0;
const float MUON_Z0_SINTHETA_CUT        = 1.0;//0.2;

class EventSelector : public TObject
{
 public:
  EventSelector(ST::SUSYObjDef_xAOD *SUSYObjDef, const std::string &sel="none", const std::string &sys="none", const int &isMC=1, const MSG::Level &dbg=MSG::ERROR);
  virtual ~EventSelector(){};

  // Initialization
  virtual bool initialize();
  virtual void finalize();
  virtual void setStore(xAOD::TStore* store){m_store=store;};

  // Preselection, before object selection
  //    virtual bool preSelectEvent();

  // Full event selection.
  virtual bool selectObject();
  virtual bool selectEvent();
  virtual double getTotalSF(){return m_totalSF;};

  Int_t getBaseLepIndex (Int_t id){return m_baseLepIndex [id];};
  Int_t getBaseLepFlavor(Int_t id){return m_baseLepFlavor[id];};
  TLorentzVector getBaseLep(Int_t id){return m_baseLeps[id];};
  Int_t getLeadLepIndex (Int_t id){return m_leadLepIndex [id];};
  Int_t getLeadLepFlavor(Int_t id){return m_leadLepFlavor[id];};
  TLorentzVector getLeadLep(Int_t id){return m_leadLeps[id];};

  ///////////////////////////////////////////////
  int Get_initial     (){return n_initial     ;};
  int Get_pass_hotSpot(){return n_pass_hotSpot;};
  int Get_pass_badJet (){return n_pass_badJet ;};
  int Get_pass_feb    (){return n_pass_feb    ;};
  int Get_pass_badMu  (){return n_pass_badMu  ;};
  int Get_pass_cosmic (){return n_pass_cosmic ;};
  int Get_pass_clean  (){return n_pass_clean  ;};
  int Get_pass_nBLep  (){return n_pass_nBLep  ;};
  int Get_pass_mllBase(){return n_pass_mllBase;};
  int Get_pass_nLep   (){return n_pass_nLep   ;};
  int Get_pass_nTau   (){return n_pass_nTau   ;};
  int Get_pass_ssEmul (){return n_pass_ssEmul ;};
  int Get_pass_trig   (){return n_pass_trig   ;};
  int Get_pass_truth  (){return n_pass_truth  ;};
  int Get_pass_sfos   (){return n_pass_sfos   ;};
  int Get_pass_lz     (){return n_pass_lz     ;};
  int Get_pass_z      (){return n_pass_z      ;};
  int Get_pass_met    (){return n_pass_met    ;};
  int Get_pass_vbf    (){return n_pass_vbf    ;};
  int Get_pass_jet    (){return n_pass_jet    ;};
  int Get_pass_mt     (){return n_pass_mt     ;};
  int Get_pass_mljj   (){return n_pass_mljj   ;};
  int Get_pass_meff   (){return n_pass_meff   ;};
  int Get_pass_lepPt  (){return n_pass_lepPt  ;};
  int Get_pass_lepDR  (){return n_pass_lepDR  ;};
  int Get_pass_other  (){return n_pass_other  ;};

  ///////////////////////////////////////////////
  // Preparing objects
  ///////////////////////////////////////////////
#ifndef __CINT__
  ST::SUSYObjDef_xAOD* getSUSYTools(){return m_susyObjTool;};
  /* virtual bool IsMyBaselineElectron(xAOD::Electron el); */
  /* virtual bool IsMySignalElectron  (xAOD::Electron el); */
  /* virtual bool IsMyBaselineMuon    (const xAOD::Muon& mu); */
  /* virtual bool IsMySignalMuon      (const xAOD::Muon* mu); */
  virtual bool IsMyPreJet          (xAOD::Jet jet);
  virtual bool IsMyBaselineJet     (xAOD::Jet jet);
  virtual bool IsMySignalJet       (xAOD::Jet jet);

  std::vector< xAOD::Electron >* GetSignalElectron(){return m_vec_signalElectron;};
  std::vector< xAOD::Electron >* GetBaseElectron  (){return m_vec_baseElectron;  };
  std::vector< xAOD::Muon >*     GetSignalMuon    (){return m_vec_signalMuon;    };
  std::vector< xAOD::Muon >*     GetBaseMuon      (){return m_vec_baseMuon;      };
  std::vector< xAOD::Jet >*      GetSignalJet     (){return m_vec_signalJet;     };
  std::vector< xAOD::Jet >*      GetBaseJet       (){return m_vec_baseJet;       };
  std::vector< xAOD::Jet >*      GetPreJet        (){return m_vec_preJet;        };
  TVector2                       GetMEt           (){return m_met;               };
#endif // not __CINT__

  ///////////////////////////////////////////////
  // Cut methods
  ///////////////////////////////////////////////

  /* bool passEventCleaning(const MuonVector& preMuons, const MuonVector& baseMuons, */
  /*                        const JetVector& preJets, const JetVector& baseJets, */
  /*                        const Susy::Met* met); */
  /* //bool passFCal(); */
  /* bool passHfor(); */
  /* bool passPeriod(); */

  /* // Lepton/jet multiplicity */
  bool passNBaseLepCut();
  bool passNSignalLepCut();
  bool passLepChan();
  bool passNLepCut();
  /* bool passNTauCut(const TauVector& taus, const TauVector& tightTaus); */
  bool passNJetCut();
  /* bool passNBJetCut(const JetVector& jets); */

  // Flavor and charge requirements
  virtual bool passSFOSCut();
  virtual bool passSFSSCut();
  virtual bool passOFOSCut();
  virtual bool passSSCut();
  virtual bool passOSCut();
  /* virtual bool passOSLepTauCut(const LeptonVector& leptons, const TauVector& taus); */
  bool passFlavChargeCut();

  /* // Trigger */
  /* bool passEventTrigger(); */
  /* bool passTrigger(const LeptonVector& leptons, const TauVector& taus, const Susy::Met* met); */

  // MET
  bool passMetCut();
  bool passMetRelCut();

  // Topology
  bool passVbfCut();

  // Lepton/tau invariant mass
  bool passMllBaseCut();
  bool passMllCut();
  bool passUpsilonCut();
  bool passZCut();
  bool passZeeSSCut();
  bool passLooseZCut();
  bool isLooseSoftEle(unsigned int id, bool isSignal=false);
  bool isLooseSoftMu(unsigned int id, bool isSignal=false);
  bool passMsfosCut();
  bool passMinMsfosCut();
  bool passMlllCut();
  /* bool passMltCut(); */
  /* bool passMttCut(const TauVector& taus); */
  /* bool passMassCuts(const LeptonVector& leptons, const TauVector& taus); */
  bool passMljjCut();

  // Transverse mass, etc.
  bool passMtCut();
  float getMaxMT2();
  bool passMaxMT2Cut();
  /* bool passMtllCut(const LeptonVector& leptons, const Susy::Met* met); */

  // Meff
  bool passMeffCut();

  // Lepton dR, dPhi
  //  bool passMinDRBaseCut();
  bool passMinDPhiOSCut();
  bool passLepDEtaCut();
  /* bool passLepAngularCuts(const LeptonVector& signalLeptons, const LeptonVector& baseLeptons); */

  // Lepton/tau pt requirements
  bool passLepPtCut();
  bool passSumLepPtCut();
  //  bool passTauPtCut();
  //  bool passSumTauPtCut();
  bool passLepTauPtCuts();

  // Truth selection
  bool passLepTruthCut();

  ///////////////////////////////////////////////
  // Event modifications
  ///////////////////////////////////////////////
  // Subtract lepton from MET and return new MET
  /* void subLepFromMet(const Susy::Met* inMet, Susy::Met& outMet, const Susy::Lepton* lep); */
  /* // Emulate SS with Zll+l */
  /* //void getSSEmulation(const LeptonVector& inLeps, LeptonVector& outLeps, */
  /*                     //const Susy::Met* inMet, Susy::Met& outMet); */
  /* // Get SS emulation leptons, as well as dropped lepton */
  /* bool getSSEmulLeps(const LeptonVector& inLeps, LeptonVector& outLeps,  */
  /*                    const Susy::Lepton*& dropLep); */
  /* // Get SS emulation jets */
  /* bool isSSEmulORJet(const Susy::Jet* jet, const JetVector& inJets, const Lepton* dropLep); */
  /* bool passSSEmulJetCuts(const Susy::Jet* jet, const LeptonVector& outLeps); */
  /* bool getSSEmulJets(const JetVector& inJets, JetVector& outJets, */
  /*                    const LeptonVector& outLeps, const Lepton* dropLep); */
  /* // SS emulation from 3L events */
  /* bool passSSEmulation(const LeptonVector& inLeps, LeptonVector& outLeps, */
  /*                      const JetVector& inJets, JetVector& outJets, */
  /*                      const Susy::Met* inMet, Susy::Met& outMet); */

  ///////////////////////////////////////////////
  // Event weighting
  ///////////////////////////////////////////////

  /* // Trigger reweighting */
  /* float getTriggerWeight(const LeptonVector& leptons, const JetVector& jets,  */
  /*                        const Susy::Met* met, WeightSys::WSys sys=WeightSys::nom); */
  /* // Lepton efficiency scale factor */
  /* float getLeptonSF(const LeptonVector& leptons, uint weightSys=WeightSys::nom); */

  /* // Test if good channel for charge flip measurement */
  /* bool isOkForQFlip(const LeptonVector& leptons); */
  /* // Get lepton vector for q-flip estimate */
  /* LeptonVector getQFlipLeptons(const LeptonVector& inLeps); */
  /* // Charge flip method returns an event weight  */
  /* // as well as the smeared electrons and MET */
  /* float getChargeFlip(const LeptonVector& inLeps, LeptonVector& outLeps,  */
  /*                     const Susy::Met* inMet, Susy::Met& outMet); */

  /* // Helper method for pileup sys */
  /* float getPileupSys(const Susy::Event* evt, WeightSys::WSys sys); */

  ///////////////////////////////////////////////
  // Misc. methods
  ///////////////////////////////////////////////

  // Dump cutflow - if derived class uses different cut ordering, override this method
  virtual void dumpEventCounters();
  virtual int getChan();
  virtual int nSignalLeps(){return m_nSignalLeps;};
  virtual int nBaselineLeps(){return m_nBaselineLeps;};
  virtual int nSignalJets(){return m_nSignalJets;};
  virtual int nBaselineJets(){return m_nBaselineJets;};
  virtual bool hasSFOS();
  virtual bool hasSFSS();
  virtual bool hasOFOS();
  virtual bool hasOS();
  virtual bool hasSS();
  //  virtual bool hasBJet();
  virtual int numBJets();
  virtual bool isInMassWindow(Double_t mass, Double_t targetMass, Double_t window);
  virtual bool hasUpsilon();
  virtual bool hasZ();
  virtual bool hasZlll();
  virtual bool hasZllll();
  virtual float findBestMSFOS(int& index1, int& index2, int& flav, float mass=MZ);
  virtual float getMetRel(bool useForward=false);
  virtual float getMt(TLorentzVector lep, TVector2 met);
  virtual float getMeff(float jetPtCut=40., bool useMet=true);
  virtual float getMljj();
  virtual TLorentzVector getFourVector(int index, int flav);
  virtual int getCharge(int index, int flav);
  virtual float getIsolationValue(int index, int flav, xAOD::Iso::IsolationType type);
  virtual xAOD::TrackParticle* getTrack(int index, int flav);
  virtual bool isOS(int charge1, int charge2);
  virtual bool isSS(int charge1, int charge2);
  virtual void TypSel(int nLep, int nTau, int nBaseLep, int nBaseTau, int nBjetMin, int nBjetMax);

  /* // Selection region */
  /* void setSelection(std::string s) { m_sel = s; } */
  /* std::string getSelection() { return m_sel; } */

  /* // Systematics */
  /* void setSystematics(ObjSys::OSys objSys=ObjSys::nom, bool doWeightSys=false){ */
  /*   m_objSys = objSys; */
  /*   m_doWeightSys = doWeightSys; */
  /* } */

  /* // Tau ID */
  /* void setTauID(TauID id) { m_tauID = id; } */

  /* // debug check */
  /* bool debugEvent(); */

  // Truth selection
  bool isRealLepton(unsigned int id);     // real, prompt lepton
  /* bool isConvLepton(const Susy::Lepton*);     // conversion */
  bool isFakeLepton(unsigned int id);     // general fake
  bool isChargeFlipElectron(unsigned int id);
  /* bool isUKLepton(const Susy::Lepton*);       // unknown lepton */
  /* bool isHFLepton(const Susy::Lepton*);       // heavy flavor */
  /* bool isLFLepton(const Susy::Lepton*);       // light flavor */
  /* bool isJFLepton(const Susy::Lepton*);       // jet flavor = HF + LF */

  /* bool isQuarkJetTau(const Susy::Tau*);       // quark jet fake tau */
  /* bool isGluonJetTau(const Susy::Tau*);       // gluon jet fake tau */

  /* // Truth particle matching */
  /* Susy::TruthParticle* getTruthLepton(const Susy::Lepton*); */

  ClassDef(EventSelector, 1);

 protected:

  ST::SUSYObjDef_xAOD           *m_susyObjTool;    // Object definition tool in SUSYTools
  xAOD::TStore                  *m_store;          // TStore passed by MyxAODAnalysis

  bool                           m_objReady;       // true after calling selectObject();
  int                            m_nSignalLeps;
  int                            m_nBaselineLeps;
  int                            m_nSignalJets;
  int                            m_nBaselineJets;
  MSG::Level                     m_dbg;            // debug level
  int                            m_isMC;           // 1:MC, 0:Data
  double                         m_totalSF;        // Total scale factor
  /* std::string                 m_sample;         // sample name */
  std::string                    m_sel;            // event selection string
  std::string                    m_sys;            // systematic name string
  /* int                         m_selFlag;        // Integer flag for selection (for HistFitterTree) */
  /* bool                        m_doWeightSys;    // Toggle weight systematics */
  /* ObjSys::OSys                m_objSys;         // Object systematic flag */

  /* //bool                      m_subLepIso;      // Flag to control subtraction of leptons from iso cones */
  /* TauID                       m_tauID;          // Tau ID selection flag */

  /* bool                        m_use2LTrig;      // Use the 2-lepton trigger logic instead of 3-lepton */
  /* static DilTrigLogic*        m_2lTrigLogic;    // 2-lepton trigger logic class */
  /* static TrilTrigLogic*       m_3lTrigLogic;    // 3-lepton trigger logic class */

  /* //ElectronVector            m_qFlipElectrons; // Smeared electrons for qflip estimate */
  /* std::vector<Susy::Electron> m_qFlipElectrons; // Smeared electrons for qflip estimate */
  /* //std::vector<Susy::Muon>   m_qFlipMuons;     // Muon copies for qflip estimate */
  /* static chargeFlip*          m_chargeFlip;     // Charge flip tool */
  /* // New charge flip wrapper */
  /* ChargeFlipTool*             m_qFlipTool;      // Charge flip tool */

  Int_t m_baseLepIndex [nAnaLep];
  Int_t m_baseLepFlavor[nAnaLep]; //0:Electron, 1:Muon, -1:Initial
  TLorentzVector m_baseLeps[nAnaLep];
  Int_t m_leadLepIndex [nAnaLep];
  Int_t m_leadLepFlavor[nAnaLep]; //0:Electron, 1:Muon, -1:Initial
  TLorentzVector m_leadLeps[nAnaLep];

#ifndef __CINT__
  std::vector< xAOD::Electron > *m_vec_signalElectron;
  std::vector< xAOD::Electron > *m_vec_baseElectron  ;
  std::vector< xAOD::Muon >     *m_vec_signalMuon;
  std::vector< xAOD::Muon >     *m_vec_baseMuon  ;
  std::vector< xAOD::Jet >      *m_vec_signalJet;
  std::vector< xAOD::Jet >      *m_vec_baseJet  ;
  std::vector< xAOD::Jet >      *m_vec_preJet  ;
  TVector2 m_met;
#endif // not __CINT__

  /* // Cut variables */
  /* bool                m_doAB3;          // process unblinded A-B3 (1/fb) */
  int                 m_nBaseLepMin;    // min baseline leptons 
  int                 m_nBaseLepMax;    // max baseline leptons 
  int                 m_nLepMin;        // min signal leptons 
  int                 m_nLepMax;        // max signal leptons 
  int                 m_nEleMin;        // min signal electrons 
  int                 m_nEleMax;        // max signal electrons 
  //int               m_nBaseTauMin;    // min baseline taus 
  //int               m_nBaseTauMax;    // max baseline taus 
  int                 m_nTauMin;        // min signal taus 
  int                 m_nTauMax;        // max signal taus 
  //int               m_nMedTauMin;     // min medium taus 
  //int               m_nMedTauMax;     // max medium taus 
  int                 m_nTightTauMin;   // min tight signal taus 
  int                 m_nTightTauMax;   // max tight signal taus 
  int                 m_nLepTauMin;     // min signal leps + taus 
  int                 m_nLepTauMax;     // max signal leps + taus 
  int                 m_nBaseLepTauMin; // min baseline leps + taus 
  int                 m_nBaseLepTauMax; // max baseline leps + taus 
  int                 m_nJetMin;        // min signal jets 
  int                 m_nJetMax;        // max signal jets 
  int                 m_nBJetMin;       // min signal jets 
  int                 m_nBJetMax;       // max signal jets 
  int                 m_nFJetMax;       // max forward jets (2lep) 
  int                 m_nCBJetMax;      // max central b-jets (2lep) 
  int                 m_nCLJetMin;      // min central light jets (2lep) 
  int                 m_nCLJetMax;      // max central light jets (2lep) 
  bool                m_useBaseLeps;    // use baseline leptons for event cuts 
  bool                m_applyTrig;      // apply 3L trigger cut 
  bool                m_trigAccOnly;    // use trigger acceptance but no matching 
  bool                m_useDilepTrigs;  // use dilepton triggers in addition to single lep 
  float               m_metMin;         // minimum met cut 
  float               m_metMax;         // maximum met cut 
  float               m_metRelMin;      // minimum met rel 
  bool                m_vetoUpsilon;    // flag to veto Upsilon
  bool                m_vetoZ;          // flag to veto Zs 
  bool                m_selZ;           // flag to select Zs 
  bool                m_vetoExtZ;       // extended multilepton Z veto  
  bool                m_selExtZ;        // extended multilepton Z veto  
  bool                m_vetoLooseZ;     // Z veto using loose soft leptons 
  bool                m_vetoZeeSS;      // veto SS ee pair in the Z window 
  //  bool                m_vetoB;          // flag to veto B jets 
  //  bool                m_selB;           // flag to select B jets 
  bool                m_vetoSFOS;       // flag to veto SFOS leptons 
  bool                m_selSFOS;        // flag to require SFOS leptons 
  bool                m_vetoSFSS;       // flag to veto SFSS leptons 
  bool                m_selSFSS;        // flag to require SFSS leptons 
  bool                m_vetoOFOS;       // flag to veto OFOS leptons 
  bool                m_selOFOS;        // flag to require OFOS leptons 
  //bool              m_vetoOFSS;       // flag to veto OFSS leptons 
  //bool              m_selOFSS;        // flag to require OFSS leptons 
  bool                m_selOS;          // flag to select OS leptons, no flav cut 
  bool                m_selSS;          // flag to select SS leptons, no flav cut 
  bool                m_selOSTau;       // flag to select OS taus 
  bool                m_selOSLepTau;    // flag to select OS lep, tau 
  bool                m_specialCut;     // just a temporary cut for testing/hacking 
  bool                m_orthoCut;       // temporary prescription for orthogonality requirement in SR0 
  float               m_mllBaseMin;     // minimum base-dilepton mass (any flav, charge) 
  float               m_minMllMin;      // minimum Msfos
  float               m_minMllMax;      // maximum Msfos
  float               m_mllMin;         // minimum dilepton mass (any flav, charge) 
  float               m_mllMax;         // maximum dilepton mass (any flav, charge) 
  float               m_vetoMllMin;     // mll veto window 
  float               m_vetoMllMax;     // mll veto window 
  float               m_msfosMin;       // minimum SFOS mass 
  float               m_msfosMax;       // maximum SFOS mass 
  float               m_mlllMin;        // minimum trilepton mass (no flav/charge requirements) 
  float               m_mlllMax;        // maximum trilepton mass (no flav/charge requirements) 
  float               m_mltMax;         // maximum M(lep,tau) cut 
  float               m_mttMin;         // minimum tau-tau mass 
  float               m_mttMax;         // maximum tau-tau mass 
  float               m_mljjMin;        // minimum M(lep,jet,jet) 
  float               m_mljjMax;        // maximum M(lep,jet,jet) 
  float               m_mtMin;          // minimum Mt cut using non-Z lepton and MET 
  float               m_mtMax;          // maximum Mt cut using non-Z lepton and MET 
  float               m_mtllMin;        // minimum Mt(l+l, met) cut 
  float               m_minDRBaseMin;   // minimum min dR between leptons 
  float               m_minDPhiOSMax;   // maximum min dphi cut between OS leptons 
  float               m_minDPhiOSMin;   // minimum min dphi cut between OS leptons 
  float               m_lepDEtaMax;     // maximum dEtall 
  float               m_jetPtMin;       // jet pt cuts 
  float               m_jetPtMax;       // jet pt cuts 
  float               m_lepPtMin;       // lepton pt cuts 
  float               m_lepPtMax;       // lepton pt cuts 
  float               m_lep1PtMin;      // leading lepton pt cut 
  float               m_lep2PtMin;      // leading lepton pt cut 
  float               m_sumLepPtMin;    // sum lepton pt cut 
  float               m_tau1PtMin;      // tau pt cuts 
  float               m_tau2PtMin;      // tau pt cuts 
  float               m_sumTauPtMin;    // sum tau pt cut 
  float               m_meffMin;        // minimum Meff cut 
  float               m_meffMax;        // maximum Meff cut 
  float               m_momMetMin;      // met or meff cut, minimum met 
  float               m_momMeffMin;     // met or meff cut, minimum meff 
  float               m_maxMT2Min;      // minimum mt2 cut, using maximal combination 
  float               m_maxMT2Max;      // maximum mt2 cut, using maximal combination 

  bool                m_selRealLeps;    // require signal leptons to be real (not charge flip) 
  bool                m_vetoRealLep1;   // flag to select fake leading light lepton 
  bool                m_estimateQFlip;  // flag to estimate the charge flip bkg 
  bool                m_emulateSS;      // remove a lepton to produce SS signature 

  //added by minoru 
  float               m_mjjMin;         // minimum Mjj cut 
  float               m_mjjMax;         // maximum Mjj cut 
  float               m_productEtaEtaMin; // minimum Eta1*Eta2Mjj cut 
  float               m_productEtaEtaMax; // maximum Eta1*Eta2Mjj cut 
  float               m_dEtaJJMin; // minimum DEtaJetJet cut 
  float               m_dEtaJJMax; // maximum DEtaJetJet cut 
  //end adding 

  // Event counters
  int                n_initial;
  int                n_pass_hotSpot;
  int                n_pass_badJet;
  int                n_pass_feb;
  int                n_pass_badMu;
  int                n_pass_cosmic;
  int                n_pass_clean;
  int                n_pass_nBLep;
  int                n_pass_mllBase;
  int                n_pass_nLep;
  int                n_pass_nTau;
  int                n_pass_ssEmul;
  int                n_pass_trig;
  int                n_pass_truth;
  int                n_pass_sfos;
  int                n_pass_lz;
  int                n_pass_z;
  int                n_pass_met;
  int                n_pass_vbf;
  int                n_pass_jet;
  int                n_pass_mt;
  int                n_pass_mljj;
  int                n_pass_meff;
  int                n_pass_lepPt;
  int                n_pass_lepDR;
  int                n_pass_other;

  /* // Weighted event counters after all cuts */
  /* float               n_evt_pileup;     // pileup weighted events */
  /* float               n_evt_lepSF;      // lepton efficiency weighted events */
  /* float               n_evt_btagSF;     // btag efficiency weighted events */
  /* float               n_evt_trigW;      // trigger efficiency weighted events */
  /* float               n_evt_qFlip;      // q-flip weighted events */
  /* float               n_evt_tot;        // all scale factors applied (except lumi) */
  /* float               n_evt_totLumi;    // all scale factors plus weighted to full lumi */
};


#endif
