/******************************************************************************
 ** WOGRA Middleware Server Data Manager Module
 **
 ** @Author Wolfgang Graßhof 
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA Solutions All rights reserved
 ** CVS Changes: $Id: CumLogInList.h,v 1.2 2005/08/20 12:04:14 Wolfi Exp $
 ******************************************************************************/

#ifndef CUMLOGINLIST_H
#define CUMLOGINLIST_H


// System and QT Includes


// own Includes
#include "datamanager.h"

// forwards
class CumLoggedIn;



class WMSMANAGER_API CumLogInList 
{
private:    

    /**
     * @supplierCardinality 0..* 
     */
    CumLoggedIn * lnkCumLoggedIn;

   /** +-=---------------------------------------------------------Sat Feb 1 14:24:43 2003--------*
    * @method  CumLogInList::CumLogInList                    // public                            *
    * @return                                                //                                   *
    * @comment                                                                                    *
    *---------------------------------------------------------------Sat Feb 1 14:24:43 2003-------*/
   public:
      CumLogInList(  );

   /** +-=---------------------------------------------------------Sat Feb 1 14:24:47 2003--------*
    * @method  CumLogInList::~CumLogInList                   // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CumLogInList                                               *
    *                                                                                             *
    *---------------------------------------------------------------Sat Feb 1 14:24:47 2003-------*/
   public:
      virtual ~CumLogInList(  );
};
#endif //CUMLOGINLIST_H
