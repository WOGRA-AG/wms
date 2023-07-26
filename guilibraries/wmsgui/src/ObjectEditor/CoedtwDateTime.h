#ifndef COEDTWDATETIME_H
#define COEDTWDATETIME_H

// System and QT Includes
#include <QDateTimeEdit>


// own Includes
#include "CoeDataTypeWidget.h"

// forwards
class QDateTimeEdit;
class QComboBox;
class QLabel;
class QCheckBox;

class CoedtwDateTime : public CoeValueWidget
{
    Q_OBJECT

private:
    QDateTimeEdit* m_pqdeDateTime;
    // following member are needed for the search
    QComboBox*     m_pqcbComboBox;
    QLabel*        m_pqlLabelFrom;
    QLabel*        m_pqlLabelTo;
    QDateTimeEdit* m_pqdDateEditFrom;
    QDateTimeEdit* m_pqdDateEditTo;
    QCheckBox* m_pqchbRelevant;


public:
    CoedtwDateTime(CdmValue* p_pCdmValue, QWidget* p_pqwParent = NULL);
    CoedtwDateTime(const CdmObject* pEventObject, CdmValue* p_pCdmValue, QWidget* p_pqwParent = nullptr);
    CoedtwDateTime(const CdmMember* p_pCdmMember, QString p_qstrKeyname, QWidget* p_pqwParent = nullptr);
    virtual ~CoedtwDateTime();
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
    void AddQueryElementFromTo(CdmQueryElement* p_pCdmQueryElementParent);
    void AddQueryElementTo(CdmQueryElement* p_pCdmQueryElementParent, bool p_bUseFromEdit = true);
    void AddQueryElementFrom(CdmQueryElement* p_pCdmQueryElementParent);
    void AddQueryElementEqual(CdmQueryElement* p_pCdmQueryElementParent);

private slots:
    void RelevantCheckBoxClickedSlot();
    void ValueChangedSlotByUser();
    void CompareComboBoxIndexChangedSlot(int p_iIndex);

};

#endif //
