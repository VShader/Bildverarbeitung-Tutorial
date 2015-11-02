#ifndef BVMAT_H
#define BVMAT_H

#include <opencv2\opencv.hpp>

namespace bv
{
	class BVMat : public cv::Mat
	{
	public:
		BVMat(const cv::Mat& mat) : Mat(mat)	{	}
	};
}

#endif // BVMAT_H
