{

  TFile *file = TFile::Open("mergingVariables.root");
  file->cd("testshower");

  MatchingVariables->Draw("POCA:Angle>>merge(60,0,1.6,100,0,100)","TrueMerge==1","colz");
  MatchingVariables->Draw("POCA:Angle>>nomerge(60,0,1.6,100,0,100)","TrueMerge==0","colz");

  TH2* newHist = nomerge->Clone();
  newHist->Divide(merge);

  newHist->GetZaxis()->SetRangeUser(0,2);

  newHist->Draw("colz");

}
