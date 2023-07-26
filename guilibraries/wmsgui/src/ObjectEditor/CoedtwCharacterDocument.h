#ifndef COEDTWCHARACTERDOCUMENT_H
#define COEDTWCHARACTERDOCUMENT_H

// System and QT Includes



// own Includes
#include "CoeDataTypeWidget.h"

// forwards
class QTextEdit;
class QPushButton;
class CoeTextEditMainWindow;

class CoedtwCharacterDocument : public CoeValueWidget
{
    Q_OBJECT

private:
    QTextEdit* m_pqteTextEdit;
    CoeTextEditMainWindow* m_pTextEdit;
    QPushButton* m_pqpbEdit;


public:
    CoedtwCharacterDocument( CdmValue* p_pCdmValue, QWidget* p_pqwParent = NULL);
    CoedtwCharacterDocument(const CdmObject *pEventObject, CdmValue* p_pCdmValue, QWidget* p_pqwParent = NULL);
    virtual ~CoedtwCharacterDocument();
    QWidget* GetEditWidget(QWidget* p_qwParent);
    virtual void SetReadOnly();
    virtual void SetEditable();
    virtual QWidget* GetTabEditWidget(QWidget* p_pqwParent);

protected slots:
    virtual void SetValue(CdmValue* p_pCdmValue);
    void setEventClassValue();

private slots:
    void ValueChangedSlotByUser();
    void EditClickedSlot();

};

#endif //
