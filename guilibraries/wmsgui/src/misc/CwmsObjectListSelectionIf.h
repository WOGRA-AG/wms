/******************************************************************************
 ** WOGRA Middleware Server GUI Tools Module
 **
 ** @Author Wolfgang Graßhof 
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies All rights reserved
 ******************************************************************************/


#ifndef CWMSOBJECTLISTSELECTIONIF_H
#define CWMSOBJECTLISTSELECTIONIF_H


// System and QT Includes
#include <QDialog>


// own Includes
#include "wmsgui.h"
#include "ui_CwmsObjectListSelection.h"


// forwards
class CdmClass;


class WMSGUI_API CwmsContainerSelectionIf : public QDialog, public Ui::CwmsObjectListSelection
{
   private:
      long m_lDbId;


   public:
   /** +-=---------------------------------------------------------Di 28. Sep 14:38:59 2010-------*
    * @method  CwmsObjectListSelectionIf::CwmsObjectListSelectionIf // public                     *
    * @return                                                //                                   *
    * @param   QWidget* parent = NULL                        //                                   *
    * @comment The constructor                                                                    *
    *----------------last changed: -----------------------------Di 28. Sep 14:38:59 2010----------*/
    CwmsContainerSelectionIf( QWidget* parent = NULL);

   public:
   /** +-=---------------------------------------------------------Mo 23. Jan 21:26:24 2006*
    * @method  CwmsObjectListSelectionIf::~CwmsObjectListSelectionIf // public, virtual           *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CwmsObjectListSelectionIf                                  *
    *                                                                                             *
    *----------------last changed: Wolfgang Graßhof-------------Mo 23. Jan 21:26:24 2006----------*/
virtual ~CwmsContainerSelectionIf(  );

   public:
   /** +-=---------------------------------------------------------Mo 23. Jan 21:26:53 2006*
    * @method  CwmsObjectListSelectionIf::SetClass           // public                            *
    * @return  void                                          //                                   *
    * @param   CdmClass* pCdmClass                           //                                   *
    * @comment                                                                                    *
    *----------------last changed: Wolfgang Graßhof-------------Mo 23. Jan 21:26:53 2006----------*/
void SetClass(  CdmClass* pCdmClass );

   public:
   /** +-=---------------------------------------------------------Mo 23. Jan 21:52:52 2006*
    * @method  CwmsObjectListSelectionIf::SetClass           // public                            *
    * @return  void                                          //                                   *
    * @param   long p_lDbId                                  //                                   *
    * @param   long p_lClassId                               //                                   *
    * @comment                                                                                    *
    *----------------last changed: Wolfgang Graßhof-------------Mo 23. Jan 21:52:52 2006----------*/
void SetClass(  long p_lDbId, long p_lClassId );


   public:
   /** +-=---------------------------------------------------------Mo 23. Jan 22:00:49 2006*
    * @method  CwmsObjectListSelectionIf::GetSelectedObjectList // public                         *
    * @return  CdmObjectContainer*                                //                                   *
    * @comment This method returns the selected obejctlist.                                       *
    *----------------last changed: Wolfgang Graßhof-------------Mo 23. Jan 22:00:49 2006----------*/
CdmObjectContainer* GetSelectedObjectContainer(  );

   public:
   /** +-=---------------------------------------------------------Mo 23. Jan 22:35:56 2006*
    * @method  CwmsObjectListSelectionIf::GetObjectContainer      // public, static                    *
    * @return  CdmObjectContainer*                                //                                   *
    * @param   long p_lDbId                                  //                                   *
    * @param   long p_lClassId                               //                                   *
    * @param   QWidget* p_pqwParent                          //                                   *
    * @comment This method does the static method call.                                           *
    *----------------last changed: Wolfgang Graßhof-------------Mo 23. Jan 22:35:56 2006----------*/
static CdmObjectContainer* GetObjectContainer(  long p_lDbId, long p_lClassId, QWidget* p_pqwParent );

    public:
    int GetContainerCount();
};

#endif //
