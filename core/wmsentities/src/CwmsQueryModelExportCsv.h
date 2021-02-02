#ifndef CWMSQUERYMODELEXPORTCSV_H
#define CWMSQUERYMODELEXPORTCSV_H

// WMS Core Includes
#include <CdmQueryModel.h>


// Own Includes
#include "basetools.h"


class BASETOOLS_API CwmsQueryModelExportCsv
{
public:
    static void SaveModel(QAbstractItemModel &p_rModel);
    static QString AskForFilename(QString p_qstrFileType);
    static void SaveContent(QString p_qstrFilename, QString p_qstrContent);
    static QString ExportCsv(QAbstractItemModel &p_rModel);
    static void ExportCsvToFile(QAbstractItemModel &p_rModel, QString qstrHeadInformation, QString qstrFootInformation);
    static QString ExportCsv(QAbstractItemModel &p_rModel, QModelIndexList &p_qlIndexes);
private:

    static QString ExportHeader(QAbstractItemModel &p_rModel);
    static QString ExportRow(QAbstractItemModel &p_rModel, int p_iRowPos);
};

#endif // CWMSQUERYMODELEXPORTCSV_H
