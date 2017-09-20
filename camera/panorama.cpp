// CPP program to Stitch
// input images (panorama) using OpenCV
#include <iostream>
#include <fstream>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <sstream>

// Include header files from OpenCV directory
// required to stitch images.
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/stitching.hpp"

using namespace std;
using namespace cv;

/*
compile with: g++ -std=c++11 -o pnrun panoroma.cpp `pkg-config --cflags --libs opencv`

run with: ./pnrun (name of outputfile) (names of images to be stitched)

./pnrun output 1 2 3 4 5

this will stitch together images 1.jpg, 2.jpg, 3.jpg etc into a file called output.jpg
*/




// Define mode for stitching as panoroma
// (One out of many functions of Stitcher)
Stitcher::Mode mode = Stitcher::SCANS;

// Array for pictures
vector<Mat> imgs;

int main(int argc, char* argv[])
{
    // Get all the images that need to be
    // stitched as arguments from command line
    for (int i = 2; i < argc; ++i)
    {
            // Read the ith argument or image
            // and push into the image array
            string input = argv[i];
            string name = input + ".jpg";
            Mat img = imread(name);
            if (img.empty())
            {
                // Exit if image is not present
                cout << "Can't read image '" << argv[i] << "'\n";
                return -1;
            }
            imgs.push_back(img);
    }

    // Define object to store the stitched image
    Mat pano;

    // Create a Stitcher class object with mode panoroma
    Ptr<Stitcher> stitcher = Stitcher::create(mode, false);

    // Command to stitch all the images present in the image array
    Stitcher::Status status = stitcher->stitch(imgs, pano);

    if (status != Stitcher::OK)
    {
        // Check if images could not be stiched
        // status is OK if images are stiched successfully
        cout << "Can't stitch images\n";
        return -1;
    }

    // Store a new image stiched from the given
    //set of images as "result.jpg"
    string panoname = argv[1];
    imwrite(panoname + ".jpg", pano);

    // Show the result
    imshow("Result", pano);

    waitKey(0);
    return 0;
}
