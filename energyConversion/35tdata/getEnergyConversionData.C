#include "TFile.h"
#include "TTree.h"
#include "TGraphErrors.h"
#include "TH1D.h"

const std::vector<int> kEnergyBins = {0,200,300,350,400,450,1000};
//const std::vector<int> kEnergyBins = {0,200,300,350,400,450};

class EMEnergyConversion {
public:

  EMEnergyConversion(TTree* tree);
  ~EMEnergyConversion();

  int GetEnergyBin(double energy);
  void Run();

private:

  TTree* fTree;

  double depositU, depositV, depositZ;
  double correctedChargeU, correctedChargeV, correctedChargeZ;
  int nhits;

  std::vector<TH1D*> hChargeHists, hEnergyHists;

  TFile* outFile;

};

EMEnergyConversion::EMEnergyConversion(TTree* tree) {

  fTree = tree;
  fTree->SetBranchAddress("NHits", &nhits);
  fTree->SetBranchAddress("DepositU", &depositU);
  fTree->SetBranchAddress("DepositV", &depositV);
  fTree->SetBranchAddress("DepositZ", &depositZ);
  fTree->SetBranchAddress("CorrectedChargeU", &correctedChargeU);
  fTree->SetBranchAddress("CorrectedChargeV", &correctedChargeV);
  fTree->SetBranchAddress("CorrectedChargeZ", &correctedChargeZ);

  outFile = TFile::Open("EnergyFits.root","RECREATE");

}

EMEnergyConversion::~EMEnergyConversion() {
  outFile->Close();
  delete outFile;
}

int EMEnergyConversion::GetEnergyBin(double energy) {

  int energyBin = -999;

  for (int bin = 0; bin < kEnergyBins.size()-1; ++bin)
    if (energy >= kEnergyBins[bin] and energy < kEnergyBins[bin+1])
      energyBin = bin;

  if (energyBin == -999) {
    if (energy < kEnergyBins[0])
      energyBin = 0;
    if (energy >= kEnergyBins[kEnergyBins.size()-1])
      energyBin = kEnergyBins.size() - 1;
  }

  if (energyBin == -999) {
    std::cout << "Logic getting energy bin has failed!" << std::endl;
    throw;
  }

  return energyBin;

}

void EMEnergyConversion::Run() {

  // Get the charge range for each bin
  std::vector<double> lowerCharge(kEnergyBins.size()-1,1e10), upperCharge(kEnergyBins.size()-1,0);
  for (int event = 0; event < fTree->GetEntriesFast(); ++event) {
    fTree->GetEntry(event);
    int bin = GetEnergyBin(depositZ);
    if (correctedChargeZ < lowerCharge[bin]) lowerCharge[bin] = correctedChargeZ;
    if (correctedChargeZ > upperCharge[bin]) upperCharge[bin] = correctedChargeZ;
  }

  // Make the histograms
  hEnergyHists.reserve(kEnergyBins.size()-1);
  hChargeHists.reserve(kEnergyBins.size()-1);
  for (int bin = 0; bin < kEnergyBins.size()-1; ++bin) {
    hEnergyHists[bin] = new TH1D(TString("EnergyDist")+TString(std::to_string(bin)),";Energy (MeV);",100,kEnergyBins[bin],kEnergyBins[bin+1]);
    hChargeHists[bin] = new TH1D(TString("ChargeDist")+TString(std::to_string(bin)),";Charge (ADC);",40,lowerCharge[bin]-100,TMath::Min(upperCharge[bin]+100,1e6));
  }

  // Fill the histograms
  for (int event = 0; event < fTree->GetEntriesFast(); ++event) {
    fTree->GetEntry(event);
    if (depositZ == 0 or correctedChargeZ == 0)
      continue;
    if (nhits < 20 or nhits > 100)
      continue;
    int bin = GetEnergyBin(depositZ);
    hEnergyHists[bin]->Fill(depositZ);
    hChargeHists[bin]->Fill(correctedChargeZ);
  }

  // Analyse and write the histograms
  TGraphErrors* energycharge = new TGraphErrors();
  outFile->cd();
  for (int bin = 0; bin < kEnergyBins.size()-1; ++bin) {
    double energy = hEnergyHists[bin]->GetMean();
    double charge_mean = hChargeHists[bin]->GetMean();
    double charge_rms = hChargeHists[bin]->GetRMS();
    hChargeHists[bin]->Fit("gaus","","",charge_mean-2*charge_rms,charge_mean+2*charge_rms);
    TF1* fit = hChargeHists[bin]->GetFunction("gaus");
    double charge = fit->GetParameter(1);
    double charge_width = fit->GetParameter(2);
    hEnergyHists[bin]->Write();
    hChargeHists[bin]->Write();
    int point = energycharge->GetN();
    energycharge->SetPoint(point, charge, energy);
    energycharge->SetPointError(point, charge_width, hEnergyHists[bin]->GetRMS());
  }
  energycharge->SetNameTitle("EnergyCharge",";Charge (ADC);Energy (MeV);");
  energycharge->SetMarkerStyle(8);
  energycharge->SetMarkerSize(1);
  energycharge->Fit("pol1");
  energycharge->Write();
  fit = energycharge->GetFunction("pol1");
  std::pair<double,double> fitParameters = std::make_pair(fit->GetParameter(0), fit->GetParameter(1));
  delete fit;
  delete energycharge;

  for (int bin = 0; bin < kEnergyBins.size()-1; ++bin) {
    delete hEnergyHists[bin];
    delete hChargeHists[bin];
  }

  std::cout << "Fit parameters are gradient " << fitParameters.second << " and intercept " << fitParameters.first << std::endl;

  return;

}

void getEnergyConversionData() {

  //gStyle->SetOptStat(0);
  TFile* inFile = TFile::Open("hit_maps.root");
  TTree* tree = (TTree*)inFile->Get("apacrossing/TrackProperties");

  EMEnergyConversion emenergyconv = EMEnergyConversion(tree);
  emenergyconv.Run();

  inFile->Close();
  inFile->Delete();

}
