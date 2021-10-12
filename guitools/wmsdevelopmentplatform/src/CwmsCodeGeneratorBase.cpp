/******************************************************************************
 ** WOGRA technologies GmbH & Co. KG Modul Information
 ** Modulename: CwmsCodeGeneratorBase.cpp
 ** Started Implementation: 2012/07/13
 ** Description:
 **
 ** Implements the language independent base class for code generation
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co. KG All rights reserved
 *****************************************************************************/

// System and QT Includes
#include <QFile>
#include <QTextStream>

// WMS Includes
#include "CdmClass.h"

// own Includes
#include "CwmsCodeGeneratorBase.h"


/** +-=---------------------------------------------------------Fr 13. Jul 09:44:00 2012----------*
 * @method  CwmsCodeGeneratorBase::CwmsCodeGeneratorBase     // public                            *
 * @return                                                   //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 13. Jul 09:44:00 2012----------*/
CwmsCodeGeneratorBase::CwmsCodeGeneratorBase()
{
}

/** +-=---------------------------------------------------------Fr 13. Jul 09:44:09 2012----------*
 * @method  CwmsCodeGeneratorBase::~CwmsCodeGeneratorBase    // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CwmsCodeGeneratorBase                                         *
 *----------------last changed: --------------------------------Fr 13. Jul 09:44:09 2012----------*/
CwmsCodeGeneratorBase::~CwmsCodeGeneratorBase()
{
}

/** +-=---------------------------------------------------------Fr 13. Jul 09:44:35 2012----------*
 * @method  CwmsCodeGeneratorBase::SaveFile                  // protected                         *
 * @return  void                                             //                                   *
 * @param   QString p_qstrFilename                           //                                   *
 * @param   QString p_qstrContent                            //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 13. Jul 09:44:35 2012----------*/
void CwmsCodeGeneratorBase::SaveFile(QString p_qstrFilename, QString p_qstrContent)
{
   QFile qFile(p_qstrFilename);

   if (qFile.open(QIODevice::WriteOnly | QIODevice::Text))
   {
      QTextStream qTextStream(&qFile);
      qTextStream << p_qstrContent;
      qFile.close();
   }
}

/** +-=---------------------------------------------------------Mo 23. Jul 10:24:05 2012----------*
 * @method  CwmsCodeGeneratorBase::GenerateCodeMemberName    // protected                         *
 * @return  QString                                          //                                   *
 * @param   QString p_qstrMember                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 23. Jul 10:24:05 2012----------*/
QString CwmsCodeGeneratorBase::GenerateCodeMemberName(QString p_qstrMember)
{
   QString qstrRet;
   qstrRet = p_qstrMember.remove("_");
   qstrRet = p_qstrMember.remove(" ");
   qstrRet = p_qstrMember.remove(":");
   qstrRet = p_qstrMember.remove("!");
   return qstrRet;
}

/** +-=---------------------------------------------------------Fr 13. Jul 09:50:11 2012----------*
 * @method  CwmsCodeGeneratorBase::AddIndent                 // protected                         *
 * @return  QString                                          //                                   *
 * @param   int p_iIndentStage                               //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 13. Jul 09:50:11 2012----------*/
QString CwmsCodeGeneratorBase::AddIndent(int p_iIndentStage)
{
   QString qstrIndent;

   while (p_iIndentStage > 0)
   {
      qstrIndent += "   ";
      p_iIndentStage--;
   }

   return qstrIndent;
}

/** +-=---------------------------------------------------------Fr 13. Jul 13:23:20 2012----------*
 * @method  CwmsCodeGeneratorBase::CheckSetterMethod         // protected                         *
 * @return  bool                                             //                                   *
 * @param   EdmValue p_eDmValue                              //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 13. Jul 13:23:20 2012----------*/
bool CwmsCodeGeneratorBase::CheckSetterMethod(EdmValueType p_eDmValue)
{
   bool bRet = false;

   switch (p_eDmValue)
   {
   case eDmValueBinaryDocument:
   case eDmValueBool:
   case eDmValueCharacterDocument:
   case eDmValueDate:
   case eDmValueDateTime:
   case eDmValueDouble:
   case eDmValueEnum:
   case eDmValueFloat:
   case eDmValueInt:
   case eDmValueLong:
   case eDmValueContainerRef:
   case eDmValueObjectRef:
   case eDmValueString:
   case eDmValueTime:
   case eDmValueUser:
   case eDmValueDictIntInt:
   case eDmValueDictIntString:
   case eDmValueDictStringDouble:
   case eDmValueDictStringInt:
   case eDmValueDictStringString:
   case eDmValueListDouble:
   case eDmValueListInt:
   case eDmValueListObjects:
   case eDmValueListString:
   case eDmValueDictIntDouble:
      bRet = true;
      break;
   case eDmValueCounter:
   case eDmValueObjectTree:
   case eDmValueFormula:
   default:
      bRet = false;
      break;
   }

   return bRet;
}

/** +-=---------------------------------------------------------Fr 13. Jul 13:36:21 2012----------*
 * @method  CwmsCodeGeneratorBase::CheckGetterMethod         // protected                         *
 * @return  bool                                             //                                   *
 * @param   EdmValue p_eDmValue                              //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 13. Jul 13:36:21 2012----------*/
bool CwmsCodeGeneratorBase::CheckGetterMethod(EdmValueType p_eDmValue)
{
   bool bRet = false;

   switch (p_eDmValue)
   {
   case eDmValueBinaryDocument:
   case eDmValueBool:
   case eDmValueCharacterDocument:
   case eDmValueCounter:
   case eDmValueDate:
   case eDmValueDateTime:
   case eDmValueDouble:
   case eDmValueEnum:
   case eDmValueFloat:
   case eDmValueFormula:
   case eDmValueInt:
   case eDmValueListDouble:
   case eDmValueListInt:
   case eDmValueListObjects:
   case eDmValueListString:
   case eDmValueLong:
   case eDmValueContainerRef:
   case eDmValueObjectRef:
   case eDmValueString:
   case eDmValueTime:
   case eDmValueUser:
   case eDmValueDictIntDouble:
   case eDmValueDictIntInt:
   case eDmValueDictIntString:
   case eDmValueDictStringDouble:
   case eDmValueDictStringInt:
   case eDmValueDictStringString:
      bRet = true;
      break;

   case eDmValueObjectTree:
   default:
      bRet = false;
      break;
   }

   return bRet;
}

/** +-=---------------------------------------------------------Mi 18. Jul 08:42:40 2012----------*
 * @method  CwmsCodeGeneratorBase::GetClassMembers           // protected                         *
 * @return  void                                             //                                   *
 * @param   CdmClass* p_pCdmClass                            //                                   *
 * @param   bool p_bIncludeBaseClassMembers                  //                                   *
 * @param   QMap<qint64, CdmMember*>& p_rqmMembers             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 18. Jul 08:42:40 2012----------*/
void CwmsCodeGeneratorBase::GetClassMembers(CdmClass* p_pCdmClass,
                                            bool p_bIncludeBaseClassMembers,
                                            QMap<qint64,
                                            CdmMember*>& p_rqmMembers)
{
   if (p_bIncludeBaseClassMembers)
   {
      p_rqmMembers = p_pCdmClass->GetClassMemberMap();
   }
   else
   {
      p_pCdmClass->GetMemberMap(p_rqmMembers);
   }
}
