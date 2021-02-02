#ifndef CWNCOMMANDLICENCECHECK_H
#define CWNCOMMANDLICENCECHECK_H

#include "CwnCommandBase.h"
#include "CwnDataAccess.h"

class CwnCommandLicenceCheck : public CwnCommandBase
{
private:
    QString m_qstrApplication;
    bool m_bDemo;
    int m_iModules;
    QString m_qstrVersion;

    int ActiveSessionCount(QString p_qstrApplication);
    int CountMaxLicences(QString p_qstrApplication, bool &p_bDemo, int &p_iModules, QString p_qstrVersion);

public:
    CwnCommandLicenceCheck(QString p_qstrApplication, QString p_qstrVersion, CwnDataAccess* p_ppDataAccess);
    virtual ~CwnCommandLicenceCheck();
    bool IsDemo();
    int GetModules();

    QString createQueryForActiveSessionCount();
    QString createQueryForCountMaxLicences();

protected:
    void interpretAnswer(QVariant& Ret);
    virtual bool CheckValid();
    virtual int Execute();

};

#endif // CWNCOMMANDLICENCECHECK_H






