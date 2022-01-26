/******************************************************************************
 ** WOGRA Middleware Server GUI Tools Module
 **
 ** @Author Wolfgang Graßhof 
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies All rights reserved
 ******************************************************************************/


#ifndef CWMSOBJECTLISTEDITORIF_H
#define CWMSOBJECTLISTEDITORIF_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes 
#include <QDialog>
#include <qmap.h>
#include <qpair.h>

// own Includes
#include "wmsgui.h"
#include "CwmsObjectListEditorBase.h"
#include "ui_CwmsObjectListEditor.h"


// forwards
class CwmsguiValidator;
class CdmObjectContainer;

typedef QPair<QString,QString> StringPair;

class WMSGUI_API CwmsObjectListEditorIf : public QDialog, public Ui::CwmsObjectListEditor, public CwmsContainerEditorBase
{
    Q_OBJECT

public:
    CwmsObjectListEditorIf(CdmObjectContainer* p_pContainer, QWidget* parent = nullptr);
    CwmsObjectListEditorIf(QWidget* parent = nullptr);
    virtual ~CwmsObjectListEditorIf();
    void AddColumn(QString p_qstrColumn);
    void SetContainer(CdmObjectContainer* p_pContainer);
    void SetModel(CdmQueryModel* p_pModel);
    void SetDefaultValueForNewObject(QString p_qstrValueName,
                                     QString p_qstrValue,
                                     QString p_qstrValue2);
    QTreeView* GetListView();
    void AddPopupItem(QString p_qstrItem);
    void ClearMenu();
    CdmObjectContainer* GetObjectList();
    void FillDialog();
    CwmsObjectListEditorWidgetIf* GetContainerEditorWidgetIf();

public slots:
    void DeleteClickedSlot();
    void NewClickedSlot();
    void EditClickedSlot();

private slots:
    void CloseClickedSlot();
};

#endif //
