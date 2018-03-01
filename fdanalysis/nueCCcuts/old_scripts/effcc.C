#include "TFile.h"
#include "TH1D.h"
#include "TTree.h"
#include "TGraph.h"
#include "TCanvas.h"
#include <vector>
#include <iostream>

using namespace std;

void effcc(){
  gROOT->SetStyle("T2K");

  //TFile f("/dune/data/users/tjyang/mva/nuetest.root");
  //TFile f("/pnfs/dune/scratch/users/tjyang/v06_03_00/mergeana/nuetest1/anahist.root");
  //TFile f("/pnfs/dune/scratch/users/tjyang/v06_03_00/mergeana/nuetest/anahist.root");
  //TFile f("/pnfs/dune/scratch/users/tjyang/v06_05_00/mergeana/nuetest45deg/anahist.root");
  //TFile f("/dune/data/users/tjyang/mva/newfiles/numutest.root");
  //TFile f("/dune/data/users/dbrailsf/oscillations/nu_mu/production/v06_11_00/D/mc/fdsenseopt/v06_11_00_D_prodgenie_nuall_dune10kt_1x2x6_hadd.root");
  //TFile f("/dune/data/users/dbrailsf/oscillations/nu_mu/production/v06_18_00/B/mc/fdsenseopt/v06_18_00_B_prodgenie_nuall_dune10kt_1x2x6_hadd.root");
  TFile f("mva_nue.root");
  //TFile f("/dune/data/users/dbrailsf/oscillations/nu_mu/production/v06_18_00/B/mc/fdsenseopt/v06_18_00_B_prodgenie_anuall_dune10kt_1x2x6_hadd.root");


  //TFile f("/pnfs/dune/scratch/users/tjyang/v06_03_00/mergeana/anuetest/anahist.root");
  TTree *pottree = (TTree*)f.Get("mvaselect/pottree");

  int run;
  double pot;
  
  pottree->SetBranchAddress("run",&run);
  pottree->SetBranchAddress("pot",&pot);

  double pot_nu = 0;
  double pot_nue = 0;
  double pot_nutau = 0;

  Long64_t nentries = pottree->GetEntries();
  for (Long64_t i = 0; i<nentries; ++i){
    pottree->GetEntry(i);
    //cout<<run<<" "<<pot<<endl;
    if (run==20000001) pot_nu += pot;
    if (run==20000002) pot_nue += pot;
    if (run==20000003) pot_nutau += pot;
  }
  cout<<pot_nu<<" "<<pot_nue<<" "<<pot_nutau<<endl;

  TH1D *enu[7];
  TH1D *mva[7];

  enu[0] = (TH1D*)f.Get("mvaselect/enu_numu_nue");
  enu[1] = (TH1D*)f.Get("mvaselect/enu_nc");
  enu[2] = (TH1D*)f.Get("mvaselect/enu_nue_nue");
  enu[3] = (TH1D*)f.Get("mvaselect/enu_numu_numu");
  enu[4] = (TH1D*)f.Get("mvaselect/enu_nue_numu");
  enu[5] = (TH1D*)f.Get("mvaselect/enu_numu_nutau");
  enu[6] = (TH1D*)f.Get("mvaselect/enu_nue_nutau");

  mva[0] = (TH1D*)f.Get("mvaselect/mva_numu_nue");
  mva[1] = (TH1D*)f.Get("mvaselect/mva_nc");
  mva[2] = (TH1D*)f.Get("mvaselect/mva_nue_nue");
  mva[3] = (TH1D*)f.Get("mvaselect/mva_numu_numu");
  mva[4] = (TH1D*)f.Get("mvaselect/mva_nue_numu");
  mva[5] = (TH1D*)f.Get("mvaselect/mva_numu_nutau");
  mva[6] = (TH1D*)f.Get("mvaselect/mva_nue_nutau");

  double mass = 2*(360-50)*2*(600-50)*(1394-150-50)*1.4/1e9; //kt
  double potpermwyr = 1.47e21/1.07;
  double totpot = 150*potpermwyr/mass;//kt*mw*yr

  double scale[7];
  scale[0] = totpot/pot_nue;
  scale[1] = totpot/(pot_nu+pot_nue+pot_nutau);
  scale[2] = totpot/pot_nu;
  scale[3] = totpot/pot_nu;
  scale[4] = totpot/pot_nutau;
  scale[5] = totpot/pot_nutau;
  scale[6] = totpot/pot_nue;

  double nue_osc = mva[0]->Integral()*scale[0];
  double nc = enu[1]->Integral()*scale[1];
  double numu = mva[3]->Integral()*scale[3]+mva[4]->Integral()*scale[4];
  double nue_beam = enu[2]->Integral()*scale[2];
  double nutau = enu[5]->Integral()*scale[5]+enu[6]->Integral()*scale[6];
  
  cout<<nue_osc<<" "<<nc<<" "<<numu<<" "<<nue_beam<<" "<<nutau<<endl;

  int nbins = mva[0]->GetNbinsX();
  vector<double> eff_nue_osc;
  vector<double> eff_nc;
  vector<double> eff_numu;
  vector<double> eff_nue_beam;
  vector<double> eff_nutau;

  cout<<nbins<<endl;
  for (int i = 1; i<=nbins; ++i){
    double nue_osc0 = 0;
    double nc0 = 0;
    double numu0 = 0;
    double nue_beam0 = 0;
    double nutau0 = 0;
    for (int j = 1; j<=nbins; ++j){
      if (mva[0]->GetBinCenter(j)>mva[0]->GetBinCenter(i)){
        nue_osc0 += mva[0]->GetBinContent(j)*scale[0];
        nc0 += mva[1]->GetBinContent(j)*scale[1];
        numu0 += mva[3]->GetBinContent(j)*scale[3]+mva[4]->GetBinContent(j)*scale[4];
        nue_beam0 += mva[2]->GetBinContent(j)*scale[2];
        nutau0 += mva[5]->GetBinContent(j)*scale[5]+mva[6]->GetBinContent(j)*scale[6];
      }
    }
    eff_nue_osc.push_back(nue_osc0/nue_osc);
    eff_nc.push_back(1-nc0/nc);
    eff_numu.push_back(numu0/numu);
    eff_nue_beam.push_back(1-nue_beam0/nue_beam);
    eff_nutau.push_back(1-nutau0/nutau);
    //cout<<eff_nue_osc.back()<<" "<<eff_nc.back()<<endl;
    //cout<<mva[0]->GetBinCenter(i)<<" "<<nue_osc0<<" "<<nc0<<" "<<numu0<<" "<<nue_beam0<<" "<<nutau0<<endl;
    std::cout<<numu0/numu<<std::endl;
  }

  TGraph *gr_nc = new TGraph(nbins,&eff_nue_osc[0],&eff_nc[0]);
  gr_nc->SetLineWidth(2);

  TCanvas *c1 = new TCanvas("c1","c1");
  c1->SetGrid();
  gr_nc->SetTitle("");
  gr_nc->GetXaxis()->SetTitle("#nu_{e} CC efficiency");
  gr_nc->GetYaxis()->SetTitle("NC rejection");
  gr_nc->Draw("al");
  c1->Print("ccroc.pdf");
  TFile *output = new TFile("output.root","RECREATE");
  gr_nc->Write("gr_nc");
  output->Close();
}
