// System and QT Includes
#include <CdmQueryBuilder.h>
#include <QList>
#include <QMap>

// WMS Includes
#include "basetools.h"
#include "CdmLogging.h"
#include "CdmClass.h"
#include "CdmMember.h"
#include "CdmObjectContainer.h"
#include "CdmObject.h"

// Own Includes
#include "CoeDataTypeWidget.h"
#include "CwmsSearchWidgetIf.h"


/** +-=---------------------------------------------------------Sa 6. Sep 09:19:05 2008-----------*
 * @method  CwmsSearchWidgetIf::CwmsSearchWidgetIf           // public                            *
 * @return                                                   //                                   *
 * @param   QWidget* p_pqwParent = nullptr                      //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 6. Sep 09:19:05 2008-----------*/
CwmsSearchWidgetIf::CwmsSearchWidgetIf(QWidget* p_pqwParent)
   : QWidget(p_pqwParent),
     m_rpClass(nullptr),
     m_rpContainer(nullptr),
     m_pqwContent(nullptr)

{
   setupUi(this);
}

/** +-=---------------------------------------------------------Sa 6. Sep 09:19:38 2008-----------*
 * @method  CwmsSearchWidgetIf::~CwmsSearchWidgetIf          // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CwmsSearchWidgetIf                                            *
 *----------------last changed: --------------------------------Sa 6. Sep 09:19:38 2008-----------*/
CwmsSearchWidgetIf::~CwmsSearchWidgetIf()
{
}

/** +-=---------------------------------------------------------Sa 21. Feb 11:13:28 2009----------*
 * @method  CwmsSearchWidgetIf::SetSearchCaption             // public                            *
 * @return  void                                             //                                   *
 * @param   QString p_qstrCaption                            //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 21. Feb 11:13:28 2009----------*/
void CwmsSearchWidgetIf::SetSearchCaption(QString p_qstrCaption)
{
   m_pqgbSearch->setTitle(p_qstrCaption);
}

CdmObjectContainer* CwmsSearchWidgetIf::GetObjectList()
{
   return m_rpContainer;
}

void CwmsSearchWidgetIf::SetObjectList(CdmObjectContainer* p_pContainer)
{
   Clear();

   if (p_pContainer)
   {
      m_rpContainer = p_pContainer;
      m_rpClass = const_cast<CdmClass*>(m_rpContainer->GetClass());
   }
}

CdmClass* CwmsSearchWidgetIf::GetClass()
{
   return m_rpClass;
}

void CwmsSearchWidgetIf::SetClass(CdmClass* p_pClass)
{
   Clear();

   if (p_pClass)
   {
      m_rpClass = p_pClass;
   }
}

/** +-=---------------------------------------------------------Mo 8. Sep 19:57:01 2008-----------*
 * @method  CwmsSearchWidgetIf::Clear                        // public                            *
 * @return  void                                             //                                   *
 * @comment This method clears the widget. After this call it can be created new.                 *
 *----------------last changed: --------------------------------Mo 8. Sep 19:57:01 2008-----------*/
void CwmsSearchWidgetIf::Clear()
{
   m_rpClass = nullptr;
   m_rpContainer = nullptr;
   m_cCdmQuery.Clear();
   m_qlValueWidgets.clear();
   m_qstrlSearchMembers.clear();
   m_qmSearchAliases.clear();
   DELPTR(m_pqwContent)
}

/** +-=---------------------------------------------------------Mi 10. Sep 19:22:04 2008----------*
 * @method  CwmsSearchWidgetIf::AddSearchMember              // public                            *
 * @return  void                                             //                                   *
 * @param   QString p_qstrKeyname                            //                                   *
 * @param   QString p_qstrAlias = ""                         //                                   *
 * @comment Adds a further search member to the search. this search members will be               *
 *          displayed in the gui and the user can enter searchcriterias to this members.          *
 *----------------last changed: --------------------------------Mi 10. Sep 19:22:04 2008----------*/
void CwmsSearchWidgetIf::AddSearchMember(QString p_qstrKeyname, QString p_qstrAlias)
{
   m_qstrlSearchMembers.append(p_qstrKeyname);

   if (p_qstrAlias.length() > 0)
   {
      m_qmSearchAliases.insert(p_qstrKeyname, p_qstrAlias);
   }
}

/** +-=---------------------------------------------------------Mi 19. Aug 18:29:44 2009----------*
 * @method  CwmsSearchWidgetIf::AddAllSearchMembers          // private                           *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 19. Aug 18:29:44 2009----------*/
void CwmsSearchWidgetIf::AddAllSearchMembers()
{
   if (m_rpClass)
   {
      QMap<qint64, CdmMember*> qmMembers;
      m_rpClass->GetMemberMap(qmMembers);

      QMap<qint64, CdmMember*>::iterator qmIt    = qmMembers.begin();
      QMap<qint64, CdmMember*>::iterator qmItEnd = qmMembers.end();

      for ( ; qmIt != qmItEnd; ++qmIt)
      {
         CdmMember* pCdmMember = qmIt.value();

         if (CHKPTR(pCdmMember))
         {
            if (IsMemberSearchable(pCdmMember))
            {
               m_qstrlSearchMembers.append(pCdmMember->GetKeyname());
            }
         }
      }
   }
}

/** +-=---------------------------------------------------------Mi 19. Aug 18:34:22 2009----------*
 * @method  CwmsSearchWidgetIf::IsMemberSearchable           // private                           *
 * @return  bool                                             //                                   *
 * @param   CdmMember* p_pCdmMember                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 19. Aug 18:34:22 2009----------*/
bool CwmsSearchWidgetIf::IsMemberSearchable(CdmMember* p_pCdmMember)
{
   bool bRet = true;

   if (CHKPTR(p_pCdmMember))
   {
      EdmValueType eDmValueType = p_pCdmMember->GetValueType();

      if (eDmValueType == eDmValueObjectRef        ||
          eDmValueType == eDmValueBinaryDocument   ||
          eDmValueType == eDmValueDictIntDouble    ||
          eDmValueType == eDmValueDictIntInt       ||
          eDmValueType == eDmValueDictIntString    ||
          eDmValueType == eDmValueDictStringDouble ||
          eDmValueType == eDmValueDictStringInt    ||
          eDmValueType == eDmValueDictStringString ||
          eDmValueType == eDmValueFormula          ||
          eDmValueType == eDmValueListDouble       ||
          eDmValueType == eDmValueListInt          ||
          eDmValueType == eDmValueListObjects      ||
          eDmValueType == eDmValueListString       ||
          eDmValueType == eDmValueContainerRef     ||
          eDmValueType == eDmValueObjectRef        ||
          eDmValueType == eDmValueObjectTree)
      {
         bRet = false;
      }
   }

   return bRet;
}

/** +-=---------------------------------------------------------Mi 10. Sep 19:22:55 2008----------*
 * @method  CwmsSearchWidgetIf::AddSearchDefaultValue        // public                            *
 * @return  void                                             //                                   *
 * @param   QString p_qstrKeyname                            //                                   *
 * @param   QString p_qstrDefaultValue                       //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 10. Sep 19:22:55 2008----------*/
void CwmsSearchWidgetIf::AddSearchDefaultValue(QString p_qstrKeyname, QString p_qstrDefaultValue)
{
   m_qmSearchDefaultValues.insert(p_qstrKeyname, p_qstrDefaultValue);
}

/** +-=---------------------------------------------------------Do 11. Sep 18:54:28 2008----------*
 * @method  CwmsSearchWidgetIf::SetSearchMemberAsHidden      // public                            *
 * @return  void                                             //                                   *
 * @param   QString p_qstrKeyname                            //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 11. Sep 18:54:28 2008----------*/
void CwmsSearchWidgetIf::SetSearchMemberAsHidden(QString p_qstrKeyname)
{
   m_qstrlHiddenSearchMembers.append(p_qstrKeyname);
}

/** +-=---------------------------------------------------------Sa 6. Sep 09:43:20 2008-----------*
 * @method  CwmsSearchWidgetIf::FillWidget                   // public                            *
 * @return  void                                             //                                   *
 * @comment Fills the widget for displaying the search widget                                     *
 *----------------last changed: --------------------------------Sa 6. Sep 09:43:20 2008-----------*/
void CwmsSearchWidgetIf::FillWidget()
{
   if (CHKPTR(m_rpClass))
   {
      DELPTR(m_pqwContent)
      m_pqwContent = new QWidget(this);
      QFormLayout* pqLayout = new QFormLayout(m_pqwContent);

      if (m_qstrlSearchMembers.count() == 0)
      {
         FillDefaultMembers();
      }

      for (int iCounter = 0; iCounter < m_qstrlSearchMembers.count(); ++iCounter)
      {
         QString qstrKeyname = m_qstrlSearchMembers.at(iCounter);
         const CdmMember* pCdmMember = m_rpClass->FindMember(qstrKeyname);

         if (CHKPTR(pCdmMember) &&
             !m_qstrlHiddenSearchMembers.contains(qstrKeyname) &&
             (pCdmMember->GetAccessMode() != eDmMemberAccessPrivate))
         {
            CoeValueWidget* pWidget = CoeValueWidget::CreateSearchValueWidget(pCdmMember, qstrKeyname, m_pqwContent);

            if (pWidget)
            {
               pWidget->CreateSearchWidget(pqLayout, m_pqwContent);

               if (m_qmSearchAliases.contains(qstrKeyname))
               {
                  pWidget->SetCaption(m_qmSearchAliases[qstrKeyname]);
               }

               if (m_qmSearchDefaultValues.contains(qstrKeyname))
               {
                  pWidget->SetSearchDeaultValue(m_qmSearchDefaultValues[qstrKeyname]);
               }

               m_qlValueWidgets.append(pWidget);
            }
         }
         else
         {
            ERR("Member " + qstrKeyname + " not found!")
         }
      }

      m_pqScrollArea->setWidget(m_pqwContent);
   }
}

/** +-=---------------------------------------------------------Sa 6. Sep 09:42:27 2008-----------*
 * @method  CwmsSearchWidgetIf::CreateQuery                  // private                           *
 * @return  void                                             //                                   *
 * @comment creates the query with the settings.                                                  *
 *----------------last changed: --------------------------------Sa 6. Sep 09:42:27 2008-----------*/
void CwmsSearchWidgetIf::CreateQuery()
{
   CreateQuery(m_cCdmQuery);
}

/** +-=---------------------------------------------------------Do 6. Sep 19:12:21 2012-----------*
 * @method  CwmsSearchWidgetIf::CreateQuery                  // public                            *
 * @return  void                                             //                                   *
 * @param   CdmQuery& p_rCdmQuery                            //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 6. Sep 19:12:21 2012-----------*/
void CwmsSearchWidgetIf::CreateQuery(CdmQuery& p_rCdmQuery)
{
    if (m_rpClass)
    {
        p_rCdmQuery.SetClass(m_rpClass);
        p_rCdmQuery.SetQueryCaseInsensitive(!m_pqchbCaseSensitive->isChecked());

        if (m_rpContainer != nullptr)
        {
            p_rCdmQuery.SetContainer(m_rpContainer);
        }

        EdmQueryElementType eDmQueryElementType = eDmQueryElementTypeAnd;

        if (m_pqrbLogicOr->isChecked())
        {
            eDmQueryElementType = eDmQueryElementTypeOr;
        }

        CdmQueryElement* pCdmQueryElement = new CdmQueryElement(&p_rCdmQuery, eDmQueryElementType);
        MAP(AddQueryElement(pCdmQueryElement), m_qlValueWidgets)
        p_rCdmQuery.ResetQueryElement(pCdmQueryElement);
    }
}

/** +-=---------------------------------------------------------Sa 6. Sep 09:44:34 2008-----------*
 * @method  CwmsSearchWidgetIf::SearchClickedSlot            // private, slots                    *
 * @return  void                                             //                                   *
 * @comment This slot will be called if the search button was clicked.                            *
 *----------------last changed: --------------------------------Sa 6. Sep 09:44:34 2008-----------*/
void CwmsSearchWidgetIf::SearchClickedSlot()
{
   emit SearchSignal();
}

/** +-=---------------------------------------------------------Di 9. Sep 08:18:25 2008-----------*
 * @method  CwmsSearchWidgetIf::GetDisplayList               // public                            *
 * @return  void                                             //                                   *
 * @param   QList<qint64>& p_rqvlResults                 // The list of objects or objectlists*
 *                                                           //  which can be used                *
 * @comment This is the abstract method which must be overwritten be the derived class. the       *
 *          gui components which uses proxies uses the list of results for displaying their       *
 *          contents.                                                                             *
 *----------------last changed: --------------------------------Di 9. Sep 08:18:25 2008-----------*/
void CwmsSearchWidgetIf::GetDisplayList(QList<qint64>& p_rqvlResults)
{
   m_cCdmQuery.Clear();
   CreateQuery();

   if (m_cCdmQuery.GetQueryElement())
   {
      if (m_cCdmQuery.Execute())
      {
         QList<qint64> qvlResult = m_cCdmQuery.GetResultList();

         QList<qint64>::const_iterator qvlIt    = qvlResult.begin();
         QList<qint64>::const_iterator qvlItEnd = qvlResult.end();

         for ( ; qvlIt != qvlItEnd; ++ qvlIt)
         {
            p_rqvlResults.append(*qvlIt);
         }
      }
      else
      {
         FATAL("Query does not work!!!!")
      }
   }
   else
   {
      if (m_rpContainer)
      {
         QList<CdmObject*> qvlObjects;
         m_rpContainer->GetObjectList(qvlObjects);

         QList<CdmObject*>::iterator qvlIt    = qvlObjects.begin();
         QList<CdmObject*>::iterator qvlItEnd = qvlObjects.end();

         for ( ; qvlIt != qvlItEnd; ++qvlIt)
         {
            CdmObject* pCdmObject = *qvlIt;

            if (CHKPTR(pCdmObject))
            {
               p_rqvlResults.append(pCdmObject->GetId());
            }
         }
      }
      else
      {
         QScopedPointer<CdmQuery> pQuery(CdmQueryBuilder::ExecuteQuery(QString("select from \"%1.class\"").arg(m_rpClass->GetKeyname())));

         if (CHKPTR(pQuery))
         {
            p_rqvlResults << pQuery->GetResultList();
         }
      }
   }

   m_cCdmQuery.Clear();
}

/** +-=---------------------------------------------------------Do 20. Aug 18:09:04 2009----------*
 * @method  CwmsSearchWidgetIf::SetSearchButtonVisibility    // public                            *
 * @return  void                                             //                                   *
 * @param   bool p_bVisiible                                 //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 20. Aug 18:09:04 2009----------*/
void CwmsSearchWidgetIf::SetSearchButtonVisibility(bool p_bVisiible)
{
   if (p_bVisiible)
   {
      m_pqpbSearch->show();
   }
   else
   {
      m_pqpbSearch->hide();
   }
}

/** +-=---------------------------------------------------------Mo 11. Feb 11:03:12 2013----------*
 * @method  CwmsSearchWidgetIf::FillDefaultMembers           // private                           *
 * @return  void                                             //                                   *
 * @param   const CdmClass* p_pCdmClass                      //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 11. Feb 11:03:12 2013----------*/
void CwmsSearchWidgetIf::FillDefaultMembers()
{
   if (CHKPTR(m_rpClass))
   {
      QMap<qint64,CdmMember*> qmMembers;
      m_rpClass->GetMemberMap(qmMembers);

      QMap<qint64, CdmMember*>::iterator qmIt    = qmMembers.begin();
      QMap<qint64, CdmMember*>::iterator qmItEnd = qmMembers.end();

      for ( ; qmIt != qmItEnd; ++qmIt)
      {
         CdmMember* pCdmMember = qmIt.value();

         if (CHKPTR(pCdmMember)                                      &&
             (pCdmMember->GetAccessMode() != eDmMemberAccessPrivate) &&
             IsMemberSearchable(pCdmMember))
         {
            m_qstrlSearchMembers.append(pCdmMember->GetKeyname());
         }
      }
   }
}

/** +-=---------------------------------------------------------Sa 6. Sep 09:45:06 2008-----------*
 * @method  CwmsSearchWidgetIf::SearchSignal                 // private, signals                  *
 * @return  void                                             //                                   *
 * @comment This signal will be emitted if the user presses the search button.                    *
 *----------------last changed: --------------------------------Sa 6. Sep 09:45:06 2008-----------*/
