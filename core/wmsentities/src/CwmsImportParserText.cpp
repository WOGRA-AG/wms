/******************************************************************************
** WOGRA technologies Modul Information
** Modulename: CwmsImportParserCsv.cpp
** Started Implementation: 2008/10/21
** Description:
** 
** This class implements the text parser
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
**(C) copyright by WOGRA technologies All rights reserved
*****************************************************************************/ 

// System and QT Includes
#include <QStringList>

// Own Includes
#include "CwmsImportSettings.h"
#include "CwmsImportSettingsColumn.h"
#include "CwmsImportParserText.h"

// WMS Includes
#include "CdmLogging.h"

/** +-=---------------------------------------------------------Di 21. Okt 20:06:41 2008----------*
 * @method  CwmsImportParserText::CwmsImportParserText       // public                            *
 * @return                                                   //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 21. Okt 20:06:41 2008----------*/
CwmsImportParserText::CwmsImportParserText()
: CwmsImportParser()
{
}

/** +-=---------------------------------------------------------Di 21. Okt 20:06:56 2008----------*
 * @method  CwmsImportParserText::~CwmsImportParserText      // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CwmsImportParserCsv                                           *
 *----------------last changed: --------------------------------Di 21. Okt 20:06:56 2008----------*/
CwmsImportParserText::~CwmsImportParserText()
{
}

/** +-=---------------------------------------------------------Di 21. Okt 20:07:04 2008----------*
 * @method  CwmsImportParserText::ParseLine                  // protected, virtual                *
 * @return  QStringList                                      //                                   *
 * @param   QString p_qstrLine                               //                                   *
 * @comment This method parses one line.                                                          *
 *----------------last changed: --------------------------------Di 21. Okt 20:07:04 2008----------*/
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
