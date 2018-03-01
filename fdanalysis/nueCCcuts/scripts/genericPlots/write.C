{

  TFile *output_file = new TFile(output_name+".root","NEW");
  for (int i_plot = 0; i_plot < NPlots; i_plot++){
    hists[i_plot]->Write();
  }
  if (canvas) canvas->Write();
  if (efficiency) efficiency->Write();
  output_file->Close();
}
