#ifndef CWMSJOURNALVIEWER_H
#define CWMSJOURNALVIEWER_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes
#include <QDialog>

// Own Includes
#include "wmsgui.h"
#include "ui_CwmsJournalViewer.h"


// Forwards
class CdmScheme;
class CdmObjectContainer;
class CdmObject;
class CdmJournalItem;
// TypeDefs


/* 
 * This class implements the viewer for journal data
 */
class WMSGUI_API CwmsJournalViewer : public QDialog, public Ui::CwmsJournalViewerClass
{
    Q_OBJECT

private:
    CdmScheme*   m_rpCdmDatabase;
    CdmObjectContainer* m_rpContainer;
    CdmObject*     m_rpCdmObject;
    QMap<QTreeWidgetItem*, CdmJournalItem*> m_qmItems;

public:
    CwmsJournalViewer( QWidget* p_pqwParent);
    virtual ~CwmsJournalViewer( );
    void FillDialog(CdmScheme* p_pCdmDtabase);
    void FillDialog(CdmObjectContainer* p_pContainer);
    void FillDialog(CdmObject* p_pCdmObject);
    void SetFromToDefaultData();

public slots:
    void CopyToClipboardClickedSlot();
    void RestoreClickedSlot();

private:
    void AddContainerHeader();
    void AddDbHeader();
    void AddObjectHeader();

    void ClearItems();
    void AddCommonHeaders(QStringList &qstrlHeader);
private slots:
    void RefreshClickedSlot( );

};

#endif
