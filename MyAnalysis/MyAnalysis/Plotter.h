#ifndef SusyAna_Plotter_h
#define SusyAna_Plotter_h

// Plotter - filling histogram for each selection region and systematics

#include<string>
#include<TObject.h>
#include"AsgTools/MsgLevel.h"

#include"MyAnalysis/EventSelector.h"

class TFile;
class TH1F;

#define nChan 5

class Plotter : public TObject
{
 public:
  Plotter(const std::string& sel="none", const std::string& sys="none", const MSG::Level& dbg=MSG::ERROR);
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
  TFile *m_rootfile;

  bool BookHistograms();

  // Declaration of histograms
  TH1F *h_xsec;
  TH1F *h_nEve;

  TH1F *h_lepChan[nChan];
  TH1F *h_lep1Pt[nChan];
  TH1F *h_lep2Pt[nChan];
  TH1F *h_lep3Pt[nChan];
  TH1F *h_el1Pt[nChan];
  TH1F *h_el2Pt[nChan];
  TH1F *h_el3Pt[nChan];
  TH1F *h_mu1Pt[nChan];
  TH1F *h_mu2Pt[nChan];
  TH1F *h_mu3Pt[nChan];
  TH1F *h_lep1Eta[nChan];
  TH1F *h_lep2Eta[nChan];
  TH1F *h_lep3Eta[nChan];

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

};
#endif
