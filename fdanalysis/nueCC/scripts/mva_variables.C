{

  TFile* inFile = new TFile("/pnfs/dune/persistent/users/wallbank/v06_26_00/mva_nue_dune10kt_1x2x6_old/mva_nue_train.root","r");
  TTree* inTree = (TTree*)inFile->Get("mvaselect/MVASelection");

  double fEvtCharge;
  double fNuEnergy, fQ2, fLepNuAngle, fLepMomX, fLepMomY, fLepMomZ;
  float fNTrack, fMaxTrackLength, fAvTrackLength, fTrackdEdx, fTrackRCH, fTrackRT, fTrackFR, fTrackPIDA, fFract5Wires, fFract10Wires, fFract50Wires, fFract100Wires;
  float fTrackCosX, fTrackCosY, fTrackCosZ, fTransEnergy;
  float fNShower, fShowerdEdx, fShowerEnergy, fShowerFrac, fShowerNHitsWire, fShowerLength, fShowerMax;
  float fShowerDisX, fShowerDisY, fShowerDisZ, fShowerCosX, fShowerCosY, fShowerCosZ;

  inTree->SetBranchAddress("evtcharge", &fEvtCharge);

  inTree->SetBranchAddress("Ev",         &fNuEnergy);
  inTree->SetBranchAddress("Q2",         &fQ2);
  inTree->SetBranchAddress("LepNuAngle", &fLepNuAngle);
  inTree->SetBranchAddress("LepMomX",    &fLepMomX);
  inTree->SetBranchAddress("LepMomY",    &fLepMomY);
  inTree->SetBranchAddress("LepMomZ",    &fLepMomZ);

  inTree->SetBranchAddress("ntrack",          &fNTrack);
  inTree->SetBranchAddress("maxtrklength",    &fMaxTrackLength);
  inTree->SetBranchAddress("avgtrklength",    &fAvTrackLength);
  inTree->SetBranchAddress("trkdedx",         &fTrackdEdx);
  inTree->SetBranchAddress("trkrch",          &fTrackRCH);
  inTree->SetBranchAddress("trkrt",           &fTrackRT);
  inTree->SetBranchAddress("trkfr",           &fTrackFR);
  inTree->SetBranchAddress("trkpida",         &fTrackPIDA);
  inTree->SetBranchAddress("fract_5_wires",   &fFract5Wires);
  inTree->SetBranchAddress("fract_10_wires",  &fFract10Wires);
  inTree->SetBranchAddress("fract_50_wires",  &fFract50Wires);
  inTree->SetBranchAddress("fract_100_wires", &fFract100Wires);
  inTree->SetBranchAddress("trkcosx",         &fTrackCosX);
  inTree->SetBranchAddress("trkcosy",         &fTrackCosY);
  inTree->SetBranchAddress("trkcosz",         &fTrackCosZ);
  inTree->SetBranchAddress("ET",              &fTransEnergy);

  inTree->SetBranchAddress("nshower",     &fNShower);
  inTree->SetBranchAddress("showerdedx",  &fShowerdEdx);
  inTree->SetBranchAddress("eshower",     &fShowerEnergy);
  inTree->SetBranchAddress("frshower",    &fShowerFrac);
  inTree->SetBranchAddress("nhitspershw", &fShowerNHitsWire);
  inTree->SetBranchAddress("shwlength",   &fShowerLength);
  inTree->SetBranchAddress("shwmax",      &fShowerMax);
  inTree->SetBranchAddress("shwdisx",     &fShowerDisX);
  inTree->SetBranchAddress("shwdisy",     &fShowerDisY);
  inTree->SetBranchAddress("shwdisz",     &fShowerDisZ);
  inTree->SetBranchAddress("shwcosx",     &fShowerCosX);
  inTree->SetBranchAddress("shwcosy",     &fShowerCosY);
  inTree->SetBranchAddress("shwcosz",     &fShowerCosZ);

  TH2F* hNTrackNuEnergy = new TH2F("NTrackNuEnergy",";Nu Energy (GeV);Num tracks;",

}

