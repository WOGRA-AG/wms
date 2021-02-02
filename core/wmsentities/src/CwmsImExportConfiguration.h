#ifndef CWMSIMEXPORTCONFIGURATION_H
#define CWMSIMEXPORTCONFIGURATION_H

#ifdef WURZELBLA
#define slots
#endif //


// System and QT Includes


// WMS Includes
#include "CdmObjectAdaptor.h"

// Own Includes
#include "basetools.h"

// Forwards
class CdmClass;

// Enumerations

class BASETOOLS_API CwmsImExportConfiguration: public CdmObjectAdaptor
{

   public:
      CwmsImExportConfiguration();
   public:
      CwmsImExportConfiguration(CdmObject* p_pCdmObject);
   public:
      virtual ~CwmsImExportConfiguration();
   public:
      int GetId();
   public:
      void SetId(int p_iValue);
   public:
      QString GetName();
   public:
      void SetName(QString p_qstrValue);
   private:
      int GetClassId();
   private:
      void SetClassId(int p_iValue);
   public:
      QString GetConfiguration();
   public:
      void SetConfiguration(QString p_qstrValue);
   public:
      static CwmsImExportConfiguration Create(CdmObjectContainer* p_pContainer);
   public:
      static bool Delete(CwmsImExportConfiguration cCwmsImExportConfiguration);
      void SetClass(CdmClass *p_pClass);
      CdmClass *GetClass();
      QString GetEncoding();
      void SetEncoding(QString p_qstrEncoding);
private:
      void SetClassUri(QString p_qstrUri);
    private:
      QString GetClassUri();
};
#endif //
