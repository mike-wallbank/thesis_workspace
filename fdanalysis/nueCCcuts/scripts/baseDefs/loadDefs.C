{
  TString DEF_LOAD_PATH = "/dune/app/users/dbrailsf/oscillation/nu_mu/cutsel/scripts/baseDefs"; 

  //Load paths 1 at a time
  gROOT->ProcessLine(".x "+DEF_LOAD_PATH+"/"+"FV.C");
  gROOT->ProcessLine(".x "+DEF_LOAD_PATH+"/"+"weighting.C");
  gROOT->ProcessLine(".x "+DEF_LOAD_PATH+"/"+"signal.C");
  gROOT->ProcessLine(".x "+DEF_LOAD_PATH+"/"+"background.C");
  gROOT->ProcessLine(".x "+DEF_LOAD_PATH+"/"+"selection.C");
}
