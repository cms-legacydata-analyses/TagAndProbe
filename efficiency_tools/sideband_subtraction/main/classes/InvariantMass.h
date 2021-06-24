#include "TH1.h"
#include "TF1.h"
#include "TCanvas.h"
#include "TStyle.h"
#include "TFitResult.h"
#include "TLegend.h"
#include "TLatex.h"
#include "TFrame.h"

#include <iostream>

using namespace std;

#include "FitFunctions.h"
#include "MassValues.h"

class InvariantMass{
private:
	const char*& resonance;
	const char*& particleName;
	const char*& canvasWatermark;
	const char*& directoryToSave;
	const char*& particleType;

	void createMassHistogram(TH1D* &hMass, const char* passingOrFailing)
	{
		string hName 			= string(passingOrFailing) + "_" + string(particleType) + "_" + string(particleName) + "_InvariantMass";
		string hTitle 			= "Invariant Mass (" + string(passingOrFailing) + " for " + string(particleType) + ")";
		string yAxisTitleForm 	= "Events / (%1." + to_string(decimals) + "f GeV/c^{2})";

		//Change hTitle name
		if (strcmp(passingOrFailing, "Passing") == 0)
			hTitle = "Invariant Mass (" + string(particleType) + ")";

		if (strcmp(passingOrFailing, "Failing") == 0)
			hTitle = "Invariant Mass (non-" + string(particleType) + ")";

		if (strcmp(passingOrFailing, "All") == 0)
			hTitle = "Invariant Mass (All)";


		//Create histogram
		hMass = new TH1D(hName.data(), hTitle.data(), nBins, xMin, xMax);
		hMass->GetYaxis()->SetTitle(Form(yAxisTitleForm.data(), hMass->GetBinWidth(0)));
		hMass->GetXaxis()->SetTitle("#mu^{+}#mu^{-} invariant mass [GeV/c^{2}]");
	}

	void drawCanvasQuarter(TCanvas* &canvas, bool drawRegions, int quarter, MassValues* ObjMassValues, int color = kBlue)
	{
		TH1D* &hMass = ObjMassValues->hMass;
		TF1*  &fFit  = ObjMassValues->fitFunction;

		canvas->cd(quarter);
		canvas->cd(quarter)->SetMargin(0.14, 0.02, 0.09, 0.07);

		if (strcmp(resonance, "Upsilon") == 0)
		{
			hMass->SetMinimum(0.);
			hMass->SetMaximum(1.2*hMass->GetBinContent(hMass->GetMaximumBin()));
		}

		hMass->SetMarkerStyle(20);		//Set markers style
		hMass->SetMarkerColor(kBlack);	//Set markers colors
		hMass->SetLineColor(kBlack);	//Set errobars color
		hMass->Draw("ep");

		//Add legend
		TLegend* tl = new TLegend(0.70,0.86,0.96,0.92);
		tl->SetTextSize(0.04);
		tl->AddEntry(hMass, "Data", "lp");

		//Draw fit
		if (fFit != NULL)
		{
			//Change the size of TLegend
			tl->SetY1(tl->GetY1() - tl->GetTextSize()*1);

			fFit->SetNpx(1000);
			fFit->SetLineColor(color);
			fFit->SetLineStyle(kSolid);
			fFit->Draw("same");
			tl->AddEntry(fFit, "Total Fit", "l");

			//If is showing pass and fail fit
			if (strcmp(resonance, "Jpsi") == 0)
			{
				const char* const fittingParName[] = {
						"Gaus(Sg) Height  ",
						"Gaus(Sg) Position",
						"Gaus(Sg) Sigma   ",

						"CB  (Sg) Alpha   ",
						"CB  (Sg) N       ",
						"CB  (Sg) Mean    ",
						"CB  (Sg) Sigma   ",
						"CB  (Sg) Yield   ",

						"Exp1(Bg) Height  ",
						"Exp1(Bg) Width   ",
						"Exp2(Bg) Height  ",
						"Exp2(Bg) Width   "
					};

				//Change the size of TLegend
				tl->SetY1(tl->GetY1() - tl->GetTextSize()*3);

				//Get parameters of fit
				int arraySize = sizeof(fittingParName)/sizeof(*fittingParName);
				double fitParameters[arraySize];
				fFit->GetParameters(fitParameters);

				//Signal Gaus Fitting
				TF1* fitGaus = new TF1("FitFunction_Gaussian", FitFunctions::Primary::Gaus, xMin, xMax, 3);
				fitGaus->SetNpx(1000);						//Resolution of signal fit function
				fitGaus->SetParameters(fitParameters);		//Get only signal part
				fitGaus->SetLineColor(kMagenta); 			//Fit Color
				fitGaus->SetLineStyle(kDashed);				//Fit Style
				fitGaus->SetLineWidth(3);					//Fit width
				fitGaus->Draw("same");
				for (int i = 0; i < arraySize; i++)
					fitGaus->SetParName(i, fittingParName[i]);
				tl->AddEntry(fitGaus, "Gaussian",    "l");
				
				//Signal CB Fitting
				TF1* fitCB = new TF1("FitFunction_CrystalBall", FitFunctions::Primary::CrystalBall, xMin, xMax, 5);
				fitCB->SetNpx(1000);						//Resolution of signal fit function
				fitCB->SetParameters(&fitParameters[3]);	//Get only signal part
				fitCB->SetLineColor(kOrange); 				//Fit Color
				fitCB->SetLineStyle(kDotted);				//Fit Style
				fitCB->SetLineWidth(3);						//Fit width
				fitCB->Draw("same");
				for (int i = 0; i < arraySize; i++)
					fitCB->SetParName(i, fittingParName[i+3]);
				tl->AddEntry(fitCB,	 "Crystal Ball", "l");

				//Background Fitting
				TF1* fitExp = new TF1("FitFunction_Background", FitFunctions::Jpsi::Background_InvariantMass, xMin, xMax, 2);
				fitExp->SetNpx(1000);						//Resolution of background fit function
				fitExp->SetParameters(&fitParameters[8]);	//Get only background part
				fitExp->SetLineColor(kBlue); 				//Fit Color
				fitExp->SetLineStyle(kDashDotted);			//Fit style
				fitExp->SetLineWidth(3);					//Fit width
				fitExp->Draw("same");
				for (int i = 0; i < arraySize; i++)
					fitExp->SetParName(i, fittingParName[i+8]);
				tl->AddEntry(fitExp, "Exponential",	 "l");
			}

			//If is showing pass and fail fit
			if (strcmp(resonance, "Upsilon") == 0)
			{
				const char* const fittingParName[] = {
						"CB  (1S) Alpha   ",
						"CB  (1S) N       ",
						"CB  (1S) Mean    ",
						"CB  (1S) Sigma   ",
						"CB  (1S) Yield   ",

						"Gaus(2S) Height  ",
						"Gaus(2S) Position",
						"Gaus(2S) Sigma   ",

						"Gaus(3S) Height  ",
						"Gaus(3S) Position",
						"Gaus(3S) Sigma   ",

						"Pol3(Bg) Height  ",
						"Pol3(Bg) Width   ",
						"Pol3(Bg) Height  ",
						"Pol3(Bg) Width   "
					};

				//Change the size of TLegend
				tl->SetY1(tl->GetY1() - tl->GetTextSize()*4);

				//Get parameters of fit
				int arraySize = sizeof(fittingParName)/sizeof(*fittingParName);
				double fitParameters[arraySize];
				fFit->GetParameters(fitParameters);
				
				//Signal CB Fitting
				TF1* fitCB1 = new TF1("FitFunction_CrystalBall", FitFunctions::Primary::CrystalBall, xMin, xMax, 5);
				fitCB1->SetNpx(1000);
				fitCB1->SetParameters(fitParameters);
				fitCB1->SetLineColor(kMagenta);
				fitCB1->SetLineStyle(kDotted);
				fitCB1->SetLineWidth(3);
				fitCB1->Draw("same");
				for (int i = 0; i < arraySize; i++)
					fitCB1->SetParName(i, fittingParName[i]);
				tl->AddEntry(fitCB1, "Crystal Ball", "l");

				//Signal Gaus Fitting
				TF1* fitGaus2 = new TF1("FitFunction_Gaussian", FitFunctions::Primary::Gaus, xMin, xMax, 3);
				fitGaus2->SetNpx(1000);
				fitGaus2->SetParameters(&fitParameters[5]);
				fitGaus2->SetLineColor(kOrange);
				fitGaus2->SetLineStyle(kDashed);
				fitGaus2->SetLineWidth(3);
				fitGaus2->Draw("same");
				for (int i = 0; i < arraySize; i++)
					fitGaus2->SetParName(i, fittingParName[i+5]);
				tl->AddEntry(fitGaus2, "Gauss (2S)", "l");

				//Signal Gaus Fitting
				TF1* fitGaus3 = new TF1("FitFunction_Gaussian", FitFunctions::Primary::Gaus, xMin, xMax, 3);
				fitGaus3->SetNpx(1000);
				fitGaus3->SetParameters(&fitParameters[8]);
				fitGaus3->SetLineColor(kMagenta - 5);
				fitGaus3->SetLineStyle(kDashed);
				fitGaus3->SetLineWidth(3);
				fitGaus3->Draw("same");
				for (int i = 0; i < arraySize; i++)
					fitGaus3->SetParName(i, fittingParName[i+8]);
				tl->AddEntry(fitGaus3, "Gauss (3S)", "l");

				//Background Fitting
				TF1* fitPol = new TF1("FitFunction_Background", FitFunctions::Upsilon::Background_InvariantMass, xMin, xMax, 4);
				fitPol->SetNpx(1000);
				fitPol->SetParameters(&fitParameters[11]);
				fitPol->SetLineColor(kBlue);
				fitPol->SetLineStyle(kDashDotted);
				fitPol->SetLineWidth(3);
				fitPol->Draw("same");
				for (int i = 0; i < arraySize; i++)
					fitPol->SetParName(i, fittingParName[i+11]);
				tl->AddEntry(fitPol, "Pol 3", "l");
			}
		}

		//Draw regions
		if (drawRegions == true)
		{
			//Change the size of TLegend
			tl->SetY1(tl->GetY1() - tl->GetTextSize()*2);

			//Get Y range of draw
			gPad->Update();
			double Ymax = gPad->GetFrame()->GetY2();
			double Ymin = gPad->GetFrame()->GetY1();

			//Draw regions
			TBox* side1  = ObjMassValues->createTBox(Ymax, -1, Ymin);
			side1->SetFillColorAlpha(kRed, 0.35);
			side1->Draw();
			TBox* signal = ObjMassValues->createTBox(Ymax, 0,  Ymin);
			signal->SetFillColorAlpha(kGreen, 0.35);
			signal->Draw();
			TBox* side2  = ObjMassValues->createTBox(Ymax, 1,  Ymin);
			side2->SetFillColorAlpha(kRed, 0.35);
			side2->Draw();

			//Add on TLegend
			tl->AddEntry(signal, "Signal R.",   "f");
			tl->AddEntry(side1,  "Sideband R.", "f");
		}

		//Draws information
		TLatex* tx = new TLatex();
		tx->SetTextSize(0.04);
		tx->SetTextAlign(12);
		tx->SetTextFont(42);
		tx->SetNDC(kTRUE);
		tx->DrawLatex(0.16,0.88,Form(canvasWatermark, ""));

		//Draws TLegend
		tl->Draw();
	}

public:
	MassValues Pass;
	MassValues All;

	double 	xMin;
	double	xMax;
	int 	nBins;
	int 	decimals = 3;

	void defineMassHistogramNumbers(double xMin, double xMax, int nBins, int decimals = 3)
	{
		this->xMin     = xMin;
		this->xMax     = xMax;
		this->nBins    = nBins;
		this->decimals = decimals;

		delete Pass.hMass;
		delete All. hMass;

		createMassHistogram(Pass.hMass, "Passing");
		createMassHistogram(All. hMass, "All");
	}

	void fillMassHistograms(double& InvariantMass, int& isPassing)
	{
		if (isPassing)
			Pass.hMass->Fill(InvariantMass);
		All.hMass->Fill(InvariantMass);
	}

	void doFit()
	{
		if (strcmp(resonance, "Jpsi") == 0)
		{
			cout << "\nFitting Passing in " << particleType << " " << particleName << "...\n";
			Pass.doFitJpsi();

			cout << "\nFitting All in " << particleType << " " << particleName << "...\n";
			All.doFitJpsi();
		}

		if (strcmp(resonance, "Upsilon") == 0)
		{
			cout << "\nFitting Passing in " << particleType << " " << particleName << "...\n";
			Pass.doFitUpsilon();

			cout << "\nFitting All in " << particleType << " " << particleName << "...\n";
			All.doFitUpsilon();
		}

		if (strcmp(resonance, "Upsilon1S") == 0)
		{
			cout << "\nFitting Passing in " << particleType << " " << particleName << "...\n";
			Pass.doFitUpsilon1S();

			cout << "\nFitting All in " << particleType << " " << particleName << "...\n";
			All.doFitUpsilon1S();
		}
	}

	void updateMassValuesFor(MassValues* ObjMassValues, bool isAll = false)
	{
		double value = 0.;
		double fwhm  = 0.;

		int method = 1; //Default
		// 1 -> estimate signal region by FWHM using histograms
		// 2 -> estimate signal region by FWHM using fitting

		//Default: method == 1
		{
			//Get value and uncertain of signal by histogram
			TH1D* &hMass = ObjMassValues->hMass; 
			int bin0 = hMass->GetMaximumBin();
			value    = hMass->GetBinCenter(bin0);
			int bin1 = hMass->FindFirstBinAbove(hMass->GetMaximum()/2);
			int bin2 = hMass->FindLastBinAbove(hMass->GetMaximum()/2);

			//If is Upsilon, consider finding the ain peak only
			if (strcmp(resonance, "Upsilon") == 0)
				bin2 = hMass->FindLastBinAbove(hMass->GetMaximum()/2, 1, 1, hMass->GetXaxis()->FindBin(9.75));

			fwhm     = hMass->GetBinCenter(bin2) - hMass->GetBinCenter(bin1);
		}

		double sigma = fwhm/2.355;

		if (strcmp(resonance, "Jpsi") == 0 || strcmp(resonance, "Upsilon1S") == 0)
		{
			//Signal region = mass +- 3*sigma
			ObjMassValues->signalRegion_x1 = value - 3*sigma;
			ObjMassValues->signalRegion_x2 = value + 3*sigma;

			//Sideband regions
			ObjMassValues->sidebandRegion1_x1 = value - 7*sigma;
			ObjMassValues->sidebandRegion1_x2 = value - 4*sigma;
			ObjMassValues->sidebandRegion2_x1 = value + 4*sigma;
			ObjMassValues->sidebandRegion2_x2 = value + 7*sigma;
		}

		if (strcmp(resonance, "Upsilon") == 0)
		{
			//Signal region = mass +- 3*sigma
			ObjMassValues->signalRegion_x1 = value - 3*sigma;
			ObjMassValues->signalRegion_x2 = value + 3*sigma;

			ObjMassValues->sidebandRegion1_x1  = xMin;
			ObjMassValues->sidebandRegion1_x2  = value - 4*sigma;
			ObjMassValues->sidebandRegion2_x1  = 10.6;
			ObjMassValues->sidebandRegion2_x2  = xMax;
		}
	}

	void updateMassValuesAll()
	{
		updateMassValuesFor(&Pass);
		updateMassValuesFor(&All);
	}

	TCanvas* createMassCanvas(bool drawRegions = false, bool shouldWrite = false, bool shouldSavePNG = false)
	{
		string canvasName 	= "InvariantMass_" + string(particleType);
		string canvasTitle	= "Invariant Mass " + string(particleType);
		string saveAs 		= string(directoryToSave) + "InvariantMass_" + string(particleType) + ".pdf";

		if (drawRegions)
		{
			canvasName 	= "InvariantMass_" + string(particleType) + "_region";
			canvasTitle	= "Invariant Mass " + string(particleType) + " with Regions";
			saveAs 		= string(directoryToSave) + "InvariantMass_" + string(particleType) + "_region" + ".pdf";
		}

		//Create canvas
		gStyle->SetCanvasPreferGL(kTRUE);
		TCanvas* c1 = new TCanvas(canvasName.data(), canvasTitle.data(), 1200, 600);
		c1->Divide(2,1);

		drawCanvasQuarter(c1, drawRegions, 1, &Pass, kGreen);
		drawCanvasQuarter(c1, drawRegions, 2, &All,  kBlue);

		c1->cd(2);

		//Draws information
		TLatex* tx = new TLatex();
		//tx->SetTextSize(0.04);
		tx->SetTextAlign(12);
		tx->SetTextFont(42);
		tx->SetNDC(kTRUE);
		//tx->DrawLatex(0.61,0.60,Form("#chi^{2}/ndf = %.3g",(fitResult).Chi2()/(fitResult).Ndf()));

		//Not show frame with mean, std dev
		gStyle->SetOptStat(0);

		//Writes in file
		if (shouldWrite == true)
		{
			c1->Write();
		}

		//If should save
		if (shouldSavePNG == true)
		{
			//Saves as image
			c1->SaveAs(saveAs.data());
		}

		return c1;
	}

	void writeMassHistogramsOnFile(bool writehPass, bool writehAll)
	{
		Pass.hMass->Write();
		All .hMass->Write();
	}
	


	InvariantMass(
		const char*& resonance,
		const char*& particleName,
		const char*& canvasWatermark,
		const char*& directoryToSave,
	 	const char*& particleType)
		  : resonance(resonance),
		    particleName(particleName),
		    canvasWatermark(canvasWatermark),
		    directoryToSave(directoryToSave),
		    particleType(particleType)
	{
		if (strcmp(resonance, "Jpsi") == 0)
		{
			xMin  = 2.9;
			xMax  = 3.3;
			nBins = 160;
		}

		if (strcmp(resonance, "Upsilon") == 0)
		{
			xMin  = 8.7;
			xMax  = 11.;
			nBins = 60;
		}

		if (strcmp(resonance, "Upsilon1S") == 0)
		{
			xMin  = 8.7;
			xMax  = 11.;
			nBins = 60;
		}

		createMassHistogram(Pass.hMass, "Passing");
		createMassHistogram(All. hMass, "All");
	}
};