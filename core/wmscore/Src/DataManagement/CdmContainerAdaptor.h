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
     qint64 m_lDbId;

      /*
       * The Objectlist Id
       */
     qint64 m_lContainerId;

      friend class CdmObjectContainer;

   public:
    CdmContainerAdaptor(CdmObjectContainer* p_pContainer);
    CdmContainerAdaptor(qint64 m_lDbId,qint64 m_lObjectListId);
    CdmContainerAdaptor();
    virtual ~CdmContainerAdaptor();
   qint64 DeleteObject(CdmObjectAdaptor* p_pCdmObjectAdaptor);
   qint64 DeleteObject(qint64 p_lObjectId);
    CdmObjectContainer* GetContainer() const;
    void Commit();
    CdmObject* CreateObject(QString p_qstrCaption);
    virtual void SetContainer(qint64 p_lDbId,qint64 p_lObjectListId);
    virtual void SetContainer(CdmObjectContainer* p_pContainer);
    CdmObject* FindObject(qint64 p_lObjectId);
    const CdmClass* GetClass() const;
   qint64 GetSchemeId() const;
    virtual void ObjectRefModifiedEvent(qint64 p_lObjectId);
    void ResetContainer();
    virtual void ObjectCommitedEvent(qint64 p_lObjectId);
    void SetContainer(QString p_qstrObjectListKeyname);

    bool IsValid();
    void ReloadContainerComplete() const;
protected:
    virtual void ObjectDeletedEvent(qint64 p_lObjectId);
    virtual void ObjectCreatedEvent(qint64 p_lObjectId);
    virtual void ObjectModifiedEvent(qint64 p_lObjectId);
};

#endif //
