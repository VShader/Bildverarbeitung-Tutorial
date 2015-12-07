#ifndef BVMAT_H
#define BVMAT_H

#include <opencv2\opencv.hpp>

#include <memory>
#include <array>
#include <cmath>

namespace bv
{
	enum RGB { r = 2, g = 1, b = 0 };

	class BVMat : public cv::Mat
	{
	public:
		BVMat(const cv::Mat& mat) : Mat(mat)	{	}
		
		void shrink(std::size_t size);
		BVMat toHSV();
		BVMat toCMY();
		BVMat toYIQ();
		BVMat toLAB();
		std::array<std::size_t, 256> makeHist() const;
		std::array<double, 256> makeNormalisedHist() const;
		std::array<double, 256> makeCumulativeHist() const;

		void histStretch();
		BVMat gammaCorrection(const double gamma);
		BVMat applyFilter(const BVMat& filter) const;

	private:
		template<typename T>
		auto histStretch(T& g, uchar gmin, uchar gmax, uchar wmin, uchar wmax)
		{
			return (g - gmin) * (wmax - wmin) / (gmax - gmin) + wmin;
		}

		template<typename T>
		std::pair<T, T> getMinMax(const std::array<T, 256>& hist)
		{
			std::pair<uchar, uchar> minMax;
			for (auto forwardIt = hist.begin(); forwardIt < hist.end(); ++forwardIt)
			{
				if (*forwardIt != 0)
				{
					minMax.first = forwardIt._Idx;
					break;
				}
			}

			for (auto backwardIt = --hist.end(); backwardIt > hist.begin(); --backwardIt)
			{
				if (*backwardIt != 0)
				{
					minMax.second = backwardIt._Idx;
					break;
				}
			}
			return minMax;
		}

		template<typename T>
		auto gammaCorrection(T& g, uchar gmin, uchar gmax, uchar wmin, uchar wmax, double gamma)
		{
			return (wmax - wmin) * std::pow(((double)(g - gmin) / (double)(gmax - gmin)), gamma) + wmin;
		}


		template<typename T>
		auto BVMat::conv(const cv::Mat& rhs) const
		{
			double output = 0;
			for (int col = 0; col < this->cols; col++)
			{
				for (int row = 0; row < this->rows; row++)
				{
					auto a = this->at<T>(row, col);
					auto b = rhs.at<T>(rhs.rows - 1 - row, rhs.cols - 1 - col);
					output += this->at<T>(row, col) * rhs.at<T>(rhs.rows - 1 - row, rhs.cols - 1 - col);
				}
			}
			return output;
		}
	};
}


#endif // BVMAT_H
