void efficiency(TString inputname,TString mvacut="0.8",TString outputname="hists_efficiencies.root",TString friendfile=""){


  TString INFV="(abs(nuvtxx_truth)<360-50&&abs(nuvtxy_truth)<600-50&&nuvtxz_truth>50&&nuvtxz_truth<1394-150)";
  TString SIGNAL_DEF="(abs(beamPdg)==14 && abs(neu)==12 && cc==1 &&"+ INFV + ")";
  TString WEIGHTING="projected_weight";


  gROOT->SetStyle("T2K");


  //Figure out how we are going to select
  //Normal selection mode
  TString SELECTION="mvaresult>"+mvacut;
  //Selecting with a friend tree
  if (friendfile!=""){
    SELECTION="mvatree.newmvaresult>"+mvacut;
  }

  //Get the file
  TFile *file = new TFile(inputname,"READ");
  //Get the tree
  TTree *MVASelection = (TTree*) file->Get("mvaselect/MVASelection");
  //If asked for, get the friend tree
  if (friendfile!=""){
    MVASelection->AddFriend("mvatree",friendfile);
  }

  TEventList alllist("alllist"), sellist("sellist");
  MVASelection->Draw(">>alllist",WEIGHTING+"*("+SIGNAL_DEF+")");
  MVASelection->Draw(">>sellist",WEIGHTING+"*("+SIGNAL_DEF+"&&"+SELECTION+")");
  std::cout << "Overall efficiency: " << sellist.GetN()/(float)alllist.GetN() << std::endl;

  //ENu
  TH1F *h_enu_sig = new TH1F("h_enu_sig","h_enu_sig",25,0,10);
  h_enu_sig->Sumw2();
  h_enu_sig->GetXaxis()->SetTitle("E_{#nu} (GeV)");
  h_enu_sig->GetYaxis()->SetTitle("No. #nu");
  TH1F *h_enu_sel_sig = new TH1F("h_enu_sel_sig","h_enu_sel_sig",25,0,10);
  h_enu_sel_sig->Sumw2();
  h_enu_sel_sig->SetLineColor(4);
  h_enu_sel_sig->SetLineColor(4);
  h_enu_sel_sig->SetFillColor(4);
  h_enu_sel_sig->SetFillStyle(3003);
  h_enu_sel_sig->GetXaxis()->SetTitle("E_{#nu} (GeV)");
  h_enu_sel_sig->GetYaxis()->SetTitle("No. #nu");

  MVASelection->Draw("Ev >> h_enu_sig",WEIGHTING+"*("+SIGNAL_DEF+")");
  MVASelection->Draw("Ev >> h_enu_sel_sig",WEIGHTING+"*("+SIGNAL_DEF+"&&"+SELECTION+")");

  TEfficiency *h_eff_enu = new TEfficiency(*h_enu_sel_sig,*h_enu_sig);
  h_eff_enu->SetTitle(TString("eff;")+h_enu_sig->GetXaxis()->GetTitle()+TString(";Efficiency (No units)"));
  //h_eff_enu->Draw();


  //Q2
  TH1F *h_q2_sig = new TH1F("h_q2_sig","h_q2_sig",25,0,10);
  h_q2_sig->Sumw2();
  h_q2_sig->SetFillStyle(3003);
  h_q2_sig->SetFillColor(1);
  h_q2_sig->GetXaxis()->SetTitle("Q^{2} (GeV^{2})");
  h_q2_sig->GetYaxis()->SetTitle("No. #nu");
  TH1F *h_q2_sel_sig = new TH1F("h_q2_sel_sig","h_q2_sel_sig",25,0,10);
  h_q2_sel_sig->Sumw2();
  h_q2_sel_sig->SetLineColor(4);
  h_q2_sel_sig->SetFillColor(4);
  h_q2_sel_sig->SetFillStyle(3003);
  h_q2_sel_sig->GetXaxis()->SetTitle("Q^{2} (GeV^{2})");
  h_q2_sel_sig->GetYaxis()->SetTitle("No. #nu");

  MVASelection->Draw("Q2 >> h_q2_sig",WEIGHTING+"*("+SIGNAL_DEF+")");
  MVASelection->Draw("Q2 >> h_q2_sel_sig",WEIGHTING+"*("+SIGNAL_DEF+"&&"+SELECTION+")");

  TEfficiency *h_eff_q2 = new TEfficiency(*h_q2_sel_sig,*h_q2_sig);
  h_eff_q2->SetTitle(TString("eff;")+h_q2_sig->GetXaxis()->GetTitle()+TString(";Efficiency (No units)"));



  //Lepton angle
  TH1F *h_lepangle_sig = new TH1F("h_lepangle_sig","h_lepangle_sig",25,0,180);
  h_lepangle_sig->Sumw2();
  h_lepangle_sig->SetFillStyle(3003);
  h_lepangle_sig->SetFillColor(1);
  h_lepangle_sig->GetXaxis()->SetTitle("Lepton angle to neutrino (degrees)");
  h_lepangle_sig->GetYaxis()->SetTitle("No. #nu");
  TH1F *h_lepangle_sel_sig = new TH1F("h_lepangle_sel_sig","h_lepangle_sel_sig",25,0,180);
  h_lepangle_sel_sig->Sumw2();
  h_lepangle_sel_sig->SetLineColor(4);
  h_lepangle_sel_sig->SetFillColor(4);
  h_lepangle_sel_sig->SetFillStyle(3003);
  h_lepangle_sel_sig->GetXaxis()->SetTitle("Lepton angle to neutrino (degrees)");
  h_lepangle_sel_sig->GetYaxis()->SetTitle("No. #nu");

  MVASelection->Draw("LepNuAngle*180/3.14159265359 >> h_lepangle_sig",WEIGHTING+"*("+SIGNAL_DEF+")");
  MVASelection->Draw("LepNuAngle*180/3.14159265359 >> h_lepangle_sel_sig",WEIGHTING+"*("+SIGNAL_DEF+"&&"+SELECTION+")");

  TEfficiency *h_eff_lepangle = new TEfficiency(*h_lepangle_sel_sig,*h_lepangle_sig);
  h_eff_lepangle->SetTitle(TString("eff;")+h_lepangle_sig->GetXaxis()->GetTitle()+TString(";Efficiency (No units)"));

  //Lepton momentum
  TH1F *h_lepmom_sig = new TH1F("h_lepmom_sig","h_lepmom_sig",25,0,10);
  h_lepmom_sig->Sumw2();
  h_lepmom_sig->SetFillStyle(3003);
  h_lepmom_sig->SetFillColor(1);
  h_lepmom_sig->GetXaxis()->SetTitle("Lepton momentum (GeV)");
  h_lepmom_sig->GetYaxis()->SetTitle("No. #nu");
  TH1F *h_lepmom_sel_sig = new TH1F("h_lepmom_sel_sig","h_lepmom_sel_sig",25,0,10);
  h_lepmom_sel_sig->Sumw2();
  h_lepmom_sel_sig->SetLineColor(4);
  h_lepmom_sel_sig->SetFillColor(4);
  h_lepmom_sel_sig->SetFillStyle(3003);
  h_lepmom_sel_sig->GetXaxis()->SetTitle("Lepton momentum (GeV)");
  h_lepmom_sel_sig->GetYaxis()->SetTitle("No. #nu");

  MVASelection->Draw("sqrt(LepMomX*LepMomX + LepMomY*LepMomY + LepMomZ*LepMomZ) >> h_lepmom_sig",WEIGHTING+"*("+SIGNAL_DEF+")");
  MVASelection->Draw("sqrt(LepMomX*LepMomX + LepMomY*LepMomY + LepMomZ*LepMomZ) >> h_lepmom_sel_sig",WEIGHTING+"*("+SIGNAL_DEF+"&&"+SELECTION+")");

  TEfficiency *h_eff_lepmom = new TEfficiency(*h_lepmom_sel_sig,*h_lepmom_sig);
  h_eff_lepmom->SetTitle(TString("eff;")+h_lepmom_sig->GetXaxis()->GetTitle()+TString(";Efficiency (No units)"));




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
