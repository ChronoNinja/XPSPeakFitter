/*
*
*
*/

#include <fstream>
#include <string>
#include <iostream>

#include "TGraph.h"
#include "TGraphErrors.h"
#include "TF1.h"
#include "TMath.h"
#include "TMultiGraph.h"
#include "TAxis.h"

int XPSFitter2() {

	gROOT->SetStyle("BABAR");
	
	ifstream OpenDataSet("OxygenRegion.txt");
	if (!OpenDataSet.is_open()) {
		return -1;
	}
	int NumLines = 0;
	string ReadLine;
	
	while (OpenDataSet.good()) {
		getline(OpenDataSet,ReadLine);
		NumLines++;
//		cout << ReadLine << endl;
	}
	
	OpenDataSet.close();
	OpenDataSet.open("OxygenRegion.txt");
	
	const int ArraySize = NumLines;
	
	double Xdat[ArraySize];
	double Ydat[ArraySize];
	double EXdat[ArraySize];
	double EYdat[ArraySize];

	double HoldVal;
	int CountingData = 0;
	int NumValsCounted = 0;
	
	for (int i = 0; i < ArraySize; ++i) {
		if (CountingData == 0) {
			OpenDataSet >> Xdat[NumValsCounted];
			OpenDataSet >> Ydat[NumValsCounted];
			EXdat[NumValsCounted] = 0;
			EYdat[NumValsCounted] = TMath::Sqrt(Ydat[NumValsCounted]);
			cout << Xdat[NumValsCounted] << "\t" << Ydat[NumValsCounted] << endl;
			NumValsCounted++;
			CountingData++;
		}
		else {
			OpenDataSet >> HoldVal;
			OpenDataSet >> HoldVal;
			CountingData++;
		}
		if (CountingData == 4) {
			CountingData = 0;
		}
	}
	
	cout << NumValsCounted << endl;
	
	double low = 530.0;
	double high = 540.0;
	
	TF1 *myFit = new TF1("myFit","[0]+[1]*x+[2]*TMath::Exp(-1.0*(x-[3])*(x-[3])/(2*[4]*[4]))+[5]*TMath::Exp(-1.0*(x-[6])*(x-[6])/(2*[4]*[4]))",low,high);
	myFit->SetParameter(0,-800000);
	myFit->SetParameter(1,1750);
	myFit->SetParameter(2,123000);
	myFit->SetParameter(3,534);
	myFit->SetParameter(4,0.7);
	myFit->SetParameter(5,12000);
	myFit->SetParameter(6,536);
	myFit->SetParameter(4,0.7);

	myFit->SetLineColor(kRed);
	
	TGraph *myG = new TGraph(NumValsCounted,Xdat,Ydat);
	myG->SetName("myG");
	TGraph *myGE = new TGraphErrors(NumValsCounted,Xdat,Ydat,EXdat,EYdat);
	
	//myG->Draw("ap");
	
	myGE->Fit(myFit,"NR");
	
	cout << myFit->GetChisquare() / myFit->GetNDF() << endl;
	TGraph *myG2 = new TGraph(); // bkg
	myG2->SetName("myG2");
	double param0 = myFit->GetParameter(0);
	double param1 = myFit->GetParameter(1);
	
	TGraph *myG3 = new TGraph(); // Peak 1
	myG3->SetName("myG3");
	double param2 = myFit->GetParameter(2);
	double param3 = myFit->GetParameter(3);
	double param4 = myFit->GetParameter(4);
	
	TGraph *myG4 = new TGraph(); // Peak 2
	myG4->SetName("myG4");
	double param5 = myFit->GetParameter(5);
	double param6 = myFit->GetParameter(6);
	double param7 = myFit->GetParameter(4);
	
	TF1 *bkg = new TF1("bkg","[0]+[1]*x",low,high);
	bkg->SetParameters(param0,param1);
	
	TF1 *peak1 = new TF1("peak1","[0]*TMath::Exp(-1.0*(x-[1])*(x-[1])/(2*[2]*[2]))",low,high);
	peak1->SetParameters(param2,param3,param4);
	
	TF1 *peak2 = new TF1("peak2","[0]*TMath::Exp(-1.0*(x-[1])*(x-[1])/(2*[2]*[2]))",low,high);
	peak2->SetParameters(param5,param6,param7);
	
	for (int i = 0; i < NumValsCounted; ++i) {
	if (Xdat[i] > low && Xdat[i] < high) {
		myG2->SetPoint(i,Xdat[i],bkg->Eval(Xdat[i]));
		myG3->SetPoint(i,Xdat[i],peak1->Eval(Xdat[i]));
		myG4->SetPoint(i,Xdat[i],peak2->Eval(Xdat[i]));
		}
	}
	
	TMultiGraph *AllG = new TMultiGraph("AllG","All Plots");
	AllG->SetName("AllG");
	AllG->Add(myGE);
	AllG->Add(myG3);
	AllG->Add(myG4);
	AllG->Draw("aplE");
	AllG->GetXaxis()->SetRangeUser(low,high);
	c1->Update();
//	myFit->Draw("same");
	
}