#!/bin/bash

if [ "$#" -ne 1 ]; then
    echo
    echo "Error: incorrect number of parameters provided."
    echo "Usage: ./addFiles.sh vXX_YY_ZZ"
    echo
    return 1
fi

if [ -e /pnfs/dune/scratch/users/wallbank/$1/mva_anue_dune10kt_1x2x6/mva_anue_train.root ]
then
    echo "File at /pnfs/dune/scratch/users/wallbank/$1/mva_anue_dune10kt_1x2x6/mva_anue_train.root already exists... overwrite? [y/n] "
    read answer
    if [ $answer != "y" ]
    then
	exit
    fi
fi

hadd -f /pnfs/dune/scratch/users/wallbank/$1/mva_anue_dune10kt_1x2x6/mva_anue_train.root /pnfs/dune/scratch/users/wallbank/$1/mva_anue_dune10kt_1x2x6/mva_anue_train_dune10kt_1x2x6_anu/anahist.root /pnfs/dune/scratch/users/wallbank/$1/mva_anue_dune10kt_1x2x6/mva_anue_train_dune10kt_1x2x6_anue/anahist.root /pnfs/dune/scratch/users/wallbank/$1/mva_anue_dune10kt_1x2x6/mva_anue_train_dune10kt_1x2x6_anutau/anahist.root