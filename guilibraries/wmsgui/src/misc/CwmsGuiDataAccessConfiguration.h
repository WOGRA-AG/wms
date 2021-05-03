#ifndef CWMSGUIDATAACCESSCONFIGURATION_H
#define CWMSGUIDATAACCESSCONFIGURATION_H

// System and Qt Includes
#include <QDialog>

// WMS QML Includes
#include "wmsgui.h"
#include "CwmsDataAccessConfiguration.h"


namespace Ui {
class CwmsGuiDataAccessConfigurationUi;
}

class WMSGUI_API CwmsGuiDataAccessConfiguration : public QDialog
{
    Q_OBJECT

public:
    explicit CwmsGuiDataAccessConfiguration(QWidget *parent = 0);
    ~CwmsGuiDataAccessConfiguration();

    void FillDialog();
public slots:
    void OkClickedSlot();
    void DeleteClickedSlot();
    void EditClickedSlot();
    void NewClickedSlot();
    void TestClickedSlot();
private:
    Ui::CwmsGuiDataAccessConfigurationUi *ui;
    CwmsDataAccessConfiguration m_Config;
    QString GetSelectedTreeConfig();
    void OpenPluginEditor(QString p_qstrConfig, QString p_qstrPlugin);
};

#endif // CWMSGUIDATAACCESSCONFIGURATION_H
