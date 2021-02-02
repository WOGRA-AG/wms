#ifndef CWNCOMMANDUPDATESCHEME_H
#define CWNCOMMANDUPDATESCHEME_H

#include "CwnCommandBase.h"

#include <QVariant>
#include <QString>

class CdmScheme;

class CwnCommandUpdateScheme : public CwnCommandBase
{
private:
    CdmScheme* m_rpScheme;
public:
    CwnCommandUpdateScheme(CdmScheme* p_pScheme, CwnDataAccess* p_pDataAccess);
    virtual ~CwnCommandUpdateScheme();

    QString createQuery();
    QString queryCausedError;

protected:
    void interpretAnswer(QVariant& Ret);
    virtual int Execute();
    virtual bool CheckValid();

};

#endif // CWNCOMMANDUPDATESCHEME_H

