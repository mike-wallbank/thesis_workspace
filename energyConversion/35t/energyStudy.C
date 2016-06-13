#include <map>

void energyStudy() {

  const int kMaxClusters = 100;

  TFile *inFile = TFile::Open("EMPi0Energy.root");
  TFile *outFile = TFile::Open("Pi0Energy.root","RECREATE");
  TTree *tree = inFile->Get("energyPi0/EMPi0Energy");

  double TrueEnergyPi0;
  double TrueEnergyHighEPhoton;
  double TrueEnergyLowEPhoton;
  int    TrueTrackIDPi0;
  int    TrueTrackIDHighEPhoton;
  int    TrueTrackIDLowEPhoton;
  double DepositHighEPhoton;
  double DepositLowEPhoton;
  double VertexDetectorDistHighEPhoton;
  double VertexDetectorDistLowEPhoton;
  int    NClusters;
  int    Cluster_Plane      [kMaxClusters];
  int    Cluster_Size       [kMaxClusters];
  int    Cluster_TrueTrackID[kMaxClusters];
  double Cluster_Charge     [kMaxClusters];
  double Cluster_Energy     [kMaxClusters];

  TH1D* hEnergyCompleteness = new TH1D("EnergyCompleteness","Fraction of Energy Deposited Reconstructed in the Largest Cluster (for both photons);Energy Completeness;",121,0,1.21);
  TH2D* hEnergyCompletenessEnergy = new TH2D("EnergyCompletenessEnergy","Completeness as Function of Photon Energy;Photon Energy;Energy Completeness;",100,0,1,101,0,1.01);

  tree->SetBranchAddress("TrueEnergyPi0",                &TrueEnergyPi0);
  tree->SetBranchAddress("TrueEnergyHighEPhoton",        &TrueEnergyHighEPhoton);
  tree->SetBranchAddress("TrueEnergyLowEPhoton",         &TrueEnergyLowEPhoton);
  tree->SetBranchAddress("TrueTrackIDPi0",               &TrueTrackIDPi0);
  tree->SetBranchAddress("TrueTrackIDHighEPhoton",       &TrueTrackIDHighEPhoton);
  tree->SetBranchAddress("TrueTrackIDLowEPhoton",        &TrueTrackIDLowEPhoton);
  tree->SetBranchAddress("DepositHighEPhoton",           &DepositHighEPhoton);
  tree->SetBranchAddress("DepositLowEPhoton",            &DepositLowEPhoton);
  tree->SetBranchAddress("VertexDetectorDistHighEPhoton",&VertexDetectorDistHighEPhoton);
  tree->SetBranchAddress("VertexDetectorDistLowEPhoton", &VertexDetectorDistLowEPhoton);
  tree->SetBranchAddress("NClusters",                    &NClusters);
  tree->SetBranchAddress("Cluster_Plane",                &Cluster_Plane);
  tree->SetBranchAddress("Cluster_Size",                 &Cluster_Size);
  tree->SetBranchAddress("Cluster_TrueTrackID",          &Cluster_TrueTrackID);
  tree->SetBranchAddress("Cluster_Charge",               &Cluster_Charge);
  tree->SetBranchAddress("Cluster_Energy",               &Cluster_Energy);

  for (unsigned int event = 0; event < tree->GetEntriesFast(); ++event) {

    if (event % 1000 == 0) std::cout << "Processing event " << event << std::endl;

    tree->GetEntry(event);

    // Find the largest cluster for both photons
    std::map<double,int> clusterEnergiesUHighEPhoton, clusterEnergiesULowEPhoton;
    std::map<double,int> clusterEnergiesVHighEPhoton, clusterEnergiesVLowEPhoton;
    std::map<double,int> clusterEnergiesZHighEPhoton, clusterEnergiesZLowEPhoton;

    // Look at clusters
    for (int cluster = 0; cluster < NClusters; ++cluster) {

      if (Cluster_Size[cluster] <= 10) continue;

      if (Cluster_TrueTrackID[cluster] == TrueTrackIDHighEPhoton) {
	if (Cluster_Plane[cluster] == 0) clusterEnergiesUHighEPhoton[Cluster_Energy[cluster]] = cluster;
	if (Cluster_Plane[cluster] == 1) clusterEnergiesVHighEPhoton[Cluster_Energy[cluster]] = cluster;
	if (Cluster_Plane[cluster] == 2) clusterEnergiesZHighEPhoton[Cluster_Energy[cluster]] = cluster;
      }

      else if (Cluster_TrueTrackID[cluster] == TrueTrackIDLowEPhoton) {
	if (Cluster_Plane[cluster] == 0) clusterEnergiesULowEPhoton[Cluster_Energy[cluster]] = cluster;
	if (Cluster_Plane[cluster] == 1) clusterEnergiesVLowEPhoton[Cluster_Energy[cluster]] = cluster;
	if (Cluster_Plane[cluster] == 2) clusterEnergiesZLowEPhoton[Cluster_Energy[cluster]] = cluster;
      }

      else continue;

    }

    if (clusterEnergiesUHighEPhoton.size()) {
      double completeness = (double)clusterEnergiesUHighEPhoton.rbegin()->first/(double)DepositHighEPhoton;
      hEnergyCompleteness->Fill(completeness);
      hEnergyCompletenessEnergy->Fill(DepositHighEPhoton, completeness);
    }
    if (clusterEnergiesVHighEPhoton.size()) {
      double completeness = (double)clusterEnergiesVHighEPhoton.rbegin()->first/(double)DepositHighEPhoton;
      hEnergyCompleteness->Fill(completeness);
      hEnergyCompletenessEnergy->Fill(DepositHighEPhoton, completeness);
    }
    if (clusterEnergiesZHighEPhoton.size()) {
      double completeness = (double)clusterEnergiesZHighEPhoton.rbegin()->first/(double)DepositHighEPhoton;
      hEnergyCompleteness->Fill(completeness);
      hEnergyCompletenessEnergy->Fill(DepositHighEPhoton, completeness);
    }
    if (clusterEnergiesULowEPhoton.size()) {
      double completeness = (double)clusterEnergiesULowEPhoton.rbegin()->first/(double)DepositLowEPhoton;
      hEnergyCompleteness->Fill(completeness);
      hEnergyCompletenessEnergy->Fill(DepositLowEPhoton, completeness);
    }
    if (clusterEnergiesVLowEPhoton.size()) {
      double completeness = (double)clusterEnergiesVLowEPhoton.rbegin()->first/(double)DepositLowEPhoton;
      hEnergyCompleteness->Fill(completeness);
      hEnergyCompletenessEnergy->Fill(DepositLowEPhoton, completeness);
    }
    if (clusterEnergiesZLowEPhoton.size()) {
      double completeness = (double)clusterEnergiesZLowEPhoton.rbegin()->first/(double)DepositLowEPhoton;
      hEnergyCompleteness->Fill(completeness);
      hEnergyCompletenessEnergy->Fill(DepositLowEPhoton, completeness);
    }

  }

  outFile->cd();
  hEnergyCompleteness->Write();
  hEnergyCompletenessEnergy->Write();

  outFile->Close();
  inFile->Close();

}
