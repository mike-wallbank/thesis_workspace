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
echo Made directory at ${CONDORDIR}

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

echo Made directory at ${CONDORRUNDIR}

# get the file from sam web
filename=`samweb list-files "run_number=$run and data_tier raw"`
path=`samweb -e lbne get-file-access-url "$filename"`
file=/pnfs/lbne${path:29}

# copy the necessary files
cd $CONDORRUNDIR
echo
echo About to copy files into directory
pwd
echo
copyfile /dune/app/users/wallbank/larsoft-base/workspace/job/RunSplitter.fcl RunSplitter.fcl
copyfile /dune/app/users/wallbank/larsoft-base/workspace/job/SliceAndFilter.fcl SliceAndFilter.fcl
copyfile /dune/app/users/wallbank/larsoft-base/workspace/job/reco_dune35tdata.fcl reco_dune35tdata.fcl
#copyfile /dune/app/users/wallbank/larsoft-base/workspace/job/apa_crossing.fcl apa_crossing.fcl
#copyfile /dune/app/users/wallbank/larsoft-base/workspace/35tanalysis/bad_timings.fcl bad_timings.fcl
copyfile $file $filename

echo "About to run jobs, contents of directory is"
ls

# run the jobs
if [ ${FILTER} -eq 1 ]
then
lar -c SliceAndFilter.fcl -s $filename -o sliced_and_filtered.root -n 5
else
lar -c RunSplitter.fcl -s $filename -o sliced_and_filtered.root -n 5
fi
lar -c reco_dune35tdata.fcl -s sliced_and_filtered.root -o reco.root
#lar -c apa_crossing.fcl -s reco.root
#lar -c bad_timings.fcl -s $filename

# copy output files back
rm -f $filename
copyfile -r $CONDORRUNDIR $OUTRUNDIR

# remove the temp directory
rm -rf $CONDORRUNDIR
