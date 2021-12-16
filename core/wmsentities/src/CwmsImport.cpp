//2008/10/21

// System and QT Includes
#include <QStringList>
#include <QApplication>
#include <CdmExecutor.h>

// Own Includes
#include "CwmsImport.h"
#include "CwmsImportSettings.h"
#include "CwmsImportSettingsColumn.h"
#include "CwmsImportParser.h"

// WMS Includes
#include "CdmMember.h"
#include "CdmValue.h"
#include "CdmDataProvider.h"
#include "CdmSessionManager.h"
#include "CdmObject.h"
#include "CdmClass.h"
#include "CdmObjectContainer.h"
#include "CdmContainerManager.h"
#include "CdmScheme.h"
#include "CdmLogging.h"

CwmsImport::CwmsImport()
    : m_pParser(nullptr),
      m_bDisplayProgress(true)
{
}

CwmsImport::~CwmsImport()
{
    DELPTR(m_pParser);
}

void CwmsImport::SetDipslayProgress(bool p_bDisplay)
{
    m_bDisplayProgress = p_bDisplay;
}

bool CwmsImport::GetDisplayProgress()
{
    return m_bDisplayProgress;
}

CwmsImportParser* CwmsImport::CreateParser(QString p_qstrSettingsFile, CdmObjectContainer* p_pList)
{
    DELPTR(m_pParser);
    m_cCwmsImportSettings.LoadSettings(p_qstrSettingsFile, p_pList->GetClassId());
    m_pParser = CwmsImportParser::ParserFactory(&m_cCwmsImportSettings);
    return m_pParser;
}

CwmsImportParser* CwmsImport::CreateParser(CwmsImportSettings p_cwmsImportSettings)
{
    DELPTR(m_pParser);
    m_cCwmsImportSettings = p_cwmsImportSettings;
    m_pParser = CwmsImportParser::ParserFactory(&m_cCwmsImportSettings);
    return m_pParser;
}

void CwmsImport::StartImport(QString p_qstrSettingsFile, CdmObjectContainer* p_pList)
{
    if (CHKPTR(p_pList))
    {
        if (!m_pParser)
        {
            CreateParser(p_qstrSettingsFile, p_pList);
            m_cCwmsImportSettings.SetContainer(p_pList);
        }

        StartImport();
    }
}

void CwmsImport::StartImport(CdmObjectContainer* p_pContainer,
                             CwmsImportSettings p_cwmsImportSettings)
{
    if (CHKPTR(p_pContainer))
    {
        m_cCwmsImportSettings = p_cwmsImportSettings;
        m_cCwmsImportSettings.SetContainer(p_pContainer);

        if (!m_pParser)
        {
            m_pParser = CreateParser(m_cCwmsImportSettings);
        }

        StartImport();
    }
}

void CwmsImport::ModifyContainerContentDependentOnMode()
{
    if (m_cCwmsImportSettings.GetImportMode() == eWmsImportModeOverwrite)
    {
        auto pContainer = m_cCwmsImportSettings.GetContainer();

        if (CHKPTR(pContainer))
        {
            pContainer->SetImportMode(false);
            pContainer->DeleteAllObjects();
            pContainer->Commit();
            pContainer->SetImportMode(true);
        }
    }
}

void CwmsImport::StartImport()
{
    ModifyContainerContentDependentOnMode();

    if (m_pParser)
    {
        m_pParser->ParseFile(this);
    }
}

CwmsImportSettings& CwmsImport::GetSettings()
{
    return m_cCwmsImportSettings;
}

QString CwmsImport::GetImportMessages()
{
    return m_qstrImportMessages;
}

CdmObjectContainer* CwmsImport::GetContainer()
{
    CdmObjectContainer* pContainer = nullptr;
    CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

    if (CHKPTR(pCdmManager))
    {
        CdmScheme* pCdmDatabase = pCdmManager->FindSchemeById(m_cCwmsImportSettings.GetDatabaseId());

        if (CHKPTR(pCdmDatabase))
        {
            CdmContainerManager* pContainerManager = pCdmDatabase->GetContainerManager();

            if (CHKPTR(pContainerManager))
            {
                pContainer = pContainerManager->FindContainerById(m_cCwmsImportSettings.GetContainerId());

                if (CHKPTR(pContainer))
                {
                    pContainer->SetImportMode(true);
                }
            }
        }
    }

    return pContainer;
}

CdmObject* CwmsImport::GetObject(const QStringList& qstrlParseData)
{
    CdmObject* pCdmObject = nullptr;
    if (m_cCwmsImportSettings.GetImportMode() == eWmsImportModeOverwrite ||
            m_cCwmsImportSettings.GetImportMode() == eWmsImportModeAppend)
    {
        CdmObjectContainer* pContainer = GetContainer();

        if (CHKPTR(pContainer))
        {
            pCdmObject = pContainer->CreateNewObject();
        }

    }
    else if (m_cCwmsImportSettings.GetImportMode() == eWmsImportModeUpdate)
    {
        pCdmObject = ExecuteObjectQuery(qstrlParseData);
    }
    else
    {
        ERR("Wrong Mode!!!");
        m_qstrImportMessages += "<p>" + qApp->tr("Import Modus ist Unbekannt.") + "</p>";
    }

    return pCdmObject;
}

CdmObject* CwmsImport::ExecuteObjectQuery(const QStringList& p_rqstrlParseData)
{
    CdmObject* pCdmObject = nullptr;
    CdmObjectContainer* pContainer = GetContainer();

    if (CHKPTR(pContainer))
    {
        CdmQuery cCdmQuery;
        cCdmQuery.SetContainer(pContainer);
        CreateQuery(cCdmQuery, p_rqstrlParseData);

        if (cCdmQuery.Execute() > 0)
        {
            QList<qint64> qvlResults;
            qvlResults = cCdmQuery.GetResultList();

            if (qvlResults.count() > 0)
            {
                QList<qint64>::iterator qvlIt = qvlResults.begin();
                QList<qint64>::iterator qvlItEnd = qvlResults.end();

                for (; qvlIt != qvlItEnd; ++qvlIt)
                {
                    qint64 lId = (*qvlIt);

                    pCdmObject = pContainer->FindObjectById(lId);

                    if (pCdmObject)
                    {
                        break;
                    }
                }

                if (qvlResults.count() > 1)
                {
                    m_qstrImportMessages += "<p>" + qApp->tr("Mehr als einen Datensatz gefunden verwende den ersten.") + "</p>";
                }
            }
        }
    }

    return pCdmObject;
}

void CwmsImport::CreateQuery(CdmQuery& p_rCdmQuery, const QStringList& p_qstrlParseData)
{
    CdmObjectContainer* pContainer = GetContainer();

    if (CHKPTR(pContainer))
    {
        const CdmClass* pCdmClass = pContainer->GetClass();

        if (CHKPTR(pCdmClass))
        {
            QList<CwmsImportSettingsColumn*> qlColumns;
            m_cCwmsImportSettings.GetColumns(qlColumns);
            CdmQueryElement* pCdmQueryElementRoot = new CdmQueryElement(&p_rCdmQuery,
                                                                        eDmQueryElementTypeAnd);

            p_rCdmQuery.ResetQueryElement(pCdmQueryElementRoot);

            for (int iPos = 0; iPos < qlColumns.count(); ++iPos)
            {
                CwmsImportSettingsColumn* pColumn = qlColumns[iPos];

                if (CHKPTR(pColumn) && pColumn->IsUpdateCriteria())
                {
                    QString qstrValue = p_qstrlParseData[iPos];
                    const CdmMember* pCdmMember = pCdmClass->FindMember(pColumn->GetMember());

                    if (pCdmMember)
                    {
                        CdmQueryElement* pCdmQueryElement = new CdmQueryElement(&p_rCdmQuery,
                                                                                eDmQueryElementTypeCompare,
                                                                                eDmQueryCompareTypeEqual);

                        switch(pCdmMember->GetValueType())
                        {
                        case eDmValueBool:
                            if (qstrValue == "1" || qstrValue == "true")
                            {
                                pCdmQueryElement->SetComparisonValue(pColumn->GetMember(), true);
                            }
                            else
                            {
                                pCdmQueryElement->SetComparisonValue(pColumn->GetMember(), false);
                            }
                            break;
                        case eDmValueString:
                        case eDmValueCharacterDocument:
                            pCdmQueryElement->SetComparisonValue(pColumn->GetMember(), qstrValue);
                            break;
                        case eDmValueCounter:
                        case eDmValueInt:
                        case eDmValueLong:
                        case eDmValueContainerRef:
                        case eDmValueObjectRef:
                            pCdmQueryElement->SetComparisonValue(pColumn->GetMember(), qstrValue.toInt());
                            break;
                        case eDmValueDate:
                        {
                            QDate qdCompareDate = QDate::fromString(qstrValue);
                            pCdmQueryElement->SetComparisonValue(pColumn->GetMember(), qdCompareDate);
                        }

                            break;
                        case eDmValueDateTime:
                        {
                            QDateTime qdtCompareDate = QDateTime::fromString(qstrValue);
                            pCdmQueryElement->SetComparisonValue(pColumn->GetMember(), qdtCompareDate);
                        }

                            break;
                        case eDmValueDouble:
                        case eDmValueFloat:
                            pCdmQueryElement->SetComparisonValue(pColumn->GetMember(), (float)qstrValue.toDouble());
                            break;
                        case eDmValueTime:
                        {
                            QTime qtCompareDate = QTime::fromString(qstrValue);
                            pCdmQueryElement->SetComparisonValue(pColumn->GetMember(), qtCompareDate);
                        }

                            break;
                        default:
                            ERR("Unsupported Type");
                            m_qstrImportMessages += "<p>" + qApp->tr("Der Typ dieses Members wird nicht untersttzt: ") + pColumn->GetMember() + "</p>";
                        }

                        pCdmQueryElementRoot->AddChild(pCdmQueryElement);
                    }
                    else
                    {
                        m_qstrImportMessages += "<p>" + qApp->tr("Member wurde nicht gefunden: ") + pColumn->GetMember() + "</p>";
                    }
                }
            }
        }
    }
}

bool CwmsImport::ExecutePreprocessing(QStringList& p_qsrlParsedData)
{
    bool bRet = true;
    CdmClassMethod* pMethod = FindPostprocessorFunction();

    if (pMethod)
    {
        QVariantList qvlJsonArray = ConvertParsedDataToJsonArray(p_qsrlParsedData);
        QVariant qvResult = CdmExecutor::GetExecutor()->ExecuteFunction(pMethod, nullptr, qvlJsonArray);

        //todo convert qvResult to ParsedData;
        auto qstrResult = qvResult.toString();
        CwmsJson json;
        auto qvList = json.parse(qstrResult).toList();
        p_qsrlParsedData.clear();

        for (int iPos = 0; iPos < qvList.count(); ++iPos)
        {
            p_qsrlParsedData.append(qvList[iPos].toString());
        }
    }

    return bRet;
}

QVariantList CwmsImport::ConvertParsedDataToJsonArray(QStringList& p_qsrlParsedData)
{
    QVariantList qvlJsonArray;
    QString qstrJsonArray = "[";

    for (int iPos = 0; iPos < p_qsrlParsedData.count(); ++iPos)
    {
        if (iPos > 0)
        {
            qstrJsonArray += ", ";
        }

        qstrJsonArray += "\""+ p_qsrlParsedData[iPos] + "\"";
    }

    qstrJsonArray += "]";
    qvlJsonArray << qstrJsonArray;
    return qvlJsonArray;
}

bool CwmsImport::ExecutePostprocessing(CdmObject* p_pObject)
{
    bool bRet = true;

    CdmClassMethod* pMethod = FindPostprocessorFunction();

    if (pMethod)
    {
        QVariantList qList;
        QVariant qvResult = CdmExecutor::GetExecutor()->ExecuteFunction(pMethod, p_pObject, qList);
    }

    return bRet;
}

CdmClassMethod* CwmsImport::FindPreprocessorFunction()
{
    QString qstrFunction = m_cCwmsImportSettings.GetPreprocessorCall();

    if (qstrFunction.isEmpty())
    {
        return nullptr;
    }

    CdmClassMethod* pFunction = FindFunction(qstrFunction);

    if (pFunction)
    {
        if (CHKPTR(pFunction))
        {
           if (pFunction->IsStatic() && pFunction->GetParameterCount() == 1)
           {
               return pFunction;
           }
           else
           {
               if (!pFunction->IsStatic())
               {
                   MSG_CRIT("Ungültiger Preprocessor Function","Eine Preprecossorfunction muss statisch sein.");
               }

               if (pFunction->GetParameterCount() != 1)
               {
                   MSG_CRIT("Ungültiger Preprocessor Function","Eine Preprecossorfunction muss einen Parameter für das Array der Eingabedaten besitzen.");
               }
           }
        }
    }

    return nullptr;
}

CdmClassMethod* CwmsImport::FindPostprocessorFunction()
{
    QString qstrFunction = m_cCwmsImportSettings.GetPostprocessorCall();

    if (qstrFunction.isEmpty())
    {
        return nullptr;
    }

    CdmClassMethod* pFunction = FindFunction(qstrFunction);

    if (pFunction)
    {
        if (!pFunction->IsStatic() && pFunction->GetParameterCount() == 0)
        {
            if (GetContainer()->GetClass() == pFunction->GetClass())
            {
                return pFunction;
            }
            else
            {
                MSG_CRIT("Ungültiger Postprocessor Function","Eine Postprecossorfunction muss innerhalb der Klasse des Imports implementiert sein.");
            }
        }
        else
        {
            if (pFunction->IsStatic())
            {
                MSG_CRIT("Ungültiger Postprocessor Function","Eine Postprecossorfunction darf nicht statisch sein.");
            }

            if (pFunction->GetParameterCount() != 0)
            {
                MSG_CRIT("Ungültiger Postprocessor Function","Eine Postprecossorfunction darf keine Aufrufparameter besitzen.");
            }
        }
    }

    return nullptr;
}

CdmClassMethod* CwmsImport::FindFunction(QString& p_qstrModelMethod)
{
    int iPos = p_qstrModelMethod.lastIndexOf(".");

    if (iPos > 0)
    {
       QString qstrMethod = p_qstrModelMethod.mid(iPos + 1);
       QString qstrClass = p_qstrModelMethod.left(iPos);
       CdmDataProvider* pProvider = CdmSessionManager::GetDataProvider();

       if (CHKPTR(pProvider))
       {
           CdmClassManager* pClassManager = pProvider->GetClassManager();

           if (CHKPTR(pClassManager))
           {
              CdmClass* pClass = pClassManager->FindClassByKeyname(qstrClass);

              if (CHKPTR(pClass))
              {
                 CdmClassMethod* pMethod = pClass->FindMethod(qstrMethod);

                 if (CHKPTR(pMethod))
                 {
                    return pMethod;
                 }
                 else
                 {
                     MSG_CRIT("Funktion nicht gefunden", "Die Funktion wurde nicht gefunden.");
                 }
              }
           }
       }
    }

    return nullptr;
}


bool CwmsImport::CreateData(QStringList& p_qsrlParsedData)
{
    bool bRet = false;
    if (ExecutePreprocessing(p_qsrlParsedData))
    {
        CdmObject* pCdmObject = GetObject(p_qsrlParsedData);

        if (pCdmObject)
        {
            SetDefaultValuesToObject(pCdmObject);
            QList<CwmsImportSettingsColumn*> qlColumns;
            m_cCwmsImportSettings.GetColumns(qlColumns);

            for (int iPos = 0; iPos < qlColumns.count(); ++iPos)
            {
                CwmsImportSettingsColumn* pColumn = qlColumns[iPos];

                if (CHKPTR(pColumn) && !pColumn->IsIgnored() && iPos < p_qsrlParsedData.count())
                {
                    QString qstrValue = p_qsrlParsedData[iPos];

                    CdmValue* pCdmValue = pCdmObject->GetValue(pColumn->GetMember());

                    if (pCdmValue)
                    {
                        pCdmValue->SetValue(qstrValue.simplified(),"");
                    }
                    else
                    {
                        m_qstrImportMessages += "<p>" + qApp->tr("Member wurde nicht gefunden: ") + pColumn->GetMember()+ "</p>";
                    }
                }
            }

            if (pCdmObject->Commit() <= 0)
            {
                pCdmObject->SetDeleted();
                pCdmObject->Commit();
            }
            else
            {
                if (ExecutePostprocessing(pCdmObject))
                {
                    bRet = true;
                }
            }
        }
    }
    else
    {
        m_qstrImportMessages += "<p>" + qApp->tr("Prepocessing fehlgeschlagen.") + "</p>";
        bRet = false;
    }

    return bRet;
}

void CwmsImport::SetDefaultValuesToObject(CdmObject* p_pCdmObject)
{

    if (CHKPTR(p_pCdmObject))
    {
        QMap<QString, TStringPair>::iterator qmIt = m_qmDefaultValues.begin();
        QMap<QString, TStringPair>::iterator qmItEnd = m_qmDefaultValues.end();

        for (; qmIt != qmItEnd; ++qmIt)
        {
            QString qstrKeyname = qmIt.key();
            TStringPair tStringPair = qmIt.value();

            CdmValue* pCdmValue = p_pCdmObject->GetValue(qstrKeyname);

            if (pCdmValue)
            {
                pCdmValue->SetValue(tStringPair.first, tStringPair.second);
            }
            else
            {
                m_qstrImportMessages += "<p>" + qApp->tr("Standardwert nicht gefunden: ") + qstrKeyname + "</p>";
            }
        }
    }
}

void CwmsImport::AddHiddenMember(QString p_qstrMember)
{
    if (!m_qstrlHiddenMembers.contains(p_qstrMember))
    {
        m_qstrlHiddenMembers.append(p_qstrMember);
    }
}

QStringList CwmsImport::GetHiddenMembersList()
{
    return m_qstrlHiddenMembers;
}

void CwmsImport::AddDefaultValues(QString p_qstrKeyname, QString p_qstrValue1, QString p_qstrValue2)
{
    TStringPair tStringPair(p_qstrValue1, p_qstrValue2);
    m_qmDefaultValues.insert(p_qstrKeyname, tStringPair);
}

void CwmsImport::Commit()
{
    CdmObjectContainer* pContainer = GetContainer();

    if (CHKPTR(pContainer))
    {
        pContainer->SetImportMode(false);
        pContainer->Commit();
    }
}
