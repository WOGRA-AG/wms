/******************************************************************************
 ** WOGRA technologies Modul Information
 ** Modulename: CdmContainerServices.h
 ** Started Implementation: 2009/04/04
 ** Description:
 ** 
 ** Implements services for objectlists.
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies All rights reserved
 *****************************************************************************/ 

#ifndef CDMOBJECTLISTSERVICES_H
#define CDMOBJECTLISTSERVICES_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes
#include <QList>
#include <QDate>
#include <QDateTime>
#include <QTime>

// Own Includes
#include "datamanager.h"


// Forwards


// Enumerations

/* 
 * This class implements services for objectlists.
 */
class WMSMANAGER_API CdmContainerServices
{
   private:
   /** +-=---------------------------------------------------------Sa 4. Apr 12:18:52 2009--------*
    * @method  CdmContainerServices::CdmContainerServices  // private                           *
    * @return                                                //                                   *
    * @comment SHOULD NOT BE CONSTRUCTED ALL METHODS AND FUNCTIONS ARE STATIC                     *
    *----------------last changed: -----------------------------Sa 4. Apr 12:18:52 2009-----------*/
    CdmContainerServices( );

   private:
   /** +-=---------------------------------------------------------Sa 4. Apr 12:19:08 2009--------*
    * @method  CdmContainerServices::~CdmContainerServices // private, virtual                  *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CdmContainerServices                                      *
    *----------------last changed: -----------------------------Sa 4. Apr 12:19:08 2009-----------*/
    virtual ~CdmContainerServices( );

   public:
   /** +-=---------------------------------------------------------Di 7. Apr 19:14:19 2009--------*
    * @method  CdmContainerServices::EvaluateSum            // public, static                    *
    * @return  QString                                       // value as string for conversion issues*
    * @param   CdmObjectContainer* p_pContainer               //                                   *
    * @param   QString p_qstrMember                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 7. Apr 19:14:19 2009-----------*/
    static QString EvaluateSum(CdmObjectContainer* p_pContainer, QString p_qstrMember);

   public:
   /** +-=---------------------------------------------------------Di 7. Apr 19:15:17 2009--------*
    * @method  CdmContainerServices::EvaluateAverage        // public, static                    *
    * @return  QString                                       // value as string for conversion issues*
    * @param   CdmObjectContainer* p_pContainer               //                                   *
    * @param   QString p_qstrMember                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 7. Apr 19:15:17 2009-----------*/
    static QString EvaluateAverage(CdmObjectContainer* p_pContainer, QString p_qstrMember);

   public:
   /** +-=---------------------------------------------------------Di 7. Apr 19:16:13 2009--------*
    * @method  CdmContainerServices::EvaluateMin            // public, static                    *
    * @return  QString                                       // value as string for conversion issues*
    * @param   CdmObjectContainer* p_pContainer               //                                   *
    * @param   QString p_qstrMember                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 7. Apr 19:16:13 2009-----------*/
    static QString EvaluateMin(CdmObjectContainer* p_pContainer, QString p_qstrMember);

   public:
   /** +-=---------------------------------------------------------Di 7. Apr 19:17:08 2009--------*
    * @method  CdmContainerServices::EvaluateMax            // public, static                    *
    * @return  QString                                       // value as string for conversion issues*
    * @param   CdmObjectContainer* p_pContainer               //                                   *
    * @param   QString p_qstrMember                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 7. Apr 19:17:08 2009-----------*/
    static QString EvaluateMax(CdmObjectContainer* p_pContainer, QString p_qstrMember);

   public:
   /** +-=---------------------------------------------------------Di 7. Apr 19:14:39 2009--------*
    * @method  CdmContainerServices::EvaluateSum            // public, static                    *
    * @return  QString                                       // value as string for conversion issues*
    * @param   QList<CdmObject*>& p_rqvlObjects        //                                   *
    * @param   QString p_qstrMember                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 7. Apr 19:14:39 2009-----------*/
    static QString EvaluateSum(QList<CdmObject*>& p_rqvlObjects, QString p_qstrMember);

   public:
   /** +-=---------------------------------------------------------Di 7. Apr 19:16:30 2009--------*
    * @method  CdmContainerServices::EvaluateMin            // public, static                    *
    * @return  QString                                       // value as string for conversion issues*
    * @param   QList<CdmObject*>& p_rqvlObjects        //                                   *
    * @param   QString p_qstrMember                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 7. Apr 19:16:30 2009-----------*/
    static QString EvaluateMin(QList<CdmObject*>& p_rqvlObjects, QString p_qstrMember);

   public:
   /** +-=---------------------------------------------------------Di 7. Apr 19:17:30 2009--------*
    * @method  CdmContainerServices::EvaluateMax            // public, static                    *
    * @return  QString                                       // value as string for conversion issues*
    * @param   QList<CdmObject*>& p_rqvlObjects        //                                   *
    * @param   QString p_qstrMember                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 7. Apr 19:17:30 2009-----------*/
    static QString EvaluateMax(QList<CdmObject*>& p_rqvlObjects, QString p_qstrMember);

  

   public:
   /** +-=---------------------------------------------------------Di 7. Apr 20:33:56 2009--------*
    * @method  CdmContainerServices::EvaluateAverage        // public, static                    *
    * @return  QString                                       // value as string for conversion issues*
    * @param   QList<CdmObject*>& p_rqvlObjects        //                                   *
    * @param   QString p_qstrMember                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 7. Apr 20:33:56 2009-----------*/
    static QString EvaluateAverage(QList<CdmObject*>& p_rqvlObjects, QString p_qstrMember);
};

#endif //
