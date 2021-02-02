/******************************************************************************
 ** WOGRA technologies Gmbh & Co KG Modul Information
 ** Modulename: CdmSystemVariables.h
 ** Started Implementation: 2012/09/13
 ** Description:
 ** 
 ** implements functions for returning system values
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co KG All rights reserved
 *****************************************************************************/ 

#ifndef CDMSYSTEMVARIABLES_H
#define CDMSYSTEMVARIABLES_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes
#include <QStringList>

// Own Includes


// Forwards


// TypeDefs


/* 
 * This class implements functions for returning system values
 */
class CdmSystemVariables
{
   private:
      static QStringList m_sqstrlVariables;
      static QString m_sqstrOpen;
      static QString m_sqstrClose;

   public:
   /** +-=---------------------------------------------------------Do 13. Sep 14:52:32 2012-------*
    * @method  CdmSystemVariables::CdmSystemVariables        // public                            *
    * @return                                                //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 13. Sep 14:52:32 2012----------*/
    CdmSystemVariables( );

   public:
   /** +-=---------------------------------------------------------Do 13. Sep 15:51:49 2012-------*
    * @method  CdmSystemVariables::GetValueAsString          // public, static                    *
    * @return  QString                                       //                                   *
    * @param   QString p_qstrVariable                        //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 13. Sep 15:51:49 2012----------*/
    static QString GetValueAsString(QString p_qstrVariable);

   public:
   /** +-=---------------------------------------------------------So 21. Okt 12:37:43 2012-------*
    * @method  CdmSystemVariables::IsSystemValue             // public, static                    *
    * @return  bool                                          //                                   *
    * @param   QString p_qstrValue                           //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 21. Okt 12:37:43 2012----------*/
    static bool IsSystemValue(QString p_qstrValue);

   private:
   /** +-=---------------------------------------------------------So 21. Okt 12:42:56 2012-------*
    * @method  CdmSystemVariables::FillVariablesInList       // private, static                   *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 21. Okt 12:42:56 2012----------*/
    static void FillVariablesInList();

   private:
   /** +-=---------------------------------------------------------So 21. Okt 12:50:53 2012-------*
    * @method  CdmSystemVariables::RemoveBraces              // private, static                   *
    * @return  bool                                          //                                   *
    * @param   QString& p_qstrValue                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 21. Okt 12:50:53 2012----------*/
    static bool RemoveBraces(QString& p_qstrValue);
};

#endif //
