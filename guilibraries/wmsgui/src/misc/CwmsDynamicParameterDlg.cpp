
#include "CdmLogging.h"

#include "CwmsDynamicParamWidget.h"
#include "CwmsDynamicParameterDlg.h"
#include "ui_CwmsDynamicParameterDlg.h"

CwmsDynamicParameterDlg::CwmsDynamicParameterDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CwmsDynamicParameterDlg)
{
    ui->setupUi(this);
}

CwmsDynamicParameterDlg::~CwmsDynamicParameterDlg()
{
    delete ui;
}

void CwmsDynamicParameterDlg::FillDialog(QList<QPair<QString, EdmValueType> >& p_qlInput)
{
    m_qlInputs = p_qlInput;
    auto pContainer = new QWidget(ui->m_pqsaParams);
    auto pLayout = new QVBoxLayout(pContainer);
    pContainer->setLayout(pLayout);

    for (int pos = 0; pos < m_qlInputs.count(); ++pos)
    {
        // Todo create Widgets in ScollArea
        QString qstrName = m_qlInputs[pos].first;
        EdmValueType eType = m_qlInputs[pos].second;
        auto pWidget = new CwmsDynamicParamWidget(qstrName, eType, pContainer);
        pLayout->addWidget(pWidget);
        m_qlParamWidgets.append(pWidget);
    }

    auto pSpacer = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Expanding);
    pLayout->addItem(pSpacer);

    ui->m_pqsaParams->setWidget(pContainer);
}

QVariantList CwmsDynamicParameterDlg::GetInputList()
{
    QVariantList qvlInputs;

    for (int pos = 0; pos < m_qlParamWidgets.count(); ++pos)
    {
        qvlInputs.append(m_qlParamWidgets[pos]->GetInput());
    }

    return qvlInputs;
}

QVariantList CwmsDynamicParameterDlg::AskForFunctionParams(QList<CdmClassMethodParameter>& p_qlParameters, QWidget* parent)
{
    QApplication::setOverrideCursor(QCursor(Qt::ArrowCursor));

    QList<QPair<QString, EdmValueType>> qlInput = ConvertClassParametersToInputParameters(p_qlParameters);
    QVariantList qvlParams;

    if (qlInput.count() > 0)
    {
        qvlParams = GetParamValues(qlInput, parent);
    }

    QApplication::restoreOverrideCursor();
    return qvlParams;
}

QList<QPair<QString, EdmValueType>> CwmsDynamicParameterDlg::ConvertClassParametersToInputParameters(QList<CdmClassMethodParameter>& p_qlParameters)
{
    QList<QPair<QString, EdmValueType>> qlResult;

    for (int pos = 0; pos < p_qlParameters.count(); ++pos)
    {
        CdmClassMethodParameter cParam = p_qlParameters[pos];

        QPair<QString, EdmValueType> pair;
        pair.first = cParam.GetName();
        pair.second = cParam.m_eType;
        qlResult.append(pair);
    }

    return qlResult;
}

QVariantList CwmsDynamicParameterDlg::AskForMemberParams(QList<CdmMember *> &p_qlParameters, QWidget* parent)
{
    QList<QPair<QString, EdmValueType>> qlInput = ConvertMemberParametersToInputParameters(p_qlParameters);

    if (qlInput.count() > 0)
    {
        return GetParamValues(qlInput, parent);
    }

    return QVariantList();
}

QList<QPair<QString, EdmValueType>> CwmsDynamicParameterDlg::ConvertMemberParametersToInputParameters(QList<CdmMember *> &p_qlParameters)
{
    QList<QPair<QString, EdmValueType>> qlResult;

    for (int pos = 0; pos < p_qlParameters.count(); ++pos)
    {
        auto * pMember = p_qlParameters[pos];

        if (CHKPTR(pMember))
        {
            QPair<QString, EdmValueType> pair;
            pair.first = pMember->GetCaption();
            pair.second = pMember->GetValueType();
            qlResult.append(pair);
        }

    }

    return qlResult;
}


QVariantList CwmsDynamicParameterDlg::GetParamValues(QList<QPair<QString, EdmValueType>>& p_qlParameters, QWidget* parent)
{
    CwmsDynamicParameterDlg cDlg(parent);
    cDlg.FillDialog(p_qlParameters);
    if (cDlg.exec() == QDialog::Accepted)
    {
        return cDlg.GetInputList();
    }

    return QVariantList();
}
