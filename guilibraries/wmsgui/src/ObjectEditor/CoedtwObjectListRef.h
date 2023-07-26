#ifndef COEDTWOBJECTLISTREF_H
#define COEDTWOBJECTLISTREF_H

// System and QT Includes

// own Includes
#include "CoeDataTypeWidget.h"

// forwards
class QLineEdit;
class QPushButton;
class CwmsObjectListEditorWidgetIf;


class CoedtwContainerRef : public CoeValueWidget
{
    Q_OBJECT

private:
    QLineEdit* m_pqleEdit;
    QPushButton* m_pqpbChange;
    QPushButton* m_pqpbClear;
    QPushButton* m_pqpbView;
    CwmsObjectListEditorWidgetIf* m_pObjectListEditor;
    qint64 m_lContainerId;

public:
    CoedtwContainerRef(CdmValue* p_pCdmValue, QWidget* p_pqwParent = nullptr);
    CoedtwContainerRef(const CdmMember *p_pCdmMember, QString p_qstrKeyname, QWidget *p_pqwParent);
    CoedtwContainerRef(const CdmObject *pEventObject, CdmValue* p_pCdmValue, QWidget* p_pqwParent = nullptr);
    virtual ~CoedtwContainerRef();
    QWidget* GetEditWidget(QWidget* p_pqwParent);
    virtual void SetReadOnly();
    virtual void SetEditable();
    virtual QWidget* GetTabEditWidget(QWidget* p_pqwParent);

    void AddQueryElement(CdmQueryElement *p_pCdmQueryElementParent);
    QWidget *GetSearchWidget(QWidget *p_pqwParent);
    void SetSearchDeaultValue(QString p_qstrDefault);
protected slots:
    virtual void SetValue(CdmValue* p_pCdmValue);
    void setEventClassValue();

private slots:
    void ValueChangedSlotByUser();
    void ChangeClickedSlot();
    void EditClickedSlot();
    void ClearClickedSlot();
};

#endif
