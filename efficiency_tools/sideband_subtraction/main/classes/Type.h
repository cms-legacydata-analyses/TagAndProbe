#include "InvariantMass.h"
#include "TagProbe.h"

//Holder for 2 TagProbe class
class Type{
private:
	const char*& resonance;
	const char*& particleName;
	const char*& canvasWatermark;
	const char*& directoryToSave;

	bool& doTagMuon;
	bool& doProbeMuon;

public:
	const char* particleType = NULL;

	InvariantMass Mass  {resonance, particleName, canvasWatermark, directoryToSave, particleType};
	TagProbe      Tag   {resonance, particleName, canvasWatermark, directoryToSave, particleType, Mass, "Tag"};
	TagProbe      Probe {resonance, particleName, canvasWatermark, directoryToSave, particleType, Mass, "Probe"};

	void defineMassHistogramNumbers(double xMin, double xMax, int nBins, int decimals = 3)
	{
		Mass.defineMassHistogramNumbers(xMin, xMax, nBins, decimals);
	}
	
	void doFit()
	{
		Mass.doFit();
	}

	void updateMassValuesAll()
	{
		Mass.updateMassValuesAll();
	}

	void createMassCanvas(bool drawRegions = false, bool shouldWrite = false, bool shouldSavePNG = false)
	{
		Mass.createMassCanvas(drawRegions, shouldWrite, shouldSavePNG);
	}

	void writeMassHistogramsOnFile(bool writehPass, bool writehAll)
	{
		Mass.writeMassHistogramsOnFile(writehPass, writehAll);
	}

	void normalizeHistograms()
	{
		if (doTagMuon)
			Tag  .normalizeHistograms();
		if (doProbeMuon)
			Probe.normalizeHistograms();
	}

	void subtractSigHistograms()
	{
		if (doTagMuon)
			Tag  .subtractSigHistograms();
		if (doProbeMuon)
			Probe.subtractSigHistograms();
	}

	void createQuantitiesCanvas(bool shouldWrite = false, bool shouldSavePNG = false)
	{
		if (doTagMuon)
			Tag  .createQuantitiesCanvas(shouldWrite, shouldSavePNG);
		if (doProbeMuon)
			Probe.createQuantitiesCanvas(shouldWrite, shouldSavePNG);
	}

	void consistencyDebugCout()
	{
		if (doTagMuon)
			Tag  .consistencyDebugCout();
		if (doProbeMuon)
			Probe.consistencyDebugCout();
	}

	void writeQuantitiesHistogramsOnFile(bool hSigBack, bool hSig, bool hBack)
	{
		if (doTagMuon)
			Tag  .writeQuantitiesHistogramsOnFile(hSigBack, hSig, hBack);
		if (doProbeMuon)
			Probe.writeQuantitiesHistogramsOnFile(hSigBack, hSig, hBack);
	}

	void createEfficiencyPlot(bool shouldWrite = false)
	{
		if (doTagMuon)
			Tag  .createEfficiencyPlot(shouldWrite);
		if (doProbeMuon)
			Probe.createEfficiencyPlot(shouldWrite);
	}

	void createEfficiencyCanvas(bool shouldWrite = false, bool shouldSavePNG = false)
	{
		if (doTagMuon)
			Tag  .createEfficiencyCanvas(shouldWrite, shouldSavePNG);
		if (doProbeMuon)
			Probe.createEfficiencyCanvas(shouldWrite, shouldSavePNG);
	}



	void fillMassHistograms(double& InvariantMass, int& isPassing)
	{
		Mass.fillMassHistograms(InvariantMass, isPassing);
	}

	void fillQuantitiesHistograms(double** quantities, int& isPassing)
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
		*/

		if (doTagMuon)
			Tag  .fillQuantitiesHistograms(&quantities[3], *quantities[6], isPassing);
		if (doProbeMuon)
			Probe.fillQuantitiesHistograms(quantities,     *quantities[6], isPassing);
	}


	Type(
		const char*& resonance,
		const char*& particleName,
		bool& doTagMuon,
		bool& doProbeMuon,
		const char*& canvasWatermark,
		const char*& directoryToSave,
	 	const char*  particleType)
		  : resonance(resonance),
		    particleName(particleName),
		    doTagMuon(doTagMuon),
		    doProbeMuon(doProbeMuon),
		    canvasWatermark(canvasWatermark),
		    directoryToSave(directoryToSave),
		    particleType(particleType)
	{}
};