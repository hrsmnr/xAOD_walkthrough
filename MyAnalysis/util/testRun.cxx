#include "xAODRootAccess/Init.h"
#include "EventLoop/Job.h"
#include "EventLoop/DirectDriver.h"
#include "SampleHandler/SampleHandler.h"
#include "SampleHandler/ToolsDiscovery.h"
#include "SampleHandler/DiskListLocal.h"
#include <TSystem.h>
#include <TString.h>
#include <vector>

#include "MyAnalysis/MyxAODAnalysis.h"

void help();
char* GetMsgLevelStr(MSG::Level level);
MSG::Level GetMsgLevel(int level);

int main( int argc, char* argv[] ) {

  if(argc==1) help();
  std::cout << "Starting analysis code..." << std::endl;
  std::cout << std::endl;

  int nEvt = -1;
  //  int nSkip = 0;
  //  int freq = 50000;
  MSG::Level dbg = MSG::ERROR;
  //  std::string sample = "";
  std::vector<std::string> sels;
  std::string file = "";
  std::string fileDir = "";
  std::string fileDirBase = "/home/hirose/atlas/data/DC14/mc14_13TeV";
  std::string outputDir = "result/submitDir";
  bool doSys = false;
  //  bool limitTree = false;
  
  /** Read inputs to program */  
  for(int i = 1; i < argc; i++) {
    if (strcmp(argv[i], "-n") == 0)
      nEvt = atoi(argv[++i]);
    //    else if (strcmp(argv[i], "-k") == 0)
    //      nSkip = atoi(argv[++i]);
    //    else if (strcmp(argv[i], "-q") == 0)
    //      freq = atoi(argv[++i]);
    else if (strcmp(argv[i], "-d") == 0)
      dbg = GetMsgLevel( atoi(argv[++i]) );
    else if (strcmp(argv[i], "-F") == 0)
      file = argv[++i];
    else if (strcmp(argv[i], "-D") == 0)
      fileDir = argv[++i];
    else if (strcmp(argv[i], "--FileDirBase") == 0)
      fileDirBase = argv[++i];
    else if (strcmp(argv[i], "-o") == 0)
      outputDir = argv[++i];
    //    else if (strcmp(argv[i], "-s") == 0)
    //      sample = argv[++i];
    else if (strcmp(argv[i], "-S") == 0)
      sels.push_back(argv[++i]);
    else if (strcmp(argv[i], "--sys") == 0)
      doSys = true;
    //    else if (strcmp(argv[i], "--limitTree") == 0)
    //      limitTree = true;
    //else if (strcmp(argv[i], "--sigCut") == 0)
      //sigCut = argv[++i];
    else if (strcmp(argv[i], "-h") == 0) help();
    else help();
  }

  // If no input is specified, return with message.
  if(fileDir.empty()){
    std::cout << "Please specify the input sample by the option \"-D\"" <<std::endl;
    std::cout << "When you specify \"test\", SUSY signal sample written below will be used." <<std::endl;
    std::cout << "-- mc14_13TeV.205048.Herwigpp_UEEE4_CTEQ6L1_sM_wA_WZ_C1_100_N1_0.merge.AOD.e3479_a266_a265_r5853_tid04786763_00" << std::endl;
    return 0;
  }

  std::cout << "flags:" << std::endl;
  //  std::cout << "  sample  " << sample   << std::endl;
  std::cout <<Form("  outDir   : %s", outputDir.c_str()  ) << std::endl;
  std::cout <<Form("  nEvt     : %d", nEvt               ) << std::endl;
  //  std::cout << "  nSkip   " << nSkip    << std::endl;
  //  std::cout << "  freq    " << freq     << std::endl;
  std::cout <<Form("  dbg      : %s", GetMsgLevelStr(dbg)) << std::endl;
  if(!fileDirBase.empty()) std::cout << Form("  DataPath : %s", fileDirBase.c_str()) << std::endl;
  if(!fileDir    .empty()) std::cout << Form("  inputDir : %s", fileDir    .c_str()) << std::endl;
  if(!file       .empty()) std::cout << Form("  file     : %s", file       .c_str()) << std::endl;
  std::cout << std::endl;

  std::cout << "selections: ";
  for(uint i=0; i<sels.size(); i++) std::cout << sels[i] << ", ";
  std::cout << std::endl;
  std::cout << std::endl;

  //Check if input file path is existing.
  std::string dirFullPath = "";
  if(fileDir=="test") fileDir = "mc14_13TeV.205048.Herwigpp_UEEE4_CTEQ6L1_sM_wA_WZ_C1_100_N1_0.merge.AOD.e3479_a266_a265_r5853_tid04786763_00"; //Default dataset for testing.
  dirFullPath = fileDirBase+"/"+fileDir;
  if(!gSystem->AccessPathName(dirFullPath.c_str())){
    //    std::cout<<"InputPath Existing : "<<dirFullPath.c_str()<<std::endl;    
  }else{
    std::cout<<"Cannot find the input file path : "<<dirFullPath.c_str()<<std::endl;    
    std::cout<<"Exitting ..."<<std::endl;    
    exit(1);
  }

  // Cloning output directory when it already exists.
  std::string submitDir = outputDir;
  TString olddir = submitDir.c_str();
  if(!gSystem->AccessPathName(olddir)){
    gSystem->Exec(Form("rm -rf %s~",olddir.Data()));
    gSystem->Rename(olddir,olddir+"~");
  }

  // Set up the job for xAOD access:
  xAOD::Init().ignore();

  // Construct the samples to run on:
  SH::SampleHandler sh;
  std::cout<<"DatasetName  : "<<fileDir.c_str()    <<std::endl;;
  std::cout<<"DataFullPath : "<<dirFullPath.c_str()<<std::endl;;
  if(!file.empty()){
    FileStat_t info;
    if(gSystem->GetPathInfo((dirFullPath+"/"+file).c_str(), info)!=0) {
      std::cout<<"cannot find the input file in the specified directory."<<std::endl;
      std::cout<<"filename : "<<file.c_str()<<std::endl;
      exit(1);
    }else{
      std::cout<<"Found "<<file.c_str()<<" in the specified directory. "<<std::endl;
    }
    SH::DiskListLocal list(fileDirBase.c_str());
    SH::scanDir(sh, list, file.c_str()); // specifying one particular data file for testing 
  }else{
    SH::DiskListLocal list(dirFullPath.c_str());
    SH::scanSingleDir (sh, fileDir.c_str(), list);
  }

  // Set the name of the input TTree. It's always "CollectionTree" for xAOD files.
  sh.setMetaString( "nc_tree", "CollectionTree" );
  sh.print(); // Print what we found:

  // Create an EventLoop job:
  EL::Job job;
  job.sampleHandler( sh );

  // Add our analysis to the job:
  MyxAODAnalysis* alg = new MyxAODAnalysis();
  alg->SetDebugMode(dbg);
  alg->SetMaxEvent(nEvt);
  alg->SetNoSyst(!doSys);
  job.algsAdd( alg );

  // Run the job using the local/direct driver:
  EL::DirectDriver driver;
  driver.submit( job, submitDir );

  return 0;
}

void help()
{
  std::cout << "  Options:"                          << std::endl;

  std::cout << "  -n number of events to process"    << std::endl;
  std::cout << "     defaults: -1 (all events)"      << std::endl;

  //  std::cout << "  -k number of events to skip"       << std::endl;
  //  std::cout << "     defaults: 0"                    << std::endl;

  //  std::cout << "  -q event printing frequency"       << std::endl;
  //  std::cout << "     defaults: 50000"                << std::endl;

  std::cout << "  --FileDirBase : input file dir location" << std::endl;
  std::cout << "     defaults: '/home/hirose/atlas/data/DC14/mc14_13TeV'" << std::endl;

  std::cout << "  -D : name of input dataset directory" << std::endl;
  std::cout << "     defaults: ''"                      << std::endl;

  std::cout << "  -F name of single input file"      << std::endl;
  std::cout << "     defaults: ''"                   << std::endl;

  std::cout << "  -o output file directory"          << std::endl;
  std::cout << "     defaults: result/submitDir"     << std::endl;

  std::cout << "  -d debug printout level"           << std::endl;
  std::cout << "     defaults: MSG::ERROR"           << std::endl;

  //  std::cout << "  -s sample name, for naming files"  << std::endl;
  //  std::cout << "     defaults: ntuple sample name"   << std::endl;

  std::cout << "  -S adds a selection region"        << std::endl;
  std::cout << "     each usage adds one region"     << std::endl;

  std::cout << "  --sys turns on MC systematics"     << std::endl;

  //  std::cout << "  --limitTree write limit tree"      << std::endl;

  std::cout << "  -h print this help"                << std::endl;

  exit(1);
}

char* GetMsgLevelStr(MSG::Level level){
  if     (level==MSG::VERBOSE) return (char*)"MSG::VERBOSE";
  else if(level==MSG::DEBUG  ) return (char*)"MSG::DEBUG";
  else if(level==MSG::INFO   ) return (char*)"MSG::INFO";
  else if(level==MSG::WARNING) return (char*)"MSG::WARNING";
  else if(level==MSG::ERROR  ) return (char*)"MSG::ERROR";
  else if(level==MSG::FATAL  ) return (char*)"MSG::FATAL";
  else if(level==MSG::ALWAYS ) return (char*)"MSG::ALWAYS";

  return (char*)"NOT DEFINED";
}

MSG::Level GetMsgLevel(int level){
  if     (level==MSG::VERBOSE) return MSG::VERBOSE;
  else if(level==MSG::DEBUG  ) return MSG::DEBUG  ;
  else if(level==MSG::INFO   ) return MSG::INFO   ;
  else if(level==MSG::WARNING) return MSG::WARNING;
  else if(level==MSG::ERROR  ) return MSG::ERROR  ;
  else if(level==MSG::FATAL  ) return MSG::FATAL  ;
  else if(level==MSG::ALWAYS ) return MSG::ALWAYS ;

  return MSG::NIL;
}
