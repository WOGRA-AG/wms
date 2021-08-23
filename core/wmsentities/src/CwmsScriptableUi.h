#ifndef CWMSSCRIPTABLEUI_H
#define CWMSSCRIPTABLEUI_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes
#include <QScriptable>
#include <QObject>

// Own Includes
#include "CwmsScriptableBase.h"
#include "basetools.h"

// Forwards
class CdmObject;
class CdmObjectContainer;

// TypeDefs



/* 
 * This class implements ui calls for the script environment.
 */
class BASETOOLS_API CwmsScriptableUi: public CwmsScriptableBase
{

public:
    CwmsScriptableUi( );
    virtual ~CwmsScriptableUi( );
    QObject* selectObject(CdmObjectContainer* p_pContainer);
    QObject* selectObjectList(CdmClass* p_pCdmClass);
    QObject* selectClass();

public slots:
    void openUi( CdmObject* p_pCdmObject);
    void openUi( CdmObjectContainer* p_pContainer);
    void openSearch( CdmObjectContainer* p_pContainer);
    void openImport( CdmObjectContainer* p_pContainer);
    void openExport( CdmObjectContainer* p_pContainer);
    void openHistory( CdmObjectContainer* p_pContainer);
    void openHistory( CdmObject* p_pCdmObject);
    void editPrintingTemplate( CdmObject* p_pCdmObject);
    void editPrintingTemplate( CdmObjectContainer* p_pContainer);
};

#endif // CWMSSCRIPTABLEUI_H

