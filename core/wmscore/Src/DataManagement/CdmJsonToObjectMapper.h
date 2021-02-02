#ifndef CDMJSONTOOBJECTMAPPER_H
#define CDMJSONTOOBJECTMAPPER_H

#include <QString>
#include <QList>
#include <QVariant>

// own Includes
#include "datamanager.h"

class CdmObject;
class CdmObjectContainer;

class WMSMANAGER_API CdmJsonToObjectMapper
{
public:
    CdmJsonToObjectMapper();

    static bool ConvertJson(CdmObject *object, QString& body);
    static bool ConvertVariantMap(CdmObject *object, QVariantMap &map);
    static bool ConvertList(CdmObjectContainer *container, QVariant& value);
    static QString GetSelfLink(QVariantMap& qvmMap);
};

#endif // CDMJSONTOOBJECTMAPPER_H
