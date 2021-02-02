/******************************************************************************
 ** WOGRA technologies Modul Information
 ** Modulename: CdmValueEnum.cpp
 ** Started Implementation: 2009/04/07
 ** Description:
 ** 
 ** Implements the user value
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies All rights reserved
 *****************************************************************************/ 

// System and QT Includes
#include <QVariantMap>

// Own Includes
#include "wmsdefines.h"
#include "CdmDataProvider.h"
#include "CdmSessionManager.h"
#include "CdmValueEnum.h"
#include "CdmLogging.h"


/** +-=---------------------------------------------------------Di 28. Aug 09:58:48 2012----------*
 * @method  CdmValueEnum::CdmValueEnum                       // public                            *
 * @return                                                   //                                   *
 * @param   long p_lDatabaseId                               // Database Id                       *
 * @param   long p_lId                                       // Value Id                          *
 * @param   QString p_qstrKeyname                            // value keyname                     *
 * @param   CdmObject* p_pCdmObject                          // Parent Object                     *
 * @comment The Userconstructor                                                                   *
 *----------------last changed: --------------------------------Di 28. Aug 09:58:48 2012----------*/
CdmValueEnum::CdmValueEnum(long p_lDatabaseId,
                           long p_lId,
                           QString p_qstrKeyname,
                           CdmObject* p_pCdmObject)
   : CdmValueInt(eDmValueEnum, p_lDatabaseId, p_lId, p_qstrKeyname, p_pCdmObject)
{

   // nothing to do
}


/** +-=---------------------------------------------------------Di 28. Aug 09:58:58 2012----------*
 * @method  CdmValueEnum::CdmValueEnum                       // public                            *
 * @return                                                   //                                   *
 * @param   QDomElement& p_rqDomElement                      // XML Source                        *
 * @param   CdmObject* p_pCdmObject                          // Parent Object                     *
 * @comment The integer constructor.                                                              *
 *----------------last changed: --------------------------------Di 28. Aug 09:58:58 2012----------*/
CdmValueEnum::CdmValueEnum(QDomElement& p_rqDomElement, CdmObject* p_pCdmObject)
   : CdmValueInt(p_rqDomElement, p_pCdmObject)
{

}

/** +-=---------------------------------------------------------Di 28. Aug 09:59:03 2012----------*
 * @method  CdmValueEnum::CdmValueEnum                       // public                            *
 * @return                                                   //                                   *
 * @param   QVariantMap& p_rqvHash                          //                                   *
 * @param   CdmObject* p_pCdmObject                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 28. Aug 09:59:03 2012----------*/
CdmValueEnum::CdmValueEnum(QVariantMap& p_rqvHash, CdmObject* p_pCdmObject)
   : CdmValueInt(p_rqvHash, p_pCdmObject)
{

}

/** +-=---------------------------------------------------------Di 28. Aug 09:59:08 2012----------*
 * @method  CdmValueEnum::~CdmValueEnum                      // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CdmValueEnum                                                  *
 *----------------last changed: --------------------------------Di 28. Aug 09:59:08 2012----------*/
CdmValueEnum::~CdmValueEnum()
{

}

/** +-=---------------------------------------------------------So 10. Feb 11:39:04 2013----------*
 * @method  CdmValueEnum::GetDisplayString                   // public, const, virtual, slots     *
 * @return  QString                                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 10. Feb 11:39:04 2013----------*/
QString CdmValueEnum::GetDisplayString() const
{
   QString qstrRet;
   const CdmMember* pCdmMember = GetMember();

   if (CHKPTR(pCdmMember))
   {
      QStringList qstrlSelection = GetSelectionList();

      int iPos = GetValue();
      if (iPos < qstrlSelection.count() && iPos >= 0)
      {
         qstrRet = qstrlSelection[iPos];
         qstrRet = qstrRet.trimmed();
      }
   }

   return qstrRet;
}

/** +-=---------------------------------------------------------So 10. Feb 11:39:17 2013----------*
 * @method  CdmValueEnum::GetSelectionList                   // public, const, slots              *
 * @return  QStringList                                      //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 10. Feb 11:39:17 2013----------*/
QStringList CdmValueEnum::GetSelectionList() const
{
   QStringList qstrlSelection;
   const CdmMember* pCdmMember = GetMember();

   if (CHKPTR(pCdmMember))
   {
      qstrlSelection = pCdmMember->GetSelectionList();
   }

   return qstrlSelection;
}

/** +-=---------------------------------------------------------So 10. Feb 11:39:38 2013----------*
 * @method  CdmValueEnum::GetVariant                         // public, const, virtual            *
 * @return  QVariant                                         //                                   *
 * @comment This method returns the value as string for displaying information.                   *
 *----------------last changed: --------------------------------So 10. Feb 11:39:38 2013----------*/
QVariant CdmValueEnum::GetVariant() const
{
   QVariantMap qmVariant = CdmValue::GetVariant().toMap();
   qmVariant.insert(WMS_VALUE, GetValue());
   qmVariant.insert("Name", GetDisplayString());
   return qmVariant;
}

/** +-=---------------------------------------------------------So 10. Feb 11:39:48 2013----------*
 * @method  CdmValueEnum::GetValueVariant                    // public, const, virtual            *
 * @return  QVariant                                         //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 10. Feb 11:39:48 2013----------*/
QVariant CdmValueEnum::GetValueVariant() const
{
   return QVariant(GetDisplayString());
}

/** +-=---------------------------------------------------------Di 28. Aug 10:00:09 2012----------*
 * @method  CdmValueEnum::SetValueVariant                    // public, virtual                   *
 * @return  void                                             //                                   *
 * @param   QVariant& p_rqVariant                            //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 28. Aug 10:00:09 2012----------*/
void CdmValueEnum::SetValueVariant(QVariant& p_rqVariant)
{
    QStringList selectionList = GetSelectionList();
    int id = selectionList.indexOf(p_rqVariant.toString());

    if (id >= 0)
    {
        SetValue(id);
    }
    else
    {
        ERR("Invalid enum value " + p_rqVariant.toString());
    }
}
