#!/bin/bash

# Define path for job directories
BASE_PATH=$PWD
mkdir -p $BASE_PATH

# Set processes
PROCESSES=( \
    JPsiToMuMu \
    Run2011A_MuOnia \
    )

# Create JDL files and job directories
for PROCESS in ${PROCESSES[@]}
do
    python create_job.py $PROCESS $BASE_PATH
done

# Submit jobs
THIS_PWD=$PWD
for PROCESS in ${PROCESSES[@]}
do
    cd $BASE_PATH/$PROCESS
    condor_submit job.jdl
    cd $THIS_PWD
done
