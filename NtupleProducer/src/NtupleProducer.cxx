#include "../include/NtupleProducer.h"

#include "Riostream.h"
#include "TSystem.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <algorithm>
#include <assert.h>

Tree                 *ntP;
TChain                *ch;
Ntuple                *nt;
std::vector<int> *evdebug;

unsigned int          idx;

int main(int argc, char *argv[])
{
    if( argc < 5 )
    {
        std::cout << "NtupleProducer usage:"        << std::endl;
        std::cout << "--file: input filename"       << std::endl;
        std::cout << "--outfile: output filename"   << std::endl;
        std::cout << "--tree: TTree name"           << std::endl;
        std::cout << "--nmax: max number of events" << std::endl;
        std::cout << "--isdata: data or MC ?"       << std::endl;
        exit(1);
    }

    const char *fname_str     = "input.txt";
    const char *fname_out_str = "output.root";
    const char *stream_str    = "FlatTree/tree";
    int        nmax           = -1;
    bool       isdata         = 0;

    for(int i=0;i<argc;i++)
    {
        if( ! strcmp(argv[i],"--file") )    fname_str      = argv[i+1];
        if( ! strcmp(argv[i],"--outfile") ) fname_out_str  = argv[i+1];	
        if( ! strcmp(argv[i],"--tree") )    stream_str     = argv[i+1];
        if( ! strcmp(argv[i],"--nmax") )    nmax           = atoi(argv[i+1]);
        if( ! strcmp(argv[i],"--isdata") )  isdata         = (bool) atoi(argv[i+1]);

    }   

    const char *fname = fname_str;
    const char *stream = stream_str;
    const char *fname_out = fname_out_str;

    std::cout << "--file="   << fname      << std::endl;
    std::cout << "--outfile="<< fname_out  << std::endl;
    std::cout << "--tree="   << stream     << std::endl;
    std::cout << "--nmax="   << nmax       << std::endl;
    std::cout << "--isdata=" << isdata     << std::endl;

    Tree tree(0,const_cast<char*>(fname),stream);
    ntP = &tree;

    ch = tree.fChain;
    Long64_t nentries = ch->GetEntries();
    ntP->registerInputBranches(ch);


    TString fname_out_root = fname_out;
    fname_out_root += ".root";
    nt = new Ntuple(fname_out_root.Data());

    nt->Init();
    std::cout << "Initialization DONE" << std::endl;
    nt->createVar();
    std::cout << "Creation DONE" << std::endl;
    nt->setBranchAddress();
    std::cout << "SetBranchAddress DONE ***" << std::endl;

    Event     ev;
    Electron  el;
    Muon      mu;
    Tau      tau; 
    Jet      jet; 
  
    Truth  truth;
    GenJet genjet;
    TriggerObj trigObj;
    
   
    evdebug = new std::vector<int>();
    //   evdebug->push_back(120);

    int nlep = 0;
    int njet = 0;

    int n_mu  = 0;
    int n_el  = 0;
    int n_tau = 0;
    int n_jet = 0;
   
  
    JetCorrectionUncertainty *jesTotal;
  
   
    if (isdata == false) jesTotal = new JetCorrectionUncertainty(*(new JetCorrectorParameters("/home-pbs/lebihan/JESJEC/Fall15_25nsV2_MC/Fall15_25nsV2_MC_UncertaintySources_AK4PFchs.txt", "Total")));
    else		 jesTotal = new JetCorrectionUncertainty(*(new JetCorrectorParameters("/home-pbs/lebihan/JESJEC/Fall15_25nsV2_DATA/Fall15_25nsV2_DATA_UncertaintySources_AK4PFchs.txt", "Total")));
    
    for(Long64_t i=0;i<nentries;i++)
    {
        if( i > nmax && nmax >= 0 ) break; 

        //std::cout << "i:" << i << std::endl;
        ch->GetEntry(i);


        nt->clearVar();	


        //	if( !(isHtoWW || isHtoZZ || isHtoTT) ) continue;

        // event
        ev.init();


        ev.read(isdata); 
	

        //	if( isHtoWW ) ev._tth_channel = 0;
        //	else if( isHtoZZ ) ev._tth_channel = 1;
        //	else if( isHtoTT ) ev._tth_channel = 2;

        nt->NtEvent->push_back(ev);


        bool mu_presel  = false,
             el_presel  = false,
             tau_presel = false,
             jet_presel = false;

        int n_mu_evt = 0;

        // muons
        for(int j=0;j<ntP->mu_n;j++)
        {
            idx = j;

            mu.init();
            mu.read();

            if( mu.sel())
            {
                nt->NtMuon->push_back(mu);
                mu_presel = true;
                n_mu_evt ++;
            }
        }
        if(mu_presel) n_mu++;
        
        int n_el_evt = 0;

        // electrons
        for(int j=0;j<ntP->el_n;j++)
        {
            idx = j;

            el.init();
            el.read();
            if( el.sel() ) nlep++;

            if( el.sel()) 
            {    
                nt->NtElectron->push_back(el);
                el_presel = true;
                n_el_evt++;
            }
        }
        if(el_presel) n_el++;

        // preselection
        // if ( (n_mu_evt + n_el_evt) < 2 ) continue; 

        // taus 
        for(int j=0;j<ntP->tau_n;j++)
        {
            idx = j;

            tau.init();
	    
            tau.read();
            tau.init();
   
            if (tau.sel()) 
            {    
                nt->NtTau->push_back(tau);
                tau_presel = true;
            }
        }	
        if(tau_presel) n_tau++;


        // jets
        for(int j=0;j<ntP->jet_n;j++)
        {
            idx = j;

            jet.init();
            jet.read(isdata);
	    
	    jesTotal->setJetPt(ntP->jet_pt->at(idx));
            jesTotal->setJetEta(ntP->jet_eta->at(idx));
            
	    jet.setJESUncertainty(jesTotal->getUncertainty(true));
            //jet.setJESUncertainty(0.);
  
            if (jet.sel()) 
            {    
                nt->NtJet->push_back(jet);
                jet_presel = true;
            }    
        }
        if(jet_presel) n_jet++;

        //trigger objects
        /*for(int j=0;j<ntP->triggerobject_n;j++)
          {
          idx = j;

          trigObj.init();
          trigObj.read();

          if (trigObj.sel()) nt->NtTriggerObj->push_back(trigObj);
          }*/

        if (!isdata)
        {
            // genjets
            for(int j=0;j<ntP->genJet_n;j++)
            {
                idx = j;

                genjet.init();
                genjet.read();

                if (genjet.sel()) nt->NtGenJet->push_back(genjet);
            }

            // truth
            truth.init();
            truth.read();
            truth.readMultiLepton();

            nt->NtTruth->push_back(truth);
        }
/*
        std::cout << " n_mu :  " << n_mu  << std::endl
          << " n_el :  " << n_el  << std::endl
          << " n_tau:  " << n_tau << std::endl
          << " n_jet:  " << n_jet << std::endl;
*/
        nt->fill();
	
    }  

    delete evdebug;
    delete nt;
}
