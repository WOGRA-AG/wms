/******************************************************************************
 ** WOGRA technologies Modul Information
 ** Modulename: CwmsImport.h
 ** Started Implementation: 2008/10/21
 ** Description:
 ** 
 ** This class implements the unified import to wms.
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies All rights reserved
 *****************************************************************************/ 

#ifndef CWMSIMPORT_H
#define CWMSIMPORT_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes
#include <QStringList>
#include <QMap>
#include <QPair>

// Own Includes
#include "basetools.h"
#include "CwmsImportSettings.h"


// WMS Includes
#include "CdmQuery.h"
#include "CdmQueryElement.h"

// Forwards
class CdmObject;
class CdmObjectContainer;
class CwmsImportParser;

// Typedefs
typedef QPair<QString,QString> TStringPair;

// Enumerations

/* 
 * This class implements the unified import to wms
 */
class BASETOOLS_API CwmsImport
{
   protected:
      CwmsImportSettings m_cCwmsImportSettings;
      QString m_qstrImportMessages;
      QStringList m_qstrlHiddenMembers;
      QMap<QString, TStringPair> m_qmDefaultValues;
      CwmsImportParser* m_pParser;
      bool m_bDisplayProgress;


   public:
   /** +-=---------------------------------------------------------Di 21. Okt 19:45:45 2008-------*
    * @method  CwmsImport::CwmsImport                        // public                            *
    * @return                                                //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 21. Okt 19:45:45 2008----------*/
    CwmsImport( );

   public:
   /** +-=---------------------------------------------------------Di 21. Okt 19:45:54 2008-------*
    * @method  CwmsImport::~CwmsImport                       // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CwmsImport                                                 *
    *----------------last changed: -----------------------------Di 21. Okt 19:45:54 2008----------*/
    virtual ~CwmsImport( );

   public:
   /** +-=---------------------------------------------------------Fr 8. Feb 14:12:03 2013--------*
    * @method  CwmsImport::CreateData                        // public, virtual                   *
    * @return  bool                                          //                                   *
    * @param   QStringList p_qsrlParsedData                  //                                   *
    * @comment This method saves the parsed data to the wems dependent from the settings.         *
    *----------------last changed: -----------------------------Fr 8. Feb 14:12:03 2013-----------*/
    virtual bool CreateData(QStringList p_qsrlParsedData);

   public:
   /** +-=---------------------------------------------------------Do 7. Feb 09:19:23 2013--------*
    * @method  CwmsImport::StartImport                       // public                            *
    * @return  void                                          //                                   *
    * @param   QString p_qstrSettingsFile                    //                                   *
    * @param   CdmObjectContainer* p_pList                        //                                   *
    * @comment This method starts the import with the overgiven settingsfilename                  *
    *----------------last changed: -----------------------------Do 7. Feb 09:19:23 2013-----------*/
    void StartImport(QString p_qstrSettingsFile, CdmObjectContainer* p_pList);

   public:
   /** +-=---------------------------------------------------------Mi 22. Okt 18:36:55 2008-------*
    * @method  CwmsImport::GetObjectList                     // public                            *
    * @return  CdmObjectContainer*                                //                                   *
    * @comment returns the objectlist for the import.                                             *
    *----------------last changed: -----------------------------Mi 22. Okt 18:36:55 2008----------*/
    CdmObjectContainer* GetObjectList();

   public:
   /** +-=---------------------------------------------------------Mi 22. Okt 19:01:39 2008-------*
    * @method  CwmsImport::GetObject                         // public                            *
    * @return  CdmObject*                                    //                                   *
    * @param   QStringList qstrlParseData                    //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 22. Okt 19:01:39 2008----------*/
    CdmObject* GetObject(QStringList qstrlParseData);

   public:
   /** +-=---------------------------------------------------------Mi 22. Okt 18:56:56 2008-------*
    * @method  CwmsImport::GetImportMessages                 // public                            *
    * @return  QString                                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 22. Okt 18:56:56 2008----------*/
    QString GetImportMessages();

   private:
   /** +-=---------------------------------------------------------Mi 22. Okt 19:01:22 2008-------*
    * @method  CwmsImport::ExecuteObjectQuery                // private                           *
    * @return  CdmObject*                                    //                                   *
    * @param   QStringList p_rqstrlParseData                 //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 22. Okt 19:01:22 2008----------*/
    CdmObject* ExecuteObjectQuery(QStringList p_rqstrlParseData);

   private:
   /** +-=---------------------------------------------------------Mi 22. Okt 19:21:48 2008-------*
    * @method  CwmsImport::CreateQuery                       // private                           *
    * @return  void                                          //                                   *
    * @param   CdmQuery& p_rCdmQuery                         //                                   *
    * @param   QStringList p_qstrlParseData                  //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 22. Okt 19:21:48 2008----------*/
    void CreateQuery(CdmQuery& p_rCdmQuery, QStringList p_qstrlParseData);

   public:
   /** +-=---------------------------------------------------------Do 7. Feb 09:21:52 2013--------*
    * @method  CwmsImport::StartImport                       // public                            *
    * @return  void                                          //                                   *
    * @param   CdmObjectContainer* p_pContainer               // the target objectlist.            *
    * @param   CwmsImportSettings p_cwmsImportSettings       //                                   *
    * @comment This method starts the import with the overgiven settingsfilename                  *
    *----------------last changed: -----------------------------Do 7. Feb 09:21:52 2013-----------*/
    void StartImport(CdmObjectContainer* p_pContainer, CwmsImportSettings p_cwmsImportSettings);

   public:
   /** +-=---------------------------------------------------------Fr 31. Okt 18:14:45 2008-------*
    * @method  CwmsImport::AddHiddenMember                   // public                            *
    * @return  void                                          //                                   *
    * @param   QString p_qstrMember                          //                                   *
    * @comment This method adds hidden members for the import.                                    *
    *----------------last changed: -----------------------------Fr 31. Okt 18:14:45 2008----------*/
    void AddHiddenMember(QString p_qstrMember);

   public:
   /** +-=---------------------------------------------------------Fr 31. Okt 18:16:23 2008-------*
    * @method  CwmsImport::GetHiddenMembersList              // public                            *
    * @return  QStringList                                   //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 31. Okt 18:16:23 2008----------*/
    QStringList GetHiddenMembersList();

   public:
   /** +-=---------------------------------------------------------Sa 1. Nov 11:01:11 2008--------*
    * @method  CwmsImport::AddDefaultValues                  // public                            *
    * @return  void                                          //                                   *
    * @param   QString p_qstrKeyname                         //                                   *
    * @param   QString p_qstrValue1                          //                                   *
    * @param   QString p_qstrValue2                          //                                   *
    * @comment This method adds the default values for importing values.                          *
    *----------------last changed: -----------------------------Sa 1. Nov 11:01:11 2008-----------*/
    void AddDefaultValues(QString p_qstrKeyname, QString p_qstrValue1, QString p_qstrValue2);

   public:
   /** +-=---------------------------------------------------------Sa 1. Nov 10:38:27 2008--------*
    * @method  CwmsImport::SetDefaultValuesToObject          // public                            *
    * @return  void                                          //                                   *
    * @param   CdmObject* p_pCdmObject                       //                                   *
    * @comment This method sets the default values to the object.                                 *
    *----------------last changed: -----------------------------Sa 1. Nov 10:38:27 2008-----------*/
    void SetDefaultValuesToObject(CdmObject* p_pCdmObject);

   public:
   /** +-=---------------------------------------------------------Sa 10. Jan 14:12:19 2009-------*
    * @method  CwmsImport::Commit                            // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment This method saves the import.                                                      *
    *----------------last changed: -----------------------------Sa 10. Jan 14:12:19 2009----------*/
    virtual void Commit();


   public:
   /** +-=---------------------------------------------------------Do 7. Feb 12:34:56 2013--------*
    * @method  CwmsImport::GetSettings                       // public                            *
    * @return  CwmsImportSettings&                           //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 7. Feb 12:34:56 2013-----------*/
    CwmsImportSettings& GetSettings();

   public:
   /** +-=---------------------------------------------------------Do 28. Feb 12:22:03 2013-------*
    * @method  CwmsImport::CreateParser                      // public                            *
    * @return  CwmsImportParser*                             //                                   *
    * @param   QString p_qstrSettingsFile                    //                                   *
    * @param   CdmObjectContainer* p_pList                        //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 28. Feb 12:22:03 2013----------*/
    CwmsImportParser* CreateParser(QString p_qstrSettingsFile, CdmObjectContainer* p_pList);

   public:
   /** +-=---------------------------------------------------------Do 28. Feb 12:36:12 2013-------*
    * @method  CwmsImport::CreateParser                      // public                            *
    * @return  CwmsImportParser*                             //                                   *
    * @param   CwmsImportSettings p_cwmsImportSettings       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 28. Feb 12:36:12 2013----------*/
    CwmsImportParser* CreateParser(CwmsImportSettings p_cwmsImportSettings);

   public:
   /** +-=---------------------------------------------------------Do 28. Feb 12:39:08 2013-------*
    * @method  CwmsImport::SetDipslayProgress                // public                            *
    * @return  void                                          //                                   *
    * @param   bool p_bDisplay                               //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 28. Feb 12:39:08 2013----------*/
    void SetDipslayProgress(bool p_bDisplay);

   public:
   /** +-=---------------------------------------------------------Do 28. Feb 12:39:33 2013-------*
    * @method  CwmsImport::GetDisplayProgress                // public                            *
    * @return  bool                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 28. Feb 12:39:33 2013----------*/
    bool GetDisplayProgress();
};

#endif //
