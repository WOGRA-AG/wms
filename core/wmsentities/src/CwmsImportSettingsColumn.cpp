/******************************************************************************
 ** WOGRA technologies Modul Information
 ** Modulename: CwmsImportSettingsColumn.cpp
 ** Started Implementation: 2008/10/20
 ** Description:
 ** 
 ** This class implements one settings column in the sourcefile
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies All rights reserved
 *****************************************************************************/ 

// System and QT Includes


// Own Includes
#include "CwmsImportSettingsColumn.h"

// WMS Includes
#include "CdmMember.h"


/** +-=---------------------------------------------------------Di 21. Okt 18:29:35 2008----------*
 * @method  CwmsImportSettingsColumn::CwmsImportSettingsColumn // public                          *
 * @return                                                   //                                   *
 * @param   QString p_qstrMember                             //                                   *
 * @param   int p_iStartPos                                  //                                   *
 * @param   int p_iEndPos                                    //                                   *
 * @param   bool p_bUpdateCriteria                           //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 21. Okt 18:29:35 2008----------*/
CwmsImportSettingsColumn::CwmsImportSettingsColumn(QString p_qstrMember,
                                                   int p_iStartPos,
                                                   int p_iEndPos,
                                                   bool p_bUpdateCriteria)
: m_qstrMember(p_qstrMember),
  m_iStartPos(p_iStartPos),
  m_iEndPos(p_iEndPos),
  m_bUpdateCriteria(p_bUpdateCriteria)
{
}

/** +-=---------------------------------------------------------Mo 20. Okt 19:05:21 2008----------*
 * @method  CwmsImportSettingsColumn::~CwmsImportSettingsColumn // public, virtual                *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CwmsImportSettingsColumn                                      *
 *----------------last changed: --------------------------------Mo 20. Okt 19:05:21 2008----------*/
CwmsImportSettingsColumn::~CwmsImportSettingsColumn()
{
}

/** +-=---------------------------------------------------------Di 21. Okt 18:30:12 2008----------*
 * @method  CwmsImportSettingsColumn::GetMember              // public                            *
 * @return  QString                                          //                                   *
 * @comment returns the corresponding member.                                                     *
 *----------------last changed: --------------------------------Di 21. Okt 18:30:12 2008----------*/
QString CwmsImportSettingsColumn::GetMember()
{
   return m_qstrMember;
}

/** +-=---------------------------------------------------------So 26. Okt 14:05:50 2008----------*
 * @method  CwmsImportSettingsColumn::SetMember              // public                            *
 * @return  void                                             //                                   *
 * @param   QString p_qstrMember                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 26. Okt 14:05:50 2008----------*/
void CwmsImportSettingsColumn::SetMember(QString p_qstrMember)
{
   m_qstrMember = p_qstrMember;
}

/** +-=---------------------------------------------------------Mo 20. Okt 19:09:39 2008----------*
 * @method  CwmsImportSettingsColumn::GetStartPos            // public                            *
 * @return  int                                              //                                   *
 * @comment returns the startpos.                                                                 *
 *----------------last changed: --------------------------------Mo 20. Okt 19:09:39 2008----------*/
int CwmsImportSettingsColumn::GetStartPos()
{
   return m_iStartPos;
}

/** +-=---------------------------------------------------------So 26. Okt 14:06:14 2008----------*
 * @method  CwmsImportSettingsColumn::SetStartPos            // public                            *
 * @return  void                                             //                                   *
 * @param   int p_iPos                                       //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 26. Okt 14:06:14 2008----------*/
void CwmsImportSettingsColumn::SetStartPos(int p_iPos)
{
   m_iStartPos = p_iPos;
}

/** +-=---------------------------------------------------------Mo 20. Okt 19:10:20 2008----------*
 * @method  CwmsImportSettingsColumn::GetEndPos              // public                            *
 * @return  int                                              //                                   *
 * @comment returns the endpos.                                                                   *
 *----------------last changed: --------------------------------Mo 20. Okt 19:10:20 2008----------*/
int CwmsImportSettingsColumn::GetEndPos()
{
   return m_iEndPos;
}

/** +-=---------------------------------------------------------So 26. Okt 14:06:30 2008----------*
 * @method  CwmsImportSettingsColumn::SetEndPos              // public                            *
 * @return  void                                             //                                   *
 * @param   int p_iEndPos                                    //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 26. Okt 14:06:30 2008----------*/
void CwmsImportSettingsColumn::SetEndPos(int p_iEndPos)
{
   m_iEndPos = p_iEndPos;
}

/** +-=---------------------------------------------------------Di 21. Okt 17:38:35 2008----------*
 * @method  CwmsImportSettingsColumn::IsUpdateCriteria       // public                            *
 * @return  bool                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 21. Okt 17:38:35 2008----------*/
bool CwmsImportSettingsColumn::IsUpdateCriteria()
{
   return m_bUpdateCriteria;
}

/** +-=---------------------------------------------------------So 26. Okt 14:06:56 2008----------*
 * @method  CwmsImportSettingsColumn::SetUpdateCriteria      // public                            *
 * @return  void                                             //                                   *
 * @param   bool p_bUpdateCriteria                           //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 26. Okt 14:06:56 2008----------*/
void CwmsImportSettingsColumn::SetUpdateCriteria(bool p_bUpdateCriteria)
{
   m_bUpdateCriteria = p_bUpdateCriteria;
}

/** +-=---------------------------------------------------------Di 21. Okt 20:51:52 2008----------*
 * @method  CwmsImportSettingsColumn::IsIgnored              // public                            *
 * @return  bool                                             //                                   *
 * @comment returns if this column should be ignored.                                             *
 *----------------last changed: --------------------------------Di 21. Okt 20:51:52 2008----------*/
bool CwmsImportSettingsColumn::IsIgnored()
{
   bool bRet = false;

   if (m_qstrMember.isEmpty())
   {
      bRet = true;
   }

   return bRet;
}