#ifndef CWMSOBJECTLISTEDITORBASE_H
#define CWMSOBJECTLISTEDITORBASE_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes
#include <QString>
#include <QPair>
#include <QStringList>

// Own Includes
#include "wmsgui.h"


// forwards
class CdmObjectContainer;
class CwmsguiValidator;
class CdmObject;
class QTreeView;
class CwmsguiObjectEditorIf;
class CdmQueryModel;

typedef QPair<QString,QString> TStringPair;

// Enumerations

/* 
 * This class implements the interfaceclass for
 * objectlisteditorwidget and objectlisteditor
 */
class WMSGUI_API CwmsContainerEditorBase
{
private:
    QStringList m_qstrlReadOnlyValues;
    QStringList m_qstrlHiddenValues;
    QStringList m_qstrlSortedList;
    bool m_bShowEditButton;
    QString m_qstrCaptionValue;
    QMap<QString, TStringPair> m_qmObjectRefData;

public:
    CwmsContainerEditorBase( );
    virtual void AddColumn(QString p_qstrColumn)= 0;
    virtual void AddReadOnlyValue(QString p_qstrValue);
    virtual void SetContainer(CdmObjectContainer* p_pContainer)= 0;
    virtual void SetModel(CdmQueryModel* p_pModel) = 0;
    virtual void SetShowEditButton(bool p_bShowEditButton);
    virtual void AddHiddenValue(QString p_qstrValue);
    virtual void SetCaptionValue(QString p_qstrValue);
    virtual void FillDialog()= 0;
    virtual void SetSortedList(QStringList p_qstrlSorting);
    virtual void SetDefaultValueForNewObject(QString p_qstrValueName,
                                             QString p_qstrValue,
                                             QString p_qstrValue2)= 0;
    virtual void AddObjectRefData(QString p_qstrMember,
                                  QString p_qstrRef,
                                  QString p_qstrDisplayCaption);


protected:
    bool OpenEditor(CdmObject* p_pCdmObject);

private:
    void FillReadOnlyMembers(CwmsguiObjectEditorIf* p_pCoeEditor);
    void FillHiddenMembers(CwmsguiObjectEditorIf* p_pCoeEditor);
    void FillObjectRefData(CwmsguiObjectEditorIf* p_pCoeEditor);
};

#endif //
