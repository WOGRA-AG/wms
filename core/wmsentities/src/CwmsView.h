#ifndef CWMSVIEW_H
#define CWMSVIEW_H

#ifdef WURZELBLA
#define slots
#endif //


// System and QT Includes


// WMS Includes
#include "CdmObjectAdaptor.h"

// Own Includes
#include "basetools.h"
// Forwards
class QStandardItemModel;
class CdmClassMethod;

// Enumerations

class BASETOOLS_API CwmsView: public CdmObjectAdaptor
{

   public:
      CwmsView();
      CwmsView(CdmObject* p_pCdmObject);
      virtual ~CwmsView();
      int GetId();
      void SetId(int p_iValue);
      QString GetName();
      void SetName(QString p_qstrValue);
      QString GetViewCommand();
      void SetViewCommand(QString p_qstrValue);
      QString GetComment();
      void SetComment(QString p_qstrValue);
      int GetReference();
      void SetReference(int p_iValue);
      bool GetValid();
      void SetValid(bool p_bValue);
      static CwmsView Create();
      CdmObject* GetReport();
      void SetReport(CdmObject* p_pObject);

      static bool Delete(CwmsView cCwmsView);
      bool IsWql();
      bool IsModel();
      QStandardItemModel *GetModel();
      static CdmClassMethod *FindModelMethod(QString &p_qstrModelMethod);
private:
      CdmClassMethod *FindModelMethod();
};
#endif //
