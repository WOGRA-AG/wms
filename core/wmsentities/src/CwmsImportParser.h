/******************************************************************************
 ** WOGRA technologies Modul Information
 ** Modulename: CwmsImportParser.h
 ** Started Implementation: 2008/10/14
 ** Description:
 ** 
 ** This class implements the parserbaseclass
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies All rights reserved
 *****************************************************************************/ 

#ifndef CWMSIMPORTPARSER_H
#define CWMSIMPORTPARSER_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes
#include <QFile>

// Own Includes
#include "basetools.h"


// Forwards
class CwmsImport;
class CwmsImportSettings;
// Enumerations

/* 
 * This class implements the parserbaseclass
 */
class BASETOOLS_API CwmsImportParser
{
   protected:
      CwmsImportSettings* m_pCwmsImportSettings;
      QIODevice* m_pqDevice;

   public:
   /** +-=---------------------------------------------------------Di 14. Okt 20:57:45 2008-------*
    * @method  CwmsImportParser::CwmsImportParser            // public                            *
    * @return                                                //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 14. Okt 20:57:45 2008----------*/
    CwmsImportParser( );

   public:
   /** +-=---------------------------------------------------------Di 14. Okt 20:57:53 2008-------*
    * @method  CwmsImportParser::~CwmsImportParser           // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CwmsImportParser                                           *
    *----------------last changed: -----------------------------Di 14. Okt 20:57:53 2008----------*/
    virtual ~CwmsImportParser( );

   public:
   /** +-=---------------------------------------------------------Di 21. Okt 18:49:24 2008-------*
    * @method  CwmsImportParser::SetImportSettings           // public                            *
    * @return  void                                          //                                   *
    * @param   CwmsImportSettings* p_pImportSettings         //                                   *
    * @comment stes the importsettings.                                                           *
    *----------------last changed: -----------------------------Di 21. Okt 18:49:24 2008----------*/
    void SetImportSettings(CwmsImportSettings* p_pImportSettings);

   public:
   /** +-=---------------------------------------------------------Di 21. Okt 18:51:24 2008-------*
    * @method  CwmsImportParser::ParserFactory               // public, static                    *
    * @return  CwmsImportParser*                             //                                   *
    * @param   CwmsImportSettings* p_pImportSettings         //                                   *
    * @comment This method creates the correct importparser dependent from ImportSettings.        *
    *----------------last changed: -----------------------------Di 21. Okt 18:51:24 2008----------*/
    static CwmsImportParser* ParserFactory(CwmsImportSettings* p_pImportSettings);

   private:
   /** +-=---------------------------------------------------------Di 21. Okt 19:09:56 2008-------*
    * @method  CwmsImportParser::OpenDevice                  // private                           *
    * @return  bool                                          //                                   *
    * @comment This method opens the file.                                                        *
    *----------------last changed: -----------------------------Di 21. Okt 19:09:56 2008----------*/
    bool OpenDevice();

   protected:
   /** +-=---------------------------------------------------------Di 21. Okt 19:30:30 2008-------*
    * @method  CwmsImportParser::ParseLine                   // protected, p virtual              *
    * @return  QStringList                                   //                                   *
    * @param   QString p_qstrLine                            //                                   *
    * @comment This method parses one line.                                                       *
    *----------------last changed: -----------------------------Di 21. Okt 19:30:30 2008----------*/
    virtual QStringList ParseLine(QString p_qstrLine)= 0;

   public:
   /** +-=---------------------------------------------------------Di 21. Okt 19:58:01 2008-------*
    * @method  CwmsImportParser::ParseFile                   // public                            *
    * @return  void                                          //                                   *
    * @param   CwmsImport* p_pCwmsImport                     //                                   *
    * @comment This mehtod parses the complete file.                                              *
    *----------------last changed: -----------------------------Di 21. Okt 19:58:01 2008----------*/
    void ParseFile(CwmsImport* p_pCwmsImport);

   public:
   /** +-=---------------------------------------------------------Do 28. Feb 12:13:43 2013-------*
    * @method  CwmsImportParser::SetDevice                   // public                            *
    * @return  void                                          //                                   *
    * @param   QIODevice* p_pDevice                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 28. Feb 12:13:43 2013----------*/
    void SetDevice(QIODevice* p_pDevice);

   private:
   /** +-=---------------------------------------------------------Do 7. Mrz 14:06:05 2013--------*
    * @method  CwmsImportParser::CloseDevice                 // private                           *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 7. Mrz 14:06:05 2013-----------*/
    void CloseDevice();
};

#endif //
