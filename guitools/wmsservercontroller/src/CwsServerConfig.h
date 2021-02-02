#ifndef CWSSERVERCONFIG_H
#define CWSSERVERCONFIG_H

#include <QDialog>

namespace Ui {
class CwsServerConfig;
}

// forwards
class QSettings;

class CwsServerConfig : public QDialog
{
    Q_OBJECT

private:
    Ui::CwsServerConfig *ui;
    QSettings* m_pSettings;

public:
    explicit CwsServerConfig(QWidget *parent = 0);
    ~CwsServerConfig();

    void FillDialog();
public slots:
    void DaemonLogPathClickedSlot();
    void ApplicationLogPathClickedSlot();
    void DataAccessClickedSlot();
    void ServerExecutableClickedSlot();
    void OKClickedSlot();
    void FillPlugins();
    void OptionSelectedSlot();
private:
    bool Save();
    bool Validate();
    bool ServerLogout();
    bool ServerLogin();
};

#endif // CWSSERVERCONFIG_H
