void effPurBGEffComparison(TString efficiency_file_name, TString purity_file_name, TString bgrejection_file_name, TString output_prefix){

  gROOT->SetStyle("T2K");

  TFile *efficiency_file = new TFile(efficiency_file_name);
  TFile *purity_file = new TFile(purity_file_name);
  //TFile *bgefficiency_file = new TFile(bgefficiency_file_name);
  TFile *bgrejection_file = new TFile(bgrejection_file_name);


  TH1F *h_all_signal = (TH1F*) efficiency_file->Get("h_all");
  h_all_signal->SetLineColor(14);
  h_all_signal->SetFillColor(14);
  h_all_signal->SetFillStyle(3003);
  h_all_signal->Scale(1./h_all_signal->GetMaximum());
  h_all_signal->GetYaxis()->SetTitle("No units");
  TEfficiency *efficiency = (TEfficiency*) efficiency_file->Get("efficiency");
  TEfficiency *purity = (TEfficiency*) purity_file->Get("efficiency");
  //TEfficiency *bgefficiency = (TEfficiency*) bgefficiency_file->Get("efficiency");
  TEfficiency *bgrejection = (TEfficiency*) bgrejection_file->Get("efficiency");



  TCanvas *canvas = new TCanvas("canvas","canvas");
  efficiency->SetMarkerColor(1);
  purity->SetMarkerColor(2);
  //bgefficiency->SetMarkerColor(4);
  bgrejection->SetMarkerColor(4);



  h_all_signal->Draw("hist");
  efficiency->Draw("same");
  purity->Draw("same");
  //bgefficiency->Draw("same");
  bgrejection->Draw("same");


  TLegend *leg = new TLegend(0.59,0.23,0.83,0.41);
  leg->SetLineColor(0);
  leg->SetFillStyle(0);
  leg->SetFillColor(0);
  leg->AddEntry(efficiency,"Efficiency","elp");
  leg->AddEntry(purity,"Purity","elp");
  //leg->AddEntry(bgefficiency,"Background efficiency","elp");
  leg->AddEntry(bgrejection,"Background rejection","elp");
  leg->AddEntry(h_all_signal,"No. true #nu_{#mu} CC events (A.U.)","f");
  leg->Draw();

  canvas->SaveAs(output_prefix+".pdf");
  canvas->SaveAs(output_prefix+".png");
  canvas->SaveAs(output_prefix+".root");



}

