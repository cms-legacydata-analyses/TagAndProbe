

TEfficiency* get_efficiency(TH1F* ALL, TH1F* PASS, string quantity, bool DataIsMc)
{
    gSystem->cd("Efficiency Result");
    gSystem->cd(quantity.c_str());
    
    string* file_name = new string[2];
    file_name[0] = "Efficiency_Run2011.root";
    file_name[1] = "Efficiency_MC.root";
    
    TFile* pFile = new TFile(file_name[DataIsMc].c_str(),"recreate");
    TEfficiency* pEff = new TEfficiency();
    pEff->SetName("Efficiency");
    pEff->SetPassedHistogram(*PASS, "f");
    pEff->SetTotalHistogram (*ALL,"f");
    
    pEff->SetDirectory(gDirectory);
    pFile->Write();
    
    TCanvas* oi = new TCanvas();
    oi->cd();
    pEff->Draw();
    
    gPad->Update();

    auto graph = pEff->GetPaintedGraph();
    graph->SetMinimum(0.8);
    graph->SetMaximum(1.2);
    gPad->Update();
    
    gSystem->cd("../..");
    delete[] file_name;
    
    return pEff;
}
