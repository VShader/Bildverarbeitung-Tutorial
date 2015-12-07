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
	BVMat image = imread(std::string(IMAGEPATH) + "Aufgabe2.jpg", 1);
	if (!image.data)
	{
		std::cerr << "No image data \n";
		return -1;
	}
	
	image.shrink(512);
	cv::cvtColor(image, image, CV_BGR2GRAY);
	image.convertTo(image, CV_64FC1);
	
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

	cv::Mat h1 = (cv::Mat_<double>(3, 3) << 1, 1, 1, 1, -8, 0, 1, 1, 1);
	constexpr double h2FilterFaktor = 1.0 / 16;
	cv::Mat h2 = (cv::Mat_<double>(3, 3) << 1, 2, 1, 2, 4, 2, 1, 2, 1) * h2FilterFaktor;
	cv::Mat h3 = (cv::Mat_<double>(3, 3) << 1, 2, 1, 0, 0, 0, -1, -2, -1);
	//filter = filter * filterFaktor;
	auto conv = image.applyFilter(h2);

	cv::Mat blur, filter2, gauss, lapla, sobelX, sobelY, canny;
	//DONE: Normierter Mittelwertsfilter mit Eingabe der Filtergröße
	cv::blur(image, blur, { 3, 3 });
	//imshow("blur", blur);
	//DONE: Gaussian
	cv::GaussianBlur(image, gauss, {3, 3}, 3);
	//imshow("gaussian", gauss);
	//TODO: 1.te x-Ableitung als Vorwärtsgradient
	//TODO: 1.te y-Ableitung als Vorwärtsgradient
	cv::filter2D(image, filter2, -1, h2, { -1, -1 }, 0, BORDER_DEFAULT);
	//imshow("ocvConv", filter2);
	cv::Laplacian(image, lapla, -1);
	//imshow("laplacian", lapla);
	cv::Sobel(image, sobelX, -1, 1, 0);
	imshow("sobelX", sobelX);
	cv::Sobel(image, sobelY, -1, 0, 1);
	imshow("sobelY", sobelY);
	//cv::Canny(image, canny, 1, 1);
	//imshow("canny", canny);
	//TODO: Gradientenbetrag nach Sobel, Formel auf Folie 7-49
	cv::Mat grad = sobelX.mul(sobelX) + sobelY.mul(sobelY);
	cv::sqrt(grad, grad);


	double min;
	double max;

	cv::minMaxIdx(grad, &min, &max);
	cv::convertScaleAbs(grad, grad, 255 / max);
	imshow("gradientenBetrag", grad);


	
	cv::minMaxIdx(image, &min, &max);
	cv::convertScaleAbs(image, image, 255 / max);

	cv::minMaxIdx(conv, &min, &max);
	cv::convertScaleAbs(conv, conv, 255 / max);
	imshow("conv", conv);
	namedWindow("Display Image", WINDOW_AUTOSIZE);
	imshow("Display Image", image);
	waitKey(0);
	return 0;
}