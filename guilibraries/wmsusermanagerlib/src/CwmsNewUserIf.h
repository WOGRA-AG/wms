// Header is missing impl started on 25.1.2005

#ifndef CWMSNEWUSERIF_H
#define CWMSNEWUSERIF_H

#ifdef WURZELBLA
#define slots
#endif //
// System and QT Includes
#include <QDialog>


// own Includes
#include "ui_CwmsNewUserDlg.h"



// forwards
class CumUserManager;



class CwmsNewUserIf : public QDialog, public Ui::CwmsNewUserDlg
{
   Q_OBJECT

private:

    CumUserManager* m_rpUserManager;

    bool Validate();
    void HideSchemeIndependentCheckbox();
    bool Save();
public:
   /** +-=---------------------------------------------------------Di 25. Jan 21:57:16 2005*
    * @method  CwmsNewUserIf::CwmsNewUserIf                  // public                            *
    * @return                                                //                                   *
    * @param   QWidget* parent = NULL                        //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 25. Jan 21:57:16 2005----------*/
CwmsNewUserIf(CumUserManager* p_pUserManager, QWidget* parent = NULL);

   public:
   /** +-=---------------------------------------------------------Di 25. Jan 21:57:26 2005*
    * @method  CwmsNewUserIf::~CwmsNewUserIf                 // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CwmsNewUserIf                                              *
    *                                                                                             *
    *----------------last changed: -----------------------------Di 25. Jan 21:57:26 2005----------*/
virtual ~CwmsNewUserIf(  );

    private slots:
   /** +-=---------------------------------------------------------Di 25. Jan 21:58:24 2005*
    * @method  CwmsNewUserIf::OKClickedSlot                  // private, slots                    *
    * @return  void                                          //                                   *
    * @comment This slot will be called if the ok button was clicked. it creates the new user.    *
    *----------------last changed: -----------------------------Di 25. Jan 21:58:24 2005----------*/
void OKClickedSlot(  );

    private slots:
   /** +-=---------------------------------------------------------Di 25. Jan 21:58:55 2005*
    * @method  CwmsNewUserIf::CancelClickedSlot              // private, slots                    *
    * @return  void                                          //                                   *
    * @comment This slot will be called if the cancle button was clicked it cancels the user creation.*
    *----------------last changed: -----------------------------Di 25. Jan 21:58:55 2005----------*/
void CancelClickedSlot(  );

   public:
static QString CreateNewUser(QWidget* p_pqwParent, CumUserManager* p_pUserManager);
};

#endif //
