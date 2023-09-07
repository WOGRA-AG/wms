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
class CdmQuery;

// TypeDefs


/* 
 * This class implements the script interface for js methods using print
 */
class BASETOOLS_API CwmsScriptablePrinter : public CwmsScriptableBase
{
    Q_OBJECT

public:
    CwmsScriptablePrinter();
    virtual ~CwmsScriptablePrinter( );

public slots:
    void print( CsaObject* p_pCsaObject);
    void print( CsaObject* p_pCsaObjectToPrint, CsaObject* p_pCdmTemplate);
    void print( CsaObjectContainer* p_pList);
    void print( CsaObjectContainer* p_pList, CsaObject* p_pCdmTemplate);
    void print( CsaObject* p_pCsaObjectToPrint, QString p_qstrTemplate);
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
    void print(CdmQuery* pQuery, CwmsReportManager &cReportManager, CsaObject* p_pCsaObject);
    QString printPdfToBase64(CdmQuery *pQuery, CwmsReportManager &cReportManager, CsaObject *p_pCsaObject);
};

#endif // CWMSSCRIPTABLEPRINTER_H
