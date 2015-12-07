#ifndef IMAGEPROVIDER_H
#define IMAGEPROVIDER_H

#include <QtQuick/QQuickImageProvider>
#include "gui.h"

class ImageProvider : public QQuickImageProvider
{
public:
    ImageProvider();

    //virtual QImage requestImage(const QString& id, QSize* size, const QSize& requestedSize);

private:
    Gui gui;
};

#endif // IMAGEPROVIDER_H
