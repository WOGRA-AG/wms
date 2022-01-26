// System and QT Includes



// own Includes
#include "CdmEnhancedQueryProxy.h"
#include "CdmClass.h"
#include "CdmObjectContainer.h"
#include "CdmObject.h"
#include "CdmMember.h"
#include "CdmLogging.h"
#include "CwmsSearchWindowDlg.h"
#include "CwmsObjectSelectionIf.h"



CwmsObjectSelectionIf::CwmsObjectSelectionIf(QWidget* parent)
    : QDialog(parent)
{
    setupUi(this);
}

CwmsObjectSelectionIf::~CwmsObjectSelectionIf()
{
}

void CwmsObjectSelectionIf::SetProxy(CdmQueryModel* p_pCwmsProxy)
{
    m_cModel.SetProxy(p_pCwmsProxy);
}

bool CwmsObjectSelectionIf::SetWql(QString p_qstrWql)
{
    m_cModel.Execute(p_qstrWql);

    if (m_cModel.GetQuery()->GetResultCount() == 0)
    {
        return false;
    }

    m_pqlvObjects->setModel(&m_cModel);
    return true;
}

void CwmsObjectSelectionIf::SetContainer(CdmObjectContainer* p_pContainer)
{
    if(CHKPTR(p_pContainer))
    {
        auto pClass = p_pContainer->GetClass();

        if (CHKPTR(pClass))
        {
            m_qstrDisplayMember = pClass->GetCaptionMemberKeyname();
        }

        m_cModel.SetContainer(p_pContainer);

        if (m_qstrDisplayMember.isEmpty())
        {
            const CdmClass* pCdmClass = p_pContainer->GetClass();

            if(pCdmClass)
            {
                QMap<qint64, CdmMember*> qmMembers;
                pCdmClass->GetMemberMap(qmMembers);

                QMap<qint64, CdmMember*>::iterator qmIt = qmMembers.begin();
                QMap<qint64, CdmMember*>::iterator qmItEnd = qmMembers.end();

                if(pCdmClass->IsEventSourcingActive() || pCdmClass->IsEventClass())
                {
                    for(; qmIt != qmItEnd; ++qmIt)
                    {
                        CdmMember *pMember = (*qmIt);
                        if(pMember)
                        {
                            QString qstrKeyname = pMember->GetKeyname();
                            if(qstrKeyname == "Id")
                            {
                                CdmClassManager *pClassManager = pCdmClass->GetClassManager();
                                CdmMember *pReferencedClassMember = getReferencedClassMemberForEvent(pMember->GetClassReference(), pClassManager);
                                if(CHKPTR(pReferencedClassMember) &&
                                        pReferencedClassMember->GetValueType() != eDmValueBinaryDocument &&
                                        pReferencedClassMember->GetValueType() != eDmValueCharacterDocument &&
                                        pReferencedClassMember->GetValueType() != eDmValueObjectRef &&
                                        pReferencedClassMember->GetValueType() != eDmValueListDouble &&
                                        pReferencedClassMember->GetValueType() != eDmValueListInt &&
                                        pReferencedClassMember->GetValueType() != eDmValueListString &&
                                        pReferencedClassMember->GetValueType() != eDmValueDictIntDouble &&
                                        pReferencedClassMember->GetValueType() != eDmValueDictIntInt &&
                                        pReferencedClassMember->GetValueType() != eDmValueDictIntString &&
                                        pReferencedClassMember->GetValueType() != eDmValueDictStringDouble &&
                                        pReferencedClassMember->GetValueType() != eDmValueDictStringInt &&
                                        pReferencedClassMember->GetValueType() != eDmValueDictStringString &&
                                        pReferencedClassMember->GetValueType() != eDmValueListObjects &&
                                        pReferencedClassMember->GetValueType() != eDmValueObjectRef &&
                                        pReferencedClassMember->GetValueType() != eDmValueContainerRef &&
                                        pReferencedClassMember->GetValueType() != eDmValueFormula)
                                {
                                    m_cModel.GetQuery()->AddResultElement(pReferencedClassMember->GetKeyname());
                                }
                                break;
                            }
                        }
                    }
                }
                else
                {
                    for(; qmIt != qmItEnd; ++qmIt)
                    {
                        CdmMember* pCdmMember = qmIt.value();

                        if(CHKPTR(pCdmMember) &&
                                pCdmMember->GetValueType() != eDmValueBinaryDocument &&
                                pCdmMember->GetValueType() != eDmValueCharacterDocument &&
                                pCdmMember->GetValueType() != eDmValueObjectRef &&
                                pCdmMember->GetValueType() != eDmValueListDouble &&
                                pCdmMember->GetValueType() != eDmValueListInt &&
                                pCdmMember->GetValueType() != eDmValueListString &&
                                pCdmMember->GetValueType() != eDmValueDictIntDouble &&
                                pCdmMember->GetValueType() != eDmValueDictIntInt &&
                                pCdmMember->GetValueType() != eDmValueDictIntString &&
                                pCdmMember->GetValueType() != eDmValueDictStringDouble &&
                                pCdmMember->GetValueType() != eDmValueDictStringInt &&
                                pCdmMember->GetValueType() != eDmValueDictStringString &&
                                pCdmMember->GetValueType() != eDmValueListObjects &&
                                pCdmMember->GetValueType() != eDmValueObjectRef &&
                                pCdmMember->GetValueType() != eDmValueContainerRef &&
                                pCdmMember->GetValueType() != eDmValueFormula)
                        {
                            m_cModel.GetQuery()->AddResultElement(pCdmMember->GetKeyname());
                        }
                    }
                }
            }
        }
        else
        {
            SetDisplayMember(m_qstrDisplayMember);
        }

        m_cModel.Execute();
        m_pqlvObjects->setModel(&m_cModel);
    }
}

CdmMember *CwmsObjectSelectionIf::getReferencedClassMemberForEvent(qint64 lReferencedClassId, CdmClassManager *pClassManager)
{
    CdmMember *pMember = nullptr;

    CdmClass *pReferencedClass = pClassManager->FindClassById(lReferencedClassId);
    QMap<qint64, CdmMember*> qmMembers;
    pReferencedClass->GetMemberMap(qmMembers);

    QMap<qint64, CdmMember*>::iterator qmIt = qmMembers.begin();
    QMap<qint64, CdmMember*>::iterator qmItEnd = qmMembers.end();
    for(; qmIt != qmItEnd; ++qmIt)
    {
        pMember = (*qmIt);
        QString qstrKeyname = pMember->GetKeyname();
        if(qstrKeyname == "Id")
        {
            break;
        }
    }
    return pMember;
}


CdmObject* CwmsObjectSelectionIf::GetSelectedObject()
{
    return m_cModel.GetObject(m_pqlvObjects);
}

QList<CdmObject*> CwmsObjectSelectionIf::GetSelectedListOfObject()
{
    return m_cModel.GetObjects(m_pqlvObjects);
}

qint64 CwmsObjectSelectionIf::GetSelectedObjectId()
{
    qint64 lRet = 0;

    CdmObject* pCdmObject = GetSelectedObject();

    if (pCdmObject)
    {
        lRet = pCdmObject->GetId();
    }

    return lRet;
}

void CwmsObjectSelectionIf::SetDisplayMember(QString p_qstrMember)
{
    if (!p_qstrMember.isEmpty())
    {
        m_cModel.GetQuery()->DeleteResultElements();
        m_cModel.GetQuery()->AddResultElement(p_qstrMember);
        m_qstrDisplayMember = p_qstrMember;
    }
}

CdmObject* CwmsObjectSelectionIf::GetObject(QString p_qstrWql, QWidget* p_pqwParent)
{
    CdmObject* pCdmObject = nullptr;
    CwmsObjectSelectionIf* pCwmsSelection = new CwmsObjectSelectionIf(p_pqwParent);
    if (pCwmsSelection->SetWql(p_qstrWql)) // more than 0 object found for selection
    {
        if(pCwmsSelection->exec() == QDialog::Accepted)
        {
            pCdmObject = pCwmsSelection->GetSelectedObject();
        }
    }

    return pCdmObject;
}

QList<CdmObject*> CwmsObjectSelectionIf::GetListofObjects(CdmObjectContainer* p_pContainer,
                                                          CdmQueryModel* p_pCwmsProxy,
                                                          QWidget* p_pqwParent,
                                                          QString p_qstrDisplayMember)
{
    QList<CdmObject*> qlObjects;

    if(CHKPTR(p_pContainer))
    {
        int iObjectsOnDb = p_pContainer->CountObjectsOnDb();
        if (iObjectsOnDb < 100)
        {
            CwmsObjectSelectionIf* pCwmsSelection = new CwmsObjectSelectionIf(p_pqwParent);
            pCwmsSelection->SetContainer(p_pContainer);
            pCwmsSelection->SetProxy(p_pCwmsProxy);
            pCwmsSelection->SetDisplayMember(p_qstrDisplayMember);

            if(pCwmsSelection->exec() == QDialog::Accepted)
            {
                qlObjects = pCwmsSelection->GetSelectedListOfObject();
            }
        }
        else
        {
            qlObjects = CwmsSearchWindowDlg::FindObjects(p_pContainer, p_pqwParent);
        }
    }


    return qlObjects;
}

CdmObject* CwmsObjectSelectionIf::GetObject(CdmObjectContainer* p_pContainer,
                                            CdmQueryModel* p_pCwmsProxy,
                                            QWidget* p_pqwParent,
                                            QString p_qstrDisplayMember)
{
    CdmObject* pCdmObject = nullptr;

    if(CHKPTR(p_pContainer))
    {
        int iObjectsOnDb = p_pContainer->CountObjectsOnDb();
        if (iObjectsOnDb < 100)
        {
            CwmsObjectSelectionIf* pCwmsSelection = new CwmsObjectSelectionIf(p_pqwParent);
            pCwmsSelection->SetContainer(p_pContainer);
            pCwmsSelection->SetProxy(p_pCwmsProxy);
            pCwmsSelection->SetDisplayMember(p_qstrDisplayMember);

            if(pCwmsSelection->exec() == QDialog::Accepted)
            {
                pCdmObject = pCwmsSelection->GetSelectedObject();
            }
        }
        else
        {
            pCdmObject = CwmsSearchWindowDlg::FindObject(p_pContainer, p_pqwParent);
        }
    }

    return pCdmObject;
}

qint64 CwmsObjectSelectionIf::GetObjectId(CdmObjectContainer* p_pContainer,
                                          CdmQueryModel* p_pCwmsProxy,
                                          QWidget* p_pqwParent)
{
    qint64 lObjectId = 0;

    if(CHKPTR(p_pContainer))
    {
        CwmsObjectSelectionIf* pCwmsSelection = new CwmsObjectSelectionIf(p_pqwParent);
        pCwmsSelection->SetProxy(p_pCwmsProxy);
        pCwmsSelection->SetContainer(p_pContainer);

        if(pCwmsSelection->exec() == QDialog::Accepted)
        {
            lObjectId = pCwmsSelection->GetSelectedObjectId();
        }
    }

    return lObjectId;
}
