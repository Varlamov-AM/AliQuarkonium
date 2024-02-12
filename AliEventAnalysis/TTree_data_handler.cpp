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
    double chic_mass = 0;
    double chic_pt = 0;

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

    //for (int i = 0; i <= 38; ++i){
    //    FILE* fp = fopen(Form("%sAliEvent_class_data_%d.root", source_data_path.Data(), i), "rb");
    //    if (fp != NULL){
    //        chain->Add(Form("%sAliEvent_class_data_%d.root", source_data_path.Data(), i));
    //    }
    //}

    FILE* fp = fopen(Form("%sAliEvent_class_data.root", source_data_path.Data()), "rb");
    if (fp != NULL){
        chain->Add(Form("%sAliEvent_class_data.root", source_data_path.Data()));
    }

    int n = chain->GetEntries();
    printf("Number of entries: %10d\n", n);

    AliEvent *General_event = 0;
    chain->SetBranchAddress("AliEvent", &General_event);
    double branchings[3] = {5.971e-2 * 1.4e-2, 5.971e-2 * 34.3e-2, 5.971e-2 * 19.0e-2};


    for (int i = 0; i < n; ++i){
        chain->GetEntry(i);

		bool signal_event_in_data                 = General_event->signal_event_in_data;
		std::vector<AliParticle> chic             = General_event->chic;
		std::vector<AliParticle> Jpsi             = General_event->Jpsi;
		std::vector<AliParticle> signal_electrons = General_event->signal_electrons;
		std::vector<AliParticle> signal_positrons = General_event->signal_positrons;
		std::vector<AliParticle> signal_photons   = General_event->signal_photons;

        if (i % 10000 == 0){
            printf("Handled events:%10d\n", i);
        }
        if (signal_event_in_data){
            if (chic.size() == 1){

                electron_p0 = signal_electrons[0].p0;
                electron_px = signal_electrons[0].px;
                electron_py = signal_electrons[0].py;
                electron_pz = signal_electrons[0].pz;

                positron_p0 = signal_positrons[0].p0;
                positron_px = signal_positrons[0].px;
                positron_py = signal_positrons[0].py;
                positron_pz = signal_positrons[0].pz;

                gamma_p0 = signal_photons[0].p0;
                gamma_px = signal_photons[0].px;
                gamma_py = signal_photons[0].py;
                gamma_pz = signal_photons[0].pz;

                if (chic[0].id == 10441){
                    branching = branchings[0];
                } else if (chic[0].id == 20443){
                    branching = branchings[1];
                } else if (chic[0].id == 445){
                    branching = branchings[2];
                }
                true_chic_daughters_for_GEANT4->Fill();
            }
        }
    }

    true_chic_daughters_for_GEANT4->Write();
    output->Close();
    
}
