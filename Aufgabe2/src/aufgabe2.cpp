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
	// 1. read width and heigh.
	// 2. define max.
	// 3. divide 512 with max
	// 4. multiply result with width and heigh
	auto maximum = std::max(image.rows, image.cols);
	float factor = 512.0f / maximum;
	Size s( (std::size_t)(image.cols * factor), (std::size_t)(image.rows * factor));
	Mat image512;
	resize(image, image512, s);
	cout << image512.channels();

	array<Mat, 3> bgrImage;
	split(image512, bgrImage.data());
	
	namedWindow("Display Image", WINDOW_AUTOSIZE);
	imshow("Display Image", image512);
	//imshow("Display Image", bgrImage.col(0));
	waitKey(0);
	return 0;
}
