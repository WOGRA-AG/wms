/******************************************************************************
 ** WOGRA technologies Gmbh & Co KG Modul Information
 ** Modulename: CwmsScriptablePrinter.h
 ** Started Implementation: 2012/11/09
 ** Description:
 ** 
 ** implements the script interface for js methods using print
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co KG All rights reserved
 *****************************************************************************/ 

#ifndef CWMSSCRIPTABLEPRINTER_H
#define CWMSSCRIPTABLEPRINTER_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes
#include <QScriptable>
#include <QObject>

// Own Includes
#include "basetools.h"
#include "CwmsScriptableBase.h"
#include "CwmsReportManager.h"

// Forwards
class CsaObject;
class CsaObjectContainer;
class CdmQueryEnhanced;

// TypeDefs


/* 
 * This class implements the script interface for js methods using print
 */
class BASETOOLS_API CwmsScriptablePrinter : public CwmsScriptableBase
{
   Q_OBJECT

   public:
   /** +-=---------------------------------------------------------Di 13. Nov 11:35:33 2012-------*
    * @method  CwmsScriptablePrinter::CwmsScriptablePrinter  // public                            *
    * @return                                                //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 13. Nov 11:35:33 2012----------*/
    CwmsScriptablePrinter( );

   public:
   /** +-=---------------------------------------------------------Di 13. Nov 11:35:41 2012-------*
    * @method  CwmsScriptablePrinter::~CwmsScriptablePrinter // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CwmsScriptablePrinter                                      *
    *----------------last changed: -----------------------------Di 13. Nov 11:35:41 2012----------*/
    virtual ~CwmsScriptablePrinter( );

    public slots:
         /** +-=---------------------------------------------------------Di 13. Nov 11:35:59 2012-------*
    * @method  CwmsScriptablePrinter::Print                  // public, slots                     *
    * @return  void                                          //                                   *
    * @param   CsaObject* p_pCsaObject                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 13. Nov 11:35:59 2012----------*/
void print( CsaObject* p_pCsaObject);

    public slots:
         /** +-=---------------------------------------------------------Di 13. Nov 11:36:34 2012-------*
    * @method  CwmsScriptablePrinter::Print                  // public, slots                     *
    * @return  void                                          //                                   *
    * @param   CsaObject* p_pCsaObjectToPrint                //                                   *
    * @param   CsaObject* p_pCdmTemplate                     //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 13. Nov 11:36:34 2012----------*/
void print( CsaObject* p_pCsaObjectToPrint, CsaObject* p_pCdmTemplate);

    public slots:
         /** +-=---------------------------------------------------------Mi 21. Nov 09:30:20 2012-------*
    * @method  CwmsScriptablePrinter::Print                  // public, slots                     *
    * @return  void                                          //                                   *
    * @param   CsaObjectContainer* p_pList                        //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 21. Nov 09:30:20 2012----------*/
void print( CsaObjectContainer* p_pList);

    public slots:
         /** +-=---------------------------------------------------------Mi 21. Nov 09:30:51 2012-------*
    * @method  CwmsScriptablePrinter::Print                  // public, slots                     *
    * @return  void                                          //                                   *
    * @param   CsaObjectContainer* p_pList                        //                                   *
    * @param   CsaObject* p_pCdmTemplate                     //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 21. Nov 09:30:51 2012----------*/
void print( CsaObjectContainer* p_pList, CsaObject* p_pCdmTemplate);

    public slots:
         /** +-=---------------------------------------------------------Di 27. Nov 16:26:59 2012-------*
    * @method  CwmsScriptablePrinter::Print                  // public, slots                     *
    * @return  void                                          //                                   *
    * @param   CsaObject* p_pCsaObjectToPrint                //                                   *
    * @param   QString p_qstrTemplate                        //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 27. Nov 16:26:59 2012----------*/
void print( CsaObject* p_pCsaObjectToPrint, QString p_qstrTemplate);

    public slots:
         /** +-=---------------------------------------------------------Mi 21. Nov 09:44:06 2012-------*
    * @method  CwmsScriptablePrinter::Print                  // public, slots                     *
    * @return  void                                          //                                   *
    * @param   CsaObjectContainer* p_pList                        //                                   *
    * @param   QString p_qstrTemplate                        //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 21. Nov 09:44:06 2012----------*/
void print( CsaObjectContainer* p_pList, QString p_qstrTemplate);
void printInLanguage(CsaObject *p_pCsaObject, QString p_qstrLanguage);

QString printPdfToBase64(CsaObjectContainer *p_pList, QString p_qstrTemplate);
QString printPdfToBase64(CsaObjectContainer *p_pList, CsaObject *p_pCdmTemplate);
QString printPdfToBase64(CsaObjectContainer *p_pList);
QString printPdfToBase64(CsaObject *p_pCsaObjectToPrint, CsaObject *p_pCdmTemplate);
QString printPdfToBase64(CsaObject *p_pCsaObjectToPrint, QString p_qstrTemplate);
QString printInLanguagePdfToBase64(CsaObject *p_pCsaObject, QString p_qstrLanguage);
QString printPdfToBase64(CsaObject *p_pCsaObject);
private:
    void print(CdmQueryEnhanced* pQuery, CwmsReportManager &cReportManager, CsaObject* p_pCsaObject);
    QString printPdfToBase64(CdmQueryEnhanced *pQuery, CwmsReportManager &cReportManager, CsaObject *p_pCsaObject);
};

#endif // CWMSSCRIPTABLEPRINTER_H
