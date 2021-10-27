
// System and Qt Includes
#include <QCoreApplication>

// WMS Core Includes
#include "CdmMessageManager.h"

// Own Includes
#include "CwmsQueryModelExportCsv.h"


void CwmsQueryModelExportCsv::SaveModel(QAbstractItemModel& p_rModel)
{
   QString qstrFilename = AskForFilename(".csv");

   if (!qstrFilename.isEmpty())
   {
      QString qstrContent;
      qstrContent = ExportCsv(p_rModel);
      SaveContent(qstrFilename, qstrContent);
   }
}

QString CwmsQueryModelExportCsv::AskForFilename(QString p_qstrFileType)
{
   QString qstrFilename = CdmMessageManager::GetSaveFile(qApp->tr("Bitte Dateinamen angeben"));

   if (!qstrFilename.isEmpty())
   {
      if (!qstrFilename.contains("."))
      {
         qstrFilename += p_qstrFileType;
      }
   }

   return qstrFilename;
}

void CwmsQueryModelExportCsv::SaveContent(QString p_qstrFilename, QString p_qstrContent)
{
   if (!p_qstrFilename.isEmpty())
   {
      QFile qFile(p_qstrFilename);

      if (qFile.open(QIODevice::WriteOnly))
      {
         QTextStream qTextStream(&qFile);
         qTextStream << p_qstrContent;
      }

      qFile.close();
   }
}

QString CwmsQueryModelExportCsv::ExportCsv(QAbstractItemModel& p_rModel)
{
    QString qstrContent;
    int iRowCount = p_rModel.rowCount();
    qstrContent += ExportHeader(p_rModel) + "\n";

    for (int iCounter = 0; iCounter < iRowCount; ++iCounter)
    {
        qstrContent += ExportRow(p_rModel, iCounter) + "\n";
    }

    return qstrContent;
}

void CwmsQueryModelExportCsv::ExportCsvToFile(QAbstractItemModel& p_rModel, QString qstrHeadInformation, QString qstrFootInformation)
{
    QString qstrFilename = AskForFilename(".csv");

    if (!qstrFilename.isEmpty())
    {
        QString qstrContent = ExportCsv(p_rModel);

        if (!qstrContent.isEmpty())
        {
            qstrContent = qstrHeadInformation + qstrContent + qstrFootInformation;
            SaveContent(qstrFilename, qstrContent);
        }
        else
        {
            MSG_CRIT("KeinDaten vorhanden","Es wurden keine Daten dargestellt, die exportiert werden konnten.");
        }
    }
}

QString CwmsQueryModelExportCsv::ExportCsv(QAbstractItemModel& p_rModel, QModelIndexList& p_qlIndexes)
{
    QString qstrContent;

    qstrContent += ExportHeader(p_rModel) + "\n";

    for (int iCounter = 0; iCounter < p_qlIndexes.count(); ++iCounter)
    {
        QModelIndex qIndex = p_qlIndexes.at(iCounter);
        qstrContent += ExportRow(p_rModel, qIndex.row());
    }

    return qstrContent;
}

QString CwmsQueryModelExportCsv::ExportHeader(QAbstractItemModel& p_rModel)
{
    QString qstrHeader;
    int iColumnCount = p_rModel.columnCount();

    qstrHeader = p_rModel.headerData(0, Qt::Vertical, Qt::DisplayRole).toString();

    if (!qstrHeader.isEmpty())
    {
        qstrHeader += qstrHeader;
        qstrHeader += ";";
    }

    for (int iCounter = 0; iCounter < iColumnCount; ++iCounter)
    {
        qstrHeader += p_rModel.headerData(iCounter, Qt::Horizontal, Qt::DisplayRole).toString();
        qstrHeader += ";";
    }

    return qstrHeader;
}

QString CwmsQueryModelExportCsv::ExportRow(QAbstractItemModel& p_rModel, int p_iRowPos)
{
    QString qstrRow;
    int iColumnCount = p_rModel.columnCount();

    QString qstrHeader = p_rModel.headerData(p_iRowPos, Qt::Vertical, Qt::DisplayRole).toString();

    if (!qstrHeader.isEmpty())
    {
        qstrRow += qstrHeader;
        qstrRow += ";";
    }

    for (int iCounter = 0; iCounter < iColumnCount; ++iCounter)
    {
        qstrRow += p_rModel.data(p_rModel.index(p_iRowPos, iCounter), Qt::DisplayRole).toString();
        qstrRow += ";";
    }

    return qstrRow;
}
