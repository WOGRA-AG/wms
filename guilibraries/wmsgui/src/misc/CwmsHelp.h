/******************************************************************************
 ** WOGRA technologies Gmbh & Co KG Modul Information
 ** Modulename: CwmsHelp.h
 ** Started Implementation: 2012/09/05
 ** Description:
 ** 
 ** implements a simple help viewer
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co KG All rights reserved
 *****************************************************************************/ 

#ifndef CWMSHELP_H
#define CWMSHELP_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes
#include <QDialog>

// Own Includes
#include "ui_CwmsHelp.h"

// Forwards


// TypeDefs

#include "wmsgui.h"

/* 
 * This class implements a simple help viewer
 */
class WMSGUI_API CwmsHelp : public QDialog, public Ui::CwmsHelpClass
{
   Q_OBJECT

   public:
    CwmsHelp(QWidget* p_pqwParent);
    virtual ~CwmsHelp();
    static void ShowTextHelp(QString p_qstrHelp, QWidget* p_pqwParent);
    static void ShowLicence(QString p_qstrHelp, QWidget* p_pqwParent);
    static void ShowHtmlHelp(QString p_qstrHelp, QWidget *p_pqwParent);
};

#endif // CWMSHELP_H
