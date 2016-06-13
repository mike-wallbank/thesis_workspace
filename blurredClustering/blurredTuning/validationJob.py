#!/usr/bin/python

import os, time

iteration = 1
directory = "/lbne/data2/users/wallbank/blurredTuning/iteration%d/" % iteration

permutations = int(os.popen("ls %s | wc -l" % directory).read())

it = 0

for perm in range(permutations):

    permutation = perm + 1

    os.chdir(directory+str(permutation))

    file = open("validation.sh","w")
    file.write("#!/bin/bash")

    # Setup software
    file.write("\nsource /grid/fermiapp/lbne/software/setup_lbne.sh")
    file.write("\nsource /lbne/app/users/wallbank/LArDev/localProducts_larsoft*/setup")
    file.write("\nmrbsetenv")
    file.write("\nmrbslp")

    # Run reconstruction and validation
    file.write("\nscp /lbne/app/users/wallbank/LArDev/workspace/testingBlurred/blurredvalidation.fcl .")
    file.write("\nlar -c blurredvalidation.fcl -s blurredReco.root")

    file.close()

    # Submit job
    #njobs = os.system("jobsub_q --user=wallbank | wc -l")
    os.system("chmod u+x validation.sh")
    os.system("jobsub_submit --group=lbne --use_gftp --resource-provides=usage_model=OPPORTUNISTIC file://%s/validation.sh" % (directory+str(permutation)))
