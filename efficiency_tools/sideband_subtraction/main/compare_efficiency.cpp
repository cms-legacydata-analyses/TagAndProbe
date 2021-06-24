 /*
!--------------------------------
!Purpose: Compare efficiency of files
!--------------------------------	
!author: Allan Jales
!--------------------------------
*/

//CONFIGS

int useScheme = 0	;
//Jpsi    Sideband Run vs Jpsi    Sideband MC
//Jpsi    Fitting  Run vs Jpsi    Fitting  MC
//Jpsi    Sideband Run vs Jpsi    Fitting  Run
//Upsilon Sideband Run vs Upsilon Sideband MC
//Upsilon Fitting  Run vs Upsilon Fitting  MC
//Upsilon Sideband Run vs Upsilon Fitting  Run

//Muon id anlyse
bool doTracker    = true;
bool doStandalone = true;
bool doGlobal     = true;

//Root files and paths for Tefficiency objects inside these files

// DATA

const char* sid_run_upsilon[][2] = {
	{"../results/Upsilon_Run_2011/generated_hist.root", "efficiency/plots/Muon_Pt_Tracker_Probe_Efficiency"},
	{"../results/Upsilon_Run_2011/generated_hist.root", "efficiency/plots/Muon_Eta_Tracker_Probe_Efficiency"},
	{"../results/Upsilon_Run_2011/generated_hist.root", "efficiency/plots/Muon_Phi_Tracker_Probe_Efficiency"},
	{"../results/Upsilon_Run_2011/generated_hist.root", "efficiency/plots/Muon_Pt_Standalone_Probe_Efficiency"},
	{"../results/Upsilon_Run_2011/generated_hist.root", "efficiency/plots/Muon_Eta_Standalone_Probe_Efficiency"},
	{"../results/Upsilon_Run_2011/generated_hist.root", "efficiency/plots/Muon_Phi_Standalone_Probe_Efficiency"},
	{"../results/Upsilon_Run_2011/generated_hist.root", "efficiency/plots/Muon_Pt_Global_Probe_Efficiency"},
	{"../results/Upsilon_Run_2011/generated_hist.root", "efficiency/plots/Muon_Eta_Global_Probe_Efficiency"},
	{"../results/Upsilon_Run_2011/generated_hist.root", "efficiency/plots/Muon_Phi_Global_Probe_Efficiency"}
};

const char* sid_run_jpsi[][2] = {
	{"../results/Jpsi_Run_2011/generated_hist.root", "efficiency/plots/Muon_Pt_Tracker_Probe_Efficiency"},
	{"../results/Jpsi_Run_2011/generated_hist.root", "efficiency/plots/Muon_Eta_Tracker_Probe_Efficiency"},
	{"../results/Jpsi_Run_2011/generated_hist.root", "efficiency/plots/Muon_Phi_Tracker_Probe_Efficiency"},
	{"../results/Jpsi_Run_2011/generated_hist.root", "efficiency/plots/Muon_Pt_Standalone_Probe_Efficiency"},
	{"../results/Jpsi_Run_2011/generated_hist.root", "efficiency/plots/Muon_Eta_Standalone_Probe_Efficiency"},
	{"../results/Jpsi_Run_2011/generated_hist.root", "efficiency/plots/Muon_Phi_Standalone_Probe_Efficiency"},
	{"../results/Jpsi_Run_2011/generated_hist.root", "efficiency/plots/Muon_Pt_Global_Probe_Efficiency"},
	{"../results/Jpsi_Run_2011/generated_hist.root", "efficiency/plots/Muon_Eta_Global_Probe_Efficiency"},
	{"../results/Jpsi_Run_2011/generated_hist.root", "efficiency/plots/Muon_Phi_Global_Probe_Efficiency"}
};

const char* fit_run_upsilon[][2] = {
	{"../../fitting/Efficiency Result/Tracker/Pt/Efficiency_Run2011.root",     "Efficiency"},
	{"../../fitting/Efficiency Result/Tracker/Eta/Efficiency_Run2011.root",    "Efficiency"},
	{"../../fitting/Efficiency Result/Tracker/Phi/Efficiency_Run2011.root",    "Efficiency"},
	{"../../fitting/Efficiency Result/Standalone/Pt/Efficiency_Run2011.root",  "Efficiency"},
	{"../../fitting/Efficiency Result/Standalone/Eta/Efficiency_Run2011.root", "Efficiency"},
	{"../../fitting/Efficiency Result/Standalone/Phi/Efficiency_Run2011.root", "Efficiency"},
	{"../../fitting/Efficiency Result/Global/Pt/Efficiency_Run2011.root",      "Efficiency"},
	{"../../fitting/Efficiency Result/Global/Eta/Efficiency_Run2011.root",     "Efficiency"},
	{"../../fitting/Efficiency Result/Global/Phi/Efficiency_Run2011.root",     "Efficiency"}
};

const char* fit_run_jpsi[][2] = {
	{"../../fitting/Efficiency Result/Tracker/Pt/Efficiency_Run2011.root",     "Efficiency"},
	{"../../fitting/Efficiency Result/Tracker/Eta/Efficiency_Run2011.root",    "Efficiency"},
	{"../../fitting/Efficiency Result/Tracker/Phi/Efficiency_Run2011.root",    "Efficiency"},
	{"../../fitting/Efficiency Result/Standalone/Pt/Efficiency_Run2011.root",  "Efficiency"},
	{"../../fitting/Efficiency Result/Standalone/Eta/Efficiency_Run2011.root", "Efficiency"},
	{"../../fitting/Efficiency Result/Standalone/Phi/Efficiency_Run2011.root", "Efficiency"},
	{"../../fitting/Efficiency Result/Global/Pt/Efficiency_Run2011.root",      "Efficiency"},
	{"../../fitting/Efficiency Result/Global/Eta/Efficiency_Run2011.root",     "Efficiency"},
	{"../../fitting/Efficiency Result/Global/Phi/Efficiency_Run2011.root",     "Efficiency"}
};

// MC METHOD

const char* sid_mc_upsilon[][2] = {
	{"../results/Upsilon_MC_2020_sbs/generated_hist.root", "efficiency/plots/Muon_Pt_Tracker_Probe_Efficiency"},
	{"../results/Upsilon_MC_2020_sbs/generated_hist.root", "efficiency/plots/Muon_Eta_Tracker_Probe_Efficiency"},
	{"../results/Upsilon_MC_2020_sbs/generated_hist.root", "efficiency/plots/Muon_Phi_Tracker_Probe_Efficiency"},
	{"../results/Upsilon_MC_2020_sbs/generated_hist.root", "efficiency/plots/Muon_Pt_Standalone_Probe_Efficiency"},
	{"../results/Upsilon_MC_2020_sbs/generated_hist.root", "efficiency/plots/Muon_Eta_Standalone_Probe_Efficiency"},
	{"../results/Upsilon_MC_2020_sbs/generated_hist.root", "efficiency/plots/Muon_Phi_Standalone_Probe_Efficiency"},
	{"../results/Upsilon_MC_2020_sbs/generated_hist.root", "efficiency/plots/Muon_Pt_Global_Probe_Efficiency"},
	{"../results/Upsilon_MC_2020_sbs/generated_hist.root", "efficiency/plots/Muon_Eta_Global_Probe_Efficiency"},
	{"../results/Upsilon_MC_2020_sbs/generated_hist.root", "efficiency/plots/Muon_Phi_Global_Probe_Efficiency"}
};

const char* sid_mc_jpsi[][2] = {
	{"../results/Jpsi_MC_2020_sbs/generated_hist.root", "efficiency/plots/Muon_Pt_Tracker_Probe_Efficiency"},
	{"../results/Jpsi_MC_2020_sbs/generated_hist.root", "efficiency/plots/Muon_Eta_Tracker_Probe_Efficiency"},
	{"../results/Jpsi_MC_2020_sbs/generated_hist.root", "efficiency/plots/Muon_Phi_Tracker_Probe_Efficiency"},
	{"../results/Jpsi_MC_2020_sbs/generated_hist.root", "efficiency/plots/Muon_Pt_Standalone_Probe_Efficiency"},
	{"../results/Jpsi_MC_2020_sbs/generated_hist.root", "efficiency/plots/Muon_Eta_Standalone_Probe_Efficiency"},
	{"../results/Jpsi_MC_2020_sbs/generated_hist.root", "efficiency/plots/Muon_Phi_Standalone_Probe_Efficiency"},
	{"../results/Jpsi_MC_2020_sbs/generated_hist.root", "efficiency/plots/Muon_Pt_Global_Probe_Efficiency"},
	{"../results/Jpsi_MC_2020_sbs/generated_hist.root", "efficiency/plots/Muon_Eta_Global_Probe_Efficiency"},
	{"../results/Jpsi_MC_2020_sbs/generated_hist.root", "efficiency/plots/Muon_Phi_Global_Probe_Efficiency"}
};

const char* fit_mc_upsilon[][2] = {
	{"../../fitting/Efficiency Result/Tracker/Pt/Efficiency_MC.root",     "Efficiency"},
	{"../../fitting/Efficiency Result/Tracker/Eta/Efficiency_MC.root",    "Efficiency"},
	{"../../fitting/Efficiency Result/Tracker/Phi/Efficiency_MC.root",    "Efficiency"},
	{"../../fitting/Efficiency Result/Standalone/Pt/Efficiency_MC.root",  "Efficiency"},
	{"../../fitting/Efficiency Result/Standalone/Eta/Efficiency_MC.root", "Efficiency"},
	{"../../fitting/Efficiency Result/Standalone/Phi/Efficiency_MC.root", "Efficiency"},
	{"../../fitting/Efficiency Result/Global/Pt/Efficiency_MC.root",      "Efficiency"},
	{"../../fitting/Efficiency Result/Global/Eta/Efficiency_MC.root",     "Efficiency"},
	{"../../fitting/Efficiency Result/Global/Phi/Efficiency_MC.root",     "Efficiency"}
};

const char* fit_mc_jpsi[][2] = {
	{"../../fitting/Efficiency Result/Tracker/Pt/Efficiency_MC.root",     "Efficiency"},
	{"../../fitting/Efficiency Result/Tracker/Eta/Efficiency_MC.root",    "Efficiency"},
	{"../../fitting/Efficiency Result/Tracker/Phi/Efficiency_MC.root",    "Efficiency"},
	{"../../fitting/Efficiency Result/Standalone/Pt/Efficiency_MC.root",  "Efficiency"},
	{"../../fitting/Efficiency Result/Standalone/Eta/Efficiency_MC.root", "Efficiency"},
	{"../../fitting/Efficiency Result/Standalone/Phi/Efficiency_MC.root", "Efficiency"},
	{"../../fitting/Efficiency Result/Global/Pt/Efficiency_MC.root",      "Efficiency"},
	{"../../fitting/Efficiency Result/Global/Eta/Efficiency_MC.root",     "Efficiency"},
	{"../../fitting/Efficiency Result/Global/Phi/Efficiency_MC.root",     "Efficiency"}
};

//How comparisons will be saved
const char* resultNames[] = {
	"Muon_Pt_Tracker_Probe_Efficiency.png",
	"Muon_Eta_Tracker_Probe_Efficiency.png",
	"Muon_Phi_Tracker_Probe_Efficiency.png",
	"Muon_Pt_Standalone_Probe_Efficiency.png",
	"Muon_Eta_Standalone_Probe_Efficiency.png",
	"Muon_Phi_Standalone_Probe_Efficiency.png",
	"Muon_Pt_Global_Probe_Efficiency.png",
	"Muon_Eta_Global_Probe_Efficiency.png",
	"Muon_Phi_Global_Probe_Efficiency.png",
};

//How comparisons will be saved
const char* resultTitles[] = {
	"Efficiency of Tracker Muon Probe",
	"Efficiency of Tracker Muon Probe",
	"Efficiency of Tracker Muon Probe",
	"Efficiency of Standalone Muon Probe",
	"Efficiency of Standalone Muon Probe",
	"Efficiency of Standalone Muon Probe",
	"Efficiency of Global Muon Probe",
	"Efficiency of Global Muon Probe",
	"Efficiency of Global Muon Probe",
};

//Label of each comparison
const char* labelScheme[][2] = {
	{"J/#psi Data Sideband",       "J/#psi MC Sideband"},
	{"J/#psi Data Fitting",        "J/#psi MC Fitting"},
	{"J/#psi Data Sideband",       "J/#psi Data Fitting"},
	{"#Upsilon(1S) Data Sideband", "#Upsilon(1S) MC Sideband"},
	{"#Upsilon(1S) Data Fitting",  "#Upsilon(1S) MC Fitting"},
	{"#Upsilon(1S) Data Sideband", "#Upsilon(1S) Data Fitting"}
};

//Where to save each comparison
const char* directoriesToSave[] = {
	"../results/Comparison/Comparison_Jpsi_Sideband_Run_vs_MC/",
	"../results/Comparison/Comparison_Jpsi_Fitting_Run_vs_MC/",
	"../results/Comparison/Comparison_Jpsi_Sideband_vs_Fitting/",
	"../results/Comparison/Comparison_Upsilon_Sideband_Run_vs_MC/",
	"../results/Comparison/Comparison_Upsilon_Fitting_Run_vs_MC/",
	"../results/Comparison/Comparison_Upsilon_Sideband_vs_Fitting/"
};

//Colors for each comparison
int colorScheme[][2] = {
	{kBlue  + 1, kRed    - 4},
	{kGreen - 2, kOrange + 2},
	{kBlue  + 1, kGreen  - 2},
	{kBlue  + 1, kRed    - 4},
	{kGreen - 2, kOrange + 2},
	{kBlue  + 1, kGreen  - 2},
};

//Choose a option between two
const char* chooseOption(int item, const char* option0, const char* option1)
{
	switch (item)
	{
		case 0:  return option0;
		case 1:  return option1;
		default: return NULL;
	}
}

//Get a file path
const char* getFilePath(int index, int row, int col)
{
	switch (useScheme)
	{
		case 0:  return chooseOption(index, sid_run_jpsi   [row][col], sid_mc_jpsi    [row][col]);
		case 1:  return chooseOption(index, fit_run_jpsi   [row][col], fit_mc_jpsi    [row][col]);
		case 2:  return chooseOption(index, sid_run_jpsi   [row][col], fit_run_jpsi   [row][col]);
		case 3:  return chooseOption(index, sid_run_upsilon[row][col], sid_mc_upsilon [row][col]);
		case 4:  return chooseOption(index, fit_run_upsilon[row][col], fit_mc_upsilon [row][col]);
		case 5:  return chooseOption(index, sid_run_upsilon[row][col], fit_run_upsilon[row][col]);

		default:
			std::cerr << "ERROR: useScheme not found\n";
			std::cerr << "ABORTING...\n";
			abort();
			return NULL;
	}
}

//Get TEfficiency from file_path
TEfficiency* get_eff_plot(const char* file_path, const char* hist_path)
{
	TFile *file0 = TFile::Open(file_path);

	if (file0 == NULL)
	{
		std::cerr << "Could not find \"" << file_path << "\" file.\n";
		std::cerr << "ABORTING...\n";
		abort();
	}

	TEfficiency* pEff0 = (TEfficiency*)file0->Get(hist_path);

	if (pEff0 == NULL)
	{
		std::cerr << "Could not find the histogram path \"" << hist_path << "\" in \"" << file_path << "\" file.\n";
		std::cerr << "ABORTING...\n";
		abort();
	}

	return pEff0;
}

//Compare two Tefficiencies and save
void compare_eff_plot(TEfficiency* pEff0, TEfficiency* pEff1, string resultName, const char* quantity = "", string resultTitle = "")
{
	//Create canvas
	TCanvas* c1 = new TCanvas();
	//gStyle->SetOptTitle(0);
	c1->SetMargin(0.10, 0.03, 0.11, 0.07);

	//Plot
	pEff0->SetMarkerColor(colorScheme[useScheme][0]);
	pEff0->SetLineColor(colorScheme[useScheme][0]);
	pEff0->SetLineWidth(1);
	pEff0->Draw();

	pEff1->SetMarkerColor(colorScheme[useScheme][1]);
	pEff1->SetLineColor(colorScheme[useScheme][1]);
	pEff1->SetLineWidth(1);
	pEff1->Draw("same");
	
	//Set range in y axis
	gPad->Update();
	auto graph = pEff0->GetPaintedGraph(); 
	graph->SetMinimum(0.0);
	graph->SetMaximum(1.2);
	gPad->Update();

	//Set range if is pT
	if (strcmp(quantity, "Pt") == 0)
	{
		pEff0->GetPaintedGraph()->GetHistogram()->GetXaxis()->SetRangeUser(0.,40.);
		graph->SetMinimum(0.5);
		graph->SetMaximum(1.2);

		if (strcmp(quantity, "") != 0)
			pEff0->SetTitle((resultTitle + ";p_{T} [GeV/c];Efficiency").data());
	}
	
	//Set range if is eta
	if (strcmp(quantity, "Eta") == 0)
	{
		pEff0->GetPaintedGraph()->GetHistogram()->GetXaxis()->SetRangeUser(-3.,3.);
		graph->SetMinimum(0.8);
		graph->SetMaximum(1.08);

		if (strcmp(quantity, "") != 0)
			pEff0->SetTitle((resultTitle + ";#eta;Efficiency").data());
	}
	
	//Set range if is phi
	if (strcmp(quantity, "Phi") == 0)
	{
		graph->SetMinimum(0.8);
		graph->SetMaximum(1.08);

		if (strcmp(quantity, "") != 0)
			pEff0->SetTitle((resultTitle + ";#phi [rad];Efficiency").data());
	}

	//Legenda
	TLegend* tl = new TLegend(0.60,0.78,0.94,0.88);
	tl->SetTextSize(0.04);
	tl->AddEntry(pEff0, labelScheme[useScheme][0], "lp");
	tl->AddEntry(pEff1, labelScheme[useScheme][1], "lp");
	tl->Draw();

	//CMS Open Data
	TLatex* txCOD = new TLatex();
	txCOD->SetTextSize(0.04);
	txCOD->SetTextAlign(12);
	txCOD->SetTextFont(42);
	txCOD->SetNDC(kTRUE);
	txCOD->DrawLatex(0.14,0.85,Form("#bf{CMS Open Data}"));


	//Saving as png

	//Path where is going to save results 
	const char* directoryToSave = directoriesToSave[useScheme];

	//Check if dir exists and create
	if (gSystem->AccessPathName(directoryToSave))
	{
		if (gSystem->mkdir(directoryToSave, true))
		{
			cerr << "\"" << directoryToSave << "\" directory not found and could not be created ERROR\n";
			abort();
		}
		else
		{
			cout << "\"" << directoryToSave << "\" directory created OK\n";
		}
	}
	else
	{
		cout << "\"" << directoryToSave << "\" directory OK\n";
	}

	//Path of file
	string saveAs = string(directoryToSave) + resultName;

	c1->SaveAs(saveAs.data());
}

//Compare efficiency
void compare_efficiency()
{
	for (int i = 0; i < 9; i++)
	{
		if (!doTracker    && i < 3)
			continue;
		if (!doStandalone && i >= 3 && i < 6)
			continue;
		if (!doGlobal     && i >= 6)
			continue;

		//Get Tefficiency object
		TEfficiency* pEff0 = get_eff_plot(getFilePath(0,i,0), getFilePath(0,i,1));
		TEfficiency* pEff1 = get_eff_plot(getFilePath(1,i,0), getFilePath(1,i,1));

		//Name of file
		string resultName  = resultNames[i];
		string resultTitle = resultTitles[i];

		std::cout << "\nEvaluating: " << resultName << "\n";
		std::cout << "----------------------------------\n";

		//Get which quantity is working on
		const char* quantity = "";

		if (regex_match(resultNames[i], regex(".*Pt.*")))
			quantity = "Pt";

		if (regex_match(resultNames[i], regex(".*Eta.*")))
			quantity = "Eta";

		if (regex_match(resultNames[i], regex(".*Phi.*")))
			quantity = "Phi";


		//Compare efficiency polts
		compare_eff_plot(pEff0, pEff1, resultName, quantity, resultTitle);
		std::cout << "----------------------------------\n";
	}

	cout << "\nUse Scheme: " << useScheme << "\n";
	cout << "Done. All result files can be found at \"" << directoriesToSave[useScheme] << "\"\n";
}