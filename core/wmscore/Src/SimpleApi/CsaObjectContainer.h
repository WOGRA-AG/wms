/******************************************************************************
 ** WOGRA Middleware Server Data Manager Module
 **
 ** @Author Wolfgang Graßhof
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 **(C) copyright by WOGRA technologies All rights reserved
 ******************************************************************************/


#ifndef CSCRIPTOBJECTCONTAINER
#define CSCRIPTOBJECTCONTAINER

// System and QT Includes
#include <QScriptValue>

// own Includes
#include "datamanager.h"
#include "CsaModelElement.h"

// Forwards
class CsaFactory;
class CsaObject;
class CdmObjectContainer;

class WMSMANAGER_API CsaObjectContainer : public CsaModelElement
{
    Q_OBJECT
    friend class CsaFactory;

    public slots:
        QObject* findObjectById(int p_iId);
        QObject *findObjectByKeyname(QString qstr_Keyname);
        QObject* copyObject(CsaObject* p_pObject);
        QObject* createObject();
        QObject* createObject(QString p_qstrKeyname);
        int commit();
        int countOverallObjects();
        int countLocalObjects();

        QVariantList getObjectList();
        void deleteObject(CsaObject* p_pObject);
        void clearContainer();
        void clearContainerLocal();
        bool isTree();
        void setTree(bool p_bTree);
        bool hasOwner();
        void loadContainerComplete();
        CsaObject *getOwner();
        void setImmutable(bool p_bImmutable);
        bool isImmutable();
        bool hasCurrentUserWriteAccess();
        bool hasCurrentUserReadAccess();
public:
        CdmObjectContainer* getInternals();
        CsaObjectContainer(CdmObjectContainer* p_pContainer, bool p_bThis = false);
        ~CsaObjectContainer();
        CsaObjectContainer():CsaModelElement(NULL), m_bThis(false){}
        QVariant getDetailedVariant();

private:
         bool m_bThis;
};

#endif //
