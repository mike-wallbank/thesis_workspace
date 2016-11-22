{
  TFile* file = TFile::Open("trackshower.root");
  TTree* tree = (TTree*)file->Get("trackshower/TrackShowerSep");

  tree->Draw("CylinderSpacePoints/AvCylinderSpacePoints>>trackcyl(20,0,1)","(HasShowerTrack&&(Track==1||ShowerTrack==1))*Length","hist");
  tree->Draw("CylinderSpacePoints/AvCylinderSpacePoints>>showercyl(20,0,1)","(HasShowerTrack&&Shower==1&&ShowerTrack==0)*Length","hist");
  showercyl->SetLineColor(2);
  trackcyl->Scale(1/trackcyl->GetEntries());
  showercyl->Scale(1/showercyl->GetEntries());
  trackcyl->Draw("hist");
  showercyl->Draw("hist same");

  tree->Draw("SphereSpacePoints/AvSphereSpacePoints>>showersph(40,0,0.5)","(HasShowerTrack&&Shower==1&&ShowerTrack==0&&SphereSpacePoints!=0&&Length>3)*Length","hist");
  tree->Draw("SphereSpacePoints/AvSphereSpacePoints>>tracksph(40,0,0.5)","(HasShowerTrack&&(Track==1||ShowerTrack==1)&&SphereSpacePoints!=0&&Length>3)*Length","hist");
  showersph->SetLineColor(2);
  showersph->Scale(1/showersph->GetEntries());
  tracksph->Scale(1/tracksph->GetEntries());
  tracksph->Draw("hist");
  showersph->Draw("hist same");

  // tree->Draw("SphereSpacePoints/AvSphereSpacePoints:CylinderSpacePoints/AvCylinderSpacePoints>>trackboth(20,0,1,40,0,5)","(HasShowerTrack&&(Track==1||ShowerTrack==1)&&SphereSpacePoints!=0)*Length","colz");
  // tree->Draw("SphereSpacePoints/AvSphereSpacePoints:CylinderSpacePoints/AvCylinderSpacePoints>>showerboth(20,0,1,40,0,5)","(HasShowerTrack&&Shower==1&&ShowerTrack==0&&SphereSpacePoints!=0)*Length","colz");
  // showerboth->Scale(1./showerboth->GetEntries());
  // trackboth->Scale(1./trackboth->GetEntries());
  // showerboth->Divide(trackboth);
  // showerboth->GetZaxis()->SetRangeUser(0,2);
  // showerboth->Draw("colz");
}
