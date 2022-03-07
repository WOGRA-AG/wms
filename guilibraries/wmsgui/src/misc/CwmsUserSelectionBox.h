/******************************************************************************
 ** WOGRA technologies GmbH & Co KG Modul Information
 ** Modulename: CwmsUserSelectionBox.h
 ** Started Implementation: 2009/11/14
 ** Description:
 ** 
 ** implements the selection box for users
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co KG All rights reserved
 *****************************************************************************/ 

#ifndef CWMSUSERSELECTIONBOX_H
#define CWMSUSERSELECTIONBOX_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes
#include <QComboBox>
#include <QMap>
#include <QList>

// Own Includes
#include "wmsgui.h"


// Forwards
class CumUser;
class CumUserGroup;

// Enumerations

/* 
 * This class implements the selection box for users
 */
class WMSGUI_API CwmsUserSelectionBox : public QComboBox
{
   
   public:
   /** +-=---------------------------------------------------------Mo 29. Okt 09:31:30 2012-------*
    * @method  CwmsUserSelectionBox::CwmsUserSelectionBox    // public                            *
    * @return                                                //                                   *
    * @param   QWidget* p_pqwParent = NULL                   //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 29. Okt 09:31:30 2012----------*/
    CwmsUserSelectionBox( QWidget* p_pqwParent = NULL);

   public:
   /** +-=---------------------------------------------------------Sa 14. Nov 11:14:37 2009-------*
    * @method  CwmsUserSelectionBox::~CwmsUserSelectionBox   // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CwmsUserSelectionBox                                       *
    *----------------last changed: -----------------------------Sa 14. Nov 11:14:37 2009----------*/
    virtual ~CwmsUserSelectionBox( );

   private:
   /** +-=---------------------------------------------------------Sa 14. Nov 11:14:55 2009-------*
    * @method  CwmsUserSelectionBox::FillComboBox            // private                           *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Sa 14. Nov 11:14:55 2009----------*/
    void FillComboBox();

   public:
   /** +-=---------------------------------------------------------Sa 14. Nov 11:15:23 2009-------*
    * @method  CwmsUserSelectionBox::SetCurrentUser          // public                            *
    * @return  void                                          //                                   *
    * @param   int p_iUserId                                 //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Sa 14. Nov 11:15:23 2009----------*/
    void SetCurrentUser(int p_iUserId);

   public:
   /** +-=---------------------------------------------------------Di 12. Mrz 12:59:50 2013-------*
    * @method  CwmsUserSelectionBox::SetCurrentUser          // public                            *
    * @return  void                                          //                                   *
    * @param   const CumUser* p_CumUser                      //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 12. Mrz 12:59:50 2013----------*/
    void SetCurrentUser(const CumUser* p_CumUser);

   public:
   /** +-=---------------------------------------------------------Sa 14. Nov 11:16:38 2009-------*
    * @method  CwmsUserSelectionBox::GetSelectedUser         // public                            *
    * @return  CumUser*                                      //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Sa 14. Nov 11:16:38 2009----------*/
    CumUser* GetSelectedUser();

   public:
   /** +-=---------------------------------------------------------Sa 14. Nov 11:16:49 2009-------*
    * @method  CwmsUserSelectionBox::GetSelectedUserId       // public                            *
    * @return  int                                           //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Sa 14. Nov 11:16:49 2009----------*/
    int GetSelectedUserId();

    void FillComboBoxWithGivenUserGroup(CumUserGroup *pUserGroup);
private:
   /** +-=---------------------------------------------------------Sa 14. Nov 11:29:57 2009-------*
    * @method  CwmsUserSelectionBox::GetUserList             // private                           *
    * @return  void                                          //                                   *
    * @param   QList<CumUser*>& p_rqllUsers            //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Sa 14. Nov 11:29:57 2009----------*/
    void GetUserList(QList<CumUser*>& p_rqllUsers);
};

#endif //
