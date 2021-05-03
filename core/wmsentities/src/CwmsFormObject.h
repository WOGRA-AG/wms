#ifndef CWMSFORMOBJECT_H
#define CWMSFORMOBJECT_H

#ifdef WURZELBLA
#define slots
#endif //


// System and QT Includes


// WMS Includes
#include "basetools.h"
#include "CwmsFormBase.h"

// Own Includes

// Forwards

// Enumerations

class BASETOOLS_API CwmsFormObject : public CwmsFormBase
{

   public:
      CwmsFormObject();
      CwmsFormObject(CdmObject* p_pCdmObject);
      virtual ~CwmsFormObject();

      QString GetCaptionValue();
      void SetCaptionValue(QString p_qstrValue);
      QString GetWql();
      void SetWql(QString p_qstrValue);
      QList<QString> GetVisibleMembers();
      void SetVisibleMembers(QList<QString> p_qllValue);
      QList<QString> GetFunctions();
      void SetFunctions(QList<QString> p_qllValue);
      QMap<QString, int> GetDisplayTypes();
      void SetDisplayTypes(QMap<QString, int> p_qmDisplayTypes);
      QMap<QString, QString> GetObjectRefAssignment();
      void SetObjectRefAssignment(QMap<QString, QString> p_qmValues);
      QMap<QString, QString> GetDefaultValues();
      void SetDefaultValues(QMap<QString, QString> p_qmValues);
      static CwmsFormObject Create(CdmObjectContainer* p_pContainer);
      static bool Delete(CwmsFormObject cCwmsFormObject);
};
#endif //
