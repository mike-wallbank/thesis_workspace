{
  gROOT->ProcessLine(".x /dune/app/users/wallbank/larsoft-fd/workspace/fdanalysis/nueCCcuts/scripts/genericPlots/1D.C");

  TH1F *h_all = (TH1F*) gDirectory->Get("h_all");
  TH1F *h_selected = (TH1F*) gDirectory->Get("h_selected");

  TEfficiency *efficiency = new TEfficiency(*h_selected,*h_all);
  efficiency->SetName("efficiency");
  efficiency->SetTitle(TString("eff;")+h_all->GetXaxis()->GetTitle()+TString("; No units"));
  efficiency->Draw();
  //efficiency->GetPaintedGraph()->GetYaxis()->SetTitle("No units");

}
