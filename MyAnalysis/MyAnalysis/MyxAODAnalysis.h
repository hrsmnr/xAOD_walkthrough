#ifndef MyAnalysis_MyxAODAnalysis_H
#define MyAnalysis_MyxAODAnalysis_H

#include <EventLoop/Algorithm.h>

/Added by minoru
#include"xAODRootAccess/Init.h"
#include"xAODRootAccess/TEvent.h"
#include"xAODRootAccess/TStore.h"
#include"CPAnalysisExamples/errorcheck.h"

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
namespace xAOD{
  class EventInfo_v1;
  typedef EventInfo_v1 EventInfo;
}
namespace CP{
  class SystematicSet;
}
class GoodRunsListSelectionTool;
class EventSelector;
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
  xAOD::TEvent *m_event; //!
  xAOD::TStore m_store; //!
  bool m_isMC; //!
  int m_eventCounter; //!
  int m_numCleanEvents; //!
  int m_debug_mode; //!
  std::vector<std::string> *m_vec_eveSelec; //!
  //0:no debug output, 1:-v, 2:-vv, 3:-vvv
  std::vector<CP::SystematicSet> m_sysList; //!

#ifndef __CINT__
  ST::SUSYObjDef_xAOD *m_susyObjTool; //!
  GoodRunsListSelectionTool *m_grl; //!
#endif // not __CINT__

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
