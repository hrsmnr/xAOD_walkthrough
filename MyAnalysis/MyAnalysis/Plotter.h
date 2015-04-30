#ifndef SusyAna_Plotter_h
#define SusyAna_Plotter_h

// Plotter - filling histogram for each selection region and systematics

#include<string>
#include<TObject.h>
#include"AsgTools/MsgLevel.h"

#include"MyAnalysis/EventSelector.h"

class Plotter : public TObject
{
 public:
  Plotter(std::string sel="none", std::string sys="none", MSG::Level dbg=MSG::ERROR);
  virtual ~Plotter(){};

  virtual void initialize();
  virtual void finalize();

  bool FillHistograms(EventSelector *EveSelec);

  ClassDef(Plotter, 1);

 protected:
  MSG::Level m_dbg; // debug level

  bool BookHistograms();

};
#endif
