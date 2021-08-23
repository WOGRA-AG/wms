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
    void GetViewList(QList<CdmObject*>& p_rqlViews);
    CwmsView GetViewById(long p_lObjectId);
    CwmsView GetViewByName(QString p_qstrName);

    CwmsView GetViewByUri(QString p_qstrUri);
private:
    void CheckViewDataStructure();
    void CreateViewClass(CdmClassManager* p_pCdmClassManager);

    void UpdateViewClass(CdmClass *p_pClass);
};

#endif // CWMSVIEWMANAGER_H
