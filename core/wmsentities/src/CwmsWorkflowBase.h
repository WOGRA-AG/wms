#ifndef CWMSWORKFLOWBASE_H
#define CWMSWORKFLOWBASE_H

#ifdef WURZELBLA
#define slots
#endif //


// System and QT Includes


// WMS Includes
#include "CdmObjectAdaptor.h"

// Own Includes
#include "basetools.h"

// Forwards

// Enumerations

class BASETOOLS_API CwmsWorkflowBase: public CdmObjectAdaptor
{

   public:
      CwmsWorkflowBase();
   public:
      CwmsWorkflowBase(CdmObject* p_pCdmObject);
   public:
      virtual ~CwmsWorkflowBase();
   public:
      CdmObject* GetResponsibility();
   public:
      void SetResponsibility(CdmObject* p_pCdmValue);
   public:
      int GetPosition();
   public:
      void SetPosition(int p_iValue);
   public:
      QString GetName();
   public:
      void SetName(QString p_qstrValue);
   public:
      QString GetDescription();
   public:
      void SetDescription(QString p_qstrValue);
   public:
      int GetState();
   public:
      void SetState(int p_iValue);
   public:
      int GetMaxDuration();
   public:
      void SetMaxDuration(int p_iValue);
};
#endif //
