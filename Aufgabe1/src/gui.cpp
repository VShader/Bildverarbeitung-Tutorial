#include "gui.h"
#include "configs.h"
#include <algorithm>

using namespace bv;


/*
 * @param image image to resize
*/
void Gui::resizeMat(cv::Mat& image, const int max)
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


void Gui::loadImage()
{
    image = cv::imread(std::string(IMAGEPATH) + "Aufgabe1.jpg", 1);
    if (!image.data)
    {
        std::cerr << "No image data \n";
        std::abort();
    }

    //Aufgabe 1.2 - 1.3
    cv::Mat image512 = image;
    resizeMat(image512, 512);
	resizeMat(image, 512);

    //Aufgabe 1.4
    cv::split(image512, bgrGrayImage.data());

	MatArray3 bgrBlack;
	bgrBlack.fill(cv::Mat::zeros(cv::Size(bgrGrayImage[0].cols, bgrGrayImage[0].rows), CV_8UC1));

	MatArray3 tmp = bgrBlack;
	tmp[r] = bgrGrayImage[r];
	cv::merge(tmp.data(), 3, bgrColourImage[r]);

	tmp = bgrBlack;
	tmp[g] = bgrGrayImage[g];
	cv::merge(tmp.data(), 3, bgrColourImage[g]);

	tmp = bgrBlack;
	tmp[b] = bgrGrayImage[b];
	cv::merge(tmp.data(), 3, bgrColourImage[b]);
}


QImage Gui::requestImage(const QString &id, QSize *size, const QSize &requestedSize)
{
	QImage dest;
	if (id == "red")
	{
		dest = createView(bgrColourImage[r]);
	}
	else if (id == "green")
	{
		dest = createView(bgrColourImage[g]);
	}
	else if (id == "blue")
	{
		dest = createView(bgrColourImage[b]);
	}
	else if (id == "redGray")
	{
		dest = createView(bgrColourImage[r]);
	}
	else if (id == "greenGray")
	{
		dest = createView(bgrColourImage[g]);
	}
	else if (id == "blueGray")
	{
		dest = createView(bgrColourImage[b]);
	}
	else
	{
		dest = createView(image);
	}
	
    if (size)
        *size = QSize(dest.width(), dest.height());

    dest.scaled(requestedSize.width(), requestedSize.height());
    return dest;
}


QImage Gui::createView(cv::Mat& input)
{
	QImage::Format format = QImage::Format::Format_RGB888;

	switch (input.type())
	{
	case CV_8UC4:
		format = QImage::Format::Format_RGB32;
		break;
		// 8-bit, 3 channel
	case CV_8UC3:
		format = QImage::Format::Format_RGB888;
		break;
	default:
		break;
	}

	QImage dest(input.data, input.cols, input.rows, input.step, format);
	dest.bits();
	return dest.rgbSwapped();
}