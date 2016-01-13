TAG=$1
if [ $# -lt 1 ]; then
  echo 'Specify a target tag (e.g. h0001, h0002...)'
  return 1
fi
DIRECTORY='result'

###################################################
## Preparing available mc and data DSIDs
###################################################
ALLDSID=()
ALLDATARUNS=()
for fname in `find $DIRECTORY/$TAG/ -mindepth 1 -maxdepth 1 -type d`
do
    tmpid=`echo $fname | cut -d'/' -f3 | cut -d'_' -f1`
    if [ ${tmpid} -lt 200000 -o 300000 -le ${tmpid} ]; then
        ALLDSID+=(${tmpid})
    else
        ALLDATARUNS+=(${tmpid})
    fi
done
DSID=(`echo ${ALLDSID[*]} | sed 's/\s/\n/g' | sort | uniq`)
if [ ${#DSID[@]} -ne 0 ]; then
    echo 'Found MC dataset list:'
    echo ${DSID[@]}
    REFID=${DSID}
fi
DATARUNS=(`echo ${ALLDATARUNS[*]} | sed 's/\s/\n/g' | sort | uniq`)
if [ ${#DATARUNS[@]} -ne 0 ]; then
    echo 'Found data run list:'
    echo ${DATARUNS[@]}
    REFID=${DATARUNS}
fi

###################################################
## Preparing available selection regions
###################################################
REGION=()
for fname in `ls -d $DIRECTORY/$TAG/${REFID}_1/data*`
do
    REG=`echo $fname | cut -d'.' -f2`
    REGION+=($REG)
done
if [ ${#REGION[@]} -ne 0 ]; then
    echo 'Found selection regions:'
    echo ${REGION[@]}
fi

###################################################
## Merging MC files
###################################################
queue=4h
for mcid in "${DSID[@]}"
do
    for reg in "${REGION[@]}"
    do
        echo 'Merging data files of '$mcid' : SelecReg='$reg' for the tag of '$TAG
        echo bsub -q ${queue} -e ${DIRECTORY}/${TAG}/${mcid}.${reg}.AnaHists.err -o ${DIRECTORY}/${TAG}/${mcid}.${reg}.AnaHists.log hadd -f ${DIRECTORY}/${TAG}/${mcid}.${reg}.AnaHists.root ${DIRECTORY}/${TAG}/${mcid}_*/data-*.${reg}.*/*.root
        bsub -q ${queue} -e ${DIRECTORY}/${TAG}/${mcid}.${reg}.AnaHists.err -o ${DIRECTORY}/${TAG}/${mcid}.${reg}.AnaHists.log hadd -f ${DIRECTORY}/${TAG}/${mcid}.${reg}.AnaHists.root ${DIRECTORY}/${TAG}/${mcid}_*/data-*.${reg}.*/*.root
    done
done

###################################################
## Merging Data files
###################################################
for reg in "${REGION[@]}"
do
    echo 'Merging data files: SelecReg='$reg' for the tag of '$TAG
    echo bsub -q ${queue} -e ${DIRECTORY}/${TAG}/data.${reg}.AnaHists.err -o ${DIRECTORY}/${TAG}/data.${reg}.AnaHists.log hadd -f ${DIRECTORY}/${TAG}/data.${reg}.AnaHists.root ${DIRECTORY}/${TAG}/2*/data*${reg}.AnaHists/*.root
    bsub -q ${queue} -e ${DIRECTORY}/${TAG}/data.${reg}.AnaHists.err -o ${DIRECTORY}/${TAG}/data.${reg}.AnaHists.log hadd -f ${DIRECTORY}/${TAG}/data.${reg}.AnaHists.root ${DIRECTORY}/${TAG}/2*/data*${reg}.AnaHists/*.root
done

