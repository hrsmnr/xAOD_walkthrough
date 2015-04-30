#ifndef MyAnalysis_MyxAODAnalysis_H
#define MyAnalysis_MyxAODAnalysis_H

#include <EventLoop/Algorithm.h>

//Added by minoru
#include"xAODRootAccess/Init.h"
#include"xAODRootAccess/TEvent.h"
#include"xAODRootAccess/TStore.h"
#include"CPAnalysisExamples/errorcheck.h"
#include"AsgTools/MsgLevel.h"

#include "PATInterfaces/SystematicVariation.h"
#include "PATInterfaces/SystematicRegistry.h"
#include "PATInterfaces/SystematicCode.h"

#include<string>
#include<vector>
#include"TH1F.h"

#define nSyst 23
#define nEveSelec 1
#define nChan 5

namespace ST{
  class SUSYObjDef_xAOD;
}
namespace SUSY{
  class CrossSectionDB;
}
namespace xAOD{
  class EventInfo_v1;
  typedef EventInfo_v1 EventInfo;
}
namespace CP{
  class SystematicSet;
}
class GoodRunsListSelectionTool;
class EventSelector;
class Plotter;
//end adding

class MyxAODAnalysis : public EL::Algorithm
{
  // put your configuration variables here as public variables.
  // that way they can be set directly from CINT and python.
public:
  // float cutValue;
  Int_t m_sysId;

  // variables that don't get filled at submission time should be
  // protected from being send from the submission node to the worker
  // node (done by the //!)
public:
  // Tree *myTree; //!
  // TH1 *myHist; //!

  //Added by minoru
  //Variables which are initialized in initialize();
  //We do need "//!" after the declaration.
  xAOD::TEvent *m_event; //!
  xAOD::TStore m_store; //!
  bool m_isMC; //!
  long long int m_eventCounter; //!
  long long int m_processedEvents; //!
  long long int m_numCleanEvents; //!
  double m_eventWeight; //!
  double m_crossSection; //!
  std::vector<CP::SystematicSet> m_sysList; //!

  //Variables which are initialized (or Set) in testRun.cxx;
  //We don't need "//!" for them.
  long long int m_maxEvent;
  MSG::Level m_debugMode;
  bool m_noSyst;
  int m_dsid;
  long long int m_nSkipNum;
  std::vector<std::string> *m_vec_eveSelec;

#ifndef __CINT__
  ST::SUSYObjDef_xAOD *m_susyObjTool; //!
  SUSY::CrossSectionDB *m_XSDB; //!
  GoodRunsListSelectionTool *m_grl; //!
#endif // not __CINT__

  Plotter *m_plotter[nChan][nSyst]; //!

  TH1F *h_xsec; //!
  TH1F *h_nEve; //!
  TH1F *h_lepChan[nChan][nSyst]; //!
  TH1F *h_all[nChan][nSyst]; //!
  TH1F *h_lep1Pt[nChan][nSyst]; //!
  TH1F *h_lep2Pt[nChan][nSyst]; //!
  TH1F *h_lep3Pt[nChan][nSyst]; //!
  TH1F *h_el1Pt[nChan][nSyst]; //!
  TH1F *h_el2Pt[nChan][nSyst]; //!
  TH1F *h_el3Pt[nChan][nSyst]; //!
  TH1F *h_mu1Pt[nChan][nSyst]; //!
  TH1F *h_mu2Pt[nChan][nSyst]; //!
  TH1F *h_mu3Pt[nChan][nSyst]; //!
  TH1F *h_lep1Eta[nChan][nSyst]; //!
  TH1F *h_lep2Eta[nChan][nSyst]; //!
  TH1F *h_lep3Eta[nChan][nSyst]; //!

  bool IsConsideredSyst(TString sysBasename);
  bool BookHistograms();
  void SetEventCounter(EventSelector *EveSelec, int eveSelec, int sys);
  bool FillHistograms(EventSelector *EveSelec);
  bool PassPreSelection(const xAOD::EventInfo* eventInfo);
  void dumpEventCounters();

  //Setter used in a steering macro (e.g. test.Run.cxx).
  void SetDebugMode(MSG::Level debugMode=MSG::ERROR){m_debugMode = debugMode;};
  void SetMaxEvent(long long int maxEvent=-1){m_maxEvent = maxEvent;};
  void SetNoSyst(bool nosyst=true){m_noSyst = nosyst;};
  void SetDSID(long long int dsid){m_dsid = dsid;};
  void SetSkipNum(long long int nskip){m_nSkipNum = nskip;};
  void SetSelectionRegion(const char* selec){m_vec_eveSelec->push_back(selec);};

  //end adding

  // this is a standard constructor
  MyxAODAnalysis ();

  // these are the functions inherited from Algorithm
  virtual EL::StatusCode setupJob (EL::Job& job);
  virtual EL::StatusCode fileExecute ();
  virtual EL::StatusCode histInitialize ();
  virtual EL::StatusCode changeInput (bool firstFile);
  virtual EL::StatusCode initialize ();
  virtual EL::StatusCode execute ();
  virtual EL::StatusCode postExecute ();
  virtual EL::StatusCode finalize ();
  virtual EL::StatusCode histFinalize ();

  // Event counters
  int n_initial[nEveSelec][nSyst];
  int n_pass_hotSpot[nEveSelec][nSyst];
  int n_pass_badJet[nEveSelec][nSyst];
  int n_pass_feb[nEveSelec][nSyst];
  int n_pass_badMu[nEveSelec][nSyst];
  int n_pass_cosmic[nEveSelec][nSyst];
  int n_pass_clean[nEveSelec][nSyst];
  int n_pass_nBLep[nEveSelec][nSyst];
  int n_pass_mllBase[nEveSelec][nSyst];
  int n_pass_nLep[nEveSelec][nSyst];
  int n_pass_nTau[nEveSelec][nSyst];
  int n_pass_ssEmul[nEveSelec][nSyst];
  int n_pass_trig[nEveSelec][nSyst];
  int n_pass_truth[nEveSelec][nSyst];
  int n_pass_sfos[nEveSelec][nSyst];
  int n_pass_lz[nEveSelec][nSyst];
  int n_pass_z[nEveSelec][nSyst];
  int n_pass_met[nEveSelec][nSyst];
  int n_pass_vbf[nEveSelec][nSyst];
  int n_pass_jet[nEveSelec][nSyst];
  int n_pass_mt[nEveSelec][nSyst];
  int n_pass_mljj[nEveSelec][nSyst];
  int n_pass_meff[nEveSelec][nSyst];
  int n_pass_lepPt[nEveSelec][nSyst];
  int n_pass_lepDR[nEveSelec][nSyst];
  int n_pass_other[nEveSelec][nSyst];

  // this is needed to distribute the algorithm to the workers
  ClassDef(MyxAODAnalysis, 1);
};

#endif
