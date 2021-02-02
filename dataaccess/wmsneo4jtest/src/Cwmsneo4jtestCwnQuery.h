#ifndef CWMSNEO4JTESTCWNQUERY_H
#define CWMSNEO4JTESTCWNQUERY_H

#include <QTest>
#include <QObject>

#include "CumUserManager.h"
#include "CdmDataProvider.h"

class Cwmsneo4jtestCwnQuery : public QObject
{
    Q_OBJECT
public:
    explicit Cwmsneo4jtestCwnQuery(QObject *parent = 0);
    CdmDataProvider* m_pCdmManager;
    CumUserManager* m_pCumManager;

private slots:
    void initTestCase();
    void cleanupTestCase();
};

#endif // CWMSNEO4JTESTCWNQUERY_H
