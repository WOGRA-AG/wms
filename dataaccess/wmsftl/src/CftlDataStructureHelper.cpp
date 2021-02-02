/******************************************************************************
 ** WOGRA technologies Gmbh & Co KG Modul Information
 ** Modulename: CftlDataStructureHelper.cpp
 ** Started Implementation: 2010/11/12
 ** Description:
 ** 
 ** This class contains helper functions for working with the wms db structure.
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies Gmbh & Co KG All rights reserved
 *****************************************************************************/ 

// System and QT Includes

// WMS Manager Includes
#include "CdmLogging.h"

// Own Includes
#include "CftlDataStructureHelper.h"

/** +-=---------------------------------------------------------Mo 25. Mrz 15:34:31 2013----------*
 * @method  CftlDataStructureHelper::GetTableIdName         // public, static                    *
 * @return  QString                                          //                                   *
 * @comment This method returns the name of the id field in the table.                            *
 *----------------last changed: --------------------------------Mo 25. Mrz 15:34:31 2013----------*/
QString CftlDataStructureHelper::GetTableIdName()
{
   return "valueid";
}

/** +-=---------------------------------------------------------Fr 12. Nov 10:29:39 2010----------*
 * @method  CftlDataStructureHelper::GetTableName           // public, static                    *
 * @return  QString                                          //                                   *
 * @param   EdmValue p_eDmValueType                          //                                   *
 * @comment This method returns the table name dependent to the query element.                    *
 *----------------last changed: --------------------------------Fr 12. Nov 10:29:39 2010----------*/
QString CftlDataStructureHelper::GetTableName(EdmValueType p_eDmValueType)
{
   QString qstrTableName;

   switch(p_eDmValueType)
   {
   case eDmValueLong:
      qstrTableName = "V_VALUE_LONG";
      break;
   case eDmValueInt:
   case eDmValueUser:
   case eDmValueUserGroup:
   case eDmValueEnum:
      qstrTableName = "V_VALUE_INT";
      break;
   case eDmValueObjectRef:
      qstrTableName = "V_VALUE_OBJECTREFERENCE";
      break;
   case eDmValueCounter:
      qstrTableName = "V_VALUE_COUNTER";
      break;
   case eDmValueBool:
      qstrTableName = "V_VALUE_BOOL";
      break;
   case eDmValueFloat:
      qstrTableName = "V_VALUE_FLOAT";
      break;
   case eDmValueDouble:
      qstrTableName = "V_VALUE_DOUBLE";
      break;
   case eDmValueString:
      qstrTableName = "V_VALUE_STRING";
      break;
   case eDmValueDate:
      qstrTableName = "V_VALUE_DATE";
      break;
   case eDmValueTime:
      qstrTableName = "V_VALUE_TIME";
      break;
   case eDmValueDateTime:
      qstrTableName = "V_VALUE_DATETIME";
      break;
   case eDmValueContainerRef:
      qstrTableName = "V_VALUE_OBJECTLISTREFERENCE";
      break;
   case eDmValueBinaryDocument:
      qstrTableName = "V_VALUE_BINARYDOCUMENT";
      break;
   case eDmValueCharacterDocument:
      qstrTableName = "V_VALUE_CHARACTERDOCUMENT";
      break;
      // The following types are all derived from chardoc
   case eDmValueListInt:
   case eDmValueListDouble:
   case eDmValueListString:
   case eDmValueDictStringInt:
   case eDmValueDictStringString:
   case eDmValueDictStringDouble:
   case eDmValueDictIntInt:
   case eDmValueDictIntString:
   case eDmValueDictIntDouble:
      qstrTableName = "V_VALUE_CHARACTERDOCUMENT";
      break;
   default:
      ERR("Invalid Type selected");
      qstrTableName = "Invalid Type";
      break;
   }

   return qstrTableName;
}

/** +-=---------------------------------------------------------Mo 25. Mrz 15:33:21 2013----------*
 * @method  CftlDataStructureHelper::GetDataFieldName       // public, static                    *
 * @return  QString                                          //                                   *
 * @comment This method returns the name of the data field.                                       *
 *----------------last changed: --------------------------------Mo 25. Mrz 15:33:21 2013----------*/
QString CftlDataStructureHelper::GetDataFieldName()
{
   return "Val";
}

/** +-=---------------------------------------------------------Sa 7. Mai 11:22:07 2011-----------*
 * @method  CftlDataStructureHelper::GetFirstMember         // public, static                    *
 * @return  QString                                          //                                   *
 * @param   QString p_qstrMemberChain                        //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 7. Mai 11:22:07 2011-----------*/
QString CftlDataStructureHelper::GetFirstMember(QString p_qstrMemberChain)
{
   QString qstrRet;

   if (p_qstrMemberChain.contains("."))
   {
      int iPos = p_qstrMemberChain.indexOf(".");
      qstrRet = p_qstrMemberChain.left(iPos);
   }
   else
   {
      qstrRet = p_qstrMemberChain;
   }

   return qstrRet;
}

/** +-=---------------------------------------------------------Sa 7. Mai 11:48:45 2011-----------*
 * @method  CftlDataStructureHelper::GetLastMember          // public, static                    *
 * @return  QString                                          //                                   *
 * @param   QString p_qstrMemberChain                        //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 7. Mai 11:48:45 2011-----------*/
QString CftlDataStructureHelper::GetLastMember(QString p_qstrMemberChain)
{
   QString qstrRet;

   if (p_qstrMemberChain.contains("."))
   {
      int iPos = p_qstrMemberChain.lastIndexOf('.');
      qstrRet = p_qstrMemberChain.mid(iPos, p_qstrMemberChain.length() - iPos);
   }
   else
   {
      qstrRet = p_qstrMemberChain;
   }

   return qstrRet;
}