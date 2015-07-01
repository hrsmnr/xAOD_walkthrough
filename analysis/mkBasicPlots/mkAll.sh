TAG=$1
if [ $# -lt 1 ]; then
  echo 'Specify a target tag (e.g. h0001, h0002...)'
  return 1
fi
DIRECTORY=${ROOTCOREBIN}/../result/
echo $DIRECTORY

###################################################
## Preparing available selection regions
###################################################
REGION=()
for fname in `ls -d $DIRECTORY/$TAG/110401_1/data*`
do
    REG=`echo $fname | cut -d'.' -f4`
    REGION+=($REG)
done

###################################################
## Merging files
###################################################
for reg in "${REGION[@]}"
do
    echo $reg
    root -q -b 'mkPlots.C("'${TAG}'","'${reg}'")'
done
