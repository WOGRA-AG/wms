/******************************************************************************
 ** WOGRA technologies Modul Information
 ** Modulename: CwmsSearchWidgetIf.h
 ** Started Implementation: 2008/09/06
 ** Description:
 **
 ** This class implements the simple search gui for searching the wms
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 **(C) copyright by WOGRA technologies All rights reserved
 *****************************************************************************/

#ifndef CWMSSEARCHWIDGETIF_H
#define CWMSSEARCHWIDGETIF_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes
#include <QWidget>
#include <QList>
#include <QList>
#include <QPointer>
#include <QStringList>
#include <QString>

// WMS Manager Includes
#include "CdmQuery.h"
#include "CdmQueryElement.h"

// Own Includes
#include "wmsgui.h"
#include "ui_CwmsSearchWidgetIf.h"


// Forwards
class CdmObjectContainer;
class CdmQuery;
class CoeValueWidget;
class QWidget;

// Enumerations

// namespaces

/* 
 * This class implements the simple search gui for searching the wms
 */
class WMSGUI_API CwmsSearchWidgetIf : public QWidget, public Ui::CwmsSearchWidgetIfClass
{
    Q_OBJECT

private:
    QStringList m_qstrlSearchMembers;
    QStringList m_qstrlHiddenSearchMembers;
    QPointer<CdmClass> m_rpClass = {};
    QPointer<CdmObjectContainer> m_rpContainer = {};
    CdmQuery m_cCdmQuery;
    QWidget* m_pqwContent = {};
    QList<CoeValueWidget*> m_qlValueWidgets;
    QMap<QString, QString> m_qmSearchDefaultValues;
    QMap<QString, QString> m_qmSearchAliases;

public:
    CwmsSearchWidgetIf( QWidget* p_pqwParent = NULL);
    virtual ~CwmsSearchWidgetIf( );
    CdmObjectContainer* GetObjectList();
    void SetObjectList(CdmObjectContainer* p_pContainer);
    CdmClass *GetClass();
    void SetClass(CdmClass *p_pClass);
    void AddSearchMember(QString p_qstrKeyname, QString p_qstrAlias = "");
    void FillWidget();
    void GetDisplayList(QList<qint64>& p_rqvlResults);
    void Clear();
    void AddSearchDefaultValue(QString p_qstrKeyname, QString p_qstrDefaultValue);
    void SetSearchMemberAsHidden(QString p_qstrKeyname);
    void SetSearchCaption(QString p_qstrCaption);
    void SetSearchButtonVisibility(bool p_bVisiible);
    void CreateQuery(CdmQuery& p_rCdmQuery);
    void SetAndSearch();
    void SetOrSearch();

private:
    void CreateQuery();
    void AddAllSearchMembers();
    bool IsMemberSearchable(CdmMember* p_pCdmMember);
    void FillDefaultMembers();


private slots:
    void SearchClickedSlot( );

signals:
    void SearchSignal( );
};

#endif // // CWMSSEARCHWIDGETIF_H
