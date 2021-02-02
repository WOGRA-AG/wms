
// System and QT Includes
#

// WMS Includes
#include "CdmObject.h"
#include "CdmClass.h"
#include "CdmMember.h"
#include "CdmLogging.h"
#include "CdmClassGroup.h"

// Own Includes
#include "CwqObjectEditorGenerator.h"



CwqObjectEditorGenerator::CwqObjectEditorGenerator(CdmObject* p_pObject)
    : m_pObject(p_pObject)
{
    m_qstrTextEditTemplate += "TextField {\n";
    m_qstrTextEditTemplate += "id: ${Keyname}EditField\n";
    m_qstrTextEditTemplate += "font.pointSize: 8\n";
    m_qstrTextEditTemplate += "Layout.fillWidth: true\n";
    m_qstrTextEditTemplate += "text: object.GetDisplayString(${Keyname})\n";

    m_qstrTextEditReadOnlyTemplate += "TextField {\n";
    m_qstrTextEditReadOnlyTemplate += "id: ${Keyname}EditField\n";
    m_qstrTextEditReadOnlyTemplate += "font.pointSize: 8\n";
    m_qstrTextEditReadOnlyTemplate += "Layout.fillWidth: true\n";
    m_qstrTextEditReadOnlyTemplate += "text: object.GetDisplayString(${Keyname})\n";
    m_qstrTextEditReadOnlyTemplate += "readOnly: true\n";

    m_qstrCheckboxEditTemplate += "CheckBox {\n";
    m_qstrCheckboxEditTemplate += "id: ${Keyname}EditField\n";
    m_qstrCheckboxEditTemplate += "Layout.fillWidth: true\n";
    m_qstrCheckboxEditTemplate += "checked: object.GetBool(\"${Keyname}\")\n";
    m_qstrCheckboxEditTemplate += "onCheckedChanged: { object.SetBool(\"${Keyname}\", checked); }\n";

    m_qstrLabelTemplate += "Text {\n";
    m_qstrLabelTemplate += "id: ${Keyname}Text\n";
    m_qstrLabelTemplate += "text: ${Caption}\n";
    m_qstrLabelTemplate += "font.pixelSize: 12\n";
}

CwqObjectEditorGenerator::~CwqObjectEditorGenerator()
{
}


QString CwqObjectEditorGenerator::GenerateEditor()
{
    QString qstrRet;

    if (m_pObject)
    {
        CdmClass* pClass = m_pObject->GetClass();

        if (CHKPTR(pClass))
        {
            QMap<int, CdmClassGroup*> qmGroups;
            pClass->GetGroups(qmGroups);

            QMap<int, CdmClassGroup*>::iterator qmIt = qmGroups.begin();
            QMap<int, CdmClassGroup*>::iterator qmItEnd = qmGroups.end();

            for (; qmIt != qmItEnd; ++qmIt)
            {
                CdmClassGroup* pGroup = qmIt.value();

                if (CHKPTR(pGroup))
                {
                    if (pGroup->CheckReadAccess())
                    {
                        QList<CdmMember*> qlMembers;
                        pGroup->GetMembers(qlMembers);

                        if (qlMembers.count() > 0)
                        {
                            m_qstrlGroups.append(pGroup->GetName());
                            QString qstrGroup = GenerateGroupContent(pGroup, qlMembers);
                            qstrRet += qstrGroup;
                        }
                    }
                }
            }
        }
    }

    return qstrRet;
}

QString CwqObjectEditorGenerator::GenerateGroupContent(CdmClassGroup* p_pGroup, QList<CdmMember*>& p_qlMembers)
{
    QString qstrContainer = "Component {\n";
    qstrContainer += "id: " + p_pGroup->GetName() + "\n\n";
    QString qstrMainData = GenerateMainDataArea(p_qlMembers);
    qstrContainer += qstrMainData;
    qstrContainer += "}\n\n";
    return qstrContainer;
}

QString CwqObjectEditorGenerator::GenerateMainDataArea(QList<CdmMember*>& p_qlMembers)
{
    QString qstrMainData;

    qstrMainData += "  GridLayout {\n";
    qstrMainData += "      id: mainData\n";
    qstrMainData += "      anchors.fill: parent\n";
    qstrMainData += "      anchors.margins: 3\n";
    qstrMainData += "      columns: 2\n\n";


    for (int iCounter = 0; iCounter < p_qlMembers.count(); ++iCounter)
    {
        CdmMember* pMember = p_qlMembers[iCounter];

        if (CHKPTR(pMember) && IsMemberMainData(pMember))
        {
            QString qstrLabel = CreateLabel(pMember);
            qstrMainData += qstrLabel;
            QString qstrData = CreateEditField(pMember);
            qstrMainData += qstrData;
        }
    }

    qstrMainData += "   }\n";
    return qstrMainData;
}

QString CwqObjectEditorGenerator::ReplaceTag(QString p_qstrTag, QString p_qstrData, QString p_qstrSource)
{
    return p_qstrSource.replace("${" + p_qstrTag + "}", p_qstrData);
}

QString CwqObjectEditorGenerator::CreateLabel(CdmMember* pMember)
{
    QString qstrLabel;

    qstrLabel = m_qstrLabelTemplate;
    qstrLabel = ReplaceTag("Keyname", pMember->GetKeyname(), qstrLabel);
    qstrLabel = ReplaceTag("Caption", pMember->GetCaption(), qstrLabel);
    qstrLabel += "}\n\n";

    return qstrLabel;
}

QString CwqObjectEditorGenerator::CreateEditField(CdmMember* pMember)
{
    QString qstrEditField;

    if (CHKPTR(pMember))
    {
        switch (pMember->GetValueType())
        {
        case eDmValueBool:
            qstrEditField = CreateBoolEditField(pMember);
            break;
        case eDmValueContainerRef:
            qstrEditField = CreateContainerRefEditField(pMember);
            break;
        case eDmValueCounter:
            qstrEditField = CreateCounterEditField(pMember);
            break;
        case eDmValueDate:
            qstrEditField = CreateDateEditField(pMember);
            break;
        case eDmValueDateTime:
            qstrEditField = CreateDateTimeEditField(pMember);
            break;
        case eDmValueDouble:
            qstrEditField = CreateDoubleEditField(pMember);
            break;
        case eDmValueEnum:
            qstrEditField = CreateEnumEditField(pMember);
            break;
        case eDmValueFloat:
            qstrEditField = CreateFloatEditField(pMember);
            break;
        case eDmValueFormula:
            qstrEditField = CreateFormulaEditField(pMember);
            break;
        case eDmValueInt:
            qstrEditField = CreateIntEditField(pMember);
            break;
        case eDmValueLong:
            qstrEditField = CreateLongEditField(pMember);
            break;
        case eDmValueObjectRef:
            qstrEditField = CreateObjectRefEditField(pMember);
            break;
        case eDmValueString:
            qstrEditField = CreateStringEditField(pMember);
            break;
        case eDmValueTime:
            qstrEditField = CreateTimeEditField(pMember);
            break;
        case eDmValueUser:
            qstrEditField = CreateUserEditField(pMember);
            break;
        case eDmValueUserGroup:
            qstrEditField = CreateUserGroupEditField(pMember);
            break;
        default:
            ERR("Wrong Type");
        }
    }

    return qstrEditField;
}

QString CwqObjectEditorGenerator::CreateBoolEditField(CdmMember* p_pMember)
{
    QString qstrEditField = m_qstrCheckboxEditTemplate;
    qstrEditField = ReplaceTag("Keyname", p_pMember->GetKeyname(), qstrEditField);
    qstrEditField += "}\n\n";
    return qstrEditField;
}

QString CwqObjectEditorGenerator::CreateContainerRefEditField(CdmMember* p_pMember)
{
    QString qstrEditField;
    Q_UNUSED(p_pMember);

    return qstrEditField;
}

QString CwqObjectEditorGenerator::CreateCounterEditField(CdmMember* p_pMember)
{
    QString qstrEditField = m_qstrTextEditReadOnlyTemplate;
    qstrEditField = ReplaceTag("Keyname", p_pMember->GetKeyname(), qstrEditField);
    qstrEditField += "}\n\n";
    return qstrEditField;
}

QString CwqObjectEditorGenerator::CreateDateEditField(CdmMember* p_pMember)
{
    QString qstrEditField;

    qstrEditField += "WmsDateEdit {\n";
    qstrEditField += "id: ${Keyname}EditField\n";
    qstrEditField += "font.pointSize: 8\n";
    qstrEditField += "Layout.fillWidth: true\n";
    qstrEditField += "onDateChanged: { object.SetDate(" + p_pMember->GetKeyname() + ", getDate()); }\n";
    qstrEditField += "onCompleted: {\n";
    qstrEditField += "   setDate(object.GetDate(\"${Keyname}\"));\n";
    qstrEditField += "}\n";
    qstrEditField += "}\n\n";

    qstrEditField = ReplaceTag("Keyname", p_pMember->GetKeyname(), qstrEditField);
    return qstrEditField;
}

QString CwqObjectEditorGenerator::CreateDateTimeEditField(CdmMember* p_pMember)
{
    QString qstrEditField;

    qstrEditField += "WmsDateTimeEdit {\n";
    qstrEditField += "id: ${Keyname}EditField\n";
    qstrEditField += "font.pointSize: 8\n";
    qstrEditField += "Layout.fillWidth: true\n";
    qstrEditField += "onDateTimeChanged: { object.SetDateTime(" + p_pMember->GetKeyname() + ", getDateTime()); }\n";
    qstrEditField += "onCompleted: {\n";
    qstrEditField += "   setDateTime(object.GetDateTime(\"${Keyname}\"));\n";
    qstrEditField += "}\n";
    qstrEditField += "}\n\n";

    qstrEditField = ReplaceTag("Keyname", p_pMember->GetKeyname(), qstrEditField);
    return qstrEditField;
}

QString CwqObjectEditorGenerator::CreateDoubleEditField(CdmMember* p_pMember)
{
    QString qstrEditField = m_qstrTextEditTemplate;
    qstrEditField = ReplaceTag("Keyname", p_pMember->GetKeyname(), qstrEditField);
    qstrEditField += "}\n\n";
    return qstrEditField;
}

QString CwqObjectEditorGenerator::CreateEnumEditField(CdmMember* p_pMember)
{
    QString qstrEditField;
    QStringList qstrlSelection = p_pMember->GetSelectionList();
    QString qstrSelection = "[ ";

    for (int iCounter = 0; iCounter < qstrlSelection.count(); ++iCounter)
    {
        qstrSelection += "\"" + qstrlSelection[iCounter] + "\"";

        if (iCounter < qstrlSelection.count() - 1)
        {
            qstrSelection +=", ";
        }
    }

    qstrSelection += " ]";

    qstrEditField += "ComboBox {\n";
    qstrEditField += "    id: ${Keyname}EditField\n";
    qstrEditField += "    model: " + qstrSelection + "\n";
    qstrEditField += "    currentIndex: object.GetInt(${Keyname})\n";
    qstrEditField += "    onCurrentIndexChanged: {\n";
    qstrEditField += "       object.SetInt(${Keyname}, currentIndex);\n";
    qstrEditField += "    }\n";
    qstrEditField += "}\n\n";

    qstrEditField = ReplaceTag("Keyname", p_pMember->GetKeyname(), qstrEditField);
    return qstrEditField;
}

QString CwqObjectEditorGenerator::CreateFloatEditField(CdmMember* p_pMember)
{
    QString qstrEditField = m_qstrTextEditTemplate;
    qstrEditField = ReplaceTag("Keyname", p_pMember->GetKeyname(), qstrEditField);
    qstrEditField += "}\n\n";
    return qstrEditField;
}

QString CwqObjectEditorGenerator::CreateFormulaEditField(CdmMember* p_pMember)
{
    QString qstrEditField = m_qstrTextEditTemplate;
    qstrEditField = ReplaceTag("Keyname", p_pMember->GetKeyname(), qstrEditField);
    qstrEditField += "}\n\n";
    return qstrEditField;
}

QString CwqObjectEditorGenerator::CreateIntEditField(CdmMember* p_pMember)
{
    QString qstrEditField = m_qstrTextEditTemplate;
    qstrEditField = ReplaceTag("Keyname", p_pMember->GetKeyname(), qstrEditField);
    qstrEditField += "}\n\n";
    return qstrEditField;
}

QString CwqObjectEditorGenerator::CreateLongEditField(CdmMember* p_pMember)
{
    QString qstrEditField = m_qstrTextEditTemplate;
    qstrEditField = ReplaceTag("Keyname", p_pMember->GetKeyname(), qstrEditField);
    qstrEditField += "}\n\n";
    return qstrEditField;
}

QString CwqObjectEditorGenerator::CreateObjectRefEditField(CdmMember* p_pMember)
{
    QString qstrEditField;
    Q_UNUSED(p_pMember);

    return qstrEditField;
}

QString CwqObjectEditorGenerator::CreateStringEditField(CdmMember* p_pMember)
{
    QString qstrEditField = m_qstrTextEditTemplate;
    qstrEditField = ReplaceTag("Keyname", p_pMember->GetKeyname(), qstrEditField);
    qstrEditField += "onTextChanged: { object.SetString(" + p_pMember->GetKeyname() + ", text); }\n";
    qstrEditField += "}\n\n";
    return qstrEditField;
}

QString CwqObjectEditorGenerator::CreateTimeEditField(CdmMember* p_pMember)
{
    QString qstrEditField;

    qstrEditField += "WmsTimeEdit {\n";
    qstrEditField += "id: ${Keyname}EditField\n";
    qstrEditField += "font.pointSize: 8\n";
    qstrEditField += "Layout.fillWidth: true\n";
    qstrEditField += "onTimeChanged: { object.SetTime(" + p_pMember->GetKeyname() + ", getTime()); }\n";
    qstrEditField += "onCompleted: {\n";
    qstrEditField += "   setTime(object.GetTime(\"${Keyname}\"));\n";
    qstrEditField += "}\n";
    qstrEditField += "}\n";

    qstrEditField = ReplaceTag("Keyname", p_pMember->GetKeyname(), qstrEditField);
    return qstrEditField;
}

QString CwqObjectEditorGenerator::CreateUserEditField(CdmMember* p_pMember)
{
    QString qstrEditField;
    Q_UNUSED(p_pMember);

    return qstrEditField;
}

QString CwqObjectEditorGenerator::CreateUserGroupEditField(CdmMember* p_pMember)
{
    QString qstrEditField;
    Q_UNUSED(p_pMember);

    return qstrEditField;
}

bool CwqObjectEditorGenerator::IsMemberMainData(CdmMember* pMember)
{
    bool bRet = true;

    if (CHKPTR(pMember))
    {
        switch (pMember->GetValueType())
        {
        case eDmValueListDouble:
        case eDmValueListInt:
        case eDmValueListObjects:
        case eDmValueListString:
        case eDmValueDictIntDouble:
        case eDmValueDictIntInt:
        case eDmValueDictIntString:
        case eDmValueDictStringDouble:
        case eDmValueDictStringInt:
        case eDmValueDictStringString:
        case eDmValueCharacterDocument:
            bRet = false;
            break;
        case eDmValueContainerRef:
            if (pMember->IsOwner())
            {
                bRet = false;
            }
            break;
        default:
            bRet = true;
        }
    }

    return bRet;
}


QMap<QString, QObject *> CwqObjectEditorGenerator::GetBindings() const
{
    return m_qmBindings;
}
