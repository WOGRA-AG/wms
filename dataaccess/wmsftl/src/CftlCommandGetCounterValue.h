#ifndef CDBCOMMANDGETCOUNTERVALUE_H
#define CDBCOMMANDGETCOUNTERVALUE_H

#include "CftlAbstractTransactionalCommand.h"

// Forwards
class CdmValueCounter;

class CftlCommandGetCounterValue : public CftlAbstractTransactionalCommand
{
private:
    CdmValueCounter* m_rpCdmCounter;
    int m_iRecursionCount;
    bool CheckIncreaseCounterNeeded(int p_iCounter,
                                    QDateTime qdCurrentDateTime,
                                    QString p_qstrTableName,
                                    QString p_qstrFieldName,
                                    long p_lContainerId);
    int IncreaseCounterValue(int p_iCounter,
                             QDateTime qdCurrentDateTime,
                             QString p_qstrTableName,
                             QString p_qstrFieldName,
                             long p_lContainerId);

    int MakeCounterValueUnique(int p_iCounter,
                               QDateTime qdCurrentDateTime,
                               QString p_qstrTableName,
                               QString p_qstrFieldName,
                               long p_lContainerId);

    long GetCounterValue(const CdmObject* p_pObject);
public:
    CftlCommandGetCounterValue(CdmValueCounter* p_pCdmCounter, CftlDataAccess* p_pDataAccess);
    CftlCommandGetCounterValue(const CdmObjectContainer* p_pContainer, CdmValue* p_pValue, CftlDataAccess* p_pDataAccess);
    virtual ~CftlCommandGetCounterValue();

protected:
    bool CheckValid();
    int Execute();
};

#endif // CDBCOMMANDGETCOUNTERVALUE_H
