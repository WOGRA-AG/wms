#ifndef CWMSOBJECTCONTAINERDATAFILLER_H
#define CWMSOBJECTCONTAINERDATAFILLER_H

// System and QT Includes
#include <QObject>
// Own Includes


// Forwards
class QTreeWidget;
class CdmClass;
class QTreeWidgetItem;

// TypeDefs


/* 
 * This class implements the editor for the member sequence
 */
class CwmsObjectContainerDataFiller
{
public:
    static void FillAllObjectContainersToView(QTreeWidget* p_pTree, bool p_bShowTechnicalClasses, int p_iLimit);
    static void FillObjectContainersToClass(CdmClass* p_pClass, QTreeWidgetItem* p_pItem, int p_iLimit);
    static void FillObjectContainersToClass(CdmClass* p_pClass, QTreeWidget* p_pTreeWidget);
};

#endif //
