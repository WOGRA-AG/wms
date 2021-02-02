#ifndef CWMSQMLIMAGEPROVIDER_H
#define CWMSQMLIMAGEPROVIDER_H

#include <QQuickImageProvider>

class CwmsqmlImageProviderPixmap : public QQuickImageProvider
{
public:
    CwmsqmlImageProviderPixmap();
    virtual ~CwmsqmlImageProviderPixmap();
    virtual QPixmap requestPixmap(const QString &id, QSize *size, const QSize &requestedSize);

};

class CwmsqmlImageProviderImage : public QQuickImageProvider
{
public:
    CwmsqmlImageProviderImage();
    virtual ~CwmsqmlImageProviderImage();
    virtual QImage requestImage(const QString &id, QSize *size, const QSize &requestedSize);

};

#endif // CWMSQMLIMAGEPROVIDER_H
