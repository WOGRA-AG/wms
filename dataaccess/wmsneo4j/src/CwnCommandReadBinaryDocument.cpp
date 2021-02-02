#include "CdmValueBinaryDocument.h"

#include "CwnCommandReadBinaryDocument.h"

#include "CwnCommandStdHeader.h"


CwnCommandReadBinaryDocument::CwnCommandReadBinaryDocument(CdmValueBinaryDocument* p_pCdmBinaryDocument, CwnDataAccess* p_pDataAccess)
    : CwnCommandBase(p_pDataAccess),
      m_rpCdmBinaryDocument(p_pCdmBinaryDocument)
{
}

CwnCommandReadBinaryDocument::~CwnCommandReadBinaryDocument()
{

}

bool CwnCommandReadBinaryDocument::CheckValid()
{
    return CHKPTR(m_rpCdmBinaryDocument);
}

QString CwnCommandReadBinaryDocument::createQuery()
{
    QString query = QString("MATCH (v:WMS_VALUE) WHERE id(v)=%1 RETURN v.val,v.filetype,v.filename;")
                 .arg(m_rpCdmBinaryDocument->GetId());
    return query;
}

int CwnCommandReadBinaryDocument::Execute()
{
    int iRet = EC(eDmUnknownSqlError);
    QString payload = createJson(createQuery());
    queryCausedError = payload;
    ConnectAndExecute(executeCommit,payload,nullptr,nullptr);
    QVariant Ret;
    interpretAnswer(Ret);
    iRet = Ret.toInt();
    return iRet;
}

void CwnCommandReadBinaryDocument::interpretAnswer(QVariant &Ret)
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
        const QVariantList* dataList=CwnCommandBase::getDataListPtr();
        if(dataList->count()>0)
        {
            const QVariantMap* rowTemp = static_cast<const QVariantMap*>(dataList->at(0).data());
            const QVariantList* list = static_cast<const QVariantList*>(rowTemp->find("row")->data());


            QString qString64 = list->at(0).toString();
            QString qstrFilename = list->at(2).toString();
            QString qstrFiletype = list->at(1).toString();
            m_rpCdmBinaryDocument->SetFilenameAndTypeWithoutModifyingValue(qstrFilename, qstrFiletype);
            m_qByteArray = QByteArray::fromBase64(qString64.toLocal8Bit());
            Ret = EC(eDmOk);
        }
        else{
            ERR("VALUE is corrupt");
            Ret = -1;
        }
    }
}

QByteArray CwnCommandReadBinaryDocument::GetByteArray()
{
    return m_qByteArray;
}
