#include "xAODRootAccess/Init.h"
#include "SampleHandler/SampleHandler.h"
#include "SampleHandler/ToolsDiscovery.h"
#include "EventLoop/Job.h"
#include "EventLoop/DirectDriver.h"
#include "SampleHandler/DiskListLocal.h"
#include <TSystem.h>
#include <TString.h>

#include "MyAnalysis/MyxAODAnalysis.h"

int main( int argc, char* argv[] ) {

  // Take the submit directory from the input if provided:
  std::string submitDir = "submitDir";
  if( argc > 1 ) submitDir = argv[ 1 ];
  TString olddir = submitDir.c_str();
  if(!gSystem->AccessPathName(olddir)){
    gSystem->Exec(Form("rm -rf %s~",olddir.Data()));
    gSystem->Rename(olddir,olddir+"~");
  }
  TString DSID = "";
  if( argc > 2 ) DSID = argv[ 2 ];

  // Set up the job for xAOD access:
  xAOD::Init().ignore();

  // Construct the samples to run on:
  SH::SampleHandler sh;

  bool isData = false;
  if(DSID.BeginsWith("data")) isData = true;

  std::string inputFilePath = "";
  if(DSID.BeginsWith("test")){
    if     (DSID.EndsWith("data")) inputFilePath = Form("/home/hirose/atlas/data/tutorial_data/r5597");
    else if(DSID.EndsWith("mc"  )) inputFilePath = Form("/home/hirose/atlas/data/tutorial_data/r5591");
    else                           inputFilePath = Form("/home/hirose/atlas/data/DC14/mc14_13TeV");
  }else{
    if(isData) inputFilePath = Form("/home/hirose/atlas/data/tutorial_data/r5597/%s",DSID.Data());
    //    else       inputFilePath = Form("/home/hirose/atlas/data/tutorial_data/r5591/%s",DSID.Data());
    else       inputFilePath = Form("/home/hirose/atlas/data/DC14/mc14_13TeV/%s",DSID.Data());
  }
  std::cout<<"DSID         : "<<DSID.Data()          <<std::endl;;
  std::cout<<"DataFullPath : "<<inputFilePath.c_str()<<std::endl;;
  SH::DiskListLocal list (inputFilePath.c_str());
  if      (DSID=="testwithdata"){
    SH::scanDir (sh, list, "AOD.01495682._002184.pool.root.1"); // specifying one particular data file for testing 
  }else if(DSID=="testwithmc"  ){
    SH::scanDir (sh, list, "AOD.01494882._113691.pool.root.1"); // specifying one particular mc file for testing
  }else if(DSID=="testwithdc14"){
    SH::scanDir (sh, list, "AOD.04786763._000001.pool.root.1"); // specifying one particular dc14 file for testing
  }else{
    SH::scanSingleDir (sh, DSID.Data(), list);
  }

  // Set the name of the input TTree. It's always "CollectionTree"
  // for xAOD files.
  sh.setMetaString( "nc_tree", "CollectionTree" );

  // Print what we found:
  sh.print();

  // Create an EventLoop job:
  EL::Job job;
  job.sampleHandler( sh );

  // Add our analysis to the job:
  MyxAODAnalysis* alg = new MyxAODAnalysis();
  job.algsAdd( alg );

  // Run the job using the local/direct driver:
  EL::DirectDriver driver;
  driver.submit( job, submitDir );

  return 0;
}
