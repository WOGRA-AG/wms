#ifndef COEValueWIDGET_H
#define COEValueWIDGET_H


// System and QT Includes
#include <QObject>
#include <QFormLayout>

// WMS Includes
#include "CdmQuery.h"
#include "CdmQueryElement.h"

// own Includes
#include "wmsgui.h"

// forwards
class QHBoxLayout;
class QLabel;
class QLineEdit;
class CdmValue;
class QWidget;
class CdmMember;


class WMSGUI_API CoeValueWidget : public QObject
{
    Q_OBJECT

protected:
    EdmStringDisplayType m_eOeDisplayType;
    CdmValue* m_rpCdmValue;
    const CdmMember* m_rpCdmMember;
    QString m_qstrKeyname;
    QLineEdit* m_rpqleCaption;
    QHBoxLayout* m_pqhbLayout;
    static QList<CdmValue*> m_qlEventClassValues;

private:
    QLabel* m_pqlLabel;

public:
    CoeValueWidget(CdmValue* p_pCdmValue, QWidget* p_pqwParent = nullptr);
    CoeValueWidget(const CdmObject *pCdmEventObject, CdmValue *p_pCdmValue, QWidget *p_pqwParent = nullptr);
    CoeValueWidget(CdmMember* p_pCdmMember, QString p_qstrKeyname, QWidget* p_pqwParent = nullptr);
    virtual ~CoeValueWidget();
    virtual QWidget* GetEditWidget(QWidget* p_pqwParent)= 0;
    static CoeValueWidget* CreateValueWidget(CdmValue* p_pCdmValue, QWidget* p_pqwParent);
    virtual void SetReadOnly(  );
    virtual void SetEditable();
    void CreateWidget(QFormLayout* p_qLayout, QWidget* p_pqwParent);
    void SetDisplayType(EdmStringDisplayType p_eOeDisplayType);
    void SetCaptionLineEdit(QLineEdit* p_pqleCaption);
    static CoeValueWidget* CreateSearchValueWidget(const CdmMember* p_pCdmMember,
                                                   QString p_qstrKeyname,
                                                   QWidget* p_pqwParent);
    virtual QWidget* GetSearchWidget(QWidget* p_pqwParent);
    void CreateSearchWidget(QFormLayout* p_pqLayout, QWidget* p_pqwParent);
    virtual void AddQueryElement(CdmQueryElement* p_pCdmQueryElementParent);
    void SetCaption(QString p_qstrCaption);
    virtual void SetSearchDeaultValue(QString p_qstrDefault);
    bool CreateTabWidget(QWidget* p_pqwParent, QVBoxLayout* p_pqlLayout);
    virtual QWidget* GetTabEditWidget(QWidget* p_pqwParent);
    virtual void setEventClassValue();

    static CoeValueWidget *CreateEventValueWidget(CdmValue *p_pCdmEventValue, QWidget *p_pqwParent, const CdmObject *p_EventObject);
public slots:
    virtual void ValueChangedSlotByUser();
    virtual void SetValue(CdmValue* p_pCdmValue);

private:
    QWidget* CreateCaptionLabel(QWidget* p_pqwParent);

};

#endif
