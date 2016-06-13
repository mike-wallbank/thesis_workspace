#!/bin/bash
touch /dune/data/users/wallbank/Sliced_And_Filtered/r014462/
rm -rf /dune/data/users/wallbank/Sliced_And_Filtered/r014462/
mkdir /dune/data/users/wallbank/Sliced_And_Filtered/r014462/
source /dune/app/users/wallbank/setup_prof.sh
lar -c /dune/app/users/wallbank/larsoft-base/workspace/35tanalysis/SliceAndFilter.fcl -s /dune/app/users/abooth/winter/EventFilter/lbne_r014462_sr01_20160304T000000.root -o /dune/data/users/wallbank/Sliced_And_Filtered/r014462/sliced_and_filtered.root
lar -c /dune/app/users/wallbank/larsoft-base/workspace/35tanalysis/reco_dune35tdata.fcl -s /dune/data/users/wallbank/Sliced_And_Filtered/r014462/sliced_and_filtered.root -o /dune/data/users/wallbank/Sliced_And_Filtered/r014462/reco.root
