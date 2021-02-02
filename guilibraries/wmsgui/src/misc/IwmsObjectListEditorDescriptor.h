/******************************************************************************
 ** WOGRA technologies Gmbh & Co KG Modul Information
 ** Modulename: IwmsObjectEditorDescriptor.h
 ** Started Implementation: 2012/12/17
 ** Description:
 ** 
 ** interface of an descriptor for opening an objectlisteditor
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co KG All rights reserved
 *****************************************************************************/ 

#ifndef IWMSOBJECTLISTEDITORDESCRIPTOR_H
#define IWMSOBJECTLISTEDITORDESCRIPTOR_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes
#include <QString>

// Own Includes
#include "wmsgui.h"
#include "CwmsguiObjectEditorSelector.h"

// Forwards
class CdmObject;
class QWidget;


// TypeDefs


/* 
 * interface of an descriptor for opening an objectlisteditor
 */
class WMSGUI_API IwmsObjectListEditorDescriptor
{
   public:
      virtual QString GetClassKeyname() = 0;
      virtual bool DisplayEditor(CdmObjectContainer* p_pCdmObject, 
                                 EwmsGuiDisplayMode p_eDisplayMode, 
                                 QWidget* p_pqwParent) = 0;

};

#endif // IWMSOBJECTEDITORDESCRIPTOR_H
