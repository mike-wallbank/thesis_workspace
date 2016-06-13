#!/bin/bash
touch /dune/data/users/wallbank/Sliced_And_Filtered/r014456/
rm -rf /dune/data/users/wallbank/Sliced_And_Filtered/r014456/
mkdir /dune/data/users/wallbank/Sliced_And_Filtered/r014456/
source /dune/app/users/wallbank/setup_prof.sh
lar -c /dune/app/users/wallbank/larsoft-base/workspace/35tanalysis/SliceAndFilter.fcl -s /dune/app/users/abooth/winter/EventFilter/lbne_r014456_sr01_20160303T234342.root -o /dune/data/users/wallbank/Sliced_And_Filtered/r014456/sliced_and_filtered.root
lar -c /dune/app/users/wallbank/larsoft-base/workspace/35tanalysis/reco_dune35tdata.fcl -s /dune/data/users/wallbank/Sliced_And_Filtered/r014456/sliced_and_filtered.root -o /dune/data/users/wallbank/Sliced_And_Filtered/r014456/reco.root
