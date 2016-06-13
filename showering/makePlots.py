#!/bin/python

import ROOT

# Open the two files

electron_colour = 1
photon_colour = 2

version = str(raw_input("Which LArSoft version would you like to make plots for? (v05_11_01) ") or "v05_11_01")

electronFile = ROOT.TFile.Open(version+"/electronana.root")
photonFile = ROOT.TFile.Open(version+"/photonana.root")

electron_dEdx = electronFile.Get("showerAnalysis/ShowerdEdx")
electron_dEdx_energy = electronFile.Get("showerAnalysis/ShowerdEdxEnergy")
electron_energy_completeness = electronFile.Get("showerAnalysis/ShowerEnergyCompleteness")
electron_recon_shower_energy = electronFile.Get("showerAnalysis/ShowerReconstructedEnergyProfile")
electron_num_recon_shower_energy = electronFile.Get("showerAnalysis/NumShowersReconstructedEnergy")
electron_num_recon_shower = electronFile.Get("showerAnalysis/NumShowersReconstructedNonZero")
electron_energy = electronFile.Get("showerAnalysis/ShowerEnergy")
electron_deposited_energy = electronFile.Get("showerAnalysis/ShowerDepositedEnergy")
electron_direction = electronFile.Get("showerAnalysis/ShowerDirection")
electron_start = electronFile.Get("showerAnalysis/ShowerStart")
electron_electronpull = electronFile.Get("showerAnalysis/ElectronPull")
electron_photonpull = electronFile.Get("showerAnalysis/PhotonPull")

photon_dEdx = photonFile.Get("showerAnalysis/ShowerdEdx")
photon_dEdx_energy = photonFile.Get("showerAnalysis/ShowerdEdxEnergy")
photon_energy_completeness = photonFile.Get("showerAnalysis/ShowerEnergyCompleteness")
photon_recon_shower_energy = photonFile.Get("showerAnalysis/ShowerReconstructedEnergyProfile")
photon_num_recon_shower_energy = photonFile.Get("showerAnalysis/NumShowersReconstructedEnergy")
photon_num_recon_shower = photonFile.Get("showerAnalysis/NumShowersReconstructedNonZero")
photon_energy = photonFile.Get("showerAnalysis/ShowerEnergy")
photon_deposited_energy = photonFile.Get("showerAnalysis/ShowerDepositedEnergy")
photon_direction = photonFile.Get("showerAnalysis/ShowerDirection")
photon_start = photonFile.Get("showerAnalysis/ShowerStart")
photon_electronpull = photonFile.Get("showerAnalysis/ElectronPull")
photon_photonpull = photonFile.Get("showerAnalysis/PhotonPull")

canvas = ROOT.TCanvas()
outFile = ROOT.TFile.Open("shower_performance.root","RECREATE")

canvas.Clear()
electron_dEdx.SetLineColor(electron_colour)
photon_dEdx.SetLineColor(photon_colour)
canvas.cd()
electron_dEdx.Draw()
photon_dEdx.Draw("same")
electron_dEdx.SetStats(0)
photon_dEdx.SetStats(0)
legend = ROOT.TLegend(0.65,0.7,0.88,0.88)
legend.AddEntry(electron_dEdx,"Electron","l")
legend.AddEntry(photon_dEdx,"Photon","l")
legend.Draw()
outFile.cd()
canvas.Write("dEdx")

canvas.Clear()
electron_dEdx_norm = electron_dEdx.Clone("electron_dEdx_norm")
electron_dEdx_norm.Scale(1./electron_dEdx.Integral())
photon_dEdx_norm = photon_dEdx.Clone("photon_dEdx_norm")
photon_dEdx_norm.Scale(1./photon_dEdx.Integral())
electron_dEdx_norm.SetLineColor(electron_colour)
electron_dEdx_norm.Fit("gaus","","",1,3)
photon_dEdx_norm.SetLineColor(photon_colour)
photon_dEdx_norm.Fit("gaus","","",2,7)
canvas.cd()
electron_dEdx_norm.Draw()
photon_dEdx_norm.Draw("same")
electron_dEdx_norm.SetStats(0)
photon_dEdx_norm.SetStats(0)
legend = ROOT.TLegend(0.65,0.7,0.88,0.88)
legend.AddEntry(electron_dEdx_norm,"Electron","l")
legend.AddEntry(photon_dEdx_norm,"Photon","l")
legend.Draw()
outFile.cd()
canvas.Write("dEdx_norm")

canvas.Clear()
electron_dEdx_energy.SetMarkerStyle(8)
electron_dEdx_energy.SetMarkerSize(0.25)
electron_dEdx_energy.SetMarkerColor(electron_colour)
photon_dEdx_energy.SetMarkerStyle(8)
photon_dEdx_energy.SetMarkerSize(0.25)
photon_dEdx_energy.SetMarkerColor(photon_colour)
canvas.cd()
electron_dEdx_energy.Draw()
photon_dEdx_energy.Draw("same")
electron_dEdx_energy.SetStats(0)
photon_dEdx_energy.SetStats(0)
legend = ROOT.TLegend(0.65,0.7,0.88,0.88)
legend.AddEntry(electron_dEdx_energy,"Electron","l")
legend.AddEntry(photon_dEdx_energy,"Photon","l")
legend.Draw()
outFile.cd()
canvas.Write("dEdx_energy")

canvas.Clear()
electron_energy.SetLineColor(electron_colour)
photon_energy.SetLineColor(photon_colour)
canvas.cd()
electron_energy.Draw()
photon_energy.Draw("same")
electron_energy.SetStats(0)
photon_energy.SetStats(0)
legend = ROOT.TLegend(0.12,0.7,0.35,0.88)
legend.AddEntry(electron_energy,"Electron","l")
legend.AddEntry(photon_energy,"Photon","l")
legend.Draw()
outFile.cd()
canvas.Write("energy")

canvas.Clear()
electron_energy_completeness.SetMarkerColor(electron_colour)
photon_energy_completeness.SetMarkerColor(photon_colour)
canvas.cd()
electron_energy_completeness.Draw()
photon_energy_completeness.Draw("same")
electron_energy_completeness.SetStats(0)
photon_energy_completeness.SetStats(0)
legend = ROOT.TLegend(0.12,0.7,0.35,0.88)
legend.AddEntry(electron_energy_completeness,"Electron","pe")
legend.AddEntry(photon_energy_completeness,"Photon","pe")
legend.Draw()
outFile.cd()
canvas.Write("energy_completeness")

canvas.Clear()
electron_deposited_energy.SetLineColor(electron_colour)
photon_deposited_energy.SetLineColor(photon_colour)
canvas.cd()
electron_deposited_energy.Draw()
photon_deposited_energy.Draw("same")
electron_deposited_energy.SetStats(0)
photon_deposited_energy.SetStats(0)
legend = ROOT.TLegend(0.12,0.7,0.35,0.88)
legend.AddEntry(electron_deposited_energy,"Electron","l")
legend.AddEntry(photon_deposited_energy,"Photon","l")
legend.Draw()
outFile.cd()
canvas.Write("deposited_energy")

canvas.Clear()
electron_direction.SetLineColor(electron_colour)
photon_direction.SetLineColor(photon_colour)
canvas.cd()
electron_direction.Draw()
photon_direction.Draw("same")
electron_direction.SetStats(0)
photon_direction.SetStats(0)
legend = ROOT.TLegend(0.12,0.7,0.35,0.88)
legend.AddEntry(electron_direction,"Electron","l")
legend.AddEntry(photon_direction,"Photon","l")
legend.Draw()
outFile.cd()
canvas.Write("direction")

canvas.Clear()
electron_direction.SetLineColor(electron_colour)
photon_direction.SetLineColor(photon_colour)
canvas.cd()
canvas.SetLogy()
electron_direction.Draw()
photon_direction.Draw("same")
legend = ROOT.TLegend(0.12,0.7,0.35,0.88)
legend.AddEntry(electron_direction,"Electron","l")
legend.AddEntry(photon_direction,"Photon","l")
legend.Draw()
outFile.cd()
canvas.Write("direction_log")
canvas.SetLogy(0)

canvas.Clear()
electron_start.SetLineColor(electron_colour)
photon_start.SetLineColor(photon_colour)
canvas.cd()
electron_start.Draw()
photon_start.Draw("same")
electron_start.SetStats(0)
photon_start.SetStats(0)
legend = ROOT.TLegend(0.65,0.7,0.88,0.88)
legend.AddEntry(electron_start,"Electron","l")
legend.AddEntry(photon_start,"Photon","l")
legend.Draw()
outFile.cd()
canvas.Write("start")

canvas.Clear()
electron_start.SetLineColor(electron_colour)
photon_start.SetLineColor(photon_colour)
canvas.cd()
canvas.SetLogy()
electron_start.Draw()
photon_start.Draw("same")
legend = ROOT.TLegend(0.65,0.7,0.88,0.88)
legend.AddEntry(electron_start,"Electron","l")
legend.AddEntry(photon_start,"Photon","l")
legend.Draw()
outFile.cd()
canvas.Write("start_log")
canvas.SetLogy(0)

canvas.Clear()
electron_num_recon_shower.SetLineColor(electron_colour)
photon_num_recon_shower.SetLineColor(photon_colour)
canvas.cd()
photon_num_recon_shower.Draw()
electron_num_recon_shower.Draw("same")
electron_num_recon_shower.SetStats(0)
photon_num_recon_shower.SetStats(0)
legend = ROOT.TLegend(0.65,0.7,0.88,0.88)
legend.AddEntry(electron_num_recon_shower,"Electron","l")
legend.AddEntry(photon_num_recon_shower,"Photon","l")
legend.Draw()
outFile.cd()
canvas.Write("num_recon_shower")

canvas.Clear()
electron_recon_shower_energy.SetMarkerColor(electron_colour)
photon_recon_shower_energy.SetMarkerColor(photon_colour)
electron_recon_shower_energy.SetLineColor(electron_colour)
photon_recon_shower_energy.SetLineColor(photon_colour)
canvas.cd()
electron_recon_shower_energy.Draw()
photon_recon_shower_energy.Draw("same")
electron_recon_shower_energy.SetStats(0)
photon_recon_shower_energy.SetStats(0)
legend = ROOT.TLegend(0.65,0.12,0.88,0.3)
legend.AddEntry(electron_recon_shower_energy,"Electron","pe")
legend.AddEntry(photon_recon_shower_energy,"Photon","pe")
legend.Draw()
outFile.cd()
canvas.Write("recon_shower_energy")

canvas.Clear()
electron_num_recon_shower_energy.SetMarkerColor(electron_colour)
photon_num_recon_shower_energy.SetMarkerColor(photon_colour)
canvas.cd()
electron_num_recon_shower_energy.Draw()
photon_num_recon_shower_energy.Draw("same")
electron_num_recon_shower_energy.SetStats(0)
photon_num_recon_shower_energy.SetStats(0)
legend = ROOT.TLegend(0.65,0.7,0.88,0.88)
legend.AddEntry(electron_num_recon_shower_energy,"Electron","l")
legend.AddEntry(photon_num_recon_shower_energy,"Photon","l")
legend.Draw()
outFile.cd()
canvas.Write("num_recon_shower_energy")

canvas.Clear()
electron_electronpull.SetLineColor(electron_colour)
photon_electronpull.SetLineColor(photon_colour)
canvas.cd()
electron_electronpull.Draw()
photon_electronpull.Draw("same")
electron_electronpull.SetStats(0)
photon_electronpull.SetStats(0)
legend = ROOT.TLegend(0.65,0.7,0.88,0.88)
legend.AddEntry(electron_electronpull,"Electron","l")
legend.AddEntry(photon_electronpull,"Photon","l")
legend.Draw()
outFile.cd()
canvas.Write("electron_pull")

canvas.Clear()
electron_photonpull.SetLineColor(electron_colour)
photon_photonpull.SetLineColor(photon_colour)
canvas.cd()
electron_photonpull.Draw()
photon_photonpull.Draw("same")
electron_photonpull.SetStats(0)
photon_photonpull.SetStats(0)
legend = ROOT.TLegend(0.65,0.7,0.88,0.88)
legend.AddEntry(electron_photonpull,"Electron","l")
legend.AddEntry(photon_photonpull,"Photon","l")
legend.Draw()
outFile.cd()
canvas.Write("photon_pull")

# Now let's do a bit of pull analysis
# Look at the dEdx plot as a whole
# then at each pull plot separately
efficiency_power = 1
purity_power = 2

# Find the cut on the dEdx plot which maximises both purities
best_metric = 0.
best_electron_purity = 0.
best_photon_purity = 0.
best_electron_efficiency = 0.
best_photon_efficiency = 0.
cut = 0.
for binIt in range(electron_dEdx.GetNbinsX()):
    bin = binIt + 1
    electron_integral1 = electron_dEdx.Integral(1,bin)
    photon_integral1 = photon_dEdx.Integral(1,bin)
    electron_integral2 = electron_dEdx.Integral(bin,electron_dEdx.GetNbinsX())
    photon_integral2 = photon_dEdx.Integral(bin,photon_dEdx.GetNbinsX())
    if electron_integral1 + photon_integral1 == 0: 
        electron_purity = 0
    else:
        electron_purity = electron_integral1 / (electron_integral1 + photon_integral1)
    if electron_integral2 + photon_integral2 == 0: 
        photon_purity = 0
    else:
        photon_purity = photon_integral2 / (electron_integral2 + photon_integral2)
    electron_efficiency = electron_integral1 / electron_dEdx.Integral()
    photon_efficiency = photon_integral2 / photon_dEdx.Integral()
    metric = ROOT.TMath.Power(electron_purity,purity_power) * ROOT.TMath.Power(electron_efficiency,efficiency_power) * ROOT.TMath.Power(photon_purity,purity_power) * ROOT.TMath.Power(photon_efficiency,efficiency_power)
    if metric > best_metric:
        best_metric = metric
        best_electron_purity = electron_purity
        best_photon_purity = photon_purity
        best_electron_efficiency = electron_efficiency
        best_photon_efficiency = photon_efficiency
        cut = electron_dEdx.GetBinCenter(bin)

print "Single cut: cutting at dEdx =", cut, "gives electron purity of", best_electron_purity, "and efficiency of", best_electron_efficiency, "; photon purity of", best_photon_purity, "and efficiency of", best_photon_efficiency

# Look at the pulls separately

# electron
best_metric = 0.
best_purity = 0.
best_efficiency = 0.
cut = 0.
for binIt in range(electron_electronpull.GetNbinsX()):
    bin = binIt + 1
    electron_integral = electron_electronpull.Integral(1,bin)
    photon_integral = photon_electronpull.Integral(1,bin)
    if electron_integral + photon_integral == 0: 
        electron_purity = 0
    else:
        electron_purity = electron_integral / (electron_integral + photon_integral)
    electron_efficiency = electron_integral / electron_electronpull.Integral()
    metric = ROOT.TMath.Power(electron_efficiency,efficiency_power) * ROOT.TMath.Power(electron_purity,purity_power)
    if metric > best_metric:
        best_metric = metric
        best_efficiency = electron_efficiency
        best_purity = electron_purity
        cut = electron_electronpull.GetBinCenter(bin)

print "Electron cut: cutting at pull =", cut, "gives electron purity of", best_purity, "and efficiency of", best_efficiency

# photon
best_metric = 0.
best_purity = 0.
best_efficiency = 0.
cut = 0.
for binIt in range(photon_photonpull.GetNbinsX()):
    bin = binIt + 1
    electron_integral = electron_photonpull.Integral(bin,photon_photonpull.GetNbinsX())
    photon_integral = photon_photonpull.Integral(bin,photon_photonpull.GetNbinsX())
    if electron_integral + photon_integral == 0: 
        photon_purity = 0
    else:
        photon_purity = photon_integral / (electron_integral + photon_integral)
    photon_efficiency = photon_integral / photon_photonpull.Integral()
    metric = ROOT.TMath.Power(photon_efficiency,efficiency_power) * ROOT.TMath.Power(photon_purity,purity_power)
    if metric > best_metric:
        best_metric = metric
        best_efficiency = photon_efficiency
        best_purity = photon_purity
        cut = photon_photonpull.GetBinCenter(bin)

print "Photon cut: cutting at pull =", cut, "gives photon purity of", best_purity, "and efficiency of", best_efficiency
