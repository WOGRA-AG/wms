/******************************************************************************
 ** WOGRA technologies Modul Information
 ** Modulename: CwmsImportParserCsv.cpp
 ** Started Implementation: 2008/10/21
 ** Description:
 ** 
 ** implements the csv parser
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies All rights reserved
 *****************************************************************************/ 

// System and QT Includes
#include <QStringList>

// Own Includes
#include "CwmsImportSettings.h"
#include "CwmsImportParserCsv.h"

/** +-=---------------------------------------------------------Di 21. Okt 20:04:47 2008----------*
 * @method  CwmsImportParserCsv::CwmsImportParserCsv         // public                            *
 * @return                                                   //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 21. Okt 20:04:47 2008----------*/
CwmsImportParserCsv::CwmsImportParserCsv()
: CwmsImportParser()
{
}

/** +-=---------------------------------------------------------Di 21. Okt 20:04:55 2008----------*
 * @method  CwmsImportParserCsv::~CwmsImportParserCsv        // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CwmsImportParserCsv                                           *
 *----------------last changed: --------------------------------Di 21. Okt 20:04:55 2008----------*/
CwmsImportParserCsv::~CwmsImportParserCsv()
{
}
/** +-=---------------------------------------------------------Di 21. Okt 20:05:27 2008----------*
 * @method  CwmsImportParserCsv::ParseLine                   // protected, virtual                *
 * @return  QStringList                                      //                                   *
 * @param   QString p_qstrLine                               //                                   *
 * @comment This method parses one line.                                                          *
 *----------------last changed: --------------------------------Di 21. Okt 20:05:27 2008----------*/
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
