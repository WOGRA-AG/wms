#ifndef COEDTWUSERGROUP_H
#define COEDTWUSERGROUP_H

// System and QT Includes
#include <QPushButton>


// own Includes
#include "CoeDataTypeWidget.h"

// forwards
class QLineEdit;
class QComboBox;

class CoedtwUserGroup : public CoeValueWidget
{
    Q_OBJECT

private:
    QPushButton* m_pqbButton;
    QLineEdit* m_qleGroup;
    qint64 m_lCurrentGroupId;

public:
    CoedtwUserGroup( CdmValue* p_pCdmValue, QWidget* p_pqwParent = NULL);
    CoedtwUserGroup(const CdmObject *pEventObject, CdmValue* p_pCdmValue, QWidget* p_pqwParent = NULL);
    CoedtwUserGroup(const CdmMember* p_pCdmMember, QString p_qstrKeyname, QWidget* p_pqwParent = NULL);
    virtual ~CoedtwUserGroup( );
    QWidget* GetEditWidget(QWidget* p_pqwParent);
    virtual void SetReadOnly();
    virtual void SetEditable();
    virtual QWidget* GetSearchWidget(QWidget* p_pqwParent);
    virtual void AddQueryElement(CdmQueryElement* p_pCdmQueryElementParent);

protected slots:
    virtual void SetValue(CdmValue* p_pCdmValue);
    void setEventClassValue();

private slots:
    void ValueChangedSlotByUser( );
    void openNewWindow();

};

#endif //
