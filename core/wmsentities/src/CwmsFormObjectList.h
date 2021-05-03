#ifndef CWMSFORMOBJECTLIST_H
#define CWMSFORMOBJECTLIST_H

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

class BASETOOLS_API CwmsFormContainer : public CwmsFormBase
{

   public:
      CwmsFormContainer();
   public:
      CwmsFormContainer(CdmObject* p_pCdmObject);
   public:
      virtual ~CwmsFormContainer();
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
      bool GetExportEnabled();
   public:
      void SetExportEnabled(bool p_bValue);
   public:
      bool GetImportEnabled();
   public:
      void SetImportEnabled(bool p_bValue);
   public:
      bool GetSearchEnabled();
   public:
      void SetSearchEnabled(bool p_bValue);
   public:
      bool GetDefault();
   public:
      void SetDefault(bool p_bValue);
   public:
      QList<QString> GetFunctions();
   public:
      void SetFunctions(QString p_qstrValue);
   public:
      CdmObject* GetPrintingTemplate();
   public:
      void SetPrintingTemplate(CdmObject* p_pCdmValue);

   public:
   /** +-=---------------------------------------------------------Mo 10. Sep 16:19:32 2012-------*
    * @method  CwmsFormObjectList::SetFunctions              // public                            *
    * @return  void                                          //                                   *
    * @param   QList<QString> p_qstrlMembers           //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 10. Sep 16:19:32 2012----------*/
      void SetFunctions(QList<QString> p_qstrlMembers);
      bool GetCopyEnabled();
      void SetCopyEnabled(bool p_bValue);
      bool GetSaveAsCsvEnabled();
      void SetSaveAsCsvEnabled(bool p_bValue);
      bool GetNewEnabled();
      void SetNewEnabled(bool p_bValue);
};
#endif //
