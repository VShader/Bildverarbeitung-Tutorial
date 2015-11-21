#include <opencv2/opencv.hpp>
#include <string>
#include <array>

#include "configs.h"
#include "bvMat.h"

using namespace cv;
using namespace bv; 
using namespace std;


int main(int argc, char** argv)
{
	BVMat image = imread(std::string(IMAGEPATH) + "Aufgabe3.jpg", 1);
	if (!image.data)
	{
		std::cerr << "No image data \n";
		return -1;
	}
	
	image.shrink(512);
	auto hist = image.makeHist();
	auto normHist = image.makeNormalisedHist();
	auto cumHist = image.makeCumulativeHist();
	
	namedWindow("Display Image", WINDOW_AUTOSIZE);
	imshow("Display Image", image);
	waitKey(0);
	return 0;
}
