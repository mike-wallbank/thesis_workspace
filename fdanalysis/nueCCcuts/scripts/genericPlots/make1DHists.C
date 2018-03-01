{
  TH1F *hists[NPlots];

  for (int i_plot = 0; i_plot < NPlots; i_plot++){
    hists[i_plot] = new TH1F(hist_names[i_plot],"",NBins,binLow,binHigh);
    hists[i_plot]->SetLineColor(line_colors[i_plot]);
    hists[i_plot]->SetFillColor(fill_colors[i_plot]);
    hists[i_plot]->SetFillStyle(fill_styles[i_plot]);
    hists[i_plot]->GetXaxis()->SetTitle(xaxis_labels[i_plot]);
    hists[i_plot]->GetYaxis()->SetTitle(yaxis_labels[i_plot]);
    thetree->Draw(draws[i_plot]+">>"+hist_names[i_plot],selections[i_plot],"goff");
  }
}
