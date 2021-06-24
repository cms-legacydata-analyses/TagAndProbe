#include "Type.h"

//Holder for 3 Type class
class SidebandSubtraction
{
public:
	const char* resonance       = "Jpsi"; // "Jpsi" | "Upsilon" | "Upsilon1S"
	const char* particleName    = "Muon";
	const char* canvasWatermark = "#bf{CMS Open Data}";
	const char* directoryToSave = "../result/";

	//Variables for computing each type
	bool doTracker    = true;
	bool doStandalone = true;
	bool doGlobal     = true;

	//Variables for computing each muon label
	bool doTagMuon   = true;
	bool doProbeMuon = true;

	Type Tracker    {resonance, particleName, doTagMuon, doProbeMuon, canvasWatermark, directoryToSave, "Tracker"};
	Type Standalone {resonance, particleName, doTagMuon, doProbeMuon, canvasWatermark, directoryToSave, "Standalone"};
	Type Global     {resonance, particleName, doTagMuon, doProbeMuon, canvasWatermark, directoryToSave, "Global"};
	
	void defineMassHistogramNumbers(double xMin, double xMax, int nBins, int decimals = 3)
	{
		if (doTracker)
			Tracker   .defineMassHistogramNumbers(xMin, xMax, nBins, decimals);
		if (doStandalone)
			Standalone.defineMassHistogramNumbers(xMin, xMax, nBins, decimals);
		if (doGlobal)
			Global    .defineMassHistogramNumbers(xMin, xMax, nBins, decimals);
	}

	void doFit()
	{
		if (doTracker)
			Tracker   .doFit();
		if (doStandalone)
			Standalone.doFit();
		if (doGlobal)
			Global    .doFit();
	}

	void normalizeHistograms()
	{
		cout << "Normalizing quantities histograms\n";
		if (doTracker)
			Tracker   .normalizeHistograms();
		if (doStandalone)
			Standalone.normalizeHistograms();
		if (doGlobal)
			Global    .normalizeHistograms();
		cout << "Quantities histograms normalized.\n";
	}

	void updateMassValuesAll()
	{
		if (doTracker)
			Tracker   .updateMassValuesAll();
		if (doStandalone)
			Standalone.updateMassValuesAll();
		if (doGlobal)
			Global    .updateMassValuesAll();
	}

	void createMassCanvas(bool drawRegions = false, bool shouldWrite = false, bool shouldSavePNG = false)
	{
		if (doTracker)
			Tracker   .createMassCanvas(drawRegions, shouldWrite, shouldSavePNG);
		if (doStandalone)
			Standalone.createMassCanvas(drawRegions, shouldWrite, shouldSavePNG);
		if (doGlobal)
			Global    .createMassCanvas(drawRegions, shouldWrite, shouldSavePNG);
	}

	void subtractSigHistograms()
	{
		if (doTracker)
			Tracker   .subtractSigHistograms();
		if (doStandalone)
			Standalone.subtractSigHistograms();
		if (doGlobal)
			Global    .subtractSigHistograms();
	}

	void createQuantitiesCanvas(bool shouldWrite = false, bool shouldSavePNG = false)
	{
		if (doTracker)
			Tracker   .createQuantitiesCanvas(shouldWrite, shouldSavePNG);
		if (doStandalone)
			Standalone.createQuantitiesCanvas(shouldWrite, shouldSavePNG);
		if (doGlobal)
			Global    .createQuantitiesCanvas(shouldWrite, shouldSavePNG);
	}

	void consistencyDebugCout()
	{
		cout << "\nChecking histograms number inconsistency (should be 0)\n";
		cout << "* total - (signal + alpha*background) by TH1D integral\n";
		if (doTracker)
			Tracker   .consistencyDebugCout();
		if (doStandalone)
			Standalone.consistencyDebugCout();
		if (doGlobal)
			Global    .consistencyDebugCout();
	}

	void writeMassHistogramsOnFile(bool writehPass, bool writehAll)
	{
		if (doTracker)
			Tracker   .writeMassHistogramsOnFile(writehPass, writehAll);
		if (doStandalone)
			Standalone.writeMassHistogramsOnFile(writehPass, writehAll);
		if (doGlobal)
			Global    .writeMassHistogramsOnFile(writehPass, writehAll);
	}

	void writeQuantitiesHistogramsOnFile(bool hSigBack, bool hSig, bool hBack)
	{
		if (doTracker)
			Tracker   .writeQuantitiesHistogramsOnFile(hSigBack, hSig, hBack);
		if (doStandalone)
			Standalone.writeQuantitiesHistogramsOnFile(hSigBack, hSig, hBack);
		if (doGlobal)
			Global    .writeQuantitiesHistogramsOnFile(hSigBack, hSig, hBack);
	}

	void createEfficiencyPlot(bool shouldWrite = false)
	{
		if (doTracker)
			Tracker   .createEfficiencyPlot(shouldWrite);
		if (doStandalone)
			Standalone.createEfficiencyPlot(shouldWrite);
		if (doGlobal)
			Global    .createEfficiencyPlot(shouldWrite);
	}

	void createEfficiencyCanvas(bool shouldWrite = false, bool shouldSavePNG = false)
	{
		if (doTracker)
			Tracker   .createEfficiencyCanvas(shouldWrite, shouldSavePNG);
		if (doStandalone)
			Standalone.createEfficiencyCanvas(shouldWrite, shouldSavePNG);
		if (doGlobal)
			Global    .createEfficiencyCanvas(shouldWrite, shouldSavePNG);
	}



	void fillMassHistograms(double** quantities, int** types)
	{
		/*
		//Assign variables for easy visualization
		double &ProbeMuon_Pt            = *quantities[0];
		double &ProbeMuon_Eta           = *quantities[1];
		double &ProbeMuon_Phi           = *quantities[2];
		double &TagMuon_Pt              = *quantities[3];
		double &TagMuon_Eta             = *quantities[4];
		double &TagMuon_Phi             = *quantities[5];
		double &InvariantMass           = *quantities[6];
		int &PassingProbeTrackingMuon   = *types[0];
		int &PassingProbeStandAloneMuon = *types[1];
		int &PassingProbeGlobalMuon     = *types[2];
		*/

		if (doTracker)
			Tracker   .fillMassHistograms(*quantities[6], *types[0]);
		if (doStandalone)
			Standalone.fillMassHistograms(*quantities[6], *types[1]);
		if (doGlobal)
			Global    .fillMassHistograms(*quantities[6], *types[2]);
	}

	void fillQuantitiesHistograms(double** quantities, int** types)
	{
		/*
		//Assign variables for easy visualization
		double &ProbeMuon_Pt            = *quantities[0];
		double &ProbeMuon_Eta           = *quantities[1];
		double &ProbeMuon_Phi           = *quantities[2];
		double &TagMuon_Pt              = *quantities[3];
		double &TagMuon_Eta             = *quantities[4];
		double &TagMuon_Phi             = *quantities[5];
		double &InvariantMass           = *quantities[6];
		int &PassingProbeTrackingMuon   = *types[0];
		int &PassingProbeStandAloneMuon = *types[1];
		int &PassingProbeGlobalMuon     = *types[2];
		*/

		if (doTracker)
			Tracker   .fillQuantitiesHistograms(quantities, *types[0]);
		if (doStandalone)
			Standalone.fillQuantitiesHistograms(quantities, *types[1]);
		if (doGlobal)
			Global    .fillQuantitiesHistograms(quantities, *types[2]);
	}
	


	SidebandSubtraction()
	{}

	SidebandSubtraction(const char* resonance)
			: resonance(resonance)
	{}
};