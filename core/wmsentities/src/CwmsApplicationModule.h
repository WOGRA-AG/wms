#ifndef CWMSAPPLICATIONMODULE_H
#define CWMSAPPLICATIONMODULE_H

#ifdef WURZELBLA
#define slots
#endif //


// System and QT Includes
#include <QPixmap>

// WMS Includes
#include "CdmObjectAdaptor.h"

// Own Includes
#include "basetools.h"

// Forwards

// Enumerations

class BASETOOLS_API CwmsApplicationModule: public CdmObjectAdaptor
{
      

   public:
      CwmsApplicationModule();
      CwmsApplicationModule(CdmObject* p_pCdmObject);
      virtual ~CwmsApplicationModule();
      QString GetName();
      void SetName(QString p_qstrValue);
      int GetPosition();
      void SetPosition(int p_iValue);
      CdmObjectContainer* GetContainerModule();
      void SetContainerModule(CdmObjectContainer* p_pCdmOLValue);
      CdmObject* GetObjectModule();
      void SetObjectModule(CdmObject* p_pCdmValue);
      CdmObject* GetUserInterface();
      void SetUserInterface(CdmObject* p_pCdmValue);
      bool GetDefault();
      void SetDefault(bool p_bValue);
      bool GetActive();
      void SetActive(bool p_bValue);
      CdmObject* GetView();
      void SetView(CdmObject* p_pCdmValue);
      QPixmap GetIcon();
      void SetIcon(QString p_qstrFilename);

   
      static CwmsApplicationModule Create(CdmObjectContainer* p_pContainer);
      static bool Delete(CwmsApplicationModule cCwmsApplicationModule);
};

#endif //
