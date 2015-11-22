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
	cv::cvtColor(image, image, CV_BGR2GRAY);
	auto hist = image.makeHist();
	auto normHist = image.makeNormalisedHist();
	auto cumHist = image.makeCumulativeHist();

	BVMat stretch = image.clone();
	stretch.histStretch();
	auto histAfter = stretch.makeHist();

	auto gamma = image.gammaCorrection(0.3);

	
	auto eq = image.clone();
	cv::equalizeHist(eq, eq);
	
	namedWindow("Display Image", WINDOW_AUTOSIZE);
	imshow("Display Image", image);
	imshow("Display stretch", stretch);
	imshow("Display gamma", gamma);
	imshow("eq", eq);
	waitKey(0);
	return 0;
}
