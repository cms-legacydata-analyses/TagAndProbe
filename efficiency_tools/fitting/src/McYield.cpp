
double* McYield(string condition, string quant, string MuonID_str = "PassingProbeTrackingMuon")
{
    TFile *file0    = TFile::Open("DATA/Upsilon/trackerMuon/T&P_UPSILON_DATA_MC.root");
    TTree *DataTree = (TTree*)file0->Get(("UPSILON_DATA"));
    
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
    
    double* output = new double[2];
    output[0] = Data_ALL->sumEntries();
    output[1] = Data_PASSING->sumEntries();
    return output;
}

