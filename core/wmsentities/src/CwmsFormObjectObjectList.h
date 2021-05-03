#ifndef CWMSFORMOBJECTOBJECTLIST_H
#define CWMSFORMOBJECTOBJECTLIST_H

#ifdef WURZELBLA
#define slots
#endif //


// System and QT Includes


// WMS Includes
#include "basetools.h"
#include "CwmsFormStandardObjectList.h"

// Own Includes

// Forwards

// Enumerations

class BASETOOLS_API CwmsFormObjectContainer : public CwmsFormStandardContainer
{

   public:
      CwmsFormObjectContainer();
   public:
      CwmsFormObjectContainer(CdmObject* p_pCdmObject);
   public:
      virtual ~CwmsFormObjectContainer();
   public:
      QList<QString> GetSelectionDisplayMembers();
	  void SetSelectionDisplayMembers(QList<QString> p_qllMembers);
public:
      void SetSelectionDisplayMembers(QString p_qstrValue);
   public:
      bool GetSelectionListReadOnly();
   public:
      void SetSelectionListReadOnly(bool p_bValue);
   public:
      QString GetEditorKeyname();
   public:
      void SetEditorKeyname(QString p_qstrValue);
   public:
      QString GetEditorWql();
   public:
      void SetEditorWql(QString p_qstrValue);
   public:
      CdmObject* GetSelectionView();
   public:
      void SetSelectionView(CdmObject* p_pValue);
   public:
      void SetSelectionObjectList(CdmObjectContainer* p_pValue);
   public:
      CdmObjectContainer* GetSelectionObjectList();
   public:
      static CwmsFormObjectContainer Create(CdmObjectContainer* p_pContainer);
   public:
      static bool Delete(CwmsFormObjectContainer cCwmsFormObjectObjectList);
};
#endif //
