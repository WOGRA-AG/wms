#ifndef CWMSDATAACCESSCONFIGURATOR_H
#define CWMSDATAACCESSCONFIGURATOR_H

// System and Qt Includes
#include <QDialog>


// own Includes
#include "CwmsDataAccessConfiguration.h"

namespace Ui {
class CwmsDataAccessConfigurator;
}

class CwmsDataAccessConfigurator : public QDialog
{
    Q_OBJECT
private:
    Ui::CwmsDataAccessConfigurator *ui;
    CwmsDataAccessConfiguration m_Config;

    void FillConfigData();
    bool Validate();
    bool Save();
public:
    explicit CwmsDataAccessConfigurator(QWidget *parent = 0);
    ~CwmsDataAccessConfigurator();


    void FillDialog(QString p_qstrConfigName, QString p_qstrPluginName);

public slots:
    void DatasourceTypeChangedSlot();
    void OKClickedSlot();
};

#endif // CWMSDATAACCESSCONFIGURATOR_H
