#ifndef CWMSDYNAMICPARAMETERDLG_H
#define CWMSDYNAMICPARAMETERDLG_H

#include <CdmClassMethod.h>
#include <QDialog>

namespace Ui {
class CwmsDynamicParameterDlg;
}

class CwmsDynamicParamWidget;

class CwmsDynamicParameterDlg : public QDialog
{
    Q_OBJECT

private:
    Ui::CwmsDynamicParameterDlg *ui;
    QList<QPair<QString, EdmValueType>> m_qlInputs;
    QList<CwmsDynamicParamWidget*> m_qlParamWidgets;

public:
    explicit CwmsDynamicParameterDlg(QWidget *parent = nullptr);
    ~CwmsDynamicParameterDlg();
    void FillDialog(QList<QPair<QString, EdmValueType>>& p_qlInput);
    QVariantList GetInputList();

    static QVariantList AskForFunctionParams(QList<CdmClassMethodParameter> &p_qlParameters, QWidget *parent);
    static QVariantList AskForMemberParams(QList<CdmMember*> &p_qlParameters, QWidget *parent);
private:

    static QList<QPair<QString, EdmValueType>> ConvertClassParametersToInputParameters(QList<CdmClassMethodParameter> &p_qlParameters);
    static QList<QPair<QString, EdmValueType>> ConvertMemberParametersToInputParameters(QList<CdmMember *> &p_qlParameters);
    static QVariantList GetParamValues(QList<QPair<QString, EdmValueType> > &p_qlParameters, QWidget *parent);
};

#endif // CWMSDYNAMICPARAMETERDLG_H
