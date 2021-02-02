#ifndef CWMSSCRIPTABLEGEOSERVICES_H
#define CWMSSCRIPTABLEGEOSERVICES_H

// System and Qt Includes
#include <QList>
#include <QVariant>
#include <QGeoRoute>
#include <QGeoCodeReply>

// Own Includes
#include "CwmsScriptableBase.h"
#include "basetools.h"

class QGeoServiceProvider;
class QGeoPositionInfoSource;
class CsaObject;
class QGeoRouteReply;

class BASETOOLS_API CwmsScriptableGeoServices : public CwmsScriptableBase
{
    Q_OBJECT

private:
    QGeoServiceProvider* m_pProvider;
    QGeoPositionInfoSource *m_pPositionProvider;

    bool waitForReplyFinished(QGeoCodeReply *p_pReply);
    QVariant coordinateToVariant(QGeoCoordinate coordinate);
    bool waitForReplyFinished(QGeoRouteReply *p_pReply);
    QVariant addressToVariant(QGeoAddress address);
    QVariant createPathVariantList(QList<QGeoCoordinate> p_rCoordinates);
    QVariant createSegmentList(QGeoRoute &p_rRoute);
public:
    CwmsScriptableGeoServices();
    virtual ~CwmsScriptableGeoServices();

public slots:
    QVariant getCurrentPosition();
    bool initGeoService();
    double calculateDistanceKm(double latFrom, double lonFrom, double latTo, double lonTo);
    QVariant calculateRoute(double latFrom, double lonFrom, double latTo, double lonTo);
    QStringList getGeoServiceList();
    bool initGeoService(QString p_qstrService);
    QVariantList rangeSearch(double latPoint, double lonPoint, double rangeKm, QString p_qstrContainerKeyname, QString qstrLatFieldName, QString LonFieldName);
    double getCurrentVerticalSpeed();
    double getCurrentGroundSpeed();
    double getCurrentAltitude();
    QVariant geoCodeToAddress(double latitude, double longitude);
    QVariant geoCodeToCoordinate(QString street, QString postcode, QString city, QString country);
    bool isInitialized();
    bool reinitGeoService(QString p_qstrService);
};

#endif // CWMSSCRIPTABLEGEOSERVICES_H
