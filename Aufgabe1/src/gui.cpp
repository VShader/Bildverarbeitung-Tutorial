#include "gui.h"
#include "configs.h"
#include <algorithm>

using namespace bv;

QImage Gui::guiImage() const
{
    cv::cvtColor(image, image, CV_BGR2RGB);
    QImage dest((const uchar *)image.data, image.cols, image.rows, image.step, QImage::Format_RGB888);
    dest.bits();
    return dest;
}


QImage Gui::guiRedImage() const
{
    return m_guiRedImage;
}


QImage Gui::guiGreenImage() const
{
    return m_guiGreenImage;
}


QImage Gui::guiBlueImage() const
{
    return m_guiBlueImage;
}


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
    cv::Mat image = cv::imread(std::string(IMAGEPATH) + "Aufgabe1.jpg", 1);
    if (!image.data)
    {
        std::cerr << "No image data \n";
        std::abort();
    }

    //Aufgabe 1.2 - 1.3
    cv::Mat image512 = image;
    resizeMat(image512, 512);

    //Aufgabe 1.4
    MatArray3 bgrGrayImage;
    cv::split(image512, bgrGrayImage.data());
}


QPixmap Gui::requestPixmap(const QString &id, QSize *size, const QSize &requestedSize)
{
    QImage dest(image.data, image.cols, image.rows, image.step, QImage::Format_RGB16);
    dest.bits();

    if (size)
        *size = QSize(dest.width(), dest.height());

    dest.scaled(requestedSize.width(), requestedSize.height());

//    gui.loadImage();
//    if(id == "image")
//    {

//    }
    return dest;

//    int width = 100;
//            int height = 50;

//            if (size)
//                *size = QSize(width, height);
//            QPixmap pixmap(requestedSize.width() > 0 ? requestedSize.width() : width,
//                           requestedSize.height() > 0 ? requestedSize.height() : height);
//            pixmap.fill(QColor(id).rgba());

//            return pixmap;
}
