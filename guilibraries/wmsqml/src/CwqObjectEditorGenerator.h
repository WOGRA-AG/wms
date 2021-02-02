#ifndef CWQOBJECTEDITORGENERATOR_H
#define CWQOBJECTEDITORGENERATOR_H

// System and QT Includes
#include <QObject>
#include <QMap>
#include <QString>

// own Includes


// forwards
class CdmObject;
class CdmClassGroup;

class CwqObjectEditorGenerator
{
private:
    CdmObject* m_pObject;
    QMap<QString, QObject*> m_qmBindings;
    QStringList m_qstrlGroups;
    QString m_qstrTextEditTemplate;
    QString m_qstrTextEditReadOnlyTemplate;
    QString m_qstrLabelTemplate;
    QString m_qstrCheckboxEditTemplate;

    QString GenerateGroupContent(CdmClassGroup *p_pGroup, QList<CdmMember*>& p_qlMembers);
    QString GenerateMainDataArea(QList<CdmMember *> &p_qlMembers);
    bool IsMemberMainData(CdmMember *pMember);
    QString CreateLabel(CdmMember *pMember);
    QString CreateEditField(CdmMember *pMember);
    QString CreateUserGroupEditField(CdmMember *p_pMember);
    QString CreateUserEditField(CdmMember *p_pMember);
    QString CreateTimeEditField(CdmMember *p_pMember);
    QString CreateStringEditField(CdmMember *p_pMember);
    QString CreateObjectRefEditField(CdmMember *p_pMember);
    QString CreateLongEditField(CdmMember *p_pMember);
    QString CreateIntEditField(CdmMember *p_pMember);
    QString CreateFormulaEditField(CdmMember *p_pMember);
    QString CreateFloatEditField(CdmMember *p_pMember);
    QString CreateEnumEditField(CdmMember *p_pMember);
    QString CreateDoubleEditField(CdmMember *p_pMember);
    QString CreateDateTimeEditField(CdmMember *p_pMember);
    QString CreateDateEditField(CdmMember *p_pMember);
    QString CreateCounterEditField(CdmMember *p_pMember);
    QString CreateContainerRefEditField(CdmMember *p_pMember);
    QString CreateBoolEditField(CdmMember *p_pMember);
    QString ReplaceTag(QString p_qstrTag, QString p_qstrData, QString p_qstrSource);
public:
    CwqObjectEditorGenerator(CdmObject* p_pObject);
    ~CwqObjectEditorGenerator();
    QString GenerateEditor();
    QMap<QString, QObject *> GetBindings() const;

};

#endif // CWQOBJECTEDITORGENERATOR_H
