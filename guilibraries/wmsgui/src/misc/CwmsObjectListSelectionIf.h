#ifndef CWMSOBJECTLISTSELECTIONIF_H
#define CWMSOBJECTLISTSELECTIONIF_H


// System and QT Includes
#include <QDialog>


// own Includes
#include "wmsgui.h"
#include "ui_CwmsObjectListSelection.h"


// forwards
class CdmClass;
class CdmObjectContainer;


class WMSGUI_API CwmsContainerSelectionIf : public QDialog, public Ui::CwmsObjectListSelection
{
private:
    qint64 m_lDbId;


public:
    CwmsContainerSelectionIf( QWidget* parent = NULL);
    virtual ~CwmsContainerSelectionIf(  );
    void SetClass(  CdmClass* pCdmClass );
    void SetClass( qint64 p_lDbId,qint64 p_lClassId );
    CdmObjectContainer* GetSelectedObjectContainer(  );
    int GetContainerCount();
    static CdmObjectContainer* GetObjectContainer( qint64 p_lDbId,qint64 p_lClassId, QWidget* p_pqwParent );
    static CdmObjectContainer *GetObjectContainer(CdmClass *p_pClass, QWidget *p_pqwParent);
};

#endif
