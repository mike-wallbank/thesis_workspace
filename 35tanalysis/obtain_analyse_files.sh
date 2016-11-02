#!/bin/bash

# Script to get files out of samweb matching runs we're interested in and run analysis over them

if [ -z $1 ]; then
    echo
    echo "Please provide an input file with the run numbers of interest!"
    echo
fi

export OUTPUTDIRTAG=both_nofilter
export RUNFILE=both_nofilter_runs.txt
export FILTER=0

# make sure output dir is empty
export OUTDIR=/pnfs/dune/persistent/users/wallbank/Sliced_And_Filtered/${OUTPUTDIRTAG}
echo Ensuring empty output directory exists at $OUTDIR
touch $OUTDIR
chmod +xrw $OUTDIR
rm -rf $OUTDIR
mkdir $OUTDIR

RUNLIST=()

while read line; do

    # ignore the line if it's a comment or empty line
    if [[ $line == \#* ]] || [[ -z $line ]]; then
	continue
    fi
    # if the line is "STOP", stop processing
    if [[ $line == STOP ]]; then
	break
    fi

    RUNLIST=("${RUNLIST[@]}" $line)

done < "$1"

printf "%s\n" "${RUNLIST[@]}" > $RUNFILE

# submit job
num_jobs=${#RUNLIST[@]}
echo Submitting $num_jobs jobs

jobsub_submit -N $num_jobs -e MRB_INSTALL -e MRB_DIR -e RUNFILE -e FILTER -e OUTPUTDIRTAG -e OUTDIR --group=dune --use_gftp --resource-provides=usage_model=OPPORTUNISTIC file:///dune/app/users/wallbank/larsoft-base/workspace/35tanalysis/do_obtain_analyse_files.sh