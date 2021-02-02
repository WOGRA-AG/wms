#ifndef CWMSCONTAINERUPDATELOCKER_H
#define CWMSCONTAINERUPDATELOCKER_H

#include <CdmContainerAdaptor.h>
#include <QLinkedList>

#include "wmsgui.h"

class WMSGUI_API CwmsContainerUpdateLocker
{

    private:
        QString m_qstrContainerKeyname;
        QLinkedList<CdmContainerAdaptor*> m_qllOriginalContainers;
        QLinkedList<CdmContainerAdaptor*> m_qllAdaptorExceptions; // this adaptors needs updates
        bool m_bForceUpdateOnDestruction;

        void RemoveAdaptorsFromContainer(CdmObjectContainer* p_pContainer);
public:
        CwmsContainerUpdateLocker(QString p_qstrContainerKeyname, bool p_bForceUpdateOnDestruction);
        CwmsContainerUpdateLocker(bool p_bForceUpdateOnDestruction);
        CdmObjectContainer *GetContainer();
        void StopUpdates();
        void EnableUpdates();
        void ForceUpdates();
        void AddUpdateException(CdmContainerAdaptor *p_pAdaptor);
        void GetAdaptorsFromContainer(CdmObjectContainer *p_pContainer);
        virtual ~CwmsContainerUpdateLocker();
        void SetContainer(QString p_qstrContainer);
};

#endif // CWMSCONTAINERUPDATELOCKER_H
