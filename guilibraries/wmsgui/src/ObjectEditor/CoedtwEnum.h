#ifndef COEDTWENUM_H
#define COEDTWENUM_H

// System and QT Includes



// own Includes
#include "CoeDataTypeWidget.h"

// forwards
class QLineEdit;
class QComboBox;

class CoedtwEnum : public CoeValueWidget
{
    Q_OBJECT

private:
    QComboBox* m_pqcbComboBox;

public:
    CoedtwEnum(CdmValue* p_pCdmValue, QWidget* p_pqwParent = NULL);
    CoedtwEnum(const CdmObject *pEventObject, CdmValue* p_pCdmValue, QWidget* p_pqwParent = NULL);
    CoedtwEnum(const CdmMember* p_pCdmMember, QString p_qstrKeyname, QWidget* p_pqwParent = NULL);
    virtual ~CoedtwEnum();
    QWidget* GetEditWidget(QWidget* p_pqwParent);
    virtual void SetReadOnly();
    virtual void SetEditable();
    virtual QWidget* GetSearchWidget(QWidget* p_pqwParent);
    virtual void AddQueryElement(CdmQueryElement* p_pCdmQueryElementParent);

protected slots:
    virtual void SetValue(CdmValue* p_pCdmValue);
    void setEventClassValue();

private:
    void AddSelectionValuesToComboBox();

private slots:
    void ValueChangedSlotByUser( );



};

#endif //
