/******************************************************************************
 ** WOGRA Middleware Server Data Manager Module
 **
 ** @Author Wolfgang Graßhof 
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies All rights reserved
 ******************************************************************************/

#ifndef CDMOBJECTFACTORY_H
#define CDMOBJECTFACTORY_H

// System and QT Includes
#include <qmap.h>


// own Includes
#include "CdmModelElement.h"


// forwards
class CdmObjectAdaptor;


/*
 * The CdmContainerAdaptor class is a baseclass
 * which can be derived by the client application.
 * with the help of this class the client application will
 * be informed, that a new object was created. In the
 * method which are needed to override you can react to
 * this events. For example creating a new object adaptor.
 * The object factory will manage one objectcontainer.
 */
class WMSMANAGER_API CdmContainerAdaptor
{

   private:
      /*
       * The Database Id
       */
      long m_lDbId;

      /*
       * The Objectlist Id
       */
      long m_lContainerId;

      friend class CdmObjectContainer;

   public:
    CdmContainerAdaptor(CdmObjectContainer* p_pContainer);
    CdmContainerAdaptor(long m_lDbId, long m_lObjectListId);
    CdmContainerAdaptor();
    virtual ~CdmContainerAdaptor();
    long DeleteObject(CdmObjectAdaptor* p_pCdmObjectAdaptor);
    long DeleteObject(long p_lObjectId);
    CdmObjectContainer* GetContainer() const;
    void Commit();
    CdmObject* CreateObject(QString p_qstrCaption);
    virtual void SetContainer(long p_lDbId, long p_lObjectListId);
    virtual void SetContainer(CdmObjectContainer* p_pContainer);
    CdmObject* FindObject(long p_lObjectId);
    const CdmClass* GetClass() const;
    long GetSchemeId() const;
    virtual void ObjectRefModifiedEvent(long p_lObjectId);
    void ResetContainer();
    virtual void ObjectCommitedEvent(long p_lObjectId);
    void SetContainer(QString p_qstrObjectListKeyname);

    bool IsValid();
    void ReloadContainerComplete() const;
protected:
    virtual void ObjectDeletedEvent(long p_lObjectId);
    virtual void ObjectCreatedEvent(long p_lObjectId);
    virtual void ObjectModifiedEvent(long p_lObjectId);
};

#endif //
