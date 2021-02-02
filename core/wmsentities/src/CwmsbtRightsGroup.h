/******************************************************************************
 ** WOGRA technologies GmbH & Co KG Modul Information
 ** Modulename: CwmsbtRightsGroup.h
 ** Started Implementation: 2010/05/08
 ** Description:
 ** 
 ** This class implements a rights group for configuring userrights
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co KG All rights reserved
 *****************************************************************************/ 

#ifndef CSLRIGHTSGROUP_H
#define CSLRIGHTSGROUP_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes
#include <QLinkedList>
#include <QWidget>
#include <QAction>

// Own Includes
#include "basetools.h"

// Forwards


// Enumerations
enum EslGuiRight
{
    eSlGuiRightNone,
    eSlGuiRightReadOnly,
    eSlGuiRightReadWrite
};

/* 
 * This class implements a rights group for configuring userrights
 */
class BASETOOLS_API CwmsbtRightsGroup
{
   private:
      QLinkedList<QObject*> m_qllWriteObjects;
      QLinkedList<QObject*> m_qllReadObjects;
      int m_iID;
      QString m_qstrDisplayName;
      EslGuiRight m_eSlRight;


   public:
   /** +-=---------------------------------------------------------Mo 10. Mai 19:57:34 2010-------*
    * @method  CwmsbtRightsGroup::CwmsbtRightsGroup                // public                            *
    * @return                                                //                                   *
    * @param   int p_iId                                     //                                   *
    * @param   QString p_qstrName                            //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 10. Mai 19:57:34 2010----------*/
    CwmsbtRightsGroup( int p_iId, QString p_qstrName);

   public:
   /** +-=---------------------------------------------------------Sa 8. Mai 13:04:01 2010--------*
    * @method  CwmsbtRightsGroup::~CwmsbtRightsGroup               // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CwmsbtRightsGroup                                             *
    *----------------last changed: -----------------------------Sa 8. Mai 13:04:01 2010-----------*/
    virtual ~CwmsbtRightsGroup( );

   public:
   /** +-=---------------------------------------------------------Sa 8. Mai 13:25:18 2010--------*
    * @method  CwmsbtRightsGroup::AddWriteRightsElement         // public                            *
    * @return  void                                          //                                   *
    * @param   QObject* p_pqObject                           //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Sa 8. Mai 13:25:18 2010-----------*/
    void AddWriteRightsElement(QObject* p_pqObject);


   public:
   /** +-=---------------------------------------------------------Sa 8. Mai 13:11:49 2010--------*
    * @method  CwmsbtRightsGroup::SetRight                      // public                            *
    * @return  void                                          //                                   *
    * @param   EslGuiRight p_eSlRight                        //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Sa 8. Mai 13:11:49 2010-----------*/
    void SetRight(EslGuiRight p_eSlRight);


   public:
   /** +-=---------------------------------------------------------Sa 8. Mai 13:26:18 2010--------*
    * @method  CwmsbtRightsGroup::AddReadRightsElement          // public                            *
    * @return  void                                          //                                   *
    * @param   QObject* p_pqObject                           //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Sa 8. Mai 13:26:18 2010-----------*/
    void AddReadRightsElement(QObject* p_pqObject);

   private:
   /** +-=---------------------------------------------------------Sa 8. Mai 13:16:27 2010--------*
    * @method  CwmsbtRightsGroup::UpdateElementsNoRights        // private                           *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Sa 8. Mai 13:16:27 2010-----------*/
    void UpdateElementsNoRights();

   private:
   /** +-=---------------------------------------------------------Sa 8. Mai 13:16:39 2010--------*
    * @method  CwmsbtRightsGroup::UpdateElementsReadOnly        // private                           *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Sa 8. Mai 13:16:39 2010-----------*/
    void UpdateElementsReadOnly();

   private:
   /** +-=---------------------------------------------------------Sa 8. Mai 13:16:57 2010--------*
    * @method  CwmsbtRightsGroup::UpdateElementsReadWite        // private                           *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Sa 8. Mai 13:16:57 2010-----------*/
    void UpdateElementsReadWite();

   private:
   /** +-=---------------------------------------------------------Sa 8. Mai 13:27:48 2010--------*
    * @method  CwmsbtRightsGroup::ChangeVisibility              // private                           *
    * @return  void                                          //                                   *
    * @param   QLinkedList<QObject*>& p_rqllWidgets          //                                   *
    * @param   bool p_bVisibility                            //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Sa 8. Mai 13:27:48 2010-----------*/
    void ChangeVisibility(QLinkedList<QObject*>& p_rqllWidgets, bool p_bVisibility);



   public:
   /** +-=---------------------------------------------------------Sa 8. Mai 13:57:52 2010--------*
    * @method  CwmsbtRightsGroup::GetRight                      // public                            *
    * @return  EslGuiRight                                   //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Sa 8. Mai 13:57:52 2010-----------*/
    EslGuiRight GetRight();

   public:
   /** +-=---------------------------------------------------------Mo 10. Mai 19:58:03 2010-------*
    * @method  CwmsbtRightsGroup::GetId                         // public                            *
    * @return  int                                           //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 10. Mai 19:58:03 2010----------*/
    int GetId();

   public:
   /** +-=---------------------------------------------------------Mo 10. Mai 19:58:20 2010-------*
    * @method  CwmsbtRightsGroup::GetDisplayName                // public                            *
    * @return  QString                                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 10. Mai 19:58:20 2010----------*/
    QString GetDisplayName();

   public:
   /** +-=---------------------------------------------------------Mo 10. Mai 20:14:23 2010-------*
    * @method  CwmsbtRightsGroup::GetWriteRightsElements        // public                            *
    * @return  QLinkedList<QObject*>                         //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 10. Mai 20:14:23 2010----------*/
    QLinkedList<QObject*> GetWriteRightsElements();

   public:
   /** +-=---------------------------------------------------------Mo 10. Mai 20:14:40 2010-------*
    * @method  CwmsbtRightsGroup::GetReadRightsElements         // public                            *
    * @return  QLinkedList<QObject*>                         //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 10. Mai 20:14:40 2010----------*/
    QLinkedList<QObject*> GetReadRightsElements();

   public:
   /** +-=---------------------------------------------------------Do 13. Mai 12:57:08 2010-------*
    * @method  CwmsbtRightsGroup::ActivateRights                // public                            *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 13. Mai 12:57:08 2010----------*/
    void ActivateRights();

   public:
   /** +-=---------------------------------------------------------Sa 15. Mai 13:49:07 2010-------*
    * @method  CwmsbtRightsGroup::SetAndActivateRight           // public                            *
    * @return  void                                          //                                   *
    * @param   EslGuiRight p_eSlRight                        //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Sa 15. Mai 13:49:07 2010----------*/
    void SetAndActivateRight(EslGuiRight p_eSlRight);

   protected:
   /** +-=---------------------------------------------------------Sa 15. Mai 14:00:20 2010-------*
    * @method  CwmsbtRightsGroup::CwmsbtRightsGroup                // protected                         *
    * @return                                                //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Sa 15. Mai 14:00:20 2010----------*/
    CwmsbtRightsGroup( );
};

#endif //
