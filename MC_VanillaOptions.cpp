#include <iostream>
#include <cmath>
#include "MC_VanillaOptions_Functions.h"

using namespace std;
enum oType { call, put };

double payoffOption(double price, double K, oType opt)
{
	double payoff = 0;
	switch (opt) {
	case call: 
		payoff = price > K ? price-K : 0;
		return payoff;
		break;
	
	case put:
		payoff = price < K ? K - price : 0;
		return payoff; 
		break;
	}
}

double vanillaOptionVal(double S, double K, double r, double div, double vol, double T, double nSim, string optType)
{
	double normRand;

	double price=0;
	double iPrice=0;
	double payoff = 0;

	for (int i = 0; i < nSim; i++)
	{
		normRand = genRandomNorm();
		iPrice = S*exp((r-div-0.5*vol*vol)*T+vol*normRand*sqrt(T));
		oType opt = optType == "call" ? call : put;
		payoff = payoffOption(iPrice, K, opt);
		price += payoff;
	}

	price = price / nSim;
	price = price * exp(-r * T);

	return price;
}

int main()
{
	double S, K, r, vol, T, nSim, div;
	string optType;

	cout << "What type of option do you want to price? (call, put): ";
	cin >> optType;
	cout << "Enter Strike: ";
	cin >> K;
	cout << "Enter Current Stock Price:";
	cin >> S;
	cout << "Enter risk-free rate (in %): ";
	cin >> r;
	r = r / 100;
	cout << "Enter dividend yield (in %): ";
	cin >> div;
	div = div / 100;
	cout << "Enter volatility (in %): ";
	cin >> vol;
	vol = vol / 100;
	cout << "Enter maturity of option (in years):";
	cin >> T;
	cout << "Enter the number of MC simulations to be performed:";
	cin >> nSim;

	double price = vanillaOptionVal(S, K, r,div, vol, T, nSim, optType);
	cout << "Monte Carlo Price of "<<optType<< "Option is " << price;

	return 0;
}