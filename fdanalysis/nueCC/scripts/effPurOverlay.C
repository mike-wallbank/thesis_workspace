void effPurOverlay(TString efficiency_file_name, TString purity_file_name, TString bg_efficiency_file_name="", TString output_prefix="output"){

  gROOT->SetStyle("T2K");
  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);

  TFile *efficiency_file = new TFile(efficiency_file_name,"READ");
  TFile *purity_file = new TFile(purity_file_name,"READ");
  TFile *bg_efficiency_file = new TFile(bg_efficiency_file_name,"READ");

  //ENu first
  TEfficiency *h_eff_enu = (TEfficiency*) efficiency_file->Get("h_enu_sig_clone");
  TH1F *h_enu_sig = (TH1F*) efficiency_file->Get("h_enu_sig");
  TEfficiency *h_pur_enu = (TEfficiency*) purity_file->Get("h_enu_sig_clone");
  TEfficiency *h_bg_eff_enu = (TEfficiency*) bg_efficiency_file->Get("h_enu_sig_clone");

  TCanvas *c_enu = new TCanvas("c_enu","c_enu",800,600);
  h_eff_enu->SetMarkerStyle(8);
  h_eff_enu->SetMarkerSize(1);
  h_eff_enu->SetMarkerColor(1);
  h_eff_enu->SetLineColor(1);
  h_eff_enu->Draw();
  gPad->Update();
  h_eff_enu->GetPaintedGraph()->SetMaximum(1.05);
  h_eff_enu->GetPaintedGraph()->SetMinimum(0.);
  //h_eff_enu->SetTitle(TString("eff;")+h_eff_enu->GetPaintedGraph()->GetXaxis()->GetTitle()+TString("; Fractional value"));
  h_eff_enu->SetTitle(TString(";True E_{#nu} (GeV); Fractional value"));
  h_eff_enu->GetPaintedGraph()->GetXaxis()->SetRangeUser(h_enu_sig->GetXaxis()->GetXmin(),h_enu_sig->GetXaxis()->GetXmax());
  h_pur_enu->Draw();
  //h_bg_eff_enu->Draw();
  gPad->Update();
  h_pur_enu->SetMarkerStyle(8);
  h_pur_enu->SetMarkerSize(1);
  h_pur_enu->SetMarkerColor(2);
  h_pur_enu->SetLineColor(2);
  //h_bg_eff_enu->SetMarkerColor(4);

  h_enu_sig->SetLineColor(14);
  h_enu_sig->SetFillColor(14);
  h_enu_sig->SetFillStyle(3003);
  h_enu_sig->Scale(1.0/h_enu_sig->GetMaximum());

  TLegend *leg_enu = new TLegend(0.55,0.6,0.88,0.86);
  std::cout <<"legend text size " << leg_enu->GetTextSize() << std::endl;
  leg_enu->AddEntry(h_eff_enu,"Efficiency","pel");
  leg_enu->AddEntry(h_pur_enu,"Purity","pel");
  //leg_enu->AddEntry(h_bg_eff_enu,"BG efficiency","pel");
  leg_enu->AddEntry(h_enu_sig,"Simuluated #nu_{e} CC spectrum (A.U.)","f");
  leg_enu->SetLineColorAlpha(0,1);
  leg_enu->SetFillStyle(0);

  h_eff_enu->Draw();
  h_pur_enu->Draw("same");
  //h_bg_eff_enu->Draw("same");
  h_enu_sig->Draw("samehist");
  leg_enu->Draw();

  TString output_name_enu = output_prefix+"_enu";
  c_enu->SaveAs(output_name_enu+".eps");
  c_enu->SaveAs(output_name_enu+".pdf");
  c_enu->SaveAs(output_name_enu+".root");
  c_enu->SaveAs(output_name_enu+".png");



  //Q2 
  TEfficiency *h_eff_q2 = (TEfficiency*) efficiency_file->Get("h_q2_sig_clone");
  TH1F *h_q2_sig = (TH1F*) efficiency_file->Get("h_q2_sig");
  TEfficiency *h_pur_q2 = (TEfficiency*) purity_file->Get("h_q2_sig_clone");
  TEfficiency *h_bg_eff_q2 = (TEfficiency*) bg_efficiency_file->Get("h_q2_sig_clone");

  TCanvas *c_q2 = new TCanvas("c_q2","c_q2",800,600);
  h_eff_q2->SetMarkerStyle(8);
  h_eff_q2->SetMarkerSize(1);
  h_eff_q2->SetMarkerColor(1);
  h_eff_q2->SetLineColor(1);
  h_eff_q2->Draw();
  gPad->Update();
  h_eff_q2->GetPaintedGraph()->SetMaximum(1.05);
  h_eff_q2->GetPaintedGraph()->SetMinimum(0.);
  h_eff_q2->SetTitle(TString(";")+h_eff_q2->GetPaintedGraph()->GetXaxis()->GetTitle()+TString("; Fractional value"));
  h_eff_q2->GetPaintedGraph()->GetXaxis()->SetRangeUser(h_q2_sig->GetXaxis()->GetXmin(),h_q2_sig->GetXaxis()->GetXmax());
  h_pur_q2->Draw();
  gPad->Update();
  h_pur_q2->SetMarkerStyle(8);
  h_pur_q2->SetMarkerSize(1);
  h_pur_q2->SetMarkerColor(2);
  h_pur_q2->SetLineColor(2);
  //h_bg_eff_q2->SetMarkerColor(4);

  h_q2_sig->SetLineColor(14);
  h_q2_sig->SetFillColor(14);
  h_q2_sig->SetFillStyle(3003);
  h_q2_sig->Scale(1.0/h_q2_sig->GetMaximum());

  TLegend *leg_q2 = new TLegend(0.55,0.6,0.88,0.86);
  leg_q2->AddEntry(h_eff_q2,"Efficiency","pel");
  leg_q2->AddEntry(h_pur_q2,"Purity","pel");
  //leg_q2->AddEntry(h_bg_eff_q2,"BG efficiency","pel");
  leg_q2->AddEntry(h_q2_sig,"No. true CC events (A.U.)","f");
  leg_q2->SetLineColorAlpha(0,1);
  leg_q2->SetFillStyle(0);

  h_eff_q2->Draw();
  h_pur_q2->Draw("same");
  //h_bg_eff_q2->Draw("same");
  h_q2_sig->Draw("samehist");
  leg_q2->Draw();

  TString output_name_q2 = output_prefix+"_q2";
  c_q2->SaveAs(output_name_q2+".eps");
  c_q2->SaveAs(output_name_q2+".pdf");
  c_q2->SaveAs(output_name_q2+".root");
  c_q2->SaveAs(output_name_q2+".png");


  //Lepton angle 
  TEfficiency *h_eff_lepangle = (TEfficiency*) efficiency_file->Get("h_lepangle_sig_clone");
  TH1F *h_lepangle_sig = (TH1F*) efficiency_file->Get("h_lepangle_sig");
  TEfficiency *h_pur_lepangle = (TEfficiency*) purity_file->Get("h_lepangle_sig_clone");
  TEfficiency *h_bg_eff_lepangle = (TEfficiency*) bg_efficiency_file->Get("h_lepangle_sig_clone");

  TCanvas *c_lepangle = new TCanvas("c_lepangle","c_lepangle",800,600);
  h_eff_lepangle->SetMarkerStyle(8);
  h_eff_lepangle->SetMarkerSize(1);
  h_eff_lepangle->SetMarkerColor(1);
  h_eff_lepangle->SetLineColor(1);
  h_eff_lepangle->Draw();
  gPad->Update();
  h_eff_lepangle->GetPaintedGraph()->SetMaximum(1.05);
  h_eff_lepangle->GetPaintedGraph()->SetMinimum(0.);
  h_eff_lepangle->SetTitle(TString(";")+h_eff_lepangle->GetPaintedGraph()->GetXaxis()->GetTitle()+TString("; Fractional value"));
  h_eff_lepangle->GetPaintedGraph()->GetXaxis()->SetRangeUser(h_lepangle_sig->GetXaxis()->GetXmin(),h_lepangle_sig->GetXaxis()->GetXmax());
  h_pur_lepangle->Draw();
  gPad->Update();
  h_pur_lepangle->SetMarkerStyle(8);
  h_pur_lepangle->SetMarkerSize(1);
  h_pur_lepangle->SetMarkerColor(2);
  h_pur_lepangle->SetLineColor(2);
  //h_bg_eff_lepangle->SetMarkerColor(4);

  h_lepangle_sig->SetLineColor(14);
  h_lepangle_sig->SetFillColor(14);
  h_lepangle_sig->SetFillStyle(3003);
  h_lepangle_sig->Scale(1.0/h_lepangle_sig->GetMaximum());

  TLegend *leg_lepangle = new TLegend(0.55,0.6,0.88,0.86);
  leg_lepangle->AddEntry(h_eff_lepangle,"Efficiency","pel");
  leg_lepangle->AddEntry(h_pur_lepangle,"Purity","pel");
  //leg_lepangle->AddEntry(h_bg_eff_lepangle,"BG efficiency","pel");
  leg_lepangle->AddEntry(h_lepangle_sig,"No. true CC events (A.U.)","f");
  leg_lepangle->SetLineColorAlpha(0,1);
  leg_lepangle->SetFillStyle(0);

  h_eff_lepangle->Draw();
  h_pur_lepangle->Draw("same");
  //h_bg_eff_lepangle->Draw("same");
  h_lepangle_sig->Draw("samehist");
  leg_lepangle->Draw();

  TString output_name_lepangle = output_prefix+"_lepangle";
  c_lepangle->SaveAs(output_name_lepangle+".eps");
  c_lepangle->SaveAs(output_name_lepangle+".pdf");
  c_lepangle->SaveAs(output_name_lepangle+".root");
  c_lepangle->SaveAs(output_name_lepangle+".png");



  //Lepton angle 
  TEfficiency *h_eff_lepmom = (TEfficiency*) efficiency_file->Get("h_lepmom_sig_clone");
  TH1F *h_lepmom_sig = (TH1F*) efficiency_file->Get("h_lepmom_sig");
  TEfficiency *h_pur_lepmom = (TEfficiency*) purity_file->Get("h_lepmom_sig_clone");
  TEfficiency *h_bg_eff_lepmom = (TEfficiency*) bg_efficiency_file->Get("h_lepmom_sig_clone");

  TCanvas *c_lepmom = new TCanvas("c_lepmom","c_lepmom",800,600);
  h_eff_lepmom->SetMarkerStyle(8);
  h_eff_lepmom->SetMarkerSize(1);
  h_eff_lepmom->SetMarkerColor(1);
  h_eff_lepmom->SetLineColor(1);
  h_eff_lepmom->Draw();
  gPad->Update();
  h_eff_lepmom->GetPaintedGraph()->SetMaximum(1.05);
  h_eff_lepmom->GetPaintedGraph()->SetMinimum(0.);
  h_eff_lepmom->SetTitle(TString(";")+h_eff_lepmom->GetPaintedGraph()->GetXaxis()->GetTitle()+TString("; Fractional value"));
  h_eff_lepmom->GetPaintedGraph()->GetXaxis()->SetRangeUser(h_lepmom_sig->GetXaxis()->GetXmin(),h_lepmom_sig->GetXaxis()->GetXmax());
  h_pur_lepmom->Draw();
  gPad->Update();
  h_pur_lepmom->SetMarkerStyle(8);
  h_pur_lepmom->SetMarkerSize(1);
  h_pur_lepmom->SetMarkerColor(2);
  h_pur_lepmom->SetLineColor(2);
  //h_bg_eff_lepmom->SetMarkerColor(4);

  h_lepmom_sig->SetLineColor(14);
  h_lepmom_sig->SetFillColor(14);
  h_lepmom_sig->SetFillStyle(3003);
  h_lepmom_sig->Scale(1.0/h_lepmom_sig->GetMaximum());

  TLegend *leg_lepmom = new TLegend(0.55,0.6,0.88,0.86);//0.595,0.246,0.885,0.417);
  leg_lepmom->AddEntry(h_eff_lepmom,"Efficiency","pel");
  leg_lepmom->AddEntry(h_pur_lepmom,"Purity","pel");
  //leg_lepmom->AddEntry(h_bg_eff_lepmom,"BG efficiency","pel");
  leg_lepmom->AddEntry(h_lepmom_sig,"No. true CC events (A.U.)","f");
  leg_lepmom->SetLineColorAlpha(0,1);
  leg_lepmom->SetFillStyle(0);

  h_eff_lepmom->Draw();
  h_pur_lepmom->Draw("same");
  //h_bg_eff_lepmom->Draw("same");
  h_lepmom_sig->Draw("samehist");
  leg_lepmom->Draw();

  TString output_name_lepmom = output_prefix+"_lepmom";
  c_lepmom->SaveAs(output_name_lepmom+".eps");
  c_lepmom->SaveAs(output_name_lepmom+".pdf");
  c_lepmom->SaveAs(output_name_lepmom+".root");
  c_lepmom->SaveAs(output_name_lepmom+".png");


}
