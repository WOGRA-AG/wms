#ifndef COEDTWDOUBLE_H
#define COEDTWDOUBLE_H

// System and QT Includes



// own Includes
#include "CoeDataTypeWidget.h"

// forwards
class QLineEdit;
class QComboBox;
class QLabel;


class CoedtwDouble : public CoeValueWidget
{

    Q_OBJECT

private:
    QLabel* m_pqlPrefix;
    QLabel* m_pqlSuffix;
    QLineEdit* m_pqleEdit;
    // following member are needed for the search
    QComboBox* m_pqcbComboBox;
    QLabel*    m_pqlLabelFrom;
    QLabel*    m_pqlLabelTo;
    QLineEdit* m_pqleTo;

public:
    CoedtwDouble(CdmValue* p_pCdmValue, QWidget* p_pqwParent = nullptr);
    CoedtwDouble(const CdmMember* p_pCdmMember, QString p_qstrKeyname, QWidget* p_pqwParent = nullptr);
    CoedtwDouble(const CdmObject* pEventObject, CdmValue* p_pCdmValue, QWidget* p_pqwParent = nullptr);
    virtual ~CoedtwDouble();
    QWidget* GetEditWidget(QWidget* p_pqwParent);
    virtual void SetReadOnly();
    virtual void SetEditable();
    virtual QWidget* GetSearchWidget(QWidget* p_pqwParent);
    virtual void AddQueryElement(CdmQueryElement* p_pCdmQueryElementParent);
    virtual void SetSearchDeaultValue(QString p_qstrDefault);

protected slots:
    virtual void SetValue(CdmValue* p_pCdmValue);
    void setEventClassValue();

private:
    void AddQueryElementFromTo(CdmQueryElement *p_pCdmQueryElementParent);
    void AddQueryElementTo(CdmQueryElement *p_pCdmQueryElementParent);
    void AddQueryElementFrom(CdmQueryElement *p_pCdmQueryElementParent);

private slots:
    void CompareComboBoxIndexChangedSlot(int p_iIndex);
    void ValueChangedSlotByUser();
};

#endif
