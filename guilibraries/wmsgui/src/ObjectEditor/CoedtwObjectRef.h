#ifndef COEDTWOBJECTREF_H
#define COEDTWOBJECTREF_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes



// own Includes
#include "CoeDataTypeWidget.h"

// forwards
class QLineEdit;
class QPushButton;
class CdmObjectContainer;
class CwmsObjectChoiceComboBox;
class CdmQueryModel;
class CwmsObjectEditor;


class CoedtwObjectRef : public CoeValueWidget
{
    Q_OBJECT

private:

    CwmsObjectChoiceComboBox* m_pqcbObjectChoice;
    QPushButton* m_pqpbSelect;
    QPushButton* m_pqpbEdit;
    QPushButton* m_pqpbClear;
    bool m_bProxyCreatedByThis;
    QLineEdit* m_pqleObject;
    bool m_bShowEditButton;
    CdmQueryModel* m_pCwmsProxy;
    CwmsObjectEditor* m_pObjectEditor;
    QString m_qstrObjectList;
    QString m_qstrVisibleKeyname;

public:
    CoedtwObjectRef( CdmValue* p_pCdmValue, QWidget* p_pqwParent = NULL);
    CoedtwObjectRef(const CdmObject *pEventObject, CdmValue* p_pCdmValue, QWidget* p_pqwParent = NULL);
    virtual ~CoedtwObjectRef(  );
    QWidget* GetEditWidget(QWidget* p_pqwParent);
    CdmObjectContainer* GetSingleObjectList(  );
    void HideEditButton();
    void SetProxy(CdmQueryModel *p_pCwmsProxy);
    virtual QWidget* GetTabEditWidget(QWidget* p_pqwParent);
    void SetProxy(QString p_qstrWql);
    void GetSelectionEdit(QHBoxLayout* pqLayout, QWidget* pqWidget);
    void GetComboBoxEdit(QWidget *pqWidget, QHBoxLayout *pqLayout);
    virtual void SetReadOnly(  );
    virtual void SetEditable();
    void SetContainer(  QString p_qstrObjectList, QString p_qstrVisibleKeyname );

protected slots:
    virtual void SetValue(  CdmValue* p_pCdmValue );
    void setEventClassValue();

private:
    void GetComboBoxEdit(CdmObjectContainer* pContainer, QWidget* pqWidget, QHBoxLayout* pqLayout);

private slots:
    void ValueChangedSlotByUser(  );
    void EditClickedSlot(  );
    void ChooseClickedSlot(  );
    void ClearClickedSlot();

};

#endif //
