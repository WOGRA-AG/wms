/******************************************************************************
 ** WOGRA technologies Gmbh & Co KG Modul Information
 ** Modulename: CwtObject.h
 ** Started Implementation: 2012/04/20
 ** Description:
 **
 **
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 **(C) copyright by WOGRA technologies GmbH & Co KG All rights reserved
 *****************************************************************************/

#ifndef CwtObject_H
#define CwtObject_H

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





/*
 * This class implements the main test class which starts all tests
 */
class CwtObject : public CwtTestBase
{
    Q_OBJECT

private:


    QString m_qstrDbName;
    int m_iObjectToCreate;
   qint64 m_lObjectId;
    QString m_qstrObjectKeyname;
    QDateTime m_qdtDateTime;

public:

    CwtObject();
    virtual ~CwtObject();



private slots:
    void initTestCase();
    void cleanupTestCase();
    void CreateObjectSlot();
    void LoadObjecByIdSlot();
    void LoadObjecByKeynametSlot();
    void DeleteObjectSlot();
    void init();
    void cleanup();
    void DoubleTestSlot();
    void FloatTestSlot();
    void OwnershipTest();
    void DeleteOwnershipObjectTest();
    void IsTypeOfTest();
    void FindObjectByIndexTest();
    void FormulaTest();
    void CheckListContentSlot();
    void CheckMapContentSlot();
    void LockObjectSlot();
    void BinDocTestSlot();
    void CreateObjectChangeMemberTypeAndDeleteObject();
    void CreateObjectSetUniqueCaptionMemberAndSearchForKeyname();
    void CreateObjectSetNotUniqueCaptionMemberAndSearchForKeyname();
};

#endif // CwtObject_H
