/******************************************************************************
 ** WOGRA Middleware Server Data Manager Module
 **
 ** @Author Wolfgang Graßhof
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 **(C) copyright by WOGRA technologies All rights reserved
 ******************************************************************************/

#ifndef CSAFACTORY_H
#define CSAFACTORY_H

// System and QT Includes
#include <QMap>
#include <QObject>

// own Includes
#include "datamanager.h"
#include "CdmClassMethod.h"
#include "CsaModelElement.h"

// Forwards
class IdmExecutorEngine;
class CdmModelElement;
class CdmLocatedElement;
class CdmObject;
class CdmObjectContainer;
class CdmClass;
class CumAccessor;
class CsaModelElement;
class CsaLocatedElement;
class CsaScheme;
class CsaClassManager;
class CsaQuery;
class CsaQueryModel;
class CsaObjectContainer;
class CsaObject;
class CsaContainerManager;
class CsaManager;
class CsaResultObject;

class WMSMANAGER_API CsaFactory : public QObject
{
    Q_OBJECT
private:
    IdmExecutorEngine* m_rpEngine;
    QMap<QString, CsaLocatedElement*> m_CollectorMap;
    QList<QObject*> m_qlGarbageColectionObjects;
    CsaScheme* m_pScheme;
    CsaClassManager* m_pClassManager;
    CsaContainerManager* m_pContainerManager;
    CsaManager* m_pManager;

private:
    CsaLocatedElement* createScriptObjectInternal(CdmLocatedElement* p_pElement, bool p_bThis);
    void addFormulaMembersToEngine(CdmObject* p_pCdmObject);

public:
    CsaFactory();
    CsaFactory(IdmExecutorEngine* p_pEngine);
    virtual ~CsaFactory();
    CsaLocatedElement* createThisScriptObject(CdmObject* p_pElement);
    CsaScheme* getScheme();
    void createFormulaScriptObject(CdmObject *p_pCdmObject);
    void throwError(QString p_qstrException);
    IdmExecutorEngine *getEngine();
    void setEngine(IdmExecutorEngine* p_pEngine);

    static CsaObjectContainer *convertContainer(CdmObjectContainer *p_pContainer, CsaFactory *p_pFactory);
    static CsaObject *convertObject(CdmObject *p_pObject, CsaFactory *p_pFactory);
    static CsaFactory* getCurrentFunctionFactory();

    CsaResultObject *createResultObject();
    static QVariant convertToResultVariant(const QVariant &p_rQVariant);
    static QVariant convertToResultVariantForSubMethodCalls(const QVariant &p_rQVariant);
public slots:
    CsaLocatedElement* createScriptObject(CdmLocatedElement* p_pElement);
    CsaClassManager* getClassManager();
    CsaContainerManager* getContainerManager();
    CsaManager* getManager();
    CsaQuery* createQuery(QString p_qstrWQl);
    void collectGarbage();
    CsaQuery *createQuery(CdmQuery *p_pQuery);
    QObject *findObjectById(int pOlId, int pId);
    void addObjectForGarbageCollection(QObject *p_pObject);
    QStringList getArguments();
};

#endif //
