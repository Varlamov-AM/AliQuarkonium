void test(){

    TFile* input = new TFile("output.root", "READ");

    TH2D* hist1 = (TH2D*)input->Get("mass_spectrum_epen_cand");
    TH2D* hist2 = (TH2D*)input->Get("mass_spectrum_signal");
    TH2D* hist3 = (TH2D*)input->Get("mass_spectrum_signal_w");
    TH2D* hist4 = (TH2D*)input->Get("mass_spectrum_signal_r");
    TH2D* hist5 = (TH2D*)input->Get("mass_spectrum_signal_rr");
    TH2D* hist6 = (TH2D*)input->Get("mass_spectrum_epen_cand_r");

    TH1D* slice1[10];
    TCanvas* c = new TCanvas("c", "c");
    c->Divide(4, 3);

    TH1D* slice2[10];
    TCanvas* cc = new TCanvas("cc", "cc");
    cc->Divide(4, 3);

    TH1D* slice3[10];
    TCanvas* ccc = new TCanvas("ccc", "ccc");
    ccc->Divide(4, 3);

    TH1D* slice4[10];
    TCanvas* cccc = new TCanvas("cccc", "cccc");
    cccc->Divide(4, 3);

    TH1D* slice5[10];
    TCanvas* ccccc = new TCanvas("ccccc", "ccccc");
    ccccc->Divide(4, 3);

    TH1D* slice6[10];
    TCanvas* cccccc = new TCanvas("cccccc", "cccccc");
    cccccc->Divide(4, 3);


    for (int i = 0; i < 10; ++i){
        slice1[i] = hist1->ProjectionX(Form("slice1_%02d_GeV", i), i + 1, i + 1);
        c->cd(i + 1);
        slice1[i]->Draw();

        slice2[i] = hist2->ProjectionX(Form("slice2_%02d_GeV", i), i + 1, i + 1);
        cc->cd(i + 1);
        slice2[i]->Draw();

        slice3[i] = hist3->ProjectionX(Form("slice3_%02d_GeV", i), i + 1, i + 1);
        ccc->cd(i + 1);
        slice3[i]->Draw();

        slice4[i] = hist4->ProjectionX(Form("slice4_%02d_GeV", i), i + 1, i + 1);
        cccc->cd(i + 1);
        slice4[i]->Draw();

        slice5[i] = hist5->ProjectionX(Form("slice5_%02d_GeV", i), i + 1, i + 1);
        ccccc->cd(i + 1);
        slice5[i]->Draw();

        slice6[i] = hist6->ProjectionX(Form("slice6_%02d_GeV", i), i + 1, i + 1);
        cccccc->cd(i + 1);
        slice6[i]->Draw();

    }

    return;
}
