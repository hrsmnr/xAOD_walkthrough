#!/bin/sh
source /cvmfs/atlas.cern.ch/repo/ATLASLocalRootBase/user/atlasLocalSetup.sh
rcSetup Base,2.1.30
rc checkout_pkg atlasoff/PhysicsAnalysis/SUSYPhys/SUSYTools/tags/SUSYTools-00-05-00-26
rc checkout_pkg atlasoff/Reconstruction/EventShapes/EventShapeTools/tags/EventShapeTools-00-01-09
rc checkout_pkg atlasoff/Reconstruction/EventShapes/EventShapeInterface/tags/EventShapeInterface-00-00-09
rc checkout_pkg atlasoff/PhysicsAnalysis/ElectronPhotonID/ElectronEfficiencyCorrection/tags/ElectronEfficiencyCorrection-00-01-19
rc checkout_pkg atlasoff/Reconstruction/Jet/JetCalibTools/tags/JetCalibTools-00-04-34
rc checkout_pkg atlasoff/Reconstruction/Jet/JetUncertainties/tags/JetUncertainties-00-09-19
rc checkout_pkg atlasoff/Event/xAOD/xAODMuon/tags/xAODMuon-00-09-02-01
rc checkout_pkg svn+ssh://svn.cern.ch/reps/atlasphys/Physics/SUSY/Tools/CalcGenericMT2
cp CalcGenericMT2/src/MT2.h MyAnalysis/MyAnalysis/
cp CalcGenericMT2/src/MT2_ROOT.h MyAnalysis/MyAnalysis/
rm -rf CalcGenericMT2
rc checkout_pkg atlasoff/PhysicsAnalysis/MCTruthClassifier/tags/MCTruthClassifier-00-01-31
cp MCTruthClassifier/MCTruthClassifier/MCTruthClassifierDefs.h MyAnalysis/MyAnalysis/
rm -rf MCTruthClassifier
rc find_packages
rc compile
ln -sf $ROOTCOREBIN/../share/CrossSection/CrossSections_13TeV.txt RootCoreBin/data/SUSYTools/
