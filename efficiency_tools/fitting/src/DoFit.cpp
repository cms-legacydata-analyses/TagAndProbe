using namespace RooFit;

double* doFit(string condition, string MuonID_str, string quant, double* init_conditions, bool save = true) // RETURNS ARRAY WITH [yield_all, yield_pass, err_all, err_pass]    ->   OUTPUT ARRAY
{
    string MuonID_file = "";
    if (MuonID_str == "PassingProbeTrackingMuon")
        MuonID_file = "trackerMuon";
    if (MuonID_str == "PassingProbeStandAloneMuon")
        MuonID_file = "standaloneMuon";
    if (MuonID_str == "PassingProbeGlobalMuon")
        MuonID_file = "globalMuon";
        
    TFile *file0       = TFile::Open(("DATA/Upsilon/" + MuonID_file + "/T&P_UPSILON_DATA.root").c_str());
    TTree *DataTree    = (TTree*)file0->Get(("UPSILON_DATA"));
    
    double _mmin = 9;  double _mmax = 10.8;
    
    RooRealVar MuonID(MuonID_str.c_str(), MuonID_str.c_str(), 0, 1); //Muon_Id
    
    RooRealVar InvariantMass("InvariantMass", "InvariantMass", _mmin, _mmax);
    
    double* limits = new double[2];
    if (quant == "Pt") {
        limits[0] = 0;
        limits[1] = 40;
    }
    if (quant == "Eta") {
        limits[0] = -3;
        limits[1] = 3;
    }
    if (quant == "Phi") {
        limits[0] = -2;
        limits[1] = 2;
    }
    RooRealVar quantity(("ProbeMuon_" + quant).c_str(), ("ProbeMuon_" + quant).c_str(), limits[0], limits[1]);
    
    RooFormulaVar* redeuce = new RooFormulaVar("PPTM", condition.c_str(), RooArgList(quantity));
    RooDataSet *Data_ALL    = new RooDataSet("DATA", "DATA", DataTree, RooArgSet(InvariantMass, MuonID, quantity),*redeuce);
    RooFormulaVar* cutvar = new RooFormulaVar("PPTM", (condition + " && " + MuonID_str + " == 1").c_str() , RooArgList(MuonID, quantity));

    RooDataSet *Data_PASSING = new RooDataSet("DATA_PASS", "DATA_PASS", DataTree, RooArgSet(InvariantMass, MuonID, quantity), *cutvar);//
    
    RooDataHist* dh_ALL     = Data_ALL->binnedClone();
    RooDataHist* dh_PASSING = Data_PASSING->binnedClone();
    
    TCanvas* c_all  = new TCanvas;
    TCanvas* c_pass = new TCanvas;
    
    RooPlot *frame = InvariantMass.frame(RooFit::Title("Invariant Mass"));
    // BACKGROUND VARIABLES
    RooRealVar a0("a0", "a0", 0, -10, 10);
    RooRealVar a1("a1", "a1", 0, -10, 10);

    // BACKGROUND FUNCTION
    RooChebychev background("background","background", InvariantMass, RooArgList(a0,a1));
    
    // GAUSSIAN VARIABLES
    RooRealVar sigma("sigma","sigma",init_conditions[3]);
    RooRealVar mean1("mean1","mean1",init_conditions[0]);
    RooRealVar mean2("mean2","mean2",init_conditions[1]);
    RooRealVar mean3("mean3","mean3",init_conditions[2]);
    // CRYSTAL BALL VARIABLES
    RooRealVar alpha("alpha","alpha", 1.4384e+00);
    RooRealVar n("n", "n", 1.6474e+01);
    // FIT FUNCTIONS
    RooCBShape  gaussian1("signal1","signal1",InvariantMass,mean1,sigma, alpha, n);
    RooGaussian gaussian2("signal2","signal2",InvariantMass,mean2,sigma);
    RooGaussian gaussian3("signal3","signal3",InvariantMass,mean3,sigma);
    
    double n_signal_initial1 =(Data_ALL->sumEntries(TString::Format("abs(InvariantMass-%g)<0.015",init_conditions[1]))-Data_ALL->sumEntries(TString::Format("abs(InvariantMass-%g)<0.030&&abs(InvariantMass-%g)>.015",init_conditions[1],init_conditions[1]))) / Data_ALL->sumEntries();
    double n_signal_initial2 =(Data_ALL->sumEntries(TString::Format("abs(InvariantMass-%g)<0.015",init_conditions[2]))-Data_ALL->sumEntries(TString::Format("abs(InvariantMass-%g)<0.030&&abs(InvariantMass-%g)>.015",init_conditions[2],init_conditions[2]))) / Data_ALL->sumEntries();
    double n_signal_initial3 =(Data_ALL->sumEntries(TString::Format("abs(InvariantMass-%g)<0.015",init_conditions[3]))-Data_ALL->sumEntries(TString::Format("abs(InvariantMass-%g)<0.030&&abs(InvariantMass-%g)>.015",init_conditions[3],init_conditions[3]))) / Data_ALL->sumEntries();
    
    double n_signal_initial_total = n_signal_initial1 + n_signal_initial2 + n_signal_initial3;
    
    RooRealVar frac1("frac1","frac1",7.1345e-01);
    RooRealVar frac2("frac2","frac2",1.9309e-01);

    RooAddPdf* signal;
    
    signal      = new RooAddPdf("signal", "signal", RooArgList(gaussian1, gaussian2,gaussian3), RooArgList(frac1, frac2));
    double n_back_initial = 1. - n_signal_initial1 - n_signal_initial2 -n_signal_initial3;
    
    RooRealVar n_signal_total("n_signal_total","n_signal_total",n_signal_initial_total,0.,Data_ALL->sumEntries());
    RooRealVar n_signal_total_pass("n_signal_total_pass","n_signal_total_pass",n_signal_initial_total,0.,Data_PASSING->sumEntries());
    
    RooRealVar n_back("n_back","n_back",n_back_initial,0.,Data_ALL->sumEntries());
    RooRealVar n_back_pass("n_back_pass","n_back_pass",n_back_initial,0.,Data_PASSING->sumEntries());
    RooAddPdf* model;
    RooAddPdf* model_pass;
    
    model      = new RooAddPdf("model","model", RooArgList(*signal, background),RooArgList(n_signal_total, n_back));
    model_pass = new RooAddPdf("model_pass", "model_pass", RooArgList(*signal, background),RooArgList(n_signal_total_pass, n_back_pass));
    
    // SIMULTANEOUS FIT
    RooCategory sample("sample","sample") ;
    sample.defineType("All") ;
    sample.defineType("PASSING") ;
    
    RooDataHist combData("combData","combined data",InvariantMass,Index(sample),Import("ALL",*dh_ALL),Import("PASSING",*dh_PASSING));
    
    RooSimultaneous simPdf("simPdf","simultaneous pdf",sample) ;
    
    simPdf.addPdf(*model,"ALL");
    simPdf.addPdf(*model_pass,"PASSING");
    
    RooFitResult* fitres = new RooFitResult;
    fitres = simPdf.fitTo(combData, RooFit::Save());
    
    // OUTPUT ARRAY
    double* output = new double[4];
    
    RooRealVar* yield_ALL = (RooRealVar*) fitres->floatParsFinal().find("n_signal_total");
    RooRealVar* yield_PASS = (RooRealVar*) fitres->floatParsFinal().find("n_signal_total_pass");
    
    output[0] = yield_ALL->getVal();
    output[1] = yield_PASS->getVal();
    
    output[2] = yield_ALL->getError();
    output[3] = yield_PASS->getError();
    
    frame->SetTitle("ALL");
    frame->SetXTitle("#mu^{+}#mu^{-} invariant mass [GeV/c^{2}]");
    Data_ALL->plotOn(frame);
    
    model->plotOn(frame);
    model->plotOn(frame,RooFit::Components("signal1"),RooFit::LineStyle(kDashed),RooFit::LineColor(kGreen));
    model->plotOn(frame,RooFit::Components("signal2"),RooFit::LineStyle(kDashed),RooFit::LineColor(kMagenta - 5));
    model->plotOn(frame,RooFit::Components("signal3"),RooFit::LineStyle(kDashed),RooFit::LineColor(kOrange));
    model->plotOn(frame,RooFit::Components("background"),RooFit::LineStyle(kDashed),RooFit::LineColor(kRed));
    
    c_all->cd();
    frame->Draw("");
    
    RooPlot *frame_pass = InvariantMass.frame(RooFit::Title("Invariant Mass"));
    
    c_pass->cd();
    
    frame_pass->SetTitle("PASSING");
    frame_pass->SetXTitle("#mu^{+}#mu^{-} invariant mass [GeV/c^{2}]");
    Data_PASSING->plotOn(frame_pass);
    
    model_pass->plotOn(frame_pass);
    model_pass->plotOn(frame_pass,RooFit::Components("signal1"),RooFit::LineStyle(kDashed),RooFit::LineColor(kGreen));
    model_pass->plotOn(frame_pass,RooFit::Components("signal2"),RooFit::LineStyle(kDashed),RooFit::LineColor(kMagenta - 5));
    model_pass->plotOn(frame_pass,RooFit::Components("signal3"),RooFit::LineStyle(kDashed),RooFit::LineColor(kOrange));
    model_pass->plotOn(frame_pass,RooFit::Components("background"),RooFit::LineStyle(kDashed),RooFit::LineColor(kRed));
    
    frame_pass->Draw();

    if(save)
    {
        c_pass->SaveAs(("Fit Result/" + condition + "_ALL.pdf").c_str());
        c_all->SaveAs (("Fit Result/" + condition + "_PASS.pdf").c_str());
    }
        
    // DELETING ALLOCATED MEMORY
    delete[] limits;
    //
    delete file0;
    //
    delete Data_ALL;
    delete Data_PASSING;
    //
    delete dh_ALL;
    delete dh_PASSING;
    //
    delete cutvar;
    delete redeuce;
    //
    delete signal;
    //
    delete c_all;
    delete c_pass;
    //
    delete model;
    delete model_pass;
    delete fitres;
    
    return output;
}
