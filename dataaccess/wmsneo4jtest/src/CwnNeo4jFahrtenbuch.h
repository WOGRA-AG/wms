#ifndef CWNNEO4JFAHRTENBUCH_H
#define CWNNEO4JFAHRTENBUCH_H

#include <QTest>
#include <QObject>

#include "CdmDataProvider.h"
#include "CumUserManager.h"

class CwnNeo4jFahrtenBuch : public QObject
{
    Q_OBJECT

private:
    CdmDataProvider* m_pCdmManager;
    CumUserManager* m_pCumManager;
    CdmClass* GetClassByName(CdmDataProvider* pCdmManager, QString qstrKeyname);

public:
    CwnNeo4jFahrtenBuch(QObject *parent = 0);

private slots:
    void initTestCase();
    void cleanupTestCase();
};

#endif // CWNNEO4JFAHRTENBUCH_H
