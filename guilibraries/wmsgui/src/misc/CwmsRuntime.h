/******************************************************************************
 ** WOGRA technologies Gmbh & Co KG Modul Information
 ** Modulename: CwmsRuntime.h
 ** Started Implementation: 2012/08/30
 ** Description:
 **
 ** implements the runtime for wms apps
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 **(C) copyright by WOGRA technologies GmbH & Co KG All rights reserved
 *****************************************************************************/

#ifndef CWMSRUNTIME_H
#define CWMSRUNTIME_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes
#include <QMainWindow>


// Own Includes
#include "CwmsRuntimeBase.h"
#include "ui_CwmsRuntime.h"

// Forwards
class CwmsUserManagerIf;

// TypeDefs


/* 
 * This class implements the runtime environment for wms apps
 */
class WMSGUI_API CwmsRuntime : public QMainWindow, public CwmsRuntimeBase, public Ui::CwmsRuntimeClass
{
   Q_OBJECT

private:
   CwmsApplication m_cApp;
   CwmsApplicationModule m_cDefaultModule;
   CwmsApplicationModule m_cCurrentModule;
   CwmsUserManagerIf* m_pCwmsUserManager;
   bool m_bLogoffOnExit;
   CwmsTranslator m_cTranslator;
   QList<QToolBar*> m_qlToolbars;
   QMenu* m_pqCurrentModuleMenu;
   QToolBar* m_pqCurrentModuleToolbar;

public:
   CwmsRuntime( QWidget* p_pqwParent);
   virtual ~CwmsRuntime( );
   void SetApplication(CwmsApplication p_cApp);
   void FillWidget();
   void SetCurrentModuleMenu(QMenu* p_pMenu);
   QString GetBuild();
   void SetLogoutOnExit(bool p_bLogout);
   QWidget* GetMainWidget();
   CwmsApplication GetApplication();
   void AddToolBar(QToolBar* p_pToolBar);

public slots:
   void LdapSettingsSlot();
protected:
   void closeEvent(QCloseEvent* p_pqCloseEvent);


private:
   void FillModules();
   void OpenDefaultModule();


private slots:
   void ClientSettingsSlot( );
   void HelpSlot( );
   void InfoSlot();
   void UserManagerSlot();
   void EditActionTriggeredSlot();
   void ChangePasswordSlot( );
   void LanguageSlot( );
   void SmtpSlot( );
   void PluginsSlot();

};

#endif // // WMSRUNTIME_H
