#include "TMath.h"

//-------------------------------------
// Fit functions for Invariant Mass
//-------------------------------------

class FitFunctions
{
public:
	class Primary
	{
	public:
		//Gaussian function
		static Double_t Gaus(Double_t *x, Double_t *par)
		{
			//par[0] = height
			//par[1] = position
			//par[2] = sigma
			Double_t gaus = par[0]*TMath::Gaus(x[0],par[1],par[2],1);
			return gaus;
		}

		//Polynomial function
		static Double_t Pol1(Double_t *x, Double_t *par)
		{
			//par[0] = b
			//par[1] = a
			Double_t pol = par[0] + par[1]*x[0];
			return pol;
		}

		static Double_t Pol3(Double_t *x, Double_t *par)
		{
			//par[0] = b
			//par[1] = a
			//par[2] = c
			//par[3] = d
			Double_t pol = par[0] + par[1]*x[0] + par[2]*x[0]*x[0] + par[3]*x[0]*x[0]*x[0];
			return pol;
		}

		//Exponential function
		static Double_t Exp(Double_t *x, Double_t *par)
		{
			//par[0] = height
			//par[1] = width
			Double_t exp = par[0] * TMath::Exp(par[1]*x[0]);
			return exp;
		}

		//Crystall ball function
		static Double_t CrystalBall(Double_t *x,Double_t *par)
		{
			//par[0] = alpha
			//par[1] = n
			//par[2] = mean
			//par[3] = sigma
			//par[4] = yield
			Double_t t = (x[0]-par[2])/par[3];
			if (par[0] < 0) t = -t;
			Double_t absAlpha = fabs((Double_t)par[0]);
			if (t >= -absAlpha)
			{
				return par[4]*exp(-0.5*t*t);
			}
			else
			{
				Double_t a =  TMath::Power(par[1]/absAlpha,par[1])*exp(-0.5*absAlpha*absAlpha);
				Double_t b = par[1]/absAlpha - absAlpha;
				return par[4]*(a/TMath::Power(b - t, par[1]));
			}
		}
	};
	class Jpsi
	{
	public:
		//Fit function for signal of Invariant Mass
		static Double_t Signal_InvariantMass(Double_t *x, Double_t *par) {
			return FitFunctions::Primary::Gaus(x,par) + FitFunctions::Primary::CrystalBall(x, &par[3]);
		}

		//Fit function for background of Invariant Mass
		static Double_t Background_InvariantMass(Double_t *x, Double_t *par) {
			return FitFunctions::Primary::Exp(x,par);
		}

		//Fit function for signal & background of Invariant Mass
		static Double_t InvariantMass(Double_t *x, Double_t *par) {
			return Signal_InvariantMass(x,par) + Background_InvariantMass(x, &par[8]);
		}
	};
	class Upsilon
	{
	public:
		//Fit function for signal of Invariant Mass
		static Double_t Signal_InvariantMass(Double_t *x, Double_t *par) {
			return FitFunctions::Primary::CrystalBall(x,par) + FitFunctions::Primary::Gaus(x, &par[5]) + FitFunctions::Primary::Gaus(x, &par[8]);
		}

		//Fit function for background of Invariant Mass
		static Double_t Background_InvariantMass(Double_t *x, Double_t *par) {
			return FitFunctions::Primary::Pol3(x, par);
		}

		//Fit function for signal & background of Invariant Mass
		static Double_t InvariantMass(Double_t *x, Double_t *par) {
			return Signal_InvariantMass(x,par) + Background_InvariantMass(x, &par[11]);
		}
	};
};