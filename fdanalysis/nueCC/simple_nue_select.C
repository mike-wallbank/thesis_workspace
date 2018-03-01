{

  // Get input files
  TFile* nuFile = new TFile("/pnfs/dune/persistent/users/wallbank/v06_26_00/nue_select_pandora/nue_select_pandora_nu/anahist.root");
  TFile* nueFile = new TFile("/pnfs/dune/persistent/users/wallbank/v06_26_00/nue_select_pandora/nue_select_pandora_nue/anahist.root");
  TFile* nutauFile = new TFile("/pnfs/dune/persistent/users/wallbank/v06_26_00/nue_select_pandora/nue_select_pandora_nutau/anahist.root");

  TTree* nuTree = (TTree*)nuFile->Get("nueSelect/NuESelection");
  TTree* nueTree = (TTree*)nueFile->Get("nueSelect/NuESelection");
  TTree* nutauTree = (TTree*)nutauFile->Get("nueSelect/NuESelection");

  TString INFV="(abs(TrueNuX)<360-50&&abs(TrueNuY)<600-50&&TrueNuZ>50&&TrueNuZ<1394-150)";
  TString SIGNAL_DEF="("+INFV+"&&Neutrino==12)";

  //  TString SELECTION="LongestShowerLength>10";
  TString SELECTION="LongestParticle==LongestShower";

  TH1F* h_enu_sig = new TH1F("h_enu_sig",";True Neutrino Energy (GeV);",25,0,10);
  TH1F* h_enu_sig_sel = new TH1F("h_enu_sig_sel",";True Neutrino Energy (GeV);",25,0,10);
  TH1F* h_enu_sel = new TH1F("h_enu_sel",";True Neutrino Energy (GeV);",25,0,10);

  nueTree->Draw("TrueNuEnergy>>h_enu_sig",SIGNAL_DEF);
  nueTree->Draw("TrueNuEnergy>>h_enu_sig_sel",SELECTION+"&&"+SIGNAL_DEF);
  nueTree->Draw("TrueNuEnergy>>h_enu_sel",SELECTION);
  nuTree->Draw("TrueNuEnergy>>+h_enu_sel",SELECTION);
  nutauTree->Draw("TrueNuEnergy>>+h_enu_sel",SELECTION);

  h_enu_sig->SetMinimum(0); h_enu_sig->SetMaximum(1);
  h_enu_sig_sel->SetMinimum(0); h_enu_sig_sel->SetMaximum(1);
  h_enu_sel->SetMinimum(0); h_enu_sel->SetMaximum(1);

  TEfficiency* h_eff_enu = new TEfficiency(*h_enu_sig_sel,*h_enu_sig);
  TEfficiency* h_pur_enu = new TEfficiency(*h_enu_sig_sel,*h_enu_sel);

  h_eff_enu->SetTitle(";True Neutrino Energy (GeV);Efficiency;");
  h_pur_enu->SetTitle(";True Neutrino Energy (GeV);Purity;");

  TCanvas* canv = new TCanvas("canv","",800,600);
  h_eff_enu->Draw();
  canv->SaveAs("eff.pdf");
  canv->Clear();
  h_pur_enu->Draw();
  canv->SaveAs("pur.pdf");

}
