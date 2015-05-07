#default target directory
TARGETDS=$1
if [ $# -lt 1 ]; then
  echo '============================================================================'
  echo 'This script execute "testRun" against all the dataset in [Dataset path].'
  echo 'Works only on the nodes'
  echo 'Usage :'
  echo '$source brunall.sh [Dataset path] [selction region1] [selection region2],,,'
  echo '============================================================================'
  echo 'Exitting ...'
  return 1
fi

#check if there is a specified target selection region
TARGETSELECREG=''
if [ $# -lt 2 ]; then
  echo 'Specify at least one target selection region (e.g. test,3lep...)'
  return 1
fi

#additional target selection region
while [ "$2" != "" ]
do
  TARGETSELECREG='-S '$2' '$TARGETSELECREG
  shift
done

echo Target DS directory     = $TARGETDS
echo Target selection region = $TARGETSELECREG

###########################################################
# Deleting old logfiles in ./lsfoutput
###########################################################
\rm -f lsfoutput/*.log~* #delete logfiles with "~" first
for logfile in `ls ./lsfoutput`
do
    \cp -p --force lsfoutput/$logfile lsfoutput/$logfile~
    \rm -f lsfoutput/$logfile
done

###########################################################
# Submitting jobs to the dataset in the target directory 
###########################################################
for TXT in `ls $TARGETDS`
do
lenFilelistDirName=${#TXT}
#extension check (should be .txt)
extensionStartPos=`expr $lenFilelistDirName - 3`
extensionEndPos=`expr $lenFilelistDirName`
extension=`echo $TXT | cut -c $extensionStartPos-$extensionEndPos`
if [ "$extension" = ".txt" ]; then
#    echo "matched"
    :
else
#    echo "unmatched"
    continue
fi
#extracting run number
if [ $lenFilelistDirName -eq 10 ]; then
    startPos=`expr $lenFilelistDirName - 9`
    runnumEndPos=`expr $lenFilelistDirName - 6`
    outputDirEndPos=`expr $lenFilelistDirName - 4`
elif [ $lenFilelistDirName -gt 10 ]; then
    startPos=1
    runnumEndPos=`expr $lenFilelistDirName - 6`
    outputDirEndPos=`expr $lenFilelistDirName - 4`
fi
outputDir=`echo $TXT | cut -c $startPos-$outputDirEndPos`
runnum=`echo $TXT | cut -c $startPos-$runnumEndPos`
#echo $TXT
######################################################

######################################################
# Waiting for #submitted jobs to be less than maxJobs
maxJobs=150
while [ $(bjobs | wc -l) -gt $maxJobs  ]
do
    echo Currently $(bjobs | wc -l) jobs are runnning. Wait for 10 seconds to keep less running jobs...
    sleep 10
done
######################################################

maxEve=-1
echo Starting testRun for DSID=$runnum ...
echo 'bsub -q 12h -o ./lsfoutput/'${outputDir}'.log testRun -n '$maxEve' --FileDirBase '$TARGETDS' --filelist '$TXT' -o result/'$outputDir' '$TARGETSELECREG
bsub -q 12h -o ./lsfoutput/{$outputDir}.log testRun -n $maxEve --FileDirBase $TARGETDS --filelist $TXT -o result/$outputDir $TARGETSELECREG
echo ''
done
