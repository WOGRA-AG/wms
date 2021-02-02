#ifndef CWMSFORMBASE_H
#define CWMSFORMBASE_H

#ifdef WURZELBLA
#define slots
#endif //


// System and QT Includes


// WMS Includes
#include "basetools.h"
#include "CdmObjectAdaptor.h"

// Own Includes

// Forwards

// Enumerations

class BASETOOLS_API CwmsFormBase: public CdmObjectAdaptor
{

   public:
      CwmsFormBase();
   public:
      CwmsFormBase(CdmObject* p_pCdmObject);
   public:
      virtual ~CwmsFormBase();
   public:
      QString GetName();
   public:
      void SetName(QString p_qstrValue);
   public:
      bool GetPrintEnabled();
   public:
      void SetPrintEnabled(bool p_bValue);
   public:
      bool GetJournalEnabled();
   public:
      void SetJournalEnabled(bool p_bValue);
   public:
      bool GetReadOnly();
   public:
      void SetReadOnly(bool p_bValue);
   public:
      bool GetDefault();
   public:
      void SetDefault(bool p_bValue);
   public:
      QString GetClassUri();
   public:
      void SetClassUri(QString p_iValue);
   public:
      CdmObject* GetPrintingTemplate();
   public:
      void SetPrintingTemplate(CdmObject* p_pCdmValue);
};
#endif //
