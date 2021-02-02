#ifndef CDBCOMMANDLICENCECHECK_H
#define CDBCOMMANDLICENCECHECK_H

#include "CftlAbstractCommand.h"

class CftlCommandLicenceCheck : public CftlAbstractCommand
{
private:
    QString m_qstrApplication;
    bool m_bDemo;
    int m_iModules;
    QString m_qstrVersion;

    int ActiveSessionCount(QString p_qstrApplication);
    int CountMaxLicences(QString p_qstrApplication, bool &p_bDemo, int &p_iModules, QString p_qstrVersion);
public:
    CftlCommandLicenceCheck(QString p_qstrApplication, QString p_qstrVersion, CftlDataAccess* p_ppDataAccess);
    virtual ~CftlCommandLicenceCheck();
    bool IsDemo();
    int GetModules();

protected:
    virtual bool CheckValid();
    virtual int Execute();
    virtual bool NeedsSessionCheck();
};

#endif // CDBCOMMANDLICENCECHECK_H
