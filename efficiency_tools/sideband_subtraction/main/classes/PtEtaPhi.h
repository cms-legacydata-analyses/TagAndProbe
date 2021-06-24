#include "PassingFailing.h"

//Holder for 3 set of histograms for each quantity
class PtEtaPhi{
private:
	const char*& resonance;
	const char*& particleName;
	const char*& canvasWatermark;
	const char*& directoryToSave;
	const char*& particleType;
	const char*& tagOrProbe;
	InvariantMass& ObjMass;

public:
	//About histograms
	const char* quantityName 		 = NULL;
	const char* xAxisName			 = NULL;
	const char* quantityUnit		 = NULL;
	const char* extendedQuantityName = NULL;

	double 	xMin = 0.;
	double	xMax = 0.;
	int 	nBins = 0;
	int 	decimals = 3;

	TEfficiency* pEff 	= NULL;

	PassingFailing Pass {resonance, particleName, canvasWatermark, directoryToSave, particleType, ObjMass, tagOrProbe,
		"Passing", quantityName, xAxisName, quantityUnit, extendedQuantityName, xMin, xMax, nBins, decimals};
	PassingFailing All  {resonance, particleName, canvasWatermark, directoryToSave, particleType, ObjMass, tagOrProbe,
		"All",     quantityName, xAxisName, quantityUnit, extendedQuantityName, xMin, xMax, nBins, decimals};

	void normalizeHistograms()
	{
		Pass.normalizeHistograms();
		All .normalizeHistograms();
	}

	void subtractSigHistograms()
	{
		Pass.subtractSigHistogram();
		All .subtractSigHistogram();
	}

	void fillQuantitiesHistograms(double& quantity, double& InvariantMass, int& isPassing)
	{
		if (isPassing)
			Pass.fillQuantitiesHistograms(quantity, InvariantMass);
		All.fillQuantitiesHistograms(quantity, InvariantMass);
	}

	void createQuantitiesCanvas(bool shouldWrite = false, bool shouldSavePNG = false)
	{
		Pass.createQuantitiesCanvas(shouldWrite, shouldSavePNG);
		All .createQuantitiesCanvas(shouldWrite, shouldSavePNG);
	}

	//Creates a efficiency plot with histograms
	TEfficiency* createEfficiencyPlot(bool shouldWrite = false)
	{
		//References
		TH1D* &hPass  = Pass.hSig;
		TH1D* &hTotal = All .hSig;

		string pName 	= string(particleName) + "_" + string(quantityName) + "_" + string(particleType) + "_" + string(tagOrProbe) + "_Efficiency";
		string pTitle 	= "Efficiency of " + string(particleType) + " " + string(particleName) + " " + string(tagOrProbe);

		//Set Y axis title for efficiency plot
		hTotal->GetYaxis()->SetTitle("Efficiency");

		//TEMPORARY?
		pEff = new TEfficiency();
		pEff->SetPassedHistogram(*hPass, "f");
		pEff->SetTotalHistogram (*hTotal,"f");
		pEff->SetName(pName.data());

		/*
		//Check if are valid and consistent histograms
		if(TEfficiency::CheckConsistency(*hPass, *hTotal))
		{
			//Fills histogram
			pEff = new TEfficiency(*hPass, *hTotal);
			pEff->SetName(pName.data());
		}
		else
		{
			//TEST FOR EVERY SINGLE BIN
			cerr << "--- Consistency error detected! Showing problematic bins of histograms ---\n";
			cerr << "Error at: " << pTitle << "\n";
			int nbinsx = hPass->GetXaxis()->GetNbins();
			cout << "Bins : " << nbinsx << "\n";
			for (int i = 0; i < nbinsx; i++)
			{
				if (hTotal->GetBinContent(i) - hPass->GetBinContent(i) < 0)
				{
					//cout << "Bin " << i << " with problems | T:" <<  hTotal->GetBinContent(i) << " - P:" << hPass->GetBinContent(i) << "\n";
					cout << "Bin " << i << " with problems | P:" <<  hPass->GetBinContent(i) << " : T:" << hTotal->GetBinContent(i) << "\n";
					cout << "-> Pass  : " << Pass.hSigBack->GetBinContent(i) << " - " << Pass.hBack->GetBinContent(i) << "a = " << Pass.hSig->GetBinContent(i) << " (a = "<< Pass.PassFailObj()->subtractionFactor() << ")\n";
					cout << "-> Total : " << All .hSigBack->GetBinContent(i) << " - " << All .hBack->GetBinContent(i) << "a = " << All .hSig->GetBinContent(i) << " (a = "<< All .PassFailObj()->subtractionFactor() << ")\n";
				}
			}
			cerr << "Consistency ERROR! Program stopped" << "\n";
			abort();
		}
		*/

		//Set plot config
		pEff->SetTitle(pTitle.data());
		pEff->SetLineWidth(2);
		pEff->SetLineColor(kBlack);
		pEff->SetMarkerStyle(21);
		pEff->SetMarkerSize(0.5);
		pEff->SetMarkerColor(kBlack);

		//Writes in file
		if (shouldWrite == true)
		{
			pEff->Write("",TObject::kOverwrite);
		}

		return pEff;
	}

	//Creates canvas for efficiency plots
	TCanvas* createEfficiencyCanvas(bool shouldWrite = false, bool shouldSavePNG = false)
	{
		string canvasName 	= string(particleName) + " " + string(tagOrProbe) + " " + string(quantityName) + " " + string(particleType) + " Efficiency" ;
		string canvasTitle 	= string(extendedQuantityName) + " Efficiency (" + string(particleType) + " " + string(tagOrProbe) + ")";
		string saveAs 		= string(directoryToSave) + string("Efficiency_") + string(particleType) + "_" + string(tagOrProbe) + "_" + string(quantityName) + ".pdf";

		//To stop crashing at graph functions after gPad->Update()
		gStyle->SetCanvasPreferGL(kFALSE);

		//Draw on canvas
		TCanvas* c1 = new TCanvas(canvasName.data(), canvasTitle.data());
		//gStyle->SetOptTitle(0);
		c1->SetMargin(0.12, 0.03, 0.11, 0.07);
		pEff->Draw();
		gPad->Update();

		//Set range in y axis
		auto graph = pEff->GetPaintedGraph(); 
		graph->SetMinimum(0.0);
		graph->SetMaximum(1.2);
		gPad->Update();
		if (strcmp(quantityName, "Phi") == 0)
		{
			graph->SetMinimum(0.5);
			graph->SetMaximum(1.1);
		}

		//Add legend
		TLegend* l = new TLegend(0.74,0.82,0.94,0.88);
		l->SetTextSize(0.04);
		l->AddEntry(pEff, "Data", "lp");
		l->Draw();

		//CMS Open Data
		TLatex* txCOD = new TLatex();
		txCOD->SetTextSize(0.04);
		txCOD->SetTextAlign(12);
		txCOD->SetTextFont(42);
		txCOD->SetNDC(kTRUE);
		txCOD->DrawLatex(0.15,0.85,Form(canvasWatermark, ""));

		//Writes in file
		if (shouldWrite == true)
		{
			c1->Write("",TObject::kOverwrite);
		}

		//If should save
		if (shouldSavePNG == true)
		{
			//Saves as image
			c1->SaveAs(saveAs.data());
		}

		return c1;
	}

	void consistencyDebugCout()
	{
		Pass.consistencyDebugCout();
		All .consistencyDebugCout();
	}

	void writeQuantitiesHistogramsOnFile(bool hSigBack, bool hSig, bool hBack)
	{
		Pass .writeQuantitiesHistogramsOnFile(hSigBack, hSig, hBack);
		All  .writeQuantitiesHistogramsOnFile(hSigBack, hSig, hBack);
	}



	PtEtaPhi(
		const char*& resonance,
		const char*& particleName,
		const char*& canvasWatermark,
		const char*& directoryToSave,
	 	const char*& particleType,
	 	InvariantMass& ObjMass,
	 	const char*& tagOrProbe,
		const char*  quantityName,
		const char*  xAxisName,
		const char*  quantityUnit,
		const char*  extendedQuantityName,
		int	    	 nBins,
		double	 	 xMin,
		double	 	 xMax,
		int	    	 decimals = 3)
		  : resonance(resonance),
		    particleName(particleName),
		    canvasWatermark(canvasWatermark),
		    directoryToSave(directoryToSave),
		    particleType(particleType),
		    ObjMass(ObjMass),
		    tagOrProbe(tagOrProbe),
			quantityName(quantityName),
			xAxisName(xAxisName),
			quantityUnit(quantityUnit),
			extendedQuantityName(extendedQuantityName),
			nBins(nBins),
			xMin(xMin),
			xMax(xMax),
			decimals(decimals)
	{}
};