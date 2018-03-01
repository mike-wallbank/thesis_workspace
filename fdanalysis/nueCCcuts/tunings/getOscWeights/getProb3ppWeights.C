#include <cstdlib>
#include <iostream>
#include "TMath.h"
#include "BargerPropagator.h"

double getProb3ppWeights(){
  return 0;
}
double getProb3ppWeights(double sin2Theta12, double sin2Theta13, double sin2Theta23, double dm2, double DM2, double delta, double energy, int pdgIn, int pdgOut, double baseline=1300, double density=2.6){
  //gSystem->Load("/dune/app/users/dbrailsf/prob3++/Prob3++.20121225/libThreeProb_2.10.a");
  BargerPropagator   * bNu = new BargerPropagator( );

  bool kSquared  = true;   // using sin^2(x) variables?

  int nu_index_in = 0;
  if (std::abs(pdgIn) == 12) nu_index_in = 1;
  else if (std::abs(pdgIn) == 14) nu_index_in = 2;
  else if (std::abs(pdgIn) == 16) nu_index_in = 3;
  int nu_outdex_out = 0;
  if (std::abs(pdgOut) == 12) nu_outdex_out = 1;
  else if (std::abs(pdgOut) == 14) nu_outdex_out = 2;
  else if (std::abs(pdgOut) == 16) nu_outdex_out = 3;


  int nu_type = 1;
  if (pdgIn < 0) nu_type = -1;

  bNu->SetMNS( sin2Theta12,  sin2Theta13, sin2Theta23, dm2, DM2, delta , energy, kSquared, nu_type ); 
  bNu->propagateLinear( nu_type, baseline, density );

  double prob = bNu->GetProb(nu_index_in, nu_outdex_out);
  delete bNu;
  return prob;
}
