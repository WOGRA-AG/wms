/******************************************************************************
 ** WOGRA technologies Gmbh & Co KG Modul Information
 ** Modulename: CwtTest.h
 ** Started Implementation: 2013/10/06
 ** Description:
 **
 **
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 **(C) copyright by WOGRA technologies GmbH & Co KG All rights reserved
 *****************************************************************************/

#ifndef CWTCLASSTEST_H
#define CWTCLASSTEST_H

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
class CwtClass : public CwtTestBase
{
    Q_OBJECT

public:
    CwtClass();
    virtual ~CwtClass();

private slots:
    void initTestCase();
    void cleanupTestCase();
    void init();
    void cleanup();
    void CreateAndDeleteSimpleClass();
    void UpdateClassRenameMemberKeyname();
    void UpdateClassRenameMemberCaption();
    void UpdateClassChangeType();
    void UpdateClassRenameMemberKeynameAndChangeType();
    void UpdateClassDeleteMember();
    void UpdateClassChangeKeyname();
    void UpdateClassChangeClassCaptionAndComment();
    void CheckClassUris();
    void CheckGroups();
    void CheckMethods();
    void CheckBaseClass();
    void CheckLoopingBaseClass();
    void AddMemberWithTheSameName();
    void CheckTranslations();
    void CheckMemberRights();
    void CheckIsInherited();
    void MemberSequenceTest();
    void CreateClassesWithTheSameName();
    void AddClassToPackage();
    void TryVeryLongClassName();
    void TryVeryLongPackageQueueClass();
    void TryVeryLongMemberName();

    void AddMethodStaticPublic();
    void UpdateClassChangeMemberType();
    void UpdateClassAfterReset();
private:
    void CheckDiamondProblemSlot(); // test not yet implemented
};

#endif //
