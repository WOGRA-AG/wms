/******************************************************************************
 ** WOGRA Middleware Server Data Manager Module
 **
 ** @Author Wolfgang Graßhof
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 **(C) copyright by WOGRA technologies All rights reserved
 ******************************************************************************/

#ifndef CSCRIPTCONTAINERMANAGER
#define CSCRIPTCONTAINERMANAGER

// System and QT Includes
#include <QList>

// own Includes
#include "datamanager.h"
#include "CsaLocatedElement.h"

// Forwards
class CsaFactory;
class CdmObjectContainer;
class CdmContainerManager;
class CsaClass;
class CsaObjectContainer;

class WMSMANAGER_API CsaContainerManager : public CsaLocatedElement
{
    Q_OBJECT

    friend class CsaFactory;
private:
    virtual ~CsaContainerManager();
    CsaContainerManager(CdmContainerManager* p_pContainerManager);
    QString createNewKeyname();
    CdmContainerManager* m_pContainerManager;
public:
    CdmContainerManager* getInternals();

public slots:
    QObject* findContainerById(int p_iId);
    QObject* findContainerByKeyname(QString p_qstrKeyname);
    QObject* findEmptyContainerById(int p_iId);
    QObject* findEmptyContainerByKeyname(QString p_qstrKeyname);
    QObject* createContainer(QString p_qstrClassKeyname);
    QObject* createContainer(QString p_qstrKeyname, QString p_qstrClassKeyname);
    QObject* createContainer(QString p_qstrKeyname, CsaClass* p_pClass);
    QObject* createContainer(CsaClass* p_pClass);
    QObject* copyContainer(CsaObjectContainer* p_pContainer, bool p_bComplete);
    QVariantList getContainerList(QString p_qstrClassName);
    QObject* reloadContainerComplete(CsaObjectContainer* p_pContainer);
    void removeContainerLocal(CsaObjectContainer* p_pContainer);
    void deleteContainer(CsaObjectContainer* p_pContainer);


    // CsaLocatedElement interface
public:
    virtual QVariant getDetailedVariant();

};

#endif //
