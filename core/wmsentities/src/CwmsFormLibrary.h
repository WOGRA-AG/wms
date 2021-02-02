#ifndef CWMSFORMLIBRARY_H
#define CWMSFORMLIBRARY_H

#ifdef WURZELBLA
#define slots
#endif //


// System and QT Includes


// WMS Includes
#include "CdmObjectAdaptor.h"

// Own Includes
#include "basetools.h"

// Forwards
class CdmObjectContainer;

// Enumerations

class BASETOOLS_API CwmsFormLibrary: public CdmObjectAdaptor
{

   public:
      CwmsFormLibrary();
   public:
      CwmsFormLibrary(CdmObject* p_pCdmObject);
   public:
      virtual ~CwmsFormLibrary();
   public:
      QString GetName();
   public:
      void SetName(QString p_qstrValue);
   public:
      QString GetVersion();
   public:
      void SetVersion(QString p_qstrValue);
   public:
      QString GetCode();
   public:
      void SetCode(QString p_qstrValue);
   public:
      static CwmsFormLibrary Create();
   public:
      static bool Delete(CwmsFormLibrary cCwmsFormLibrary);
    public:
      static CdmObjectContainer *GetContainer();
};
#endif //
