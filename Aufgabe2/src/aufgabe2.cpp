#include <opencv2/opencv.hpp>
#include <string>
#include <algorithm>
#include <array>

#include "configs.h"
#include "bvMat.h"

using namespace cv;
using namespace bv; 
using namespace std;


int main(int argc, char** argv)
{
	BVMat image = imread(std::string(IMAGEPATH) + "Aufgabe2.jpg", 1);
	if (!image.data)
	{
		std::cerr << "No image data \n";
		return -1;
	}
	
	image.shrink(512);

	//array<Mat, 3> bgrImage;
	//split(image, bgrImage.data());

	auto cmy = image.toCMY();
	auto hsv = image.toHSV();
	auto lab = image.toLAB();
	auto yiq = image.toYIQ();

	using MatArray3 = std::array<cv::Mat, 3>;
	MatArray3 bgrGrayImage;
	cv::split(yiq, bgrGrayImage.data());

	imshow("y", bgrGrayImage[0]);
	imshow("i", bgrGrayImage[1]);
	imshow("q", bgrGrayImage[2]);
	
	namedWindow("Display Image", WINDOW_AUTOSIZE);
	imshow("Display Image", image);
	//imshow("HSV", hsv);
	//imshow("CMY", cmy);
	//imshow("LAB", lab);
	imshow("yiq", yiq);
	//imshow("Display Image", bgrImage.col(0));
	waitKey(0);
	return 0;
}
