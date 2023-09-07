#ifndef CWMSCSVEXPORT_H
#define CWMSCSVEXPORT_H

#include <QString>
#include <QScopedPointer>

#include "CdmQuery.h"

#include "basetools.h"

class BASETOOLS_API CwmsCsvExport
{
private:
    QString m_qstrFileName;
    QString m_qstrContent;
    QString m_qstrDateFormat;
    QMap<QString,QString> m_qmHeaderMapping;
    QMap<QString,int> m_qmMaxFieldLength;
    QScopedPointer<CdmQuery> m_pQuery;
    CdmObjectContainer* m_rpContainer;
    int m_iDecimalPlaces;

public:
    CwmsCsvExport(QString p_qstrFilename, QString p_qstrQuery);
    CwmsCsvExport(QString p_qstrFilename, CdmObjectContainer* p_pContainer);
    void GenerateCsvData();
    void SetDateFormat(QString p_qstrFormat);
    void AddHeaderMapping(QString p_qstrKeyname, QString p_qstrOutputString);
    CdmQuery *GetQuery();
    void SetDecimalPlaces(int iDecimalPlaces);

    void GenerateQueryContent();
    void GenerateContainerContent();

    void GenerateHeader(QStringList &qstrlHeaders);
    void AddLine(QStringList &qstrlHeaders);
    void WriteFile();
    void AddMaxFieldLength(QString p_qstrKeyname, int p_Length);
};

#endif // CWMSCSVEXPORT_H
