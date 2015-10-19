#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <string>
#include <algorithm>
#include <array>
#include "configs.h"

using namespace cv;
using namespace bv;
using namespace std;

enum class RGB : size_t { r = 2, g = 1, b = 0 };


int main(int argc, char** argv)
{
	//Aufgabe 1.1
	Mat image = imread(std::string(IMAGEPATH) + "Aufgabe1.jpg", 1);
	if (!image.data)
	{
		std::cerr << "No image data \n";
		return -1;
	}
	//Aufgabe 1.2 - 1.3
	// 1. read width and heigh.
	// 2. define max.
	// 3. divide 512 with max
	// 4. multiply result with width and heigh
	auto maximum = std::max(image.rows, image.cols);
	float factor = 512.0f / maximum;
	Size s(image.rows * factor, image.cols * factor);
	Mat image512;
	resize(image, image512, s);



	//Aufgabe 1.4
	array<Mat, 3> bgrGrayImage;
	split(image512, bgrGrayImage.data());

	//Aufgabe 1.5
	imwrite("RedImage.jpg", bgrGrayImage[(size_t)RGB::r]);
	imwrite("GreenImage.jpg", bgrGrayImage[(size_t)RGB::g]);
	imwrite("BlueImage.jpg", bgrGrayImage[(size_t)RGB::b]);
	

	//Aufgabe 1.6
	//namedWindow("Display Image", WINDOW_AUTOSIZE);
	imshow("Display Image", image512);
	imshow("Rotkanal", bgrGrayImage[(size_t)RGB::r]);
	imshow("Grünkanal", bgrGrayImage[(size_t)RGB::g]);
	imshow("Blaukanal", bgrGrayImage[(size_t)RGB::b]);
	

	array<Mat, 3> bgrBlack;
	bgrBlack.fill(Mat::zeros(Size(bgrGrayImage[0].cols, bgrGrayImage[0].rows), CV_8UC1));


	array<Mat, 3> rImage = bgrBlack;
	rImage[(size_t)RGB::r] = bgrGrayImage[(size_t)RGB::r];
	Mat rIm;
	merge(rImage.data(), 3, rIm);
	imshow("Rotkanal - rot eingefärbt", rIm);

	array<Mat, 3> gImage = bgrBlack;
	gImage[(size_t)RGB::g] = bgrGrayImage[(size_t)RGB::g];
	Mat gIm;
	merge(gImage.data(), 3, gIm);
	imshow("Grünkanal - grün eingefärbt", gIm);

	array<Mat, 3> bImage = bgrBlack;
	bImage[(size_t)RGB::b] = bgrGrayImage[(size_t)RGB::b];
	Mat bIm;
	merge(bImage.data(), 3, bIm);
	imshow("Blaukanal - blau eingefärbt", bIm);

	waitKey(0);
	return 0;
}
