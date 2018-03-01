void tmvaReader(TString input_files_names, TString weight_file, TString output_name="friend_mva.root"){

  TMVA::Reader *reader = new TMVA::Reader();

  double evtcharge_double;
  float evtcharge;
  float ntrack;
  float maxtrklength;
  float avgtrklength;
  float trkdedx;
  float trkrch;
  float trkrt;
  float trkfr;
  float trkpida;
  float nshower;
  float showerdedx;
  float eshower;
  float frshower;
  float nhitspershw;
  float shwlength;
  float shwmax;
  float fract_5_wires;
  float fract_10_wires;
  float fract_50_wires;
  float fract_100_wires;
  float shwdis;
  float shwdisx;
  float shwdisy;
  float shwdisz;
  float shwcosx;
  float shwcosy;
  float shwcosz;
  float trkcosx;
  float trkcosy;
  float trkcosz;
  float ET;


  double mvaresult;
  int beamPdg;
  int neu;
  bool cc;

  /*
   evtcharge
   ntrack
   maxtrklength
   avgtrklength
   trkdedx
   trkrch
   trkrt
   trkfr
   trkpida
   fract_5_wires
   fract_10_wires
   fract_50_wires
   fract_100_wires
   trkcosx
   trkcosy
   trkcosz
   ET
   */

 /*
   nshower
   showerdedx
   eshower
   frshower
   nhitspershw
   shwlength
   shwmax
   shwdis
   shwdisx
   shwdisy
   shwdisz
   shwcosx
   shwcosy
   shwcosz
   */


  reader->AddVariable("evtcharge",&evtcharge);
  reader->AddVariable("ntrack",&ntrack);
  reader->AddVariable("maxtrklength",&maxtrklength);
  reader->AddVariable("avgtrklength",&avgtrklength);
  reader->AddVariable("trkdedx",&trkdedx);
  reader->AddVariable("trkrch",&trkrch);
  reader->AddVariable("trkrt",&trkrt);
  reader->AddVariable("trkfr",&trkfr);
  reader->AddVariable("trkpida",&trkpida);
  reader->AddVariable("fract_5_wires",&fract_5_wires);
  reader->AddVariable("fract_10_wires",&fract_10_wires);
  reader->AddVariable("fract_50_wires",&fract_50_wires);
  reader->AddVariable("fract_100_wires",&fract_100_wires);
  reader->AddVariable("trkcosx",&trkcosx);
  reader->AddVariable("trkcosy",&trkcosy);
  reader->AddVariable("trkcosz",&trkcosz);
  reader->AddVariable("ET",&ET);


  reader->BookMVA("BDTG",weight_file);


  TChain *chain = new TChain("mvaselect/MVASelection");
  chain->SetBranchAddress("evtcharge",&evtcharge_double);
  chain->SetBranchAddress("ntrack",&ntrack );
  chain->SetBranchAddress("maxtrklength",&maxtrklength );
  chain->SetBranchAddress("avgtrklength",&avgtrklength );
  chain->SetBranchAddress("trkdedx",&trkdedx);
  chain->SetBranchAddress("trkrch",&trkrch );
  chain->SetBranchAddress("trkrt",&trkrt);
  chain->SetBranchAddress("trkfr",&trkfr);
  chain->SetBranchAddress("trkpida",&trkpida);
  chain->SetBranchAddress("fract_5_wires",&fract_5_wires);
  chain->SetBranchAddress("fract_10_wires",&fract_10_wires );
  chain->SetBranchAddress("fract_50_wires",&fract_50_wires );
  chain->SetBranchAddress("fract_100_wires",&fract_100_wires);
  chain->SetBranchAddress("trkcosx",&trkcosx);
  chain->SetBranchAddress("trkcosy",&trkcosy);
  chain->SetBranchAddress("trkcosz",&trkcosz);
  chain->SetBranchAddress("ET",&ET );
  chain->SetBranchAddress("mvaresult",&mvaresult);
  chain->SetBranchAddress("neu",&neu);
  chain->SetBranchAddress("beamPdg",&beamPdg);
  chain->SetBranchAddress("cc",&cc);



  chain->Add(input_files_names);
  UInt_t NEntries = chain->GetEntries();
  std::cout<<"NEntries: "<<NEntries<<std::endl;



  TFile *output_file = new TFile(output_name,"RECREATE");
  TTree *friend_tree = new TTree("mvatree","mva friend tree");
  double val;
  friend_tree->Branch("newmvaresult",&val);

  for (UInt_t entry = 0; entry < NEntries; entry++){
    chain->GetEntry(entry);
    //Convert evtcharge to float //UGH
    evtcharge = (double)(evtcharge_double);

    if (mvaresult < -1.5){
      val = mvaresult;

    }
    else{
      val = reader->EvaluateMVA("BDTG");
    }

    friend_tree->Fill();
  }

  friend_tree->Write();
  output_file->Close();
}
