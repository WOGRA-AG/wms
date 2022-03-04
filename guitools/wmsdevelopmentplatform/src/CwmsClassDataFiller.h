#ifndef CWMSCLASSDATAFILLER_H
#define CWMSCLASSDATAFILLER_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes
#include <QObject>
// Own Includes


// Forwards
class QTreeWidget;
class QComboBox;
class CdmClass;
class CdmClassManager;
class QTreeWidgetItem;
class CdmPackage;

// TypeDefs


/* 
 * This class implements the editor for the member sequence
 */
class CwmsClassDataFiller : public QObject
{
   Q_OBJECT

   private:
    static void FillFunctions(CdmClass* p_pCdmClass, QTreeWidgetItem* p_pqtwClass);
    static void FillMembersAndGroups(CdmClass* p_pCdmClass, QTreeWidgetItem* p_pqtwClass);
    static void FillPackage(CdmPackage *p_pPackage, QTreeWidgetItem *p_pParent);
   static bool IsTechnicalPackage(CdmPackage *p_pPackage);
public:
    static void FillClass(CdmClass* p_pCdmClass,
                          QTreeWidgetItem* p_pqtwClass);
    static void FillClasses(CdmClassManager* p_pClassManager,
                            QTreeWidgetItem* p_pParent,
                            bool p_bShowTechnicalItems);
    static void FillClassesToComboBox(QComboBox* p_pComboBox,
                                      bool p_bAddAbstractClasses,
                                      bool p_bFilterMode,
                                      bool p_bShowTechnicalClasses);
    static bool IsTechnicalClass(CdmClass* p_pClass);
};

#endif //
