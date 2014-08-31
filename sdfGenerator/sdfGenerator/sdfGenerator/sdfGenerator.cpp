// sdfGenerator.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <fstream>
#include <vector>
#include <array>
#include <iostream>
#include <process.h>

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
		string cameraCmd = "define camera eye 65.0 0 0 " + to_string(i) + " 0 0 -1 0 1 0";
		string outputImg = "render eye " + outputImage[i] + " 600 600";
		fOut << "define material red 1 0 0 1 0 0 1 0 0 1" << endl
			<< "define material blue 0 0 1 0 0 1 0 0 1 1" << endl
			<< "define shape box floor   -400 -400 0  400 -410 -8000 blue" << endl
			<< "define shape box ceiling -400  400 0  400  410 -8000 blue" << endl
			<< "define shape box left    -400 -400 0 -410  400 -8000 blue" << endl
			<< "define shape box right    400 -400 0  410  410 -8000 blue" << endl
			<< "define shape sphere sphere 0 0 -200 30 red" << endl
			<< "define shape composite root left right floor ceiling sphere" << endl
			<< "define light ambient amb 0.5 0.5 0.5" << endl
			<< cameraCmd << endl << outputImg << endl;
		fOut.close();

	}


	puts("Doing something");

	for (int i = 141; i < 143; i++)
	{
		char buffer[50];
		sprintf_s(buffer, "file%d.txt", i);
		_spawnl(P_WAIT, "raytracer.exe", "gridscene.sdf", buffer, "Arg2", NULL); //renders each file seperately, must close the generated image by hand
		//_spawnl(P_NOWAIT, "raytracer.exe", "gridscene.sdf", buffer, "Arg2", NULL); renders every file at the same time
	}

	return 0;
}

