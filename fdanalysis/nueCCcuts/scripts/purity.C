void purity(TString inputname,TString mvacut="0.02",TString outputname="hists_purities.root") {

  //Oscillation weights
  gROOT->ProcessLine(".L /dune/app/users/dbrailsf/oscillation/nu_mu/cutsel/tunings/getOscWeights/getProb3ppWeights.C+");
  
  double DEF_SIN2THETA12 = 0.308;
  double DEF_SIN2THETA13 = 0.02163;
  double DEF_SIN2THETA23 = 0.440;
  double DEF_DLITTLEM2 = 7.49e-5;
  double DEF_DBIGM2 = 2.526e-3;
  double DEF_DELTA = 0;

  TString DEF_OSCILLATION_WEIGHTING = Form("(getProb3ppWeights(%f,%f,%f,%f,%f,%f,Enu,BeamPdg,NuPdg))",DEF_SIN2THETA12,DEF_SIN2THETA13,DEF_SIN2THETA23,DEF_DLITTLEM2,DEF_DBIGM2,DEF_DELTA);

  TString INFV="(abs(SelRecoStartX)<360-50&&abs(SelRecoStartY)<600-50&&SelRecoStartZ>50&&SelRecoStartZ<1394-150)";
  TString SIGNAL_DEF="(abs(BeamPdg)==14 && abs(NuPdg)==12 && NC==0  && "+ INFV + ")";
  TString DEF_POT_WEIGHTING = "(ProjectedPOTWeight)";
  TString WEIGHTING = "("+DEF_OSCILLATION_WEIGHTING+"*"+DEF_POT_WEIGHTING+")";
  //TString WEIGHTING="ProjectedPOTWeight";
  TString SELECTION="SelMVAElectron>"+mvacut;

  //gROOT->SetStyle("T2K");


  //Get the file
  TFile *file = new TFile(inputname,"READ");
  //Get the tree
  TTree *MVASelection = (TTree*) file->Get("nuecutselection/nuecutsel");


  TEventList alllist("alllist"), sellist("sellist");
  MVASelection->Draw(">>alllist",WEIGHTING+"*("+SELECTION+")");
  MVASelection->Draw(">>sellist",WEIGHTING+"*("+SIGNAL_DEF+"&&"+SELECTION+")");
  std::cout << "Overall purity: " << sellist.GetN()/(float)alllist.GetN() << std::endl;


  //ENu
  TH1F *h_enu_sig = new TH1F("h_enu_sig","h_enu_sig",25,0,10);
  h_enu_sig->Sumw2();
  h_enu_sig->GetXaxis()->SetTitle("E_{#nu_{e}} (GeV)");
  h_enu_sig->GetYaxis()->SetTitle("No. #nu_{e}");
  TH1F *h_enu_sel_sig = new TH1F("h_enu_sel_sig","h_enu_sel_sig",25,0,10);
  h_enu_sel_sig->Sumw2();
  h_enu_sel_sig->SetLineColor(4);
  h_enu_sel_sig->SetLineColor(4);
  h_enu_sel_sig->SetFillColor(4);
  h_enu_sel_sig->SetFillStyle(3003);
  h_enu_sel_sig->GetXaxis()->SetTitle("E_{#nu_{e}} (GeV)");
  h_enu_sel_sig->GetYaxis()->SetTitle("No. #nu_{e}");

  MVASelection->Draw("Enu >> h_enu_sig",WEIGHTING+"*("+SELECTION+")");
  MVASelection->Draw("Enu >> h_enu_sel_sig",WEIGHTING+"*("+SIGNAL_DEF+"&&"+SELECTION+")");

  TEfficiency *h_eff_enu = new TEfficiency(*h_enu_sel_sig,*h_enu_sig);
  h_eff_enu->SetTitle(TString("eff;")+h_enu_sig->GetXaxis()->GetTitle()+TString(";#nu_{e}#rightarrow e purity (No units)"));
  //h_eff_enu->Draw();


  //Q2
  TH1F *h_q2_sig = new TH1F("h_q2_sig","h_q2_sig",25,0,10);
  h_q2_sig->Sumw2();
  h_q2_sig->SetFillStyle(3003);
  h_q2_sig->SetFillColor(1);
  h_q2_sig->GetXaxis()->SetTitle("Q^{2} (GeV^{2})");
  h_q2_sig->GetYaxis()->SetTitle("No. #nu_{e}");
  TH1F *h_q2_sel_sig = new TH1F("h_q2_sel_sig","h_q2_sel_sig",25,0,10);
  h_q2_sel_sig->Sumw2();
  h_q2_sel_sig->SetLineColor(4);
  h_q2_sel_sig->SetFillColor(4);
  h_q2_sel_sig->SetFillStyle(3003);
  h_q2_sel_sig->GetXaxis()->SetTitle("Q^{2} (GeV^{2})");
  h_q2_sel_sig->GetYaxis()->SetTitle("No. #nu_{e}");

  MVASelection->Draw("Q2 >> h_q2_sig",WEIGHTING+"*("+SELECTION+")");
  MVASelection->Draw("Q2 >> h_q2_sel_sig",WEIGHTING+"*("+SIGNAL_DEF+"&&"+SELECTION+")");

  TEfficiency *h_eff_q2 = new TEfficiency(*h_q2_sel_sig,*h_q2_sig);
  h_eff_q2->SetTitle(TString("eff;")+h_q2_sig->GetXaxis()->GetTitle()+TString(";#nu_{e}#rightarrow e purity (No units)"));


  //Lepton angle
  TH1F *h_lepangle_sig = new TH1F("h_lepangle_sig","h_lepangle_sig",25,0,180);
  h_lepangle_sig->Sumw2();
  h_lepangle_sig->SetFillStyle(3003);
  h_lepangle_sig->SetFillColor(1);
  h_lepangle_sig->GetXaxis()->SetTitle("Lepton angle to neutrino (degrees)");
  h_lepangle_sig->GetYaxis()->SetTitle("No. #nu_{e}");
  TH1F *h_lepangle_sel_sig = new TH1F("h_lepangle_sel_sig","h_lepangle_sel_sig",25,0,180);
  h_lepangle_sel_sig->Sumw2();
  h_lepangle_sel_sig->SetLineColor(4);
  h_lepangle_sel_sig->SetFillColor(4);
  h_lepangle_sel_sig->SetFillStyle(3003);
  h_lepangle_sel_sig->GetXaxis()->SetTitle("Lepton angle to neutrino (degrees)");
  h_lepangle_sel_sig->GetYaxis()->SetTitle("No. #nu_{e}");

  MVASelection->Draw("LepNuAngle*180/3.14159265359 >> h_lepangle_sig",WEIGHTING+"*("+SELECTION+")");
  MVASelection->Draw("LepNuAngle*180/3.14159265359 >> h_lepangle_sel_sig",WEIGHTING+"*("+SIGNAL_DEF+"&&"+SELECTION+")");

  TEfficiency *h_eff_lepangle = new TEfficiency(*h_lepangle_sel_sig,*h_lepangle_sig);
  h_eff_lepangle->SetTitle(TString("eff;")+h_lepangle_sig->GetXaxis()->GetTitle()+TString(";#nu_{e}#rightarrow e purity (No units)"));


  //Lepton momentum
  TH1F *h_lepmom_sig = new TH1F("h_lepmom_sig","h_lepmom_sig",25,0,10);
  h_lepmom_sig->Sumw2();
  h_lepmom_sig->SetFillStyle(3003);
  h_lepmom_sig->SetFillColor(1);
  h_lepmom_sig->GetXaxis()->SetTitle("Lepton momentum (GeV)");
  h_lepmom_sig->GetYaxis()->SetTitle("No. #nu_{e}");
  TH1F *h_lepmom_sel_sig = new TH1F("h_lepmom_sel_sig","h_lepmom_sel_sig",25,0,10);
  h_lepmom_sel_sig->Sumw2();
  h_lepmom_sel_sig->SetLineColor(4);
  h_lepmom_sel_sig->SetFillColor(4);
  h_lepmom_sel_sig->SetFillStyle(3003);
  h_lepmom_sel_sig->GetXaxis()->SetTitle("Lepton momentum (GeV)");
  h_lepmom_sel_sig->GetYaxis()->SetTitle("No. #nu_{e}");

  MVASelection->Draw("sqrt(LepMomX*LepMomX + LepMomY*LepMomY + LepMomZ*LepMomZ) >> h_lepmom_sig",WEIGHTING+"*("+SELECTION+")");
  MVASelection->Draw("sqrt(LepMomX*LepMomX + LepMomY*LepMomY + LepMomZ*LepMomZ) >> h_lepmom_sel_sig",WEIGHTING+"*("+SIGNAL_DEF+"&&"+SELECTION+")");

  TEfficiency *h_eff_lepmom = new TEfficiency(*h_lepmom_sel_sig,*h_lepmom_sig);
  h_eff_lepmom->SetTitle(TString("eff;")+h_lepmom_sig->GetXaxis()->GetTitle()+TString(";#nu_{e}#rightarrow e purity (No units)"));






  TFile *output = new TFile(outputname,"RECREATE");
  h_enu_sig->Write();
  h_enu_sel_sig->Write();
  h_eff_enu->Write();
  h_q2_sig->Write();
  h_q2_sel_sig->Write();
  h_eff_q2->Write();
  h_lepangle_sig->Write();
  h_lepangle_sel_sig->Write();
  h_eff_lepangle->Write();
  h_lepmom_sig->Write();
  h_lepmom_sel_sig->Write();
  h_eff_lepmom->Write();


  output->Close();

  /*
  h_eff_q2->Draw();
  gPad->Update();
  h_eff_q2->GetPaintedGraph()->SetMaximum(1.05);
  h_eff_q2->GetPaintedGraph()->SetMinimum(0.0);
  h_eff_q2->GetPaintedGraph()->GetXaxis()->SetRangeUser(0,10.);
  h_q2_sig->Scale(1./h_q2_sig->GetMaximum());
  */











  //Oscillation probability stuff if required
  /*
  float osc_dm2=0.002457;
  float osc_L=1300.; 
  float th13 = 0.148;
  float th23 = 0.738;
  TF1 *osceq = new TF1("f2","[4]*(1-(cos([2])^2*sin(2*[3])^2+sin([3])^4*sin(2*[2])^2)*sin(1.267*[0]*[1]/x)*sin(1.267*[0]*[1]/x))",0.,10.);
  osceq->SetParameters(osc_dm2,osc_L,th13,th23,h_enu_sig->GetMaximum()*0.8);
  osceq->SetLineStyle(2);
  osceq->Draw("same");
  */

}
