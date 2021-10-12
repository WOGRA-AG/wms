// System and QT Includes


// WMS Includes
#include "CdmClass.h"
#include "CdmClassMethod.h"
#include "CdmMember.h"
#include "CdmDataProvider.h"
#include "CdmSessionManager.h"
#include "CdmLogging.h"
#include "CdmClassManager.h"

// Own Includes
#include "CwmsSymbolSearch.h"



CwmsSymbolSearch::CwmsSymbolSearch(QString p_qstrSearch, bool p_bClass, bool p_bMember, bool p_bMethod)
    : m_qstrSearch(p_qstrSearch),
      m_bClass(p_bClass),
      m_bMembers(p_bMember),
      m_bMethods(p_bMethod)
{
     // nothing to do here
}

CwmsSymbolSearch::~CwmsSymbolSearch()
{
    // nothing to do here
}

void CwmsSymbolSearch::Execute()
{
    if (!m_qstrSearch.isEmpty())
    {
        // the class search must be performed in every case
        // because every search elements are parts of classes
        ClassSearch();
    }
}



void CwmsSymbolSearch::ClassSearch()
{
    CdmDataProvider* pManager = CdmSessionManager::GetDataProvider();

    if (CHKPTR(pManager))
    {
        CdmClassManager* pClassManager = pManager->GetClassManager();

        if (CHKPTR(pClassManager))
        {
            QList<CdmClass*> qllClasses;
            pClassManager->GetClassList(qllClasses);

            QList<CdmClass*>::iterator qllIt = qllClasses.begin();
            QList<CdmClass*>::iterator qllItEnd = qllClasses.end();

            for (; qllIt != qllItEnd; ++qllIt)
            {
                CdmClass* pClass = *qllIt;

                if (CHKPTR(pClass))
                {
                    if (m_bClass)
                    {
                        if (CheckElement(pClass))
                        {
                            m_qlFoundClasses.append(pClass);
                        }
                    }

                    if (m_bMembers)
                    {
                        MemberSearch(pClass);
                    }

                    if (m_bMethods)
                    {
                        MethodSearch(pClass);
                    }
                }
            }
        }
    }
}


void CwmsSymbolSearch::MemberSearch(CdmClass* p_pClass)
{
    if (CHKPTR(p_pClass))
    {
        QMap<qint64, CdmMember*> qmMembers;
        p_pClass->GetMemberMap(qmMembers);

        QMap<qint64, CdmMember*>::iterator qmIt = qmMembers.begin();
        QMap<qint64, CdmMember*>::iterator qmItEnd = qmMembers.end();

        for (; qmIt != qmItEnd; ++qmIt)
        {
            CdmMember* pMember = qmIt.value();

            if (CHKPTR(pMember))
            {
                if (CheckElement(pMember))
                {
                    m_qlFoundMembers.append(pMember);
                }
            }
        }
    }
}

void CwmsSymbolSearch::MethodSearch(CdmClass* p_pClass)
{
    if (CHKPTR(p_pClass))
    {
        QMap<QString, CdmClassMethod*> qmMethods = p_pClass->GetMethods();

        QMap<QString, CdmClassMethod*>::iterator qmIt = qmMethods.begin();
        QMap<QString, CdmClassMethod*>::iterator qmItEnd = qmMethods.end();

        for (; qmIt != qmItEnd; ++qmIt)
        {
            CdmClassMethod* pMethod = qmIt.value();

            if (CHKPTR(pMethod))
            {
                QString qstrMethodName = pMethod->GetMethodName();
                QString qstrCode = pMethod->GetSourceCode();

                if (qstrMethodName.contains(m_qstrSearch, Qt::CaseInsensitive) ||
					qstrCode.contains(m_qstrSearch, Qt::CaseInsensitive))
                {
                    m_qlFoundMethods.append(pMethod);
                }
            }
        }
    }
}


bool CwmsSymbolSearch::CheckElement(CdmModelElement* p_pElement)
{
    bool bFound = false;

    if (CHKPTR(p_pElement))
    {
        QString qstrKeyname = p_pElement->GetKeyname();
        QString qstrCaption = p_pElement->GetCaption();

        if (qstrKeyname.contains(m_qstrSearch, Qt::CaseInsensitive) ||
             qstrCaption.contains(m_qstrSearch, Qt::CaseInsensitive))
        {
            bFound = true;
        }
    }

    return bFound;
}
