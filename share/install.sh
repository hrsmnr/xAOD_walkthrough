#!/bin/sh
git clone git://github.com/hrsmnr/MMTool.git
source /cvmfs/atlas.cern.ch/repo/ATLASLocalRootBase/user/atlasLocalSetup.sh
rcSetup Base,2.1.33
rc checkout_pkg $SVNOFF/PhysicsAnalysis/SUSYPhys/SUSYTools/tags/SUSYTools-00-05-00-31
rc checkout_pkg $SVNOFF/Reconstruction/EventShapes/EventShapeTools/tags/EventShapeTools-00-01-09
rc checkout_pkg $SVNOFF/Reconstruction/EventShapes/EventShapeInterface/tags/EventShapeInterface-00-00-09
rc checkout_pkg $SVNOFF/PhysicsAnalysis/ElectronPhotonID/ElectronEfficiencyCorrection/tags/ElectronEfficiencyCorrection-00-01-19
rc checkout_pkg $SVNOFF/PhysicsAnalysis/ElectronPhotonID/PhotonEfficiencyCorrection/tags/PhotonEfficiencyCorrection-00-01-05
rc checkout_pkg $SVNPERF/CombPerf/FlavorTag/FlavorTagEfficiencyMaps/PreRun2_DC14/tags/PreRun2_DC14-00-00-07
mv $ROOTCOREBIN/../PreRun2_DC14 $ROOTCOREBIN/../BTagEfficiencyReader
rc checkout_pkg svn+ssh://svn.cern.ch/reps/atlasphys/Physics/SUSY/Tools/CalcGenericMT2
cp CalcGenericMT2/src/MT2.h MyAnalysis/MyAnalysis/
cp CalcGenericMT2/src/MT2_ROOT.h MyAnalysis/MyAnalysis/
rm -rf CalcGenericMT2
rc checkout_pkg atlasoff/PhysicsAnalysis/MCTruthClassifier/tags/MCTruthClassifier-00-01-31
cp MCTruthClassifier/MCTruthClassifier/MCTruthClassifierDefs.h MyAnalysis/MyAnalysis/
rm -rf MCTruthClassifier
rc find_packages
rc compile
\cp -f $ROOTCOREBIN/../MyAnalysis/share/CrossSection/CrossSections_13TeV.txt $ROOTCOREBIN/data/SUSYTools/
