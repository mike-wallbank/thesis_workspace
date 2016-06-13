#!/usr/bin/python

# Script to look through output of tuningJob to make plots

import os
import ROOT
import operator

iteration = 1
permutations = int(os.popen("ls /lbne/data2/users/wallbank/blurredTuning/iteration%d | wc -l" % iteration).read())
print "There are ", permutations, " permutations to be looked at!"

hCompleteness    = ROOT.TH2F("Completeness","Completeness",1000,0,1000,101,0,1.01)
hCleanliness     = ROOT.TH2F("Cleanliness","Cleanliness",1000,0,1000,101,0,1.01)
hComplClean      = ROOT.TH2F("ComplClean","Completeness * Cleanliness",1000,0,1000,100,0,1.01)
hComplComplClean = ROOT.TH2F("ComplComplClean","Completeness^2 * Cleanliness",1000,0,1000,100,0,1.01)

metricBest = 0
permBest = 0
compBest = 0.
cleanBest = 0.

metricMap = {}

for perm in range(permutations-1):

    permutation = perm + 1
    os.chdir("/lbne/data2/users/wallbank/blurredTuning/iteration%d/%d/" % (iteration,permutation))

    if not os.path.exists("effpur"): continue
    print os.getcwd()

    completeness,cleanliness = [float(x) for x in open('effpur').read().strip("\n").split()]

    hCompleteness.Fill(permutation,completeness)
    hCleanliness.Fill(permutation,cleanliness)
    hComplClean.Fill(permutation,completeness * cleanliness)
    hComplComplClean.Fill(permutation,completeness * completeness * cleanliness)

    # Think of the metric
    metric = completeness * completeness * cleanliness
    #metric = completeness
    if metric > metricBest:
        metricBest = metric
        permBest = permutation
        compBest = completeness
        cleanBest = cleanliness
    metricMap[permutation] = metric

print "Best metric is permutation ", permBest, " with completeness ", compBest, " and cleanliness ", cleanBest

sorted_metrics = sorted(metricMap.items(), key=operator.itemgetter(1))
for perm in sorted_metrics:
    print perm

os.chdir("/lbne/app/users/wallbank/LArDev/workspace/blurredTuning")

c1 = ROOT.TCanvas("c1","",800,600)
hCompleteness.Draw()
c1.SaveAs("Completeness.png")

c2 = ROOT.TCanvas("c2","",800,600)
hCleanliness.Draw()
c2.SaveAs("Cleanliness.png")

c3 = ROOT.TCanvas("c3","",800,600)
hComplClean.Draw()
c3.SaveAs("ComplClean.png")

c4 = ROOT.TCanvas("c4","",800,600)
hComplComplClean.Draw()
c4.SaveAs("ComplComplClean.png")
