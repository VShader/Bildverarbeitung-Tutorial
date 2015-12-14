#ifndef GUI_H
#define GUI_H

#include <QImage>
#include <QtQuick/QQuickImageProvider>
#include <opencv2/opencv.hpp>
#include <array>


using MatArray3 = std::array<cv::Mat, 3>;

class Gui : public QQuickImageProvider
{
    //Q_PROPERTY(QImage guiImage READ guiImage NOTIFY imageChanged)
public:
    explicit Gui() : QQuickImageProvider(QQuickImageProvider::Image) {}
    void loadImage();
    QImage requestImage(const QString& id, QSize* size, const QSize& requestedSize);

    enum RGB { r = 2, g = 1, b = 0 };


public slots:


signals:
    void imageChanged();


private:
    /*
     * @param image image to resize
    */
    void resizeMat(cv::Mat& image, const int max);
	QImage createView(cv::Mat& image);

    cv::Mat image;
	MatArray3 bgrGrayImage;
	MatArray3 bgrColourImage;
};

#endif // GUI_H
