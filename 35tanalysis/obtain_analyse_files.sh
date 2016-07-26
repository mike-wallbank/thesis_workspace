#!/bin/bash

# Script to get files out of samweb matching runs we're interested in and run analysis over them

while read run; do

    # ignore the line if it's a comment or empty line
    if [[ $run == \#* ]] || [[ -z $run ]]; then
	continue
    fi

    echo Analysing run $run

    # get the file from sam web
    filename=`samweb list-files "run_number=$run and data_tier raw"`
    path=`samweb -e lbne get-file-access-url "$filename"`
    file=/pnfs/lbne${path:29}

    # get the directories
    outDir=/dune/data/users/wallbank/Sliced_And_Filtered/both/${run}
    condorDir='${_CONDOR_SCRATCH_DIR}'/both/${run}

    # make output dir
    touch ${outDir}
    rm -rf ${outDir}
    mkdir ${outDir}

    # write a script to run the job
    cat > "jobs/job_r${run}.sh" <<EOF
#!/bin/bash

echo Start of analysing run $run

alias copyfile="ifdh cp --force=expgridftp"

# setup the software
source /grid/fermiapp/products/dune/setup_dune.sh
source ${MRB_INSTALL}/setup
#source ${MRB_DIR}/bin/mrbSetEnv
source ${MRB_DIR}/bin/setup_local_products

# copy the necessary files
mkdir -p $condorDir
cd $condorDir
copyfile /dune/app/users/wallbank/larsoft-base/workspace/35tanalysis/SliceAndFilter.fcl .
copyfile /dune/app/users/wallbank/larsoft-base/workspace/35tanalysis/reco_dune35tdata.fcl .
copyfile /dune/app/users/wallbank/larsoft-base/workspace/35tanalysis/apa_crossing.fcl .
copyfile $file .

echo
echo Contents of directory
ls
echo

# run the jobs
lar -c SliceAndFilter.fcl -s $filename -o sliced_and_filtered.root
lar -c reco_dune35tdata.fcl -s sliced_and_filtered.root -o reco.root
lar -c apa_crossing.fcl -s reco.root

# copy output files back
rm -f $filename
copyfile -r $condorDir $outDir

# remove the temp directory
rm -rf $condorDir

echo End of script

EOF

    # submit job
    chmod +x jobs/job_r${run}.sh
    jobsub_submit --group=dune --use_gftp --resource-provides=usage_model=OPPORTUNISTIC file:///dune/app/users/wallbank/larsoft-base/workspace/35tanalysis/jobs/job_r${run}.sh

done < good_runs.txt