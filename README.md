# xAOD_walkthrough
Analysis framework based on Base,2.1.30 with SUSYTools-00-05-00-26.

## Contents ----
./MyAnalysis : analysis package
./share      : contains misc. files (e.g. install.sh, GRL.xml)

## Usage -----
kinit [your account]@CERN.CH #not necessary but recommended
./share/install.sh #setting up RootCore and installing all necesarry packages

## Tips / example -----
$source rcSetup.sh
$rc find_packages
$rc compile
$testRun -D test -n 10
$source share runOnLocal.sh [Dataset directory] [Signal selection]
$source share runOnLSF.sh [Dataset directory] [Signal selection]
