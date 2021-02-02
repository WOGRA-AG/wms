
#include <QWidget>
#include <QLineEdit>
#include <QTextEdit>
#include <QPlainTextEdit>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QRadioButton>
#include <QCheckBox>
#include <QComboBox>
#include <QDateTimeEdit>
#include <QLabel>


#include "CdmLogging.h"
#include "CdmMember.h"
#include "CdmDataProvider.h"
#include "CdmClass.h"
#include "CdmObject.h"
#include "CumUserManager.h"
#include "CumUser.h"
#include "CumUserGroup.h"
#include "CdmValue.h"
#include "CdmValueBinaryDocument.h"
#include "CdmValueCharacterDocument.h"
#include "CdmValueFloat.h"
#include "CdmValueBool.h"
#include "CdmValueCounter.h"
#include "CdmValueDate.h"
#include "CdmJournalItem.h"
#include "CdmValueDateTime.h"
#include "CdmValueDouble.h"
#include "CdmValueInt.h"
#include "CdmValueLong.h"
#include "CdmValueUser.h"
#include "CdmValueContainerRef.h"
#include "CdmValueObjectRef.h"
#include "CdmValueString.h"
#include "CdmValueTime.h"
#include "CdmValueEnum.h"
#include "CdmValueFormula.h"
#include "CdmValueUser.h"
#include "CdmValueUserGroup.h"

#include "CoeTextEditMainWindow.h"

#include "CdmQueryBuilder.h"

#include "CwmsObjectBinder.h"

#define WMS_NO_RIGHTS "keine Berechtigung"

CwmsObjectBinder::CwmsObjectBinder(CdmObject* p_pObject)
    : m_cObjectAdaptor(p_pObject),
      m_bUseLableForCaption(false)
{

}


CwmsObjectBinder::~CwmsObjectBinder()
{

}

void CwmsObjectBinder::SetUseLabelForCaption(bool p_bFlag)
{
    m_bUseLableForCaption = p_bFlag;
}

bool CwmsObjectBinder::GetUseLabelForCaption()
{
    return m_bUseLableForCaption;
}

CdmObject *CwmsObjectBinder::GetObject()
{
    return m_cObjectAdaptor.GetObject();
}

void CwmsObjectBinder::SetObject(CdmObject *p_pObject)
{
    m_cObjectAdaptor.SetObject(p_pObject);
}

void CwmsObjectBinder::BindValue(QString p_qstrValue, QWidget *p_pqwWidget)
{
    if (m_cObjectAdaptor.GetValue(p_qstrValue) != nullptr && p_pqwWidget != nullptr)
    {
        m_qmBindings.insert(p_pqwWidget, p_qstrValue);
    }
    else
    {
        ERR("Value " + p_qstrValue + " not found or Widget is null");
    }
}

void CwmsObjectBinder::FillData()
{
    QMapIterator<QWidget*,QString> qmIt(m_qmBindings);

    while (qmIt.hasNext())
    {
        qmIt.next();
        FillData(qmIt.value(), qmIt.key());
    }
}

void CwmsObjectBinder::RefreshValue(QString &p_qstrMemberName)
{
    QMapIterator<QWidget*,QString> qmIt(m_qmBindings);

    while (qmIt.hasNext())
    {
        qmIt.next();
        if (qmIt.value() == p_qstrMemberName)
        {
            FillData(qmIt.value(), qmIt.key());
        }
    }
}

void CwmsObjectBinder::FillData(QString p_qstrValue, QWidget *p_pqwWidget)
{
    if (CHKPTR(p_pqwWidget))
    {
        CdmValue* pValue = m_cObjectAdaptor.GetValue(p_qstrValue);

        if (CHKPTR(pValue))
        {
            switch (pValue->GetValueType())
            {
            case eDmValueInt:
                FillData(dynamic_cast<CdmValueInt*>(pValue), p_pqwWidget);
                break;
            case eDmValueLong:
                FillData(dynamic_cast<CdmValueLong*>(pValue), p_pqwWidget);
                break;
            case eDmValueString:
                FillData(dynamic_cast<CdmValueString*>(pValue), p_pqwWidget);
                break;
            case eDmValueTime:
                FillData(dynamic_cast<CdmValueTime*>(pValue), p_pqwWidget);
                break;
            case eDmValueObjectRef:
                FillData(dynamic_cast<CdmValueObjectRef*>(pValue), p_pqwWidget);
                break;
            case eDmValueContainerRef:
                FillData(dynamic_cast<CdmValueContainerRef*>(pValue), p_pqwWidget);
                break;
            case eDmValueFormula:
                FillData(dynamic_cast<CdmValueFormula*>(pValue), p_pqwWidget);
                break;
            case eDmValueUser:
                FillData(dynamic_cast<CdmValueUser*>(pValue), p_pqwWidget);
                break;
            case eDmValueUserGroup:
                FillData(dynamic_cast<CdmValueUserGroup*>(pValue), p_pqwWidget);
                break;
            case eDmValueBool:
                FillData(dynamic_cast<CdmValueBool*>(pValue), p_pqwWidget);
                break;
            case eDmValueCharacterDocument:
                FillData(dynamic_cast<CdmValueCharacterDocument*>(pValue), p_pqwWidget);
                break;
            case eDmValueCounter:
                FillData(dynamic_cast<CdmValueCounter*>(pValue), p_pqwWidget);
                break;
            case eDmValueDate:
                FillData(dynamic_cast<CdmValueDate*>(pValue), p_pqwWidget);
                break;
            case eDmValueDateTime:
                FillData(dynamic_cast<CdmValueDateTime*>(pValue), p_pqwWidget);
                break;
            case eDmValueDouble:
                FillData(dynamic_cast<CdmValueDouble*>(pValue), p_pqwWidget);
                break;
            case eDmValueEnum:
                FillData(dynamic_cast<CdmValueEnum*>(pValue), p_pqwWidget);
                break;
            case eDmValueFloat:
                FillData(dynamic_cast<CdmValueFloat*>(pValue), p_pqwWidget);
                break;
            default:
                ERR("Unsupported Type in Binding. Type" + QString::number(pValue->GetValueType()));
            }
        }
    }
}

void CwmsObjectBinder::FillLabelData(CdmValue* p_pValue, QLabel* p_pWidget)
{
    if (CHKPTR(p_pWidget))
    {
        if (m_bUseLableForCaption)
        {
            p_pWidget->setText(p_pValue->GetCaption());
        }
        else
        {
            if (IsAccessible(p_pValue))
            {
                p_pWidget->setText(p_pValue->GetDisplayString());
            }
            else
            {
                p_pWidget->setText(WMS_NO_RIGHTS);
            }
        }
    }
}

bool CwmsObjectBinder::IsAccessible(CdmValue* p_pValue)
{
    bool bAccessible = true;

    if (CHKPTR(p_pValue))
    {
        const CdmMember* pMember = p_pValue->GetMember();

        if (pMember->GetAccessMode() == eDmMemberAccessPrivate)
        {
            bAccessible = false;
        }
        else
        {
            CdmRights& cCdmRights = const_cast<CdmMember*> (pMember)->GetRights();

            if (!cCdmRights.HasCurrentUserReadAccess())
            {
                bAccessible = false;
            }
        }
    }

    return bAccessible;
}

bool CwmsObjectBinder::IsReadOnly(CdmValue* p_pValue)
{
    bool bReadOnly = false;

    if (CHKPTR(p_pValue))
    {
        const CdmMember* pMember = p_pValue->GetMember();

        if (pMember->GetAccessMode() == eDmMemberAccessProtected)
        {
            bReadOnly = true;
        }
        else
        {
            CdmRights& cCdmRights = const_cast<CdmMember*> (pMember)->GetRights();

            if (!cCdmRights.HasCurrentUserWriteAccess())
            {
                bReadOnly = true;
            }
            else
            {
                const CdmObject* pObject = p_pValue->GetObject();

                if (pObject->IsReadOnly())
                {
                    bReadOnly = true;
                }
            }
        }
    }

    return bReadOnly;
}

void CwmsObjectBinder::FillData(CdmValueInt* p_pValue, QWidget* p_pWidget)
{
    if (CHKPTR(p_pValue) && CHKPTR(p_pWidget))
    {
        QString qstrWidgetType = p_pWidget->metaObject()->className();

        if (qstrWidgetType == "QLabel")
        {
            FillLabelData(p_pValue, dynamic_cast<QLabel*>(p_pWidget));
        }
        else if (qstrWidgetType == "QLineEdit")
        {
            auto pEdit = dynamic_cast<QLineEdit*>(p_pWidget);

            if (CHKPTR(pEdit))
            {
                if (IsAccessible(p_pValue))
                {
                    pEdit->setAlignment(Qt::AlignRight);
                    QLocale loc;
                    pEdit->setText(loc.toString(p_pValue->GetValue()));

                    if (IsReadOnly(p_pValue))
                    {
                        pEdit->setReadOnly(true);
                    }
                }
                else
                {
                    pEdit->setText(WMS_NO_RIGHTS);
                }
            }
        }
        else if (qstrWidgetType == "QSpinBox")
        {
            auto pEdit = dynamic_cast<QSpinBox*>(p_pWidget);

            if (IsAccessible(p_pValue))
            {
                if (CHKPTR(pEdit))
                {
                    pEdit->setMaximum(10000000);
                    pEdit->setMinimum(-10000000);
                    pEdit->setValue(p_pValue->GetValue());
                }

                if (IsReadOnly(p_pValue))
                {
                    pEdit->setEnabled(false);
                }
            }
            else
            {
                pEdit->setMaximum(10000000);
                pEdit->setMinimum(-10000000);
                pEdit->setValue(-10000000);

            }
        }
        else
        {
            ERR(QString("Unsupported Widget Type %1 for Value %2").arg(qstrWidgetType).arg(p_pValue->GetKeyname()));
        }
    }
}

void CwmsObjectBinder::FillData(CdmValueLong* p_pValue, QWidget* p_pWidget)
{
    if (CHKPTR(p_pValue) && CHKPTR(p_pWidget))
    {
        QString qstrWidgetType = p_pWidget->metaObject()->className();

        if (qstrWidgetType == "QLabel")
        {
            FillLabelData(p_pValue, dynamic_cast<QLabel*>(p_pWidget));
        }
        else if (qstrWidgetType == "QLineEdit")
        {
            auto pEdit = dynamic_cast<QLineEdit*>(p_pWidget);

            if (CHKPTR(pEdit))
            {
                if (IsAccessible(p_pValue))
                {
                    pEdit->setAlignment(Qt::AlignRight);
                    QLocale loc;
                    pEdit->setText(loc.toString(static_cast<int>(p_pValue->GetValue())));

                    if (IsReadOnly(p_pValue))
                    {
                        pEdit->setReadOnly(true);
                    }
                }
                else
                {
                    pEdit->setText(WMS_NO_RIGHTS);
                }
            }
        }
        else if (qstrWidgetType == "QSpinBox")
        {
            auto pEdit = dynamic_cast<QSpinBox*>(p_pWidget);

            if (IsAccessible(p_pValue))
            {
                if (CHKPTR(pEdit))
                {
                    pEdit->setMaximum(10000000);
                    pEdit->setMinimum(-10000000);
                    pEdit->setValue(p_pValue->GetValue());
                }

                if (IsReadOnly(p_pValue))
                {
                    pEdit->setEnabled(false);
                }
            }
            else
            {
                pEdit->setMaximum(10000000);
                pEdit->setMinimum(-10000000);
                pEdit->setValue(-10000000);
            }
        }
        else
        {
            ERR(QString("Unsupported Widget Type %1 for Value %2").arg(qstrWidgetType).arg(p_pValue->GetKeyname()));
        }
    }
}

void CwmsObjectBinder::FillData(CdmValueFloat* p_pValue, QWidget* p_pWidget)
{
    if (CHKPTR(p_pValue) && CHKPTR(p_pWidget))
    {
        QString qstrWidgetType = p_pWidget->metaObject()->className();

        if (qstrWidgetType == "QLabel")
        {
            FillLabelData(p_pValue, dynamic_cast<QLabel*>(p_pWidget));
        }
        else if (qstrWidgetType == "QLineEdit")
        {
            auto pEdit = dynamic_cast<QLineEdit*>(p_pWidget);

            if (CHKPTR(pEdit))
            {
                if (IsAccessible(p_pValue))
                {
                    pEdit->setAlignment(Qt::AlignRight);
                    QLocale loc;
                    pEdit->setText(loc.toString(static_cast<int>(p_pValue->GetValue())));

                    if (IsReadOnly(p_pValue))
                    {
                        pEdit->setReadOnly(true);
                    }
                }
                else
                {
                    pEdit->setText(WMS_NO_RIGHTS);
                }
            }
        }
        else if (qstrWidgetType == "QDoubleSpinBox")
        {
            auto pEdit = dynamic_cast<QDoubleSpinBox*>(p_pWidget);

            if (IsAccessible(p_pValue))
            {
                if (CHKPTR(pEdit))
                {
                    pEdit->setMaximum(10000000);
                    pEdit->setMinimum(-10000000);
                    pEdit->setValue(p_pValue->GetValue());
                }

                if (IsReadOnly(p_pValue))
                {
                    pEdit->setEnabled(false);
                }
            }
            else
            {
                pEdit->setMaximum(10000000);
                pEdit->setMinimum(-10000000);
                pEdit->setValue(-10000000);
            }
        }
        else
        {
            ERR(QString("Unsupported Widget Type %1 for Value %2").arg(qstrWidgetType).arg(p_pValue->GetKeyname()));
        }
    }
}

void CwmsObjectBinder::FillData(CdmValueDouble* p_pValue, QWidget* p_pWidget)
{
    if (CHKPTR(p_pValue) && CHKPTR(p_pWidget))
    {
        QString qstrWidgetType = p_pWidget->metaObject()->className();

        if (qstrWidgetType == "QLabel")
        {
            FillLabelData(p_pValue, dynamic_cast<QLabel*>(p_pWidget));
        }
        else if (qstrWidgetType == "QLineEdit")
        {
            auto pEdit = dynamic_cast<QLineEdit*>(p_pWidget);

            if (CHKPTR(pEdit))
            {
                if (IsAccessible(p_pValue))
                {
                    pEdit->setAlignment(Qt::AlignRight);
                    QLocale loc;
                    pEdit->setText(loc.toString(static_cast<int>(p_pValue->GetValue())));

                    if (IsReadOnly(p_pValue))
                    {
                        pEdit->setReadOnly(true);
                    }
                }
                else
                {
                    pEdit->setText(WMS_NO_RIGHTS);
                }
            }
        }
        else if (qstrWidgetType == "QDoubleSpinBox")
        {
            auto pEdit = dynamic_cast<QDoubleSpinBox*>(p_pWidget);

            if (IsAccessible(p_pValue))
            {
                if (CHKPTR(pEdit))
                {
                    pEdit->setMaximum(10000000);
                    pEdit->setMinimum(-10000000);
                    pEdit->setValue(p_pValue->GetValue());
                }

                if (IsReadOnly(p_pValue))
                {
                    pEdit->setEnabled(false);
                }
            }
            else
            {
                pEdit->setMaximum(10000000);
                pEdit->setMinimum(-10000000);
                pEdit->setValue(-10000000);
            }
        }
        else
        {
            ERR(QString("Unsupported Widget Type %1 for Value %2").arg(qstrWidgetType).arg(p_pValue->GetKeyname()));
        }
    }
}

void CwmsObjectBinder::FillData(CdmValueEnum* p_pValue, QWidget* p_pWidget)
{
    if (CHKPTR(p_pValue) && CHKPTR(p_pWidget))
    {
        QString qstrWidgetType = p_pWidget->metaObject()->className();

        if (qstrWidgetType == "QLabel")
        {
            FillLabelData(p_pValue, dynamic_cast<QLabel*>(p_pWidget));
        }
        else if (qstrWidgetType == "QLineEdit")
        {
            auto pEdit = dynamic_cast<QLineEdit*>(p_pWidget);

            if (CHKPTR(pEdit))
            {
                if (IsAccessible(p_pValue) && IsReadOnly(p_pValue))
                {
                    pEdit->setText(p_pValue->GetDisplayString());
                    pEdit->setReadOnly(true);
                }
                else
                {
                    ERR(QString("Unsupported Widget Type %1 for Value %2").arg(qstrWidgetType).arg(p_pValue->GetKeyname()));
                }
            }
        }
        else if (qstrWidgetType == "QComboBox")
        {
            auto pEdit = dynamic_cast<QComboBox*>(p_pWidget);

            if (IsAccessible(p_pValue))
            {
                if (CHKPTR(pEdit))
                {
                    QStringList qstrlSelection = p_pValue->GetSelectionList();

                    pEdit->clear();

                    for (int iCounter = 0; iCounter < qstrlSelection.count(); ++iCounter)
                    {
                       pEdit->addItem(qstrlSelection[iCounter]);
                    }

                    pEdit->setCurrentIndex(p_pValue->GetValue());
                }

                if (IsReadOnly(p_pValue))
                {
                    pEdit->setEnabled(false);
                }
            }
            else
            {
                pEdit->setEnabled(false);
            }
        }
        else
        {
            ERR(QString("Unsupported Widget Type %1 for Value %2").arg(qstrWidgetType).arg(p_pValue->GetKeyname()));
        }
    }
}

void CwmsObjectBinder::FillData(CdmValueBool* p_pValue, QWidget* p_pWidget)
{
    if (CHKPTR(p_pValue) && CHKPTR(p_pWidget))
    {
        QString qstrWidgetType = p_pWidget->metaObject()->className();

        if (qstrWidgetType == "QLabel")
        {
            FillLabelData(p_pValue, dynamic_cast<QLabel*>(p_pWidget));
        }
        else if (qstrWidgetType == "QCheckBox")
        {
            auto pEdit = dynamic_cast<QCheckBox*>(p_pWidget);

            if (CHKPTR(pEdit))
            {
                if (IsAccessible(p_pValue))
                {
                    pEdit->setChecked(p_pValue->GetValue());
                }

                if (IsReadOnly(p_pValue))
                {
                    pEdit->setEnabled(false);
                }
            }
        }
        else if (qstrWidgetType == "QComboBox")
        {
            auto pEdit = dynamic_cast<QComboBox*>(p_pWidget);

            if (IsAccessible(p_pValue))
            {
                if (CHKPTR(pEdit))
                {
                    QStringList qstrlSelection;
                    qstrlSelection.append("ja");
                    qstrlSelection.append("nein");

                    pEdit->clear();

                    for (int iCounter = 0; iCounter < qstrlSelection.count(); ++iCounter)
                    {
                       pEdit->addItem(qstrlSelection[iCounter]);
                    }

                    if (p_pValue->GetValue())
                    {
                        pEdit->setCurrentIndex(0);
                    }
                    else
                    {
                        pEdit->setCurrentIndex(1);
                    }
                }

                if (IsReadOnly(p_pValue))
                {
                    pEdit->setEnabled(false);
                }
            }
            else
            {
                pEdit->setEnabled(false);
            }
        }
        else
        {
            ERR(QString("Unsupported Widget Type %1 for Value %2").arg(qstrWidgetType).arg(p_pValue->GetKeyname()));
        }
    }
}

void CwmsObjectBinder::FillData(CdmValueString* p_pValue, QWidget* p_pWidget)
{
    if (CHKPTR(p_pValue) && CHKPTR(p_pWidget))
    {
        QString qstrWidgetType = p_pWidget->metaObject()->className();

        if (qstrWidgetType == "QLabel")
        {
            FillLabelData(p_pValue, dynamic_cast<QLabel*>(p_pWidget));
        }
        else if (qstrWidgetType == "QLineEdit")
        {
            auto pEdit = dynamic_cast<QLineEdit*>(p_pWidget);

            if (CHKPTR(pEdit))
            {
                if (IsAccessible(p_pValue))
                {
                    pEdit->setText(p_pValue->GetValue());

                    if (IsReadOnly(p_pValue))
                    {
                        pEdit->setReadOnly(true);
                    }
                }
                else
                {
                    pEdit->setText(WMS_NO_RIGHTS);
                }
            }
        }
        else if (qstrWidgetType == "QTextEdit")
        {
            auto pEdit = dynamic_cast<QTextEdit*>(p_pWidget);

            if (CHKPTR(pEdit))
            {
                if (IsAccessible(p_pValue))
                {
                    pEdit->setText(p_pValue->GetValue());

                    if (IsReadOnly(p_pValue))
                    {
                        pEdit->setReadOnly(true);
                    }
                }
                else
                {
                    pEdit->setText(WMS_NO_RIGHTS);
                }
            }
        }
        else if (qstrWidgetType == "QPlainTextEdit")
        {
            auto pEdit = dynamic_cast<QPlainTextEdit*>(p_pWidget);

            if (CHKPTR(pEdit))
            {
                if (IsAccessible(p_pValue))
                {
                    pEdit->setPlainText(p_pValue->GetValue());

                    if (IsReadOnly(p_pValue))
                    {
                        pEdit->setReadOnly(true);
                    }
                }
                else
                {
                    pEdit->setPlainText(WMS_NO_RIGHTS);
                }
            }
        }
        else if (qstrWidgetType == "QComboBox")
        {
            auto pEdit = dynamic_cast<QComboBox*>(p_pWidget);

            if (CHKPTR(pEdit))
            {
                if (IsAccessible(p_pValue))
                {
                    pEdit->setEditText(p_pValue->GetValue());

                    if (IsReadOnly(p_pValue))
                    {
                        pEdit->setEnabled(true);
                    }
                }
                else
                {
                    pEdit->setEnabled(WMS_NO_RIGHTS);
                }
            }
        }
        else
        {
            ERR(QString("Unsupported Widget Type %1 for Value %2").arg(qstrWidgetType).arg(p_pValue->GetKeyname()));
        }
    }
}

void CwmsObjectBinder::FillData(CdmValueTime* p_pValue, QWidget* p_pWidget)
{
    if (CHKPTR(p_pValue) && CHKPTR(p_pWidget))
    {
        QString qstrWidgetType = p_pWidget->metaObject()->className();

        if (qstrWidgetType == "QLabel")
        {
            FillLabelData(p_pValue, dynamic_cast<QLabel*>(p_pWidget));
        }
        else if (qstrWidgetType == "QLineEdit")
        {
            auto pEdit = dynamic_cast<QLineEdit*>(p_pWidget);

            if (CHKPTR(pEdit))
            {
                if (IsAccessible(p_pValue))
                {
                    pEdit->setText(p_pValue->GetDisplayString());
                    pEdit->setReadOnly(true);
                }
                else
                {
                    pEdit->setText(WMS_NO_RIGHTS);
                }
            }
        }
        else if (qstrWidgetType == "QTimeEdit")
        {
            auto pEdit = dynamic_cast<QTimeEdit*>(p_pWidget);

            if (CHKPTR(pEdit))
            {
                if (IsAccessible(p_pValue))
                {
                    pEdit->setTime(p_pValue->GetValue());

                    if (IsReadOnly(p_pValue))
                    {
                        pEdit->setEnabled(false);
                    }
                }
                else
                {
                    pEdit->setTime(QTime(0,0,0));
                    pEdit->setEnabled(false);
                }
            }
        }
        else
        {
            ERR(QString("Unsupported Widget Type %1 for Value %2").arg(qstrWidgetType).arg(p_pValue->GetKeyname()));
        }
    }

}

void CwmsObjectBinder::FillData(CdmValueDate* p_pValue, QWidget* p_pWidget)
{
    if (CHKPTR(p_pValue) && CHKPTR(p_pWidget))
    {
        QString qstrWidgetType = p_pWidget->metaObject()->className();

        if (qstrWidgetType == "QLabel")
        {
            FillLabelData(p_pValue, dynamic_cast<QLabel*>(p_pWidget));
        }
        else if (qstrWidgetType == "QLineEdit")
        {
            auto pEdit = dynamic_cast<QLineEdit*>(p_pWidget);

            if (CHKPTR(pEdit))
            {
                if (IsAccessible(p_pValue))
                {
                    pEdit->setText(p_pValue->GetDisplayString());
                    pEdit->setReadOnly(true);
                }
                else
                {
                    pEdit->setText(WMS_NO_RIGHTS);
                }
            }
        }
        else if (qstrWidgetType == "QDateEdit")
        {
            auto pEdit = dynamic_cast<QDateEdit*>(p_pWidget);

            if (CHKPTR(pEdit))
            {
                if (IsAccessible(p_pValue))
                {
                    pEdit->setDate(p_pValue->GetValue());

                    if (IsReadOnly(p_pValue))
                    {
                        pEdit->setEnabled(false);
                    }
                }
                else
                {
                    pEdit->setDate(QDate(1970,1,1));
                    pEdit->setEnabled(false);
                }
            }
        }
        else
        {
            ERR(QString("Unsupported Widget Type %1 for Value %2").arg(qstrWidgetType).arg(p_pValue->GetKeyname()));
        }
    }
}


void CwmsObjectBinder::FillData(CdmValueDateTime* p_pValue, QWidget* p_pWidget)
{
    if (CHKPTR(p_pValue) && CHKPTR(p_pWidget))
    {
        QString qstrWidgetType = p_pWidget->metaObject()->className();

        if (qstrWidgetType == "QLabel")
        {
            FillLabelData(p_pValue, dynamic_cast<QLabel*>(p_pWidget));
        }
        else if (qstrWidgetType == "QLineEdit")
        {
            auto pEdit = dynamic_cast<QLineEdit*>(p_pWidget);

            if (CHKPTR(pEdit))
            {
                if (IsAccessible(p_pValue))
                {
                    pEdit->setText(p_pValue->GetDisplayString());
                    pEdit->setReadOnly(true);
                }
                else
                {
                    pEdit->setText(WMS_NO_RIGHTS);
                }
            }
        }
        else if (qstrWidgetType == "QDateTimeEdit")
        {
            auto pEdit = dynamic_cast<QDateTimeEdit*>(p_pWidget);

            if (CHKPTR(pEdit))
            {
                if (IsAccessible(p_pValue))
                {
                    pEdit->setDateTime(p_pValue->GetValue());

                    if (IsReadOnly(p_pValue))
                    {
                        pEdit->setEnabled(false);
                    }
                }
                else
                {
                    pEdit->setTime(QTime(0,0,0));
                    pEdit->setDate(QDate(1970,1,1));
                    pEdit->setEnabled(false);
                }
            }
        }
        else
        {
            ERR(QString("Unsupported Widget Type %1 for Value %2").arg(qstrWidgetType).arg(p_pValue->GetKeyname()));
        }
    }
}

void CwmsObjectBinder::FillData(CdmValueCharacterDocument* p_pValue, QWidget* p_pWidget)
{
    if (CHKPTR(p_pValue) && CHKPTR(p_pWidget))
    {
        QString qstrWidgetType = p_pWidget->metaObject()->className();

        if (qstrWidgetType == "QLabel")
        {
            FillLabelData(p_pValue, dynamic_cast<QLabel*>(p_pWidget));
        }
        else if (qstrWidgetType == "QLineEdit")
        {
            auto pEdit = dynamic_cast<QLineEdit*>(p_pWidget);

            if (CHKPTR(pEdit))
            {
                if (IsAccessible(p_pValue))
                {
                    pEdit->setText(p_pValue->GetValue());

                    if (IsReadOnly(p_pValue))
                    {
                        pEdit->setReadOnly(true);
                    }
                }
                else
                {
                    pEdit->setText(WMS_NO_RIGHTS);
                }
            }
        }
        else if (qstrWidgetType == "QTextEdit")
        {
            auto pEdit = dynamic_cast<QTextEdit*>(p_pWidget);

            if (CHKPTR(pEdit))
            {
                if (IsAccessible(p_pValue))
                {
                    pEdit->setText(p_pValue->GetValue());

                    if (IsReadOnly(p_pValue))
                    {
                        pEdit->setReadOnly(true);
                    }
                }
                else
                {
                    pEdit->setText(WMS_NO_RIGHTS);
                }
            }
        }
        else if (qstrWidgetType == "QPlainTextEdit")
        {
            auto pEdit = dynamic_cast<QPlainTextEdit*>(p_pWidget);

            if (CHKPTR(pEdit))
            {
                if (IsAccessible(p_pValue))
                {
                    pEdit->setPlainText(p_pValue->GetValue());

                    if (IsReadOnly(p_pValue))
                    {
                        pEdit->setReadOnly(true);
                    }
                }
                else
                {
                    pEdit->setPlainText(WMS_NO_RIGHTS);
                }
            }
        }
        else if (qstrWidgetType == "CoeTextEditMainWindow")
        {
            auto pEdit = dynamic_cast<CoeTextEditMainWindow*>(p_pWidget);

            if(CHKPTR(pEdit))
            {
                if(IsAccessible(p_pValue))
                {
                    pEdit->SetText(p_pValue->GetValue());

                    if (IsReadOnly(p_pValue))
                    {
                        pEdit->ui.m_pqteTextEdit->setReadOnly(true);
                    }
                }
                else
                {
                    pEdit->SetText(WMS_NO_RIGHTS);
                }
            }
        }
        else
        {
            ERR(QString("Unsupported Widget Type %1 for Value %2").arg(qstrWidgetType).arg(p_pValue->GetKeyname()));
        }
    }
}

void CwmsObjectBinder::FillData(CdmValueCounter* p_pValue, QWidget* p_pWidget)
{
    if (CHKPTR(p_pValue) && CHKPTR(p_pWidget))
    {
        QString qstrWidgetType = p_pWidget->metaObject()->className();

        if (qstrWidgetType == "QLabel")
        {
            FillLabelData(p_pValue, dynamic_cast<QLabel*>(p_pWidget));
        }
        else if (qstrWidgetType == "QLineEdit")
        {
            auto pEdit = dynamic_cast<QLineEdit*>(p_pWidget);

            if (CHKPTR(pEdit))
            {
                if (IsAccessible(p_pValue))
                {
                    pEdit->setText(p_pValue->GetDisplayString());
                    pEdit->setReadOnly(true);
                }
                else
                {
                    pEdit->setText(WMS_NO_RIGHTS);
                }
            }
        }
        else
        {
            ERR(QString("Unsupported Widget Type %1 for Value %2").arg(qstrWidgetType).arg(p_pValue->GetKeyname()));
        }
    }
}

void CwmsObjectBinder::FillData(CdmValueFormula* p_pValue, QWidget* p_pWidget)
{
    if (CHKPTR(p_pValue) && CHKPTR(p_pWidget))
    {
        QString qstrWidgetType = p_pWidget->metaObject()->className();

        if (qstrWidgetType == "QLabel")
        {
            FillLabelData(p_pValue, dynamic_cast<QLabel*>(p_pWidget));
        }
        else if (qstrWidgetType == "QLineEdit")
        {
            auto pEdit = dynamic_cast<QLineEdit*>(p_pWidget);

            if (CHKPTR(pEdit))
            {
                if (IsAccessible(p_pValue))
                {
                    pEdit->setText(p_pValue->GetDisplayString());
                    pEdit->setReadOnly(true);
                }
                else
                {
                    pEdit->setText(WMS_NO_RIGHTS);
                }
            }
        }
        else
        {
            ERR(QString("Unsupported Widget Type %1 for Value %2").arg(qstrWidgetType).arg(p_pValue->GetKeyname()));
        }
    }
}

void CwmsObjectBinder::FillData(CdmValueUser* p_pValue, QWidget* p_pWidget)
{
    if (CHKPTR(p_pValue) && CHKPTR(p_pWidget))
    {
        QString qstrWidgetType = p_pWidget->metaObject()->className();

        if (qstrWidgetType == "QLabel")
        {
            FillLabelData(p_pValue, dynamic_cast<QLabel*>(p_pWidget));
        }
        else if (qstrWidgetType == "QLineEdit")
        {
            auto pEdit = dynamic_cast<QLineEdit*>(p_pWidget);

            if (CHKPTR(pEdit))
            {
                if (IsAccessible(p_pValue) && IsReadOnly(p_pValue))
                {
                    pEdit->setText(p_pValue->GetDisplayString());
                    pEdit->setReadOnly(true);
                }
                else
                {
                    ERR(QString("Unsupported Widget Type %1 for Value %2").arg(qstrWidgetType).arg(p_pValue->GetKeyname()));
                }
            }
        }
        else if (qstrWidgetType == "QComboBox")
        {
            auto pEdit = dynamic_cast<QComboBox*>(p_pWidget);

            if (IsAccessible(p_pValue))
            {
                if (CHKPTR(pEdit))
                {
                    CdmDataProvider* pProvider = CdmSessionManager::GetDataProvider();

                    if (CHKPTR(pProvider))
                    {
                        CumUserManager* pUserManager = pProvider->GetUserManager();

                        if (CHKPTR(pUserManager))
                        {
                            QLinkedList<CumUser*> qllUsers;
                            pUserManager->GetUserListUnmanaged(qllUsers);
                            QLinkedListIterator<CumUser*> qllIt(qllUsers);

                            pEdit->addItem("-", "");

                            while(qllIt.hasNext())
                            {
                                CumUser* pUser = qllIt.next();

                                if (CHKPTR(pUser))
                                {
                                    pEdit->addItem(pUser->GetDisplayString(), pUser->GetUri());

                                    CumUser* pUserSelected = p_pValue->GetUser();

                                    if (pUserSelected)
                                    {
                                        if (pUser->GetId() == pUserSelected->GetId())
                                        {
                                            pEdit->setCurrentIndex(pEdit->count() - 1);
                                        }
                                    }
                                }

                                DELPTR(pUser);
                            }
                        }
                    }
                }

                if (IsReadOnly(p_pValue))
                {
                    pEdit->setEnabled(false);
                }
            }
            else
            {
                pEdit->setEnabled(false);
            }
        }
        else
        {
            ERR(QString("Unsupported Widget Type %1 for Value %2").arg(qstrWidgetType).arg(p_pValue->GetKeyname()));
        }
    }
}

void CwmsObjectBinder::FillData(CdmValueUserGroup* p_pValue, QWidget* p_pWidget)
{
    if (CHKPTR(p_pValue) && CHKPTR(p_pWidget))
    {
        QString qstrWidgetType = p_pWidget->metaObject()->className();

        if (qstrWidgetType == "QLabel")
        {
            FillLabelData(p_pValue, dynamic_cast<QLabel*>(p_pWidget));
        }
        else if (qstrWidgetType == "QLineEdit")
        {
            auto pEdit = dynamic_cast<QLineEdit*>(p_pWidget);

            if (CHKPTR(pEdit))
            {
                if (IsAccessible(p_pValue) && IsReadOnly(p_pValue))
                {
                    pEdit->setText(p_pValue->GetDisplayString());
                    pEdit->setReadOnly(true);
                }
                else
                {
                    ERR(QString("Unsupported Widget Type for Value %2").arg(qstrWidgetType).arg(p_pValue->GetKeyname()));
                }
            }
        }
        else if (qstrWidgetType == "QComboBox")
        {
            auto pEdit = dynamic_cast<QComboBox*>(p_pWidget);

            if (IsAccessible(p_pValue))
            {
                if (CHKPTR(pEdit))
                {
                    CdmDataProvider* pProvider = CdmSessionManager::GetDataProvider();

                    if (CHKPTR(pProvider))
                    {
                        CumUserManager* pUserManager = pProvider->GetUserManager();

                        if (CHKPTR(pUserManager))
                        {
                            QLinkedList<CumUserGroup*> qllUserGroups;
                            pUserManager->GetUserGroupList(qllUserGroups);
                            QLinkedListIterator<CumUserGroup*> qllIt(qllUserGroups);

                            pEdit->addItem("-", "");

                            while(qllIt.hasNext())
                            {
                                CumUserGroup* pUserGroup = qllIt.next();

                                if (CHKPTR(pUserGroup))
                                {
                                    pEdit->addItem(pUserGroup->GetGroupName(), pUserGroup->GetUri());

                                    CumUserGroup* pUserGroupSelected = p_pValue->GetUserGroup();

                                    if (pUserGroupSelected)
                                    {
                                        if (pUserGroup->GetId() == pUserGroupSelected->GetId())
                                        {
                                            pEdit->setCurrentIndex(pEdit->count() - 1);
                                        }
                                    }
                                }
                            }
                        }
                    }
                }

                if (IsReadOnly(p_pValue))
                {
                    pEdit->setEnabled(false);
                }
            }
            else
            {
                pEdit->setEnabled(false);
            }
        }
        else
        {
            ERR(QString("Unsupported Widget Type %1 for Value %2").arg(qstrWidgetType).arg(p_pValue->GetKeyname()));
        }
    }
}

void CwmsObjectBinder::FillData(CdmValueObjectRef *p_pValue, QWidget *p_pWidget)
{
    if (CHKPTR(p_pValue) && CHKPTR(p_pWidget))
    {
        QString qstrWidgetType = p_pWidget->metaObject()->className();

        if (qstrWidgetType == "QLabel")
        {
            FillLabelData(p_pValue, dynamic_cast<QLabel*>(p_pWidget));
        }
        else if(qstrWidgetType == "QComboBox" || qstrWidgetType == "CwmsObjectChoiceComboBox")
        {
            auto pEdit = dynamic_cast<QComboBox*>(p_pWidget);
            if(CHKPTR(pEdit))
            {
                pEdit->addItem("-", "");

                QString qstrWql = QString("SELECT FROM \"%1.class\"").arg(p_pValue->GetClass()->GetKeyname());

                QScopedPointer<CdmQuery> pQuery(CdmQueryBuilder::ExecuteQuery(qstrWql));
                int lCount = pQuery->GetResultCount();
                for(int i = 0; i < lCount; i++)
                {
                    CdmObject *pObject = pQuery->GetObjectAt(i);
                    pEdit->addItem(pObject->GetDisplayString(p_pValue->GetClass()->GetCaptionMemberKeyname()), pObject->GetUri());

                    if(p_pValue->GetObject()!= nullptr && p_pValue->GetObject()->GetUri() == pObject->GetUri())
                    {
                        pEdit->setCurrentIndex(pEdit->count() - 1);
                    }
                }
            }
        }
        else
        {
            ERR(QString("Unsupported Widget Type %1 for Value %2").arg(qstrWidgetType).arg(p_pValue->GetKeyname()));
        }
    }
}

void CwmsObjectBinder::UpdateDataWithoutCommit()
{
    QMapIterator<QWidget*,QString> qmIt(m_qmBindings);

    while (qmIt.hasNext())
    {
        qmIt.next();
        SaveData(qmIt.value(), qmIt.key());
    }
}

void CwmsObjectBinder::CommitChanges()
{
    m_cObjectAdaptor.CommitObject();
}

void CwmsObjectBinder::SaveData()
{
    UpdateDataWithoutCommit();
    CommitChanges();
}

void CwmsObjectBinder::SaveData(QString p_qstrValue, QWidget *p_pqwWidget)
{
    if (CHKPTR(p_pqwWidget))
    {
        CdmValue* pValue = m_cObjectAdaptor.GetValue(p_qstrValue);

        if (CHKPTR(pValue))
        {
            switch (pValue->GetValueType())
            {
            case eDmValueInt:
                SaveData(dynamic_cast<CdmValueInt*>(pValue), p_pqwWidget);
                break;
            case eDmValueLong:
                SaveData(dynamic_cast<CdmValueLong*>(pValue), p_pqwWidget);
                break;
            case eDmValueString:
                SaveData(dynamic_cast<CdmValueString*>(pValue), p_pqwWidget);
                break;
            case eDmValueTime:
                SaveData(dynamic_cast<CdmValueTime*>(pValue), p_pqwWidget);
                break;
            case eDmValueObjectRef:
                SaveData(dynamic_cast<CdmValueObjectRef*>(pValue), p_pqwWidget);
                break;
            case eDmValueContainerRef:
                SaveData(dynamic_cast<CdmValueContainerRef*>(pValue), p_pqwWidget);
                break;
            case eDmValueUser:
                SaveData(dynamic_cast<CdmValueUser*>(pValue), p_pqwWidget);
                break;
            case eDmValueUserGroup:
                SaveData(dynamic_cast<CdmValueUserGroup*>(pValue), p_pqwWidget);
                break;
            case eDmValueBool:
                SaveData(dynamic_cast<CdmValueBool*>(pValue), p_pqwWidget);
                break;
            case eDmValueCharacterDocument:
                SaveData(dynamic_cast<CdmValueCharacterDocument*>(pValue), p_pqwWidget);
                break;
            case eDmValueDate:
                SaveData(dynamic_cast<CdmValueDate*>(pValue), p_pqwWidget);
                break;
            case eDmValueDateTime:
                SaveData(dynamic_cast<CdmValueDateTime*>(pValue), p_pqwWidget);
                break;
            case eDmValueDouble:
                SaveData(dynamic_cast<CdmValueDouble*>(pValue), p_pqwWidget);
                break;
            case eDmValueEnum:
                SaveData(dynamic_cast<CdmValueEnum*>(pValue), p_pqwWidget);
                break;
            case eDmValueFloat:
                SaveData(dynamic_cast<CdmValueFloat*>(pValue), p_pqwWidget);
                break;
            default:
                INFO("Unsupported Type in Binding. Type" + QString::number(pValue->GetValueType()));
            }
        }
    }
}

bool CwmsObjectBinder::IsChangeable(CdmValue* p_pValue)
{
    return (IsAccessible(p_pValue) && !IsReadOnly(p_pValue));
}

void CwmsObjectBinder::SaveData(CdmValueInt* p_pValue, QWidget* p_pWidget)
{
    if (CHKPTR(p_pValue) && CHKPTR(p_pWidget))
    {
        if (IsChangeable(p_pValue))
        {
            QString qstrWidgetType = p_pWidget->metaObject()->className();

            if (qstrWidgetType == "QLineEdit")
            {
                auto pEdit = dynamic_cast<QLineEdit*>(p_pWidget);

                if (CHKPTR(pEdit))
                {
                    QLocale loc;
                    int iValue = loc.toInt(pEdit->text());
                    p_pValue->SetValue(iValue);
                }
            }
            else if (qstrWidgetType == "QSpinBox")
            {
                auto pEdit = dynamic_cast<QSpinBox*>(p_pWidget);

                if (CHKPTR(pEdit))
                {
                    p_pValue->SetValue(pEdit->value());
                }
            }

        }
    }
}

void CwmsObjectBinder::SaveData(CdmValueLong* p_pValue, QWidget* p_pWidget)
{
    if (CHKPTR(p_pValue) && CHKPTR(p_pWidget))
    {
        if (IsChangeable(p_pValue))
        {
            QString qstrWidgetType = p_pWidget->metaObject()->className();

            if (qstrWidgetType == "QLineEdit")
            {
                auto pEdit = dynamic_cast<QLineEdit*>(p_pWidget);

                if (CHKPTR(pEdit))
                {
                    QLocale loc;
                    int iValue = loc.toInt(pEdit->text());
                    p_pValue->SetValue(iValue);
                }
            }
            else if (qstrWidgetType == "QSpinBox")
            {
                auto pEdit = dynamic_cast<QSpinBox*>(p_pWidget);

                if (CHKPTR(pEdit))
                {
                    p_pValue->SetValue(pEdit->value());
                }
            }
        }
    }
}

void CwmsObjectBinder::SaveData(CdmValueFloat* p_pValue, QWidget* p_pWidget)
{
    if (CHKPTR(p_pValue) && CHKPTR(p_pWidget))
    {
        if (IsChangeable(p_pValue))
        {
            QString qstrWidgetType = p_pWidget->metaObject()->className();

            if (qstrWidgetType == "QLineEdit")
            {
                auto pEdit = dynamic_cast<QLineEdit*>(p_pWidget);

                if (CHKPTR(pEdit))
                {
                    QLocale loc;
                    double dValue = loc.toDouble(pEdit->text());
                    p_pValue->SetValue(dValue);
                }
            }
            else if (qstrWidgetType == "QDoubleSpinBox")
            {
                auto pEdit = dynamic_cast<QDoubleSpinBox*>(p_pWidget);

                if (CHKPTR(pEdit))
                {
                    p_pValue->SetValue(pEdit->value());
                }
            }
        }
    }
}

void CwmsObjectBinder::SaveData(CdmValueDouble* p_pValue, QWidget* p_pWidget)
{
    if (CHKPTR(p_pValue) && CHKPTR(p_pWidget))
    {
        if (IsChangeable(p_pValue))
        {
            QString qstrWidgetType = p_pWidget->metaObject()->className();

            if (qstrWidgetType == "QLineEdit")
            {
                auto pEdit = dynamic_cast<QLineEdit*>(p_pWidget);

                if (CHKPTR(pEdit))
                {
                    QLocale loc;
                    double dValue = loc.toDouble(pEdit->text());
                    p_pValue->SetValue(dValue);
                }
            }
            else if (qstrWidgetType == "QDoubleSpinBox")
            {
                auto pEdit = dynamic_cast<QDoubleSpinBox*>(p_pWidget);

                if (CHKPTR(pEdit))
                {
                    p_pValue->SetValue(pEdit->value());
                }
            }
        }
    }
}

void CwmsObjectBinder::SaveData(CdmValueEnum* p_pValue, QWidget* p_pWidget)
{
    if (CHKPTR(p_pValue) && CHKPTR(p_pWidget))
    {
        if (IsChangeable(p_pValue))
        {
            QString qstrWidgetType = p_pWidget->metaObject()->className();

            if (qstrWidgetType == "QComboBox")
            {
                auto pEdit = dynamic_cast<QComboBox*>(p_pWidget);

                if (CHKPTR(pEdit))
                {
                    p_pValue->SetValue(pEdit->currentIndex());
                }
            }
        }
    }
}

void CwmsObjectBinder::SaveData(CdmValueBool* p_pValue, QWidget* p_pWidget)
{
    if (CHKPTR(p_pValue) && CHKPTR(p_pWidget))
    {
        if (IsChangeable(p_pValue))
        {
            QString qstrWidgetType = p_pWidget->metaObject()->className();

            if (qstrWidgetType == "QCheckBox")
            {
                auto pEdit = dynamic_cast<QCheckBox*>(p_pWidget);

                if (CHKPTR(pEdit))
                {
                    p_pValue->SetValue(pEdit->isChecked());
                }
            }
            else if (qstrWidgetType == "QComboBox")
            {
                auto pEdit = dynamic_cast<QComboBox*>(p_pWidget);

                if (CHKPTR(pEdit))
                {
                    if (pEdit->currentIndex() == 0)
                    {
                        p_pValue->SetValue(true);
                    }
                    else
                    {
                        p_pValue->SetValue(false);
                    }
                }
            }
        }
    }
}

void CwmsObjectBinder::SaveData(CdmValueString* p_pValue, QWidget* p_pWidget)
{
    if (CHKPTR(p_pValue) && CHKPTR(p_pWidget))
    {
        if (IsChangeable(p_pValue))
        {
            QString qstrWidgetType = p_pWidget->metaObject()->className();

            if (qstrWidgetType == "QLineEdit")
            {
                auto pEdit = dynamic_cast<QLineEdit*>(p_pWidget);

                if (CHKPTR(pEdit))
                {
                    p_pValue->SetValue(pEdit->text());
                }
            }
            else if (qstrWidgetType == "QTextEdit")
            {
                auto pEdit = dynamic_cast<QTextEdit*>(p_pWidget);

                if (CHKPTR(pEdit))
                {
                    p_pValue->SetValue(pEdit->toHtml());
                }
            }
            else if (qstrWidgetType == "QPlainTextEdit")
            {
                auto pEdit = dynamic_cast<QTextEdit*>(p_pWidget);

                if (CHKPTR(pEdit))
                {
                    p_pValue->SetValue(pEdit->toPlainText());
                }
            }
            else if (qstrWidgetType == "QComboBox")
            {
               auto pEdit = dynamic_cast<QComboBox*>(p_pWidget);

               if(CHKPTR(pEdit))
               {
                    p_pValue->SetValue(pEdit->currentText());
               }
            }
        }
    }
}

void CwmsObjectBinder::SaveData(CdmValueTime* p_pValue, QWidget* p_pWidget)
{
    if (CHKPTR(p_pValue) && CHKPTR(p_pWidget))
    {
        if (IsChangeable(p_pValue))
        {
            QString qstrWidgetType = p_pWidget->metaObject()->className();

            if (qstrWidgetType == "QLineEdit")
            {
                auto pEdit = dynamic_cast<QLineEdit*>(p_pWidget);

                if (CHKPTR(pEdit))
                {
                    QLocale loc;
                    QString qstrTime = pEdit->text();
                    p_pValue->SetValue(loc.toTime(qstrTime));
                }
            }
            else if (qstrWidgetType == "QTimeEdit")
            {
                auto pEdit = dynamic_cast<QTimeEdit*>(p_pWidget);

                if (CHKPTR(pEdit))
                {
                    p_pValue->SetValue(pEdit->time());
                }
            }

        }
    }
}

void CwmsObjectBinder::SaveData(CdmValueDate* p_pValue, QWidget* p_pWidget)
{
    if (CHKPTR(p_pValue) && CHKPTR(p_pWidget))
    {
        if (IsChangeable(p_pValue))
        {
            QString qstrWidgetType = p_pWidget->metaObject()->className();

            if (qstrWidgetType == "QLineEdit")
            {
                auto pEdit = dynamic_cast<QLineEdit*>(p_pWidget);

                if (CHKPTR(pEdit))
                {
                    QLocale loc;
                    QString qstrTime = pEdit->text();
                    p_pValue->SetValue(loc.toDate(qstrTime));
                }
            }
            else if (qstrWidgetType == "QDateEdit")
            {
                auto pEdit = dynamic_cast<QDateEdit*>(p_pWidget);

                if (CHKPTR(pEdit))
                {
                    p_pValue->SetValue(pEdit->date());
                }
            }
        }
    }
}


void CwmsObjectBinder::SaveData(CdmValueDateTime* p_pValue, QWidget* p_pWidget)
{
    if (CHKPTR(p_pValue) && CHKPTR(p_pWidget))
    {
        if (IsChangeable(p_pValue))
        {
            QString qstrWidgetType = p_pWidget->metaObject()->className();

            if (qstrWidgetType == "QLineEdit")
            {
                auto pEdit = dynamic_cast<QLineEdit*>(p_pWidget);

                if (CHKPTR(pEdit))
                {
                    QLocale loc;
                    QString qstrTime = pEdit->text();
                    p_pValue->SetValue(loc.toDateTime(qstrTime));
                }
            }
            else if (qstrWidgetType == "QDateTimeEdit")
            {
                auto pEdit = dynamic_cast<QDateTimeEdit*>(p_pWidget);

                if (CHKPTR(pEdit))
                {
                    p_pValue->SetValue(pEdit->dateTime());
                }
            }
        }
    }
}

void CwmsObjectBinder::SaveData(CdmValueCharacterDocument* p_pValue, QWidget* p_pWidget)
{
    if (CHKPTR(p_pValue) && CHKPTR(p_pWidget))
    {
        if (IsChangeable(p_pValue))
        {
            QString qstrWidgetType = p_pWidget->metaObject()->className();

            if (qstrWidgetType == "QLineEdit")
            {
                auto pEdit = dynamic_cast<QLineEdit*>(p_pWidget);

                if (CHKPTR(pEdit))
                {
                    p_pValue->SetValue(pEdit->text());
                }
            }
            else if (qstrWidgetType == "QTextEdit")
            {
                auto pEdit = dynamic_cast<QTextEdit*>(p_pWidget);

                if (CHKPTR(pEdit))
                {
                    p_pValue->SetValue(pEdit->toHtml());
                }
            }
            else if (qstrWidgetType == "QPlainTextEdit")
            {
                auto pEdit = dynamic_cast<QTextEdit*>(p_pWidget);

                if (CHKPTR(pEdit))
                {
                    p_pValue->SetValue(pEdit->toPlainText());
                }
            }
            else if (qstrWidgetType == "CoeTextEditMainWindow")
            {
                auto pEdit = dynamic_cast<CoeTextEditMainWindow*>(p_pWidget);

                if(CHKPTR(pEdit))
                {
                    p_pValue->SetValue(pEdit->GetText());
                }
            }
        }
    }
}

void CwmsObjectBinder::SaveData(CdmValueUser* p_pValue, QWidget* p_pWidget)
{
    if (CHKPTR(p_pValue) && CHKPTR(p_pWidget))
    {
        if (IsChangeable(p_pValue))
        {
            QString qstrWidgetType = p_pWidget->metaObject()->className();

            if (qstrWidgetType == "QComboBox")
            {
                auto pEdit = dynamic_cast<QComboBox*>(p_pWidget);

                if (CHKPTR(pEdit))
                {
                    QString qstrUri = pEdit->currentData().toString();

                    if (!qstrUri.isEmpty() && qstrUri != "-")
                    {
                        CdmDataProvider* pProvider = CdmSessionManager::GetDataProvider();

                        if (CHKPTR(pProvider))
                        {
                            CdmLocatedElement* pElement = pProvider->GetUriObject(qstrUri);

                            if (CHKPTR(pElement) && pElement->IsUser())
                            {
                                p_pValue->SetUser(dynamic_cast<CumUser*> (pElement));
                            }
                        }
                    }
                    else
                    {
                        p_pValue->SetUser(nullptr);
                    }
                }
            }
        }
    }
}

void CwmsObjectBinder::SaveData(CdmValueUserGroup* p_pValue, QWidget* p_pWidget)
{
    if (CHKPTR(p_pValue) && CHKPTR(p_pWidget))
    {
        if (IsChangeable(p_pValue))
        {
            QString qstrWidgetType = p_pWidget->metaObject()->className();

            if (qstrWidgetType == "QComboBox")
            {
                auto pEdit = dynamic_cast<QComboBox*>(p_pWidget);

                if (CHKPTR(pEdit))
                {
                    QString qstrUri = pEdit->currentData().toString();

                    if (!qstrUri.isEmpty() && qstrUri != "-")
                    {
                        CdmDataProvider* pProvider = CdmSessionManager::GetDataProvider();

                        if (CHKPTR(pProvider))
                        {
                            CdmLocatedElement* pElement = pProvider->GetUriObject(qstrUri);

                            if (CHKPTR(pElement) && pElement->IsUserGroup())
                            {
                                p_pValue->SetUserGroup(dynamic_cast<CumUserGroup*> (pElement));
                            }
                        }
                    }
                    else
                    {
                        p_pValue->SetUserGroup(nullptr);
                    }
                }
            }
        }
    }
}

CdmObject* CwmsObjectBinder::GetSelectedObject(QWidget* p_pWidget, QString p_qstrKeyname)
{
    CdmObject* pObject = nullptr;
    CdmValue* pValue = m_cObjectAdaptor.GetValue(p_qstrKeyname);

    if (CHKPTR(pValue))
    {
        if (pValue->GetValueType() == eDmValueObjectRef)
        {
            QString qstrWidgetType = p_pWidget->metaObject()->className();

            if (qstrWidgetType == "QComboBox")
            {
                auto pEdit = dynamic_cast<QComboBox*>(p_pWidget);

                if (CHKPTR(pEdit))
                {
                    QString qstrUri = pEdit->currentData().toString();

                    if (!qstrUri.isEmpty() && qstrUri != "-")
                    {
                        CdmDataProvider* pProvider = CdmSessionManager::GetDataProvider();

                        if (CHKPTR(pProvider))
                        {
                            CdmLocatedElement* pElement = pProvider->GetUriObject(qstrUri);

                            if (CHKPTR(pElement) && pElement->IsObject())
                            {
                                pObject = dynamic_cast<CdmObject*>(pElement);
                            }
                        }
                    }
                }
            }
        }
    }

    return pObject;
}

void CwmsObjectBinder::SaveData(CdmValueObjectRef *p_pValue, QWidget *p_pWidget)
{
    if (CHKPTR(p_pValue) && CHKPTR(p_pWidget))
    {
        if (IsChangeable(p_pValue))
        {
            QString qstrWidgetType = p_pWidget->metaObject()->className();

            if (qstrWidgetType == "QComboBox")
            {
                auto pEdit = GetSelectedObject(p_pWidget, p_pValue->GetKeyname());
                p_pValue->SetValue(pEdit);
            }
        }
    }
}
