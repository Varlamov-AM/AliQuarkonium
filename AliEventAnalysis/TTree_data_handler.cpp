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
    output->cd();
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

    for (int i = 0; i < 50; ++i){
        for (int j = 0; j < 10000; ++j){
            if (j % 1000 == 0){
                printf("Handled events:%10d\n", j);
            }
            electron_p0 = 0;
            electron_px = 0;
            electron_py = 0;
            electron_pz = 0;

            positron_p0 = 0;
            positron_px = 0;
            positron_py = 0;
            positron_pz = 0;

            gamma_p0 = i * 0.1;
            gamma_px = 0;
            gamma_py = 0;
            gamma_pz = i * 0.1;
        }
    }
    true_chic_daughters_for_GEANT4->Write();
    output->Close();
    
}
