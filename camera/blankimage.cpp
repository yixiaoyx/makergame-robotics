// Title: Create a coloured image in C++ using OpenCV.

// highgui - an easy-to-use interface to
// video capturing, image and video codecs,
// as well as simple UI capabilities.
#include "opencv2/highgui/highgui.hpp"
#include <opencv2/core/core.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
// Namespace where all the C++ OpenCV
// functionality resides.
using namespace cv;

// For basic input / output operations.
// Else use macro 'std::' everywhere.
using namespace std;

int main()
{
    // To create an image
    // CV_8UC3 depicts : (3 channels,8 bit image depth
    // Height  = 500 pixels, Width = 1000 pixels
    // (0, 0, 100) assigned for Blue, Green and Red
    //             plane respectively.
    // So the image will appear red as the red
    // component is set to 100.
    Mat loadim;
    loadim = imread("TestImage.jpg", CV_8UC3);
    if (loadim.empty())
    {
        cout << "could not load image\n";
        return -1;	// Unsuccessful.
    }
    Mat img(500, 500, CV_8UC3, Scalar(0,0, 100));

    // check whether the image is loaded or not
    if (img.empty())
    {
        cout << "\n Image not created. You"
                     " have done something wrong. \n";
		return -1;	// Unsuccessful.
    }

    // first argument: name of the window
    // second argument: flag- types:
    // WINDOW_NORMAL If this is set, the user can
    //               resize the window.
    // WINDOW_AUTOSIZE If this is set, the window size
    //                is automatically adjusted to fit
    //                the displayed image, and you cannot
    //                change the window size manually.
    // WINDOW_OPENGL  If this is set, the window will be
    //                created with OpenGL support.
    namedWindow("A_good_name", CV_WINDOW_AUTOSIZE);

    // first argument: name of the window
    // second argument: image to be shown(Mat object)

    const int x =100;
    const int y =100;
    cv::Mat destRoi;
    try {
        destRoi = img(cv::Rect(x, y, loadim.cols, loadim.rows));
    }  catch (...) {
        std::cerr << "Trying to create roi out of image boundaries" << std::endl;
        return -1;
    }
    loadim.copyTo(destRoi);




    //loadim.copyTo(img.rowRange(1, 161).colRange(1, 201));   //more info here https://stackoverflow.com/questions/10991523/opencv-draw-an-image-over-another-image
    imshow("A_good_name", destRoi);
    //imshow("A_good_name", loadim);
    waitKey(0); //wait infinite time for a keypress

    // destroy the window with the name, "MyWindow"
    destroyWindow("A_good_name");

    return 0;
}
// END OF PROGRAM
