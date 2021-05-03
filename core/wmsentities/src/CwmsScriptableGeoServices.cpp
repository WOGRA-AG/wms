// System and Qt Includes
//#include <math.h>
#include <QCoreApplication>
#include <QThread>
#include <QScopedPointer>
#include <QGeoServiceProvider>
#include <QGeoCodingManager>
#include <QGeoAddress>
#include <QGeoCodeReply>
#include <QGeoRouteSegment>
#include <QGeoPositionInfoSource>
#include <QGeoCoordinate>
#include <QGeoRoutingManager>
#include <QGeoManeuver>

// WMS Commons Includes
#include "CwmsUtilities.h"

// WMS Includes
#include "CsaObject.h"
#include "CsaFactory.h"
#include "CdmObject.h"
#include "CdmQuery.h"
#include "CdmQueryBuilder.h"
#include "CdmLogging.h"


// own Includes
#include "CwmsScriptableGeoServices.h"

#define DISTANCE "distance"
#define DIRECTION "direction"
#define POSITION "position"
#define INSTRUCTION "instruction"
#define PATH "path"
#define MANEUVER "maneuver"
#define DISTANCE_UNIT 111.045
#define MSLEEP_TIMER 10
#define GEO_REPLY_TIMEOUT_MSECS 10000
#define LATITUDE "latitude"
#define LONGITUDE "longitude"
#define ALTITUDE "altitude"
#define M_PI 3.14

CwmsScriptableGeoServices::CwmsScriptableGeoServices()
    : m_pProvider(nullptr),
      m_pPositionProvider(nullptr)
{
}

CwmsScriptableGeoServices::~CwmsScriptableGeoServices()
{
    DELPTR(m_pProvider);
    DELPTR(m_pPositionProvider)
}

bool CwmsScriptableGeoServices::initGeoService()
{
    return initGeoService("osm");
}

bool CwmsScriptableGeoServices::initGeoService(QString p_qstrService)
{
    if (!isInitialized())
    {
        m_pProvider = new QGeoServiceProvider(p_qstrService);
        m_pPositionProvider = QGeoPositionInfoSource::createDefaultSource(this);

        if (m_pPositionProvider)
        {
            m_pPositionProvider->setUpdateInterval(5000);
            m_pPositionProvider->startUpdates();
        }

        return true;
    }

    return false;
}

bool CwmsScriptableGeoServices::reinitGeoService(QString p_qstrService)
{
    if (m_pProvider)
    {
        DELPTR(m_pProvider);
    }

    if (m_pPositionProvider)
    {
        DELPTR(m_pPositionProvider);
    }

    m_pProvider = new QGeoServiceProvider(p_qstrService);
    m_pPositionProvider = QGeoPositionInfoSource::createDefaultSource(this);

    if (m_pPositionProvider)
    {
        m_pPositionProvider->setUpdateInterval(5000);
        m_pPositionProvider->startUpdates();
    }

    return true;
}

bool CwmsScriptableGeoServices::isInitialized()
{
    return (m_pPositionProvider && m_pProvider);
}

QStringList CwmsScriptableGeoServices::getGeoServiceList()
{
    QStringList list;
    return QGeoServiceProvider::availableServiceProviders();
}



QVariant CwmsScriptableGeoServices::getCurrentPosition()
{
    QVariant qvCoordinate;
    if (CHKPTR(m_pPositionProvider))
    {
        QGeoPositionInfo info = m_pPositionProvider->lastKnownPosition();
        QGeoCoordinate coordinate = info.coordinate();
        qvCoordinate = coordinateToVariant(coordinate);
    }
    else
    {
        ERR("Geo Services not initialized.");
    }
    return qvCoordinate;
}

QVariant CwmsScriptableGeoServices::coordinateToVariant(QGeoCoordinate coordinate)
{
    QVariantMap qvCoordinate;

    if (coordinate.isValid())
    {
       double latitude = coordinate.latitude();
        double longitude = coordinate.longitude();
        double altitude = coordinate.altitude();

        if (!CwmsUtilities::isNumberValid(altitude))
        {
            // No height information there ;)
            altitude = 0;
        }

        qvCoordinate.insert(LATITUDE, latitude);
        qvCoordinate.insert(LONGITUDE, longitude);
        qvCoordinate.insert(ALTITUDE, altitude);
    }
    else
    {
        ERR("Invalid Geocoordinate!");
    }

    return qvCoordinate;
}

QVariant CwmsScriptableGeoServices::geoCodeToAddress(double latitude, double longitude)
{
    QVariant address;
    if (CHKPTR(m_pProvider))
    {
        QGeoCodingManager* pGeoCondingManager = m_pProvider->geocodingManager();

        if (CHKPTR(pGeoCondingManager))
        {
            QGeoCoordinate coordinate(latitude, longitude);
            QGeoCodeReply * reply = pGeoCondingManager->reverseGeocode(coordinate);

            if (CHKPTR(reply))
            {
                waitForReplyFinished(reply);

                if (reply->error() == QGeoCodeReply::NoError)
                {
                    QList<QGeoLocation> results = reply->locations();

                    if (results.count() > 0)
                    {
                        QGeoLocation location = results[0];
                        QGeoAddress geoAddress = location.address();
                        address = addressToVariant(geoAddress);
                    }
                    else
                    {
                        ERR("No address found");
                    }
                }
                else
                {
                    ERR("Geocoding error: " + reply->errorString());
                }

                reply->deleteLater();
            }
        }
    }
    else
    {
        ERR("Geo Services not initialized.");
    }

    return address;
}

QVariant CwmsScriptableGeoServices::addressToVariant(QGeoAddress geoAddress)
{
    QVariantMap qvAddress;
    qvAddress.insert("city", geoAddress.city());
    qvAddress.insert("country", geoAddress.country());
    qvAddress.insert("countryCode", geoAddress.countryCode());
    qvAddress.insert("postcode", geoAddress.postalCode());
    qvAddress.insert("street", geoAddress.street());
    qvAddress.insert("state", geoAddress.state());
    qvAddress.insert("text", geoAddress.text());
    qvAddress.insert("district", geoAddress.district());
    return qvAddress;
}

QVariant CwmsScriptableGeoServices::geoCodeToCoordinate(QString street, QString postcode, QString city, QString country)
{
    QVariant qvCoordinate;
    if (CHKPTR(m_pProvider))
    {
        QGeoCodingManager* pGeoCondingManager = m_pProvider->geocodingManager();

        if (CHKPTR(pGeoCondingManager))
        {
            QGeoAddress address;
            address.setStreet(street);
            address.setPostalCode(postcode);
            address.setCity(city);
            address.setCountry(country);
            QGeoCodeReply * reply = pGeoCondingManager->geocode(address);

            if (CHKPTR(reply))
            {
                waitForReplyFinished(reply);

                if (reply->error() == QGeoCodeReply::NoError)
                {
                    QList<QGeoLocation> results = reply->locations();

                    if (results.count() > 0)
                    {
                        QGeoLocation location = results[0];
                        QGeoCoordinate coordinate = location.coordinate();
                        qvCoordinate = coordinateToVariant(coordinate);

                    }
                    else
                    {
                        ERR("No address found");
                    }
                }
                else
                {
                    ERR("Geocoding error: " + reply->errorString());
                }

                reply->deleteLater();
            }
        }
    }
    else
    {
        ERR("Geo Services not initialized.");
    }

    return qvCoordinate;
}

bool CwmsScriptableGeoServices::waitForReplyFinished(QGeoCodeReply* p_pReply)
{
    if (CHKPTR(p_pReply))
    {
        int sleepCounter = 0;
        while (!p_pReply->isFinished() && p_pReply->error() == QGeoCodeReply::NoError && sleepCounter < GEO_REPLY_TIMEOUT_MSECS / MSLEEP_TIMER)
        {
            QThread::currentThread()->msleep(MSLEEP_TIMER);
            ++sleepCounter;
            qApp->processEvents();
        }

        return p_pReply->isFinished();
    }

    return false;
}

bool CwmsScriptableGeoServices::waitForReplyFinished(QGeoRouteReply* p_pReply)
{
    if (CHKPTR(p_pReply))
    {
        int sleepCounter = 0;
        while (!p_pReply->isFinished() && p_pReply->error() == QGeoRouteReply::NoError && sleepCounter < GEO_REPLY_TIMEOUT_MSECS / MSLEEP_TIMER)
        {
            QThread::currentThread()->msleep(MSLEEP_TIMER);
            ++sleepCounter;
            qApp->processEvents();
        }

        return p_pReply->isFinished();
    }

    return false;
}

double CwmsScriptableGeoServices::getCurrentAltitude()
{
    if (CHKPTR(m_pPositionProvider))
    {
        QGeoPositionInfo info = m_pPositionProvider->lastKnownPosition();
        QGeoCoordinate coordinate = info.coordinate();
        return coordinate.altitude();
    }
    else
    {
        ERR("Geo Services not initialized.");
    }

    return -1;
}

double CwmsScriptableGeoServices::getCurrentGroundSpeed()
{
    if (CHKPTR(m_pPositionProvider))
    {
        QGeoPositionInfo info = m_pPositionProvider->lastKnownPosition();
        return info.attribute(QGeoPositionInfo::GroundSpeed);
    }
    else
    {
        ERR("Geo Services not initialized.");
    }

    return -1;
}

double CwmsScriptableGeoServices::getCurrentVerticalSpeed()
{
    if (CHKPTR(m_pPositionProvider))
    {
        QGeoPositionInfo info = m_pPositionProvider->lastKnownPosition();
        return info.attribute(QGeoPositionInfo::VerticalSpeed);
    }
    else
    {
        ERR("Geo Services not initialized.");
    }

    return -1;
}


double CwmsScriptableGeoServices::calculateDistanceKm(double latFrom, double lonFrom, double latTo, double lonTo)
{
    QGeoCoordinate coordinateFrom(latFrom, lonFrom);
    QGeoCoordinate coordinateTo(latTo, lonTo);
    return coordinateFrom.distanceTo(coordinateTo) / 1000;
}


QVariant CwmsScriptableGeoServices::calculateRoute(double latFrom, double lonFrom, double latTo, double lonTo)
{
    QVariantMap qvRoute;
    if (CHKPTR(m_pPositionProvider))
    {
        QGeoRoutingManager* pRoutingManager = m_pProvider->routingManager();

        if (CHKPTR(pRoutingManager))
        {
            QGeoCoordinate start(latFrom, lonFrom);
            QGeoCoordinate destination(latTo, lonTo);
            QGeoRouteRequest request(start, destination);

            QGeoRouteReply *reply = pRoutingManager->calculateRoute(request);

            if (CHKPTR(reply))
            {
                if (waitForReplyFinished(reply))
                {
                    if (reply->error() == QGeoRouteReply::NoError)
                    {
                        if (reply->routes().size() != 0)
                        {
                            // ... but by default it will only get a single route
                            QGeoRoute route = reply->routes().at(0);
                            qvRoute.insert(DISTANCE, route.distance() / 1000);
                            QVariant path = createPathVariantList(route.path());
                            qvRoute.insert(PATH, path);
                            QVariant qvSegments = createSegmentList(route);
                            qvRoute.insert("segments", qvSegments);
                        }
                        else
                        {
                            ERR("No route found!");
                        }
                    }
                    else
                    {
                        ERR("Geocoding error: " + reply->errorString());
                    }
                }
                else
                {
                    ERR("Geocoding timed out. ");
                }

                reply->deleteLater();
            }
        }
    }
    else
    {
        ERR("Geo Services not initialized.");
    }

    return qvRoute;
}

QVariant CwmsScriptableGeoServices::createSegmentList(QGeoRoute& p_rRoute)
{
    QVariantList segments;

    QGeoRouteSegment segment = p_rRoute.firstRouteSegment();

    while (segment.isValid())
    {
        QVariantMap qvSegment;
        qvSegment.insert(DISTANCE, segment.distance() / 1000);
        qvSegment.insert(PATH, createPathVariantList(segment.path()));
        QGeoManeuver maneuver = segment.maneuver();
        QVariantMap maneuverMap;
        maneuverMap.insert(DISTANCE, maneuver.distanceToNextInstruction() / 1000);
        maneuverMap.insert(DIRECTION, maneuver.direction());
        maneuverMap.insert(INSTRUCTION, maneuver.instructionText());
        maneuverMap.insert(POSITION, coordinateToVariant(maneuver.position()));
        qvSegment.insert(MANEUVER, maneuverMap);
        segment = segment.nextRouteSegment();
        segments.append(qvSegment);
    }

    return segments;
}

QVariant CwmsScriptableGeoServices::createPathVariantList(QList<QGeoCoordinate> p_rCoordinates)
{
    QVariantList path;

    for (int pos = 0; pos < p_rCoordinates.count(); ++pos)
    {
        QVariant qvGeo;
        QGeoCoordinate coordinate = p_rCoordinates[pos];
        qvGeo = coordinateToVariant(coordinate);
        path.append(qvGeo);
    }

    return path;
}

QVariantList CwmsScriptableGeoServices::rangeSearch(double latPoint, double lonPoint, double rangeKm, QString p_qstrContainerKeyname, QString qstrLatFieldName, QString qstrLonFieldName)
{
    QVariantList results;
    CsaFactory* pFactory = getFactory();

    if (CHKPTR(pFactory))
    {
        QGeoCoordinate center(latPoint, lonPoint);
        double latDivision = (rangeKm / DISTANCE_UNIT);
        double latFrom = (latPoint - latDivision);
        double latTo = (latPoint + latDivision);
        latPoint *= M_PI / 180.0;
        double lonFormulaMultiplication = (rangeKm / (DISTANCE_UNIT)); //* cos((double)latPoint))); TODO
        double lonFrom = (lonPoint - lonFormulaMultiplication);
        double lonTo = (lonPoint + lonFormulaMultiplication);

        if (!p_qstrContainerKeyname.isEmpty())
        {
            QString qstrWql = "select from " + p_qstrContainerKeyname +
                    " where and(" + qstrLatFieldName + " >= " + QString::number(latFrom, 'g', 8) + ", " + qstrLatFieldName + " <= " + QString::number(latTo, 'g', 8) +
                    ", " + qstrLonFieldName + " >= " + QString::number(lonFrom, 'g', 8) + ", " + qstrLonFieldName + " <= " + QString::number(lonTo, 'g', 8) + ")";
            ERR(qstrWql);
            QScopedPointer<CdmQuery> pQuery (CdmQueryBuilder::ExecuteQuery(qstrWql));

            if (pQuery != nullptr)
            {
                for (int counter = 0; counter < pQuery->GetResultCount(); ++counter)
                {
                    CdmObject* pObject = pQuery->GetObjectAt(counter);

                    if (CHKPTR(pObject))
                    {
                        CsaLocatedElement* pElement = pFactory->createScriptObject(pObject);
                        CsaObject* pSimpleObject = dynamic_cast<CsaObject*> (pElement);

                        if (pSimpleObject)
                        {
                            // because our range search was made with an rectangle we have to sort out the object which do not fit in range criteria.
                            QGeoCoordinate poi(pSimpleObject->getValueDouble(qstrLatFieldName), pSimpleObject->getValueDouble(qstrLonFieldName));
                            double distanceKm = center.distanceTo(poi) / 1000;
                            if (distanceKm <= rangeKm)
                            {
                                results.append(QVariant::fromValue(pSimpleObject));
                            }
                        }
                    }
                }
            }
        }
    }

    return results;
}
