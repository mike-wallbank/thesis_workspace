{
  gROOT->SetStyle("T2K");
  //Simple script to draw MuonMVA for muons and not muons

  const int NPlots = 2;
  int NBins = 50;
  double binLow = -0.5;
  double binHigh = 0.4;

  TString hist_names[NPlots];
  TString selections[NPlots];
  TString xaxis_labels[NPlots];
  TString yaxis_labels[NPlots];
  int line_colors[NPlots];
  int fill_colors[NPlots];
  int fill_styles[NPlots];

  hist_names[0]="h_muons";
  selections[0]="abs(TruePDG)==13";
  xaxis_labels[0]="Muon-like MVA (no units)";
  yaxis_labels[0]="A.U.";
  line_colors[0]=4;
  fill_colors[0]=4;
  fill_styles[0]=3003;
  
  hist_names[1]="h_notmuons";
  selections[1]="abs(TruePDG)!=13";
  xaxis_labels[1]="Muon-like MVA (no units)";
  yaxis_labels[1]="A.U.";
  line_colors[1]=2;
  fill_colors[1]=2;
  fill_styles[1]=3003;


  TH1F *hists[NPlots];
  TTree *PIDAna = (TTree*) _file0->Get("numucutselection/PIDAna");

  for (int i_plot = 0; i_plot < NPlots; i_plot++){
    hists[i_plot] = new TH1F(hist_names[i_plot],"",NBins,binLow,binHigh);
    hists[i_plot]->SetLineColor(line_colors[i_plot]);
    hists[i_plot]->SetFillColor(fill_colors[i_plot]);
    hists[i_plot]->SetFillStyle(fill_styles[i_plot]);
    hists[i_plot]->GetXaxis()->SetTitle(xaxis_labels[i_plot]);
    hists[i_plot]->GetYaxis()->SetTitle(yaxis_labels[i_plot]);


    PIDAna->Draw("MuonMVA>>"+hist_names[i_plot],selections[i_plot] + " && RecoLength > 00","goff");
  }
 
  TCanvas *c_muonmva = new TCanvas("c_muonmva","c_muonmva");
  hists[0]->Draw("hist");
  hists[1]->Draw("histsame");
  TLegend *leg = new TLegend(0.16,0.78,0.43,0.92);
  leg->AddEntry(hists[0],"Muons","F");
  leg->AddEntry(hists[1],"Not muons","F");
  leg->SetFillStyle(0);
  leg->SetLineColor(0);
  leg->Draw();
}
