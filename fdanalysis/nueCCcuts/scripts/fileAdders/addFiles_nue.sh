#!/bin/bash

if [ "$#" -ne 1 ]; then
    echo
    echo "Error: incorrect number of parameters provided."
    echo "Usage: ./addFiles.sh vXX_YY_ZZ"
    echo
    return 1
fi

if [ -e /pnfs/dune/persistent/users/wallbank/$1/selection_nue_dune10kt_1x2x6/selection_nue.root ]
then
    echo "File at /pnfs/dune/persistent/users/wallbank/$1/selection_nue_dune10kt_1x2x6/selection_nue.root already exists... overwrite? [y/n] "
    read answer
    if [ $answer != "y" ]
    then
	exit
    fi
fi

hadd -f /pnfs/dune/persistent/users/wallbank/$1/selection/selection_nue.root /pnfs/dune/persistent/users/wallbank/$1/selection/selection_nue_dune10kt_1x2x6_nu/anahist.root /pnfs/dune/persistent/users/wallbank/$1/selection/selection_nue_dune10kt_1x2x6_nue/anahist.root /pnfs/dune/persistent/users/wallbank/$1/selection/selection_nue_dune10kt_1x2x6_nutau/anahist.root