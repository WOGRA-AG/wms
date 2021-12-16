// System and QT Includes
#include <QStringList>

// Own Includes
#include "CwmsImportSettings.h"
#include "CwmsImportParserCsv.h"

CwmsImportParserCsv::CwmsImportParserCsv()
: CwmsImportParser()
{
}

CwmsImportParserCsv::~CwmsImportParserCsv()
{
}

QStringList CwmsImportParserCsv::ParseLine(QString p_qstrLine)
{
   QStringList qstrlResult;
   QString qstrSeparator = m_pCwmsImportSettings->GetCsvSeperator();
   QString qstrStringEnclosing = m_pCwmsImportSettings->GetStringEnclosing();
   QString qstrSeparatorTemp;
   QString qstrValue;
   int iPos = 0;

   while (iPos != -1)
   {
      if (p_qstrLine.startsWith(qstrStringEnclosing))
      {
         p_qstrLine.remove(0, 1);
         qstrSeparatorTemp = qstrStringEnclosing + qstrSeparator;
         iPos = p_qstrLine.indexOf(qstrSeparatorTemp);
      }
      else
      {
         qstrSeparatorTemp = qstrSeparator;
         iPos = p_qstrLine.indexOf(qstrSeparatorTemp);
      }

      qstrValue = p_qstrLine.mid(0, iPos);
      qstrlResult.append(qstrValue);
      p_qstrLine = p_qstrLine.mid(iPos + qstrSeparatorTemp.length(), p_qstrLine.length() - iPos - qstrSeparatorTemp.length());
   }

   return qstrlResult;
}
