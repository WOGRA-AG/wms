/******************************************************************************
 ** WOGRA technologies Modul Information
 ** Modulename: CwmsObjectListEditorBase.h
 ** Started Implementation: 2008/08/19
 ** Description:
 ** 
 ** Implements the interfaceclass for objectlisteditorwidget and objectlisteditor
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies All rights reserved
 *****************************************************************************/ 

#ifndef CWMSOBJECTLISTEDITORBASE_H
#define CWMSOBJECTLISTEDITORBASE_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes
#include <QString>
#include <QPair>
#include <QStringList>

// Own Includes
#include "wmsgui.h"


// forwards
class CdmObjectContainer;
class CwmsguiValidator;
class CdmObject;
class QTreeView;
class CwmsguiObjectEditorIf;
class CdmQueryModel;

typedef QPair<QString,QString> TStringPair;

// Enumerations

/* 
 * This class implements the interfaceclass for 
 * objectlisteditorwidget and objectlisteditor
 */
class WMSGUI_API CwmsContainerEditorBase
{
private:
   QStringList m_qstrlReadOnlyValues;
   QStringList m_qstrlHiddenValues;
   QStringList m_qstrlSortedList;
   bool m_bShowEditButton;
   QString m_qstrCaptionValue;
   QMap<QString, TStringPair> m_qmObjectRefData;

   public:
   /** +-=---------------------------------------------------------So 14. Mrz 12:15:37 2010-------*
    * @method  CwmsObjectListEditorBase::AddColumn           // public, p virtual                 *
    * @return  void                                          //                                   *
    * @param   QString p_qstrColumn                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 14. Mrz 12:15:37 2010----------*/
    virtual void AddColumn(QString p_qstrColumn)= 0;

   public:
   /** +-=---------------------------------------------------------So 14. Mrz 12:15:14 2010-------*
    * @method  CwmsObjectListEditorBase::AddReadOnlyValue    // public, virtual                   *
    * @return  void                                          //                                   *
    * @param   QString p_qstrValue                           //                                   *
    * @comment This method adds readonly values.                                                  *
    *----------------last changed: -----------------------------So 14. Mrz 12:15:14 2010----------*/
    virtual void AddReadOnlyValue(QString p_qstrValue);

   public:
   /** +-=---------------------------------------------------------Di 19. Aug 21:50:35 2008-------*
    * @method  CwmsObjectListEditorBase::SetObjectList       // public, p virtual                 *
    * @return  void                                          //                                   *
    * @param   CdmObjectContainer* p_pContainer               //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 19. Aug 21:50:35 2008----------*/
    virtual void SetContainer(CdmObjectContainer* p_pContainer)= 0;


   public:
   /** +-=---------------------------------------------------------Di 25. Sep 15:08:27 2012-------*
    * @method  CwmsObjectListEditorIf::SetModel              // public, p virtual                 *
    * @return  void                                          //                                   *
    * @param   CdmQueryModel* p_pModel                     //                                   *
    * @comment This method sets the proxy for this gui component.                                 *
    *----------------last changed: -----------------------------Di 25. Sep 15:08:27 2012----------*/
    virtual void SetModel(CdmQueryModel* p_pModel) = 0;

   public:
   /** +-=---------------------------------------------------------So 14. Mrz 12:16:02 2010-------*
    * @method  CwmsObjectListEditorBase::SetShowEditButton   // public, virtual                   *
    * @return  void                                          //                                   *
    * @param   bool p_bShowEditButton                        //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 14. Mrz 12:16:02 2010----------*/
    virtual void SetShowEditButton(bool p_bShowEditButton);

   public:
   /** +-=---------------------------------------------------------So 14. Mrz 12:16:15 2010-------*
    * @method  CwmsObjectListEditorBase::AddHiddenValue      // public, virtual                   *
    * @return  void                                          //                                   *
    * @param   QString p_qstrValue                           //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 14. Mrz 12:16:15 2010----------*/
    virtual void AddHiddenValue(QString p_qstrValue);

   public:
   /** +-=---------------------------------------------------------So 14. Mrz 12:18:57 2010-------*
    * @method  CwmsObjectListEditorBase::SetCaptionValue     // public, virtual                   *
    * @return  void                                          //                                   *
    * @param   QString p_qstrValue                           //                                   *
    * @comment Over this method you can set, from which value the objectcaption will be           *
    *          autmatically copied.                                                               *
    *----------------last changed: -----------------------------So 14. Mrz 12:18:57 2010----------*/
    virtual void SetCaptionValue(QString p_qstrValue);

   public:
   /** +-=---------------------------------------------------------Di 19. Aug 21:56:24 2008-------*
    * @method  CwmsObjectListEditorBase::FillDialog          // public, p virtual                 *
    * @return  void                                          //                                   *
    * @comment This method fills the dialog after all settings were done.                         *
    *----------------last changed: -----------------------------Di 19. Aug 21:56:24 2008----------*/
    virtual void FillDialog()= 0;


   public:
   /** +-=---------------------------------------------------------So 14. Mrz 12:22:17 2010-------*
    * @method  CwmsObjectListEditorBase::SetSortedList       // public, virtual                   *
    * @return  void                                          //                                   *
    * @param   QStringList p_qstrlSorting                    //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 14. Mrz 12:22:17 2010----------*/
    virtual void SetSortedList(QStringList p_qstrlSorting);

   public:
   /** +-=---------------------------------------------------------Di 19. Aug 22:00:44 2008-------*
    * @method  CwmsObjectListEditorBase::SetDefaultValueForNewObject // public, p virtual         *
    * @return  void                                          //                                   *
    * @param   QString p_qstrValueName                       //                                   *
    * @param   QString p_qstrValue                           //                                   *
    * @param   QString p_qstrValue2                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 19. Aug 22:00:44 2008----------*/
    virtual void SetDefaultValueForNewObject(QString p_qstrValueName,
                                             QString p_qstrValue,
                                             QString p_qstrValue2)= 0;


   public:
   /** +-=---------------------------------------------------------So 14. Mrz 12:17:01 2010-------*
    * @method  CwmsObjectListEditorBase::CwmsObjectListEditorBase // public                       *
    * @return                                                //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 14. Mrz 12:17:01 2010----------*/
    CwmsContainerEditorBase( );

   protected:
   /** +-=---------------------------------------------------------Di 16. Mrz 08:24:47 2010-------*
    * @method  CwmsObjectListEditorBase::OpenEditor          // protected                         *
    * @return  bool                                          //                                   *
    * @param   CdmObject* p_pCdmObject                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 16. Mrz 08:24:47 2010----------*/
    bool OpenEditor(CdmObject* p_pCdmObject);

   private:
   /** +-=---------------------------------------------------------So 14. Mrz 13:55:35 2010-------*
    * @method  CwmsObjectListEditorBase::FillReadOnlyMembers // private                           *
    * @return  void                                          //                                   *
    * @param   CwmsguiObjectEditorIf* p_pCoeEditor           //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 14. Mrz 13:55:35 2010----------*/
    void FillReadOnlyMembers(CwmsguiObjectEditorIf* p_pCoeEditor);

   private:
   /** +-=---------------------------------------------------------So 14. Mrz 13:55:51 2010-------*
    * @method  CwmsObjectListEditorBase::FillHiddenMembers   // private                           *
    * @return  void                                          //                                   *
    * @param   CwmsguiObjectEditorIf* p_pCoeEditor           //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 14. Mrz 13:55:51 2010----------*/
    void FillHiddenMembers(CwmsguiObjectEditorIf* p_pCoeEditor);

   public:
   /** +-=---------------------------------------------------------So 14. Mrz 14:37:08 2010-------*
    * @method  CwmsObjectListEditorBase::AddObjectRefData    // public, virtual                   *
    * @return  void                                          //                                   *
    * @param   QString p_qstrMember                          //                                   *
    * @param   QString p_qstrRef                             //                                   *
    * @param   QString p_qstrDisplayCaption                  //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 14. Mrz 14:37:08 2010----------*/
    virtual void AddObjectRefData(QString p_qstrMember,
                                  QString p_qstrRef,
                                  QString p_qstrDisplayCaption);

   private:
   /** +-=---------------------------------------------------------So 14. Mrz 14:32:47 2010-------*
    * @method  CwmsObjectListEditorBase::FillObjectRefData   // private                           *
    * @return  void                                          //                                   *
    * @param   CwmsguiObjectEditorIf* p_pCoeEditor           //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 14. Mrz 14:32:47 2010----------*/
    void FillObjectRefData(CwmsguiObjectEditorIf* p_pCoeEditor);
};

#endif //
