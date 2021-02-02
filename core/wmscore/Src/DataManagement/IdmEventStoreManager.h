#ifndef IDMEVENTSTOREMANAGER_H
#define IDMEVENTSTOREMANAGER_H

#include <QString>
#include <QVariant>
#include "CwmsJson.h"
#include "CdmClassMethod.h"
#include <QObject>
#include "CdmObjectContainer.h"
#include "IdmEventIterator.h"

class IdmEventStoreManager
{
public:
    virtual void subscribe(CdmClassMethod* pSubscriber) = 0;
    virtual void startEvent(QString qstr_EventName) = 0;
    virtual void stopEvent(QString qstr_EventName, QObject *pEventDto) = 0;
    virtual QList<CdmClassMethod*>& getSubscribers() = 0;
    virtual IdmEventIterator* getEventIterator() = 0;
    virtual QObject* createEventDtoObject(QVariantList qvlEvent) = 0;
    virtual int deleteAllExistingEventsByDatabaseId(int i_DbId) = 0;
    virtual void setInitEventUuidAndInitDto(QString qstrInitEventUuid, QObject *pInitEventDto) = 0;
    virtual void setEndEventUuidAndInitDto(QString qstrEndEventUuid, QObject *pEndEventDto) = 0;
    virtual QVariantList formatEventContent(QVariant qvClassContent, QVariant qvObjectContent) = 0;
    virtual QString getFormattedEventContentAsString(QVariantList qvlEventContent) = 0;
    virtual void DeleteContainersAfterSavingEvent(CdmContainerManager *pManager, CdmObjectContainer *pEventContainer) = 0;
    virtual void fireEvents(QObject* pEventDto) = 0;
};

#endif // IDMEVENTSTOREMANAGER_H
