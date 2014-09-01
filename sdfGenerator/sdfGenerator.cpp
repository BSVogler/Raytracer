// sdfGenerator.cpp : Defines the entry point for the console application.
//

#include <string>
#include <fstream>
#include <vector>
#include <array>
#include <iostream>
#include <sys/stat.h>

using namespace std;

int main(int argc, char* argv[]) {
	mkdir("sdfGeneratorOutput", 0777);
	const int imagecount = 120;
	array<string, imagecount> outputNames;

	for (int  i = 0; i < imagecount; ++i) {
		outputNames[i] = "scene" + to_string(i) + ".sdf";
		
		cout << outputNames[i] << endl;
	}


	array <string, imagecount> outputImage;

	for (int i = 0; i <imagecount; ++i){
		outputImage[i] = "image" + to_string(i) + ".ppm";
	}

	for (int i = 0; i < imagecount; ++i){
		double yAxis = i*0.1;
		ofstream fOut("sdfGeneratorOutput/"+outputNames[i]);
		string cameraCmd = "define camera eye 65.0 0 0 " + to_string(i) + " 0 0 -1 0 1 0";
		string outputImg = "render eye /Users/Benedikt/Studium/Programmiersprachen/Übung/Raytracer/PS-Raytracer/output/tmp/" + outputImage[i] + " 1280 720 4";
		

		fOut
			<<"define material red    1 0 0  1 0 0  0.5 0   0  4" << endl
			<<"define material blue   0 0 1  0 0 1  0   0   1  1" << endl << endl
			<<"define material white  1 1 1  1 1 1  1   1   1  1" << endl
			<<"define material yellow 1 1 0  1 1 0  1   1   0  1 0.6 0.0005" << endl
			<<"define material green  0 1 0  0 1 0  0   1   0  1" << endl
			<<"define shape box floor -400 -400 0  470 -410 -8000 blue" << endl
			<<"define shape box left    -400 -400 0 -410  400 -8000 white" << endl
			<<"define shape box right    400 -400 -500  460  110 -8000 red" << endl
			<<"define shape sphere sphere   0   "<<to_string(i-100) <<"-200 30 yellow" << endl
			<<"define shape sphere sphere2 60 -50 -200 20 red" << endl
			<<"define shape sphere sphere3 -30   20 -250 25 green" << endl
			<<"define shape composite root left right floor sphere sphere2 sphere3" << endl
			<<"define light ambient amb 0.05 0.1 0.05" << endl
			<<"define light diffuse sun 50 50 -180 1.0 1.0 1.0" << endl
			<<"define light diffuse sun2 -50 30 -150 0.1 1.0 0.5" << endl
			<< cameraCmd << endl
			<< outputImg<<endl;
		fOut.close();

	}

	return 0;
}

