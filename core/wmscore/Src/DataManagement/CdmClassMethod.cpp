/******************************************************************************
 ** WOGRA technologies GmbH & Co. KG Modul Information
 ** Modulename: CdmClassMethod.cpp
 ** Started Implementation: 2012/06/18
 ** Description:
 **
 ** Implements a class methods
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 **(C) copyright by WOGRA technologies GmbH & Co. KG All rights reserved
 *****************************************************************************/

// System and QT Includes
#include <QStringList>
#include <QFile>
#include <QPixmap>
#include <QByteArray>
#include <QVariant>

// WMS Commons Includes
#include "CwmsUtilities.h"
#include "wmsdefines.h"

// own Includes
#include "CdmSessionManager.h"
#include "CdmDataProvider.h"
#include "CdmMessageManager.h"
#include "CdmLogging.h"
#include "CdmClass.h"
#include "CdmExecutor.h"
#include "CdmClassMethod.h"

/** +-=---------------------------------------------------------Fr 21. Sep 11:17:35 2012----------*
 * @method  CdmClassMethod::CdmClassMethod                   // public                            *
 * @return                                                   //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 21. Sep 11:17:35 2012----------*/
CdmClassMethod::CdmClassMethod()
    : m_eAccess(eDmMemberAccessPrivate),
      m_iVersion(0),
      m_eReturnType(eDmValueNone),
      m_iId(-1),
      m_bStatic(false),
      m_rpCdmClass(nullptr)
{
}

/** +-=---------------------------------------------------------Mi 27. Jun 16:03:30 2012----------*
 * @method  CdmClassMethod::CdmClassMethod                   // public                            *
 * @return                                                   //                                   *
 * @param   int p_iId                                        //                                   *
 * @param   QString p_qstrMethodName                         //                                   *
 * @param   EdmValue p_eReturnType                      //                                   *
 * @param   EdmMemberAccess p_eAccessMode                    //                                   *
 * @param   QString p_qstrCode                               //                                   *
 * @param   int p_iVersion                                   //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 27. Jun 16:03:30 2012----------*/
CdmClassMethod::CdmClassMethod(int p_iId,
                               QString p_qstrMethodName,
                               EdmValueType p_eReturnType,
                               EdmMemberAccess p_eAccessMode,
                               QString p_qstrCode,
                               int p_iVersion)
    : m_qstrMethodName(p_qstrMethodName),
      m_qstrSourceCode(""),
      m_eAccess(p_eAccessMode),
      m_iVersion(p_iVersion),
      m_eReturnType(p_eReturnType),
      m_iId(p_iId),
      m_bStatic(false),
      m_rpCdmClass(nullptr)
{
    SetSourceCode(p_qstrCode);
}

/** +-=---------------------------------------------------------Mi 20. Jun 15:04:36 2012----------*
 * @method  CdmClassMethod::CdmClassMethod                   // public                            *
 * @return                                                   //                                   *
 * @param   QVariantMap& p_rvHash                           //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 20. Jun 15:04:36 2012----------*/
CdmClassMethod::CdmClassMethod(QVariantMap& p_rvHash)
    : m_eAccess(eDmMemberAccessPrivate),
      m_iVersion(0),
      m_eReturnType(eDmValueNone),
      m_iId(-1),
      m_bStatic(false),
      m_rpCdmClass(nullptr)
{
    SetVariant(p_rvHash);
}

/** +-=---------------------------------------------------------Mo 18. Jun 16:34:05 2012----------*
 * @method  CdmClassMethod::~CdmClassMethod                  // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CdmClassMethod                                                *
 *----------------last changed: --------------------------------Mo 18. Jun 16:34:05 2012----------*/
CdmClassMethod::~CdmClassMethod()
{
}

/** +-=---------------------------------------------------------Sa 9. Feb 12:19:52 2013-----------*
 * @method  CdmClassMethod::GetId                            // public, const, slots              *
 * @return  int                                              //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 9. Feb 12:19:52 2013-----------*/
int CdmClassMethod::GetId() const
{
    return m_iId.load();
}

/** +-=---------------------------------------------------------Mi 27. Jun 16:04:26 2012----------*
 * @method  CdmClassMethod::SetId                            // public                            *
 * @return  void                                             //                                   *
 * @param   int p_iId                                        //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 27. Jun 16:04:26 2012----------*/
void CdmClassMethod::SetId(int p_iId)
{
    m_iId = p_iId;
}

/** +-=---------------------------------------------------------Mi 20. Jun 15:04:53 2012----------*
 * @method  CdmClassMethod::SetVariant                       // public                            *
 * @return  void                                             //                                   *
 * @param   QVariantMap& p_rqvHash                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 20. Jun 15:04:53 2012----------*/
void CdmClassMethod::SetVariant(QVariantMap& p_rqvHash)
{
    SYNCHRONIZED_WRITE;
    QVariantMap qmRights = p_rqvHash[WMS_RIGHTS].toMap();
    m_cCdmRights.SetVariant(qmRights);
    m_qstrMethodName = p_rqvHash[WMS_NAME].toString();
    SetSourceCode(p_rqvHash[WMS_CODE].toString());
    m_eReturnType = (EdmValueType)p_rqvHash[WMS_TYPE].toInt();
    m_bStatic = p_rqvHash[WMS_STATIC].toBool();
    m_eAccess = (EdmMemberAccess)p_rqvHash[WMS_ACCESS].toInt();
    m_iVersion = p_rqvHash[WMS_VERSION].toInt();
    m_qstrComment = p_rqvHash[WMS_COMMENT].toString();
    m_qstrCaption = p_rqvHash[WMS_CAPTION].toString();
    m_qbaIcon = QByteArray::fromBase64(p_rqvHash[WMS_ICON].toString().toLocal8Bit());
    QVariantMap qvParameters = p_rqvHash[WMS_PARAMETERS].toMap();

    QVariantMap::iterator qvIt = qvParameters.begin();
    QVariantMap::iterator qvItEnd = qvParameters.end();
    m_qlParameters.clear();
    for(int i=0; i<qvParameters.size(); i++){
        CdmClassMethodParameter cParam;
        m_qlParameters.append(cParam);
    }

    for (; qvIt != qvItEnd; ++qvIt)
    {
        CdmClassMethodParameter cParam;
        QVariantMap qvParameter = qvIt.value().toMap();
        cParam.SetName(qvParameter[WMS_NAME].toString());
        cParam.m_eType = (EdmValueType)qvParameter[WMS_TYPE].toInt();
        cParam.m_iPos = qvParameter[WMS_POS].toInt();
        cParam.m_lReference = qvParameter[WMS_REFERENCE].toInt();
        m_qlParameters[cParam.m_iPos] = cParam;
    }
}

/** +-=---------------------------------------------------------Mo 12. Nov 11:23:59 2012----------*
 * @method  CdmClassMethod::SetClass                         // public                            *
 * @return  void                                             //                                   *
 * @param   CdmClass* p_pCdmClass                            //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 12. Nov 11:23:59 2012----------*/
void CdmClassMethod::SetClass(CdmClass* p_pCdmClass)
{
    SYNCHRONIZED_WRITE;
    m_rpCdmClass = p_pCdmClass;
}

/** +-=---------------------------------------------------------Sa 9. Feb 12:20:13 2013-----------*
 * @method  CdmClassMethod::GetClass                         // public, const, slots              *
 * @return  CdmClass*                                        //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 9. Feb 12:20:13 2013-----------*/
CdmClass* CdmClassMethod::GetClass() const
{
    SYNCHRONIZED_READ;
    return m_rpCdmClass;
}

/** +-=---------------------------------------------------------Sa 9. Feb 12:20:30 2013-----------*
 * @method  CdmClassMethod::GetVersion                       // public, const, slots              *
 * @return  int                                              //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 9. Feb 12:20:30 2013-----------*/
int CdmClassMethod::GetVersion() const
{
    return m_iVersion.load();
}

/** +-=---------------------------------------------------------Mo 18. Jun 16:34:51 2012----------*
 * @method  CdmClassMethod::SetVersion                       // public                            *
 * @return  void                                             //                                   *
 * @param   int p_iVersion                                   //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 18. Jun 16:34:51 2012----------*/
void CdmClassMethod::SetVersion(int p_iVersion)
{
    m_iVersion = p_iVersion;
}

/** +-=---------------------------------------------------------Mi 27. Jun 15:55:20 2012----------*
 * @method  CdmClassMethod::SetSourceCode                    // public                            *
 * @return  void                                             //                                   *
 * @param   QString p_qstrCode                               //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 27. Jun 15:55:20 2012----------*/
void CdmClassMethod::SetSourceCode(QString p_qstrCode)
{
    SYNCHRONIZED_WRITE;
    if (!CwmsUtilities::IsStringBase64Encode(p_qstrCode))
    {
        QByteArray ba;
        ba.append(p_qstrCode);
        m_qstrSourceCode = ba.toBase64();
    }
    else
    {
        m_qstrSourceCode = p_qstrCode;
    }
}

/** +-=---------------------------------------------------------Sa 9. Feb 12:20:39 2013-----------*
 * @method  CdmClassMethod::GetSourceCode                    // public, const, slots              *
 * @return  QString                                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 9. Feb 12:20:39 2013-----------*/
QString CdmClassMethod::GetSourceCode() const
{
    SYNCHRONIZED_READ;
    QString qstrCode;
    if (CwmsUtilities::IsStringBase64Encode(m_qstrSourceCode))
    {
        QByteArray ba;
        ba.append(m_qstrSourceCode);
        qstrCode = QByteArray::fromBase64(ba);
    }
    else
    {
        qstrCode = m_qstrSourceCode;
    }

    return qstrCode;
}

QString CdmClassMethod::GetSourceCodeBase64() const
{
    SYNCHRONIZED_READ;
    if (!CwmsUtilities::IsStringBase64Encode(m_qstrSourceCode))
    {
        QByteArray ba;
        ba.append(m_qstrSourceCode);
        return ba.toBase64();
    }

    return m_qstrSourceCode;
}

QString CdmClassMethod::GetMethodName() const
{
    SYNCHRONIZED_READ;
    return m_qstrMethodName;
}

void CdmClassMethod::SetMethodName(QString p_qstrName)
{
    SYNCHRONIZED_WRITE;
    m_qstrMethodName = p_qstrName;
}

void CdmClassMethod::SetCaption(QString p_qstrCaption)
{
    SYNCHRONIZED_WRITE;
    m_qstrCaption = p_qstrCaption;
}

QString CdmClassMethod::GetCaption() const
{
    SYNCHRONIZED_READ;
    QString qstrRet;

    if (m_qstrCaption.isEmpty())
    {
        qstrRet = GetMethodName();
    }
    else
    {
        qstrRet = m_qstrCaption;
    }

    return qstrRet;
}

void CdmClassMethod::SetIcon(QString p_qstrFilename)
{
    SYNCHRONIZED_WRITE;
    QFile qFile(p_qstrFilename);

    if (qFile.open(QIODevice::ReadOnly))
    {
        m_qbaIcon = qFile.readAll();
    }
    else
    {
        ERR(tr("Can not open file for reading"));
    }
}

void CdmClassMethod::SetIcon(QByteArray p_qbArray)
{
    SYNCHRONIZED_WRITE;
    m_qbaIcon = p_qbArray;
}

QPixmap CdmClassMethod::GetIcon() const
{
    SYNCHRONIZED_READ;
    QPixmap qPixmap;
    qPixmap.loadFromData(m_qbaIcon);
    return qPixmap;
}

QByteArray CdmClassMethod::GetIconAsByteArray() const
{
    SYNCHRONIZED_READ;
    return m_qbaIcon;
}

void CdmClassMethod::SetAccess(EdmMemberAccess p_eType)
{
    SYNCHRONIZED_WRITE;
    m_eAccess = p_eType;
}

EdmMemberAccess CdmClassMethod::GetAccess() const
{
    SYNCHRONIZED_READ;
    return m_eAccess;
}

void CdmClassMethod::SetReturnType(EdmValueType p_eType)
{
    SYNCHRONIZED_WRITE;
    m_eReturnType = p_eType;
}

EdmValueType CdmClassMethod::GetReturnType() const
{
    SYNCHRONIZED_READ;
    return m_eReturnType;
}

void CdmClassMethod::SetParameters(QList<CdmClassMethodParameter> p_qmParameters)
{
    SYNCHRONIZED_WRITE;
    m_qlParameters = p_qmParameters;
}

QList<CdmClassMethodParameter> CdmClassMethod::GetParameters() const
{
    SYNCHRONIZED_READ;
    return m_qlParameters;
}

int CdmClassMethod::GetParameterCount() const
{
    SYNCHRONIZED_READ;
    return m_qlParameters.count();
}

bool CdmClassMethod::HasParameters() const
{
    return (GetParameterCount() != 0);
}

void CdmClassMethod::SetParameters(QString p_qstrParameters)
{
    SYNCHRONIZED_WRITE;
    if (!p_qstrParameters.isEmpty() && p_qstrParameters != "-")
    {
        QStringList qstrlParameters = p_qstrParameters.split("||");

        for (int iPos = 0; iPos < qstrlParameters.count(); ++iPos)
        {
            QString qstrParameter = qstrlParameters[iPos];
            if (qstrParameter.length() > 0)
            {
                CdmClassMethodParameter cParam;
                QStringList qstrlTemp = qstrParameter.split("|");
                cParam.SetName(qstrlTemp[0]);
                cParam.m_eType = (EdmValueType)qstrlTemp[1].toInt();
                cParam.m_iPos = (EdmValueType)qstrlTemp[2].toInt();

                if (qstrParameter.count() == 4 &&
                        (cParam.m_eType == eDmValueContainerRef ||
                         cParam.m_eType == eDmValueObjectRef))
                {
                    cParam.m_lReference = qstrlTemp[3].toInt();
                }

                m_qlParameters.append(cParam);
            }
        }
    }
}

void CdmClassMethod::AddParameter(QString p_qstrName, EdmValueType p_eValueType,qint64 p_lClassId)
{
    SYNCHRONIZED_WRITE;
    CdmClassMethodParameter cParam;
    cParam.SetName(p_qstrName);
    cParam.m_eType = p_eValueType;
    cParam.m_lReference = p_lClassId;
    cParam.m_iPos = m_qlParameters.count();
    m_qlParameters.append(cParam);
}

QString CdmClassMethod::GetParametersAsString() const
{
    SYNCHRONIZED_READ;
    QString qstrRet;

    if (!m_qlParameters.isEmpty())
    {

        for (int iCounter = 0; iCounter < m_qlParameters.count(); ++iCounter)
        {
            CdmClassMethodParameter cParam = m_qlParameters[iCounter];
            qstrRet += cParam.GetName() + "|";
            qstrRet += QString::number(cParam.m_eType) + "|";
            qstrRet += QString::number(cParam.m_iPos);

            if (cParam.m_lReference > 0)
            {
                //   qstrRet +=  "|" + cParam.m_lReference;
            }

            if (iCounter < m_qlParameters.count() - 1)
            {
                qstrRet += "||";
            }
        }
    }


    return qstrRet;
}

QString CdmClassMethod::GetParametersAsStringForFunction() const
{
    SYNCHRONIZED_READ;
    QString qstrRet;

    if (!m_qlParameters.isEmpty())
    {

        for (int iCounter = 0; iCounter < m_qlParameters.count(); ++iCounter)
        {
            CdmClassMethodParameter cParam = m_qlParameters[iCounter];
            qstrRet += cParam.GetName();
            if (iCounter < m_qlParameters.count() - 1)
            {
                qstrRet += ", ";
            }
        }
    }


    return qstrRet;
}

void CdmClassMethod::DeleteParameter(QString p_qstrName)
{
    SYNCHRONIZED_WRITE;
    for (int iCounter = 0; iCounter < m_qlParameters.count(); ++iCounter)
    {
        CdmClassMethodParameter cParam = m_qlParameters[iCounter];

        if (cParam.GetName() == p_qstrName)
        {
            m_qlParameters.removeAt(iCounter);
            break;
        }
    }
}

void CdmClassMethod::MoveParameterUp(QString p_qstrParam)
{
    SYNCHRONIZED_WRITE;
    for (int iCounter = 0; iCounter < m_qlParameters.count(); ++iCounter)
    {
        CdmClassMethodParameter cParam = m_qlParameters[iCounter];

        if (cParam.GetName() == p_qstrParam)
        {
            if (iCounter > 0)
            {
                CdmClassMethodParameter cTemp = m_qlParameters[iCounter-1];
                m_qlParameters.removeAt(iCounter-1);
                m_qlParameters.removeAt(iCounter-1);
                cParam.m_iPos = iCounter - 1;
                cTemp.m_iPos = iCounter;
                m_qlParameters.insert(iCounter-1, cParam);
                m_qlParameters.insert(iCounter, cTemp);
                break;
            }
        }
    }
}

void CdmClassMethod::MoveParameterDown(QString p_qstrParam)
{
    SYNCHRONIZED_WRITE;
    for (int iCounter = 0; iCounter < m_qlParameters.count(); ++iCounter)
    {
        CdmClassMethodParameter cParam = m_qlParameters[iCounter];

        if (cParam.GetName() == p_qstrParam)
        {
            if (iCounter + 1 < m_qlParameters.count())
            {
                CdmClassMethodParameter cTemp = m_qlParameters[iCounter+1];
                m_qlParameters.removeAt(iCounter);
                m_qlParameters.removeAt(iCounter);
                cTemp.m_iPos = iCounter;
                cParam.m_iPos = iCounter + 1;
                m_qlParameters.insert(iCounter, cTemp);
                m_qlParameters.insert(iCounter+1, cParam);
                break;
            }
        }
    }
}

bool CdmClassMethod::CheckExecuteAccess() const
{
    SYNCHRONIZED_READ;
    return m_cCdmRights.HasCurrentUserWriteAccess();
}

CdmClassMethodParameter CdmClassMethod::GetParameterByPos(int p_iPos) const
{
    SYNCHRONIZED_READ;
    CdmClassMethodParameter cParam;

    if (p_iPos < m_qlParameters.count())
    {
        cParam = m_qlParameters[p_iPos];
    }
    else
    {
        ERR(tr("Zuviele Parameter für Funktionsaufruf Funktion: ") + GetMethodName());
    }

    return cParam;
}

CdmRights& CdmClassMethod::GetRights()
{
    SYNCHRONIZED_READ;
    return m_cCdmRights;
}

QString CdmClassMethod::GetCallInterface() const
{
    SYNCHRONIZED_READ;
    QString qstrRet = m_qstrMethodName + "(";
    bool bFirst = true;

    for (int iCounter = 0; iCounter < m_qlParameters.count(); ++iCounter)
    {
        CdmClassMethodParameter cParam = m_qlParameters[iCounter];
        QString qstrKey = cParam.GetName();
        EdmValueType eDmValue = cParam.m_eType;

        if (!bFirst)
        {
            qstrRet += ", ";
        }
        else
        {
            bFirst = false;
        }

        qstrRet += CdmMember::GetValueTypeAsString(eDmValue) + " ";
        qstrRet += qstrKey;
    }

    qstrRet += ")";
    return qstrRet;
}

QString CdmClassMethod::GetComment() const
{
    SYNCHRONIZED_READ;
    return m_qstrComment;
}

void CdmClassMethod::SetComment(QString p_qstrComment)
{
    SYNCHRONIZED_WRITE;
    m_qstrComment = p_qstrComment;
}

bool CdmClassMethod::IsStatic() const
{
    return m_bStatic.load();
}

void CdmClassMethod::SetStatic(bool p_bStatic)
{
    m_bStatic = p_bStatic;
}

QVariant CdmClassMethod::GetVariant() const
{
    SYNCHRONIZED_READ;
    QVariantMap qvHash;

    qvHash.insert(WMS_RIGHTS, m_cCdmRights.GetVariant());
    qvHash.insert(WMS_NAME, m_qstrMethodName);
    qvHash.insert(WMS_CODE, GetSourceCodeBase64());
    qvHash.insert(WMS_TYPE, m_eReturnType);
    qvHash.insert(WMS_ACCESS, m_eAccess);
    qvHash.insert(WMS_VERSION, m_iVersion.load());
    qvHash.insert(WMS_COMMENT, m_qstrComment);
    qvHash.insert(WMS_CAPTION, m_qstrCaption);
    qvHash.insert(WMS_STATIC, m_bStatic.load());
    QString qstrIcon(m_qbaIcon.toBase64());
    qvHash.insert(WMS_ICON, qstrIcon);

    QVariantMap qvParameters;

    for (int iCounter = 0; iCounter < m_qlParameters.count(); ++iCounter)
    {
        QVariantMap qvParameter;
        CdmClassMethodParameter cParam = m_qlParameters[iCounter];
        qvParameter.insert(WMS_TYPE, cParam.m_eType);
        qvParameter.insert(WMS_POS, cParam.m_iPos);
        qvParameter.insert(WMS_REFERENCE, cParam.m_lReference);
        qvParameter.insert(WMS_NAME, cParam.GetName());
        qvParameters.insert(cParam.GetName(), qvParameter);
    }

    qvHash.insert(WMS_PARAMETERS, qvParameters);
    return qvHash;
}

QString CdmClassMethod::GenerateScriptCode()
{
    SYNCHRONIZED_READ;
    QString qstrParameters;

    for (int iCounter = 0; iCounter < m_qlParameters.count(); ++iCounter)
    {
        qstrParameters += m_qlParameters[iCounter].GetName();

        if (iCounter < m_qlParameters.count() -1)
        {
            qstrParameters += ",";
        }
    }

    QString qstrCode = "function " + GetMethodName() + "(" + qstrParameters + ")\n";
    qstrCode += "{\n";
    qstrCode += GetSourceCode() + "\n";
    qstrCode += "}\n";


    return qstrCode;

}

bool CdmClassMethod::LockClassMethod()
{
    SYNCHRONIZED_WRITE;
    bool bRet = false;

    CdmDataProvider* pManager = CdmSessionManager::GetDataProvider();

    if (CHKPTR(pManager))
    {
        IdmDataAccess* pDataAccess = pManager->GetDataAccess();

        if (CHKPTR(pDataAccess))
        {
            bRet = pDataAccess->LockClassMethod(GetId());
        }
    }

    return bRet;
}

bool CdmClassMethod::UnlockClassMethod()
{
    SYNCHRONIZED_WRITE;
    bool bRet = false;

    CdmDataProvider* pManager = CdmSessionManager::GetDataProvider();

    if (CHKPTR(pManager))
    {
        IdmDataAccess* pDataAccess = pManager->GetDataAccess();

        if (CHKPTR(pDataAccess))
        {
            bRet = pDataAccess->UnlockClassMethod(GetId());
        }
    }

    return bRet;
}

QString CdmClassMethod::GetUri() const
{
    SYNCHRONIZED_READ;
    QString qstrUri;
    if (CHKPTR(m_rpCdmClass))
    {
        qstrUri = CdmLocatedElement::CreateUri(WMS_URI_METHOD,
                                               m_rpCdmClass->GetFullQualifiedName(),
                                               GetMethodName());
    }

    return qstrUri;
}

QString CdmClassMethod::GetUriInternal() const
{
    return CdmLocatedElement::CreateUriPath(WMS_URI_METHOD,
                                            m_rpCdmClass->GetFullQualifiedName(),
                                            GetMethodName(), "");
}

bool CdmClassMethod::IsMethod() const
{
    return true;
}

QString CdmClassMethod::GetAccessModeAsString() const
{
    switch (m_eAccess)
    {
    case eDmMemberAccessPrivate:
        return WMS_ACCESS_PRIVATE;
        break;
    case eDmMemberAccessProtected:
        return WMS_ACCESS_PROTECTED;
        break;
    case eDmMemberAccessPublic:
        return WMS_ACCESS_PUBLIC;
        break;
    default:
        return "Unknown";
    }
}


QVariant CdmClassMethod::ExecuteStaticFunction(bool p_bDebugger)
{
    QVariant qvResult;

    if (IsStatic())
    {
        QVariantList qlParameters;

        if (p_bDebugger)
        {
            qvResult = CdmExecutor::DebugFunction(this, nullptr, qlParameters, true, true);
        }
        else
        {
            qvResult = CdmExecutor::ExecuteFunction(this, nullptr, qlParameters, true, true, false, false);
        }
    }

    return qvResult;
}

QVariant CdmClassMethod::ExecuteFunction(bool p_bDebugger, CdmObject* pObject)
{
    QVariant qvResult;

    if (IsStatic())
    {
        qvResult = ExecuteStaticFunction(p_bDebugger);
    }
    else
    {
        if (pObject)
        {
            QVariantList qlParameters;
            if (p_bDebugger)
            {
                qvResult = CdmExecutor::DebugFunction(this, pObject, qlParameters, true, true);
            }
            else
            {
                qvResult = CdmExecutor::ExecuteFunction(this, pObject, qlParameters, true, true, false, false);
            }
        }
        else
        {
            MSG_INFO(("Funktion wird nicht ausgeführt"), ("Die Funktion kann nicht ausgeführt werden, da kein Objekt gewählt wurde."));
        }
    }

    return qvResult;
}
// CdmClassMethodParameter CdmClassMethodParameter CdmClassMethodParameter CdmClassMethodParameter
// CdmClassMethodParameter CdmClassMethodParameter CdmClassMethodParameter CdmClassMethodParameter
// CdmClassMethodParameter CdmClassMethodParameter CdmClassMethodParameter CdmClassMethodParameter

CdmClassMethodParameter::CdmClassMethodParameter()
    : m_iPos(0),
      m_eType(eDmValueNone),
      m_lReference(0),
      m_qstrName("")
{
    // does nothing
}

void CdmClassMethodParameter::SetName(QString p_qstrName)
{
    m_qstrName = p_qstrName;
}

QString CdmClassMethodParameter::GetName() const
{
    return m_qstrName;
}
