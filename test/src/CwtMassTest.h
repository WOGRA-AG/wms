#ifndef CWTMASSTEST_H
#define CWTMASSTEST_H

#include <QtTest>
#include <QObject>

class CdmClass;
class CdmObjectContainer;

class CwtMassTest: public QObject
{
   Q_OBJECT
public:
    CwtMassTest();
private slots:
    void initTestCase();
    void MassDataTest();
    void cleanupTestCase();
private:
    CdmClass* CreateClass();
    void CreateData(CdmObjectContainer *p_pContainer);
    QStringList m_qstrlMembers;
    QString m_qstrDbName;
    QTime m_qTimeStart;
};

#endif // CWTMASSTEST_H
