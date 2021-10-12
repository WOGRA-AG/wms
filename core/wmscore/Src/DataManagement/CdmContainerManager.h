/******************************************************************************
 ** WOGRA Middleware Server Data Manager Module
 **
 ** @Author Wolfgang Graßhof
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 **(C) copyright by WOGRA technologies All rights reserved
 ******************************************************************************/

#ifndef CDMOBJECTLISTMANAGER_H
#define CDMOBJECTLISTMANAGER_H


// System and QT Includes
#include <qmap.h>
#include <QList>
#include <QVariantList>


// own Includes
#include "CdmModelElementBase.h"

// forwards
class QDomElement;
class CdmObjectContainer;
class CdmClass;



/*
 * This class manages the loaded objectlists in the client
 */
class WMSMANAGER_API CdmContainerManager : public CdmModelElementBase
{
    Q_OBJECT

    friend class CdmScheme;


private:    
    QMap<qint64,CdmObjectContainer*>  m_qmContainer;
    QList<QString> m_qlToResolve;

private:
    CdmContainerManager(qint64 p_lDatabaseId);

public:
    virtual ~CdmContainerManager(); // can not be private because qthreadstorage deletes this pointer
    QVariant GetVariant() const;
    void Commit();
    CdmObjectContainer* FindContainerByIdLocal(qint64 p_lObjectListId);
    virtual QString GetUri() const;
    bool IsContainerManager() const;
    QString GetUriInternal() const;
    CdmObject *FindObject(qint64 p_lContainerId,qint64 p_lObjectId);
    void GetDeploymentVariant(CdmClass* p_pClass, QVariantList& p_rqvObjectContainers) const;
    void Deploy(QVariantList& p_rqvList);
    void AddDeploymentResolveValue(CdmValue* p_pCdmValue);
    int CreateContainer(CdmClass* p_pCdmClass, QString& p_qstrKeyname);
    int CreateContainer(qint64 p_lClassId, QString& p_qstrKeyname);
    CdmObjectContainer* FindContainerById(qint64 p_lObjectListId);
    CdmObjectContainer* FindContainerByKeyname( QString p_qstrKeyname);
    int DeleteContainer(CdmObjectContainer* p_pContainer);
    int DeleteContainer(qint64 p_lObjectListId);
    int DeleteContainer(QString p_qstrKeyname);
    CdmObjectContainer* FindEmptyContainerByKeyname( QString p_qstrKeyname);
    void RemoveContainerLocally();
    void RemoveContainerLocally(CdmObjectContainer* p_pContainer);
    void RemoveContainerLocally(qint64 p_lObjectListId);
    void RemoveContainerLocally(QString p_qstrName);
    CdmObjectContainer* CopyContainer(CdmObjectContainer* p_pCdmObjetList, bool p_bComplete);
    CdmObjectContainer* CopyContainer(qint64 p_lObjetListId, bool p_bComplete);
    CdmObjectContainer* CopyContainer(QString p_qstrKeyname, bool p_bComplete);
    int CreateContainer(QString p_qstrClassKeyname, QString& p_qstrObjectListKeyname);
    CdmObjectContainer* FindEmptyContainerById(qint64 p_lId);
    QList<QString> GetContainerList(qint64 p_lClassId);
    QList<QString> GetContainerList(QString p_qstrClassKeyName);
    int CreateContainer(QString p_qstrClassKeyname,
                        QString& p_qstrObjectListKeyname,
                        QString p_qstrObjectListCaption,
                        QString p_qstrObjectListComment);
    CdmObjectContainer* ReloadContainerComplete(qint64 p_lObjectListId);
    void ReloadContainerComplete(CdmObjectContainer*& p_rpContainer);
    int CreateContainer(QString p_qstrClassKeyname,
                        QString& p_qstrObjectListKeyname,
                        QString p_qstrObjectListCaption,
                        QString p_qstrObjectListComment,
                        bool p_bTree);

private:
    void DeploymentResolveValue();
    void DeployNewContainer(QString qstrClassUri, QString qstrKeyname, QVariantMap qvObjectList);
   qint64 GetNewContainerId(qint64 p_lClassId);
};

#endif
