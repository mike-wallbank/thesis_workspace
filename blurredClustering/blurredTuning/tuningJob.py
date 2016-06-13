#!/usr/bin/python

# Tuning Blurred Clustering within LArSoft. Loop over various parameter combinations and run the reconstruction for them

import os, time

BlurWireList            = [4,8,12,16]
BlurTickList            = [4,8,12,16]
BlurSigmaList           = [1,2,3,4,5]
ClusterWireDistanceList = [1,2,3,4,5]
ClusterTickDistanceList = [1,2,3,4,5]
TimeThresholdList       = [20]
NeighboursThresholdList = [0]
MinNeighboursList       = [0]
MinSizeList             = [0]
MinSeedList             = [0.1]
ChargeThresholdList     = [0.05]

directory = "/lbne/data2/users/wallbank/blurredTuning/iteration1/"

it = 0

for BlurWire in BlurWireList:
    for BlurTick in BlurTickList:
        for BlurSigma in BlurSigmaList:
            for ClusterWireDistance in ClusterWireDistanceList:
                for ClusterTickDistance in ClusterTickDistanceList:
                    for TimeThreshold in TimeThresholdList:
                        for NeighboursThreshold in NeighboursThresholdList:
                            for MinNeighbours in MinNeighboursList:
                                for MinSize in MinSizeList:
                                    for MinSeed in MinSeedList:
                                        for ChargeThreshold in ChargeThresholdList:

                                            # Change implementation to these parameters and make jobs here
                                            it += 1

                                            # Make a directory to hold the results of this parameter permutation
                                            os.mkdir(directory+str(it))
                                            os.chdir(directory+str(it))
                                            os.system("cp /lbne/app/users/wallbank/LArDev/workspace/blurredTuning/reco_lbne35t_blur.fcl .")
                                            
                                            # Append the standard reco file with the new parameters
                                            file = open("reco_lbne35t_blur.fcl",'a')
                                            file.write("\n\n")
                                            file.write("\nphysics.producers.blurredclusteringdc.BlurredClusteringAlg.BlurWire:            %f" % BlurWire)
                                            file.write("\nphysics.producers.blurredclusteringdc.BlurredClusteringAlg.BlurTick:            %f" % BlurTick)
                                            file.write("\nphysics.producers.blurredclusteringdc.BlurredClusteringAlg.BlurSigma:           %f" % BlurSigma)
                                            file.write("\nphysics.producers.blurredclusteringdc.BlurredClusteringAlg.ClusterWireDistance: %f" % ClusterWireDistance)
                                            file.write("\nphysics.producers.blurredclusteringdc.BlurredClusteringAlg.ClusterTickDistance: %f" % ClusterTickDistance)
                                            file.write("\nphysics.producers.blurredclusteringdc.BlurredClusteringAlg.NeighboursThreshold: %f" % NeighboursThreshold)
                                            file.write("\nphysics.producers.blurredclusteringdc.BlurredClusteringAlg.MinNeighbours:       %f" % MinNeighbours)
                                            file.write("\nphysics.producers.blurredclusteringdc.BlurredClusteringAlg.MinSize:             %f" % MinSize)
                                            file.write("\nphysics.producers.blurredclusteringdc.BlurredClusteringAlg.MinSeed:             %f" % MinSeed)
                                            file.write("\nphysics.producers.blurredclusteringdc.BlurredClusteringAlg.TimeThreshold:       %f" % TimeThreshold)
                                            file.write("\nphysics.producers.blurredclusteringdc.BlurredClusteringAlg.ChargeThreshold:     %f" % ChargeThreshold)
                                            file.close()

                                            # Write a job submission sript to run the loops over
                                            file = open('jobSubmit.sh','w')

                                            file.write("#!/bin/bash")

                                            # Setup software
                                            file.write("\nsource /grid/fermiapp/lbne/software/setup_lbne.sh")
                                            file.write("\nsource /lbne/app/users/wallbank/LArDev/localProducts_larsoft*/setup")
                                            file.write("\ncd /lbne/app/users/wallbank/LArDev/build*")
                                            file.write("\nmrbsetenv")
                                            file.write("\nmrbslp")
                                            
                                            # Run reconstruction and validation
                                            file.write("\nmkdir -p ${_CONDOR_SCRATCH_DIR}/%d" % it)
                                            file.write("\ncd ${_CONDOR_SCRATCH_DIR}/%d" % it)
                                            file.write("\nscp /lbne/data2/users/wallbank/evs*.root .")
                                            file.write("\nscp %s/reco_lbne35t_blur.fcl ." % (directory+str(it)))
                                            file.write("\nscp /lbne/app/users/wallbank/LArDev/workspace/blurredTuning/blurredvalidation.fcl .")
                                            file.write("\nlar -c ./reco_lbne35t_blur.fcl -s evs*.root -n 50 -o blurredReco.root")
                                            file.write("\nlar -c blurredvalidation.fcl -s blurredReco.root")
                                            file.write("\nrm -f evs*.root")
                                            file.write("\nifdh cp -r --force=expgridftp ${_CONDOR_SCRATCH_DIR}/%d %s" % (it,directory+str(it)))
                                            
                                            file.close()

                                            # Submit job
                                            os.system("chmod u+x jobSubmit.sh")
                                            os.system("jobsub_submit --group=lbne --use_gftp --resource-provides=usage_model=OPPORTUNISTIC file://%s/jobSubmit.sh" % (directory+str(it)))
