{
  TString DEF_SIGNAL_INFV = "((NuX>"+DEF_FV_XLOW+") && (NuX<"+DEF_FV_XHIGH+") && (NuY>"+DEF_FV_YLOW+") && (NuY<"+DEF_FV_YHIGH+") && (NuZ>"+DEF_FV_ZLOW+") && (NuZ<"+DEF_FV_ZHIGH+"))";
  TString DEF_SIGNAL = "(NuPdg==14 && BeamPdg==14 && NC==0 && "+DEF_SIGNAL_INFV+")";

  TString DEF_SIGNAL_WEIGHTED = "(("+DEF_WEIGHTING+")*("+DEF_SIGNAL+"))";
}
