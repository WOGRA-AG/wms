/******************************************************************************
 ** WOGRA technologies Gmbh & Co KG Modul Information
 ** Modulename: CwmsMemberSequenceEditor.h
 ** Started Implementation: 2012/08/22
 ** Description:
 ** 
 ** implements the editor for the member sequence
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co KG All rights reserved
 *****************************************************************************/ 

#ifndef CWMSMEMBERSEQUENCEEDITOR_H
#define CWMSMEMBERSEQUENCEEDITOR_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes
#include <QVector>

// Own Includes
#include "ui_CwmsMemberSequenceEditor.h"

// Forwards
class CdmClass;
class CdmMember;
class CdmClassGroup;
class QTreeWidgetItem;

// TypeDefs


/* 
 * This class implements the editor for the member sequence
 */
class CwmsMemberSequenceEditor : public QDialog, public Ui::CwmsMemberSequenceEditorClass
{
   Q_OBJECT

   private:
      CdmClass* m_rpCdmClass;
      QList<int> m_qlAddedMembers;
      QMap<CdmClassGroup*, QTreeWidgetItem*> m_qmGroups;


   public:
   /** +-=---------------------------------------------------------Mi 22. Aug 17:48:07 2012-------*
    * @method  CwmsMemberSequenceEditor::CwmsMemberSequenceEditor // public                       *
    * @return                                                //                                   *
    * @param   QWidget* p_pqwParent                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 22. Aug 17:48:07 2012----------*/
    CwmsMemberSequenceEditor( QWidget* p_pqwParent);

   public:
   /** +-=---------------------------------------------------------Mi 22. Aug 17:48:31 2012-------*
    * @method  CwmsMemberSequenceEditor::~CwmsMemberSequenceEditor // public, virtual             *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CwmsMemberSequenceEditor                                   *
    *----------------last changed: -----------------------------Mi 22. Aug 17:48:31 2012----------*/
    virtual ~CwmsMemberSequenceEditor( );

   public:
   /** +-=---------------------------------------------------------Mi 22. Aug 17:48:49 2012-------*
    * @method  CwmsMemberSequenceEditor::FillDialog          // public                            *
    * @return  void                                          //                                   *
    * @param   CdmClass* p_pCdmClass                         //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 22. Aug 17:48:49 2012----------*/
    void FillDialog(CdmClass* p_pCdmClass);

    private slots:
   /** +-=---------------------------------------------------------Mi 22. Aug 17:49:13 2012-------*
    * @method  CwmsMemberSequenceEditor::UpClickedSlot       // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 22. Aug 17:49:13 2012----------*/
void UpClickedSlot( );

    private slots:
   /** +-=---------------------------------------------------------Mi 22. Aug 17:49:25 2012-------*
    * @method  CwmsMemberSequenceEditor::DownClickedSlot     // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 22. Aug 17:49:25 2012----------*/
void DownClickedSlot( );

    private slots:
   /** +-=---------------------------------------------------------Mi 22. Aug 17:49:36 2012-------*
    * @method  CwmsMemberSequenceEditor::OKClickedSlot       // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 22. Aug 17:49:36 2012----------*/
void OKClickedSlot( );

   private:
   /** +-=---------------------------------------------------------Mi 22. Aug 17:58:41 2012-------*
    * @method  CwmsMemberSequenceEditor::FillGroupsAndMembers // private                          *
    * @return  void                                          //                                   *
    * @param   QVector<QString>& p_rqvHash                   //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 22. Aug 17:58:41 2012----------*/
    void FillGroupsAndMembers(QVector<QString>& p_rqvHash);

   private:
   /** +-=---------------------------------------------------------Mi 22. Aug 17:51:52 2012-------*
    * @method  CwmsMemberSequenceEditor::FillGroupsAndMembers // private                          *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 22. Aug 17:51:52 2012----------*/
    void FillGroupsAndMembers();

   private:
   /** +-=---------------------------------------------------------Mi 22. Aug 17:58:54 2012-------*
    * @method  CwmsMemberSequenceEditor::FillGroups          // private                           *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 22. Aug 17:58:54 2012----------*/
    void FillGroups();

   private:
   /** +-=---------------------------------------------------------Mi 22. Aug 18:13:31 2012-------*
    * @method  CwmsMemberSequenceEditor::FillMembers         // private                           *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 22. Aug 18:13:31 2012----------*/
    void FillMembers();

   private:
   /** +-=---------------------------------------------------------Mi 22. Aug 18:13:56 2012-------*
    * @method  CwmsMemberSequenceEditor::FillMembers         // private                           *
    * @return  void                                          //                                   *
    * @param   QVector<QString>& p_rqvHash                   //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 22. Aug 18:13:56 2012----------*/
    void FillMembers(QVector<QString>& p_rqvHash);

   private:
   /** +-=---------------------------------------------------------Mo 11. Feb 11:06:50 2013-------*
    * @method  CwmsMemberSequenceEditor::AddMemberToGroup    // private                           *
    * @return  void                                          //                                   *
    * @param   const CdmMember* p_pCdmMember                 //                                   *
    * @param   const CdmClassGroup* p_pCdmGroup              //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 11. Feb 11:06:50 2013----------*/
    void AddMemberToGroup(const CdmMember* p_pCdmMember, const CdmClassGroup* p_pCdmGroup);

   private:
   /** +-=---------------------------------------------------------Mo 11. Feb 11:10:50 2013-------*
    * @method  CwmsMemberSequenceEditor::AddMember           // private                           *
    * @return  void                                          //                                   *
    * @param   const CdmMember* p_pCdmMember                 //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 11. Feb 11:10:50 2013----------*/
    void AddMember(const CdmMember* p_pCdmMember);

   public:
   /** +-=---------------------------------------------------------Do 23. Aug 10:48:36 2012-------*
    * @method  CwmsMemberSequenceEditor::GetSelectedItem     // public                            *
    * @return  QTreeWidgetItem*                              //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 23. Aug 10:48:36 2012----------*/
    QTreeWidgetItem* GetSelectedItem();

   public:
   /** +-=---------------------------------------------------------Mo 11. Feb 11:07:15 2013-------*
    * @method  CwmsMemberSequenceEditor::SetMemberToTreeViewItem // public                        *
    * @return  void                                          //                                   *
    * @param   const CdmMember* p_pCdmMember                 //                                   *
    * @param   QTreeWidgetItem* p_pqItem                     //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 11. Feb 11:07:15 2013----------*/
    void SetMemberToTreeViewItem(const CdmMember* p_pCdmMember, QTreeWidgetItem* p_pqItem);

   public:
   /** +-=---------------------------------------------------------Do 23. Aug 11:10:32 2012-------*
    * @method  CwmsMemberSequenceEditor::GetSequence         // public                            *
    * @return  QVector<QString>                              //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 23. Aug 11:10:32 2012----------*/
    QVector<QString> GetSequence();

   private:
   /** +-=---------------------------------------------------------Di 6. Nov 16:11:14 2012--------*
    * @method  CwmsMemberSequenceEditor::FillMembersNotInHash // private                          *
    * @return  void                                          //                                   *
    * @param   QVector<QString>& p_rqvHash                   //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 6. Nov 16:11:14 2012-----------*/
    void FillMembersNotInHash(QVector<QString>& p_rqvHash);
};

#endif // CWMSMEMBERSEQUENCEEDITOR_H
