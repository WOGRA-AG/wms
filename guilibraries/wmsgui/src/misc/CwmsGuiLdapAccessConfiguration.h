#ifndef CWMSGUILDAPACCESSCONFIGURATION_H
#define CWMSGUILDAPACCESSCONFIGURATION_H

#include <QDialog>
#include <QWidget>

#include "CdmSettings.h"
#include "wmsgui.h"


namespace Ui {
class CwmsGuiLdapAccessConfigurationClass;
}

class WMSGUI_API CwmsGuiLdapAccessConfiguration : public QDialog
{
    Q_OBJECT

public:
    //explicit Dialog(QDialog *parent = 0, Settings *s = NULL, Cldap *cset = NULL, int *h = NULL);
    explicit CwmsGuiLdapAccessConfiguration(CdmSettings *m_cCdmSettings, QWidget *parent);
    ~CwmsGuiLdapAccessConfiguration();

private:
    Ui::CwmsGuiLdapAccessConfigurationClass *ui;
    CdmSettings *m_cCdmSettings;

    void loadSettings();
    void saveSettings();

private slots:
    void doSave();
    void doTest();
    void doCancel();
};

#endif // CWMSGUILDAPACCESSCONFIGURATION_H
