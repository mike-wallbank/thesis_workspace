{
  gROOT->SetStyle("T2K");
  gROOT->ProcessLine(".x /dune/app/users/wallbank/larsoft-fd/workspace/fdanalysis/nueCCcuts/scripts/baseDefs/loadDefs.C");
  //Simple script to draw ElectronMVA for electrons and not electrons

  const int NPlots = 4;
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

  hist_names[0]="h_electrons";
  selections[0]=(TString)("");
  selections[0] = (TString)("(("+DEF_WEIGHTING+")*(("+DEF_SIGNAL+")&&(!("+DEF_SELECTION+")&&abs(SelTruePDG)==13)))");
  draws[0]="SelMVAElectron";
  xaxis_labels[0]="Electron-like MVA (no units)";
  yaxis_labels[0]="No. events";
  line_colors[0]=4;
  fill_colors[0]=4;
  fill_styles[0]=3003;
  leg_names[0]="#mu";
  leg_styles[0]="F";
  
  hist_names[1]="h_protons";
  selections[1] = (TString)("(("+DEF_WEIGHTING+")*(("+DEF_SIGNAL+")&&(!("+DEF_SELECTION+")&&abs(SelTruePDG)==2212)))");
  draws[1]="SelMVAElectron";
  xaxis_labels[1]="Electron-like MVA (no units)";
  yaxis_labels[1]="No. events";
  line_colors[1]=2;
  fill_colors[1]=2;
  fill_styles[1]=3003;
  leg_names[1]="p";
  leg_styles[1]="F";

  hist_names[2]="h_pions";
  selections[2] = (TString)("(("+DEF_WEIGHTING+")*(("+DEF_SIGNAL+")&&(!("+DEF_SELECTION+")&&abs(SelTruePDG)==211)))");
  draws[2]="SelMVAElectron";
  xaxis_labels[2]="Electron-like MVA (no units)";
  yaxis_labels[2]="No. events";
  line_colors[2]=1;
  fill_colors[2]=1;
  fill_styles[2]=3003;
  leg_names[2]="#pi^{#pm}";
  leg_styles[2]="F";

  hist_names[3]="h_other";
  selections[3] = (TString)("(("+DEF_WEIGHTING+")*(("+DEF_SIGNAL+")&&(!("+DEF_SELECTION+")&&(!((abs(SelTruePDG)==13)||abs(SelTruePDG==2212)||abs(SelTruePDG)==211)))))");
  draws[3]="SelMVAElectron";
  xaxis_labels[3]="Electron-like MVA (no units)";
  yaxis_labels[3]="No. events";
  line_colors[3]=6;
  fill_colors[3]=6;
  fill_styles[3]=3003;
  leg_names[3]="Other";
  leg_styles[3]="F";



  TLegend *leg = new TLegend(0.16,0.62,0.45,0.92);

  TTree *thetree = (TTree*) _file0->Get("nuecutselection/nuecutsel");

  gROOT->ProcessLine(".x /dune/app/users/wallbank/larsoft-fd/workspace/fdanalysis/nueCCcuts/scripts/genericPlots/stack.C");
}
