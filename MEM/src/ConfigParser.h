
#ifndef CONFIGPARSER_H
#define CONFIGPARSER_H

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class ConfigParser
{
  public:
  ConfigParser();
  ~ConfigParser();

  void GetConfigFromFile(string);
  void LoadHypotheses(int*, string**, int**, int**); 
  void LoadIntegrationRange(double*, double*, double*);
  void LoadJetChoice(string*);
  void LoadOptim(int*);
  void LoadOptim(int*,int*,int*,int*);

  ifstream fconf;

  int nHyp;
  string* sHyp;
  int* Hyp;

  int doTTLL, doTTHfl, doTTHsl, doTTW, doTTWJJ, doTTbarfl, doTTbarsl;
  int nPointsHypTTLL, nPointsHypTTHsl, nPointsHypTTHfl, nPointsHypTTW, nPointsHypTTWJJ, nPointsHypTTbarfl, nPointsHypTTbarsl;
  double valJetTFfracmin, valJetTFfracmax, valNeutMaxE;
  string valJetChoice;
  int valOptim, valOptimTopLep, valOptimTopHad, valOptimHiggs, valOptimW;
  string valMadgraphDir, valTFfile;
  int valVerbosity;
  int valTFOption;

  void ReadOptionValue(string*, int*);
  void ReadOptionValue(string*, double*);
  void ReadOptionValue(string*, string*);

  private:
};

ConfigParser::ConfigParser(){
}

void ConfigParser::GetConfigFromFile(string InputFile){

  fconf.open(InputFile.c_str());
  string line;
  string option;

  getline(fconf, line);
  getline(fconf, line);
  getline(fconf, line);
  ReadOptionValue(&option, &valVerbosity);

  getline(fconf, line); 
  getline(fconf, line);
  getline(fconf, line);
  ReadOptionValue(&option, &doTTLL);
  ReadOptionValue(&option, &nPointsHypTTLL);
  ReadOptionValue(&option, &doTTHsl);
  ReadOptionValue(&option, &nPointsHypTTHsl);
  ReadOptionValue(&option, &doTTHfl);
  ReadOptionValue(&option, &nPointsHypTTHfl);
  ReadOptionValue(&option, &doTTW);
  ReadOptionValue(&option, &nPointsHypTTW);
  ReadOptionValue(&option, &doTTWJJ);
  ReadOptionValue(&option, &nPointsHypTTWJJ);
  ReadOptionValue(&option, &doTTbarfl);
  ReadOptionValue(&option, &nPointsHypTTbarfl);
  ReadOptionValue(&option, &doTTbarsl);
  ReadOptionValue(&option, &nPointsHypTTbarsl);
  ReadOptionValue(&option, &valOptim);
  ReadOptionValue(&option, &valOptimTopHad);
  ReadOptionValue(&option, &valOptimTopLep);
  ReadOptionValue(&option, &valOptimHiggs);
  ReadOptionValue(&option, &valOptimW);

  getline(fconf, line);
  getline(fconf, line);
  getline(fconf, line);
  ReadOptionValue(&option, &valJetTFfracmin);
  ReadOptionValue(&option, &valJetTFfracmax);
  ReadOptionValue(&option, &valNeutMaxE);
  ReadOptionValue(&option, &valJetChoice);

  getline(fconf, line);
  getline(fconf, line);
  getline(fconf, line);
  ReadOptionValue(&option, &valMadgraphDir);

  getline(fconf, line);
  getline(fconf, line);
  getline(fconf, line);
  ReadOptionValue(&option, &valTFfile);
  ReadOptionValue(&option, &valTFOption);

  fconf.close();
  return;
}

ConfigParser::~ConfigParser(){
}

void ConfigParser::ReadOptionValue(string* option, int* value){
  string svalue;
  fconf >> *option;
  fconf >> svalue;
  cout << *option << " "<<svalue << endl;
  *value = atoi(svalue.c_str());
  return;
}

void ConfigParser::ReadOptionValue(string* option, double* value){
  string svalue;
  fconf >> *option;
  fconf >> svalue;
  cout << *option << " "<<svalue << endl;
  *value = atof(svalue.c_str());
  return;
}

void ConfigParser::ReadOptionValue(string* option, string* value){
  string svalue;
  fconf >> *option;
  fconf >> svalue;
  cout << *option << " "<<svalue << endl;
  *value = svalue;
  return;
}

void ConfigParser::LoadHypotheses(int* nhyp, string** shyp, int** hyp, int** nPointsHyp){

  (*nhyp) = 0;

  if (doTTLL) (*nhyp)++;
  if (doTTHsl) (*nhyp)++;
  if (doTTHfl) (*nhyp)++;
  if (doTTW) (*nhyp)++;
  if (doTTWJJ) (*nhyp)++;
  if (doTTbarfl) (*nhyp)++;
  if (doTTbarsl) (*nhyp)++;

  (*shyp) = new string[(*nhyp)];
  (*hyp) = new int[(*nhyp)];
  (*nPointsHyp) = new int[(*nhyp)]; 

  int ih=0;
  if (doTTLL){
    (*shyp)[ih] = "TTLL";
    (*hyp)[ih] = kMEM_TTLL_TopAntitopDecay;
    (*nPointsHyp)[ih] = nPointsHypTTLL;
    ih++;
  }
  if (doTTHsl){
    (*shyp)[ih] = "TTHsl";
    (*hyp)[ih] = kMEM_TTH_TopAntitopHiggsSemiLepDecay;
    (*nPointsHyp)[ih] = nPointsHypTTHsl;
    ih++;
  }
  if (doTTHfl){
    (*shyp)[ih] = "TTHfl";
    (*hyp)[ih] = kMEM_TTH_TopAntitopHiggsDecay;
    (*nPointsHyp)[ih] = nPointsHypTTHfl;
    ih++;
  }
  if (doTTW){
    (*shyp)[ih] = "TTW";
    (*hyp)[ih] = kMEM_TTW_TopAntitopDecay;
    (*nPointsHyp)[ih] = nPointsHypTTW;
    ih++;
  }
  if (doTTWJJ){
    (*shyp)[ih] = "TTWJJ";
    (*hyp)[ih] = kMEM_TTWJJ_TopAntitopDecay;
    (*nPointsHyp)[ih] = nPointsHypTTWJJ;
    ih++;
  }
  if (doTTbarfl){
    (*shyp)[ih] = "TTbarfl";
    (*hyp)[ih] = kMEM_TTbar_TopAntitopFullyLepDecay;
    (*nPointsHyp)[ih] = nPointsHypTTbarfl;
    ih++;
  }
  if (doTTbarsl){
    (*shyp)[ih] = "TTbarsl";
    (*hyp)[ih] = kMEM_TTbar_TopAntitopSemiLepDecay;
    (*nPointsHyp)[ih] = nPointsHypTTbarsl;
    ih++;
  }

  for (int ih=0; ih<(*nhyp); ih++) cout << "Will run hyp "<<(*shyp)[ih]<<" code "<<(*hyp)[ih]<<" with "<<(*nPointsHyp)[ih]<<" iterations"<<endl;

  return;
}

void ConfigParser::LoadIntegrationRange(double* jetTFfracmin, double* jetTFfracmax, double* neutMaxE){

  *jetTFfracmin = valJetTFfracmin;
  *jetTFfracmax = valJetTFfracmax;
  *neutMaxE = valNeutMaxE;

  cout << "Integration will use JetTFfracmin="<< (*jetTFfracmin)<<" JetTFfracmax="<< (*jetTFfracmax) <<" NeutMaxE="<< (*neutMaxE) <<endl;

  return;
}

void ConfigParser::LoadJetChoice(string* jetChoice){

  *jetChoice = valJetChoice;
  cout << "In 2j categories, choose 2 jets with option "<< (*jetChoice) << endl;

  return;
}

void ConfigParser::LoadOptim(int* doOptim){

  *doOptim = valOptim;
  cout << "Optimizing phase space with option: "<< (*doOptim) <<endl;
}

void ConfigParser::LoadOptim(int* doOptimTopHad, int* doOptimTopLep, int* doOptimHiggs, int* doOptimW){

  *doOptimTopHad = valOptimTopHad;
  *doOptimTopLep = valOptimTopLep;
  *doOptimHiggs = valOptimHiggs;
  *doOptimW = valOptimW;

  cout << "Optimizing phase space with option: TopHad "<< (*doOptimTopHad)<<", TopLep "<< (*doOptimTopLep)<< ", Higgs "<< (*doOptimHiggs)<< ", Woffshell "<< (*doOptimW)<<endl;
}



#endif
