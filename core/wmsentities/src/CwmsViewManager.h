﻿/******************************************************************************
 ** WOGRA technologies Gmbh & Co KG Modul Information
 ** Modulename: CwmsViewManager.h
 ** Started Implementation: 2012/08/24
 ** Description:
 **
 ** implements the manager for views
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 **(C) copyright by WOGRA technologies GmbH & Co KG All rights reserved
 *****************************************************************************/

#ifndef CWMSVIEWMANAGER_H
#define CWMSVIEWMANAGER_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes
#include <QObject>

// Own Includes
#include "CwmsView.h"
#include "basetools.h"

// Forwards
class CdmClassManager;
class CdmObject;
class CdmObjectContainer;

// TypeDefs


/* 
 * This class implements the manager for views
 */
class BASETOOLS_API CwmsViewManager : public QObject
{
public:
    CwmsViewManager();
    virtual ~CwmsViewManager();
    CdmObjectContainer* GetContainer();
    void GetViewList(QLinkedList<CdmObject*>& p_rqlViews);
    CwmsView GetViewById(long p_lObjectId);
    CwmsView GetViewByName(QString p_qstrName);

    CwmsView GetViewByUri(QString p_qstrUri);
private:
    void CheckViewDataStructure();
    void CreateViewClass(CdmClassManager* p_pCdmClassManager);

};

#endif // CWMSVIEWMANAGER_H
