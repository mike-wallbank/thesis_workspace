{

  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);
  gStyle->SetOptStat("e");
  gStyle->SetStatX(0.9);
  gStyle->SetStatY(0.937);
  gStyle->SetStatW(0.3);
  gStyle->SetStatH(0.15);
  gStyle->SetHistLineColor(1);
  TGaxis::SetMaxDigits(3);

  const int kMaxObjects = 999;

  TFile* inFile = new TFile("nuecutselection.root","r");
  TTree* inTree = (TTree*)inFile->Get("nuecutselection/PIDAna");

  int fRun;
  int fSubRun;
  int fNObjects;
  bool fTrack[kMaxObjects], fShower[kMaxObjects];
  int fTruePDG[kMaxObjects], fRecoPDG[kMaxObjects];
  double fElectronMVA[kMaxObjects], fMuonMVA[kMaxObjects], fPhotonMVA[kMaxObjects], fProtonMVA[kMaxObjects], fPionMVA[kMaxObjects];
  double fObjPurity[kMaxObjects];
  char* fPrimary[kMaxObjects];
  double fTrueEnergy[kMaxObjects], fRecoEnergy[kMaxObjects];
  double fTrueX[kMaxObjects], fTrueY[kMaxObjects], fTrueZ[kMaxObjects];
  double fTrueEndX[kMaxObjects], fTrueEndY[kMaxObjects], fTrueEndZ[kMaxObjects];
  double fRecoX[kMaxObjects], fRecoY[kMaxObjects], fRecoZ[kMaxObjects];
  double fRecoEndX[kMaxObjects], fRecoEndY[kMaxObjects], fRecoEndZ[kMaxObjects];
  double fRecoLength[kMaxObjects];
  int fRecoPoints[kMaxObjects];

  inTree->SetBranchAddress("Run",         &fRun);
  inTree->SetBranchAddress("SubRun",      &fSubRun);
  inTree->SetBranchAddress("NObjects",    &fNObjects);
  inTree->SetBranchAddress("Track",       fTrack);
  inTree->SetBranchAddress("Shower",      fShower);
  inTree->SetBranchAddress("TruePDG",     fTruePDG);
  inTree->SetBranchAddress("RecoPDG",     fRecoPDG);
  inTree->SetBranchAddress("ElectronMVA", fElectronMVA);
  inTree->SetBranchAddress("MuonMVA",     fMuonMVA);
  inTree->SetBranchAddress("PhotonMVA",   fPhotonMVA);
  inTree->SetBranchAddress("ProtonMVA",   fProtonMVA);
  inTree->SetBranchAddress("PionMVA",     fPionMVA);
  inTree->SetBranchAddress("ObjPurity",   fObjPurity);
  inTree->SetBranchAddress("Primary",     fPrimary);
  inTree->SetBranchAddress("TrueEnergy",  fTrueEnergy);
  inTree->SetBranchAddress("RecoEnergy",  fRecoEnergy);
  inTree->SetBranchAddress("TrueX",       fTrueX);
  inTree->SetBranchAddress("TrueY",       fTrueY);
  inTree->SetBranchAddress("TrueZ",       fTrueZ);
  inTree->SetBranchAddress("TrueEndX",    fTrueEndX);
  inTree->SetBranchAddress("TrueEndY",    fTrueEndY);
  inTree->SetBranchAddress("TrueEndZ",    fTrueEndZ);
  inTree->SetBranchAddress("RecoX",       fRecoX);
  inTree->SetBranchAddress("RecoY",       fRecoY);
  inTree->SetBranchAddress("RecoZ",       fRecoZ);
  inTree->SetBranchAddress("RecoEndX",    fRecoEndX);
  inTree->SetBranchAddress("RecoEndY",    fRecoEndY);
  inTree->SetBranchAddress("RecoEndZ",    fRecoEndZ);
  inTree->SetBranchAddress("RecoLength",  fRecoLength);
  inTree->SetBranchAddress("RecoPoints",  fRecoPoints);

  TH1D* hElectronMVASignal = new TH1D("ElectronMVASignal",";Electron MVA value;",100,-1,1);
  TH1D* hElectronMVABackground = new TH1D("ElectronMVABackground",";Electron MVA value;",100,-1,1);
  TH1D* hPhotonMVASignal = new TH1D("PhotonMVASignal",";Photon MVA value;",100,-1,1);
  TH1D* hPhotonMVABackground = new TH1D("PhotonMVABackground",";Photon MVA value;",100,-1,1);

  for (int event = 0; event < inTree->GetEntriesFast(); ++event) {

    if (event % 1000 == 0)
      std::cout << "Processing event " << event << std::endl;

    inTree->GetEntry(event);

    for (int object = 0; object < fNObjects; ++object) {

      if (fShower[object]) {

	if (fTruePDG[object] == 11)
	  hElectronMVASignal->Fill(fElectronMVA[object]);
	else
	  hElectronMVABackground->Fill(fElectronMVA[object]);

	if (fTruePDG[object] == 22)
	  hPhotonMVASignal->Fill(fPhotonMVA[object]);
	else
	  hPhotonMVABackground->Fill(fPhotonMVA[object]);

      }

    }

  }

  TCanvas* canv = new TCanvas("canv","",800,600);
  hElectronMVASignal->Scale(1./hElectronMVASignal->Integral());
  hElectronMVASignal->SetFillStyle(3003);
  hElectronMVASignal->SetFillColor(4);
  hElectronMVASignal->SetLineColor(4);
  hElectronMVABackground->Scale(1./hElectronMVABackground->Integral());
  hElectronMVABackground->SetFillStyle(3003);
  hElectronMVABackground->SetFillColor(2);
  hElectronMVABackground->SetLineColor(2);
  hElectronMVABackground->Draw("hist");
  hElectronMVASignal->Draw("hist sames");
  canv->Update();
  TPaveStats* ps2 = (TPaveStats*)hElectronMVASignal->GetListOfFunctions()->FindObject("stats");
  ps2->SetX1NDC(0.3); ps2->SetX2NDC(0.6);
  ((TPaveStats*)hElectronMVABackground->GetListOfFunctions()->FindObject("stats"))->SetTextColor(2);
  ps2->SetTextColor(4);
  canv->cd();
  TLegend* leg = new TLegend(0.6,0.7,0.85,0.85);
  leg->AddEntry(hElectronMVASignal,"Electrons","f");
  leg->AddEntry(hElectronMVABackground,"Not electrons","f");
  leg->Draw();
  canv->SaveAs("ElectronMVA.eps");
  delete leg;

  canv->Clear();
  hPhotonMVASignal->Scale(1./hPhotonMVASignal->Integral());
  hPhotonMVASignal->SetFillStyle(3003);
  hPhotonMVASignal->SetFillColor(4);
  hPhotonMVASignal->SetLineColor(4);
  hPhotonMVABackground->Scale(1./hPhotonMVABackground->Integral());
  hPhotonMVABackground->SetFillStyle(3003);
  hPhotonMVABackground->SetFillColor(2);
  hPhotonMVABackground->SetLineColor(2);
  hPhotonMVABackground->Draw("hist");
  hPhotonMVASignal->Draw("hist same");
  leg = new TLegend(0.6,0.7,0.9,0.9);
  leg->AddEntry(hPhotonMVASignal,"Photons","lf");
  leg->AddEntry(hPhotonMVABackground,"Not photons","lf");
  leg->Draw();
  canv->SaveAs("PhotonMVA.eps");  
  delete leg;

  return;

}
