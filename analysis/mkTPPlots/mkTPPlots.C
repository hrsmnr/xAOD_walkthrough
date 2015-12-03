#include<iostream>

#include"TString.h"
#include"TFile.h"
#include"TH1F.h"
#include"TUtil.cc"

Int_t mkTPPlots(){

  std::cout<<"Making efficiency file by the tag and probe method."<<std::endl;

  //  TString numerFileName = "../../result/submitDir~/data-2762.2S2B.AnaHists/data15_13TeV.00276262.physics_Main.merge.DAOD_SUSY2.f620_m1480_p2425_tid06564027_00.root";
  //  TString denomFileName = "../../result/submitDir/data-2762.2S2B.AnaHists/data15_13TeV.00276262.physics_Main.merge.DAOD_SUSY2.f620_m1480_p2425_tid06564027_00.root";
  //  TString numerFileName = "../../result/submitDir~/data-2762.2S2BSelZ.AnaHists/data15_13TeV.00276262.physics_Main.merge.DAOD_SUSY2.f620_m1480_p2425_tid06564027_00.root";
  //  TString denomFileName = "../../result/submitDir/data-2762.2S2BSelZ.AnaHists/data15_13TeV.00276262.physics_Main.merge.DAOD_SUSY2.f620_m1480_p2425_tid06564027_00.root";
  TString twoLepFileName = "../../result/submitDir~/data-2762.2S2B.AnaHists/data15_13TeV.00276262.physics_Main.merge.DAOD_SUSY2.f620_m1480_p2425_tid06564027_00.root";
  TString numerFileName = "../../result/submitDir~/data-2762.2S2BSelUpsi.AnaHists/data15_13TeV.00276262.physics_Main.merge.DAOD_SUSY2.f620_m1480_p2425_tid06564027_00.root";
  TString denomFileName = "../../result/submitDir/data-2762.2S2BSelUpsi.AnaHists/data15_13TeV.00276262.physics_Main.merge.DAOD_SUSY2.f620_m1480_p2425_tid06564027_00.root";
  TFile* f_beforeSelec = new TFile(twoLepFileName.Data());
  TFile* f_numer = new TFile(numerFileName.Data());
  TFile* f_denom = new TFile(denomFileName.Data());

  //For efficiency as a function of Pt
  TH1F* h_numerElPt = (TH1F*)(f_numer->Get("ee_lep2Pt"));
  TH1F* h_denomElPt = (TH1F*)(f_denom->Get("ee_lep2Pt"));
  TH1F* h_numerMuPt = (TH1F*)(f_numer->Get("mm_lep2Pt"));
  TH1F* h_denomMuPt = (TH1F*)(f_denom->Get("mm_lep2Pt"));

  TH1F* h_elEffPt = (TH1F*)(h_numerElPt->Clone("h_elEff"));
  TH1F* h_muEffPt = (TH1F*)(h_numerMuPt->Clone("h_muEff"));
  h_elEffPt->Reset();
  h_muEffPt->Reset();

  h_elEffPt->GetXaxis()->SetTitle("Electron P_{T} [GeV]");
  h_elEffPt->GetYaxis()->SetTitle("Efficiency(L#rightarrowT)");
  h_muEffPt->GetXaxis()->SetTitle("Muon P_{T} [GeV]");
  h_muEffPt->GetYaxis()->SetTitle("Efficiency(L#rightarrowT)");

  h_elEffPt->Divide(h_numerElPt,h_denomElPt,1.,1.,"b");
  h_muEffPt->Divide(h_numerMuPt,h_denomMuPt,1.,1.,"b");

  //Msfos distributions
  TH1F* h_beforeSelecElMsfos = (TH1F*)(f_beforeSelec->Get("ee_msfos"));
  TH1F* h_beforeSelecMuMsfos = (TH1F*)(f_beforeSelec->Get("mm_msfos"));
  TH1F* h_numerElMsfos = (TH1F*)(f_numer->Get("ee_msfos"));
  TH1F* h_denomElMsfos = (TH1F*)(f_denom->Get("ee_msfos"));
  TH1F* h_numerMuMsfos = (TH1F*)(f_numer->Get("mm_msfos"));
  TH1F* h_denomMuMsfos = (TH1F*)(f_denom->Get("mm_msfos"));

  h_beforeSelecElMsfos->GetXaxis()->SetRangeUser(0.,20.);
  h_beforeSelecMuMsfos->GetXaxis()->SetRangeUser(0.,20.);
  h_numerElMsfos->GetXaxis()->SetRangeUser(0.,20.);
  h_denomElMsfos->GetXaxis()->SetRangeUser(0.,20.);
  h_numerMuMsfos->GetXaxis()->SetRangeUser(0.,20.);
  h_denomMuMsfos->GetXaxis()->SetRangeUser(0.,20.);

  h_numerElMsfos->SetLineColor(kRed);
  h_denomElMsfos->SetLineColor(kBlack);
  h_numerMuMsfos->SetLineColor(kRed);
  h_denomMuMsfos->SetLineColor(kBlack);

  //Drawing histograms
  TUtil* u = new TUtil("result.ps","result.root",600,800);

  u->SetPadNumXY(2,3);
  u->Draw(h_numerElPt);
  u->Draw(h_numerMuPt);
  u->Draw(h_denomElPt);
  u->Draw(h_denomMuPt);

  h_elEffPt->GetYaxis()->SetRangeUser(0.,1.1);
  h_muEffPt->GetYaxis()->SetRangeUser(0.,1.1);
  u->Draw(h_elEffPt);
  u->Draw(h_muEffPt);

  u->Update();
  u->Draw(h_beforeSelecElMsfos);
  u->Draw(h_beforeSelecMuMsfos);
  u->Draw(h_denomElMsfos);
  u->Draw(h_numerElMsfos,"same");
  u->Draw(h_denomMuMsfos);
  u->Draw(h_numerMuMsfos,"same");

  delete u;
  delete f_numer;
  delete f_denom;

  return 0;
}
