/*
*
*
*/

#include <fstream>
#include <string>
#include <iostream>

#include "TGraph.h"

int XPSFitter() {

	ifstream OpenDataSet("../DataFiles/InitialDataSet/UO2_O1s_Post.txt");
	if (!OpenDataSet.is_open()) {
		return -1;
	}
	int NumLines = 0;
	string ReadLine;
	
	while (OpenDataSet.good()) {
		getline(OpenDataSet,ReadLine);
		NumLines++;
		cout << ReadLine << endl;
	}
	
	OpenDataSet.close();
	OpenDataSet.open("../DataFiles/InitialDataSet/UO2_O1s_Post.txt");
	
	double Xdat[NumLines];
	double Ydat[NumLines];
	
	for (int i = 0; i < NumLines; ++i) {
		OpenDataSet >> Xdat[i];
		OpenDataSet >> Ydat[i];
	}
	
	TGraph *myG = new TGraph(NumLines-1,Xdat,Ydat);
	myG->SetName("myG");
	myG->Draw("apl");
	
}