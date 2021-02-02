/******************************************************************************
 ** WOGRA technologies GmbH & Co. KG Modul Information
 ** Modulename: CwmsScriptableUi.cpp
 ** Started Implementation: 2012/11/27
 ** Description:
 **
 ** implements ui calls for the script environment.
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co. KG All rights reserved
 *****************************************************************************/

// System and QT Includes

// WMS Includes
#include "CdmLogging.h"
#include "CdmObject.h"
#include "CdmObjectContainer.h"
#include "CdmQueryEnhanced.h"

// own Includes
#include "CwmsScriptableUi.h"

/** +-=---------------------------------------------------------Di 27. Nov 16:42:15 2012----------*
 * @method  CwmsScriptableUi::CwmsScriptableUi               // public                            *
 * @return                                                   //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 27. Nov 16:42:15 2012----------*/
CwmsScriptableUi::CwmsScriptableUi()
{
}

/** +-=---------------------------------------------------------Di 27. Nov 16:42:22 2012----------*
 * @method  CwmsScriptableUi::~CwmsScriptableUi              // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CwmsScriptableUi                                              *
 *----------------last changed: --------------------------------Di 27. Nov 16:42:22 2012----------*/
CwmsScriptableUi::~CwmsScriptableUi()
{
}

/** +-=---------------------------------------------------------Di 27. Nov 16:43:00 2012----------*
 * @method  CwmsScriptableUi::OpenUi                         // public, slots                     *
 * @return  void                                             //                                   *
 * @param   CdmObject* p_pCdmObject                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 27. Nov 16:43:00 2012----------*/
void CwmsScriptableUi::openUi(CdmObject* p_pCdmObject)
{
   Q_UNUSED(p_pCdmObject);
}

/** +-=---------------------------------------------------------Di 27. Nov 16:43:34 2012----------*
 * @method  CwmsScriptableUi::OpenUi                         // public, slots                     *
 * @return  void                                             //                                   *
 * @param   CdmObjectContainer* p_pContainer                  //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 27. Nov 16:43:34 2012----------*/
void CwmsScriptableUi::openUi(CdmObjectContainer* p_pContainer)
{
   Q_UNUSED(p_pContainer);
}

/** +-=---------------------------------------------------------Di 27. Nov 16:43:52 2012----------*
 * @method  CwmsScriptableUi::OpenSearch                     // public, slots                     *
 * @return  void                                             //                                   *
 * @param   CdmObjectContainer* p_pContainer                  //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 27. Nov 16:43:52 2012----------*/
void CwmsScriptableUi::openSearch(CdmObjectContainer* p_pContainer)
{
   Q_UNUSED(p_pContainer);
}

/** +-=---------------------------------------------------------Di 27. Nov 16:44:44 2012----------*
 * @method  CwmsScriptableUi::OpenImport                     // public, slots                     *
 * @return  void                                             //                                   *
 * @param   CdmObjectContainer* p_pContainer                  //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 27. Nov 16:44:44 2012----------*/
void CwmsScriptableUi::openImport(CdmObjectContainer* p_pContainer)
{
   Q_UNUSED(p_pContainer);
}

/** +-=---------------------------------------------------------Di 27. Nov 16:45:03 2012----------*
 * @method  CwmsScriptableUi::OpenExport                     // public, slots                     *
 * @return  void                                             //                                   *
 * @param   CdmObjectContainer* p_pContainer                  //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 27. Nov 16:45:03 2012----------*/
void CwmsScriptableUi::openExport(CdmObjectContainer* p_pContainer)
{
   Q_UNUSED(p_pContainer);
}

/** +-=---------------------------------------------------------Di 27. Nov 16:46:13 2012----------*
 * @method  CwmsScriptableUi::OpenHistory                    // public, slots                     *
 * @return  void                                             //                                   *
 * @param   CdmObjectContainer* p_pContainer                  //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 27. Nov 16:46:13 2012----------*/
void CwmsScriptableUi::openHistory(CdmObjectContainer* p_pContainer)
{
   Q_UNUSED(p_pContainer);
}

/** +-=---------------------------------------------------------Di 27. Nov 16:46:31 2012----------*
 * @method  CwmsScriptableUi::OpenHistory                    // public, slots                     *
 * @return  void                                             //                                   *
 * @param   CdmObject* p_pCdmObject                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 27. Nov 16:46:31 2012----------*/
void CwmsScriptableUi::openHistory(CdmObject* p_pCdmObject)
{
   Q_UNUSED(p_pCdmObject);
}

/** +-=---------------------------------------------------------Di 27. Nov 16:47:35 2012----------*
 * @method  CwmsScriptableUi::SelectObject                   // public                            *
 * @return  QObject*                                         //                                   *
 * @param   CdmObjectContainer* p_pContainer                  //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 27. Nov 16:47:35 2012----------*/
QObject* CwmsScriptableUi::selectObject(CdmObjectContainer* p_pContainer)
{
   QObject* pRet = nullptr;

   Q_UNUSED(p_pContainer);

   return pRet;
}

/** +-=---------------------------------------------------------Di 27. Nov 16:47:59 2012----------*
 * @method  CwmsScriptableUi::SelectObjectList               // public                            *
 * @return  QObject*                                         //                                   *
 * @param   CdmClass* p_pCdmClass                            //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 27. Nov 16:47:59 2012----------*/
QObject* CwmsScriptableUi::selectObjectList(CdmClass* p_pCdmClass)
{
   QObject* pRet = nullptr;

   Q_UNUSED(p_pCdmClass);


   return pRet;
}

/** +-=---------------------------------------------------------Di 27. Nov 16:49:03 2012----------*
 * @method  CwmsScriptableUi::EditPrintingTemplate           // public, slots                     *
 * @return  void                                             //                                   *
 * @param   CdmObjectContainer* p_pContainer                  //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 27. Nov 16:49:03 2012----------*/
void CwmsScriptableUi::editPrintingTemplate(CdmObjectContainer* p_pContainer)
{
   Q_UNUSED(p_pContainer);
}

/** +-=---------------------------------------------------------Di 27. Nov 16:48:54 2012----------*
 * @method  CwmsScriptableUi::EditPrintingTemplate           // public, slots                     *
 * @return  void                                             //                                   *
 * @param   CdmObject* p_pCdmObject                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 27. Nov 16:48:54 2012----------*/
void CwmsScriptableUi::editPrintingTemplate(CdmObject* p_pCdmObject)
{
   Q_UNUSED(p_pCdmObject);
}

/** +-=---------------------------------------------------------Di 27. Nov 16:49:32 2012----------*
 * @method  CwmsScriptableUi::SelectClass                    // public                            *
 * @return  QObject*                                         //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 27. Nov 16:49:32 2012----------*/
QObject* CwmsScriptableUi::selectClass()
{
   QObject* pRet = nullptr;

   return pRet;
}
