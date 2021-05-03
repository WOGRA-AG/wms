#ifndef CWMSESCALATION_H
#define CWMSESCALATION_H

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

class BASETOOLS_API CwmsEscalation: public CdmObjectAdaptor
{

   public:
      CwmsEscalation();
   public:
      CwmsEscalation(CdmObject* p_pCdmObject);
   public:
      virtual ~CwmsEscalation();
   public:
      QList<int> GetEmployees();
   public:
      void AddEmployee(int p_iValue);
   public:
      int GetViolationOfLimit();
   public:
      void SetViolationOfLimit(int p_iValue);
   public:
      int GetEscalationStep();
   public:
      void SetEscalationStep(int p_iValue);
   public:
      static CwmsEscalation Create(CdmObjectContainer* p_pContainer);
   public:
      static bool Delete(CwmsEscalation cCbmsEscalation);



   private:
   /** +-=---------------------------------------------------------Mi 17. Okt 16:14:24 2012-------*
    * @method  CwmsEscalation::CreateMailContent             // private                           *
    * @return  QString                                       //                                   *
    * @param   CdmObject* p_pCdmWorkflow                     //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 17. Okt 16:14:24 2012----------*/
    QString CreateMailContent(CdmObject* p_pCdmWorkflow);

   public:
   /** +-=---------------------------------------------------------Mi 17. Okt 16:18:12 2012-------*
    * @method  CwmsEscalation::SendEscalationMail            // public                            *
    * @return  void                                          //                                   *
    * @param   CdmObject* pCdmWorkflow                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 17. Okt 16:18:12 2012----------*/
    void SendEscalationMail(CdmObject* pCdmWorkflow);
};
#endif //
