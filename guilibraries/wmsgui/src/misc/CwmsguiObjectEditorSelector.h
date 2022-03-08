#ifndef CWMSGUIOBJECTEDITORSELECTOR_H
#define CWMSGUIOBJECTEDITORSELECTOR_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes

// WMS Includes
#include "CdmObjectAdaptor.h"

// Own Includes
#include "wmsgui.h"

// Forwards
class IwmsObjectEditorDescriptor;
class IwmsObjectListEditorDescriptor;

// Enumerations
enum EwmsGuiDisplayMode
{
    eWmsGuiDisplayModeNew,
    eWmsGuiDisplayModeWrite,
    eWmsGuiDisplayModeRead
};

//defs
#define WMS_NEW "newObject"
#define WMS_DELETE "deleteObject"
#define WMS_UPDATE "updateObject"

// TypeDefs


/* 
 * This class implements the choices the right editor for editing a given object.
 */
class WMSGUI_API CwmsguiObjectEditorSelector
{
private:
    static CwmsguiObjectEditorSelector* m_pSelector;
    QMap<QString, IwmsObjectEditorDescriptor*> m_qmObjectDescriptors;
    QMap<QString, IwmsObjectListEditorDescriptor*> m_qmObjectListDescriptors;

public:
    static bool Create(CdmObject* p_pCdmObject, QWidget* p_pqwParent);
    static bool Create(CdmObjectAdaptor& p_CdmObjectAdaptor, QWidget* p_pqwParent);
    static bool Edit(CdmObject* p_pCdmObject, QWidget* p_pqwParent);
    static bool Edit(CdmObjectAdaptor p_CdmObjectAdaptor, QWidget* p_pqwParent);
    static bool Edit(CdmObjectContainer* p_pContainer, QWidget* p_pqwParent);
    static bool View(CdmObject* p_pCdmObject, QWidget* p_pqwParent);
    static bool View(CdmObjectAdaptor p_CdmObjectAdaptor, QWidget* p_pqwParent);
    static bool View(CdmObjectContainer* p_pContainer, QWidget* p_pqwParent);
    static void InstallObjectEditorDescriptor(IwmsObjectEditorDescriptor* p_pDescriptor);
    static void InstallContainerEditorDescriptor(IwmsObjectListEditorDescriptor* p_pDescriptor);
    static void Init();

protected:
    static CwmsguiObjectEditorSelector* GetSelector();
    virtual bool DisplayObjectEditor(CdmObject* p_pCdmObject,
                                     EwmsGuiDisplayMode p_eDisplayMode,
                                     QWidget* p_pqwParent);
    virtual bool DisplayContainerEditor(CdmObjectContainer* p_pContainer,
                                        EwmsGuiDisplayMode p_eDisplayMode,
                                        QWidget* p_pqwParent);

    bool ExistUserdefinedForm(const CdmClass* p_pClass);

private:
    CwmsguiObjectEditorSelector();
    virtual ~CwmsguiObjectEditorSelector();
    bool DisplayDefaultObjectEditor(CdmObject* p_pCdmObject,
                                    EwmsGuiDisplayMode p_eDisplayMode,
                                    QWidget* p_pqwParent);
    bool HasConfiguredObjectEditor(CdmObject* p_pCdmObject);
    bool DisplayConfiguredObjectEditor(CdmObject* p_pCdmObject,
                                       EwmsGuiDisplayMode p_eDisplayMode,
                                       QWidget* p_pqwParent);
    bool DisplayUserdefinedForm(CdmObject* p_pCdmObject, QWidget* p_pqwParent);
    bool DisplayUserdefinedForm(CdmObjectContainer *p_pCdmObject, QWidget *p_pqwParent);
};

#endif // CWMSGUIOBJECTEDITORSELECTOR_H
