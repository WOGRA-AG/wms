

// System and QT Includes
#include <QtQml>
#include <QFile>
#include <QCoreApplication>
#include <QDir>
#include <QDebug>
#include <QTextStream>
#include <QQuickWindow>


// WMS Manager Includes
#include "CdmObject.h"
#include "CsaObject.h"
#include "CsaValue.h"
#include "CdmValue.h"
#include "CdmObjectContainer.h"
#include "CdmClass.h"
#include "CdmClassGroup.h"
#include "CdmLogging.h"

// Own Includes
#include "CwmsQmlApplicationController.h"
#include "CwqObjectEditorGenerator.h"
#include "CwqQmlObjectViewer.h"
#include "CwqObjectEditorController.h"


CwqObjectEditorController::CwqObjectEditorController(QObject *parent)
    : QObject(parent),
      m_Adaptor(nullptr),
      m_bNew(false)
{
}


CwqObjectEditorController::CwqObjectEditorController(CdmObject* p_pObject, QObject *parent)
    : QObject(parent),
      m_Adaptor(p_pObject)
{
}

CwqObjectEditorController::~CwqObjectEditorController()
{

}

void CwqObjectEditorController::setObject(CsaObject* p_pObject, bool p_bNew)
{
    m_bNew = p_bNew;

    if (p_pObject)
    {
        m_Adaptor.SetObject(p_pObject->getInternals());
    }
    else
    {
        WARNING ("Object was nullptr");
        m_Adaptor.SetObject(nullptr);
    }
}

CsaObject* CwqObjectEditorController::getObjectW()
{
    CdmObject* pObject = nullptr;
    CdmObjectContainer* pContainer = m_Adaptor.GetObjectContainer();

    if (CHKPTR(pContainer))
    {
        pObject = pContainer->FindObjectById(m_Adaptor.GetObjectId());
    }

    return CwmsQmlApplicationController::getController()->convertObject(pObject);;
}

QStringList CwqObjectEditorController::getGroups()
{
    QStringList qstrlGroups;
    if (CHKPTR(getObjectW()))
    {
        CdmObject* pObject = getObjectW()->getInternals();

        if (CHKPTR(pObject))
        {
            CdmClass* pClass = pObject->GetClass();

            if (CHKPTR(pClass))
            {
                QMap<int, CdmClassGroup*> qmGroups;
                pClass->GetGroups(qmGroups);

                QMap<int, CdmClassGroup*>::iterator qmIt = qmGroups.begin();
                QMap<int, CdmClassGroup*>::iterator qmItEnd = qmGroups.end();

                for (; qmIt != qmItEnd; ++qmIt)
                {
                    CdmClassGroup* pGroup = qmIt.value();

                    if (CHKPTR(pGroup) && pGroup->CheckReadAccess())
                    {
                        qstrlGroups.append(pGroup->GetName());
                    }
                }
            }
        }
    }

    return qstrlGroups;
}

CdmClassGroup* CwqObjectEditorController::getGroupByName(QString p_qstrName)
{
    CdmClassGroup* pGroup = nullptr;
    if (CHKPTR(getObjectW()))
    {
        CdmObject* pObject = getObjectW()->getInternals();

        if (CHKPTR(pObject))
        {
            CdmClass* pClass = pObject->GetClass();

            if (CHKPTR(pClass))
            {
                pGroup = pClass->FindGroupByName(p_qstrName);
            }
        }
    }

    return pGroup;
}

int CwqObjectEditorController::getGroupCount()
{
    int iCount = 0;

    if (CHKPTR(getObjectW()))
    {
        CdmObject* pObject = getObjectW()->getInternals();

        if (CHKPTR(pObject))
        {
            CdmClass* pClass = pObject->GetClass();

            if (CHKPTR(pClass))
            {
                QMap<int, CdmClassGroup*> qmGroups;
                pClass->GetGroups(qmGroups);

                QMap<int, CdmClassGroup*>::iterator qmIt = qmGroups.begin();
                QMap<int, CdmClassGroup*>::iterator qmItEnd = qmGroups.end();

                for (; qmIt != qmItEnd; ++qmIt)
                {
                    CdmClassGroup* pGroup = qmIt.value();

                    if (CHKPTR(pGroup) && pGroup->CheckReadAccess())
                    {
                        ++iCount;
                    }
                }
            }
        }
    }

    return iCount;
}

QList<QObject*> CwqObjectEditorController::getValuesOfGroup(QString p_qstrGroupName, bool p_bComplex)
{
    QList<QObject*> qlValues;

    if (p_qstrGroupName.isEmpty())
    {
        qlValues = getValues(p_bComplex);
    }
    else
    {
        CdmClassGroup* pGroup = getGroupByName(p_qstrGroupName);
        if (CHKPTR(getObjectW()))
        {
            CdmObject* pObject = getObjectW()->getInternals();
            if (CHKPTR(pObject) && CHKPTR(pGroup) && pGroup->CheckReadAccess())
            {
                QList<CdmMember*> qlMembers;
                pGroup->GetMembers(qlMembers);

                for (int iPos = 0; iPos < qlMembers.count(); ++iPos)
                {
                    CdmMember* pMember = qlMembers[iPos];

                    if (CHKPTR(pMember))
                    {
                        if (pMember->CheckReadAccess())
                        {
                            CdmValue* pValue = pObject->GetValue(pMember->GetKeyname());

                            if (CHKPTR(pValue) && (!isComplexUiType(pValue->GetValueType()) || p_bComplex))
                            {
                                CsaFactory* pFactory = CwmsQmlApplicationController::getController()->getFactory();
                                qlValues.append(pFactory->createScriptObject(pValue));
                            }
                        }
                    }
                }
            }
        }
    }

    return qlValues;
}

int CwqObjectEditorController::countComplexTypesOfGroup(QString p_qstrGroupName)
{
    int iComplexTypes = 0;

    if (p_qstrGroupName.isEmpty())
    {
        iComplexTypes = countComplexTypesOfObject();
    }
    else
    {
        QList<QObject*> qlValues = getValuesOfGroup(p_qstrGroupName, true);

        for (int iPos = 0; iPos < qlValues.count(); ++iPos)
        {
            CsaValue* pValue = static_cast<CsaValue*>(qlValues[iPos]);

            if (CHKPTR(pValue))
            {
                if (isComplexUiType(pValue))
                {
                    ++iComplexTypes;
                }
            }
        }
    }

    return iComplexTypes;
}

bool CwqObjectEditorController::needsMultiPageView(QString p_qstrGroupName)
{
    return (countPagesOfGroup(p_qstrGroupName) > 1);
}

int CwqObjectEditorController::countPagesOfGroup(QString p_qstrGroupName)
{
    int iPages = 0;
    bool simpleTypesFound = false;
    QList<QObject*> qlValues = getValuesOfGroup(p_qstrGroupName, true);

    for (int iPos = 0; iPos < qlValues.count(); ++iPos)
    {
        CsaValue* pValue = static_cast<CsaValue*>(qlValues[iPos]);

        if (CHKPTR(pValue))
        {
            if (isComplexUiType(pValue))
            {
                ++iPages;
            }
            else if (!simpleTypesFound)
            {
                ++iPages;
                simpleTypesFound = true;
            }
        }
    }

    return iPages;
}

bool CwqObjectEditorController::hasSimpleTypes(QString p_qstrGroupName)
{
    bool bRet = false;
    QList<QObject*> qlValues = getValuesOfGroup(p_qstrGroupName, true);

    for (int iPos = 0; iPos < qlValues.count(); ++iPos)
    {
        CsaValue* pValue = static_cast<CsaValue*>(qlValues[iPos]);

        if (CHKPTR(pValue))
        {
            if (!isComplexUiType(pValue))
            {
                bRet = true;
                break;
            }
        }
    }

    return bRet;
}

int CwqObjectEditorController::countComplexTypesOfObject()
{
    int iComplexTypes = 0;
    QList<QObject*> qlValues = getValues(true);

    for (int iPos = 0; iPos < qlValues.count(); ++iPos)
    {
        CsaValue* pValue = static_cast<CsaValue*>(qlValues[iPos]);

        if (CHKPTR(pValue))
        {
            if (isComplexUiType(pValue))
            {
                ++iComplexTypes;
            }
        }
    }

    return iComplexTypes;
}

QList<QObject*> CwqObjectEditorController::getValues(bool p_bComplex)
{
    QList<QObject*> qlValues;
    if (CHKPTR(getObjectW()))
    {
        CdmObject* pObject = getObjectW()->getInternals();
        CdmClass* pClass = pObject->GetClass();

        if (CHKPTR(pObject) && CHKPTR(pClass))
        {
            QVector<QString> qvMemberSequence = pClass->GetMemberSequence();

            for (int iPos = 0; iPos < qvMemberSequence.count(); ++iPos)
            {
                QString qstrMemberKeyname = qvMemberSequence[iPos];
                const CdmMember* pMember = pClass->FindMember(qstrMemberKeyname);

                if (CHKPTR(pMember))
                {
                    if (pMember->CheckReadAccess())
                    {
                        CdmValue* pValue = pObject->GetValue(pMember->GetKeyname());

                        if (CHKPTR(pValue) && (!isComplexUiType(pValue->GetValueType()) || p_bComplex))
                        {
                            CsaFactory* pFactory = CwmsQmlApplicationController::getController()->getFactory();
                            qlValues.append(pFactory->createScriptObject(pValue));
                        }
                    }
                }
            }
        }
    }

    return qlValues;
}

bool CwqObjectEditorController::isComplexUiType(CsaValue* p_pValue)
{
    bool bRet = false;

    if (CHKPTR(p_pValue))
    {
        bRet = isComplexUiType(p_pValue->getType());
    }


    return bRet;
}

bool CwqObjectEditorController::isComplexUiType(EdmValueType p_eType)
{
    bool bRet = false;

    switch (p_eType)
    {
    case eDmValueBool:
    case eDmValueInt:
    case eDmValueCounter:
    case eDmValueLong:
    case eDmValueFloat:
    case eDmValueDouble:
    case eDmValueString:
    case eDmValueFormula:
    case eDmValueDate:
    case eDmValueTime:
    case eDmValueDateTime:
    case eDmValueBinaryDocument:
    case eDmValueEnum:
    case eDmValueUser:
    case eDmValueUserGroup:
        bRet = false;
        break;
    case eDmValueObjectRef:
    case eDmValueContainerRef:
    case eDmValueCharacterDocument:
    case eDmValueDictIntDouble:
    case eDmValueDictIntString:
    case eDmValueDictIntInt:
    case eDmValueDictStringDouble:
    case eDmValueDictStringInt:
    case eDmValueDictStringString:
    case eDmValueListDouble:
    case eDmValueListInt:
    case eDmValueListString:
    case eDmValueListObjects:
        bRet = true;
        break;
    default:
        ERR( "Value not implemented" );
        bRet = false;
        break;
    }



    return bRet;
}


QObject* CwqObjectEditorController::getComplexValueAt(QString p_qstrGroupName, int p_iPageNumber)
{
    CsaValue* pValue = nullptr;

    QList<QObject*> qlValues = getValuesOfGroup(p_qstrGroupName, true);
    int iPageCount = 1;

    if (!hasSimpleTypes(p_qstrGroupName))
    {
        p_iPageNumber++;
    }


    for (int iPos = 0; iPos < qlValues.count(); ++iPos)
    {
        CsaValue* pValueCurrent = static_cast<CsaValue*>(qlValues[iPos]);

        if (CHKPTR(pValueCurrent))
        {
            if (isComplexUiType(pValueCurrent))
            {
                if (iPageCount == p_iPageNumber)
                {
                    pValue = pValueCurrent;
                    break;
                }

                ++iPageCount;
            }
        }
    }


    return pValue;
}

QString CwqObjectEditorController::getQmlElementByValue(CsaValue* p_pValue)
{
    QString qstrElementName;

    if (CHKPTR(p_pValue))
    {
        switch (p_pValue->getType())
        {
        case eDmValueBool:
            qstrElementName = "WmsObjectEditorBool.qml";
            break;
        case eDmValueInt:
        case eDmValueCounter:
        case eDmValueLong:
        case eDmValueFloat:
        case eDmValueDouble:
        case eDmValueString:
        case eDmValueFormula:
            qstrElementName = "WmsObjectEditorVariant.qml";
            break;
        case eDmValueDate:
        case eDmValueTime:
        case eDmValueDateTime:
            qstrElementName = "WmsObjectEditorDateTime.qml";
            break;
        case eDmValueObjectRef:
            qstrElementName = "";
            ERR("TODO");
            break;
        case eDmValueContainerRef:
            qstrElementName = "";
            ERR("TODO");
            break;
        case eDmValueBinaryDocument:
            qstrElementName = "WmsObjectEditorBinDoc.qml";
            break;
        case eDmValueCharacterDocument:
            qstrElementName = "WmsObjectEditorCharDoc.qml";
            break;
        case eDmValueDictIntDouble:
        case eDmValueDictIntString:
        case eDmValueDictIntInt:
        case eDmValueDictStringDouble:
        case eDmValueDictStringInt:
        case eDmValueDictStringString:
            qstrElementName = "WmsObjectEditorMap.qml";
            break;
        case eDmValueListDouble:
        case eDmValueListInt:
        case eDmValueListString:
        case eDmValueListObjects:
            qstrElementName = "WmsObjectEditorList.qml";
            break;
        case eDmValueEnum:
        case eDmValueUser:
        case eDmValueUserGroup:
            qstrElementName = "WmsObjectEditorSelection.qml";
            break;
        default:
            ERR( "Value not implemented" );
            break;
        }
    }

    return qstrElementName;
}

void CwqObjectEditorController::okClicked()
{
    m_Adaptor.CommitObject();
}

void CwqObjectEditorController::cancelClicked()
{
    if (CHKPTR(getObjectW()))
    {
        CdmObject* pObject = getObjectW()->getInternals();

        if (CHKPTR(pObject))
        {
            if (m_bNew)
            {
                pObject->SetDeleted();
                pObject->Commit();
            }
            else
            {
                pObject->Refresh();
            }
        }
    }
}

void CwqObjectEditorController::registerToQml()
{
    qmlRegisterType<CwqObjectEditorController>("com.wogra.wmsqml", 1, 0, "WmsObjectEditorController");
}
