// sdfGenerator.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <fstream>
#include <vector>
#include <array>
#include <iostream>

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	array<string, 101> outputNames;

	for (int  i = 1; i <= 100; i++)
	{
		outputNames[i] = "file" + to_string(i + 140) + ".txt";
		
		cout << outputNames[i] << endl;
	}


	array <string, 141> outputImage;

	for (int i = 1; i <=140; i++)
	{
		outputImage[i] = "picture1" + to_string(i + 140) + ".ppm";
	}

	for (int i = 1; i <= 100; i++)
	{
		double yAxis = i*0.1;
		ofstream fOut(outputNames[i]);
		string cameraCmd = "define camera eye 45.0 0 0 " + to_string(i) + " 0 0 -1 0 1 0";
		string outputImg = "render eye " + outputImage[i] + " 600 600";
		fOut << "define material red 1 0 0 1 0 0 1 0 0 1" << endl
			<< "define material blue 0 0 1 0 0 1 0 0 1 1" << endl
			<< "define shape box rbottom 0.0 -7.5 -10.5 2.0 5.0 -6.0 blue" << endl
			<< "define shape sphere bsphere 0 -6.900000 -10.0 2.0 red" << endl
			<< "define light diffuse spot1 -500 800 0 0.8 0.8 0.8" << endl
			<< cameraCmd << endl << outputImg << endl;
		fOut.close();

	}

	return 0;
}

