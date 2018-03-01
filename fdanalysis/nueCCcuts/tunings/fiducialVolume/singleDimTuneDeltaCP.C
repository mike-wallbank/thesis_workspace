void singleDimTuneDeltaCP(TString inputname, double deltaCP_A = 0, double deltaCP_B = TMath::Pi()/2., TString vol="+z"){

  //Wall distance
  int NBinsX = 500;
  double binLowX = 0;
  double binHighX = 500;

  //Reco energy
  int NBinsY = 50;
  double binLowY = 0;
  double binHighY = 10;



  gROOT->SetStyle("T2K");



  TFile *file = new TFile(inputname,"READ");
  TTree *tree = (TTree*) file->Get("nuecutselection/nuecutsel");

  TString output_name = Form("output_deltaCP_%f_to_%f_FVTune",deltaCP_A,deltaCP_B);
  output_name+=vol+".root";
  TFile *output = new TFile(output_name,"RECREATE");



  gROOT->ProcessLine(".L /dune/app/users/dbrailsf/oscillation/nu_mu/cutsel/tunings/getOscWeights/getProb3ppWeights.C+");
  TString oscWeightA = Form("getProb3ppWeights(0.308,0.02163,0.440,7.49e-5,2.526e-3,%f,Enu,BeamPdg,NuPdg)",deltaCP_A);
  TString oscWeightB = Form("getProb3ppWeights(0.308,0.02163,0.440,7.49e-5,2.526e-3,%f,Enu,BeamPdg,NuPdg)",deltaCP_B);


  //Make the two histograms like
  TH2F *histA = new TH2F("histA","",NBinsX, binLowX, binHighX, NBinsY, binLowY, binHighY);
  histA->GetXaxis()->SetTitle("Distance from wall (cm)");
  histA->GetYaxis()->SetTitle("Reco E_{#nu} (GeV)");
  histA->GetZaxis()->SetTitle("No. events");
  histA->Sumw2();
  TH2F *histB = (TH2F*) histA->Clone("histB");
  //TH2F *histB = new TH2F("histB","",NBinsX, binLowX, binHighX, NBinsY, binLowY, binHighY);

  //figure out what the hell to draw
  TString draw_coordinate;
  double wall_position;
  if (vol.EqualTo("+x")) {
    draw_coordinate = "SelRecoStartX";
    wall_position = 360;
  }
  else if (vol.EqualTo("-x")) {
    draw_coordinate = "SelRecoStartX";
    wall_position = -360;
  }
  else if (vol.EqualTo("+y")) {
    draw_coordinate = "SelRecoStartY";
    wall_position = 600;
  }
  else if (vol.EqualTo("-y")) {
    draw_coordinate = "SelRecoStartY";
    wall_position = -600;
  }
  else if (vol.EqualTo("+z")) {
    draw_coordinate = "SelRecoStartZ";
    wall_position = 1394;
  }
  else if (vol.EqualTo("-z")) {
    draw_coordinate = "SelRecoStartZ";
    wall_position = 0;
  }
  else {
    std::cout<<"Incorrect wall specified: " << vol << "   Exiting!"<<std::endl;
    return;
  }

  TString draw_distance = Form("(abs("+draw_coordinate+" - %lf))",wall_position);
  std::cout<<draw_distance<<std::endl;


  tree->Draw("RecoENu:"+draw_distance+" >> histA","("+oscWeightA+"*ProjectedPOTWeight)*1");
  tree->Draw("RecoENu:"+draw_distance+" >> histB","("+oscWeightB+"*ProjectedPOTWeight)*1");

  histA->Write();
  histB->Write();


  TH1F *hist_pref1;
  TH1F *hist_pref2;

  double best_chi2 = 0;
  double best_walldist = -99999;
  //hist to hold the chi2
  TH1F *h_chi2 = new TH1F("h_chi2","",NBinsY,binLowY,binHighY);
  h_chi2->GetXaxis()->SetTitle(histA->GetYaxis()->GetTitle());
  h_chi2->Sumw2();
  TGraph *g_chi2 = new TGraph();

  //Loop over the Xbins of the histogram and start smashing some projections
  for (int i_bin = 1; i_bin <= histA->GetXaxis()->GetNbins(); i_bin++){
    double current_walldist = histA->GetXaxis()->GetBinLowEdge(i_bin);
    std::cout<<"Testing for distance from wall  > " << current_walldist << " cm (Up to and including "  << histA->GetXaxis()->GetBinLowEdge(histA->GetXaxis()->GetNbins())<< " cm)" << std::endl;
    
    //Make the projections
    TString histA_proj_name = Form("h_deltaCP_%f_WallDistGR%f",deltaCP_A,current_walldist);
    TH1D *histA_proj = histA->ProjectionY(histA_proj_name, i_bin, -1, "e");
    histA_proj->Write();

    TString histB_proj_name = Form("h_deltaCP_%f_WallDistGR%f",deltaCP_B,current_walldist);
    TH1D *histB_proj = histB->ProjectionY(histB_proj_name, i_bin, -1, "e");
    histB_proj->Write();

    //Now have two histograms, lets calculate the chi2
    double chi2 = 0;
    for (int bin = 1; bin <= histA_proj->GetXaxis()->GetNbins(); bin++){
      double hist_val = histA_proj->GetBinContent(bin);
      double hist_err = histA_proj->GetBinError(bin);
      double hist2_val = histB_proj->GetBinContent(bin);
      double hist2_err = histB_proj->GetBinError(bin);

      double numerator = (hist_val-hist2_val)*(hist_val-hist2_val);
      double denominator = (hist_err*hist_err + hist2_err*hist2_err);
      double d_chi2 = 0;
      if (denominator > 0) d_chi2 = numerator/denominator;

      chi2 += d_chi2;
      h_chi2->Fill(histA_proj->GetBinCenter(bin),d_chi2);
    }
    TString h_chi2_name = Form("h_chi2_WallDistGR%f",current_walldist);
    h_chi2->Write(h_chi2_name);
    g_chi2->SetPoint(g_chi2->GetN(),current_walldist,chi2);
    if (chi2 > best_chi2){
      best_chi2 = chi2;
      best_walldist = current_walldist;
    }
    std::cout<<"---chi2: " << chi2 << std::endl;
    h_chi2->Reset();


  }
  std::cout<<"----Max chi2: " << best_chi2 << std::endl;
  std::cout<<"----Best wall dist: " << best_walldist << std::endl;

  g_chi2->Draw();
  g_chi2->GetXaxis()->SetTitle("Distance from wall (cm)");
  g_chi2->GetYaxis()->SetTitle("#chi^{2}");
  g_chi2->Write("g_chi2");

  output->Close();

}
