/******************************************************************************
 ** WOGRA Middleware Server Data Manager Module
 **
 ** @Author Wolfgang Gra‗hof 
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies All rights reserved
 ******************************************************************************/

#ifndef CDMCLASSDIAMONDVALIDATOR_H
#define CDMCLASSDIAMONDVALIDATOR_H

// System and QT Includes
#include <QString>

// own Includes
#include "datamanager.h"

// forwards
class CdmClass;
class CdmMember;
class CdmClassMethod;
class CdmClassValidator;


/**
 *  Implements the Classes for WMS. One class can only own 1024 members.
 *  A class can only be created by the class manager.
 */
class WMSMANAGER_API CdmClassDiamondValidator
{
   private:
      CdmClass* m_rpClass;
      QString m_qstrErrorMessage;
      
   public:
      CdmClassDiamondValidator(CdmClass* p_pClass);
      virtual ~CdmClassDiamondValidator();
      bool Validate();
      //************************************
      // Method:    Validate
      // FullName:  CdmClassDiamondValidator::Validate
      // Access:    public static 
      // Returns:   bool
      // Qualifier:
      // Parameter: CdmClass * p_pClass
      //************************************
      static bool Validate(CdmClass* p_pClass);
      QString GetErrorMessage() const { return m_qstrErrorMessage; }

   private:
      bool ValidateMembers();
      bool ValidateMethods();
      bool ValidateValidators();
      CdmClass* FindClassById(qint64 p_lId);
      bool ValidateBaseClassesMembers(CdmClass* p_pClass, QMap<qint64,CdmMember*>& p_qmExistingMembers);
      bool ValidateBaseClassMembers(CdmClass* p_pClass, QMap<qint64,CdmMember*>& p_qmExistingMembers);
      bool CheckMember(CdmMember* pMember, QMap<qint64,CdmMember*>& p_qmExistingMembers);
      bool ValidateBaseClassesMethods(CdmClass* p_pClass, QMap<QString,CdmClassMethod*>& p_qmExistingMethods);
      bool ValidateBaseClassMethods(CdmClass* p_pClass, QMap<QString,CdmClassMethod*>& p_qmExistingMethods);
      bool CheckMethod(CdmClassMethod* p_pMethod, QMap<QString,CdmClassMethod*>& p_qmExistingMethods);
};

#endif //
