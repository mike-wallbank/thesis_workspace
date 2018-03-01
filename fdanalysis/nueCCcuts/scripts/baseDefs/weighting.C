{

  //Oscillation weights
  gROOT->ProcessLine(".L /dune/app/users/dbrailsf/oscillation/nu_mu/cutsel/tunings/getOscWeights/getProb3ppWeights.C+");
  
  double DEF_SIN2THETA12 = 0.308;
  double DEF_SIN2THETA13 = 0.02163;
  double DEF_SIN2THETA23 = 0.440;
  double DEF_DLITTLEM2 = 7.49e-5;
  double DEF_DBIGM2 = 2.526e-3;
  double DEF_DELTA = 0;

  TString DEF_OSCILLATION_WEIGHTING = Form("(getProb3ppWeights(%f,%f,%f,%f,%f,%f,Enu,BeamPdg,NuPdg))",DEF_SIN2THETA12,DEF_SIN2THETA13,DEF_SIN2THETA23,DEF_DLITTLEM2,DEF_DBIGM2,DEF_DELTA);


  TString DEF_POT_WEIGHTING = "(ProjectedPOTWeight)";
  TString DEF_WEIGHTING = "("+DEF_OSCILLATION_WEIGHTING+"*"+DEF_POT_WEIGHTING+")";
  //TString DEF_WEIGHTING = "("+DEF_POT_WEIGHTING+")";

}
