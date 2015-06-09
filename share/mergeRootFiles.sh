TAG=$1
if [ $# -lt 1 ]; then
  echo 'Specify a target tag (e.g. h0001, h0002...)'
  return 1
fi
DSID=("110302" "110305" #single top
    "110401" #ttbar
    "119353" "119355" "119583" #ttV
    "147406" "147407" "147408" #Z+jets
    "161105" "161155" "161305"
    "161555" "161566" "161577" "161595" "161617"
    "161635" "161646" "161657" "161675" "161686" "161697" "161805" "161827" "161849" #Higgs
    "174830" "174831" "174832" "174833" #ttV
    "187160" "187161" "187162" "187163" "187164" "187165"
    "187166" "187167" "187168" "187170" "187171" "187172"
    "187173" "187174" "187175" "187176" "187177" "187178" #WZ
    "187180" "187181" "187182" "187183" "187184" "187185" "187186" "187187" "187188" #ZZ
    "205048" "205049" "205050" "205051" "205052" "205053"
    "205054" "205055" "205056" "205128" "205129" "205130" "205131" #Signal(N2C1toWZ)
)
REGION=("2S3B" "2S3BZveto" "2S3BBveto" "2S3BMet" "2S3BZvetoBvetoMet" "3S3B" "3S3BZveto" "3S3BBveto" "3S3BMet" "3S3BZvetoBvetoMet" "3S4B" "3S4BZveto" "3S4BBveto" "3S4BMet" "3S4BZvetoBvetoMet")

DIRECTORY='result'
for i in "${DSID[@]}"
do
    for j in "${REGION[@]}"
    do
        echo 'Merging data files of '$i' : SelecReg='$j' for the tag of '$TAG
        echo time hadd -f ${DIRECTORY}/${TAG}/${i}.${j}.AnaHists.root ${DIRECTORY}/${TAG}/${i}_*/data-*.${j}.*/*.root
        time hadd -f ${DIRECTORY}/${TAG}/${i}.${j}.AnaHists.root ${DIRECTORY}/${TAG}/${i}_*/data-*.${j}.*/*.root
    done
done
