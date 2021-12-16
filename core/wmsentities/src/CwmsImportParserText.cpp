// System and QT Includes
#include <QStringList>

// Own Includes
#include "CwmsImportSettings.h"
#include "CwmsImportSettingsColumn.h"
#include "CwmsImportParserText.h"

// WMS Includes
#include "CdmLogging.h"

CwmsImportParserText::CwmsImportParserText()
: CwmsImportParser()
{
}

CwmsImportParserText::~CwmsImportParserText()
{
}

QStringList CwmsImportParserText::ParseLine(QString p_qstrLine)
{
   QStringList qstrlResult;
   QList<CwmsImportSettingsColumn*> qlColumns;
   QString qstrValue;

   m_pCwmsImportSettings->GetColumns(qlColumns);
   
   for (int iCounter = 0; iCounter < qlColumns.count(); ++iCounter)
   {
      CwmsImportSettingsColumn* pCwmsColumn = qlColumns[iCounter];

      if (CHKPTR(pCwmsColumn) && !pCwmsColumn->IsIgnored())
      {
         int iStartPos = pCwmsColumn->GetStartPos();
         int iEndPos = pCwmsColumn->GetEndPos();

         if (iStartPos >= 0 && iEndPos > 0)
         {
            qstrValue = p_qstrLine.mid(iStartPos, iEndPos - iStartPos + 1);
            qstrValue = qstrValue.trimmed();
            qstrlResult.append(qstrValue);
         }
         else
         {
            qstrlResult.append("");
         }
      }
   }

   return qstrlResult;
}
