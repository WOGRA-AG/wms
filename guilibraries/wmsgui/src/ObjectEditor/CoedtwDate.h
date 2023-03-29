#ifndef COEDTWDATE_H
#define COEDTWDATE_H

// System and QT Includes



// own Includes
#include "CoeDataTypeWidget.h"

// forwards
class QDateEdit;
class QComboBox;
class QLabel;
class QCheckBox;

class CoedtwDate : public CoeValueWidget
{
    Q_OBJECT

private:
    QDateEdit* m_pqdeDate;
    // folowing members are used for the search
    QComboBox* m_pqcbComboBox;
    QLabel*    m_pqlLabelFrom;
    QLabel*    m_pqlLabelTo;
    QDateEdit* m_pqdDateEditFrom;
    QDateEdit* m_pqdDateEditTo;
    QCheckBox* m_pqchbRelevant;

public:
    CoedtwDate(CdmValue* p_pCdmValue, QWidget* p_pqwParent = nullptr);
    CoedtwDate(const CdmObject *pEventObject, CdmValue* p_pCdmValue, QWidget* p_pqwParent = nullptr);
    virtual ~CoedtwDate();
    QWidget* GetEditWidget(QWidget* p_pqwParent);
    virtual void SetSearchDeaultValue(QString p_qstrDefault);
    virtual void SetReadOnly(  );
    virtual void SetEditable();
    CoedtwDate(CdmMember* p_pCdmMember, QString p_qstrKeyname, QWidget* p_pqwParent = nullptr);
    virtual QWidget* GetSearchWidget(QWidget* p_pqwParent);
    virtual void AddQueryElement(CdmQueryElement* p_pCdmQueryElementParent);

protected slots:
    virtual void SetValue(CdmValue* p_pCdmValue);
    void setEventClassValue();

private:
    void AddQueryElementEqual(CdmQueryElement* p_pCdmQueryElementParent);
    void AddQueryElementFrom(CdmQueryElement* p_pCdmQueryElementParent);
    void AddQueryElementTo(CdmQueryElement* p_pCdmQueryElementParent, bool p_bUseFromEdit = true);
    void AddQueryElementFromTo(CdmQueryElement* p_pCdmQueryElementParent);

private slots:
    void RelevantCheckBoxClickedSlot();
    void ValueChangedSlotByUser();
    void CompareComboBoxIndexChangedSlot(int p_iIndex);

};

#endif //
