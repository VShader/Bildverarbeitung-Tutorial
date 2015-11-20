#include "bvMat.h"

#include <array>
#include <algorithm>

using namespace std;
using namespace bv;

void BVMat::shrink(size_t size)
{
	// 1. read width and heigh.
	// 2. define max.
	// 3. divide 512 with max
	// 4. multiply result with width and heigh
	auto maximum = std::max(this->rows, this->cols);
	float factor = (float)size / maximum;
	cv::Size s((std::size_t)(this->cols * factor), (std::size_t)(this->rows * factor));
	cv::resize(*this, *this, s);
}

BVMat BVMat::toHSV()
{
	BVMat hsvMat = this->clone();
	cv::cvtColor(hsvMat, hsvMat, cv::COLOR_BGR2HSV);
	return hsvMat;
}

BVMat BVMat::toCMY()
{
	auto cmyMat = this->clone();
	cmyMat = cv::Scalar(255, 255, 255) - cmyMat;
	return cmyMat;
}

BVMat BVMat::toYIQ()
{
	cv::Mat yiqMat;
	this->convertTo(yiqMat, CV_64FC3);
	//cv::normalize(yiqMat, yiqMat);

	using mMatrix = std::array<std::array<double, 3>, 3>;
	constexpr mMatrix val = { 0.299, 0.587, 0.114,
		0.595716, -0.274453, -0.321263,
		0.211456, -0.522591, 0.311135 };

	for (int rowIt = 0; rowIt < yiqMat.rows; rowIt++)
	{
		for (int colIt = 0; colIt < yiqMat.cols; colIt++)
		{
			auto& pixel = yiqMat.at<cv::Vec3d>(rowIt, colIt);
			auto tmpPixel = pixel;
			tmpPixel[r] = tmpPixel[r] / 255;
			tmpPixel[g] = tmpPixel[g] / 255;
			tmpPixel[b] = tmpPixel[b] / 255;
			pixel[r] = tmpPixel[r] * val[0][0] + tmpPixel[g] * val[0][1] + tmpPixel[b] * val[0][2];
			pixel[g] = tmpPixel[r] * val[1][0] + tmpPixel[g] * val[1][1] + tmpPixel[b] * val[1][2];
			pixel[b] = tmpPixel[r] * val[2][0] + tmpPixel[g] * val[2][1] + tmpPixel[b] * val[2][2];
		}
	}
	return yiqMat;
}

BVMat BVMat::toLAB()
{
	BVMat labMat = this->clone();
	cv::cvtColor(labMat, labMat, cv::COLOR_BGR2Lab);
	return labMat;
}
