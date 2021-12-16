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
class CdmClassMethod;
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
    CwmsImport( );
    virtual ~CwmsImport( );
    virtual bool CreateData(QStringList &p_qsrlParsedData);
    void StartImport(QString p_qstrSettingsFile, CdmObjectContainer* p_pList);
    CdmObjectContainer* GetContainer();
    CdmObject* GetObject(const QStringList &qstrlParseData);
    QString GetImportMessages();
    void StartImport(CdmObjectContainer* p_pContainer, CwmsImportSettings p_cwmsImportSettings);
    void AddHiddenMember(QString p_qstrMember);
    QStringList GetHiddenMembersList();
    void AddDefaultValues(QString p_qstrKeyname, QString p_qstrValue1, QString p_qstrValue2);
    void SetDefaultValuesToObject(CdmObject* p_pCdmObject);
    virtual void Commit();
    CwmsImportSettings& GetSettings();
    CwmsImportParser* CreateParser(QString p_qstrSettingsFile, CdmObjectContainer* p_pList);
    CwmsImportParser* CreateParser(CwmsImportSettings p_cwmsImportSettings);
    void SetDipslayProgress(bool p_bDisplay);
    bool GetDisplayProgress();

private:
    CdmObject* ExecuteObjectQuery(const QStringList &p_rqstrlParseData);
    void CreateQuery(CdmQuery& p_rCdmQuery, const QStringList &p_qstrlParseData);

    void StartImport();
    void ModifyContainerContentDependentOnMode();
    bool ExecutePreprocessing(QStringList &p_qsrlParsedData);
    bool ExecutePostprocessing(CdmObject *p_pObject);
    CdmClassMethod *FindFunction(QString &p_qstrModelMethod);
    CdmClassMethod *FindPostprocessorFunction();
    CdmClassMethod *FindPreprocessorFunction();
    QVariantList ConvertParsedDataToJsonArray(QStringList &p_qsrlParsedData);
};

#endif //
