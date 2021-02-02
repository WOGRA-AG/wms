/******************************************************************************
 ** WOGRA technologies Gmbh & Co KG Modul Information
 ** Modulename: CwtTest.h
 ** Started Implementation: 2012/04/20
 ** Description:
 **
 **
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 **(C) copyright by WOGRA technologies GmbH & Co KG All rights reserved
 *****************************************************************************/

#ifndef CWTDATABASETEST_H
#define CWTDATABASETEST_H

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

// own Includes
#include "CwtTest.h"
#include "CwtTestBase.h"

// Forwards
class CdmScheme;
class CdmManager;
class CdmClassManager;
class CdmContainerManager;

// TypeDefs

// enums


/* 
 * This class implements the main test class which starts all tests
 */
class CwtScheme : public CwtTestBase
{
    Q_OBJECT


public:
    CwtScheme();
    virtual ~CwtScheme();


private slots:
    void initTestCase();
    void cleanupTestCase();
    void init();
    void cleanup();
    void CreateAndDeleteScheme();
    void CheckSchemeListSlot();
    void LoadSchemeSlot();
    void TryToLoadNotExistingSchemeSlot();
    void AddLanguagesToScheme();
    void TryToCreateTwoSchemesWithTheSameName();
    void AddTheSameLanguageTwice();
    void UpdateVersion();
};

#endif // CWTDATABASETEST_H
