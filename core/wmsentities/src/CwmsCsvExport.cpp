#include "CdmLogging.h"
#include "CdmObject.h"
#include "CdmObjectContainer.h"
#include "CdmClass.h"
#include "CdmMember.h"
#include "CdmContainerManager.h"
#include "CdmQueryBuilder.h"

// Own Includes
#include "CwmsCsvExport.h"

CwmsCsvExport::CwmsCsvExport(QString p_qstrFilename, QString p_qstrQuery)
    : m_qstrFileName(p_qstrFilename),
      m_pQuery(CdmQueryBuilder::ExecuteQuery(p_qstrQuery)),
      m_rpContainer(NULL),
      m_iDecimalPlaces(2)
{

}

CwmsCsvExport::CwmsCsvExport(QString p_qstrFilename, CdmObjectContainer *p_pContainer)
    : m_qstrFileName(p_qstrFilename),
      m_pQuery(NULL),
      m_rpContainer(p_pContainer),
      m_iDecimalPlaces(2)
{

}


void CwmsCsvExport::GenerateCsvData()
{
    if (!m_pQuery.isNull())
    {
        GenerateQueryContent();
    }
    else if (m_rpContainer)
    {
        GenerateContainerContent();
    }
    else
    {
        ERR("Invalid configuration no Query and Container are NULL");
    }
}

void CwmsCsvExport::SetDateFormat(QString p_qstrFormat)
{
    m_qstrDateFormat = p_qstrFormat;
}

void CwmsCsvExport::SetDecimalPlaces(int iDecimalPlaces)
{
    m_iDecimalPlaces = iDecimalPlaces;
}

void CwmsCsvExport::AddHeaderMapping(QString p_qstrKeyname, QString p_qstrOutputString)
{
    m_qmHeaderMapping.insert(p_qstrKeyname, p_qstrOutputString);
}

void CwmsCsvExport::AddMaxFieldLength(QString p_qstrKeyname, int p_Length)
{
    m_qmMaxFieldLength.insert(p_qstrKeyname, p_Length);
}

void CwmsCsvExport::GenerateQueryContent()
{
    QStringList qstrlHeaders;

    for (int iPos = 0; iPos < m_pQuery->GetColumnCount(); ++iPos)
    {
        qstrlHeaders.append(m_pQuery->GetKeynameAt(iPos));
    }

    GenerateHeader(qstrlHeaders);

    if (m_pQuery->GetResultCount() > 0)
    {
        QLocale loc;
        for (int iRowPos = 0; iRowPos < m_pQuery->GetResultCount(); ++iRowPos)
        {
            QStringList qstrlContent;

            for (int iColPos = 0; iColPos < m_pQuery->GetColumnCount(); ++iColPos)
            {
                CdmQueryResultElement* pResultElement = m_pQuery->GetResultElement(iColPos);

                if (CHKPTR(pResultElement))
                {
                    QString qstrResultValue;
                    switch (pResultElement->GetValueType())
                    {
                    case eDmValueDate:
                        if (m_qstrDateFormat.isEmpty())
                        {
                            qstrResultValue = m_pQuery->GetResultAt(iColPos, iRowPos).toDate().toString("dd.MM.yyyy");
                        }
                        else
                        {
                            qstrResultValue = m_pQuery->GetResultAt(iColPos, iRowPos).toDate().toString(m_qstrDateFormat);
                        }
                        break;
                    case eDmValueDateTime:
                        qstrResultValue = loc.toString(m_pQuery->GetResultAt(iColPos, iRowPos).toDateTime());
                        break;
                    case eDmValueInt:
                    case eDmValueLong:
                        qstrResultValue = loc.toString(m_pQuery->GetResultAt(iColPos, iRowPos).toInt());
                        break;
                    case eDmValueFloat:
                    case eDmValueDouble:
                        qstrResultValue = loc.toString(m_pQuery->GetResultAt(iColPos, iRowPos).toDouble(), 'f', m_iDecimalPlaces);
                        break;
                    default:
                        qstrResultValue = m_pQuery->GetResultAt(iColPos, iRowPos).toString();
                    }


                    if(qstrlContent.count() > iColPos)
                    {
                        QString qstrCell = qstrlContent[iColPos];

                        if (m_qmMaxFieldLength.contains(qstrCell))
                        {
                            qstrResultValue = qstrResultValue.left(m_qmMaxFieldLength[qstrCell]);
                        }
                    }


                    qstrResultValue = qstrResultValue.replace("\n","");
                    qstrlContent.append(qstrResultValue);
                }
            }

            AddLine(qstrlContent);
            qstrlContent.clear();
        }
    }
}

void CwmsCsvExport::GenerateContainerContent()
{
    CdmContainerManager* pContainerManager = m_rpContainer->GetContainerManager();

    if (CHKPTR(pContainerManager))
    {
        pContainerManager->ReloadContainerComplete(m_rpContainer);

        QStringList qstrlHeaders;
        const CdmClass* pClass = m_rpContainer->GetClass();

        if (CHKPTR(pClass))
        {
            QVector<QString> qvMembers = pClass->GetMemberSequence();

            for (int iPos = 0; iPos < qvMembers.count(); ++iPos)
            {
                qstrlHeaders.append(qvMembers[iPos]);
            }

            GenerateHeader(qstrlHeaders);

            QList<CdmObject*> qllObjects;
            m_rpContainer->GetObjectList(qllObjects);

            QList<CdmObject*>::iterator qllIt = qllObjects.begin();
            QList<CdmObject*>::iterator qllItEnd = qllObjects.end();

            for (; qllIt != qllItEnd; ++qllIt)
            {
                CdmObject* pObject = *qllIt;

                if (CHKPTR(pObject))
                {
                    QStringList qstrlContent;

                    for (int iPos = 0; iPos < qvMembers.count(); ++iPos)
                    {
                        qstrlContent.append(pObject->GetDisplayString(qvMembers[iPos]));
                    }

                    AddLine(qstrlContent);
                    qstrlContent.clear();
                }
            }
        }
    }
}

void CwmsCsvExport::GenerateHeader(QStringList& qstrlHeaders)
{
    AddLine(qstrlHeaders);
}

void CwmsCsvExport::AddLine(QStringList& qstrlContent)
{
    bool bFirst = true;

    QString qstrSet;

    for (int iPos = 0; iPos < qstrlContent.count(); ++iPos)
    {
        if (!bFirst)
        {
            qstrSet += ";";
        }
        else
        {
            bFirst = false;
        }

        QString qstrCell = qstrlContent[iPos];

        if (m_qmHeaderMapping.contains(qstrCell))
        {
            qstrCell += m_qmHeaderMapping[qstrCell];
        }

        qstrCell = qstrCell.replace(";","");
        qstrSet += qstrCell;
    }

    qstrSet = qstrSet.replace("\r\n","");
    qstrSet = qstrSet.replace("\n","");

    qstrSet += "\r\n";
    m_qstrContent += qstrSet;
}


void CwmsCsvExport::WriteFile()
{
    QFile qFile(m_qstrFileName);

    if (qFile.open(QIODevice::WriteOnly))
    {
        QTextStream qTextStream(&qFile);
        qTextStream << m_qstrContent;
        qFile.close();
    }
    else
    {
        ERR("Could not open file for writing");
    }
}

CdmQuery* CwmsCsvExport::GetQuery()
{
        return m_pQuery.data();
}
