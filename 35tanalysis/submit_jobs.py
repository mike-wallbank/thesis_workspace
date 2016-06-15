#!/bin/python

import os

for line in open("good_runs.txt"):
    file_name = line.strip()
    run = line.split("/")[7].split("_")[1]

    # write a job to submit to the grid
    job_file = open("jobs/job_"+str(run)+".sh",'w')
    job_file.write("#!/bin/bash\n")
    job_file.write("source /dune/app/users/wallbank/setup_prof.sh\n")

    # get a directory on /dune/data
    outDir = "/dune/data/users/wallbank/Sliced_And_Filtered/EW"+str(run)+"/"
    job_file.write("touch "+str(outDir)+"\n")
    job_file.write("rm -rf "+str(outDir)+"\n")
    job_file.write("mkdir "+str(outDir)+"\n")

    # copy to condor to execute
    condorDir = "${CONDOR_SCRATH_DIR}/EW/"+str(run)+"/"
    job_file.write("mkdir -p "+str(condorDir)+"\n")
    job_file.write("cd "+str(condorDir)+"\n")
    job_file.write("lar -c /dune/app/users/wallbank/larsoft-base/workspace/35tanalysis/SliceAndFilter.fcl -s "+str(file_name)+" -o "+str(outDir)+"sliced_and_filtered.root\n")
    job_file.write("lar -c /dune/app/users/wallbank/larsoft-base/workspace/35tanalysis/reco_dune35tdata.fcl -s "+str(outDir)+"sliced_and_filtered.root -o "+str(outDir)+"reco.root\n")

    # submit to grid
    os.system("chmod +x jobs/job_"+str(run)+".sh")
    os.system("jobsub_submit --group=dune --use_gftp --resource-provides=usage_model=OPPORTUNISTIC file:///dune/app/users/wallbank/larsoft-base/workspace/35tanalysis/jobs/job_"+str(run)+".sh")

#jobsub_submit --group=lbne --use_gftp --resource-provides=usage_model=OPPORTUNISTIC file://%s/jobSubmit.sh
