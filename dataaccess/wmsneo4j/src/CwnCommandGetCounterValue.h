#ifndef CWNCOMMANDGETCOUNTERVALUE_H
#define CWNCOMMANDGETCOUNTERVALUE_H

#include "CwnCommandBase.h"

// Forwards
class CdmValueCounter;

class CwnCommandGetCounterValue : public CwnCommandBase
{
private:
    CdmValueCounter* m_rpCdmCounter;
    long m_lObjectListId;
    long m_lValueId;
    QString m_qstrKeyname;

    QString queryCausedError;


    bool CheckIncreaseCounterNeeded(int p_iCounter, int p_iTimeStamp, QString p_qstrKeyname, int p_lObjectId, int);
    int IncreaseCounterValue(int p_iCounter, int p_iTimeStamp, QString p_qstrKeyname, int p_lObjectId, int p_iValueId);
    int MakeCounterValueUnique(int p_iCounter, int p_iTimeStamp, QString p_qstrKeyname, int p_lObjectId, int p_iValueId);
    long GetCounterValue(long p_lObjectListId, long p_lValueId, QString p_qstrKeyname);
public:
    CwnCommandGetCounterValue(CdmValueCounter* p_pCdmCounter, CwnDataAccess* p_pDataAccess);
    CwnCommandGetCounterValue(long p_lObjectListId, long p_lValueId, QString p_qstrKeyname, CwnDataAccess* p_pDataAccess);
    virtual ~CwnCommandGetCounterValue();

protected:
    void interpretAnswer(QVariant& Ret);
    virtual int Execute();
    virtual bool CheckValid();
};

#endif // CwnCOMMANDGETCOUNTERVALUE_H
