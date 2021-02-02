#ifndef CDBCOMMANDLICENCECHECK_H
#define CDBCOMMANDLICENCECHECK_H

#include "CdbAbstractCommand.h"

class CdbCommandLicenceCheck : public CdbAbstractCommand
{
private:
    QString m_qstrApplication;
    bool m_bDemo;
    int m_iModules;
    QString m_qstrVersion;

    int ActiveSessionCount(QString p_qstrApplication);
    int CountMaxLicences(QString p_qstrApplication, bool &p_bDemo, int &p_iModules, QString p_qstrVersion);
public:
    CdbCommandLicenceCheck(QString p_qstrApplication, QString p_qstrVersion, CdbDataAccess* p_ppDataAccess);
    virtual ~CdbCommandLicenceCheck();
    bool IsDemo();
    int GetModules();

protected:
    virtual bool CheckValid();
    virtual int Execute();
    virtual bool NeedsActiveSession();
};

#endif // CDBCOMMANDLICENCECHECK_H
