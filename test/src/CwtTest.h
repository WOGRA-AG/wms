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

#ifndef CWTTEST_H
#define CWTTEST_H

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
class CwtTest : public CwtTestBase
{
   Q_OBJECT

   private:
      QTime m_qTimeStart;
      long m_lObjectId;
      long m_lClassId;
      QTime m_qTestTimeWithPreparation;
      QDateTime m_qdTestDateTime;
      QString m_qstrDbName;
      int m_iObjectToCreate;
    public: static long mem;

   public:
   /** +-=---------------------------------------------------------Fr 20. Apr 10:40:12 2012-------*
    * @method  CwtTest::CwtTest                              // public                            *
    * @return                                                //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 20. Apr 10:40:12 2012----------*/
    CwtTest( );

   public:
   /** +-=---------------------------------------------------------Fr 20. Apr 10:40:20 2012-------*
    * @method  CwtTest::~CwtTest                             // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CwtTest                                                    *
    *----------------last changed: -----------------------------Fr 20. Apr 10:40:20 2012----------*/
    virtual ~CwtTest( );

    private slots:
    /** +-=---------------------------------------------------------Do 26. Apr 11:11:02 2012-------*
    * @method  CwtTest::initTestCase                         // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 26. Apr 11:11:02 2012----------*/
    void initTestCase( );

    private slots:
    /** +-=---------------------------------------------------------Do 26. Apr 11:11:20 2012-------*
    * @method  CwtTest::cleanupTestCase                      // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 26. Apr 11:11:20 2012----------*/
    void cleanupTestCase( );

    private slots:
    /** +-=---------------------------------------------------------Mi 23. Mai 14:53:09 2012-------*
     * @method  CwtTest::FindAdminUserSlot                    // private, slots                    *
     * @return  void                                          //                                   *
     * @comment                                                                                    *
     *----------------last changed: -----------------------------Mi 23. Mai 14:53:09 2012----------*/
    void FindAdminUserSlot( );

    private slots:
   /** +-=---------------------------------------------------------Do 10. Mai 19:12:21 2012-------*
    * @method  CwtTest::CheckDatabaseListSlot                // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 10. Mai 19:12:21 2012----------*/
void CheckDatabaseListSlot( );

    private slots:
   /** +-=---------------------------------------------------------Mi 6. Feb 10:19:33 2013--------*
    * @method  CwtTest::CheckUser                            // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 6. Feb 10:19:33 2013-----------*/
void CheckUser( );

    private slots:
   /** +-=---------------------------------------------------------Mi 6. Feb 10:19:43 2013--------*
    * @method  CwtTest::CheckUserGroup                       // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 6. Feb 10:19:43 2013-----------*/
void CheckUserGroup( );

    private slots:
    /** +-=---------------------------------------------------------Fr 20. Apr 11:37:25 2012-------*
    * @method  CwtTest::LoadDatabaseSlot                     // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 20. Apr 11:37:25 2012----------*/
    void LoadDatabaseSlot( );

    private slots:
    /** +-=---------------------------------------------------------Mo 23. Apr 15:33:08 2012-------*
    * @method  CwtTest::CreateClassSlot                      // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 23. Apr 15:33:08 2012----------*/
    void CreateClassSlot( );

    private slots:
    /** +-=---------------------------------------------------------Mo 10. Dez 15:26:15 2012-------*
    * @method  CwtTest::CheckClassUrisSlot                   // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 10. Dez 15:26:15 2012----------*/
    void CheckClassUrisSlot( );

    private slots:
   /** +-=---------------------------------------------------------Fr 20. Apr 11:33:53 2012-------*
    * @method  CwtTest::CreateObjectListSlot                 // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 20. Apr 11:33:53 2012----------*/
   void CreateObjectListSlot( );

   private slots:
   /** +-=---------------------------------------------------------Sa 28. Apr 13:04:21 2012-------*
   * @method  CwtTest::CreateObjectByWebServiceSlot                     // private, slots                    *
   * @return  void                                          //                                   *
   * @comment                                                                                    *
   *----------------last changed: -----------------------------Sa 28. Apr 13:04:21 2012----------*/
   void CreateObjectByWebServiceSlot( );

   private slots:
   /** +-=---------------------------------------------------------Sa 28. Apr 13:04:21 2012-------*
   * @method  CwtTest::CreateObjectSlot                     // private, slots                    *
   * @return  void                                          //                                   *
   * @comment                                                                                    *
   *----------------last changed: -----------------------------Sa 28. Apr 13:04:21 2012----------*/
   void CreateObjectSlot( );

   private slots:
   /** +-=---------------------------------------------------------Sa 28. Apr 13:05:16 2012-------*
   * @method  CwtTest::LoadObjectSlot                       // private, slots                    *
   * @return  void                                          //                                   *
   * @comment                                                                                    *
   *----------------last changed: -----------------------------Sa 28. Apr 13:05:16 2012----------*/
   void LoadObjectSlot( );

    private slots:
   /** +-=---------------------------------------------------------Do 3. Mai 11:04:30 2012--------*
    * @method  CwtTest::QueryTestSlotAnd                     // private, slots                    *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 3. Mai 11:04:30 2012-----------*/
void QueryTestSlotAnd( );

   private slots:
   /** +-=---------------------------------------------------------Do 3. Mai 11:04:49 2012--------*
   * @method  CwtTest::QueryTestSlotOr                      // private, slots                    *
   * @return  void                                          //                                   *
   * @comment                                                                                    *
   *----------------last changed: -----------------------------Do 3. Mai 11:04:49 2012-----------*/
   void QueryTestSlotOr( );

   private slots:
   /** +-=---------------------------------------------------------Do 3. Mai 11:08:29 2012--------*
   * @method  CwtTest::QueryTestSlotAndOneWrong             // private, slots                    *
   * @return  void                                          //                                   *
   * @comment                                                                                    *
   *----------------last changed: -----------------------------Do 3. Mai 11:08:29 2012-----------*/
   void QueryTestSlotAndOneWrong( );

   private slots:
   /** +-=---------------------------------------------------------Do 3. Mai 11:08:56 2012--------*
   * @method  CwtTest::QueryTestSlotOrOneWrong              // private, slots                    *
   * @return  void                                          //                                   *
   * @comment                                                                                    *
   *----------------last changed: -----------------------------Do 3. Mai 11:08:56 2012-----------*/
   void QueryTestSlotOrOneWrong( );

   private slots:
   /** +-=---------------------------------------------------------Do 3. Mai 11:13:40 2012--------*
   * @method  CwtTest::QueryTestSlotAndBothWrong            // private, slots                    *
   * @return  void                                          //                                   *
   * @comment                                                                                    *
   *----------------last changed: -----------------------------Do 3. Mai 11:13:40 2012-----------*/
   void QueryTestSlotAndBothWrong( );

   private slots:
   /** +-=---------------------------------------------------------Do 3. Mai 11:14:01 2012--------*
   * @method  CwtTest::QueryTestSlotOrBothWrong             // private, slots                    *
   * @return  void                                          //                                   *
   * @comment                                                                                    *
   *----------------last changed: -----------------------------Do 3. Mai 11:14:01 2012-----------*/
   void QueryTestSlotOrBothWrong( );
   
   private slots:
   /** +-=---------------------------------------------------------Mi 2. Mai 10:57:44 2012--------*
   * @method  CwtTest::QueryEnhancedTestSlot                // private, slots                    *
   * @return  void                                          //                                   *
   * @comment                                                                                    *
   *----------------last changed: -----------------------------Mi 2. Mai 10:57:44 2012-----------*/
   void QueryEnhancedTestSlot( );

   private slots:
   /** +-=---------------------------------------------------------Sa 28. Apr 13:04:30 2012-------*
   * @method  CwtTest::DeleteObjectSlot                     // private, slots                    *
   * @return  void                                          //                                   *
   * @comment                                                                                    *
   *----------------last changed: -----------------------------Sa 28. Apr 13:04:30 2012----------*/
   void DeleteObjectSlot( );

   private slots:
   /** +-=---------------------------------------------------------Sa 28. Apr 13:04:47 2012-------*
   * @method  CwtTest::DeleteObjectListSlot                 // private, slots                    *
   * @return  void                                          //                                   *
   * @comment                                                                                    *
   *----------------last changed: -----------------------------Sa 28. Apr 13:04:47 2012----------*/
   void DeleteObjectListSlot( );

   private slots:
   /** +-=---------------------------------------------------------Sa 28. Apr 13:04:57 2012-------*
   * @method  CwtTest::DeleteClassSlot                      // private, slots                    *
   * @return  void                                          //                                   *
   * @comment                                                                                    *
   *----------------last changed: -----------------------------Sa 28. Apr 13:04:57 2012----------*/
   void DeleteClassSlot( );

   private slots:
   /** +-=---------------------------------------------------------Sa 28. Apr 13:17:59 2012-------*
   * @method  CwtTest::DeleteDatabaseSlot                   // private, slots                    *
   * @return  void                                          //                                   *
   * @comment                                                                                    *
   *----------------last changed: -----------------------------Sa 28. Apr 13:17:59 2012----------*/
   void DeleteDatabaseSlot( );

   private slots:
   /** +-=---------------------------------------------------------Fr 20. Apr 10:49:29 2012-------*
   * @method  CwtTest::LogoutSlot                           // private, slots                    *
   * @return  void                                          //                                   *
   * @comment                                                                                    *
   *----------------last changed: -----------------------------Fr 20. Apr 10:49:29 2012----------*/
   void LogoutSlot( );





   private:
   /** +-=---------------------------------------------------------Do 3. Mai 11:11:11 2012--------*
    * @method  CwtTest::AddQueryElements                     // private                           *
    * @return  void                                          //                                   *
    * @param   CdmQuery& p_rQuery                            //                                   *
    * @param   EdmQueryElementType p_eType                   //                                   *
    * @param   QString p_qstrString                          //                                   *
    * @param   int p_iInt                                    //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 3. Mai 11:11:11 2012-----------*/
    void AddQueryElements(CdmQuery& p_rQuery,
                          EdmQueryElementType p_eType,
                          QString p_qstrString,
                          int p_iInt);



   private:
   /** +-=---------------------------------------------------------Do 3. Mai 11:07:23 2012--------*
    * @method  CwtTest::AddQueryElementsOneWrong             // private                           *
    * @return  void                                          //                                   *
    * @param   CdmQuery& p_rQuery                            //                                   *
    * @param   EdmQueryElementType p_eType                   //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 3. Mai 11:07:23 2012-----------*/
    void AddQueryElementsOneWrong(CdmQuery& p_rQuery, EdmQueryElementType p_eType);



   private:
   /** +-=---------------------------------------------------------Do 3. Mai 11:10:33 2012--------*
    * @method  CwtTest::AddQueryElementsBothWrong            // private                           *
    * @return  void                                          //                                   *
    * @param   CdmQuery& p_rQuery                            //                                   *
    * @param   EdmQueryElementType p_eType                   //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 3. Mai 11:10:33 2012-----------*/
    void AddQueryElementsBothWrong(CdmQuery& p_rQuery, EdmQueryElementType p_eType);

   private:
   /** +-=---------------------------------------------------------Do 3. Mai 11:10:54 2012--------*
    * @method  CwtTest::AddQueryElementsRight                // private                           *
    * @return  void                                          //                                   *
    * @param   CdmQuery& p_rQuery                            //                                   *
    * @param   EdmQueryElementType p_eType                   //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 3. Mai 11:10:54 2012-----------*/
    void AddQueryElementsRight(CdmQuery& p_rQuery, EdmQueryElementType p_eType);




};

#endif // CWTTEST_H
