#ifndef CWMSLOGINIF_H
#define CWMSLOGINIF_H

#ifdef WURZELBLA
#define slots
#endif



// System and QT Includes
#include <QDialog>
#include <QSettings>


// own Includes
#include "wmsgui.h"
#include "CdmSettings.h"
#include "ui_cwmslogindlg.h"


// forwards
class CdmDataAccess;


class WMSGUI_API CwmsGuiLoginIf : public QDialog, public Ui::CwmsLoginDlg
{
    Q_OBJECT

private:
    CdmSettings m_cCdmSettings;
    QSettings m_qSettings;
    QString m_qstrApplicationName;

    static bool loginP(QString p_qstrApplication, QString p_qstrLogin, QString p_qstrPassword);
public:
    virtual ~CwmsGuiLoginIf(  );
    void SetCaption(  QString p_qstrCaption );
    void SetApplicationInfoText(  QString p_qstrLoginLabel );
    CwmsGuiLoginIf( QString p_qstrAppliactionName, QWidget* parent = nullptr);

    static bool Login(QString p_qstrApplicationName,
                      QWidget* p_pqwParent );
    static  bool TryLogin(QString p_qstrLogin, QString p_qstrPassword, QString p_qstrApplicationName, CwmsGuiLoginIf* pCwmsLoginIf);

protected slots:
    virtual void CancelClickedSlot(  );
    virtual void OKClickedSlot(  );

private slots:
    void ClientSettingsClickedSlot( );
    void LdapSettingsClickedSlot( );
    bool LdapLogin(QString username, QString passwd);
};


#endif
