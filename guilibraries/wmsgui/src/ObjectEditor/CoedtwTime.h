#ifndef COEDTWTIME_H
#define COEDTWTIME_H

// System and QT Includes



// own Includes
#include "CoeDataTypeWidget.h"

// forwards
class QTimeEdit;
class QComboBox;
class QLabel;
class QCheckBox;

class CoedtwTime : public CoeValueWidget
{
    Q_OBJECT

private:
    QTimeEdit* m_pqdeTime;
    // following member are needed for the search
    QComboBox* m_pqcbComboBox;
    QLabel*    m_pqlLabelFrom;
    QLabel*    m_pqlLabelTo;
    QTimeEdit* m_pqdDateEditFrom;
    QTimeEdit* m_pqdDateEditTo;
    QCheckBox* m_pqchbRelevant;

public:
    CoedtwTime(CdmValue* p_pCdmValue, QWidget* p_pqwParent = NULL);
    CoedtwTime(const CdmObject* pEventObject, CdmValue* p_pCdmValue, QWidget* p_pqwParent = NULL);
    virtual ~CoedtwTime();
    QWidget* GetEditWidget(QWidget* p_pqwParent);
    virtual void SetSearchDeaultValue(QString p_qstrDefault);
    virtual void SetReadOnly();
    virtual void SetEditable();
    CoedtwTime( CdmMember* p_pCdmMember, QString p_qstrKeyname, QWidget* p_pqwParent = NULL);
    virtual QWidget* GetSearchWidget(QWidget* p_pqwParent);
    virtual void AddQueryElement(CdmQueryElement* p_pCdmQueryElementParent);

protected slots:
    virtual void SetValue(CdmValue* p_pCdmValue);
    void setEventClassValue();

private:
    void AddQueryElementTo(CdmQueryElement* p_pCdmQueryElementParent, bool p_bUseFromEdit = true);
    void AddQueryElementFrom(CdmQueryElement* p_pCdmQueryElementParent);
    void AddQueryElementEqual(CdmQueryElement* p_pCdmQueryElementParent);
    void AddQueryElementFromTo(CdmQueryElement* p_pCdmQueryElementParent);

private slots:
    void RelevantCheckBoxClickedSlot();
    void CompareComboBoxIndexChangedSlot( int p_iIndex);
    void ValueChangedSlotByUser();

};

#endif //
