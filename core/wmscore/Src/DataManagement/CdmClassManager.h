/******************************************************************************
 ** WOGRA Middleware Server Data Manager Module
 **
 ** @Author Wolfgang Graßhof
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 **(C) copyright by WOGRA technologies All rights reserved
 ******************************************************************************/

#ifndef CDMCLASSMANAGER_H
#define CDMCLASSMANAGER_H

// System and QT Includes
#include <qmap.h>
#include <QVariant>
#include <QList>


// own Includes
#include "CdmModelElementBase.h"



// forwards
class CdmPackage;
class QDomElement;
template<class T> class QLinkedList;

/*
 * This class manages the class of a virtual database
 */
class WMSMANAGER_API CdmClassManager : public CdmModelElementBase 
{
    Q_OBJECT

    friend class IdmDataAccess;
    friend class CdmDataAccessHelper;
    friend class CdmGlobalContext;

private:
    QMap<long,CdmClass*> m_qmClasses;
    QList<CdmPackage*> m_qlPackages;

private:
    CdmClassManager(long p_lDbId);
    virtual ~CdmClassManager();

public:
    int GetInheritedClasses(CdmClass* p_pCdmBaseClass, QLinkedList<CdmClass*>& p_rqvlClassList);
    CdmClass* CreateClass(QString p_qstrKeyname);
    int DeleteClass(long p_lId);
    int DeleteClass(CdmClass* p_pCdmClass);
    long GetNewClassId();
    int XmlExport(QDomElement& p_rqdeClassManager) const;
    int XmlImport(QDomElement& p_rqdeClassManager);
    QVariant GetVariant() const;
    void SetVariant(QVariant p_qvClasses);
    void Deploy(QVariantMap& p_rqvHash);
    CdmPackage* CreatePackage(QString p_qstrName);
    CdmPackage* CreatePackage(QString p_qstrName, CdmPackage* p_pParent);
    CdmPackage* FindPackageByName(QString p_qstrPackage);
    CdmPackage* FindPackageById(long p_lId);
    void DeletePackage(CdmPackage* p_pPackage);
    void MoveClassToPackage(CdmClass* p_pClass, CdmPackage* p_pPackage);
    void UpdateModifiedClasses();
    CdmPackage *FindPackageByUri(QString p_qstrPackage);
    QList<CdmPackage *> GetPackageList();
    CdmClass *CreateClass(QString p_qstrKeyname, CdmPackage *p_pPackage);
    bool ExistPackage(QString p_qstrPackage);
    CdmPackage *FindPackageByClassUri(QString p_qstrUri);
    void DeployPackages(QVariantMap& p_rqvHash);
    void DeployClasses(QVariantMap& p_rqvHash);
    QString GetUri() const;
    bool IsClassManager() const;
    QString GetUriInternal() const;
    QList<CdmClass *> getEventClassList();
    CdmClass *findEventClassByKeyname(QString qstrKeyname);
    int DeleteClass(QString p_qstrClassName);
    CdmClass* FindClassByKeyname( QString p_qstrKeyname);
    CdmClass* FindClassByKeyname(CdmPackage* p_pPackage, QString p_qstrKeyname);
    CdmClass* FindClassById(long p_lId);
    void GetClassList( QLinkedList<CdmClass*>& p_pqlClasses);
    int ExistClass(QString p_qstrClassKeyname) const;
    void GenerateClassDocumentation( QString p_qstrDatabase, QString p_qstrFilename) const;

private:
    CdmClass* CreateClass(long p_lId, QString p_qstrKeyname);
    int AddClass(CdmClass* p_pCdmClass);
    int XmlImportClass(QDomElement& p_rqdeElement);
    void AddPackage(CdmPackage *p_pPackage);
    CdmClass *CreateClassWithoutCheck(QString p_qstrKeyname);
    void CreateClassVariant(CdmClass* pCdmClass, QStringList& qstrlClasses, QVariantList& p_rqlMap) const;
};
#endif
