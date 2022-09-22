#ifndef CWMSGUIOBJECTLISTOVERVIEWIF_H
#define CWMSGUIOBJECTLISTOVERVIEWIF_H


// System and QT Includes
#include <QDialog>

// own Includes
#include "wmsgui.h"
#include "CdmModelElement.h"
#include "ui_cwmsguiobjecteditor.h"
#include "IdmEventStoreManager.h"

// defines
#ifndef NEW
#define NEW "new"
#endif

#ifndef DELETE
#define DELETE "delete"
#endif

#ifndef UPDATE
#define UPDATE "update"
#endif

// forwards
class CdmObject;
class CwmsguiValidator;

class WMSGUI_API CwmsguiObjectEditorIf : public QDialog, public Ui::CwmsguiObjectEditor
{
    Q_OBJECT

private:
    CwmsguiValidator* m_rpCwmsValidator;
    CdmObject* m_rpCdmObject;
    QString m_qstrObjectEventMode;

public:
    CwmsguiObjectEditorIf(CdmObject* p_pCdmObject, QWidget* parent = NULL);
    virtual ~CwmsguiObjectEditorIf();
    void FillDialog();
    void AddHiddenValue(QString p_qstrValue);
    void AddReadOnlyValue(QString p_qstrValue);
    void AddObjectRefData(QString p_qstrValue, QString p_qstrObjectList, QString p_qstrDisplayValue);
    void SetDisplayType(QString p_qstrValue, EdmStringDisplayType p_eOeDisplayType);
    void SetValidator(CwmsguiValidator* p_pCwmsguiValidator);
    void SetSortedList(QStringList p_qstrlSorting);
    void SetCaptionValue(QString p_qstrValue);
    void AddProxy(QString p_qstrKeyname, CdmQueryModel* p_pCwmsProxy);
    void SetReadOnly();
    void SetFormConfiguration(CdmObject* p_pObject);
    void SetObjectEventMode(QString qstr_EventMode);
    QString GetObjectEventMode() const;

    void AddObjectRefData(QString p_qstrValue, QString p_qstrWql);
protected slots:
    void OKClickedSlot();

private:
    CdmObjectContainer *findValueObjectContainer();
    CdmObjectContainer *getValueObjectContainer();

};

#endif //
