#ifndef COEDTWUSER_H
#define COEDTWUSER_H

// System and QT Includes
#include <QPushButton>
#include <QTreeWidget>

// own Includes
#include "CoeDataTypeWidget.h"
#include "CumUser.h"

// forwards
class QLineEdit;
class QComboBox;

class CoedtwUser : public CoeValueWidget
{
    Q_OBJECT

private:
    QPushButton* m_pqbButton;
    QPushButton* m_pqpbClear;
    QLineEdit* m_pqleUser;
    qint64 m_lCurrentUserId;

public:
    CoedtwUser( CdmValue* p_pCdmValue, QWidget* p_pqwParent = NULL);
    CoedtwUser(const CdmObject *pEventObject, CdmValue* p_pCdmValue, QWidget* p_pqwParent = NULL);
    CoedtwUser( CdmMember* p_pCdmMember, QString p_qstrKeyname, QWidget* p_pqwParent = NULL);
    virtual ~CoedtwUser( );
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
    void ClearClickedSlot();

};

#endif
