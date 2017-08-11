{

  gStyle->SetOptStat(0);
  const int kMaxParticles = 1000000;

  TFile* inFile = new TFile("/pnfs/dune/scratch/users/wallbank/v06_45_01/reconana/pdkcosmobg/anahist.root");
  //TFile* inFile = new TFile("/dune/app/users/wallbank/larsoft-pdk/workspace/protonDecay/pdk_recon_ana.root");
  TTree* inTree = (TTree*)inFile->Get("pdkreconana/ReconPerformance");
  if (!inTree) {
    std::cout << "Input tree now found." << std::endl;
    return 0;
  }

  int fNKaons;
  int fNMuons;
  int fNMuons20cm;
  int fNHits2cm;

  int fNParticles;
  int fPDG[kMaxParticles];
  double fTrueEnergy[kMaxParticles];
  int fNParticleTracks[kMaxParticles];
  double fEfficiency[kMaxParticles];
  int fReconHits[kMaxParticles][3];
  int fReconPDG[kMaxParticles][3];
  double fPIDA[kMaxParticles][3];

  int fNTracks;
  int fTrackPDG[kMaxParticles];
  double fTrackTrueEnergy[kMaxParticles];
  int fTrackReconHits[kMaxParticles][3];
  int fTrackReconPDG[kMaxParticles][3];
  double fTrackPIDA[kMaxParticles][3];

  inTree->SetBranchAddress("NKaons",     &fNKaons);
  inTree->SetBranchAddress("NMuons",     &fNMuons);
  inTree->SetBranchAddress("NMuons20cm", &fNMuons20cm);
  inTree->SetBranchAddress("NHits2cm",   &fNHits2cm);

  inTree->SetBranchAddress("NParticles",      &fNParticles);
  inTree->SetBranchAddress("PDG",             fPDG);
  inTree->SetBranchAddress("TrueEnergy",      fTrueEnergy);
  inTree->SetBranchAddress("NParticleTracks", fNParticleTracks);
  inTree->SetBranchAddress("Efficiency",      fEfficiency);
  inTree->SetBranchAddress("ReconHits",       fReconHits);
  inTree->SetBranchAddress("ReconPDG",        fReconPDG);
  inTree->SetBranchAddress("PIDA",            fPIDA);

  inTree->SetBranchAddress("NTracks",         &fNTracks);
  inTree->SetBranchAddress("TrackPDG",        fTrackPDG);
  inTree->SetBranchAddress("TrackTrueEnergy", fTrackTrueEnergy);
  inTree->SetBranchAddress("TrackReconHits",  fTrackReconHits);
  inTree->SetBranchAddress("TrackReconPDG",   fTrackReconPDG);
  inTree->SetBranchAddress("TrackPIDA",       fTrackPIDA);

  TH1D* hProtonPIDA = new TH1D("ProtonPIDA",";PIDA;",100,0,40);
  TH1D* hMuonPIDA = new TH1D("MuonPIDA",";PIDA;",100,0,40);
  TH1D* hKaonPIDA = new TH1D("KaonPIDA",";PIDA;",100,0,40);

  TH1D* hProtonPIDAPlane = new TH1D("ProtonPIDAPlane",";PIDA;",100,0,40);
  TH1D* hMuonPIDAPlane = new TH1D("MuonPIDAPlane",";PIDA;",100,0,40);
  TH1D* hKaonPIDAPlane = new TH1D("KaonPIDAPlane",";PIDA;",100,0,40);

  TH1D* hProtonProtonPID = new TH1D("ProtonProtonPID", ";Energy (GeV);", 100,0,10);
  TH1D* hProtonMuonPID   = new TH1D("ProtonMuonPID",   ";Energy (GeV);", 100,0,10);
  TH1D* hProtonKaonPID   = new TH1D("ProtonKaonPID",   ";Energy (GeV);", 100,0,10);
  TH1D* hProtonOtherPID  = new TH1D("ProtonOtherPID",  ";Energy (GeV);", 100,0,10);
  TH1D* hMuonProtonPID   = new TH1D("MuonProtonPID",   ";Energy (GeV);", 100,0,1000);
  TH1D* hMuonMuonPID     = new TH1D("MuonMuonPID",     ";Energy (GeV);", 100,0,1000);
  TH1D* hMuonKaonPID     = new TH1D("MuonKaonPID",     ";Energy (GeV);", 100,0,1000);
  TH1D* hMuonOtherPID    = new TH1D("MuonOtherPID",    ";Energy (GeV);", 100,0,1000);
  TH1D* hKaonProtonPID   = new TH1D("KaonProtonPID",   ";Energy (GeV);", 100,0,10);
  TH1D* hKaonMuonPID     = new TH1D("KaonMuonPID",     ";Energy (GeV);", 100,0,10);
  TH1D* hKaonKaonPID     = new TH1D("KaonKaonPID",     ";Energy (GeV);", 100,0,10);
  TH1D* hKaonOtherPID    = new TH1D("KaonOtherPID",    ";Energy (GeV);", 100,0,10);
  // TH1D* hOtherProtonPID  = new TH1D("OtherProtonPID",  ";Energy (GeV);", 100,0,100);
  // TH1D* hOtherMuonPID    = new TH1D("OtherMuonPID",    ";Energy (GeV);", 100,0,100);
  // TH1D* hOtherKaonPID    = new TH1D("OtherKaonPID",    ";Energy (GeV);", 100,0,100);
  // TH1D* hOtherOtherPID   = new TH1D("OtherOtherPID",   ";Energy (GeV);", 100,0,100);

  TH1D* hProtonTrackProtonPID = new TH1D("ProtonTrackProtonPID", ";Energy (GeV);", 100,0,10);
  TH1D* hProtonTrackMuonPID   = new TH1D("ProtonTrackMuonPID",   ";Energy (GeV);", 100,0,10);
  TH1D* hProtonTrackKaonPID   = new TH1D("ProtonTrackKaonPID",   ";Energy (GeV);", 100,0,10);
  TH1D* hProtonTrackOtherPID  = new TH1D("ProtonTrackOtherPID",  ";Energy (GeV);", 100,0,10);
  TH1D* hMuonTrackProtonPID   = new TH1D("MuonTrackProtonPID",   ";Energy (GeV);", 100,0,1000);
  TH1D* hMuonTrackMuonPID     = new TH1D("MuonTrackMuonPID",     ";Energy (GeV);", 100,0,1000);
  TH1D* hMuonTrackKaonPID     = new TH1D("MuonTrackKaonPID",     ";Energy (GeV);", 100,0,1000);
  TH1D* hMuonTrackOtherPID    = new TH1D("MuonTrackOtherPID",    ";Energy (GeV);", 100,0,1000);
  TH1D* hKaonTrackProtonPID   = new TH1D("KaonTrackProtonPID",   ";Energy (GeV);", 100,0,10);
  TH1D* hKaonTrackMuonPID     = new TH1D("KaonTrackMuonPID",     ";Energy (GeV);", 100,0,10);
  TH1D* hKaonTrackKaonPID     = new TH1D("KaonTrackKaonPID",     ";Energy (GeV);", 100,0,10);
  TH1D* hKaonTrackOtherPID    = new TH1D("KaonTrackOtherPID",    ";Energy (GeV);", 100,0,10);
  // TH1D* hOtherTrackProtonPID  = new TH1D("OtherTrackProtonPID",  ";Energy (GeV);", 100,0,100);
  // TH1D* hOtherTrackMuonPID    = new TH1D("OtherTrackMuonPID",    ";Energy (GeV);", 100,0,100);
  // TH1D* hOtherTrackKaonPID    = new TH1D("OtherTrackKaonPID",    ";Energy (GeV);", 100,0,100);
  // TH1D* hOtherTrackOtherPID   = new TH1D("OtherTrackOtherPID",   ";Energy (GeV);", 100,0,100);

  for (int event = 0; event < inTree->GetEntriesFast(); ++event) {

    if (event % 1000 == 0)
      std::cout << "Processing event " << event << std::endl;

    inTree->GetEntry(event);

    for (int track = 0; track < fNTracks; ++track) {
      int best_plane = -1;
      int largest_nhits = 0;
      for (int plane = 0; plane < 3; ++plane) {
	if (fTrackReconHits[track][plane] > largest_nhits) {
	  best_plane = plane;
	  largest_nhits = fTrackReconHits[track][plane];
	}
	if (fTrackPIDA[track][plane] == 0)
	  continue;
	if (fTrackPDG[track] == 2212)
	  hProtonPIDA->Fill(fTrackPIDA[track][plane]);
	if (fTrackPDG[track] == 13)
	  hMuonPIDA->Fill(fTrackPIDA[track][plane]);
	if (fTrackPDG[track] == 321)
	  hKaonPIDA->Fill(fTrackPIDA[track][plane]);
      }
      if (best_plane > -1) {
	if (fTrackPDG[track] == 2212) {
	  hProtonPIDAPlane->Fill(fTrackPIDA[track][best_plane]);
	  if (fTrackReconPDG[track][best_plane] == 2212)
	    hProtonTrackProtonPID->Fill(fTrackTrueEnergy[track]);
	  else if (fTrackReconPDG[track][best_plane] == 13)
	    hProtonTrackMuonPID->Fill(fTrackTrueEnergy[track]);
	  else if (fTrackReconPDG[track][best_plane] == 321)
	    hProtonTrackKaonPID->Fill(fTrackTrueEnergy[track]);
	  else
	    hProtonTrackOtherPID->Fill(fTrackTrueEnergy[track]);
	}
	if (fTrackPDG[track] == 13) {
	  hMuonPIDAPlane->Fill(fTrackPIDA[track][best_plane]);
	  if (fTrackReconPDG[track][best_plane] == 2212)
	    hMuonTrackProtonPID->Fill(fTrackTrueEnergy[track]);
	  else if (fTrackReconPDG[track][best_plane] == 13)
	    hMuonTrackMuonPID->Fill(fTrackTrueEnergy[track]);
	  else if (fTrackReconPDG[track][best_plane] == 321)
	    hMuonTrackKaonPID->Fill(fTrackTrueEnergy[track]);
	  else
	    hMuonTrackOtherPID->Fill(fTrackTrueEnergy[track]);
	}
	if (fTrackPDG[track] == 321) {
	  hKaonPIDAPlane->Fill(fTrackPIDA[track][best_plane]);
	  if (fTrackReconPDG[track][best_plane] == 2212)
	    hKaonTrackProtonPID->Fill(fTrackTrueEnergy[track]);
	  else if (fTrackReconPDG[track][best_plane] == 13)
	    hKaonTrackMuonPID->Fill(fTrackTrueEnergy[track]);
	  else if (fTrackReconPDG[track][best_plane] == 321)
	    hKaonTrackKaonPID->Fill(fTrackTrueEnergy[track]);
	  else
	    hKaonTrackOtherPID->Fill(fTrackTrueEnergy[track]);
	}
      }
    }

    for (int particle = 0; particle < fNParticles; ++particle) {
      int best_plane = -1;
      int largest_nhits = 0;
      for (int plane = 0; plane < 3; ++plane) {
      	if (fReconHits[particle][plane] > largest_nhits) {
      	  best_plane = plane;
      	  largest_nhits = fReconHits[particle][plane];
      	}
      }
      if (best_plane < 0)
      	continue;
      if (fPDG[particle] == 2212) {
    	if (fReconPDG[particle][best_plane] == 2212)
    	  hProtonProtonPID->Fill(fTrueEnergy[particle]);
    	else if (fReconPDG[particle][best_plane] == 13)
    	  hProtonMuonPID->Fill(fTrueEnergy[particle]);
    	else if (fReconPDG[particle][best_plane] == 321)
    	  hProtonKaonPID->Fill(fTrueEnergy[particle]);
    	else
    	  hProtonOtherPID->Fill(fTrueEnergy[particle]);
      }
      else if (fPDG[particle] == 13) {
    	if (fReconPDG[particle][best_plane] == 2212)
    	  hMuonProtonPID->Fill(fTrueEnergy[particle]);
    	else if (fReconPDG[particle][best_plane] == 13)
    	  hMuonMuonPID->Fill(fTrueEnergy[particle]);
    	else if (fReconPDG[particle][best_plane] == 321)
    	  hMuonKaonPID->Fill(fTrueEnergy[particle]);
    	else
    	  hMuonOtherPID->Fill(fTrueEnergy[particle]);
      }
      else if (fPDG[particle] == 321) {
    	if (fReconPDG[particle][best_plane] == 2212)
    	  hKaonProtonPID->Fill(fTrueEnergy[particle]);
    	else if (fReconPDG[particle][best_plane] == 13)
    	  hKaonMuonPID->Fill(fTrueEnergy[particle]);
    	else if (fReconPDG[particle][best_plane] == 321)
    	  hKaonKaonPID->Fill(fTrueEnergy[particle]);
    	else
    	  hKaonOtherPID->Fill(fTrueEnergy[particle]);
      }
    } // particle

  } // event

  TCanvas* canv = new TCanvas("canv","",800,600);
  hProtonPIDA->Scale(1./hProtonPIDA->GetEntries());
  hProtonPIDA->SetLineColor(2);
  hProtonPIDA->SetFillColor(2);
  hProtonPIDA->SetFillStyle(3003);
  hMuonPIDA->Scale(1./hMuonPIDA->GetEntries());
  hMuonPIDA->SetLineColor(3);
  hMuonPIDA->SetFillColor(3);
  hMuonPIDA->SetFillStyle(3003);
  hKaonPIDA->Scale(1./hKaonPIDA->GetEntries());
  hKaonPIDA->SetLineColor(4);
  hKaonPIDA->SetFillColor(4);
  hKaonPIDA->SetFillStyle(3003);
  hKaonPIDA->Draw("hist");
  hMuonPIDA->Draw("hist same");
  hProtonPIDA->Draw("hist same");
  TLegend* leg = new TLegend(0.6,0.7,0.9,0.9);
  leg->AddEntry(hProtonPIDA, "Proton", "f");
  leg->AddEntry(hMuonPIDA,   "Muon",   "f");
  leg->AddEntry(hKaonPIDA,   "Kaon",   "f");
  leg->Draw();
  canv->SaveAs("PIDA.eps");

  canv->cd();
  canv->Clear();
  hProtonPIDAPlane->Scale(1./hProtonPIDAPlane->GetEntries());
  hProtonPIDAPlane->SetLineColor(2);
  hProtonPIDAPlane->SetFillColor(2);
  hProtonPIDAPlane->SetFillStyle(3003);
  hMuonPIDAPlane->Scale(1./hMuonPIDAPlane->GetEntries());
  hMuonPIDAPlane->SetLineColor(3);
  hMuonPIDAPlane->SetFillColor(3);
  hMuonPIDAPlane->SetFillStyle(3003);
  hKaonPIDAPlane->Scale(1./hKaonPIDAPlane->GetEntries());
  hKaonPIDAPlane->SetLineColor(4);
  hKaonPIDAPlane->SetFillColor(4);
  hKaonPIDAPlane->SetFillStyle(3003);
  hKaonPIDAPlane->Draw("hist");
  hMuonPIDAPlane->Draw("hist same");
  hProtonPIDAPlane->Draw("hist same");
  leg->Clear();
  leg->AddEntry(hProtonPIDAPlane, "Proton", "f");
  leg->AddEntry(hMuonPIDAPlane,   "Muon",   "f");
  leg->AddEntry(hKaonPIDAPlane,   "Kaon",   "f");
  leg->Draw();
  canv->SaveAs("PIDAPlane.eps");

  canv->cd();
  canv->Clear();
  hProtonProtonPID->SetLineColor(2);
  hProtonProtonPID->SetFillColor(2);
  hProtonProtonPID->SetFillStyle(3003);
  hProtonMuonPID->SetLineColor(3);
  hProtonMuonPID->SetFillColor(3);
  hProtonMuonPID->SetFillStyle(3003);
  hProtonKaonPID->SetLineColor(4);
  hProtonKaonPID->SetFillColor(4);
  hProtonKaonPID->SetFillStyle(3003);
  hProtonOtherPID->SetLineColor(5);
  hProtonOtherPID->SetFillColor(5);
  hProtonOtherPID->SetFillStyle(3003);
  hProtonProtonPID->Draw();
  hProtonMuonPID->Draw("same");
  hProtonKaonPID->Draw("same");
  hProtonOtherPID->Draw("same");
  leg->Clear();
  leg->AddEntry(hProtonProtonPID, "Proton", "f");
  leg->AddEntry(hProtonMuonPID,   "Muon",   "f");
  leg->AddEntry(hProtonKaonPID,   "Kaon",   "f");
  leg->AddEntry(hProtonOtherPID,  "Other",  "f");
  leg->Draw();
  canv->SaveAs("ProtonPID.eps");

  canv->cd();
  canv->Clear();
  hMuonProtonPID->SetLineColor(2);
  hMuonProtonPID->SetFillColor(2);
  hMuonProtonPID->SetFillStyle(3003);
  hMuonMuonPID->SetLineColor(3);
  hMuonMuonPID->SetFillColor(3);
  hMuonMuonPID->SetFillStyle(3003);
  hMuonKaonPID->SetLineColor(4);
  hMuonKaonPID->SetFillColor(4);
  hMuonKaonPID->SetFillStyle(3003);
  hMuonOtherPID->SetLineColor(5);
  hMuonOtherPID->SetFillColor(5);
  hMuonOtherPID->SetFillStyle(3003);
  hMuonMuonPID->Draw();
  hMuonProtonPID->Draw("same");
  hMuonKaonPID->Draw("same");
  hMuonOtherPID->Draw("same");
  leg->Clear();
  leg->AddEntry(hMuonProtonPID, "Proton", "f");
  leg->AddEntry(hMuonMuonPID,   "Muon",   "f");
  leg->AddEntry(hMuonKaonPID,   "Kaon",   "f");
  leg->AddEntry(hMuonOtherPID,  "Other",  "f");
  leg->Draw();
  canv->SaveAs("MuonPID.eps");

  canv->cd();
  canv->Clear();
  hKaonProtonPID->SetLineColor(2);
  hKaonProtonPID->SetFillColor(2);
  hKaonProtonPID->SetFillStyle(3003);
  hKaonMuonPID->SetLineColor(3);
  hKaonMuonPID->SetFillColor(3);
  hKaonMuonPID->SetFillStyle(3003);
  hKaonKaonPID->SetLineColor(4);
  hKaonKaonPID->SetFillColor(4);
  hKaonKaonPID->SetFillStyle(3003);
  hKaonOtherPID->SetLineColor(5);
  hKaonOtherPID->SetFillColor(5);
  hKaonOtherPID->SetFillStyle(3003);
  hKaonProtonPID->Draw();
  hKaonMuonPID->Draw("same");
  hKaonKaonPID->Draw("same");
  hKaonOtherPID->Draw("same");
  leg->Clear();
  leg->AddEntry(hKaonProtonPID, "Proton", "f");
  leg->AddEntry(hKaonMuonPID,   "Muon",   "f");
  leg->AddEntry(hKaonKaonPID,   "Kaon",   "f");
  leg->AddEntry(hKaonOtherPID,  "Other",  "f");
  leg->Draw();
  canv->SaveAs("KaonPID.eps");

  canv->cd();
  canv->Clear();
  hProtonTrackProtonPID->SetLineColor(2);
  hProtonTrackProtonPID->SetFillColor(2);
  hProtonTrackProtonPID->SetFillStyle(3003);
  hProtonTrackMuonPID->SetLineColor(3);
  hProtonTrackMuonPID->SetFillColor(3);
  hProtonTrackMuonPID->SetFillStyle(3003);
  hProtonTrackKaonPID->SetLineColor(4);
  hProtonTrackKaonPID->SetFillColor(4);
  hProtonTrackKaonPID->SetFillStyle(3003);
  hProtonTrackOtherPID->SetLineColor(5);
  hProtonTrackOtherPID->SetFillColor(5);
  hProtonTrackOtherPID->SetFillStyle(3003);
  hProtonTrackProtonPID->Draw();
  hProtonTrackMuonPID->Draw("same");
  hProtonTrackKaonPID->Draw("same");
  hProtonTrackOtherPID->Draw("same");
  leg->Clear();
  leg->AddEntry(hProtonTrackProtonPID, "Proton", "f");
  leg->AddEntry(hProtonTrackMuonPID,   "Muon",   "f");
  leg->AddEntry(hProtonTrackKaonPID,   "Kaon",   "f");
  leg->AddEntry(hProtonTrackOtherPID,  "Other",  "f");
  leg->Draw();
  canv->SaveAs("ProtonTrackPID.eps");

  canv->cd();
  canv->Clear();
  hMuonTrackProtonPID->SetLineColor(2);
  hMuonTrackProtonPID->SetFillColor(2);
  hMuonTrackProtonPID->SetFillStyle(3003);
  hMuonTrackMuonPID->SetLineColor(3);
  hMuonTrackMuonPID->SetFillColor(3);
  hMuonTrackMuonPID->SetFillStyle(3003);
  hMuonTrackKaonPID->SetLineColor(4);
  hMuonTrackKaonPID->SetFillColor(4);
  hMuonTrackKaonPID->SetFillStyle(3003);
  hMuonTrackOtherPID->SetLineColor(5);
  hMuonTrackOtherPID->SetFillColor(5);
  hMuonTrackOtherPID->SetFillStyle(3003);
  hMuonTrackMuonPID->Draw();
  hMuonTrackProtonPID->Draw("same");
  hMuonTrackKaonPID->Draw("same");
  hMuonTrackOtherPID->Draw("same");
  leg->Clear();
  leg->AddEntry(hMuonTrackProtonPID, "Proton", "f");
  leg->AddEntry(hMuonTrackMuonPID,   "Muon",   "f");
  leg->AddEntry(hMuonTrackKaonPID,   "Kaon",   "f");
  leg->AddEntry(hMuonTrackOtherPID,  "Other",  "f");
  leg->Draw();
  canv->SaveAs("MuonTrackPID.eps");

  canv->cd();
  canv->Clear();
  hKaonTrackProtonPID->SetLineColor(2);
  hKaonTrackProtonPID->SetFillColor(2);
  hKaonTrackProtonPID->SetFillStyle(3003);
  hKaonTrackMuonPID->SetLineColor(3);
  hKaonTrackMuonPID->SetFillColor(3);
  hKaonTrackMuonPID->SetFillStyle(3003);
  hKaonTrackKaonPID->SetLineColor(4);
  hKaonTrackKaonPID->SetFillColor(4);
  hKaonTrackKaonPID->SetFillStyle(3003);
  hKaonTrackOtherPID->SetLineColor(5);
  hKaonTrackOtherPID->SetFillColor(5);
  hKaonTrackOtherPID->SetFillStyle(3003);
  hKaonTrackProtonPID->Draw();
  hKaonTrackMuonPID->Draw("same");
  hKaonTrackKaonPID->Draw("same");
  hKaonTrackOtherPID->Draw("same");
  leg->Clear();
  leg->AddEntry(hKaonTrackProtonPID, "Proton", "f");
  leg->AddEntry(hKaonTrackMuonPID,   "Muon",   "f");
  leg->AddEntry(hKaonTrackKaonPID,   "Kaon",   "f");
  leg->AddEntry(hKaonTrackOtherPID,  "Other",  "f");
  leg->Draw();
  canv->SaveAs("KaonTrackPID.eps");

  return 0;

}
