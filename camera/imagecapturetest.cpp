#include <opencv2/opencv.hpp>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sstream>
/*
compile with: g++ -std=c++11 -o caprun imagecapturetest.cpp `pkg-config --cflags --libs opencv`

run with: ./caprun

press space bar to capture an image
*/

using namespace cv;
using namespace std;

int main(int argc, char ** argv){
	cv::VideoCapture cap(1);
	if(!cap.isOpened()){
		return -1;
	}
	cv::Mat img;
  int imnum = 0;
	srand(time(NULL));
	while(1){
		waitKey(0);
		for(int i = 0; i < 5; i++) //not sure why but this makes sure the captured image is up to date, some sort of pause i think
		cap >> img;
		std::string s = "image";
		cv::imwrite(std::to_string(imnum) + ".jpg", img);
		cv::waitKey(33);            //this takes an image and saves it everytime you press space bar
		imshow("picture taken", img);
		cout << "wrote image " << imnum<< endl;
    imnum ++;
	}
	return 1;
}
