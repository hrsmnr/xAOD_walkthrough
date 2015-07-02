# xAOD_walkthrough
Analysis framework based on Base,2.1.33 with SUSYTools-00-05-00-31.

## Contents of the package ----
./MyAnalysis : analysis package for EventLoop.  
./lsfoutput  : empty directory to store LSF outputs (only for login.icepp.jp).  
./result     : empty directory to store results of each EventLoop process will be in this directory.  
./share      : contains misc. files (e.g. install.sh, GRL.xml, XSDB.txt).  
./analysis/  : analysis codes  
  --mkBasicPlots : ROOT script to make distributions of Data/MC.  

## Usage -----
kinit [your account]@CERN.CH #not necessary but recommended  
./share/install.sh #setting up RootCore and installing all necessary packages  

## Tips / example -----
$git clone git://github.com/hrsmnr/xAOD_walkthrough.git [destination]  
$git remote add origin https://hrsmnr@github.com/hrsmnr/xAOD_walkthrough.git  
$git log --branches --not --remotes  
$source rcSetup.sh  
$rc find_packages  
$rc compile  
$testRun -D test -n 10  
$source share/runOnLocal.sh [Dataset directory] [Signal selection]  
$source share/runOnLSF.sh [Dataset directory] [Signal selection]  
$python share/mkFileList.py [optionally: target directory]  
$source share/runOnLSFSplitDS.sh [Dataset directory] [Signal selection]  
$source share/runOnLSFHybridInput.sh [Dataset directory] [Signal selection]  
$source share/mergeRootFiles.sh [tag(e.g. h0001)]  
$root -q -b -n 'mkPlots.C+O("h0015","3S3B")'  
$root -q -b -n 'mkFRMeas.C+O("h0015","3S3B")'  
$bkill -u [your account] -b 0 #kill all your jobs on LSF  
$bjobs -l  
$bjobs -u all  
$bjobs -a  
$bhosts  
$bqueues  

## To use FAX as an input of the analysis  
$setupATLAS  
$localSetupFAX  
$voms-proxy-init --voms atlas:/atlas/jp  
$source rcSetup.sh  
$python share/mkFaxFileList.py [optionally: target dataset list]  
## Submitting jobs with FAX to LSF  
-- Make your GRID passward file as ./share/pfile.txt
-- Attention: make sure no access right for others!! (chmod 0600 ./share/pfile.txt)

## Patches (might) needed in other packages
===================================================================  
--- SUSYTools/Root/SUSYObjDef_xAOD.cxx  (revision 676240)  
+++ SUSYTools/Root/SUSYObjDef_xAOD.cxx  (working copy)  
@@ -1353,7 +1353,8 @@  
   bool isbjet = (weight > opcut);  
 
   if (m_doTruthBtag) {  
-    m_btagEffReader.setRandomSeed(int( 1e5 + 5 * fabs(input.eta()))); //set a unique seed for each jet  
+    //    m_btagEffReader.setRandomSeed(int( 1e5 + 5 * fabs(input.eta()))); //set a unique seed for each jet  
+    m_btagEffReader.setRandomSeed(int( 1e5 * 5 * fabs(input.eta()))); //set a unique seed for each jet  
     isbjet = m_btagEffReader.performTruthTagging(&input);  
   }  
 
===================================================================  
--- SUSYTools/Root/SUSYToolsInit.cxx    (revision 676240)  
+++ SUSYTools/Root/SUSYToolsInit.cxx    (working copy)  
@@ -145,6 +145,7 @@  
     ATH_CHECK( muonCalibrationAndSmearingTool->setProperty("SmearingType", "q_pT") );  
     ATH_CHECK( muonCalibrationAndSmearingTool->setProperty("Release", "Rel17.2Sum13") );  
     ATH_CHECK( muonCalibrationAndSmearingTool->initialize() );  
+    muonCalibrationAndSmearingTool->msg().setLevel( MSG::ERROR );  
     m_muonCalibrationAndSmearingTool = muonCalibrationAndSmearingTool;  
   }  
@@ -450,6 +450,7 @@  
     // ATH_CHECK( metRebuilder->setProperty("SoftTermType","Reference") );  
     ATH_CHECK( metRebuilder->setProperty("SoftTermType","") ); // ignore autoconfiguration  
     ATH_CHECK( metRebuilder->initialize() );  
+    metRebuilder->msg().setLevel( MSG::ERROR );  
     m_metRebuilder = metRebuilder;  
   }  
===================================================================  
--- SUSYTools/Root/SUSYObjDef_xAOD.cxx  (revision 676240)  
+++ SUSYTools/Root/SUSYObjDef_xAOD.cxx  (working copy)  
@@ -1353,7 +1353,8 @@  
   bool isbjet = (weight > opcut);  
 
   if (m_doTruthBtag) {  
-    m_btagEffReader.setRandomSeed(int( 1e5 + 5 * fabs(input.eta()))); //set a unique seed for each jet  
+    //    m_btagEffReader.setRandomSeed(int( 1e5 + 5 * fabs(input.eta()))); //set a unique seed for each jet  
+    m_btagEffReader.setRandomSeed(int( 1e5 * 5 * fabs(input.eta()))); //set a unique seed for each jet  
     isbjet = m_btagEffReader.performTruthTagging(&input);  
   }  
@@ -1466,7 +1470,8 @@  
       std::vector<int> nTrkVec;  
       (*jet_itr)->getAttribute(xAOD::JetAttribute::NumTrkPt500, nTrkVec);  
-      int jet_nTrk = nTrkVec[this->GetPrimVtx()->index()];  
+      int jet_nTrk = (this->GetPrimVtx() == 0 || nTrkVec.size() == 0) ? 0 : nTrkVec[this->GetPrimVtx()->index()];  
+      //      int jet_nTrk = nTrkVec[this->GetPrimVtx()->index()];  
@@ -1705,7 +1712,8 @@  
        std::vector<int> nTrkVec;  
       (*jet_itr)->getAttribute(xAOD::JetAttribute::NumTrkPt500, nTrkVec);  
-      int jet_nTrk = nTrkVec[this->GetPrimVtx()->index()];  
+      int jet_nTrk = (this->GetPrimVtx() == 0 || nTrkVec.size() == 0) ? 0 : nTrkVec[this->GetPrimVtx()->index()];  
+      //      int jet_nTrk = nTrkVec[this->GetPrimVtx()->index()];  
