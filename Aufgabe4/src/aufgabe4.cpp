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
	
	//Mat kernel;
	//int c;
	//// Initialize arguments for the filter
	//cv::Point anchor = Point(-1, -1);
	//double delta = 0;

	//int ddepth = -1;
	//int ind = 3;
	//// Update kernel size for a normalized box filter
	//int kernel_size = 3 + 2 * (ind % 5);
	//kernel = Mat::ones(kernel_size, kernel_size, CV_32F) / (float)(kernel_size * kernel_size);
	//// Apply filter
	//filter2D(image, image, ddepth, kernel, anchor, delta, BORDER_DEFAULT);
	//imshow("filtert", image);
	//ind++;

	cv::Mat filter = (cv::Mat_<uchar>(3, 3) << 1, 2, 1, 1, 1, 1, 1, 2, 1);
	auto conv = image.applyFilter(filter);

	imshow("conv", conv);


	namedWindow("Display Image", WINDOW_AUTOSIZE);
	imshow("Display Image", image);
	waitKey(0);
	return 0;
}