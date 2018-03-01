{
  //loop backwards so that the order makes sense with a stack
  for (int i_plot = NPlots-1; i_plot >= 0; i_plot--){
    leg->AddEntry(hists[i_plot],leg_names[i_plot],leg_styles[i_plot]);
  }
  leg->SetFillStyle(0);
  leg->SetLineStyle(0);
  leg->SetLineColorAlpha(0,0);
  leg->Draw();
}
