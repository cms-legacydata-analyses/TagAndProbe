 /*
!--------------------------------
!Purpose: Find efficiency using Tag And Probe method
!--------------------------------	
!author: Allan Jales
!--------------------------------
*/

#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"

#include <iostream>
#include <chrono>
#include <TSystem.h>

#include "classes/SidebandSubtraction.h"
#include "config/cuts.h"

using namespace std;

//Select particles, draws and save histograms
void macro()
{
	//Input files, options are set here!
	#include "config/settings.cpp"



	//Check if the name of dir is ok
	if (string(directoryToSave).back() != string("/"))
	{
		cerr << "To avoid errors, please end the result directory with a \"/\"\n";
		abort();
	}

	//Check if dir exists and create
	if (gSystem->AccessPathName(directoryToSave))
	{
		if (gSystem->mkdir(directoryToSave, true))
		{
			cerr << "\"" << directoryToSave << "\" path could not be found and could not be created ERROR\n";
			cerr << "Try to create manually this folder path\n";
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



	//Compatibility adjusts on file read (for data_histoall ntuples)
	string folderName = "tagandprobe/";
	if (needsRetroCompatibility)
		folderName = "demo/";

	//Open and read files
	TFile *file0  = TFile::Open(files[useFile]);
	TTree *TreePC = (TTree*)file0->Get((folderName + "PlotControl").data());
	TTree *TreeAT = (TTree*)file0->Get((folderName + "AnalysisTree").data());
	cout << "Using \"" << files[useFile] << "\" ntupple\n";
	
	//Create variables
	double ProbeMuon_Pt;
	double ProbeMuon_Eta;
	double ProbeMuon_Phi;
	double TagMuon_Pt;
	double TagMuon_Eta;
	double TagMuon_Phi;
	double InvariantMass;
	int PassingProbeTrackingMuon;
	int PassingProbeStandAloneMuon;
	int PassingProbeGlobalMuon;

	//Assign variables
	TreePC->SetBranchAddress("ProbeMuon_Pt",				&ProbeMuon_Pt);
	TreePC->SetBranchAddress("ProbeMuon_Eta",				&ProbeMuon_Eta);
	TreePC->SetBranchAddress("ProbeMuon_Phi",				&ProbeMuon_Phi);
	TreePC->SetBranchAddress("TagMuon_Pt",					&TagMuon_Pt);
	TreePC->SetBranchAddress("TagMuon_Eta",					&TagMuon_Eta);
	TreePC->SetBranchAddress("TagMuon_Phi",					&TagMuon_Phi);
	if (needsRetroCompatibility)
	TreePC->SetBranchAddress("InvariantMass",				&InvariantMass);
	else
	TreeAT->SetBranchAddress("InvariantMass",				&InvariantMass);
	TreeAT->SetBranchAddress("PassingProbeTrackingMuon",	&PassingProbeTrackingMuon);
	TreeAT->SetBranchAddress("PassingProbeStandAloneMuon",	&PassingProbeStandAloneMuon);
	TreeAT->SetBranchAddress("PassingProbeGlobalMuon",		&PassingProbeGlobalMuon);

	double* quantities[] = {&ProbeMuon_Pt,
							&ProbeMuon_Eta,
							&ProbeMuon_Phi,
							&TagMuon_Pt,
							&TagMuon_Eta,
							&TagMuon_Phi,
							&InvariantMass,
		};
	
	int* types[] = {&PassingProbeTrackingMuon,
					&PassingProbeStandAloneMuon,
					&PassingProbeGlobalMuon
		};

	//Create a object and set configs
	SidebandSubtraction SdS{resonance};
	SdS.canvasWatermark	= canvasWatermark;
	SdS.directoryToSave = directoryToSave;
	SdS.doTracker       = doTracker;
	SdS.doStandalone    = doStandalone;
	SdS.doGlobal        = doGlobal;
	SdS.doTagMuon       = doTagMuon;
	SdS.doProbeMuon     = doProbeMuon;

	cout << "resonance: " << SdS.resonance << "\n";
	cout << "Using subtraction factor as integral of background fit\n";

	//Get data size and set data limit if has
	long long numberEntries = TreePC->GetEntries();
	if (limitData > 0 && limitData < numberEntries)
		numberEntries = limitData;
	printf("Data analysed = %lld of %lld\n", numberEntries, TreePC->GetEntries());



	//Prepare for showing progress
	string progressFormat = "Progress: %05.2f%% %0"+to_string(strlen(to_string(numberEntries).data()))+"lld/%lld\r";
	auto lastTime = std::chrono::steady_clock::now();
	auto start    = std::chrono::steady_clock::now();

/*
	//TEMPORARY FOR TEST
	TFile *file1 = TFile::Open("../results/Jpsi Run 2011/generated_hist.root");
	SdS.Tracker.Mass.Pass.hMass = (TH1D*)file1->Get("histograms/Passing_Tracker_Muon_InvariantMass");
	SdS.Tracker.Mass.All.hMass = (TH1D*)file1->Get("histograms/All_Tracker_Muon_InvariantMass");
	SdS.Standalone.Mass.Pass.hMass = (TH1D*)file1->Get("histograms/Passing_Standalone_Muon_InvariantMass");
	SdS.Standalone.Mass.All.hMass = (TH1D*)file1->Get("histograms/All_Standalone_Muon_InvariantMass");
	SdS.Global.Mass.Pass.hMass = (TH1D*)file1->Get("histograms/Passing_Global_Muon_InvariantMass");
	SdS.Global.Mass.All.hMass = (TH1D*)file1->Get("histograms/All_Global_Muon_InvariantMass");
*/

	cout << "\nFilling Invariant Mass Histograms..... (1/2)\n";

	//Loop between the components
	for (long long i = 0; i < numberEntries; i++)
	{
		//Select particle pair
		TreePC->GetEntry(i);
		TreeAT->GetEntry(i);

		//Show progress on screen
		if (chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now() - lastTime).count() >= 1000 || i == numberEntries - 1)
		{
			printf(progressFormat.data(), (float)(i+1)/(float)numberEntries*100, i+1, numberEntries);
			lastTime = chrono::steady_clock::now();
		}

		//Fill histograms
		if (applyCuts(quantities, types))
		{
			SdS.fillMassHistograms(quantities, types);
		}
	}

	cout << "\nTook " << chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now() - start).count() << " ms\n";

	//Do function fit over the histogram
	SdS.doFit();

	//Get values for invariant mass and sigma from plot
	SdS.updateMassValuesAll();

	//-------------------------------------
	// Generate and save files
	//-------------------------------------

	//Supress canvas PROBLEMS BELOW:
	//- Does not store TBox of sideband subtraction
	//gROOT->SetBatch(1);

	//Create file root to store generated files
	TFile* generatedFile = TFile::Open((string(directoryToSave) + "generated_hist.root").data(),"RECREATE");
	generatedFile->mkdir("canvas/");
	generatedFile->   cd("canvas/");

	if (shouldDrawInvariantMassCanvas)
	{
		bool drawRegions 	= false;
		bool shouldWrite 	= true;
		bool shouldSavePNG 	= true;

		SdS.createMassCanvas(drawRegions, shouldWrite, shouldSavePNG);
	}

	if (shouldDrawInvariantMassCanvasRegion)
	{
		bool drawRegions 	= true;
		bool shouldWrite 	= true;
		bool shouldSavePNG 	= true;

		SdS.createMassCanvas(drawRegions, shouldWrite, shouldSavePNG);
	}
	


	//Prepare for showing progress
	lastTime = std::chrono::steady_clock::now();
	start    = std::chrono::steady_clock::now();

	cout << "\nFilling Quantities Histograms..... (2/2)\n";

	//Loop between the components again
	for (long long i = 0; i < numberEntries; i++)
	{
		//Select particle pair
		TreePC->GetEntry(i);
		TreeAT->GetEntry(i);

		//Show progress on screen
		if (chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now() - lastTime).count() >= 1000 || i == numberEntries - 1)
		{
			printf(progressFormat.data(), (float)(i+1)/(float)numberEntries*100, i+1, numberEntries);
			lastTime = chrono::steady_clock::now();
		}

		//Fill histograms
		if (applyCuts(quantities, types))
		{	
			SdS.fillQuantitiesHistograms(quantities, types);
		}
	}
	cout << "\nTook " << chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now() - start).count() << " ms\n";

	//Normalize Histograms for variable binning
	cout << "\n";
	SdS.normalizeHistograms();	

	//For sideband subtraction
	SdS.subtractSigHistograms();



	if (shouldDrawQuantitiesCanvas)
	{
		bool shouldWrite 	= true;
		bool shouldSavePNG 	= true;

		cout << "\n";
		SdS.createQuantitiesCanvas(shouldWrite, shouldSavePNG);
	}

	//Debug consistency for histograms
	SdS.consistencyDebugCout();

	//Save histograms
	generatedFile->mkdir("histograms/");
	generatedFile->   cd("histograms/");

	//Write quantities histograms on file
	{
		bool writehSigBack 	= true;
		bool writehSig 		= true;
		bool writehBack 	= true;
	
		SdS.writeQuantitiesHistogramsOnFile(writehSigBack, writehSig, writehBack);
	}

	//Write mass histograms on file
	{
		bool writehPass = true;
		bool writehAll 	= true;

		SdS.writeMassHistogramsOnFile(writehPass, writehAll);
	}

	//Save plots
	generatedFile->mkdir("efficiency/plots/");
	generatedFile->cd("efficiency/plots/");

	//Creates efficiency plots
	{
		bool shouldWrite 	= true;

		SdS.createEfficiencyPlot(shouldWrite);
	}


	//Saves new histograms and canvas in file
	generatedFile->mkdir("efficiency/canvas/");
	generatedFile->cd("efficiency/canvas/");

	if (shouldDrawEfficiencyCanvas)
	{
		bool shouldWrite 	= true;
		bool shouldSavePNG 	= true;

		cout << "\n";
		SdS.createEfficiencyCanvas(shouldWrite, shouldSavePNG);
	}

	//Close files
	generatedFile->Close();

	cout << "\nDone. All result files can be found at \"" << SdS.directoryToSave << "\"\n\n";
}