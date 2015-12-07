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
    explicit Gui() : QQuickImageProvider(QQuickImageProvider::Pixmap) {}
    QImage guiImage() const;
    QImage guiRedImage() const;
    QImage guiGreenImage() const;
    QImage guiBlueImage() const;
    void loadImage();
    QPixmap requestPixmap(const QString& id, QSize* size, const QSize& requestedSize);

    enum RGB { r = 2, g = 1, b = 0 };


public slots:


signals:
    void imageChanged();


private:
    /*
     * @param image image to resize
    */
    void resizeMat(cv::Mat& image, const int max);

    cv::Mat image;
    cv::Mat redImage;
    cv::Mat greenImage;
    cv::Mat blueImage;
    QImage m_guiImage;
    QImage m_guiRedImage;
    QImage m_guiGreenImage;
    QImage m_guiBlueImage;
};

#endif // GUI_H
