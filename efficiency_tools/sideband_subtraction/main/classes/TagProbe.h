#include "PtEtaPhi.h"

//Holder for 3 set of histograms for each quantity
class TagProbe{
private:
	const char*& resonance;
	const char*& particleName;
	const char*& canvasWatermark;
	const char*& directoryToSave;
	const char*& particleType;
	InvariantMass& ObjMass;

public:
	const char* tagOrProbe = NULL;

	PtEtaPhi Pt  {resonance, particleName, canvasWatermark, directoryToSave, particleType, ObjMass, tagOrProbe,
		"Pt",  "p_{t}", "GeV/c", "Transverse Momentum", 50,  0.00, 80.00};
	PtEtaPhi Eta {resonance, particleName, canvasWatermark, directoryToSave, particleType, ObjMass, tagOrProbe,
		"Eta", "#eta",  "", 	 "Pseudorapidity",      50, -2.50,  2.50};
	PtEtaPhi Phi {resonance, particleName, canvasWatermark, directoryToSave, particleType, ObjMass, tagOrProbe,
		"Phi", "#phi",  "rad",   "Azimuthal Angle",     15, -3.15,  3.15};

	void normalizeHistograms()
	{
		Pt .normalizeHistograms();
		Eta.normalizeHistograms();
		Phi.normalizeHistograms();
	}

	void subtractSigHistograms()
	{
		Pt .subtractSigHistograms();
		Eta.subtractSigHistograms();
		Phi.subtractSigHistograms();
	}

	void createQuantitiesCanvas(bool shouldWrite = false, bool shouldSavePNG = false)
	{
		Pt .createQuantitiesCanvas(shouldWrite, shouldSavePNG);
		Eta.createQuantitiesCanvas(shouldWrite, shouldSavePNG);
		Phi.createQuantitiesCanvas(shouldWrite, shouldSavePNG);
	}

	void consistencyDebugCout()
	{
		Pt .consistencyDebugCout();
		Eta.consistencyDebugCout();
		Phi.consistencyDebugCout();
	}

	void writeQuantitiesHistogramsOnFile(bool hSigBack, bool hSig, bool hBack)
	{
		Pt .writeQuantitiesHistogramsOnFile(hSigBack, hSig, hBack);
		Eta.writeQuantitiesHistogramsOnFile(hSigBack, hSig, hBack);
		Phi.writeQuantitiesHistogramsOnFile(hSigBack, hSig, hBack);
	}

	void createEfficiencyPlot(bool shouldWrite = false)
	{
		Pt .createEfficiencyPlot(shouldWrite);
		Eta.createEfficiencyPlot(shouldWrite);
		Phi.createEfficiencyPlot(shouldWrite);
	}

	void createEfficiencyCanvas(bool shouldWrite = false, bool shouldSavePNG = false)
	{
		Pt .createEfficiencyCanvas(shouldWrite, shouldSavePNG);
		Eta.createEfficiencyCanvas(shouldWrite, shouldSavePNG);
		Phi.createEfficiencyCanvas(shouldWrite, shouldSavePNG);
	}


	void fillQuantitiesHistograms(double** quantities, double& InvariantMass, int& isPassing)
	{
		/*
		//Assign variables for easy visualization
		double &pt  = *quantities[0];
		double &eta = *quantities[1];
		double &phi = *quantities[2];
		*/

		Pt .fillQuantitiesHistograms(*quantities[0], InvariantMass, isPassing);
		Eta.fillQuantitiesHistograms(*quantities[1], InvariantMass, isPassing);
		Phi.fillQuantitiesHistograms(*quantities[2], InvariantMass, isPassing);
	}



	TagProbe(
		const char*& resonance,
		const char*& particleName,
		const char*& canvasWatermark,
		const char*& directoryToSave,
	 	const char*& particleType,
	 	InvariantMass& ObjMass,
	 	const char*  tagOrProbe)
		  : resonance(resonance),
		    particleName(particleName),
		    canvasWatermark(canvasWatermark),
		    directoryToSave(directoryToSave),
		    particleType(particleType),
		    ObjMass(ObjMass),
		    tagOrProbe(tagOrProbe)
	{}
};