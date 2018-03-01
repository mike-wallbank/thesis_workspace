{
  gROOT->SetStyle("T2K");

  TH1F *hA = (TH1F*) _file0->Get("h_chi2_muonMVAGR0.030000");

  hA->SetLineWidth(2);

  hA->GetYaxis()->SetTitle("#chi^{2}");

  TCanvas *c1 = new TCanvas("c1","c1",800,800);
  hA->Draw("hist");

  /*
  TLegend *leg = new TLegend(0.5,0.7,0.8,0.9);
  leg->SetFillColor(0);
  leg->SetLineColor(0);
  leg->AddEntry(hA,"#theta_{23}=41.5#circ","F");
  leg->AddEntry(hB,"#theta_{23}=40.4#circ","F");
  leg->Draw();
  */

}
