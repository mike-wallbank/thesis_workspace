#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"

const std::vector<int> kEnergyBins = {0,200,300,350,400,450,590,1000};

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
    hChargeHists[bin] = new TH1D(TString("ChargeDist")+TString(std::to_string(bin)),";Charge (ADC);",100,lowerCharge[bin]-100,upperCharge[bin]+100);
  }

  // Fill the histograms
  for (int event = 0; event < fTree->GetEntriesFast(); ++event) {
    fTree->GetEntry(event);
    int bin = GetEnergyBin(depositZ);
    hEnergyHists[bin]->Fill(depositZ);
    hChargeHists[bin]->Fill(correctedChargeZ);
  }

  // Analyse and write the histograms
  TGraph* energycharge = new TGraph();
  outFile->cd();
  for (int bin = 0; bin < kEnergyBins.size()-1; ++bin) {
    double energy = hEnergyHists[bin]->GetMean();
    hChargeHists[bin]->Fit("gaus");
    TF1* fit = hChargeHists[bin]->GetFunction("gaus");
    double charge = fit->GetParameter(1);
    hEnergyHists[bin]->Write();
    hChargeHists[bin]->Write();
    energycharge->SetPoint(energycharge->GetN(), charge, energy);
  }
  energycharge->SetNameTitle("EnergyCharge",";Charge (ADC);Energy (MeV);");
  energycharge->Write();

  for (int bin = 0; bin < kEnergyBins.size()-1; ++bin) {
    delete hEnergyHists[bin];
    delete hChargeHists[bin];
  }

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
