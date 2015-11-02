#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <string>
#include <algorithm>
#include <array>
#include <memory>

#include <QApplication>
#include <QQmlApplicationEngine>

#include "configs.h"

using namespace bv;
using namespace std;

enum class RGB : size_t { r = 2, g = 1, b = 0 };

/*
 * @param image image to resize
*/
void resizeMat(cv::Mat& image, const int max)
{
    // 1. read width and heigh.
    // 2. define max.
    // 3. divide 512 with max
    // 4. multiply result with width and heigh
    auto maximum = std::max(image.rows, image.cols);
    float factor = (float)max / maximum;
    cv::Size s(image.cols * factor, image.rows * factor);
    cv::resize(image, image, s);
}


int main(int argc, char** argv)
{
	QApplication app(argc, argv);
	QQmlApplicationEngine engine(QUrl("qrc:/ui/RGBchannels.qml"));

    using MatArray3 = std::array<cv::Mat, 3>;


	//Aufgabe 1.1
    cv::Mat image = cv::imread(std::string(IMAGEPATH) + "Aufgabe1.jpg", 1);
	if (!image.data)
	{
		std::cerr << "No image data \n";
		return -1;
	}

	//Aufgabe 1.2 - 1.3
    cv::Mat image512 = image;
    resizeMat(image512, 512);



	//Aufgabe 1.4
    MatArray3 bgrGrayImage;
    cv::split(image512, bgrGrayImage.data());

	//Aufgabe 1.5
    cv::imwrite("RedImage.jpg", bgrGrayImage[(size_t)RGB::r]);
    cv::imwrite("GreenImage.jpg", bgrGrayImage[(size_t)RGB::g]);
    cv::imwrite("BlueImage.jpg", bgrGrayImage[(size_t)RGB::b]);
	

	//Aufgabe 1.6
	//namedWindow("Display Image", WINDOW_AUTOSIZE);
    cv::imshow("Display Image", image512);
    cv::imshow("Rotkanal", bgrGrayImage[(size_t)RGB::r]);
    cv::imshow("Grünkanal", bgrGrayImage[(size_t)RGB::g]);
    cv::imshow("Blaukanal", bgrGrayImage[(size_t)RGB::b]);
	

    MatArray3 bgrBlack;
    bgrBlack.fill(cv::Mat::zeros(cv::Size(bgrGrayImage[0].cols, bgrGrayImage[0].rows), CV_8UC1));


    MatArray3 rImage = bgrBlack;
	rImage[(size_t)RGB::r] = bgrGrayImage[(size_t)RGB::r];
    cv::Mat rIm;
    cv::merge(rImage.data(), 3, rIm);
    cv::imshow("Rotkanal - rot eingefärbt", rIm);

    MatArray3 gImage = bgrBlack;
	gImage[(size_t)RGB::g] = bgrGrayImage[(size_t)RGB::g];
    cv::Mat gIm;
    cv::merge(gImage.data(), 3, gIm);
    cv::imshow("Grünkanal - grün eingefärbt", gIm);


    MatArray3 bImage = bgrBlack;
	bImage[(size_t)RGB::b] = bgrGrayImage[(size_t)RGB::b];
    cv::Mat bIm;
    cv::merge(bImage.data(), 3, bIm);
    cv::imshow("Blaukanal - blau eingefärbt", bIm);


	return app.exec();
}
