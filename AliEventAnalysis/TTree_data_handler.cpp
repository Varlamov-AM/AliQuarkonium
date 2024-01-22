#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <TFile.h>
#include <TCanvas.h>
#include <TTree.h>
#include <TChain.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TF1.h>
#include <TString.h>
#include <TLorentzVector.h>
#include "AliParticle.h"
#include "AliEvent.h"
#include <vector>

class AliEvent;
class AliParticle;

TLorentzVector resolutionElectron(TLorentzVector);
TLorentzVector resolutionPhoton(TLorentzVector);
bool IsElectronDetectedInALICE3(TLorentzVector, int);

Double_t CB(Double_t*, Double_t*);
Double_t Sigmoid(Double_t);

int main(int argc, char* argv[]){

    TString source_data_path;

    if (argc != 2){
        return 0;
    } else if (argc == 2) {
        source_data_path = TString(argv[1]);
    }
    
    TFile* output = new TFile(Form("%selectron_positron_gamma_4momentum.root", source_data_path.Data()), "RECREATE");
    TTree* true_chic_daughters_for_GEANT4 = new TTree("signal_event_electron_positron_gamma_from_chic_with_branchings", "signal_event_electron_positron_gamma_from_chic_with_branchings");

    double branching = 0;
    double gamma_px = 0;
    double gamma_py = 0;
    double gamma_pz = 0;
    double gamma_p0 = 0;
    double electron_px = 0;
    double electron_py = 0;
    double electron_pz = 0;
    double electron_p0 = 0;
    double positron_px = 0;
    double positron_py = 0;
    double positron_pz = 0;
    double positron_p0 = 0;

    true_chic_daughters_for_GEANT4->Branch("event_branching", &branching);

    true_chic_daughters_for_GEANT4->Branch("gamma_px", &gamma_px);
    true_chic_daughters_for_GEANT4->Branch("gamma_py", &gamma_py);
    true_chic_daughters_for_GEANT4->Branch("gamma_pz", &gamma_pz);
    true_chic_daughters_for_GEANT4->Branch("gamma_p0", &gamma_p0);

    true_chic_daughters_for_GEANT4->Branch("electron_px", &electron_px);
    true_chic_daughters_for_GEANT4->Branch("electron_py", &electron_py);
    true_chic_daughters_for_GEANT4->Branch("electron_pz", &electron_pz);
    true_chic_daughters_for_GEANT4->Branch("electron_p0", &electron_p0);

    true_chic_daughters_for_GEANT4->Branch("positron_px", &positron_px);
    true_chic_daughters_for_GEANT4->Branch("positron_py", &positron_py);
    true_chic_daughters_for_GEANT4->Branch("positron_pz", &positron_pz);
    true_chic_daughters_for_GEANT4->Branch("positron_p0", &positron_p0);

  	true_chic_daughters_for_GEANT4->SetAutoSave(0);

    TChain* chain = new TChain("AliEvent_data");

    for (int i = 0; i <= 38; ++i){
        FILE* fp = fopen(Form("%sAliEvent_class_data_%d.root", source_data_path.Data(), i), "rb");
        if (fp != NULL){
            chain->Add(Form("%sAliEvent_class_data_%d.root", source_data_path.Data(), i));
        }
    }

    int n = chain->GetEntries();
    printf("Number of entries: %10d\n", n);

    AliEvent *General_event = 0;
    chain->SetBranchAddress("AliEvent", &General_event);
    double branchings[3] = {5.971e-2 * 1.4e-2, 5.971e-2 * 34.3e-2, 5.971e-2 * 19.0e-2};


    for (int i = 0; i < n; ++i){
        chain->GetEntry(i);
        std::vector<AliParticle> chi_cJ   = General_event->chic;
        std::vector<AliParticle> electron = General_event->electrons;
        std::vector<AliParticle> positron = General_event->positrons;
        std::vector<AliParticle> photon   = General_event->photons;

        if (i % 10000 == 0){
            printf("Handled events:%10d\n", i);
        }

        if (!chi_cJ.empty()){
            for (auto el : electron){
                if (el.mother_id == 443)
                electron_p0 = el.p0;
                electron_px = el.px;
                electron_py = el.py;
                electron_pz = el.pz;
            }
            for (auto po : positron){
                if (po.mother_id == 443)
                positron_p0 = po.p0;
                positron_px = po.px;
                positron_py = po.py;
                positron_pz = po.pz;
            }
            for (auto gam : photon){
                if (gam.mother_id == 445 or 
                    gam.mother_id == 10441 or
                    gam.mother_id == 20443){

                    int event_type = -1;

                    if (fabs(gam.FMomentum().Eta()) > 0.5){
                        continue;
                    }

                    if (gam.mother_id == 10441){ event_type = 0;}
                    if (gam.mother_id == 20443){ event_type = 1;}
                    if (gam.mother_id == 445)  { event_type = 2;}

                    gamma_p0 = gam.p0;
                    gamma_px = gam.px;
                    gamma_py = gam.py;
                    gamma_pz = gam.pz;
                    branching = branchings[event_type];
                }
            }
        } else {continue;}

        true_chic_daughters_for_GEANT4->Fill();

    }

    true_chic_daughters_for_GEANT4->Write();
    output->Close();
    
}
