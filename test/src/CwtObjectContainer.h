
#ifndef CwtObjectContainerTest_H
#define CwtObjectContainerTest_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes
#include <QtTest>
#include <QObject>
#include <QDateTime>

// WMS Includes
#include "CdmQuery.h"
#include "CdmQueryElement.h"

// Own Includes
#include "CwtTestBase.h"

// Forwards
class CdmScheme;
class CdmManager;
class CdmClassManager;
class CdmContainerManager;

// TypeDefs



/*
 * This class implements the main test class which starts all tests
 */
class CwtObjectContainer: public CwtTestBase
{
    Q_OBJECT

private:
    CdmClass* m_pClass;

    void CreateTestClass();
public:

    CwtObjectContainer();
    virtual ~CwtObjectContainer();

private slots:
    void initTestCase();
    void cleanupTestCase();
    void init();
    void cleanup();
    void CheckContainerClass();
    void CreateAndDeleteContainer();
    void FindContainerById();
    void FindContainerByKeyname();
    void FindContainerByUri();
    void FindContainerByUriInternal();
    void RemoveContainerLocally();
    void RemoveAllContainerLocally();
    void CheckUniqueName();
    void GetContainerList();
    void CreateAndDeleteObject();
    void CheckConfigItems();
    void FindContainerWithObject();
    void FindContainerWithoutObjects();
    void CopyContainer();
    void CreateTreeContainer();
    void CreateAndDeleteContainerOverContainerManager();
};

#endif // CwtObjectContainerTest_H
