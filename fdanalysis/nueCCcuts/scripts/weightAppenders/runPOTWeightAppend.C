#include <vector>
#include "/dune/app/users/dbrailsf/oscillation/nu_mu/cutsel/scripts/weightAppenders/potWeightAppend.C"

//Hello friend
//This short script interfaces with the POT weight appender so you don't have to! 
//You could also write your own interface
//The POT weight appender takes the following arguments
// 1: A vector of trees that you want to add the POT information to
// 2: The POT tree itself
// 3: a POT to weight up to (you can pick any number you like, I normally got for 1e21)
// I hope that the below code is easy enough to read
// Basically you need to change the file->Get lines to pull out the trees you want to append information to and for the pot tree
//
// Run this script as
// root -l 'runPOTWeightAppend.C("path/to/my/file.root",1e21)'
void runPOTWeightAppend(TString file_name, double projected_pot=1.){

  TFile *file = new TFile(file_name,"UPDATE");
  if (!file){
    std::cout<<"Could not open " << file_name << std::endl;
    return;
  }

  //NTrees and treeNames will need changing
  std::vector<TTree*> trees;
  trees.push_back((TTree*) file->Get("nuecutselection/nuecutsel"));
  //trees.push_back((TTree*) file->Get("nuecutselection/PIDAna"));

  //POT tree name will need changing 
  TTree *pottree = (TTree*) file->Get("nuecutselection/pottree");
  if (!pottree) {
    std::cout<<"Could not find POT tree"<<std::endl;
    return;
  }

  potWeightAppend(trees,pottree,projected_pot);

  file->Write();
  file->Close();

  return;
}
