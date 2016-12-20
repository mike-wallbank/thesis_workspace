#!/bin/bash

if [ "$#" -ne 1 ]; then
    echo
    echo "Error: incorrect number of parameters provided."
    echo "Usage: ./addFiles.sh vXX_YY_ZZ"
    echo
    return 1
fi

hadd /pnfs/dune/scratch/users/wallbank/$1/mva_nue_dune10kt_1x2x6/mva_train.root /pnfs/dune/scratch/users/wallbank/$1/mva_nue_dune10kt_1x2x6/mva_nue_dune10kt_1x2x6_nu/anahist.root /pnfs/dune/scratch/users/wallbank/$1/mva_nue_dune10kt_1x2x6/mva_nue_dune10kt_1x2x6_nue/anahist.root /pnfs/dune/scratch/users/wallbank/$1/mva_nue_dune10kt_1x2x6/mva_nue_dune10kt_1x2x6_nutau/anahist.root