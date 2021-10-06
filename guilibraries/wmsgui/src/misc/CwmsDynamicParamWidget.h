#ifndef CWMSDYNAMICPARAMWIDGET_H
#define CWMSDYNAMICPARAMWIDGET_H

// System and Qt Includes
#include <QWidget>

#include "CdmModelElement.h"


class CwmsDynamicParamWidget : public QWidget
{
    Q_OBJECT

private:
    QString m_qstrName;
    EdmValueType m_eType;
    QWidget* m_pInput;

public:
    explicit CwmsDynamicParamWidget(QString p_qstrName, EdmValueType p_eType, QWidget *parent = nullptr);
    virtual ~CwmsDynamicParamWidget();
    void CreateWidget();
    QVariant GetInput();

private:
    void CreateBoolWidget();
    void CreateNumberWidget();
    void CreateTextWidget();
    void CreateDateWidget();
    void CreateDateTimeWidget();
    void CreateTimeWidget();
    void CreateUserWidget();
    void CreateUserGroupWidget();


    QHBoxLayout* CreateLayoutAndLabel();
    QVariant GetBoolValue();
    QVariant GetNumberValue();
    QVariant GetTextValue();
    QVariant GetDateValue();
    QVariant GetDateTimeValue();
    QVariant GetTimeValue();
    QVariant GetUserValue();
signals:

};

#endif // CWMSDYNAMICPARAMWIDGET_H
