#ifndef COEDTWSTRING_H
#define COEDTWSTRING_H

// System and QT Includes



// own Includes
#include "CoeDataTypeWidget.h"

// forwards
class QLineEdit;
class QComboBox;

class CoedtwString : public CoeValueWidget
{

    Q_OBJECT

private:
    QLineEdit* m_pqleEdit;
    // following member are needed for the search
    QComboBox* m_pqcbComboBox;

public:
    CoedtwString(CdmValue* p_pCdmValue, QWidget* p_pqwParent = NULL);
    CoedtwString(const CdmObject *pCdmEventObject, CdmValue *p_pCdmValue, QWidget *p_pqwParent = NULL);
    virtual ~CoedtwString();
    QWidget* GetEditWidget(QWidget* p_pqwParent);
    virtual void SetReadOnly();
    virtual void SetEditable();
    CoedtwString(CdmMember* p_pCdmMember, QString p_qstrKeyname, QWidget* p_pqwParent = NULL);
    virtual QWidget* GetSearchWidget(QWidget* p_pqwParent);
    virtual void AddQueryElement(CdmQueryElement* p_pCdmQueryElementParent);
    virtual void SetSearchDeaultValue(QString p_qstrDefault);
    virtual void setEventClassValue();

protected slots:
    virtual void SetValue(CdmValue* p_pCdmValue);

private slots:
    void ValueChangedSlotByUser();
    void SearchClickedSlot();

};

#endif //
