/******************************************************************************
 ** WOGRA technologies Gmbh & Co KG Modul Information
 ** Modulename: CwmsTranslator.h
 ** Started Implementation: 2012/09/07
 ** Description:
 ** 
 ** implements the translator for apps.
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co KG All rights reserved
 *****************************************************************************/ 

#ifndef CWMSTRANSLATOR_H
#define CWMSTRANSLATOR_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes
#include <QTranslator>

// Own Includes
#include "CwmsApplication.h"


// Forwards


// TypeDefs


/* 
 * This class implements the ...
 */
class CwmsTranslator : public QTranslator
{
   private:
      int m_iObjectListId;
      QMap<QString, QString> m_qmTranslations;

   public:
   /** +-=---------------------------------------------------------Fr 7. Sep 11:10:52 2012--------*
    * @method  CwmsTranslator::CwmsTranslator                // public                            *
    * @return                                                //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 7. Sep 11:10:52 2012-----------*/
    CwmsTranslator( );

   public:
   /** +-=---------------------------------------------------------Fr 7. Sep 11:11:00 2012--------*
    * @method  CwmsTranslator::~CwmsTranslator               // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CwmsTranslator                                             *
    *----------------last changed: -----------------------------Fr 7. Sep 11:11:00 2012-----------*/
    virtual ~CwmsTranslator( );

   public:
   /** +-=---------------------------------------------------------Fr 7. Sep 11:50:35 2012--------*
    * @method  CwmsTranslator::translate                     // public, const                     *
    * @return  QString                                       //                                   *
    * @param   const char * context                          //                                   *
    * @param   const char * sourceText                       //                                   *
    * @param   const char *# disambiguation = 0              //                                   *
    * @comment const char * context, const char * sourceText, const char * disambiguation = 0     *
    *----------------last changed: -----------------------------Fr 7. Sep 11:50:35 2012-----------*/
    QString translate(const char * context,
                      const char * sourceText,
                      const char * disambiguation = 0) const;

   public:
   /** +-=---------------------------------------------------------Fr 7. Sep 12:00:41 2012--------*
    * @method  CwmsTranslator::translate                     // public, const                     *
    * @return  QString                                       //                                   *
    * @param   const char * context                          //                                   *
    * @param   const char * sourceText                       //                                   *
    * @param   const char * disambiguation                   //                                   *
    * @param   int n                                         //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 7. Sep 12:00:41 2012-----------*/
    QString translate(const char * context,
                      const char * sourceText,
                      const char * disambiguation,
                      int n) const;

   public:
   /** +-=---------------------------------------------------------Fr 7. Sep 11:15:22 2012--------*
    * @method  CwmsTranslator::LoadTranslations              // public                            *
    * @return  void                                          //                                   *
    * @param   CwmsApplication p_cApp                        //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 7. Sep 11:15:22 2012-----------*/
    void LoadTranslations(CwmsApplication p_cApp);

   public:
   /** +-=---------------------------------------------------------Fr 7. Sep 11:18:25 2012--------*
    * @method  CwmsTranslator::GetObjectList                 // public                            *
    * @return  CdmObjectContainer*                                //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 7. Sep 11:18:25 2012-----------*/
    CdmObjectContainer* GetObjectList();

   public:
   /** +-=---------------------------------------------------------Fr 7. Sep 11:22:03 2012--------*
    * @method  CwmsTranslator::GetCurrentLanguage          // public                            *
    * @return  int                                           //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 7. Sep 11:22:03 2012-----------*/
    QString GetCurrentLanguage() const;

   private:
   /** +-=---------------------------------------------------------Fr 7. Sep 11:58:17 2012--------*
    * @method  CwmsTranslator::AddTranslation                // private                           *
    * @return  void                                          //                                   *
    * @param   QString p_qstrTranslation                     //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 7. Sep 11:58:17 2012-----------*/
    void AddTranslation(QString p_qstrTranslation);
};

#endif // CWMSTRANSLATOR_H
