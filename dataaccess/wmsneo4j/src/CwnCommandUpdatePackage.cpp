#include "CwnCommandUpdatePackage.h"
#include "CdmPackage.h"
#include "CwnHelper.h"

#include "CwnCommandStdHeader.h"

CwnCommandUpdatePackage::CwnCommandUpdatePackage(CdmPackage *p_pPackage, CwnDataAccess *p_pDataAccess)
: CwnCommandBase(p_pDataAccess),
m_pPackage(p_pPackage)
{

}

CwnCommandUpdatePackage::~CwnCommandUpdatePackage()
{

}

QString CwnCommandUpdatePackage::createQuery()
{
    QString qstrSystemPackage = CwnHelper::ConvertBoolToString(m_pPackage->IsSystemPackage());
    QStringList piecesToChange = m_pPackage->GetPackageString().split(".");
    QStringList piecesOriginal = m_pPackage->GetOriginalPackgeString().split(".");
    bool parentPathChanged = false;

    if(piecesOriginal.count() < piecesToChange.count())
    {
        //Pfadverlängerung auf false gesetzt, da es nicht möglich sein sollte.
        parentPathChanged = false;
        notSupported = true;

    }
    else if(piecesOriginal.count() > piecesToChange.count())
    {
        //Pfadverkürzung auf false gesetzt, da es nicht möglich sein sollte.
        parentPathChanged = false;
        notSupported = true;
    }
    else if(piecesOriginal.count() == piecesToChange.count())
    {
        for(int i=0;i<piecesOriginal.count()-1;i++)
        {
            if(piecesOriginal[i] != piecesToChange[i])
            {
                //Ein Blatt wird unbenannt oder ein Knoten mit weiteren Kindern
                //Auf false gesetzt, da es nicht möglich sein sollte.
                parentPathChanged = false;
                notSupported = true;
                break;
            }
            else
            {
                //Ein Pfad wird bis zu einem Knoten  verändert
            }
        }
    }

    if(parentPathChanged)
    {
        QString uniquematch = QString("(s:Scheme)");

        for(int i=0;i<=piecesToChange.count()-1;i++)
        {
            uniquematch += QString("-[:pkglevel]->(:Package {URIname:\'%1\'})").arg(piecesToChange[i]);
        }

        QString changematch = QString("(q:Scheme)");

        for(int i=0;i<=piecesOriginal.count()-2;i++)
        {
            changematch += QString("-[:pkglevel]->(:Package {URIname:\'%1\'})").arg(piecesOriginal[i]);
        }

        changematch += QString("-[:pkglevel]->(k:Package {URIname:\'%1\'})").arg(piecesOriginal[piecesOriginal.count()-1]);

        QString changeMatchSchemeOrPackage;

        if(piecesOriginal.count()>1)
        {
            changeMatchSchemeOrPackage += QString("(:Package)-[l:pkglevel]->(k:Package)");
        }
        else
        {
            changeMatchSchemeOrPackage += QString("(:Scheme)-[l:pkglevel]->(k:Package)");
        }


        QString fatherOfChange;
        QString createStatement;

        if(piecesToChange.count()>1)
        {
            fatherOfChange += QString("(t:Scheme)");
            for(int i=0;i<=piecesToChange.count()-3;i++)
            {
                fatherOfChange  += QString("-[:pkglevel]->(:Package {URIname:\'%1\'})").arg(piecesToChange[i]);
            }

            fatherOfChange += QString("-[:pkglevel]->(f:Package {URIname:\'%1\'})").arg(piecesToChange[piecesToChange.count()-2]);
            createStatement = QString("WITH f,l,k CREATE (f)-[r:pkglevel]->(k) DELETE l");
        }
        else
        {
            fatherOfChange += QString("(t:Scheme)");
            createStatement = QString("WITH t,l,k CREATE (t)-[r:pkglevel]->(k) DELETE l");
        }

        QString query = QString("MATCH e=%1 WHERE id(s)=%2 WITH count(e) AS num WHERE num=0 MATCH %3 WHERE id(q)=%4 SET k.URIname=\'%5\', k.SystemPackage=\'%6\' WITH k MATCH %7 MATCH %8 WHERE id(t)=%9 %10;")
                .arg(uniquematch)
                .arg(m_pPackage->GetSchemeId())
                .arg(changematch)
                .arg(m_pPackage->GetSchemeId())
                .arg(piecesToChange[piecesToChange.count()-1])
                .arg(qstrSystemPackage)
                .arg(changeMatchSchemeOrPackage)
                .arg(fatherOfChange)
                .arg(m_pPackage->GetSchemeId())
                .arg(createStatement);
        return query;
    }
    else
    {
        if(notSupported)
            return QString("RETURN 1");

        // piecesToChange == piecesOriginal
        if(piecesToChange.count()>=1)
        {

            QString uniquematch = QString("(s:Scheme)");

            for(int i=0;i<=piecesToChange.count()-1;i++)
            {
                uniquematch += QString("-[:pkglevel]->(:Package {URIname:\'%1\'})").arg(piecesToChange[i]);
            }

            QString changematch = QString("(q:Scheme)");

            for(int i=0;i<=piecesOriginal.count()-2;i++)
            {
                changematch += QString("-[:pkglevel]->(:Package {URIname:\'%1\'})").arg(piecesOriginal[i]);
            }

            changematch += QString("-[:pkglevel]->(k:Package {URIname:\'%1\'})").arg(piecesOriginal[piecesOriginal.count()-1]);

            QString query = QString("MATCH e=%1 WHERE id(s)=%2 WITH count(e) AS num WHERE num=0 MATCH %3 WHERE id(q)=%4 SET k.URIname=\'%5\', k.SystemPackage=\'%6\' RETURN k;")
                    .arg(uniquematch)
                    .arg(m_pPackage->GetSchemeId())
                    .arg(changematch)
                    .arg(m_pPackage->GetSchemeId())
                    .arg(piecesToChange[piecesToChange.count()-1])
                    .arg(qstrSystemPackage);
            return query;
        }
        else if(piecesToChange.count() <1)
        {
            //Not possible
            return QString("42");
        }
    }
    //Not possible
    return QString("42");
}

void CwnCommandUpdatePackage::interpretAnswer(QVariant &Ret)
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
            if(notSupported)
            {
                Ret=-1;
                ERR("You can only rename the last Package keyname, of the given Package Hierachy String of keynames");
                return;
            }

            INFO("Package updated.");
            m_pPackage->ResetNewModified();
            Ret = EC(eDmOk);
        }
        else
        {
            Ret = -1;
            ERR("Could not update Package!");
        }
    }
}

int CwnCommandUpdatePackage::Execute()
{
    int iRet = EC(eDmUnknownSqlError);
    //qDebug() << createQuery();
    QString payload = createJson(createQuery());
    queryCausedError = payload;
    ConnectAndExecute(executeCommit,payload,nullptr,nullptr);
    QVariant Ret;
    interpretAnswer(Ret);
    iRet = Ret.toInt();
    return iRet;
}

bool CwnCommandUpdatePackage::CheckValid()
{
    return CHKPTR(m_pPackage);
}
