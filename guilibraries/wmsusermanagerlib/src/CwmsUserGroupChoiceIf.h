// Header is missing impl started on 27.1.2005

#ifndef CwmsUserGroupChoiceIf_H
#define CwmsUserGroupChoiceIf_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes
#include <QDialog>
#include <QLinkedList>


// own Includes
#include "wmsusermanagerglobal.h"
#include "ui_CwmsUserGroupChoiceIf.h"



// forwards
class CumUser;


class WMSUSERMANAGER_API CwmsUserGroupChoiceIf : public QDialog, public Ui::CwmsUserGroupChoiceDlg
{
   Q_OBJECT


   public:
   /** +-=---------------------------------------------------------Do 27. Jan 07:17:06 2005*
    * @method  CwmsUserGroupChoiceIf::CwmsUserGroupChoiceIf            // public                            *
    * @return                                                //                                   *
    * @param   QWidget* parent = NULL                        //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 27. Jan 07:17:06 2005----------*/
CwmsUserGroupChoiceIf(QWidget* parent = NULL);

   public:
   /** +-=---------------------------------------------------------Do 27. Jan 07:17:12 2005*
    * @method  CwmsUserGroupChoiceIf::~CwmsUserGroupChoiceIf           // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CwmsUserGroupChoiceIf                                           *
    *                                                                                             *
    *----------------last changed: -----------------------------Do 27. Jan 07:17:12 2005----------*/
virtual ~CwmsUserGroupChoiceIf(  );


    private slots:
   /** +-=---------------------------------------------------------Do 27. Jan 07:17:52 2005*
    * @method  CwmsUserGroupChoiceIf::OKClickedSlot               // private, slots                    *
    * @return  void                                          //                                   *
    * @comment This slot will be called if the OK Button was clicked.                             *
    *----------------last changed: -----------------------------Do 27. Jan 07:17:52 2005----------*/
void OKClickedSlot(  );

    private slots:
   /** +-=---------------------------------------------------------Do 27. Jan 07:18:13 2005*
    * @method  CwmsUserGroupChoiceIf::CancelClickedSlot           // private, slots                    *
    * @return  void                                          //                                   *
    * @comment This slot will be called if the cancel button was clicked.                         *
    *----------------last changed: -----------------------------Do 27. Jan 07:18:13 2005----------*/
void CancelClickedSlot(  );

void SearchGroupClickedSlot();

   public:
    int GetSelectedGroupId();

   public:
    static long GetGroupSelection(  QWidget* parent );
};

#endif //
