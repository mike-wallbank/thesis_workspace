{
  gROOT->ProcessLine(".x /dune/app/users/wallbank/larsoft-fd/workspace/fdanalysis/nueCCcuts/scripts/genericPlots/make1DHists.C");
 
  //Calculate Ymax
  double max = hists[0]->GetMaximum();
  for (int i_plot = 0; i_plot < NPlots; i_plot++){
    if (hists[i_plot]->GetMaximum() > max){
      max = hists[i_plot]->GetMaximum();
    }
  }
  hists[0]->SetMaximum(max*1.05);
  TCanvas *canvas = new TCanvas("canvas","canvas");
  for (int i_plot = 0; i_plot < NPlots; i_plot++){
    TString drawcmd = "hist";
    if (i_plot>0) drawcmd = "histsame";
    hists[i_plot]->Draw(drawcmd);
  }

  if (leg){
    gROOT->ProcessLine(".x /dune/app/users/wallbank/larsoft-fd/workspace/fdanalysis/nueCCcuts/scripts/genericPlots/makeLegend.C");
  }

  //TFile *output_file = new TFile(output_name+".root","NEW");
  //output_file->cd();
  //for (i_plot = 0; i_plot < NPlots; i_plot++){
  //  hists[i_plot]->Write();
  //}
  //canvas->Write();
  //output_file->Close();
}
