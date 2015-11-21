#ifndef BVMAT_H
#define BVMAT_H

#include <opencv2\opencv.hpp>

#include <memory>

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
		std::array<std::size_t, 256> makeHist();
		std::array<double, 256> makeNormalisedHist();
		std::array<double, 256> makeCumulativeHist();
	};
}

#endif // BVMAT_H
