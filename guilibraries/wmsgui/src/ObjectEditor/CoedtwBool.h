#ifndef COEDTWBOOL_H
#define COEDTWBOOL_H

// System and QT Includes



// own Includes
#include "CoeDataTypeWidget.h"

// forwards
class QCheckBox;


class CoedtwBool : public CoeValueWidget
{
    Q_OBJECT

private:
    QCheckBox* m_pqchbCheckbox;

public:
    CoedtwBool( CdmValue* p_pCdmValue, QWidget* p_pqwParent = NULL);
    CoedtwBool(const CdmObject *pEventObject, CdmValue *p_pCdmValue, QWidget *p_pqwParent = NULL);
    CoedtwBool(const CdmMember* p_pCdmMember, QString p_qstrKeyname, QWidget* p_pqwParent = NULL);
    virtual ~CoedtwBool();
    QWidget* GetEditWidget(QWidget* p_pqwParent);
    virtual void SetReadOnly();
    virtual void SetEditable();
    virtual QWidget* GetSearchWidget(QWidget* p_pqwParent);
    virtual void AddQueryElement(CdmQueryElement* p_pCdmQueryElementParent);
    virtual void SetSearchDeaultValue(QString p_qstrDefault);

protected slots:
    virtual void SetValue(CdmValue* p_pCdmValue);
    void setEventClassValue();

private slots:
    void ValueChangedSlotByUser();

};

#endif //
