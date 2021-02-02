/******************************************************************************
 ** WOGRA Middleware Server Data Manager Module
 **
 ** @Author Wolfgang Graï¿½of 
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies All rights reserved
 ** CVS Changes: $Id: CwmsguiValidator.h,v 1.1 2006/03/03 22:44:49 Entwicklung Exp $
 ******************************************************************************/

#ifndef CWMSGUIVALIDATOR_H
#define CWMSGUIVALIDATOR_H


// System and QT Includes



// own Includes
#include "wmsgui.h"

// forwards


class WMSGUI_API CwmsguiValidator
{



   public:
   /** +-=---------------------------------------------------------Do 23. Feb 11:11:46 2006-------*
    * @method  CwmsguiValidator::CwmsguiValidator            // public                            *
    * @return                                                //                                   *
    * @comment The baseclass constructor. It does nothing.                                        *
    *----------------last changed: Wolfgang Graï¿½of-------------Do 23. Feb 11:11:46 2006----------*/
    CwmsguiValidator( );

   public:
   /** +-=---------------------------------------------------------Do 23. Feb 11:11:53 2006-------*
    * @method  CwmsguiValidator::~CwmsguiValidator           // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CwmsguiValidator                                           *
    *----------------last changed: Wolfgang Graï¿½of-------------Do 23. Feb 11:11:53 2006----------*/
    virtual ~CwmsguiValidator( );

   public:
   /** +-=---------------------------------------------------------Do 23. Feb 11:15:09 2006-------*
    * @method  CwmsguiValidator::Validate                    // public, p virtual                 *
    * @return  bool                                          //                                   *
    * @comment This is the abstract method which must be overwritten by derived classes. this     *
    *          method will be called in editing gui components. If this method returns true. The  *
    *          commit will be done by the gui component. If not, no commit will be done.          *
    *----------------last changed: Wolfgang Graï¿½of-------------Do 23. Feb 11:15:09 2006----------*/
    virtual bool Validate()= 0;
};

#endif //
