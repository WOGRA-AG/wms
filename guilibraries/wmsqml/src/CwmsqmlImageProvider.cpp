
// WMS Includes
#include "CdmClass.h"
#include "CdmClassManager.h"
#include "CdmObjectContainer.h"

// Basetools Includes
#include "CwmsFormManager.h"

// Own Includes
#include "CwmsqmlImageProvider.h"

CwmsqmlImageProviderPixmap::CwmsqmlImageProviderPixmap()
    : QQuickImageProvider(QQuickImageProvider::Pixmap)
{
    // nothing to do
}

CwmsqmlImageProviderPixmap::~CwmsqmlImageProviderPixmap()
{
    // nothing to do
}


QPixmap CwmsqmlImageProviderPixmap::requestPixmap(const QString &id, QSize *size, const QSize &requestedSize)
{
    Q_UNUSED(size);
    QPixmap pixmap;
    CwmsFormManager cFormManager;
    QByteArray qByteArray = cFormManager.GetResource(id, QQuickImageProvider::Pixmap);
    pixmap.loadFromData(qByteArray);
    pixmap = pixmap.scaled(requestedSize);
    return pixmap;
}

CwmsqmlImageProviderImage::CwmsqmlImageProviderImage()
    : QQuickImageProvider(QQuickImageProvider::Image)
{
    // nothing to do
}

CwmsqmlImageProviderImage::~CwmsqmlImageProviderImage()
{
    // nothing to do
}


QImage CwmsqmlImageProviderImage::requestImage(const QString &id, QSize *size, const QSize &requestedSize)
{
    QImage image;
    Q_UNUSED(size);
    CwmsFormManager cFormManager;
    QByteArray qByteArray = cFormManager.GetResource(id, QQuickImageProvider::Image);
    image.loadFromData(qByteArray);
    image = image.scaled(requestedSize);
    return image;
}

