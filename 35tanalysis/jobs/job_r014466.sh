#!/bin/bash

echo Start of analysing run 014466

alias copyfile="ifdh cp --force=expgridftp"

# setup the software
source /grid/fermiapp/products/dune/setup_dune.sh
source /dune/app/users/wallbank/larsoft-base/prof/localProducts_larsoft_v05_15_00_e9_prof/setup
#source /grid/fermiapp/products/larsoft/mrb/v1_07_03/bin/mrbSetEnv
source /grid/fermiapp/products/larsoft/mrb/v1_07_03/bin/setup_local_products

# copy the necessary files
mkdir -p ${_CONDOR_SCRATCH_DIR}/both/014466
cd ${_CONDOR_SCRATCH_DIR}/both/014466
copyfile /dune/app/users/wallbank/larsoft-base/workspace/35tanalysis/SliceAndFilter.fcl .
copyfile /dune/app/users/wallbank/larsoft-base/workspace/35tanalysis/reco_dune35tdata.fcl .
copyfile /dune/app/users/wallbank/larsoft-base/workspace/35tanalysis/apa_crossing.fcl .
copyfile /pnfs/lbne/pnfs/fnal.gov/usr/lbne/test-data/lbne/raw/00/63/86/01/lbne_r014466_sr01_20160304T000946.root .

echo
echo Contents of directory
ls
echo

# run the jobs
lar -c SliceAndFilter.fcl -s lbne_r014466_sr01_20160304T000946.root -o sliced_and_filtered.root
lar -c reco_dune35tdata.fcl -s sliced_and_filtered.root -o reco.root
lar -c apa_crossing.fcl -s reco.root

# copy output files back
rm -f lbne_r014466_sr01_20160304T000946.root
copyfile -r ${_CONDOR_SCRATCH_DIR}/both/014466 /dune/data/users/wallbank/Sliced_And_Filtered/both/014466

# remove the temp directory
rm -rf ${_CONDOR_SCRATCH_DIR}/both/014466

echo End of script

