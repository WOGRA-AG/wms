#ifndef CWMSFORMMANAGER_H
#define CWMSFORMMANAGER_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes
#include <QObject>

// Own Includes
#include "basetools.h"

// Forwards
class CdmContainerManager;

// TypeDefs


/* 
 * This class implements the manager for forms
 */
class BASETOOLS_API CwmsFormManager : public QObject
{

public:
    CwmsFormManager();
    virtual ~CwmsFormManager();
    CdmObjectContainer* GetFormSearchContainer();
    CdmObject* GeDefaultObjectForm(CdmObject* p_pCdmObject);
    CdmObject* GeDefaultContainerForm(CdmObjectContainer* p_pContainer);
    CdmObjectContainer* GetStandardFormContainer();
    CdmObjectContainer* GetGenericFormContainer();
    CdmObjectContainer* GetFormObjectObjectContainer();
    CdmObjectContainer* GetFormViewContainer();
    CdmObjectContainer* GetFormUserDefinedContainer();
    CdmObjectContainer* GetFormLibrary();
    QString GetClassUri(CdmModelElement* p_pElement);
    CdmObject *GetUserDefinedUiForElement(CdmModelElement *p_pElement);
    CdmObject *GetUserDefinedUi(CdmObject *p_pElement);
    CdmObject *GetUserDefinedUi(CdmObjectContainer *p_pElement);
    CdmObject *GetUserDefinedUi(QString p_qstrName);
    QString GetWmsLibrary(QString p_qstrName, QString p_qstrVersion);
    void CreateFormResourceClass(CdmClass* pCdmClassFormResources);
    QByteArray GetResource(QString p_qstrName, int p_iType);
    CdmObjectContainer *GetResourceContainer();
    CdmObjectContainer *GetInteractiveComponentContainer();
    CdmObject *GetUserDefinedUi(const CdmClass *p_pClass);

private:
    void CheckFormDataStructure();
    void CreateFormClasses(CdmClassManager* p_pCdmManager);
    void CreateFormBaseClass(CdmClass* p_pCdmClass);
    void CreateFormObjectListClass(CdmClass* p_pCdmClass);
    void CreateFormObjectClass(CdmClass* p_pCdmClass);
    void CreateFormUserDefinedClass(CdmClass* p_pCdmClass);
    void CreateFormViewClass(CdmClass* p_pCdmClass);
    void CreateFormStandardObjectListClass(CdmClass* p_pCdmClass);
    void CreateFormObjectObjectListClass(CdmClass* p_pCdmClass);
    CdmContainerManager* GetContainerManager();
    void CreateObjectContainer(CdmClass* p_pCdmClass, QString p_qstrKeyname);
    void CreateFormSearchClass(CdmClass* p_pCdmClass);
    void CreateFormLibrary(CdmClass* pCdmClassFormLibrary);
    QString GenerateWqlByName(QString p_qstrName, CdmObjectContainer *pContainer);
    QString GenerateWqlByClassUri(QString qstrClassUri, CdmObjectContainer* pContainer);
    QString GenerateLibraryWql(QString p_qstrName, QString p_qstrVersion, CdmObjectContainer *pContainer);
    QString GenerateResourceWql(QString p_qstrName, int p_type, CdmObjectContainer *pContainer);
    void CreateResource();
    void AddWqlMemberToClass(CdmClass *p_pClass);
    void CreateInteractiveComponentClass(CdmClass *pClass);
    void CreateInteractiveComponent();
    void UpdateUserdefinedUiClass(CdmClass *p_pClass);
    CdmObject *GetUserDefinedUiForClassUri(QString p_qstrClassUri);
    void UpdateTechnicalFormContainerClass(CdmClass *p_pClass);
};

#endif // CWMSFORMMANAGER_H
