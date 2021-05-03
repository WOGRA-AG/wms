/******************************************************************************
 ** WOGRA technologies GmbH & Co KG Modul Information
 ** Modulename: CwmsbtRightsGroup.cpp
 ** Started Implementation: 2010/05/08
 ** Description:
 ** 
 ** This class implements a rights group for configuring userrights
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co KG All rights reserved
 *****************************************************************************/ 

// System and QT Includes


// Own Includes
#include "CwmsbtRightsGroup.h"

#include <QTreeWidgetItem>


/** +-=---------------------------------------------------------Mo 10. Mai 19:57:34 2010----------*
 * @method  CwmsbtRightsGroup::CwmsbtRightsGroup                   // public                            *
 * @return                                                   //                                   *
 * @param   int p_iId                                        //                                   *
 * @param   QString p_qstrName                               //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 10. Mai 19:57:34 2010----------*/
CwmsbtRightsGroup::CwmsbtRightsGroup(int p_iId, QString p_qstrName)
: m_iID(p_iId),
  m_qstrDisplayName(p_qstrName),
  m_eSlRight(eSlGuiRightNone)
{

}

/** +-=---------------------------------------------------------Sa 15. Mai 14:00:20 2010----------*
 * @method  CwmsbtRightsGroup::CwmsbtRightsGroup                   // protected                         *
 * @return                                                   //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 15. Mai 14:00:20 2010----------*/
CwmsbtRightsGroup::CwmsbtRightsGroup()
: m_iID(0),
  m_qstrDisplayName(""),
  m_eSlRight(eSlGuiRightNone)
{
}

/** +-=---------------------------------------------------------Sa 8. Mai 13:04:01 2010-----------*
 * @method  CwmsbtRightsGroup::~CwmsbtRightsGroup                  // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CwmsbtRightsGroup                                                *
 *----------------last changed: --------------------------------Sa 8. Mai 13:04:01 2010-----------*/
CwmsbtRightsGroup::~CwmsbtRightsGroup()
{
}

/** +-=---------------------------------------------------------Mo 10. Mai 19:58:03 2010----------*
 * @method  CwmsbtRightsGroup::GetId                            // public                            *
 * @return  int                                              //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 10. Mai 19:58:03 2010----------*/
int CwmsbtRightsGroup::GetId()
{
   return m_iID;
}

/** +-=---------------------------------------------------------Mo 10. Mai 19:58:20 2010----------*
 * @method  CwmsbtRightsGroup::GetDisplayName                   // public                            *
 * @return  QString                                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 10. Mai 19:58:20 2010----------*/
QString CwmsbtRightsGroup::GetDisplayName()
{
   return m_qstrDisplayName;
}

/** +-=---------------------------------------------------------Mo 10. Mai 20:14:23 2010----------*
 * @method  CwmsbtRightsGroup::GetWriteRightsElements           // public                            *
 * @return  QList<QObject*>                            //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 10. Mai 20:14:23 2010----------*/
QList<QObject*> CwmsbtRightsGroup::GetWriteRightsElements()
{
   return m_qllWriteObjects;
}

/** +-=---------------------------------------------------------Mo 10. Mai 20:14:40 2010----------*
 * @method  CwmsbtRightsGroup::GetReadRightsElements            // public                            *
 * @return  QList<QObject*>                            //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 10. Mai 20:14:40 2010----------*/
QList<QObject*> CwmsbtRightsGroup::GetReadRightsElements()
{
   return m_qllReadObjects;
}


/** +-=---------------------------------------------------------Sa 8. Mai 13:25:18 2010-----------*
 * @method  CwmsbtRightsGroup::AddWriteRightsElement            // public                            *
 * @return  void                                             //                                   *
 * @param   QObject* p_pqObject                              //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 8. Mai 13:25:18 2010-----------*/
void CwmsbtRightsGroup::AddWriteRightsElement(QObject* p_pqObject)
{
   if (p_pqObject->isWidgetType() || p_pqObject->inherits("QAction") || p_pqObject->inherits("QTreeWidgetItem"))
   {
      m_qllWriteObjects.append(p_pqObject);
   }
}


/** +-=---------------------------------------------------------Sa 8. Mai 13:26:18 2010-----------*
 * @method  CwmsbtRightsGroup::AddReadRightsElement             // public                            *
 * @return  void                                             //                                   *
 * @param   QObject* p_pqObject                              //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 8. Mai 13:26:18 2010-----------*/
void CwmsbtRightsGroup::AddReadRightsElement(QObject* p_pqObject)
{
   if (p_pqObject->isWidgetType() || p_pqObject->inherits("QAction") || p_pqObject->inherits("QTreeWidgetItem"))
   {
      m_qllReadObjects.append(p_pqObject);
   }
}

/** +-=---------------------------------------------------------Sa 15. Mai 13:49:07 2010----------*
 * @method  CwmsbtRightsGroup::SetAndActivateRight              // public                            *
 * @return  void                                             //                                   *
 * @param   EslGuiRight p_eSlRight                           //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 15. Mai 13:49:07 2010----------*/
void CwmsbtRightsGroup::SetAndActivateRight(EslGuiRight p_eSlRight)
{
   SetRight(p_eSlRight);
   ActivateRights();
}

/** +-=---------------------------------------------------------Sa 8. Mai 13:11:49 2010-----------*
 * @method  CwmsbtRightsGroup::SetRight                         // public                            *
 * @return  void                                             //                                   *
 * @param   EslGuiRight p_eSlRight                           //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 8. Mai 13:11:49 2010-----------*/
void CwmsbtRightsGroup::SetRight(EslGuiRight p_eSlRight)
{
   m_eSlRight = p_eSlRight;
}

/** +-=---------------------------------------------------------Do 13. Mai 12:57:08 2010----------*
 * @method  CwmsbtRightsGroup::ActivateRights                   // public                            *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 13. Mai 12:57:08 2010----------*/
void CwmsbtRightsGroup::ActivateRights()
{
   if (m_eSlRight == eSlGuiRightNone)
   {
      UpdateElementsNoRights();
   }
   else if (m_eSlRight == eSlGuiRightReadOnly)
   {
      UpdateElementsReadOnly();
   }
   else
   {
      UpdateElementsReadWite();
   }
}

/** +-=---------------------------------------------------------Sa 8. Mai 13:57:52 2010-----------*
 * @method  CwmsbtRightsGroup::GetRight                         // public                            *
 * @return  EslGuiRight                                      //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 8. Mai 13:57:52 2010-----------*/
EslGuiRight CwmsbtRightsGroup::GetRight()
{
   return m_eSlRight;
}

/** +-=---------------------------------------------------------Sa 8. Mai 13:16:27 2010-----------*
 * @method  CwmsbtRightsGroup::UpdateElementsNoRights           // private                           *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 8. Mai 13:16:27 2010-----------*/
void CwmsbtRightsGroup::UpdateElementsNoRights()
{
   ChangeVisibility(m_qllReadObjects,  false);
   ChangeVisibility(m_qllWriteObjects, false);
}

/** +-=---------------------------------------------------------Sa 8. Mai 13:16:39 2010-----------*
 * @method  CwmsbtRightsGroup::UpdateElementsReadOnly           // private                           *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 8. Mai 13:16:39 2010-----------*/
void CwmsbtRightsGroup::UpdateElementsReadOnly()
{
   ChangeVisibility(m_qllReadObjects,  true);
   ChangeVisibility(m_qllWriteObjects, false);
}

/** +-=---------------------------------------------------------Sa 8. Mai 13:16:57 2010-----------*
 * @method  CwmsbtRightsGroup::UpdateElementsReadWite           // private                           *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 8. Mai 13:16:57 2010-----------*/
void CwmsbtRightsGroup::UpdateElementsReadWite()
{
   ChangeVisibility(m_qllReadObjects,  true);
   ChangeVisibility(m_qllWriteObjects, true);
   
}

/** +-=---------------------------------------------------------Sa 8. Mai 13:27:48 2010-----------*
 * @method  CwmsbtRightsGroup::ChangeVisibility                 // private                           *
 * @return  void                                             //                                   *
 * @param   QList<QObject*>& p_rqllWidgets             //                                   *
 * @param   bool p_bVisibility                               //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 8. Mai 13:27:48 2010-----------*/
void CwmsbtRightsGroup::ChangeVisibility(QList<QObject*>& p_rqllWidgets, bool p_bVisibility)
{
   QList<QObject*>::iterator qllIt = p_rqllWidgets.begin();
   QList<QObject*>::iterator qllItEnd = p_rqllWidgets.end();

   for (; qllIt != qllItEnd; ++qllIt)
   {
      QObject* pqObject = *(qllIt);

      if (pqObject)
      {
         if (pqObject->isWidgetType())
         {
            dynamic_cast<QWidget*>(pqObject)->setVisible(p_bVisibility);
         }
         else if (pqObject->inherits("QAction"))
         {
             dynamic_cast<QAction*>(pqObject)->setVisible(p_bVisibility);
         }
         else if (pqObject->inherits("QTreeWidgetItem"))
         {
             dynamic_cast<QTreeWidgetItem*>(pqObject)->setHidden(!p_bVisibility);
         }
      }
   }
}

