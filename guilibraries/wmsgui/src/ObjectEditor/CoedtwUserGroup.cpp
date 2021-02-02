/******************************************************************************
 ** WOGRA Middleware Server Data Manager Module
 **
 ** @Author Wolfgang Graßhof 
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies All rights reserved
 ******************************************************************************/


// System and QT Includes
#include <QComboBox>
#include <QLineEdit>

// own Includes
#include "CdmDataProvider.h"
#include "CdmSessionManager.h"
#include "CumUserGroup.h"
#include "CumUserManager.h"
#include "CdmLogging.h"
#include "CdmValueUserGroup.h"
#include "CoedtwUserGroup.h"
#include "CwmsUserGroupChoiceIf.h"


/** +-=---------------------------------------------------------Di 28. Aug 15:33:23 2012----------*
 * @method  CoedtwUserGroup::CoedtwUserGroup                 // public, virtual                   *
 * @return                                                   //                                   *
 * @param   CdmValue* p_pCdmValue                            //                                   *
 * @param   QWidget* p_pqwParent = nullptr                      //                                   *
 * @comment The Constructor for valueediting.                                                     *
 *----------------last changed: --------------------------------Di 28. Aug 15:33:23 2012----------*/
CoedtwUserGroup::CoedtwUserGroup(CdmValue* p_pCdmValue, QWidget* p_pqwParent)
   : CoeValueWidget(p_pCdmValue, p_pqwParent),
     m_lCurrentGroupId(0)
{
    m_pqbButton = nullptr;
    m_qleGroup = nullptr;
}

CoedtwUserGroup::CoedtwUserGroup(const CdmObject *pEventObject, CdmValue* p_pCdmValue, QWidget* p_pqwParent)
    : CoeValueWidget(pEventObject, p_pCdmValue, p_pqwParent),
      m_lCurrentGroupId(0)
 {
     m_pqbButton = nullptr;
     m_qleGroup = nullptr;
 }

/** +-=---------------------------------------------------------Di 28. Aug 15:33:31 2012----------*
 * @method  CoedtwUserGroup::CoedtwUserGroup                 // public, virtual                   *
 * @return                                                   //                                   *
 * @param   CdmMember* p_pCdmMember                          //                                   *
 * @param   QString p_qstrKeyname                            //                                   *
 * @param   QWidget* p_pqwParent = nullptr                      //                                   *
 * @comment The Constuctor for searching.                                                         *
 *----------------last changed: --------------------------------Di 28. Aug 15:33:31 2012----------*/
CoedtwUserGroup::CoedtwUserGroup(CdmMember* p_pCdmMember,
                                 QString p_qstrKeyname,
                                 QWidget* p_pqwParent)
   : CoeValueWidget(p_pCdmMember, p_qstrKeyname, p_pqwParent) ,
     m_lCurrentGroupId(0)
{
   m_pqbButton = nullptr;
   m_qleGroup = nullptr;

}

/** +-=---------------------------------------------------------Di 28. Aug 15:33:41 2012----------*
 * @method  CoedtwUserGroup::~CoedtwUserGroup                // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CoedtwBinaryDocument                                          *
 *----------------last changed: --------------------------------Di 28. Aug 15:33:41 2012----------*/
CoedtwUserGroup::~CoedtwUserGroup()
{
   // nothing to do
}

/** +-=---------------------------------------------------------Di 28. Aug 15:33:48 2012----------*
 * @method  CoedtwUserGroup::GetEditWidget                   // public                            *
 * @return  QWidget*                                         //                                   *
 * @param   QWidget* p_pqwParent                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 28. Aug 15:33:48 2012----------*/
QWidget* CoedtwUserGroup::GetEditWidget(QWidget* p_pqwParent)
{
   QWidget* pqWidget = new QWidget(p_pqwParent);
   QHBoxLayout* pqLayout = new QHBoxLayout(pqWidget);
   m_qleGroup = new QLineEdit(pqWidget);
   m_qleGroup->setReadOnly(true);
   pqLayout->addWidget(m_qleGroup);
   m_pqbButton = new QPushButton("Auswählen", pqWidget);
   pqLayout->addWidget(m_pqbButton);
   connect(m_pqbButton, SIGNAL(clicked(bool)), this, SLOT(openNewWindow()));
   return pqWidget;
}

/** +-=---------------------------------------------------------Di 28. Aug 15:33:57 2012----------*
 * @method  CoedtwUserGroup::SetValue                        // protected, virtual                *
 * @return  void                                             //                                   *
 * @param   CdmValue* p_pCdmValue                            //                                   *
 * @comment This method sets the value in the widget.                                             *
 *----------------last changed: --------------------------------Di 28. Aug 15:33:57 2012----------*/
void CoedtwUserGroup::SetValue(CdmValue* p_pCdmValue)
{
   if (m_qleGroup && p_pCdmValue)
   {
      CumUserGroup* pCumGroup = ((CdmValueUserGroup*)p_pCdmValue)->GetUserGroup();

      if(pCumGroup)
      {
          m_qleGroup->setText(pCumGroup->GetGroupName());
          m_lCurrentGroupId = pCumGroup->GetId();
      }
      else
      {
          m_qleGroup->setText("");
      }
   }
}

void CoedtwUserGroup::setEventClassValue()
{
    if(CHKPTR(m_rpCdmValue) && m_qleGroup)
    {
        CumUserGroup* pCumGroup = ((CdmValueUserGroup*)m_rpCdmValue)->GetUserGroup();

        if(pCumGroup)
        {
            m_qleGroup->setText(pCumGroup->GetGroupName());
            m_lCurrentGroupId = pCumGroup->GetId();
        }
        else
        {
            m_qleGroup->setText("");
        }

        if(!m_qlEventClassValues.contains(m_rpCdmValue))
        {
            m_qlEventClassValues.append(m_rpCdmValue);
        }
    }
}

/** +-=---------------------------------------------------------Di 28. Aug 15:34:14 2012----------*
 * @method  CoedtwUserGroup::ValueChangedSlot                // private, slots                    *
 * @return  void                                             //                                   *
 * @comment This slot will be called if the value has changed.                                    *
 *----------------last changed: --------------------------------Di 28. Aug 15:34:14 2012----------*/
void CoedtwUserGroup::ValueChangedSlotByUser()
{
}

/** +-=---------------------------------------------------------Di 28. Aug 15:34:24 2012----------*
 * @method  CoedtwUserGroup::SetReadOnly                     // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment This method sets the current Value widget in ReadOnlymode.                            *
 *----------------last changed: --------------------------------Di 28. Aug 15:34:24 2012----------*/
void CoedtwUserGroup::SetReadOnly()
{
   m_pqbButton->hide();
}

void CoedtwUserGroup::SetEditable()
{
    m_pqbButton->show();
}

/** +-=---------------------------------------------------------Di 28. Aug 15:34:34 2012----------*
 * @method  CoedtwUserGroup::GetSearchWidget                 // public, virtual                   *
 * @return  QWidget*                                         //                                   *
 * @param   QWidget* p_pqwParent                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 28. Aug 15:34:34 2012----------*/
QWidget* CoedtwUserGroup::GetSearchWidget(QWidget* p_pqwParent)
{
   return GetEditWidget(p_pqwParent);
}

/** +-=---------------------------------------------------------Di 28. Aug 15:34:41 2012----------*
 * @method  CoedtwUserGroup::AddQueryElement                 // public, virtual                   *
 * @return  void                                             //                                   *
 * @param   CdmQueryElement* p_pCdmQueryElementParent        //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 28. Aug 15:34:41 2012----------*/
void CoedtwUserGroup::AddQueryElement(CdmQueryElement* p_pCdmQueryElementParent)
{
   if (CHKPTR(p_pCdmQueryElementParent) && m_lCurrentGroupId > 0)
   {
      EdmQueryCompareType eDmQueryCompareType = eDmQueryCompareTypeEqual;

      CdmQueryElement* pCdmQueryElement = new CdmQueryElement(p_pCdmQueryElementParent->GetQuery(),
                                                              eDmQueryElementTypeCompare,
                                                              eDmQueryCompareType);

      pCdmQueryElement->SetComparisonValue(m_qstrKeyname, m_lCurrentGroupId);
      p_pCdmQueryElementParent->AddChild(pCdmQueryElement);
   }
}

void CoedtwUserGroup::openNewWindow()
{
    m_lCurrentGroupId = CwmsUserGroupChoiceIf::GetGroupSelection(nullptr);

    if(m_lCurrentGroupId > 0)
    {
        CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

        if(CHKPTR(pCdmManager))
        {
            CumUserManager* pCumUserManager = pCdmManager->GetUserManager();

            if(CHKPTR(pCumUserManager))
            {
                CumUserGroup* pCumGroup = pCumUserManager->FindUserGroupById(m_lCurrentGroupId);

                if(pCumGroup)
                {
                    dynamic_cast<CdmValueUserGroup*>(m_rpCdmValue)->SetValue(m_lCurrentGroupId);
                    m_qleGroup->setText(pCumGroup->GetGroupName());
                }
                else
                {
                    m_qleGroup->setText("");
                    m_lCurrentGroupId = 0;
                }
            }
        }
    }
}
