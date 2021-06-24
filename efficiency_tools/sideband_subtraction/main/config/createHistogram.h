/*
What is this file: This file is called in PassingFailing.cpp
What does it do:   It set quantity histograms bins and create the hitogram
*/

void createHistogram(TH1D* &histo, const char* histoName)
{
	//Set parameters
	string hName 		  = string(particleType) + string(passingOrFailing) + string(tagOrProbe) + string(particleName) + "_" + string(quantityName) + string(histoName);
	string hTitle 		  = string(passingOrFailing) + " in " + string(particleType) + " " + string(tagOrProbe);
	string xAxisTitle 	  = string(xAxisName);
	string yAxisTitleForm = "Events";

	//Add unit if has
	if (strcmp(quantityUnit, "") != 0)
		xAxisTitle += " [" + string(quantityUnit) + "]";

	//Change title is passing
	if (strcmp(passingOrFailing, "Passing") == 0)
		hTitle = string(particleType) + " " + string(particleName) + " " + string(tagOrProbe);

	if (strcmp(passingOrFailing, "All") == 0)
		hTitle = "All " + string(particleName) + " " + string(tagOrProbe);


	//Variable bin for pT
	if (strcmp(quantityName, "Pt") == 0)
	{
		double xbins[] = {0., 2.0, 3.4, 4.0, 4.4, 4.7, 5.0, 5.6, 5.8, 6.0, 6.2, 6.4, 6.6, 6.8, 7.3, 9.5, 13.0, 17.0, 40.};
		
		int nbins = sizeof(xbins)/sizeof(*xbins) - 1;
		histo = new TH1D(hName.data(), hTitle.data(), nbins, xbins);
	}

	//Variable bin for eta
	else if (strcmp(quantityName, "Eta") == 0)
	{
		double xbins[] = {-2.4, -1.8, -1.4, -1.2, -1.0, -0.8, -0.5, -0.2, 0, 0.2, 0.5, 0.8, 1.0, 1.2, 1.4, 1.8, 2.4};
		
		int nbins = sizeof(xbins)/sizeof(*xbins) - 1;
		histo = new TH1D(hName.data(), hTitle.data(), nbins, xbins);
	}

	//Bins for phi 
	else
	{
		double xbins[] = {-3.0, -1.8, -1.6, -1.2, -1.0, -0.7, -0.4, -0.2, 0, 0.2, 0.4, 0.7, 1.0, 1.2, 1.6, 1.8, 3.0};
		
		int nbins = sizeof(xbins)/sizeof(*xbins) - 1;
		histo = new TH1D(hName.data(), hTitle.data(), nbins, xbins);
	}

	//Edit histogram axis
	histo->GetYaxis()->SetTitle(Form(yAxisTitleForm.data(), histo->GetBinWidth(0)));
	histo->GetXaxis()->SetTitle(xAxisTitle.data());
}