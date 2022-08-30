#ifndef CWMSOBJECTEDITOR_H
#define CWMSOBJECTEDITOR_H

// System and QT Includes
#include <QWidget>
#include <QScrollArea>
#include <qstringlist.h>
#include <qpair.h>
#include <qmap.h>
#include <QList>

// WMS Includes
#include "CdmObjectAdaptor.h"

// own Includes
#include "CwmsApplicationModule.h"
#include "ui_CwmsObjectEditor.h"
#include "wmsgui.h"

// forwards
class CwmsRuntime;
class CdmObject;
class CdmClassGroup;
class CdmClass;
class CdmValue;
class CdmMember;
class CdmQueryModel;
class QVBoxLayout;
class QFrame;
class QPushButton;
class QFormLayout;
class CoeValueWidget;
class QToolBar;
class QMenu;

// Type definitions
typedef QPair<QString, QString> TStringPair;

// enumeration

// defines
#ifndef NEW
#define NEW "new"
#endif

#ifndef DELETE
#define DELETE "delete"
#endif

#ifndef UPDATE
#define UPDATE "update"
#endif

/*
 * This class is a gui interface for editing objects.
 */
class WMSGUI_API CwmsObjectEditor : public QWidget, public Ui::CwmsObjectEditorClass
{
    Q_OBJECT
private:
    QWidget* m_pqwContainter;
    CdmObjectAdaptor m_cCdmObjectAdaptor;
    bool m_bReadOnly;
    bool m_bShowEditButton;
    bool m_bHideSystemMembers;
    QStringList m_qstrlHiddenValues;
    QStringList m_qstrlReadOnlyValues;
    QStringList m_qstrlSortedMembers;
    QMap<QString, TStringPair> m_qmObjectRefs;
    QMap<QString, EdmStringDisplayType> m_qmDisplayType;
    QMap<QString, CdmQueryModel*> m_qmProxies;
    QList<QString> m_qlAddedMembers;
    QStringList m_qstrlFunctions;
    QMap<QPushButton*, QString> m_qmFunctionMapping;
    QString m_qstrCaptionValue;
    CdmObject* m_rpCdmPrintingTemplate;
    bool m_bOwnerMode;
    QToolBar* m_pToolBar;
    QMenu* m_pMenu;
    bool m_bIsObjEventEditor;
    QStringList m_qstrlEventClassMembers;
    bool m_bCheckEventMode;
    CoeValueWidget *m_pCoeValueWidget;
    bool m_bIsUpdateEvent;

public:
    CwmsObjectEditor( CdmObject* p_pCdmObject, QWidget* p_pqwParent = nullptr);
    virtual ~CwmsObjectEditor(  );
    void AddHiddenValue(  QString p_qstrKeyname );
    void AddReadOnlyValue(  QString p_qstrKeyname );
    void FillObjectEditor(  );
    CwmsObjectEditor( QWidget* p_pqwParent = nullptr);
    void SetReadOnly(  bool p_bReadOnly );
    void SetFormConfiguration(CdmObject* p_pObject);
    QList<qint64> GetSortMemberList(  );
    void SetSortedList(  QStringList p_qstrlistSortedMembers );
    void AddObjectRefData(QString p_qstrValue,
                          QString p_qstrObjectListKeyname,
                          QString p_qstrObjectValue);

    void SetDisplayType(QString p_qstrValue, EdmStringDisplayType p_EoeDisplayType);
    QList<qint64> GetSortedMemberListFromStringList();
    void SetCaptionValue(QString p_qstrValue);
    void SetShowEditButton(bool p_bShow);
    bool ShowEditButton();
    void SetSystemMembersHidden(bool p_bHidden);
    void setObjectName(QString p_qstrName);
    void SetObject(CdmObject* p_pCdmObject);
    CdmObject* GetObject();
    void AddProxy(QString p_qstrKeyname, CdmQueryModel *p_pCwmsProxy);
    void Initialize(CwmsApplicationModule p_cModule, CwmsRuntime* p_pRuntime);
    void GetParentWidgetAndLayout(CdmClassGroup* p_pGroup,
                                  QWidget*& p_rpWidget,
                                  QFormLayout*& p_rpLayout,
                                  QTabWidget*& p_rpTab);
    void DeactivateOwnerMode();

    void AddObjectRefData(QString p_qstrValue, QString p_qstrWql);
public slots:
    void SaveClickedSlot();
    void ResetClickedSlot();
    void MetaDataClickedSlot();

private:
    void FillMembers();
    void AddMemberInFormLayout(QString p_qstrKeyname, QWidget* p_qwParent, QFormLayout* p_qLayout);
    void CreateMemberUi(CdmValue* p_pCdmValue, QWidget* p_pqfParent, QFormLayout* p_qLayout);
    void FillGroups();
    bool IsReadOnly(  );
    void BuildWidget();
    bool FindInHiddenList(  CdmValue* p_pCdmValue );
    bool IsReadOnly(const CdmMember* p_pCdmMember);
    CdmValue* FindValueByMemberId( qint64 p_lMemberId );
    bool IsSystemMembersHidden();
    bool HasMembersWithoutGroup();
    void SetModule(CwmsApplicationModule p_cModule);
    void ConnectRuntime(CwmsRuntime* p_pRuntime, CwmsApplicationModule& p_cModule);
    void AddGroupsToListWidget();
    void BuildContainerWidget();
    int CountAdditionalTabs(CdmClassGroup* p_pCdmGroup);
    int CountAditionalTabsforNoneGroupMembers();
    bool NeedsMemberTab(CdmMember* p_pCdmMember);
    void GetClassMembers(QMap<qint64, CdmMember*>& p_rqmMembers);
    void GetClassMembers(QMap<qint64, CdmMember *> &p_rqmMembers, CdmClass *pClass);
    CdmMember* GetMemberById(qint64 p_lId);
    CdmMember* GetMemberById(qint64 p_lId, CdmClass *pClass);
    void AddMemberInTab(QString p_qstrKeyname, QTabWidget* p_qwParent);
    bool CreateTabMemberUi(CdmValue* p_pCdmValue, QWidget* p_pqfParent, QVBoxLayout* p_qLayout);
    void FillMembers(QList<CdmClassGroup *> &p_qlGroups);
    void AddMember(CdmMember* p_pCdmMember,
                   QWidget* p_pqMain,
                   QFormLayout* p_pLayout,
                   QTabWidget* p_pqTab);

    void CheckReadOnly(const CdmMember* p_pCdmMeber, CoeValueWidget* p_pWidget);
    void AddFunctions();
    void CheckEditable(const CdmMember *p_pCdmMeber, CoeValueWidget *p_pWidget);
    void GetGroupList(QListWidgetItem *pItem, QList<CdmClassGroup *> &p_rqlGroups);

private slots:
    void CaptionChangedSlot(const QString & p_qstrCaption);
    void JournalClickedSlot( );
    void PrintClickedSlot( );
    void GroupChangedSlot();
    void FunctionClickedSlot( );

};

#endif //

