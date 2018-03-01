{
  gROOT->SetStyle("T2K");
  gROOT->ProcessLine(".x /dune/app/users/wallbank/larsoft-fd/workspace/fdanalysis/nueCCcuts/scripts/baseDefs/loadDefs.C");
  //Simple script to draw MuonMVA for muons and not muons

  TString output_name = "myefficiencyLepMom"; //No postfix (e.g. .root)
  const int NPlots = 2;
  int NBins = 20;
  double binLow = 0.;
  double binHigh = 10.;

  TString hist_names[NPlots];
  TString draws[NPlots];
  TString selections[NPlots];
  TString xaxis_labels[NPlots];
  TString yaxis_labels[NPlots];
  int line_colors[NPlots];
  int fill_colors[NPlots];
  int fill_styles[NPlots];
  TString leg_names[NPlots];
  TString leg_styles[NPlots];

  hist_names[0]="h_all";
  selections[0]=(TString)(DEF_SIGNAL_WEIGHTED);
  draws[0]="sqrt(LepMomX*LepMomX + LepMomY*LepMomY + LepMomZ*LepMomZ)";
  xaxis_labels[0]="Lepton momentum (GeV)";
  yaxis_labels[0]="No. events";
  line_colors[0]=4;
  fill_colors[0]=4;
  fill_styles[0]=3003;
  leg_names[0]="All signal";
  leg_styles[0]="F";
  
  hist_names[1]="h_selected";
  selections[1]=(TString)(DEF_SELECTION_SIGNAL_WEIGHTED);
  draws[1]="sqrt(LepMomX*LepMomX + LepMomY*LepMomY + LepMomZ*LepMomZ)";
  xaxis_labels[1]="Lepton momentum (GeV)";
  yaxis_labels[1]="No. events";
  line_colors[1]=1;
  fill_colors[1]=1;
  fill_styles[1]=3003;
  leg_names[1]="Selected signal";
  leg_styles[1]="F";


  TLegend *leg = new TLegend(0.57,0.76,0.84,0.91);

  TTree *thetree = (TTree*) _file0->Get("nuecutselection/nuecutsel");

  gROOT->ProcessLine(".x /dune/app/users/wallbank/larsoft-fd/workspace/fdanalysis/nueCCcuts/scripts/genericPlots/efficiency.C");
  gROOT->ProcessLine(".x /dune/app/users/wallbank/larsoft-fd/workspace/fdanalysis/nueCCcuts/scripts/genericPlots/write.C");
}
