# xAOD_walkthrough
Analysis framework based on Base,2.1.30 with SUSYTools-00-05-00-26.

## Usage -----
$source rcSetup.sh
$rc find_packages
$rc compile
$testRun (Output directory) (DatasetName)
(e.g. $time testRun submitDir testwithmc 2>&1 | tee logmine.txt)

test
