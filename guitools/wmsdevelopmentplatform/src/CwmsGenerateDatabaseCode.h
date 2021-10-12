/******************************************************************************
 ** WOGRA technologies Gmbh & Co KG Modul Information
 ** Modulename: CwmsGenerateDatabaseCode.h
 ** Started Implementation: 2011/11/10
 ** Description:
 ** 
 ** This class generates the interface for the complete database
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co KG All rights reserved
 *****************************************************************************/ 

#ifndef CWMSGENERATEDATABASECODE_H
#define CWMSGENERATEDATABASECODE_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes
#include <QString>
#include <QVector>
#include <QList>
#include <QList>
#include <QMap>

// Own Includes
#include "CwmsCodeGeneratorC.h"

// Forwards
class CdmClass;
class CdmClassManager;

// TypeDefs


/* 
 * This class generates the interface for the complete database
 */
class CwmsGenerateDatabaseCode
{
   private:
      CdmClassManager* m_rpCdmClassManager;
      QString m_qstrClassPrefix;
      QString m_qstrDirectory;
      QVector<qint64> m_qvGeneratedClasses;
      QList<CdmClass*> m_qllNotGeneratedClasses;
      QMap<qint64, QString> m_qmClassNames;
      QMap<qint64, QString> m_qmFilenames;


   public:
   /** +-=---------------------------------------------------------Fr 11. Nov 18:16:09 2011-------*
    * @method  CwmsGenerateDatabaseCode::CwmsGenerateDatabaseCode // public                       *
    * @return                                                //                                   *
    * @param   CdmClassManager* p_pCdmClassManager           //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 11. Nov 18:16:09 2011----------*/
    CwmsGenerateDatabaseCode( CdmClassManager* p_pCdmClassManager);

   public:
   /** +-=---------------------------------------------------------Fr 11. Nov 18:16:24 2011-------*
    * @method  CwmsGenerateDatabaseCode::~CwmsGenerateDatabaseCode // public, virtual             *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CwmsGenerateDatabaseCode                                   *
    *----------------last changed: -----------------------------Fr 11. Nov 18:16:24 2011----------*/
    virtual ~CwmsGenerateDatabaseCode( );

   public:
   /** +-=---------------------------------------------------------Do 10. Nov 19:03:30 2011-------*
    * @method  CwmsGenerateDatabaseCode::GenerateDatabaseCode // public                           *
    * @return  void                                          //                                   *
    * @param   QString p_qstrDirectory                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 10. Nov 19:03:30 2011----------*/
    void GenerateDatabaseCode(QString p_qstrDirectory);

   public:
   /** +-=---------------------------------------------------------Do 10. Nov 19:03:59 2011-------*
    * @method  CwmsGenerateDatabaseCode::SetClassPrefix      // public                            *
    * @return  void                                          //                                   *
    * @param   QString p_qstrPrefix                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 10. Nov 19:03:59 2011----------*/
    void SetClassPrefix(QString p_qstrPrefix);

   private:
   /** +-=---------------------------------------------------------Do 10. Nov 19:06:05 2011-------*
    * @method  CwmsGenerateDatabaseCode::GenerateClassName   // private                           *
    * @return  QString                                       //                                   *
    * @param   QString p_qstrClass                           //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 10. Nov 19:06:05 2011----------*/
    QString GenerateClassName(QString p_qstrClass);


   private:
   /** +-=---------------------------------------------------------Do 10. Nov 19:17:36 2011-------*
    * @method  CwmsGenerateDatabaseCode::AreAllBaseClassesGenerated // private                    *
    * @return  bool                                          //                                   *
    * @param   QList<qint64> p_qllBaseClasses                  //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 10. Nov 19:17:36 2011----------*/
    bool AreAllBaseClassesGenerated(QList<qint64> p_qllBaseClasses);

   private:
   /** +-=---------------------------------------------------------Do 10. Nov 19:26:05 2011-------*
    * @method  CwmsGenerateDatabaseCode::GenerateClassCode   // private                           *
    * @return  void                                          //                                   *
    * @param   CdmClass* p_pCdmClass                         //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 10. Nov 19:26:05 2011----------*/
    void GenerateClassCode(CdmClass* p_pCdmClass);

   private:
   /** +-=---------------------------------------------------------Do 10. Nov 19:30:50 2011-------*
    * @method  CwmsGenerateDatabaseCode::AddBaseClassData    // private                           *
    * @return  void                                          //                                   *
    * @param   CdmClass* p_pCdmClass                         //                                   *
    * @param   CwmsCodeGeneratorC& p_rCwmsGenerator          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 10. Nov 19:30:50 2011----------*/
    void AddBaseClassData(CdmClass* p_pCdmClass, CwmsCodeGeneratorC& p_rCwmsGenerator);

   private:
   /** +-=---------------------------------------------------------Do 10. Nov 19:38:55 2011-------*
    * @method  CwmsGenerateDatabaseCode::GenerateNotCreatedClasses // private                     *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 10. Nov 19:38:55 2011----------*/
    void GenerateNotCreatedClasses();
};

#endif // CWMSGENERATEDATABASECODE_H
