#!/bin/bash

echo Start of analysing run 014444

alias copyfile="ifdh cp --force=expgridftp"

# setup the software
source /grid/fermiapp/products/dune/setup_dune.sh
source /dune/app/users/wallbank/larsoft-base/prof/localProducts_larsoft_v05_12_01_e9_prof/setup
#source /grid/fermiapp/products/larsoft/mrb/v1_07_01/bin/mrbSetEnv
source /grid/fermiapp/products/larsoft/mrb/v1_07_01/bin/setup_local_products

# copy the necessary files
mkdir -p ${_CONDOR_SCRATCH_DIR}/EW/014444
cd ${_CONDOR_SCRATCH_DIR}/EW/014444
copyfile /dune/app/users/wallbank/larsoft-base/workspace/35tanalysis/SliceAndFilter.fcl .
copyfile /dune/app/users/wallbank/larsoft-base/workspace/35tanalysis/reco_dune35tdata.fcl .
copyfile /pnfs/lbne/pnfs/fnal.gov/usr/lbne/test-data/lbne/raw/00/63/78/50/lbne_r014444_sr01_20160303T225238.root .

echo
echo Contents of directory
ls
echo

# run the jobs
lar -c SliceAndFilter.fcl -s lbne_r014444_sr01_20160303T225238.root -o sliced_and_filtered.root
lar -c reco_dune35tdata.fcl -s sliced_and_filtered.root -o reco.root

# copy output files back
copyfile -r ${_CONDOR_SCRATCH_DIR}/EW/014444 /dune/data/users/wallbank/Sliced_And_Filtered/EW/014444

# remove the temp directory
rm -rf ${_CONDOR_SCRATCH_DIR}/EW/014444

echo End of script

