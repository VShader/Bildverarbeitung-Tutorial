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
	cv::normalize(yiqMat, yiqMat, 0, 1, cv::NORM_MINMAX);

	using mMatrix = std::array<std::array<double, 3>, 3>;
	constexpr mMatrix val = { 0.299, 0.587, 0.114,
		0.595716, -0.274453, -0.321263,
		0.211456, -0.522591, 0.311135 };

	for (int colIt = 0; colIt < yiqMat.cols; colIt++)
	{
		for (int rowIt = 0; rowIt < yiqMat.rows; rowIt++)
		{
			auto& pixel = yiqMat.at<cv::Vec3d>(rowIt, colIt);
			auto tmpPixel = pixel;
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

std::array<std::size_t, 256> BVMat::makeHist() const
{
	//check if grayscale, if not convert.
	if(this->dims > 2)
		cv::cvtColor(*this, *this, CV_BGR2GRAY);

	std::array<std::size_t, 256> hist;
	hist.fill(0);
	for (int colIt = 0; colIt < this->cols; colIt++)
	{
		for (int rowIt = 0; rowIt < this->rows; rowIt++)
		{
			auto& pixel = this->at<uchar>(rowIt, colIt);
			hist[pixel] += 1;
		}
	}
	return hist;
}

std::array<double, 256> BVMat::makeNormalisedHist() const
{
	array<double, 256> hist;
	auto tmpHist = makeHist();
	for (int i = 0; i < tmpHist.size(); ++i)
	{
		hist[i] = (double)tmpHist[i] / (rows * cols);
	}
	return hist;
}

std::array<double, 256> BVMat::makeCumulativeHist() const
{
	auto hist = makeNormalisedHist();
	for (auto iterator = ++hist.begin(); iterator < hist.end(); iterator++)
	{
		*iterator += *(iterator - 1);
	}
	return hist;
}

void BVMat::histStretch()
{
	constexpr uchar wmin = 0;
	constexpr uchar wmax = 255;

	auto hist = makeHist();
	const auto minMax = getMinMax(hist);

	for (int colIt = 0; colIt < this->cols; colIt++)
	{
		for (int rowIt = 0; rowIt < this->rows; rowIt++)
		{
			auto& pixel = this->at<uchar>(rowIt, colIt);
			pixel = histStretch(pixel, minMax.first, minMax.second, wmin, wmax);
		}
	}
}

BVMat BVMat::gammaCorrection(const double gamma)
{
	cv::Mat gammaMat = this->clone();
	//this->convertTo(gammaMat, CV_64FC1);

	constexpr uchar wmin = 0;
	constexpr uchar wmax = 255;

	auto hist = makeHist();
	const auto minMax = getMinMax(hist);

	for (int colIt = 0; colIt < gammaMat.cols; colIt++)
	{
		for (int rowIt = 0; rowIt < gammaMat.rows; rowIt++)
		{
			auto& pixel = gammaMat.at<uchar>(rowIt, colIt);
			pixel = gammaCorrection(pixel, 0, 255, wmin, wmax, gamma);
		}
	}
	return gammaMat;
}



BVMat BVMat::applyFilter(const BVMat& filter) const
{
	// Better zero Mat + insert image
	cv::Mat output;
	this->convertTo(output, CV_64FC2);
	cv::Mat input = output.clone();
	cv::Mat sourceMat(input.rows + 2, input.cols + 2, input.type(), cv::Scalar(0)); // Zero Mat
	//this->copyTo(sourceMat.rowRange(1, sourceMat.rows - 1), sourceMat.colRange(1, sourceMat.cols - 1));
	this->copyTo(sourceMat(cv::Rect(1, 1, this->cols , this->rows)));
	//src.copyTo(dst(Rect(left, top, src.cols, src.rows)));


	//BVMat output = this->clone();
	//cv::Mat output = cv::Mat::zeros(this->rows + 1, this->cols + 1, this->type);

	// 3. rest

	for (int i = 1; i < output.cols - 1; i++)
	{
		for (int j = 1; j < output.rows - 1; j++)
		{
			cv::Mat roi(sourceMat, cv::Rect(i -1, j -1, 3, 3));
			output.at<double>(j, i) = filter.conv<double>(roi);
		}
	}

	return output;
}
