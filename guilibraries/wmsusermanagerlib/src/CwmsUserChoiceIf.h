// Header is missing impl started on 27.1.2005

#ifndef CWMSUSERCHOICEIF_H
#define CWMSUSERCHOICEIF_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes
#include <QDialog>
#include <QList>


// own Includes
#include "wmsusermanagerglobal.h"
#include "ui_CwmsUserChoiceDlg.h"



// forwards
class CumUser;


class WMSUSERMANAGER_API CwmsUserChoiceIf : public QDialog, public Ui::CwmsUserChoiceDlg
{
   Q_OBJECT


   public:
   /** +-=---------------------------------------------------------Do 27. Jan 07:17:06 2005*
    * @method  CwmsUserChoiceIf::CwmsUserChoiceIf            // public                            *
    * @return                                                //                                   *
    * @param   QWidget* parent = NULL                        //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 27. Jan 07:17:06 2005----------*/
CwmsUserChoiceIf(QWidget* parent = NULL);

   public:
   /** +-=---------------------------------------------------------Do 27. Jan 07:17:12 2005*
    * @method  CwmsUserChoiceIf::~CwmsUserChoiceIf           // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CwmsUserChoiceIf                                           *
    *                                                                                             *
    *----------------last changed: -----------------------------Do 27. Jan 07:17:12 2005----------*/
virtual ~CwmsUserChoiceIf(  );


    private slots:
   /** +-=---------------------------------------------------------Do 27. Jan 07:17:52 2005*
    * @method  CwmsUserChoiceIf::OKClickedSlot               // private, slots                    *
    * @return  void                                          //                                   *
    * @comment This slot will be called if the OK Button was clicked.                             *
    *----------------last changed: -----------------------------Do 27. Jan 07:17:52 2005----------*/
void OKClickedSlot(  );

    private slots:
   /** +-=---------------------------------------------------------Do 27. Jan 07:18:13 2005*
    * @method  CwmsUserChoiceIf::CancelClickedSlot           // private, slots                    *
    * @return  void                                          //                                   *
    * @comment This slot will be called if the cancel button was clicked.                         *
    *----------------last changed: -----------------------------Do 27. Jan 07:18:13 2005----------*/
void CancelClickedSlot(  );

void SearchUserClickedSlot();

   public:
   /** +-=---------------------------------------------------------Mo 29. Okt 15:16:59 2012-------*
    * @method  CwmsUserChoiceIf::GetSelectedUserId           // public                            *
    * @return  int                                           //                                   *
    * @comment This method returns the selected User.                                             *
    *----------------last changed: -----------------------------Mo 29. Okt 15:16:59 2012----------*/
    int GetSelectedUserId();

   public:
   /** +-=---------------------------------------------------------Do 27. Jan 07:42:30 2005*
    * @method  CwmsUserChoiceIf::GetUserSelection            // public, static                    *
    * @return  long                                          // UserId                            *
    * @param   QWidget* parent                               //                                   *
    * @comment This static member function gets a selected user from the complete user list.      *
    *----------------last changed: -----------------------------Do 27. Jan 07:42:30 2005----------*/
static long GetUserSelection(  QWidget* parent );
};

#endif //
