/******************************************************************************
 ** WOGRA technologies GmbH & Co. KG Modul Information
 ** Modulename: CwmsObjectObjectListEditorWidget.cpp
 ** Started Implementation: 2012/09/17
 ** Description:
 **
 ** implements the editor for object objectlists
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co. KG All rights reserved
 *****************************************************************************/

// System and QT Includes
#include <QList>


// WMS Includes
#include "CdmQueryEnhanced.h"
#include "CdmQueryBuilder.h"
#include "CdmLogging.h"
#include "CdmValue.h"
#include "CdmValueContainerRef.h"
#include "CdmObject.h"
#include "CdmMessageManager.h"

// own Includes
#include "CwmsFormObjectObjectListEditor.h"
#include "CwmsRuntime.h"
#include "CwmsObjectObjectListEditorWidget.h"
#include "CwmsTreeWidgetHelper.h"

/** +-=---------------------------------------------------------Mo 17. Sep 10:31:18 2012----------*
 * @method  CwmsObjectObjectListEditorWidget::CwmsObjectObjectListEditorWidget // public          *
 * @return                                                   //                                   *
 * @param   QWidget* p_pqwParent                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 17. Sep 10:31:18 2012----------*/
CwmsObjectContainerEditorWidget::CwmsObjectContainerEditorWidget(QWidget* p_pqwParent)
: QWidget(p_pqwParent)
{
    setupUi(this);
}

/** +-=---------------------------------------------------------Mo 17. Sep 10:31:51 2012----------*
 * @method  CwmsObjectObjectListEditorWidget::~CwmsObjectObjectListEditorWidget // public, virtual*
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CwmsObjectObjectListEditorWidget                              *
 *----------------last changed: --------------------------------Mo 17. Sep 10:31:51 2012----------*/
CwmsObjectContainerEditorWidget::~CwmsObjectContainerEditorWidget()
{
}

/** +-=---------------------------------------------------------Mo 17. Sep 10:32:19 2012----------*
 * @method  CwmsObjectObjectListEditorWidget::FillDialog     // private                           *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 17. Sep 10:32:19 2012----------*/
void CwmsObjectContainerEditorWidget::FillDialog()
{
    BODY_TRY
    m_cModel.Execute(m_pCdmQuery);
    m_pqtvSelection->setModel(&m_cModel);
    m_pqtvSelection->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_pqtvSelection->setSelectionMode(QAbstractItemView::SingleSelection);
    // Select first item
    m_pqtvSelection->selectionModel()->select(m_cModel.index(0,0), QItemSelectionModel::Select | QItemSelectionModel::Rows);
    // Fill Editor with selected data

    m_pqtvSelection->header()->setStretchLastSection(false);
    CwmsTreeWidgetHelper::ResizeColumnsToContent(m_pqtvSelection);

    if (m_cModel.rowCount() > 0 && m_cModel.columnCount() > 0)
    {
        m_pqtvSelection->setCurrentIndex(m_cModel.index(0,0));
        TreeViewSelectionChangedSlot();
    }
   BODY_CATCH
}

/** +-=---------------------------------------------------------Mo 17. Sep 11:20:20 2012----------*
 * @method  CwmsObjectObjectListEditorWidget::TreeViewSelectionChangedSlot // private, slots      *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 17. Sep 11:20:20 2012----------*/
void CwmsObjectContainerEditorWidget::TreeViewSelectionChangedSlot()
{
   CdmObject* pCdmObject = m_cModel.GetObject(m_pqtvSelection->currentIndex());

   if ((pCdmObject))
   {
      if (!m_qstrEditorWql.isEmpty())
      {
         CdmQueryBuilder cBuilder(m_qstrEditorWql);
		 cBuilder.AddValueEntry("${Value}", pCdmObject->GetDisplayString(m_qstrKeyname));
         QString qstrWql = cBuilder.GetFinalWql();
         m_pCwmsEditor->SetQuery(qstrWql);
      }
      else
      {
         CdmValue* pCdmValue = pCdmObject->GetValue(m_qstrKeyname);

         if (CHKPTR(pCdmValue) && pCdmValue->GetValueType() == eDmValueContainerRef)
         {
            CdmObjectContainer* pContainer = ((CdmValueContainerRef*)pCdmValue)->GetContainer();

            if (pContainer)
            {
               m_pCwmsEditor->SetContainer(pContainer);
            }
         }
      }
   }
}

/** +-=---------------------------------------------------------Mo 17. Sep 11:04:16 2012----------*
 * @method  CwmsObjectObjectListEditorWidget::SetView        // public                            *
 * @return  void                                             //                                   *
 * @param   CwmsView p_cCwmsView                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 17. Sep 11:04:16 2012----------*/
void CwmsObjectContainerEditorWidget::SetView(CwmsView p_cCwmsView)
{
   if (p_cCwmsView.IsValid())
   {
      m_pCdmQuery = (CdmQueryEnhanced*)CdmQueryBuilder::BuildQuery(p_cCwmsView.GetViewCommand());
   }
}



/** +-=---------------------------------------------------------Mo 17. Sep 10:37:50 2012----------*
 * @method  CwmsObjectObjectListEditorWidget::SetModule      // private                           *
 * @return  void                                             //                                   *
 * @param   CwmsApplicationModule p_cModule                  //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 17. Sep 10:37:50 2012----------*/
void CwmsObjectContainerEditorWidget::SetModule(CwmsApplicationModule p_cModule)
{
   if (p_cModule.IsValid())
   {
      CdmObject* pCdmObject = p_cModule.GetUserInterface();

      if (CHKPTR(pCdmObject))
      {
         CwmsFormObjectContainer cForm(pCdmObject);
         m_qstrKeyname = cForm.GetEditorKeyname();
         m_qstrEditorWql = cForm.GetEditorWql();
         //bool bSelectionReadOnly = cForm.GetSelectionListReadOnly(); // currently not used
         CdmObject* pCdmObjectView = cForm.GetSelectionView();

         if (pCdmObjectView)
         {
            SetView(CwmsView(pCdmObjectView));
         }
         else
         {
            QList<QString> qllDisplayMembers = cForm.GetSelectionDisplayMembers();
            CdmObjectContainer* pContainer = cForm.GetSelectionObjectList();

            if (pContainer)
            {
               m_pCdmQuery = new CdmQueryEnhanced();
               m_pCdmQuery->SetContainer(pContainer);

               QList<QString>::iterator qllIt = qllDisplayMembers.begin();
               QList<QString>::iterator qllItEnd = qllDisplayMembers.end();

               for (; qllIt != qllItEnd; ++qllIt)
               {
                  m_pCdmQuery->AddResultElement(*qllIt);
               }
            }
            else
            {
               MSG_CRIT("Ungültige Konfiguration",
                        "Die Konfiguration der UI Komponente ist ungültig.\n"
                        "Wenden Sie sich an Ihren Hersteller.\n"
                        "Weitere Informationen: Kein View oder keine Objektliste mit Darstellungsfeldern definiert.");
            }
         }
      }
   }
}

/** +-=---------------------------------------------------------Mo 17. Sep 10:36:05 2012----------*
 * @method  CwmsObjectObjectListEditorWidget::Initialize     // public                            *
 * @return  void                                             //                                   *
 * @param   CwmsApplicationModule p_cModule                  //                                   *
 * @param   CwmsRuntime* p_pRuntime                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 17. Sep 10:36:05 2012----------*/
void CwmsObjectContainerEditorWidget::Initialize(CwmsApplicationModule p_cModule,
                                                  CwmsRuntime* p_pRuntime)
{
   m_pCwmsEditor->Initialize(p_cModule, p_pRuntime);
   SetModule(p_cModule);
   FillDialog();
}
