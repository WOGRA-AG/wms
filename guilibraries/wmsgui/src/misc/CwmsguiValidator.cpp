/******************************************************************************
 ** WOGRA Middleware Server Data Manager Module
 **
 ** @Author Wolfgang Graßhof 
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies All rights reserved
 ** CVS Changes: $Id: CwmsguiValidator.cpp,v 1.1 2006/03/03 22:44:48 Entwicklung Exp $
 ******************************************************************************/



// System and QT Includes



// own Includes
#include "CwmsguiValidator.h"



/** +-=---------------------------------------------------------Do 23. Feb 11:11:46 2006----------*
 * @method  CwmsguiValidator::CwmsguiValidator               // public                            *
 * @return                                                   //                                   *
 * @comment The baseclass constructor. It does nothing.                                           *
 *----------------last changed: Wolfgang Graßhof----------------Do 23. Feb 11:11:46 2006----------*/
CwmsguiValidator::CwmsguiValidator()
{
   // nothing to do
}

/** +-=---------------------------------------------------------Do 23. Feb 11:11:53 2006----------*
 * @method  CwmsguiValidator::~CwmsguiValidator              // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CwmsguiValidator                                              *
 *----------------last changed: Wolfgang Graßhof----------------Do 23. Feb 11:11:53 2006----------*/
CwmsguiValidator::~CwmsguiValidator()
{
   // nothing to do
}

/** +-=---------------------------------------------------------Do 23. Feb 11:15:09 2006----------*
 * @method  CwmsguiValidator::Validate                       // public, p virtual                 *
 * @return  bool                                             //                                   *
 * @comment This is the abstract method which must be overwritten by derived classes. this        *
 *          method will be called in editing gui components. If this method returns true. The     *
 *          commit will be done by the gui component. If not, no commit will be done.             *
 *----------------last changed: Wolfgang Graßhof----------------Do 23. Feb 11:15:09 2006----------*/
