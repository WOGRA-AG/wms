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
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QWidget>
#include <QLineEdit>
#include <QTreeWidget>

// own Includes
#include "CwmsUserChoiceIf.h"
#include "CdmDataProvider.h"
#include "CdmSessionManager.h"
#include "CumUser.h"
#include "CumUserManager.h"
#include "CdmLogging.h"
#include "CdmValueUser.h"
#include "CoedtwUser.h"


/** +-=---------------------------------------------------------Di 28. Aug 15:06:06 2012----------*
 * @method  CoedtwUser::CoedtwUser                           // public, virtual                   *
 * @return                                                   //                                   *
 * @param   CdmValue* p_pCdmValue                            //                                   *
 * @param   QWidget* p_pqwParent = nullptr                      //                                   *
 * @comment The Constructor for valueediting.                                                     *
 *----------------last changed: --------------------------------Di 28. Aug 15:06:06 2012----------*/
CoedtwUser::CoedtwUser(CdmValue* p_pCdmValue, QWidget* p_pqwParent)
    : CoeValueWidget(p_pCdmValue, p_pqwParent),
      m_lCurrentUserId(0)
{
    m_pqbButton = nullptr;
    m_pqleUser = nullptr;
}

CoedtwUser::CoedtwUser(const CdmObject *pEventObject, CdmValue* p_pCdmValue, QWidget* p_pqwParent)
    : CoeValueWidget(pEventObject, p_pCdmValue, p_pqwParent),
      m_lCurrentUserId(0)
{
    m_pqbButton = nullptr;
    m_pqleUser = nullptr;
}

/** +-=---------------------------------------------------------Di 28. Aug 15:06:15 2012----------*
 * @method  CoedtwUser::CoedtwUser                           // public, virtual                   *
 * @return                                                   //                                   *
 * @param   CdmMember* p_pCdmMember                          //                                   *
 * @param   QString p_qstrKeyname                            //                                   *
 * @param   QWidget* p_pqwParent = nullptr                      //                                   *
 * @comment The Constuctor for searching.                                                         *
 *----------------last changed: --------------------------------Di 28. Aug 15:06:15 2012----------*/
CoedtwUser::CoedtwUser(CdmMember* p_pCdmMember, QString p_qstrKeyname, QWidget* p_pqwParent)
    : CoeValueWidget(p_pCdmMember, p_qstrKeyname, p_pqwParent),
      m_lCurrentUserId(0)
{
    m_pqbButton = nullptr;
}

/** +-=---------------------------------------------------------Di 28. Aug 15:06:20 2012----------*
 * @method  CoedtwUser::~CoedtwUser                          // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CoedtwBinaryDocument                                          *
 *----------------last changed: --------------------------------Di 28. Aug 15:06:20 2012----------*/
CoedtwUser::~CoedtwUser()
{
    // nothing to do
}

/** +-=---------------------------------------------------------Di 28. Aug 15:06:32 2012----------*
 * @method  CoedtwUser::GetEditWidget                        // public                            *
 * @return  QWidget*                                         //                                   *
 * @param   QWidget* p_pqwParent                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 28. Aug 15:06:32 2012----------*/
QWidget* CoedtwUser::GetEditWidget(QWidget* p_pqwParent)
{
    QWidget* pqWidget = new QWidget(p_pqwParent);
    QHBoxLayout* pqLayout = new QHBoxLayout(pqWidget);
    m_pqleUser = new QLineEdit(pqWidget);
    m_pqleUser->setReadOnly(true);
    pqLayout->addWidget(m_pqleUser);
    m_pqbButton = new QPushButton(QStringLiteral("Auswählen"), pqWidget);
    pqLayout->addWidget(m_pqbButton);
    connect(m_pqbButton, SIGNAL(clicked(bool)), this, SLOT(openNewWindow()));
    return pqWidget;
}

/** +-=---------------------------------------------------------Di 28. Aug 15:09:33 2012----------*
 * @method  CoedtwUser::SetValue                             // protected, virtual                *
 * @return  void                                             //                                   *
 * @param   CdmValue* p_pCdmValue                            //                                   *
 * @comment This method sets the value in the widget.                                             *
 *----------------last changed: --------------------------------Di 28. Aug 15:09:33 2012----------*/
void CoedtwUser::SetValue(CdmValue* p_pCdmValue)
{
    if (m_pqleUser && p_pCdmValue)
    {
        CumUser* pUser = ((CdmValueUser*)p_pCdmValue)->GetUser();

        if (pUser)
        {
            m_pqleUser->setText(pUser->GetDisplayString());
            m_lCurrentUserId = pUser->GetId();
        }
        else
        {
            m_pqleUser->setText("");
        }
    }
}

void CoedtwUser::setEventClassValue()
{
    if(CHKPTR(m_rpCdmValue) && m_pqleUser)
    {
        CumUser* pUser = ((CdmValueUser*)m_rpCdmValue)->GetUser();

        if (pUser)
        {
            m_pqleUser->setText(pUser->GetDisplayString());
            m_lCurrentUserId = pUser->GetId();
        }
        else
        {
            m_pqleUser->setText("");
        }

        if(!m_qlEventClassValues.contains(m_rpCdmValue))
        {
            m_qlEventClassValues.append(m_rpCdmValue);
        }
    }
}

/** +-=---------------------------------------------------------Di 28. Aug 15:09:40 2012----------*
 * @method  CoedtwUser::ValueChangedSlot                     // private, slots                    *
 * @return  void                                             //                                   *
 * @comment This slot will be called if the value has changed.                                    *
 *----------------last changed: --------------------------------Di 28. Aug 15:09:40 2012----------*/
void CoedtwUser::ValueChangedSlotByUser()
{
    setEventClassValue();
}

/** +-=---------------------------------------------------------Di 28. Aug 15:09:47 2012----------*
 * @method  CoedtwUser::SetReadOnly                          // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment This method sets the current Value widget in ReadOnlymode.                            *
 *----------------last changed: --------------------------------Di 28. Aug 15:09:47 2012----------*/
void CoedtwUser::SetReadOnly()
{
    m_pqbButton->hide();
}

void CoedtwUser::SetEditable()
{
    m_pqbButton->show();
}

/** +-=---------------------------------------------------------Di 28. Aug 15:09:52 2012----------*
 * @method  CoedtwUser::GetSearchWidget                      // public, virtual                   *
 * @return  QWidget*                                         //                                   *
 * @param   QWidget* p_pqwParent                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 28. Aug 15:09:52 2012----------*/
QWidget* CoedtwUser::GetSearchWidget(QWidget* p_pqwParent)
{
    return GetEditWidget(p_pqwParent);
}

/** +-=---------------------------------------------------------Di 28. Aug 15:09:57 2012----------*
 * @method  CoedtwUser::AddQueryElement                      // public, virtual                   *
 * @return  void                                             //                                   *
 * @param   CdmQueryElement* p_pCdmQueryElementParent        //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 28. Aug 15:09:57 2012----------*/
void CoedtwUser::AddQueryElement(CdmQueryElement* p_pCdmQueryElementParent)
{
    if (CHKPTR(p_pCdmQueryElementParent) && m_lCurrentUserId > 0)
    {
        EdmQueryCompareType eDmQueryCompareType = eDmQueryCompareTypeEqual;

        CdmQueryElement* pCdmQueryElement = new CdmQueryElement(p_pCdmQueryElementParent->GetQuery(),
                                                                eDmQueryElementTypeCompare,
                                                                eDmQueryCompareType);

        pCdmQueryElement->SetComparisonValue(m_qstrKeyname, m_lCurrentUserId);
        p_pCdmQueryElementParent->AddChild(pCdmQueryElement);
    }
}

void CoedtwUser::openNewWindow(){
    m_lCurrentUserId = CwmsUserChoiceIf::GetUserSelection(nullptr);

    if (m_lCurrentUserId > 0)
    {
       CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

       if (CHKPTR(pCdmManager))
       {
          CumUserManager* pCumUserManager = pCdmManager->GetUserManager();

          if (CHKPTR(pCumUserManager))
          {
             CumUser* pCumUser = pCumUserManager->FindUserById(m_lCurrentUserId);

             if (pCumUser)
             {
                 if (m_rpCdmValue)
                 {
                    dynamic_cast<CdmValueUser*>(m_rpCdmValue)->SetValue(m_lCurrentUserId);
                 }

                 m_pqleUser->setText(pCumUser->GetDisplayString());
             }
             else
             {
                 m_pqleUser->setText("");
                 m_lCurrentUserId = 0;
             }
          }
       }
    }
}
