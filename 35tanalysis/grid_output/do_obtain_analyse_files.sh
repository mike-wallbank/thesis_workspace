#!/bin/bash

alias copyfile="ifdh cp --force=expgridftp"

# setup the software
source /grid/fermiapp/products/dune/setup_dune.sh
source ${MRB_INSTALL}/setup
#source ${MRB_DIR}/bin/mrbSetEnv
source ${MRB_DIR}/bin/setup_local_products

# make a temp dir in condor scratch
CONDORDIR=${_CONDOR_SCRATCH_DIR}/${outputDirTag}
mkdir -p ${CONDORDIR}

# get the run number for this job
copyfile /dune/app/users/wallbank/larsoft-base/workspace/35tanalysis/$RUNFILE ${CONDORDIR}
readarray -t RUNS < $CONDORDIR/$RUNFILE
run=${RUNS[$PROCESS]}
echo Start of analysing run $run

# make output dirs for this run
OUTRUNDIR=${OUTDIR}/${run}
CONDORRUNDIR=${CONDORDIR}/${run}

touch ${OUTRUNDIR}
rm -rf ${OUTRUNDIR}
mkdir ${OUTRUNDIR}
mkdir -p ${CONDORRUNDIR}

# get the file from sam web
filename=`samweb list-files "run_number=$run and data_tier raw"`
path=`samweb -e lbne get-file-access-url "$filename"`
file=/pnfs/lbne${path:29}

# copy the necessary files
cd $CONDORRUNDIR
copyfile /dune/app/users/wallbank/larsoft-base/workspace/35tanalysis/RunSplitterDefault.fcl .
copyfile /dune/app/users/wallbank/larsoft-base/workspace/35tanalysis/SliceAndFilter.fcl .
copyfile /dune/app/users/wallbank/larsoft-base/workspace/35tanalysis/reco_dune35tdata.fcl .
copyfile /dune/app/users/wallbank/larsoft-base/workspace/job/apa_crossing.fcl .
#copyfile /dune/app/users/wallbank/larsoft-base/workspace/35tanalysis/bad_timings.fcl .
copyfile $file .

# run the jobs
if [ ${FILTER} -eq 1 ]
then
lar -c SliceAndFilter.fcl -s $filename -o sliced_and_filtered.root
else
lar -c RunSplitterDefault.fcl -s $filename -o sliced_and_filtered.root
fi
lar -c reco_dune35tdata.fcl -s sliced_and_filtered.root -o reco.root
lar -c apa_crossing.fcl -s reco.root
#lar -c bad_timings.fcl -s $filename

# copy output files back
rm -f $filename
copyfile -r $CONDORRUNDIR $OUTRUNDIR

# remove the temp directory
rm -rf $CONDORRUNDIR
