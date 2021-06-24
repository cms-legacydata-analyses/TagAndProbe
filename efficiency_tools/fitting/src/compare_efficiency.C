/*
!--------------------------------
!Purpose: Compare efficiency of files
!--------------------------------
!author: Allan Jales
!--------------------------------
*/

//This code has been adjusted for this tutorial

void compare_plot(TFile *file0, TFile *file1, const char* path, string quantity)
{
    TEfficiency* pEff0 = (TEfficiency*)file0->Get(path);
    TEfficiency* pEff1 = (TEfficiency*)file1->Get(path);

    int colorScheme[][2] = {
        {kGreen - 2, kBlue},
        {kBlue,      kRed},
        {kGreen - 2, kRed}
    };

    const char* nameScheme[][2] = {
        {"#Upsilon data", "J/#psi data"},
        {"Real data",     "Simulated data"},
        {"Real data",     "Simulated data"}
    };

    int useScheme = 1;
    //Upsilon vs Jpsi
    //Jpsi    Run vs MC
    //Upsilon Run vs MC

    if (pEff0 == NULL)
    {
        cerr << "Could not read the path in file0\n";
        abort();
    }

    if (pEff1 == NULL)
    {
        cerr << "Could not read the path in file1\n";
        abort();
    }

    //Create canvas
    TCanvas* c1 = new TCanvas();
    //gStyle->SetOptTitle(0);
    c1->SetMargin(0.10, 0.03, 0.11, 0.07);

    //Plot
    pEff0->SetMarkerColor(colorScheme[useScheme][0]);
    pEff0->SetLineColor(colorScheme[useScheme][0]);
    pEff0->Draw();
    gPad->Update();
    
    if (quantity == "Pt")
    {
        pEff0->SetTitle("Efficiency of Tracker Probe Muon;_{p}T (GeV/c);Efficiency");
    }
    if (quantity == "Eta")
    {
        pEff0->SetTitle("Efficiency of Tracker Probe Muon;#eta;Efficiency");
    }
    if (quantity == "Phi")
    {
        pEff0->SetTitle("Efficiency of Tracker Probe Muon;#phi;Efficiency");
    }

    pEff1->SetMarkerColor(colorScheme[useScheme][1]);
    pEff1->SetLineColor(colorScheme[useScheme][1]);
    pEff1->Draw("same");

    //Set range in y axis
    gPad->Update();
    auto graph = pEff0->GetPaintedGraph();
    graph->SetMinimum(0.0);
    graph->SetMaximum(1.2);
    gPad->Update();

     if (quantity == "Pt")
     {
        pEff0->GetPaintedGraph()->GetHistogram()->GetXaxis()->SetRangeUser(0.,80.);
        graph->SetMinimum(0.5);
        graph->SetMaximum(1.2);
     }
    
    if (quantity == "Eta")
    {
        pEff0->GetPaintedGraph()->GetHistogram()->GetXaxis()->SetRangeUser(-3.,3.);
        graph->SetMinimum(0.8);
        graph->SetMaximum(1.08);
    }
    
    if (quantity == "Phi")
    {
        pEff0->GetPaintedGraph()->GetHistogram()->GetXaxis()->SetRangeUser(-3.,3.);
        graph->SetMinimum(0.8);
        graph->SetMaximum(1.08);
    }

    //Legenda
    TLegend* tl = new TLegend(0.68,0.78,0.94,0.88);
    tl->SetTextSize(0.04);
    tl->AddEntry(pEff0, nameScheme[useScheme][0], "lp");
    tl->AddEntry(pEff1, nameScheme[useScheme][1],   "lp");
    tl->Draw();

    //CMS Open Data
    TLatex* txCOD = new TLatex();
    txCOD->SetTextSize(0.04);
    txCOD->SetTextAlign(12);
    txCOD->SetTextFont(42);
    txCOD->SetNDC(kTRUE);
    txCOD->DrawLatex(0.14,0.85,Form("#bf{CMS Open Data}"));

    //Results stored in...
    const char* directoryToSave = "Comparison Run2011 vs MC/";

    //Check if dir exists
    if (gSystem->AccessPathName(directoryToSave))
    {
        if (gSystem->mkdir(directoryToSave))
        {
            cerr << "\"" << directoryToSave << "\" directory not found and could not be created ERROR" << endl;
            abort();
        }
        else
        {
            cout << "\"" << directoryToSave << "\" directory created OK" << endl;
        }
    }
    else
    {
        cout << "\"" << directoryToSave << "\" directory OK" << endl;
    }

    //stores file as .png
    string saveAs = string(directoryToSave) + string(pEff0->GetName()) + ".png";

    c1->SaveAs(saveAs.data());
}

//Compare efficiency
void compare_efficiency(string quantity, string run2011, string MC)
{
    TFile *file0 = TFile::Open(run2011.c_str());
    TFile *file1 = TFile::Open(MC.c_str());

    if (file0 == NULL || file1 == NULL)
    {
        std::cerr << "ABORTING...\n";
        abort();
    }

    compare_plot(file0, file1, "Efficiency", quantity);
}
