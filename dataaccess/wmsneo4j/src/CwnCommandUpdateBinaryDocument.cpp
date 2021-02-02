#include <QFileInfo>

// WMS Includes
#include "CdmValueBinaryDocument.h"

#include "CwnCommandUpdateBinaryDocument.h"

#include "CwnCommandStdHeader.h"


CwnCommandUpdateBinaryDocument::CwnCommandUpdateBinaryDocument(CdmValueBinaryDocument* p_pValue, CwnDataAccess* p_pDataAccess)
    : CwnCommandBase(p_pDataAccess),
      m_rpValue(p_pValue)
{
}

CwnCommandUpdateBinaryDocument::~CwnCommandUpdateBinaryDocument()
{

}

bool CwnCommandUpdateBinaryDocument::CheckValid()
{
    return CHKPTR(m_rpValue);
}

QString CwnCommandUpdateBinaryDocument::createQuery()
{
    QString qcstrBase64 = m_rpValue->GetBase64();
    // if string is empty the bindoc was deleted.

    // adding new dataset
    QString qstrFilename = ShortFilename(m_rpValue->GetFilename());

    QString query;

    if (!qcstrBase64.isEmpty())
    {
        query = QString("MATCH(v:WMS_VALUE) WHERE id(v)=%1 SET v.filetype=\'%2\', v.filename=\'%3'\', v.val=\'%4\' RETURN id(v);")
                         .arg(m_rpValue->GetId())
                         .arg(m_rpValue->GetFileType())
                         .arg(qstrFilename)
                         .arg(qcstrBase64);
    }
    else
    {
        query = QString("MATCH(v:WMS_VALUE) WHERE id(v)=%1 SET v.filetype='', v.filename='', v.val=\'%2\' RETURN id(v);")
                         .arg(m_rpValue->GetId())
                         .arg(qcstrBase64);
    }

    return query;
}

int CwnCommandUpdateBinaryDocument::Execute()
{
    int iRet = EC(eDmUnknownSqlError);
    QString payload = createJson(createQuery());
    //qDebug()<<payload;
    queryCausedError = payload;
    ConnectAndExecute(executeCommit,payload,nullptr,nullptr);
    QVariant Ret;
    interpretAnswer(Ret);
    iRet = Ret.toInt();
    return iRet;
}

QString CwnCommandUpdateBinaryDocument::ShortFilename(QString p_qstrFilename)
{
   QString qstrFilename;

   if (p_qstrFilename.length() > 32)
   {
      QFileInfo qfInfo(p_qstrFilename);
      QString qstrSuffix = qfInfo.completeSuffix();
      qstrFilename = qfInfo.baseName();
      qstrFilename = qstrFilename.left(31 - qstrSuffix.length());
      qstrFilename += "." + qstrSuffix;
   }
   else
   {
      qstrFilename = p_qstrFilename;
   }

   return qstrFilename;
}

void CwnCommandUpdateBinaryDocument::interpretAnswer(QVariant &Ret)
{
    CwmsJson json;
    QString qstrJson;
    qstrJson.append(answer);
    QVariant parsedJson = json.parse(qstrJson);
    this->qResult = static_cast<const QVariantMap*>(parsedJson.data());

    //qDebug() << qstrJson;
    if(!parsedJson.isValid())
        this->qResult=nullptr;
    if(CwnCommandBase::checkForErrors(this->qResult,queryCausedError))
    {
        Ret=EC(eDmInvalidSelectStatement);

    }
    else
    {
        if(CwnCommandBase::getDataListPtr()->count()>0)
        {
            Ret=1;
        }
        else{
            ERR("Could not update Binary Document.");
            Ret = -1;
        }
    }
}
