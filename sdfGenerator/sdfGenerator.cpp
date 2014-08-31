// sdfGenerator.cpp : Defines the entry point for the console application.
//

#include <string>
#include <fstream>
#include <vector>
#include <array>
#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {
	const int imagecount = 120;
	array<string, imagecount> outputNames;

	for (int  i = 0; i < imagecount; ++i) {
		outputNames[i] = "file" + to_string(i) + ".sdf";
		
		cout << outputNames[i] << endl;
	}


	array <string, imagecount> outputImage;

	for (int i = 0; i <imagecount; ++i){
		outputImage[i] = "picture" + to_string(i) + ".ppm";
	}

	for (int i = 0; i < imagecount; ++i){
		double yAxis = i*0.1;
		ofstream fOut("output/"+outputNames[i]);
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

	return 0;
}

