#include <iostream>
#include <cmath>
#include "MC_VanillaOptions_Functions.h"

using namespace std;
enum oType { call, put, dcall, dput };
oType opt;

 void getOptionType(string optType){

	if (optType == "call"){
		opt = call;
	}
	else if (optType == "put") {
		opt = put;
	}
	else if (optType == "dcall") {
		opt = dcall;
	}
	else { opt = dput;	}
}
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

	case dcall:
		payoff = price > K ? 1: 0;
		return payoff;
		break;

	case dput:
		payoff = price < K ? 1: 0;
		return payoff;
		break;

	default:
		cout << "Invalid option type";
	}

		
}

double vanillaOptionVal(double* S, double* K, double* r, double* div, double* vol, double* T, double* nSim, double* d_payoff, string optType)
{
	double normRand;

	double price=0;
	double iPrice=0;
	double payoff = 0;

	for (int i = 0; i < *nSim; i++)
	{
		normRand = genRandomNorm();
		iPrice = *S*exp((*r-*div-0.5* *vol* *vol)* *T+ *vol*normRand* sqrt(*T));
		//oType opt = optType == "call" ? call : put;
		getOptionType(optType);
		payoff = payoffOption(iPrice, *K, opt);
		price += payoff;
	}
	if (optType == "dcall" or optType == "dput") {
		price = price * *d_payoff;
	}

	price = price / *nSim;
	price = price * exp(-*r * *T);

	return price;
}

int main()
{
	double S, K, r, vol, T, nSim, div, d_payoff;
	string optType;

	cout << "What type of option do you want to price? (call, put, dcall, dput): ";
	cin >> optType;
	if (optType == "dcall" or optType == "dput")
	{
		cout << "For the digital option, what is the payoff if option expires In-The-Money?";
		cin >> d_payoff;
	}
	else {
		d_payoff = 0.0;
	}
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

	double price = vanillaOptionVal(&S, &K, &r,&div, &vol, &T, &nSim, &d_payoff, optType);
	cout << "Monte Carlo Price of "<<optType<< " option is " << price;

	return 0;
}