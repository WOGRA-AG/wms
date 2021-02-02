/******************************************************************************
 ** WOGRA technologies Gmbh & Co KG Modul Information
 ** Modulename: CwmscomDataResult.h
 ** Started Implementation: 2012/04/01
 ** Description:
 ** 
 ** Implements the result container
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co KG All rights reserved
 *****************************************************************************/ 

#ifndef CBMSCOMDATARESULT_H
#define CBMSCOMDATARESULT_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes
#include <QString>
#include <QVariant>

// BASETOOLS Includes
#include "CwmsHttpService.h"

// Own Includes
#include "wmscom.h"

// Forwards
class CwmscomData;


// Enumerations
enum EwmscomMessageServerity
{
   eWmscomMessageServerityInfo,
   eWmscomMessageServerityWarning,
   eWmscomMessageServerityError,
   eWmscomMessageServerityFatal
};


/* 
 * This class implements the result container
 */
class WMSCOM_API CwmscomDataResult
{
   private:
      CwmscomData* m_rpRequestObject;
      EwmsHttpStatusCode m_eReturnCode;
   protected:
      QVariantMap m_qmResult;

   public:
   /** +-=---------------------------------------------------------So 1. Apr 10:44:30 2012--------*
    * @method  CwmscomDataResult::CwmscomDataResult          // public                            *
    * @return                                                //                                   *
    * @param   CwmscomData* p_pRequestObject                 //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 1. Apr 10:44:30 2012-----------*/
    CwmscomDataResult( CwmscomData* p_pRequestObject);

   public:
   /** +-=---------------------------------------------------------Di 29. Mai 10:47:46 2012-------*
    * @method  CwmscomDataResult::~CwmscomDataResult         // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CwmscomDataResult                                          *
    *----------------last changed: -----------------------------Di 29. Mai 10:47:46 2012----------*/
    virtual ~CwmscomDataResult( );


   public:
   /** +-=---------------------------------------------------------Mo 9. Apr 11:27:06 2012--------*
    * @method  CwmscomDataResult::GetResultMap               // public                            *
    * @return  QVariantMap&                                  //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 9. Apr 11:27:06 2012-----------*/
    QVariantMap& GetResultMap();

   public:
   /** +-=---------------------------------------------------------So 1. Apr 10:45:42 2012--------*
    * @method  CwmscomDataResult::SetMessageCode             // public                            *
    * @return  void                                          //                                   *
    * @param   int p_iCode                                   //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 1. Apr 10:45:42 2012-----------*/
    void SetMessageCode(int p_iCode);

   public:
   /** +-=---------------------------------------------------------So 1. Apr 10:46:04 2012--------*
    * @method  CwmscomDataResult::GetMessageCode             // public                            *
    * @return  int                                           //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 1. Apr 10:46:04 2012-----------*/
    int GetMessageCode();

   public:
   /** +-=---------------------------------------------------------So 1. Apr 10:46:33 2012--------*
    * @method  CwmscomDataResult::SetMessage                 // public                            *
    * @return  void                                          //                                   *
    * @param   QString p_qstrMessage                         //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 1. Apr 10:46:33 2012-----------*/
    void SetMessage(QString p_qstrMessage);

   public:
   /** +-=---------------------------------------------------------So 1. Apr 10:46:52 2012--------*
    * @method  CwmscomDataResult::GetMessage                 // public                            *
    * @return  QString                                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 1. Apr 10:46:52 2012-----------*/
    QString GetMessage();

   public:
   /** +-=---------------------------------------------------------So 1. Apr 10:47:20 2012--------*
    * @method  CwmscomDataResult::SetSeverity                // public                            *
    * @return  void                                          //                                   *
    * @param   EbmscomMessageServerity p_eSeverity           //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 1. Apr 10:47:20 2012-----------*/
    void SetSeverity(EwmscomMessageServerity p_eSeverity);

   public:
   /** +-=---------------------------------------------------------So 1. Apr 10:47:45 2012--------*
    * @method  CwmscomDataResult::GetSeverity                // public                            *
    * @return  EbmscomMessageServerity                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 1. Apr 10:47:45 2012-----------*/
    EwmscomMessageServerity GetSeverity();

   public:
   /** +-=---------------------------------------------------------So 1. Apr 10:48:51 2012--------*
    * @method  CwmscomDataResult::GetRequestObject           // public                            *
    * @return  CwmscomData*                                  //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 1. Apr 10:48:51 2012-----------*/
    CwmscomData* GetRequestObject();

   public:
   /** +-=---------------------------------------------------------Mo 9. Apr 11:42:53 2012--------*
    * @method  CwmscomDataResult::AddValue                   // public                            *
    * @return  void                                          //                                   *
    * @param   QString p_qstrKey                             //                                   *
    * @param   QVariant p_qvValue                            //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 9. Apr 11:42:53 2012-----------*/
    void AddValue(QString p_qstrKey, QVariant p_qvValue);


   public:
   /** +-=---------------------------------------------------------Mo 9. Apr 11:27:48 2012--------*
    * @method  CwmscomDataResult::SetResultMap               // public                            *
    * @return  void                                          //                                   *
    * @param   QVariantMap p_qMap                            //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 9. Apr 11:27:48 2012-----------*/
    void SetResultMap(QVariantMap p_qMap);

   public:
   /** +-=---------------------------------------------------------Mo 9. Jul 11:45:55 2012--------*
    * @method  CwmscomDataResult::SetReturnCode              // public                            *
    * @return  void                                          //                                   *
    * @param   int p_iCode                                   //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 9. Jul 11:45:55 2012-----------*/
    void SetReturnCode(int p_iCode);
    EwmsHttpStatusCode GetReturnCode();
};

#endif // CBMSCOMDATARESULT_H
