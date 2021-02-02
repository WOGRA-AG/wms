// Header is missing impl started on 25.1.2005


#ifndef CWMSUSERIF_H
#define CWMSUSERIF_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT includes
#include <QWidget>
#include <QLinkedList>


// own Inlcudes
#include "ui_CwmsUserWidget.h"


// forwards
class CumUser;
class CumUserGroup;

class CwmsUserIf : public QWidget, public Ui::CwmsUserWidget
{
   Q_OBJECT


   private:
      CumUser* m_rpCumUser;
      QLinkedList<CumUserGroup*> m_qvlUserGroups;


   public:
   /** +-=---------------------------------------------------------Di 25. Jan 20:13:45 2005*
    * @method  CwmsUserIf::CwmsUserIf                        // public                            *
    * @return                                                //                                   *
    * @param   CumUser* p_pCumUser                           //                                   *
    * @param   QWidget* p_pqwParent = NULL                   //                                   *
    * @comment Constructor for initializing values.                                               *
    *----------------last changed: -----------------------------Di 25. Jan 20:13:45 2005----------*/
CwmsUserIf(  CumUser* p_pCumUser, QWidget* p_pqwParent = NULL);

   public:
   /** +-=---------------------------------------------------------Di 25. Jan 20:14:53 2005*
    * @method  CwmsUserIf::~CwmsUserIf                       // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CwmsUserIf                                                 *
    *                                                                                             *
    *----------------last changed: -----------------------------Di 25. Jan 20:14:53 2005----------*/
virtual ~CwmsUserIf(  );

public slots:
void AddScheme();
void RemoveScheme();
void AddGroup();
void RemoveGroup();
private:
   /** +-=---------------------------------------------------------Di 25. Jan 20:15:11 2005*
    * @method  CwmsUserIf::FillDialog                        // private                           *
    * @return  void                                          //                                   *
    * @comment This method fills the user widget.                                                 *
    *----------------last changed: -----------------------------Di 25. Jan 20:15:11 2005----------*/
void FillDialog(  );

void FillGroups();

void FillSchemes();
private slots:
   /** +-=---------------------------------------------------------Di 25. Jan 20:23:17 2005*
    * @method  CwmsUserIf::ChangePasswordClickedSlot         // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 25. Jan 20:23:17 2005----------*/
void ChangePasswordClickedSlot(  );


    private slots:
   /** +-=---------------------------------------------------------Di 25. Jan 20:23:39 2005*
    * @method  CwmsUserIf::UpdateCLickedSlot                 // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 25. Jan 20:23:39 2005----------*/
void UpdateCLickedSlot(  );
};


#endif //
