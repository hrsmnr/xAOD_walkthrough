#include<iostream>
#include<vector>
#include<string>

#include"TFile.h"
#include"TString.h"
#include"THStack.h"
#include"TLegend.h"

#include"TUtil.cc"
#include"AtlasUtils.cc"

//enum DistType{met,nJet,nDistType};
//TString DistTypeNames[nDistType] = {"met","nJet"};
enum DistType{
  //  all,
  lep1Pt,
  lep2Pt,
  lep3Pt,
  el1Pt,
  el2Pt,
  el3Pt,
  mu1Pt,
  mu2Pt,
  mu3Pt,
  lep1Eta,
  lep2Eta,
  lep3Eta,
  //  sumLepPt,
  //  sumLepPtMet,
  //  dPhiWZ,
  //  nMuComb,
  // elPtcone30,
  // elEtcone30,
  // muPtcone30,
  // muEtcone30,
  // lepD0,
  // lep1D0,
  // lep2D0,
  // lep3D0,
  // lepZ0,
  // lep1Z0,
  // lep2Z0,
  // lep3Z0,
  // lepClass,
  // lep1Class,
  // lep2Class,
  // lep3Class,
  // hasSS,
  // nTau,
  // tauPt,
  // tau1Pt,
  // tau2Pt,
  // tau1Eta,
  // tau2Eta,
  // dPhiTauTau,
  // tauProng,
  // tauClass,
  // tau1Class,
  // tau2Class,
  // minDRLepLep,
  // dPhiLep1Met,
  // dPhiLep2Met,
  // dPhiLep3Met,
  // dPhiLLMet,
  // dPhiJet1Met,
  // dPhiJet2Met,
  // dPhiJJMet,
  // minDPhiLepLep,
  // minDPhiLepMet,
  // minDPhiJetJet,
  // minDPhiJetMet,
  // minDPhiTauMet,
  // minDRLepJet,
  // maxDPhiLepLep,
  // maxDPhiLepMet,
  // maxDPhiJetJet,
  // maxDPhiJetMet,
  // maxDRLepJet,
  // dEtaLL,
  // dEtaJetJet,
  // maxDEtaJetJet,
  // minDEtaJetJet,
  // msfos,
  // msfss,
  // mlll,
  // mtFine,
  // mtCoarse,
  // mtLow,
  // mt2Max,
  // mt2MaxFine,
  // meff,
  // meffNoMet,
  // mjj,
  // mlljj,
  // mlt,
  // mtt,
  // mbb,
  // mljj,
  // mljjFine,
  // mtll,
  // met,
  // metLow,
  // metMid,
  // metHigh,
  // metEle,
  // metMuo,
  // metJet,
  // metCell,
  // metRel,
  // nJet,
  // nBJet,
  // jet1Pt,
  // jet2Pt,
  // jet3Pt,
  // jetPt,
  // bJetPt,
  // bJet1Pt,
  // bJet2Pt,
  // bJet3Pt,
  // jetEta,
  // bJetEta,
  // bJet1Eta,
  // bJet2Eta,
  // bJet3Eta,
  // jetPhi,
  // jetMV1,
  // jetJVF,
  // bJetJVF,
  // jetDPhi,
  // jetDEta,
  // dijetM,
  // productEta1Eta2,
  // nVtx,
  // mu,
  nDistType
};
TString DistTypeNames[nDistType] = {
  // "all",
  "lep1Pt",
  "lep2Pt",
  "lep3Pt",
  "el1Pt",
  "el2Pt",
  "el3Pt",
  "mu1Pt",
  "mu2Pt",
  "mu3Pt",
  "lep1Eta",
  "lep2Eta",
  "lep3Eta" //Attention, no comma at end.
  // "sumLepPt",
  // "sumLepPtMet",
  // "dPhiWZ",
  // "nMuComb",
  // "elPtcone30",
  // "elEtcone30",
  // "muPtcone30",
  // "muEtcone30",
  // "lepD0",
  // "lep1D0",
  // "lep2D0",
  // "lep3D0",
  // "lepZ0",
  // "lep1Z0",
  // "lep2Z0",
  // "lep3Z0",
  // "lepClass",
  // "lep1Class",
  // "lep2Class",
  // "lep3Class",
  // "hasSS",
  // "nTau",
  // "tauPt",
  // "tau1Pt",
  // "tau2Pt",
  // "tau1Eta",
  // "tau2Eta",
  // "dPhiTauTau",
  // "tauProng",
  // "tauClass",
  // "tau1Class",
  // "tau2Class",
  // "minDRLepLep",
  // "dPhiLep1Met",
  // "dPhiLep2Met",
  // "dPhiLep3Met",
  // "dPhiLLMet",
  // "dPhiJet1Met",
  // "dPhiJet2Met",
  // "dPhiJJMet",
  // "minDPhiLepLep",
  // "minDPhiLepMet",
  // "minDPhiJetJet",
  // "minDPhiJetMet",
  // "minDPhiTauMet",
  // "minDRLepJet",
  // "maxDPhiLepLep",
  // "maxDPhiLepMet",
  // "maxDPhiJetJet",
  // "maxDPhiJetMet",
  // "maxDRLepJet",
  // "dEtaLL",
  // "dEtaJetJet",
  // "maxDEtaJetJet",
  // "minDEtaJetJet",
  // "msfos",
  // "msfss",
  // "mlll",
  // "mtFine",
  // "mtCoarse",
  // "mtLow",
  // "mt2Max",
  // "mt2MaxFine",
  // "meff",
  // "meffNoMet",
  // "mjj",
  // "mlljj",
  // "mlt",
  // "mtt",
  // "mbb",
  // "mljj",
  // "mljjFine",
  // "mtll",
  // "met",
  // "metLow",
  // "metMid",
  // "metHigh",
  // "metEle",
  // "metMuo",
  // "metJet",
  // "metCell",
  // "metRel",
  // "nJet",
  // "nBJet",
  // "jet1Pt",
  // "jet2Pt",
  // "jet3Pt",
  // "jetPt",
  // "bJetPt",
  // "bJet1Pt",
  // "bJet2Pt",
  // "bJet3Pt",
  // "jetEta",
  // "bJetEta",
  // "bJet1Eta",
  // "bJet2Eta",
  // "bJet3Eta",
  // "jetPhi",
  // "jetMV1",
  // "jetJVF",
  // "bJetJVF",
  // "jetDPhi",
  // "jetDEta",
  // "dijetM",
  // "productEta1Eta2",
  // "nVtx",
  // "mu"
};

enum FSType{allchan,eee,eem,emm,mmm,nFSType};
TString FSTypeNames[nFSType] = {"all","eee","eem","emm","mmm"};

/////////////////////////////////////////////////////////////////
enum SignalType{
  SmplViaWZ,
  nSignalType};
TString SignalTypeNames[nSignalType] = {"SmplViaWZ"};
enum SimplifiedModelType{
  SmplViaWZ_1 , SmplViaWZ_2 , SmplViaWZ_3 , SmplViaWZ_4 , SmplViaWZ_5 ,
  SmplViaWZ_6 , SmplViaWZ_7 , SmplViaWZ_8 , SmplViaWZ_9 , nSimplifiedModelType};
Int_t SmplViaWZHistColors[nSimplifiedModelType] = {kAzure,kAzure-1,kAzure-2,kAzure-3,kAzure-4,
                                                   kCyan-2,kCyan-3,kCyan-4,kCyan-5};
Int_t SmplViaWZLineStyle [nSimplifiedModelType] = {kDotted,kDotted,kDotted,kDotted,kDotted,
                                                   kDotted,kDotted,kDotted,kDotted};
std::vector<TString> *SignalFileNames[nSignalType];
std::vector<Int_t> *DrawnSignalType;
std::vector<Int_t> *DrawnSignalFile;
std::vector<Int_t> *DrawnSignalColor;
std::vector<Int_t> *DrawnSignalStyle;

void SetSignalType(void){
  DrawnSignalType  = new std::vector<Int_t>();
  DrawnSignalFile  = new std::vector<Int_t>();
  DrawnSignalColor = new std::vector<Int_t>();
  DrawnSignalStyle = new std::vector<Int_t>();
  //Signal reference sample #1
  DrawnSignalType->push_back(SmplViaWZ);
  DrawnSignalFile->push_back(SmplViaWZ_1);
  DrawnSignalColor->push_back(kRed);
  DrawnSignalStyle->push_back(kDotted);
  //Signal reference sample #2
  DrawnSignalType->push_back(SmplViaWZ);
  DrawnSignalFile->push_back(SmplViaWZ_5);
  DrawnSignalColor->push_back(kBlue);
  DrawnSignalStyle->push_back(kDashDotted); //kDashDotted, kDashed

  for(Int_t signaltype=0; signaltype<nSignalType; signaltype++){
    SignalFileNames[signaltype] = new std::vector<TString>();
  }
  //Do not change the push_back order!!
  //Simplified Model with WZ
  SignalFileNames[SmplViaWZ]->push_back("205048");
  SignalFileNames[SmplViaWZ]->push_back("205049");
  SignalFileNames[SmplViaWZ]->push_back("205050");
  SignalFileNames[SmplViaWZ]->push_back("205051");
  SignalFileNames[SmplViaWZ]->push_back("205052");
  SignalFileNames[SmplViaWZ]->push_back("205053");
  SignalFileNames[SmplViaWZ]->push_back("205054");
  SignalFileNames[SmplViaWZ]->push_back("205055");
  SignalFileNames[SmplViaWZ]->push_back("205056");

}


/////////////////////////////////////////////////////////////////////////////////////////
enum DataType{periodA,nDataType};
TString DataTypeNames[nDataType] = {"periodA"};

std::vector<TString> *DataFileNames;
void SetDataType(void){
  DataFileNames = new std::vector<TString>();
  for(Int_t dataType=0; dataType<nDataType; dataType++){
    DataFileNames->push_back(DataTypeNames[dataType]);
  }
}


/////////////////////////////////////////////////////////////////////////////////////////
enum BGType{WZ,nBGType};
TString BGTypeNames[nBGType] = {"WZ"};
Int_t BGTypeHistColors[nBGType] = {kAzure-3};
Int_t BGTypeFillColors[nBGType] = {kAzure-3};
Int_t BGStackOrder1[nBGType] = {WZ};
Int_t BGStackOrder2[nBGType] = {WZ};
// enum BGType{WZ,ttbar,nBGType};
// TString BGTypeNames[nBGType] = {"WZ","ttbar"};
// Int_t BGTypeHistColors[nBGType] = {kAzure-3,kCyan-2};
// Int_t BGTypeFillColors[nBGType] = {kAzure-3,kCyan-2};
// Int_t BGStackOrder1[nBGType] = {WZ,ttbar};
// Int_t BGStackOrder2[nBGType] = {ttbar,WZ};
// enum BGType{WZ,ZZ,ttW,ttZ,tPlusVs,Tribosons,Higgs,Zjets,Wjets,ttbar,OtherFake,nBGType};
// TString BGTypeNames[nBGType] = {"WZ","ZZ","ttW","ttZ","tPlusVs","Tribosons","Higgs","Zjets","Wjets","ttbar","OtherFake"};
// Int_t BGTypeHistColors[nBGType] = {kAzure-3,kAzure-4,kCyan-2,kCyan-1,kCyan,kMagenta,kBlack,kViolet-7,kViolet-9,kOrange-2,kGreen+2};
// Int_t BGTypeFillColors[nBGType] = {kAzure-3,kAzure-4,kCyan-2,kCyan-1,kCyan,kMagenta,kWhite,kViolet-7,kViolet-9,kOrange-2,kGreen+2};
// Int_t BGStackOrder1[nBGType] = {WZ,ZZ,ttW,ttZ,tPlusVs,Tribosons,Higgs,Zjets,Wjets,ttbar,OtherFake};
// Int_t BGStackOrder2[nBGType] = {OtherFake,ttbar,Wjets,Zjets,Higgs,Tribosons,tPlusVs,ttZ,ttW,ZZ,WZ};

//enum WZFiles{WZpeee,WZpemm,WZpett,WZpmee,WZpmmm,WZpmtt,WZptee,WZptmm,WZpttt,
//	     WZneee,WZnemm,WZnett,WZnmee,WZnmmm,WZnmtt,WZntee,WZntmm,WZnttt,nWZFiles};
std::vector<TString> *BGFileNames  [nBGType];
std::vector<TString> *BGIncludeFlag[nBGType]; //e.g. "00110" means the sample is included to the "eem" and "emm" channels.

void SetBGType(void){
  for(Int_t bgtype=0; bgtype<nBGType; bgtype++){
    BGFileNames  [bgtype] = new std::vector<TString>();
    BGIncludeFlag[bgtype] = new std::vector<TString>();
  }

  //WZ files
  BGFileNames[WZ]->push_back("187160"); BGIncludeFlag[WZ]->push_back("01000");
  BGFileNames[WZ]->push_back("187161"); BGIncludeFlag[WZ]->push_back("00010");
  // BGFileNames[WZ]->push_back("187162"); BGIncludeFlag[WZ]->push_back("01110");
  // BGFileNames[WZ]->push_back("187163"); BGIncludeFlag[WZ]->push_back("00100");
  // BGFileNames[WZ]->push_back("187164"); BGIncludeFlag[WZ]->push_back("00001");
  // BGFileNames[WZ]->push_back("187165"); BGIncludeFlag[WZ]->push_back("00111");
  // BGFileNames[WZ]->push_back("187166"); BGIncludeFlag[WZ]->push_back("01100");
  // BGFileNames[WZ]->push_back("187167"); BGIncludeFlag[WZ]->push_back("00011");
  // BGFileNames[WZ]->push_back("187168"); BGIncludeFlag[WZ]->push_back("01111");
  // BGFileNames[WZ]->push_back("187170"); BGIncludeFlag[WZ]->push_back("01000");
  // BGFileNames[WZ]->push_back("187171"); BGIncludeFlag[WZ]->push_back("00010");
  // BGFileNames[WZ]->push_back("187172"); BGIncludeFlag[WZ]->push_back("01110");
  // BGFileNames[WZ]->push_back("187173"); BGIncludeFlag[WZ]->push_back("00100");
  // BGFileNames[WZ]->push_back("187174"); BGIncludeFlag[WZ]->push_back("00001");
  // BGFileNames[WZ]->push_back("187175"); BGIncludeFlag[WZ]->push_back("00111");
  // BGFileNames[WZ]->push_back("187176"); BGIncludeFlag[WZ]->push_back("01100");
  // BGFileNames[WZ]->push_back("187177"); BGIncludeFlag[WZ]->push_back("00011");
  // BGFileNames[WZ]->push_back("187178"); BGIncludeFlag[WZ]->push_back("01111");

  //ttbar
  //  BGFileNames[ttbar]->push_back("110401"); BGIncludeFlag[ttbar]->push_back("01111");//no all-had

}

TString getHistFileName(std::string path){
  TString strFileName = gSystem->GetFromPipe(("ls "+path+"hist*.root").c_str());
  //  std::cout << "-- result" << std::endl;
  //  std::cout << strFileName.Data() << std::endl;
  if(strFileName==""){
    std::cout<<"Cannnot find output histogram in "<<path.c_str()<<std::endl;
    exit(1);
  }
  return strFileName;
}

Int_t mkPlots(TString SelecReg){

  std::cout<<"Making plots for the region \""<<SelecReg.Data()<<"\"."<<std::endl;

  std::vector<TFile*> *vec_datafiles   = new std::vector<TFile*>();
  std::vector<TFile*> *vec_mcfiles     = new std::vector<TFile*>();
  std::vector<TFile*> *vec_signalfiles = new std::vector<TFile*>();
  vec_datafiles  ->clear();
  vec_mcfiles    ->clear();
  vec_signalfiles->clear();

  SetDataType();
  SetBGType();
  SetSignalType();

  TString filepath_prefix = "$ROOTCOREBIN/../result/";

  // //DataFiles
  // for(Int_t datatype=0; datatype<nDataType; datatype++){
  //   std::cout<<"Now processing for the real data : "<<DataTypeNames[datatype].Data()<<std::endl;
  //   TString dsid = DataFileNames->at(datatype).Data();
  //   TString filename = filepath_prefix+dsid+"."+SelecReg+".AnaHists.root";
  //   TFile *f_tmp = new TFile(filename.Data());
  //   f_tmp->cd("nom");
  //   vec_datafiles->push_back(f_tmp);
  //   std::cout<<"**** DatasetID : "<<dsid.Data()<<", filename="<<filename.Data()<<std::endl;
  // }

  //Background Files
  for(Int_t bgtype=0; bgtype<nBGType; bgtype++){
    UInt_t nsamples = BGFileNames[bgtype]->size();
    std::cout<<"Now processing for the background : "<<BGTypeNames[bgtype].Data()<<" ("<<nsamples<<" files)"<<std::endl;
    for(UInt_t bgfile=0; bgfile<nsamples; bgfile++){
      TString dsid = BGFileNames[bgtype]->at(bgfile).Data();
      TString includeflag = BGIncludeFlag[bgtype]->at(bgfile).Data();
      //      TString filename = filepath_prefix+dsid+"_00/"+SelecReg+".AnaHists.root";
      TString filename = getHistFileName((filepath_prefix+dsid+"_00/").Data());
      TFile *f_tmp = new TFile(filename.Data());
      vec_mcfiles->push_back(f_tmp);
      std::cout<<"**** DatasetID : "<<dsid.Data()<<", filename="<<filename.Data()<<", IncludeFlag="<<includeflag.Data()<<std::endl;
    }
  }

  //Signal Files
  for(Int_t signaltype=0; signaltype<nSignalType; signaltype++){
    UInt_t nsamples = SignalFileNames[signaltype]->size();
    std::cout<<"Now processing for the signal : "<<SignalTypeNames[signaltype].Data()<<" ("<<nsamples<<" files)"<<std::endl;
    for(UInt_t signalfile=0; signalfile<nsamples; signalfile++){
      TString dsid = SignalFileNames[signaltype]->at(signalfile).Data();
      //      TString filename = filepath_prefix+dsid+"."+SelecReg+".AnaHists.root";
      TString filename = getHistFileName((filepath_prefix+dsid+"_00/").Data());
      TFile *f_tmp = new TFile(filename.Data());
      vec_signalfiles->push_back(f_tmp);
      std::cout<<"**** DatasetID : "<<dsid.Data()<<", filename="<<filename.Data()<<std::endl;
    }
  }

  ////////////////////////////////////////////////////
  //Defining histograms
  ////////////////////////////////////////////////////
  //counting the number of signal samples
  //  TH1::SetDefaultSumw2(); //No need to call this for ROOT6
  TH1F* dist_data[nFSType][nDistType];
  TH1F* dist_bg[nFSType][nBGType][nDistType];
  TH1F* dist_totalbg[nFSType][nDistType];
  TH1F* dist_totalbgErr[nFSType][nDistType];
  TH1F* dist_ratio[nFSType][nDistType];
  TH1F* dist_ratioErr[nFSType][nDistType];
  std::vector<TH1F*> *vec_dist_signal[nFSType][nSignalType][nDistType];
  //  std::cout<<vec_mcfiles->at(0)->GetName()<<std::endl;
  for(Int_t fstype=0; fstype<nFSType; fstype++){
    for(Int_t disttype=0; disttype<nDistType; disttype++){
      std::string distname = DistTypeNames[disttype].Data();
      TFile *f_tmp = vec_signalfiles->at(0);
      TH1F *h_tmp = (TH1F*)(f_tmp->Get(Form("all_%s;1",distname.c_str())));
      //     //Real data
      //     std::cout<<"Preparing final histogram of data for "<<FSTypeNames[fstype]<<" based on "<<Form("all_%s;1",distname.c_str())<<"."<<std::endl;
      //     dist_data[fstype][disttype] = (TH1F*)(h_tmp->Clone(Form("dist_data_%d_%d",fstype,disttype)));
      //     dist_data[fstype][disttype]->Reset();
      //Total BG
      std::cout<<"Preparing final histogram of total BG for "<<FSTypeNames[fstype]<<" based on "<<Form("all_%s;1",distname.c_str())<<"."<<std::endl;
      dist_totalbg[fstype][disttype] = (TH1F*)(h_tmp->Clone(Form("dist_totalbg_%d_%d",fstype,disttype)));
      dist_totalbg[fstype][disttype]->Reset();
      //     //Ratio plot
      //     std::cout<<"Preparing final histogram of Data/SM ratio and its error for "<<FSTypeNames[fstype]<<" based on "<<Form("all_%s;1",distname.c_str())<<"."<<std::endl;
      //     dist_ratio[fstype][disttype] = (TH1F*)(h_tmp->Clone(Form("dist_ratio_%d_%d",fstype,disttype)));
      //     dist_ratio[fstype][disttype]->Reset();
      //     dist_ratioErr[fstype][disttype] = (TH1F*)(h_tmp->Clone(Form("dist_ratioErr_%d_%d",fstype,disttype)));
      //     dist_ratioErr[fstype][disttype]->Reset();
      //Backgrounds
      for(Int_t bgtype=0; bgtype<nBGType; bgtype++){
        std::cout<<"Preparing final histogram of "<<BGTypeNames[bgtype]<<" for "<<FSTypeNames[fstype]<<" based on "<<Form("all_%s;1",distname.c_str())<<"."<<std::endl;
        dist_bg[fstype][bgtype][disttype] = (TH1F*)(h_tmp->Clone(Form("dist_bg_%d_%d_%d",fstype,bgtype,disttype)));
        dist_bg[fstype][bgtype][disttype]->Reset();
      }
      //Signal sample
      for(Int_t signaltype=0; signaltype<nSignalType; signaltype++){
        vec_dist_signal[fstype][signaltype][disttype] = new std::vector<TH1F*>();
        std::cout<<"Preparing histograms of "<<SignalTypeNames[signaltype]<<" for "<<FSTypeNames[fstype]<<" based on "<<Form("all_%s;1",distname.c_str())<<"."<<std::endl;
        for(UInt_t signalfile=0; signalfile<SignalFileNames[signaltype]->size(); signalfile++){
          vec_dist_signal[fstype][signaltype][disttype]->push_back((TH1F*)(h_tmp->Clone(Form("dist_signal_%d_%d_%d",fstype,signaltype,disttype))));
          vec_dist_signal[fstype][signaltype][disttype]->at(signalfile)->Reset();
        }
      }
    }
  }

  // //Adding histograms of data for eee,eem,emm,mmm.
  // for(UInt_t datafile=0; datafile<nDataType; datafile++){
  //   for(Int_t fstype=0; fstype<nFSType; fstype++){
  //     std::string fsname = FSTypeNames[fstype].Data();
  //     std::cout<<"Adding histograms in "<<DataFileNames->at(datafile)<<" to "<<FSTypeNames[fstype]<<" histograms..."<<std::endl;
  //     for(Int_t disttype=0; disttype<nDistType; disttype++){
	// //Getting the histogram to add.
	// std::string distname = DistTypeNames[disttype].Data();
	// std::string histname = Form("%s_%s;1",fsname.c_str(),distname.c_str());
	// TFile *f_tmp = vec_datafiles->at(datafile);
	// TH1F *h_tmp = (TH1F*)(f_tmp->Get(histname.c_str()));
	// dist_data[fstype][disttype]->Add(h_tmp);
	// dist_data[fstype][disttype]->SetTitle(FSTypeNames[fstype]+":Data");
	// dist_data[fstype][disttype]->SetMarkerStyle(kFullCircle);
	// dist_data[fstype][disttype]->SetMarkerSize(1.2);
	// std::cout<<"#Entries : "<<h_tmp->GetName()<<" : "<<h_tmp->GetEntries()<<std::endl;
  //     }
  //   }
  // }

  // //Adding histograms of BG for eee,eem,emm,mmm.
  UInt_t fileidx=0;
  for(Int_t bgtype=0; bgtype<nBGType; bgtype++){
    UInt_t nsamples = BGFileNames[bgtype]->size();
    for(UInt_t bgfile=0; bgfile<nsamples; bgfile++){
      for(Int_t fstype=0; fstype<nFSType; fstype++){
        std::string fsname = FSTypeNames[fstype].Data();
        TString includeflag = BGIncludeFlag[bgtype]->at(bgfile);
        TString inclFlag4fs = includeflag[fstype];
        std::cout<<"FileIndex:"<<fileidx<<", DSID="<<BGFileNames[bgtype]->at(bgfile)<<std::endl;
        if(inclFlag4fs=="0") continue;
        else{
          std::cout<<"Adding histograms in "<<BGFileNames[bgtype]->at(bgfile)<<" to "<<FSTypeNames[fstype]<<" histograms..."<<std::endl;
          for(Int_t disttype=0; disttype<nDistType; disttype++){
            //Getting the histogram to add.
            std::string distname = DistTypeNames[disttype].Data();
            std::string histname = Form("%s_%s;1",fsname.c_str(),distname.c_str());
            TFile *f_tmp = vec_mcfiles->at(fileidx);
            TH1F *h_tmp = (TH1F*)(f_tmp->Get(histname.c_str()));
            if(h_tmp->Integral()<0.){
              std::cout<<"FileIdx : "<<fileidx<<", "<<h_tmp->Integral()<<std::endl;
              getchar();
            }
            dist_bg[fstype][bgtype][disttype]->Add(h_tmp);
            dist_bg[fstype][bgtype][disttype]->SetTitle(FSTypeNames[fstype]+":"+BGTypeNames[bgtype]);
            dist_bg[fstype][bgtype][disttype]->SetMarkerColor(BGTypeHistColors[bgtype]);
            dist_bg[fstype][bgtype][disttype]->SetFillColor(BGTypeFillColors[bgtype]);
            dist_bg[fstype][bgtype][disttype]->SetLineColor(BGTypeFillColors[bgtype]);
            std::cout<<"#Entries : "<<h_tmp->GetName()<<" : "<<h_tmp->GetEntries()<<std::endl;
          }
        }
      }
      fileidx++;
    }
  }

  //Adding histograms of Signal for eee,eem,emm,mmm.
  fileidx=0;
  for(Int_t signaltype=0; signaltype<nSignalType; signaltype++){
    UInt_t nsamples = SignalFileNames[signaltype]->size();
    for(UInt_t signalfile=0; signalfile<nsamples; signalfile++){
      for(Int_t fstype=0; fstype<nFSType; fstype++){
        std::string fsname = FSTypeNames[fstype].Data();
        std::cout<<"Adding histograms in "<<SignalFileNames[signaltype]->at(signalfile)<<" to "<<FSTypeNames[fstype]<<" histograms..."<<std::endl;
        for(Int_t disttype=0; disttype<nDistType; disttype++){
          //Getting the histogram to add.
          std::string distname = DistTypeNames[disttype].Data();
          std::string histname = Form("%s_%s;1",fsname.c_str(),distname.c_str());
          TFile *f_tmp = vec_signalfiles->at(fileidx);
          TH1F *h_tmp = (TH1F*)(f_tmp->Get(histname.c_str()));
          vec_dist_signal[fstype][signaltype][disttype]->at(signalfile)->Add(h_tmp);
          vec_dist_signal[fstype][signaltype][disttype]->at(signalfile)->SetTitle(FSTypeNames[fstype]+":"+SignalTypeNames[signaltype]);
          Int_t color = kBlack;
          Int_t style = kSolid;
          if(SignalTypeNames[signaltype]=="SmplViaWZ"){
            color = SmplViaWZHistColors[signalfile];
            style = SmplViaWZLineStyle [signalfile];
          }
          vec_dist_signal[fstype][signaltype][disttype]->at(signalfile)->SetMarkerColor(color);
          vec_dist_signal[fstype][signaltype][disttype]->at(signalfile)->SetLineColor(color);
          vec_dist_signal[fstype][signaltype][disttype]->at(signalfile)->SetLineStyle(style);
          std::cout<<"#Entries : "<<h_tmp->GetName()<<" : "<<h_tmp->GetEntries()<<std::endl;
        }
      }
      fileidx++;
    }
  }

  //Making histograms for all channels (eee,eem,emm,mmm).
  for(Int_t disttype=0; disttype<nDistType; disttype++){
    for(Int_t bgtype=0; bgtype<nBGType; bgtype++){
      dist_bg[allchan][bgtype][disttype]->Add(dist_bg[eee][bgtype][disttype]);
      dist_bg[allchan][bgtype][disttype]->Add(dist_bg[eem][bgtype][disttype]);
      dist_bg[allchan][bgtype][disttype]->Add(dist_bg[emm][bgtype][disttype]);
      dist_bg[allchan][bgtype][disttype]->Add(dist_bg[mmm][bgtype][disttype]);
      dist_bg[allchan][bgtype][disttype]->SetTitle(FSTypeNames[allchan]+":"+BGTypeNames[bgtype]);
      dist_bg[allchan][bgtype][disttype]->SetMarkerColor(BGTypeHistColors[bgtype]);
      dist_bg[allchan][bgtype][disttype]->SetLineColor(BGTypeFillColors[bgtype]);
      dist_bg[allchan][bgtype][disttype]->SetFillColor(BGTypeFillColors[bgtype]);
    }
  }

  //Making plots for total BG
  THStack *hs_bg[nFSType][nDistType];
  for(Int_t fstype=0; fstype<nFSType; fstype++){
    for(Int_t disttype=0; disttype<nDistType; disttype++){
      //for the shape
      for(Int_t bgtype=0; bgtype<nBGType; bgtype++){
        dist_totalbg[fstype][disttype]->Add(dist_bg[fstype][bgtype][disttype]);
      }
      dist_totalbg[fstype][disttype]->SetTitle(FSTypeNames[fstype]+":Total");
      dist_totalbg[fstype][disttype]->SetLineColor(kRed);
      //for the error band
      dist_totalbgErr[fstype][disttype] = (TH1F*)dist_totalbg[fstype][disttype]->Clone(Form("dist_totalbgErr_%d_%d",fstype,disttype));
      dist_totalbgErr[fstype][disttype]->SetTitle(FSTypeNames[fstype]+":Total");
      dist_totalbgErr[fstype][disttype]->SetLineColor(kBlack);
      dist_totalbgErr[fstype][disttype]->SetFillColor(kGray+3);
      dist_totalbgErr[fstype][disttype]->SetMarkerStyle(0);
      dist_totalbgErr[fstype][disttype]->SetFillStyle(3454);
      //Creating SM stuck histogram
      std::string distname = DistTypeNames[disttype].Data();
      std::cout<<"Preparing THStack for "<<FSTypeNames[fstype]<<" based on "<<Form("all_%s;1",distname.c_str())<<"."<<std::endl;
      hs_bg[fstype][disttype] = new THStack(Form("hs_bg_%d_%d",fstype,disttype),FSTypeNames[fstype]+":Total");
      for(Int_t bgtype=0; bgtype<nBGType; bgtype++){
        std::cout<<"Adding "<<BGTypeNames[BGStackOrder2[bgtype]]<<" to THStack..."<<std::endl;
        hs_bg[fstype][disttype]->Add(dist_bg[fstype][BGStackOrder2[bgtype]][disttype]);
        //	std::cout<<"Adding "<<BGTypeNames[bgtype]<<" to THStack..."<<std::endl;
        //	hs_bg[fstype][disttype]->Add(dist_bg[fstype][bgtype][disttype]);
      }
    }
  }

  // //Making plots for Data/MC ratio
  // for(Int_t fstype=0; fstype<nFSType; fstype++){
  //   for(Int_t disttype=0; disttype<nDistType; disttype++){
  //     dist_ratio[fstype][disttype]->SetTitle(FSTypeNames[fstype]+":Total");
  //     dist_ratio[fstype][disttype]->GetYaxis()->SetTitle("Data/SM");
  //     dist_ratio[fstype][disttype]->SetLineColor(kBlack);
  //     dist_ratio[fstype][disttype]->SetMarkerColor(kBlack);
  //     dist_ratio[fstype][disttype]->SetMarkerStyle(kFullCircle);
  //     dist_ratio[fstype][disttype]->SetMarkerSize(1.2);
  //     dist_ratioErr[fstype][disttype]->SetTitle(FSTypeNames[fstype]+":Total");
  //     dist_ratioErr[fstype][disttype]->GetYaxis()->SetTitle("Data/SM");
  //     dist_ratioErr[fstype][disttype]->SetLineColor(kBlack);
  //     dist_ratioErr[fstype][disttype]->SetFillColor(kGray+3);
  //     dist_ratioErr[fstype][disttype]->SetMarkerStyle(0);
  //     dist_ratioErr[fstype][disttype]->SetFillStyle(3454);

  //     Int_t nbins = dist_ratioErr[fstype][disttype]->GetNbinsX();
  //     for(Int_t bin=0; bin<nbins; bin++){
	// Double_t dataCont = dist_data   [fstype][disttype]->GetBinContent(bin+1);
	// Double_t bgCont   = dist_totalbg[fstype][disttype]->GetBinContent(bin+1);
	// Double_t dataErr  = dist_data   [fstype][disttype]->GetBinError(bin+1);
	// Double_t bgErr    = dist_totalbg[fstype][disttype]->GetBinError(bin+1);
	// Double_t ratioData    = bgCont!=0.?dataCont/bgCont:0.;
	// Double_t ratioDataErr = bgCont!=0.?dataErr/bgCont:0.;
	// Double_t ratioMC      = 1.;
	// //	Double_t ratioMCErr   = bgCont!=0.?bgErr*dataCont/bgCont/bgCont:0.;
	// Double_t ratioMCErr   = bgCont!=0.?bgErr/bgCont:0.;
	// dist_ratio[fstype][disttype]->SetBinContent(bin+1,ratioData);
	// dist_ratio[fstype][disttype]->SetBinError(bin+1,ratioDataErr);
	// dist_ratioErr[fstype][disttype]->SetBinContent(bin+1,ratioMC);
	// dist_ratioErr[fstype][disttype]->SetBinError(bin+1,ratioMCErr);
  //     }

  //   }
  // }

  //Preparing the legend
  TLegend *leg = new TLegend(0.1,0.1,0.9,0.9);
  leg->SetNColumns(1);
  leg->SetFillColor(0);
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);
  leg->SetTextFont(72);
  leg->SetTextSize(0.05);
  // leg->AddEntry(dist_data[0][0],"Data","lp");
  leg->AddEntry(dist_bg[0][WZ][0],"WZ","f");
  // leg->AddEntry(dist_bg[0][ZZ][0],"ZZ","f");
  // leg->AddEntry(dist_bg[0][ttW][0],"t#bar{t}W","f");
  // leg->AddEntry(dist_bg[0][ttZ][0],"t#bar{t}Z","f");
  // leg->AddEntry(dist_bg[0][Tribosons][0],"Tribosons","f");
  // //For Higgs histograms, special treatment is needed to make it visible.
  // TH1F* h_higgs4leg = (TH1F*)dist_bg[0][Higgs][0]->Clone("h_higgs4leg");
  // h_higgs4leg->SetLineColor(kBlack);
  // leg->AddEntry(h_higgs4leg,"Higgs","f");
  // leg->AddEntry(dist_bg[0][Zjets][0],"Z/#gamma^{*}+jets","f");
  // leg->AddEntry(dist_bg[0][Wjets][0],"W+jets","f");
  // leg->AddEntry(dist_bg[0][ttbar][0],"t#bar{t}","f");
  // leg->AddEntry(dist_bg[0][OtherFake][0],"Other BG with fakes","f");
  // leg->AddEntry(dist_totalbg[0][0],"Total SM","l");
  // leg->AddEntry(dist_totalbgErr[0][0],"Unct. for SM ","f");


  ////////////////////////////////////////////////////
  // histograms definition end.
  ////////////////////////////////////////////////////

  Bool_t debugPlot = kTRUE;
  TUtil *u = new TUtil(("plots/"+SelecReg+".ps").Data(),("plots/"+SelecReg+".root").Data(),debugPlot);
  
  // for(Int_t disttype=0; disttype<nDistType; disttype++){
  //   for(Int_t bgtype=0; bgtype<nBGType; bgtype++){
  //     u->Draw(dist_bg[allchan][bgtype][disttype],"E");
  //     u->cdPad();
  //     u->Draw(dist_bg[eee][bgtype][disttype],"E");
  //     u->Draw(dist_bg[eem][bgtype][disttype],"E");
  //     u->Draw(dist_bg[emm][bgtype][disttype],"E");
  //     u->Draw(dist_bg[mmm][bgtype][disttype],"E");
  //   }
  // }

  u->SetPadNumXY(3,4);
  for(Int_t disttype=0; disttype<nDistType; disttype++){
    u->cdPad();
    for(Int_t bgtype=0; bgtype<nBGType; bgtype++){
      dist_bg[allchan][bgtype][disttype]->DrawNormalized(bgtype==0?"":"same");
    }
  }

  u->SetPadNumXY(1,3);
  //  u->SetPadNumXY(3,4);
  for(Int_t fstype=0; fstype<nFSType; fstype++){
    for(Int_t disttype=0; disttype<nDistType; disttype++){
      //      u->Draw(dist_totalbgErr[fstype][disttype],"E2",010);
      //      u->Draw(dist_totalbg   [fstype][disttype],"samehist"); //should be drawn after the error histogram.
      //      dist_data[fstype][disttype]->Draw("sameE");
      //      Double_t logMax = TMath::Max(dist_totalbg[fstype][disttype]->GetMaximum(),dist_data[fstype][disttype]->GetMaximum());
      //      Double_t linMax = TMath::Max(dist_totalbg[fstype][disttype]->GetMaximum(),dist_data[fstype][disttype]->GetMaximum());
      Double_t logMax = TMath::Max(dist_totalbg[fstype][disttype]->GetMaximum(),-1.);
      Double_t linMax = TMath::Max(dist_totalbg[fstype][disttype]->GetMaximum(),-1.);
      logMax *= 1.3E0*TMath::Log10(logMax);
      linMax *= 1.3E0;

      Double_t entry = dist_totalbg[fstype][disttype]->GetEntries();
      Double_t integral = dist_totalbg[fstype][disttype]->Integral();
      if(fstype==0 && DistTypeNames[disttype]=="nJet"){
        std::cout<<"*********************************************"<<std::endl;
        std::cout<<"Total BG : "<<integral<<std::endl;
        std::cout<<"*********************************************"<<std::endl;
      }
      if(entry==0.){ //to avoid error in PostScript
        u->Draw(dist_totalbg[fstype][disttype],"hist");
        u->Draw(dist_totalbg[fstype][disttype],"hist",010);
      }else{
        //////////////////////////////////////////////////////////////
        // Linear version
        //////////////////////////////////////////////////////////////
        u->cdPad();
        //should be drawn in this order
        hs_bg[fstype][disttype]->SetMaximum(linMax);
        hs_bg[fstype][disttype]->Draw("hist");
        hs_bg[fstype][disttype]->GetXaxis()->SetTitle(dist_bg[fstype][0][disttype]->GetXaxis()->GetTitle());
        hs_bg[fstype][disttype]->GetYaxis()->SetTitle(dist_bg[fstype][0][disttype]->GetYaxis()->GetTitle());
        u->Draw(dist_totalbg   [fstype][disttype],"samehist"); //should be drawn after the error histogram.
        //	dist_data[fstype][disttype]->Draw("sameE");
        u->Draw(dist_totalbgErr[fstype][disttype],"sameE2");
        TH1F *h_sig1 = vec_dist_signal[fstype][DrawnSignalType->at(0)][disttype]->at(DrawnSignalFile->at(0));
        TH1F *h_sig2 = vec_dist_signal[fstype][DrawnSignalType->at(1)][disttype]->at(DrawnSignalFile->at(1));
        h_sig1->SetLineColor(DrawnSignalColor->at(0));
        h_sig2->SetLineColor(DrawnSignalColor->at(1));
        h_sig1->SetMarkerColor(DrawnSignalColor->at(0));
        h_sig2->SetMarkerColor(DrawnSignalColor->at(1));
        h_sig1->SetFillColor(0);
        h_sig2->SetFillColor(0);
        h_sig1->SetLineStyle(DrawnSignalStyle->at(0));
        h_sig2->SetLineStyle(DrawnSignalStyle->at(1));
        h_sig1->Draw("samehist");
        h_sig2->Draw("samehist");
        //////////////////////////////////////////////////////////////
        // Log version
        //////////////////////////////////////////////////////////////
        u->cdPad();
        //should be drawn in this order
        hs_bg[fstype][disttype]->SetMaximum(logMax);
        hs_bg[fstype][disttype]->SetMinimum(1.E-2);
        hs_bg[fstype][disttype]->Draw("hist");
        u->Draw(dist_totalbg   [fstype][disttype],"samehist");
        //	dist_data[fstype][disttype]->Draw("sameE");
        u->Draw(dist_totalbgErr[fstype][disttype],"sameE2");
        h_sig1->Draw("samehist");
        //	h_sig2->Draw("samehist");
        gPad->SetLogy();
      }
      //Ratio plot
      u->cdPad(); //not needed when we include ratio plot in the future
      // //should be drawn in this order
      // Double_t ratioWidth = 1.0;
      // dist_ratio[fstype][disttype]->SetStats(0);
      // dist_ratio[fstype][disttype]->GetYaxis()->SetRangeUser(1.-ratioWidth,1.+ratioWidth);
      // //      dist_ratio[fstype][disttype]->SetMarkerColor(kBlack);
      // u->Draw(dist_ratio[fstype][disttype],"E");
      // u->Draw(dist_ratioErr[fstype][disttype],"sameE2");
    }
  }

  //Plotting signal only distributions
  for(Int_t fstype=0; fstype<nFSType; fstype++){
    for(Int_t disttype=0; disttype<nDistType; disttype++){
      for(Int_t signaltype=0; signaltype<nSignalType; signaltype++){
        UInt_t nsamples = SignalFileNames[signaltype]->size();
        for(UInt_t signalfile=0; signalfile<nsamples; signalfile++){
          std::string option = (signaltype==0&&signalfile==0) ? "" : "same";
          if(option=="") u->cdPad();
          vec_dist_signal[fstype][signaltype][disttype]->at(signalfile)->Draw(option.c_str());
        }
      }
    }
  }

  //drawing legends again...
  u->SetPadNumXY(1,1);
  leg->AddEntry(vec_dist_signal[0][DrawnSignalType->at(0)][0]->at(DrawnSignalFile->at(0)),"SUSY Ref1","l");
  leg->AddEntry(vec_dist_signal[0][DrawnSignalType->at(1)][0]->at(DrawnSignalFile->at(1)),"SUSY Ref2","l");
  leg->Draw();


  delete vec_datafiles;
  delete vec_signalfiles;
  delete vec_mcfiles;
  delete u;

  return 0;
}
