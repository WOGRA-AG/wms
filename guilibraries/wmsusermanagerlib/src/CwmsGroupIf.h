/******************************************************************************
** WOGRA technologies GmbH & Co. KG Modul Information
** Modulename: CwmsGroupIf.cpp
** Started Implementation: 2005/01/26
** Description:
**
** IMplements the form for group management
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
**(C) copyright by WOGRA technologies GmbH & Co. KG All rights reserved
*****************************************************************************/

#ifndef CWMSGROUPIF_H
#define CWMSGROUPIF_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT includes
#include <QList>


// own Includes
#include "ui_CwmsGroupWidget.h"


// forwards
class CumUser;
class CumUserGroup;


class CwmsGroupIf : public QWidget, public Ui::CwmsGroupWidget
{
   Q_OBJECT

private:
    CumUserGroup* m_rpCumUserGroup;
    QList<CumUser*> m_qvlUsers;

public:
    CwmsGroupIf( CumUserGroup*, QWidget*);
    virtual ~CwmsGroupIf();

   private:
   /** +-=---------------------------------------------------------Mi 26. Jan 19:13:04 2005*
    * @method  CwmsGroupIf::FillDialog                       // private                           *
    * @return  void                                          //                                   *
    * @comment This method fills the dialog.                                                      *
    *----------------last changed: -----------------------------Mi 26. Jan 19:13:04 2005----------*/
void FillDialog(  );

   private:
   /** +-=---------------------------------------------------------Mi 26. Jan 19:21:06 2005*
    * @method  CwmsGroupIf::ClearUserList                    // private                           *
    * @return  void                                          //                                   *
    * @comment This method clears the user list.                                                  *
    *----------------last changed: -----------------------------Mi 26. Jan 19:21:06 2005----------*/
void ClearUserList(  );

   private:
   /** +-=---------------------------------------------------------Mi 26. Jan 19:22:13 2005*
    * @method  CwmsGroupIf::FillUserList                     // private                           *
    * @return  void                                          //                                   *
    * @comment This method fills the User Listview                                                *
    *----------------last changed: -----------------------------Mi 26. Jan 19:22:13 2005----------*/
void FillUserList(  );

    private slots:
   /** +-=---------------------------------------------------------Mi 26. Jan 19:26:08 2005*
    * @method  CwmsGroupIf::AddClickedSlot                   // private, slots                    *
    * @return  void                                          //                                   *
    * @comment This slot will be called if the Add Button was clicked. It opens a dialog and the user can add a new user to this group.*
    *----------------last changed: -----------------------------Mi 26. Jan 19:26:08 2005----------*/
void AddClickedSlot(  );

    private slots:
   /** +-=---------------------------------------------------------Mi 26. Jan 19:26:30 2005*
    * @method  CwmsGroupIf::RemoveClickedSlot                // private, slots                    *
    * @return  void                                          //                                   *
    * @comment This slot removes the selected user from group.                                    *
    *----------------last changed: -----------------------------Mi 26. Jan 19:26:30 2005----------*/
void RemoveClickedSlot(  );

    private slots:
   /** +-=---------------------------------------------------------Mi 26. Jan 19:26:53 2005*
    * @method  CwmsGroupIf::UpdateClickedSlot                // private, slots                    *
    * @return  void                                          //                                   *
    * @comment This slot updates all changes on this group.                                       *
    *----------------last changed: -----------------------------Mi 26. Jan 19:26:53 2005----------*/
void UpdateClickedSlot(  );
};

#endif //
