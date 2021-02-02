// Header is missing impl started on 25.1.2005

#ifndef CWMSPASSWORDIF_H
#define CWMSPASSWORDIF_H


// System and QT Includes
#include <QDialog>


// own Includes
#include "wmsusermanagerglobal.h"
#include "ui_CwmsPasswordDlg.h"



// forwards
class CumUser;



class WMSUSERMANAGER_API CwmsPasswordIf : public QDialog, public Ui::CwmsNewPasswordDlg
{
   Q_OBJECT

   private:
      CumUser* m_rpUser;

   public:
   /** +-=---------------------------------------------------------Mi 7. Sep 15:20:48 2011--------*
    * @method  CwmsPasswordIf::CwmsPasswordIf                // public                            *
    * @return                                                //                                   *
    * @param   QString p_qstrOriginalPasswort                //                                   *
    * @param   QWidget* parent = NULL                        //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 7. Sep 15:20:48 2011-----------*/
    CwmsPasswordIf(CumUser* p_pUser,
                    QWidget* parent = NULL);

   public:
   /** +-=---------------------------------------------------------Di 25. Jan 22:20:38 2005*
    * @method  CwmsPasswordIf::~CwmsPasswordIf               // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CwmsPasswordIf                                             *
    *                                                                                             *
    *----------------last changed: -----------------------------Di 25. Jan 22:20:38 2005----------*/
virtual ~CwmsPasswordIf(  );

    private slots:
   /** +-=---------------------------------------------------------Di 25. Jan 22:24:12 2005*
    * @method  CwmsPasswordIf::CancelClickedSlot             // private, slots                    *
    * @return  void                                          //                                   *
    * @comment This slot will be called if the cancle button was clicked. it rejects the dialog.  *
    *----------------last changed: -----------------------------Di 25. Jan 22:24:12 2005----------*/
void CancelClickedSlot(  );

    private slots:
   /** +-=---------------------------------------------------------Di 25. Jan 22:24:38 2005*
    * @method  CwmsPasswordIf::OKClickedSlot                 // private, slots                    *
    * @return  void                                          //                                   *
    * @comment This slot will be called if the ok button was clicked it accepts the changes.      *
    *----------------last changed: -----------------------------Di 25. Jan 22:24:38 2005----------*/
void OKClickedSlot(  );

   public:
   /** +-=---------------------------------------------------------Di 25. Jan 22:31:28 2005*
    * @method  CwmsPasswordIf::ChangePassword                // public, static                    *
    * @return  bool                                          //                                   *
    * @param   CumUser* p_pCumUser                           //                                   *
    * @param   QWidget* parent                               //                                   *
    * @comment This is static memeber function which is able to change the user password.         *
    *----------------last changed: -----------------------------Di 25. Jan 22:31:28 2005----------*/
static bool ChangePassword(  CumUser* p_pCumUser, QWidget* parent );
};

#endif //
