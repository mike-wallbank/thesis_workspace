{
  gROOT->SetStyle("T2K");
  gROOT->ProcessLine(".x /dune/app/users/wallbank/larsoft-fd/workspace/fdanalysis/nueCCcuts/scripts/baseDefs/loadDefs.C");
  //Simple script to draw ElectronMVA for electrons and not electrons

  TString output_name = "myoutput"; //No postfix (e.g. .root)
  const int NPlots = 2;
  int NBins = 50;
  double binLow = -0.5;
  double binHigh = 0.4;

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

  hist_names[0]="h_signal";
  //  selections[0]=(TString)(DEF_SELECTION_SIGNAL_WEIGHTED);
  selections[0]=(TString)(DEF_SIGNAL_WEIGHTED);
  draws[0]="SelMVAElectron";
  xaxis_labels[0]="Electron-like MVA (no units)";
  yaxis_labels[0]="No. events";
  line_colors[0]=4;
  fill_colors[0]=4;
  fill_styles[0]=3003;
  leg_names[0]="Signal";
  leg_styles[0]="F";
  
  hist_names[1]="h_background";
  //  selections[1]=(TString)(DEF_SELECTION_BACKGROUND_WEIGHTED);
  selections[1]=(TString)(DEF_BACKGROUND_WEIGHTED);
  draws[1]="SelMVAElectron";
  xaxis_labels[1]="Electron-like MVA (no units)";
  yaxis_labels[1]="No. events";
  line_colors[1]=2;
  fill_colors[1]=2;
  fill_styles[1]=3003;
  leg_names[1]="Background";
  leg_styles[1]="F";


  TLegend *leg = new TLegend(0.164,0.77,0.44,0.92);

  TTree *thetree = (TTree*) _file0->Get("nuecutselection/nuecutsel");

  gROOT->ProcessLine(".x /dune/app/users/wallbank/larsoft-fd/workspace/fdanalysis/nueCCcuts/scripts/genericPlots/1D.C");

}
