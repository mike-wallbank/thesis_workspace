{
  gROOT->ProcessLine(".x /dune/app/users/wallbank/larsoft-fd/workspace/fdanalysis/nueCCcuts/scripts/genericPlots/make1DHists.C");
 
  THStack *stack = new THStack("stack","stack");
  for (int i_plot = 0; i_plot < NPlots; i_plot++){
    stack->Add(hists[i_plot]);
  }
  TCanvas *canvas = new TCanvas("canvas","canvas");
  stack->Draw("hist");
  stack->GetXaxis()->SetTitle(xaxis_labels[0]);
  stack->GetYaxis()->SetTitle(yaxis_labels[0]);
  stack->Draw("hist");
  if (leg){
    gROOT->ProcessLine(".x /dune/app/users/wallbank/larsoft-fd/workspace/fdanalysis/nueCCcuts/scripts/genericPlots/makeLegend.C");
  }
}
