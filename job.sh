#!/bin/bash

# Exit on error
set -e

echo "### Begin of job"

ID=$1
echo "ID:" $ID

PROCESS=$2
echo "Process:" $PROCESS

FILE=$3
echo "File:" $FILE

FIRST_LETTER=$(whoami | cut -c1)
echo "FIRST_LETTER:" $FIRST_LETTER

LOCAL_PLACE=OpenData 

USERNAME=$(whoami)
echo "USERNAME: " $USERNAME 

EOS_HOME=/eos/user/${FIRST_LETTER}/${USERNAME}
echo "EOS home:" $EOS_HOME

OUTPUT_DIR=${EOS_HOME}/opendata_files/
echo "Output directory:" $OUTPUT_DIR

CMSSW_BASE=/afs/cern.ch/work/${FIRST_LETTER}/${USERNAME}/${LOCAL_PLACE}/CMSSW_5_3_32
echo "CMSSW base:" $CMSSW_BASE

if [[ ${FILE} == *"Run2011A"* ]]; then
    CONFIG=${CMSSW_BASE}/src/workspace/TagAndProbe/configs/TagAndProbe_Data.py
else
    CONFIG=${CMSSW_BASE}/src/workspace/TagAndProbe/configs/TagAndProbe_MC.py
fi
echo "CMSSW config:" $CONFIG

echo "Hostname:" `hostname`

echo "How am I?" `id`

echo "Where am I?" `pwd`

echo "What is my system?" `uname -a`

echo "### Start working"

# Trigger auto mount of EOS
ls -la $EOS_HOME
echo $EOS_HOME

# Make output directory
mkdir -p ${OUTPUT_DIR}/${PROCESS}
echo ${OUTPUT_DIR} "/" ${PROCESS}

# Setup CMSSW
THIS_DIR=$PWD
cd $CMSSW_BASE
source /cvmfs/cms.cern.ch/cmsset_default.sh
eval `scramv1 runtime -sh`
cd $THIS_DIR
echo $THIS_DIR

# Copy config file
mkdir -p configs/
CONFIG_COPY=configs/cfg_${ID}.py
#echo "config: " $CONFIG
#echo "CONFIG_COPY: " $CONFIG_COPY
echo "Starting to Copy"

cp $CONFIG $CONFIG_COPY
echo "Ending to copy...."

# Modify CMSSW config to run only a single file
sed -i -e "s,^files =,files = ['"${FILE}"'] #,g" $CONFIG_COPY
sed -i -e 's,^files.extend,#files.extend,g' $CONFIG_COPY

# Modify CMSSW config to read lumi mask from EOS
sed -i -e 's,data/Cert,'${CMSSW_BASE}'/src/workspace/TagAndProbe/data/Cert,g' $CONFIG_COPY

# Modify config to write output directly to EOS
sed -i -e 's,output.root,'${PROCESS}_${ID}.root',g' $CONFIG_COPY

# Print config
cat $CONFIG_COPY

# Run CMSSW config
cmsRun $CONFIG_COPY

# Copy output file
xrdcp -f ${PROCESS}_${ID}.root root://eosuser.cern.ch/${OUTPUT_DIR}/${PROCESS}/${PROCESS}_${ID}.root
rm ${PROCESS}_${ID}.root

echo "### End of job"
