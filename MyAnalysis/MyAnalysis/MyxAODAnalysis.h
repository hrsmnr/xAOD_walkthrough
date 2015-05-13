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

#include"MyAnalysis/Plotter.h"

#include<string>
#include<vector>

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
class TStopwatch;
//end adding

class MyxAODAnalysis : public EL::Algorithm
{
  // put your configuration variables here as public variables.
  // that way they can be set directly from CINT and python.
public:

  // variables that don't get filled at submission time should be
  // protected from being send from the submission node to the worker
  // node (done by the //!)
public:

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
  bool m_useFAX;
  int m_dsid;
  long long int m_nSkipNum;
  std::vector<std::string> *m_vec_eveSelec;
  std::string m_outputDir;

#ifndef __CINT__
  ST::SUSYObjDef_xAOD *m_susyObjTool; //!
  SUSY::CrossSectionDB *m_XSDB; //!
  GoodRunsListSelectionTool *m_grl; //!
#endif // not __CINT__

  std::vector<std::vector<Plotter*> > *m_vec_plotter; //!
  std::vector<std::vector<TStopwatch*> > *m_vec_watch; //!

  bool IsConsideredSyst(TString sysBasename);
  void SetEventCounter(EventSelector *EveSelec, int eveSelec, int sys);
  bool PassPreSelection(const xAOD::EventInfo* eventInfo);
  void dumpEventCounters();

  //Setter used in a steering macro (e.g. test.Run.cxx).
  void SetDebugMode(MSG::Level debugMode=MSG::ERROR){m_debugMode = debugMode;};
  void SetMaxEvent(long long int maxEvent=-1){m_maxEvent = maxEvent;};
  void SetNoSyst(bool nosyst=true){m_noSyst = nosyst;};
  void SetupFAX(bool useFAX){m_useFAX = useFAX;};
  void SetDSID(int dsid){m_dsid = dsid;};
  void SetSkipNum(long long int nskip){m_nSkipNum = nskip;};
  void SetSelectionRegion(const char* selec){m_vec_eveSelec->push_back(selec);};
  void SetOutputDir(const char* path){m_outputDir = path;};

  // Event counters
  // First index is for selection regions and second for systematic variation.
  std::vector<std::vector<int> > *n_initial; //!
  std::vector<std::vector<int> > *n_pass_hotSpot; //!
  std::vector<std::vector<int> > *n_pass_badJet; //!
  std::vector<std::vector<int> > *n_pass_feb; //!
  std::vector<std::vector<int> > *n_pass_badMu; //!
  std::vector<std::vector<int> > *n_pass_cosmic; //!
  std::vector<std::vector<int> > *n_pass_clean; //!
  std::vector<std::vector<int> > *n_pass_nBLep; //!
  std::vector<std::vector<int> > *n_pass_mllBase; //!
  std::vector<std::vector<int> > *n_pass_nLep; //!
  std::vector<std::vector<int> > *n_pass_nTau; //!
  std::vector<std::vector<int> > *n_pass_ssEmul; //!
  std::vector<std::vector<int> > *n_pass_trig; //!
  std::vector<std::vector<int> > *n_pass_truth; //!
  std::vector<std::vector<int> > *n_pass_sfos; //!
  std::vector<std::vector<int> > *n_pass_lz; //!
  std::vector<std::vector<int> > *n_pass_z; //!
  std::vector<std::vector<int> > *n_pass_met; //!
  std::vector<std::vector<int> > *n_pass_vbf; //!
  std::vector<std::vector<int> > *n_pass_jet; //!
  std::vector<std::vector<int> > *n_pass_mt; //!
  std::vector<std::vector<int> > *n_pass_mljj; //!
  std::vector<std::vector<int> > *n_pass_meff; //!
  std::vector<std::vector<int> > *n_pass_lepPt; //!
  std::vector<std::vector<int> > *n_pass_lepDR; //!
  std::vector<std::vector<int> > *n_pass_other; //!

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

  // this is needed to distribute the algorithm to the workers
  ClassDef(MyxAODAnalysis, 1);
};

#endif
