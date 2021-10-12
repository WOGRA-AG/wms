/******************************************************************************
 ** WOGRA Middleware Server Data Manager Module
 **
 ** @Author Wolfgang Graßhof 
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies All rights reserved
 ******************************************************************************/

#ifndef CDMBASEMANAGER_H
#define CDMBASEMANAGER_H

// System and QT Includes


// own Includes
#include "CdmLocatedElement.h"
#include "datamanager.h"
#include "IdmDataAccess.h"

// forwards
class QString;
class CdmDataProvider;
class CdmSettings;
class CdmLogging;
class CdmClassManager;
class CdmContainerManager;
class IdmDataAccess;


/*
 * This class is the base class for all manager classes
 */
class WMSMANAGER_API CdmModelElementBase : public CdmLocatedElement
{
   Q_OBJECT

   protected:

      /*
       * The db id of this manager
       */
      QAtomicInteger<qint64> m_lSchemeId;

   public:
   /** +-=---------------------------------------------------------Sa 20. Aug 12:35:52 2005*
    * @method  CdmModelElementBase::~CdmModelElementBase               // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CdmModelElementBase                                             *
    *----------------last changed: -----------------------------Sa 20. Aug 12:35:52 2005----------*/
virtual ~CdmModelElementBase(  );
   public:
   /** +-=---------------------------------------------------------Sa 9. Feb 11:50:55 2013--------*
    * @method  CdmModelElementBase::GetManager               // public, const                     *
    * @return  CdmManager*                                   //                                   *
    * @comment returns the Manager object to get access to him.                                   *
    *----------------last changed: -----------------------------Sa 9. Feb 11:50:55 2013-----------*/
    CdmDataProvider* GetDataProvider() const;
   public:
   /** +-=---------------------------------------------------------Sa 9. Feb 11:51:09 2013--------*
    * @method  CdmModelElementBase::GetSettings              // public, const                     *
    * @return  CdmSettings*                                  //                                   *
    * @comment returns the system settings.                                                       *
    *----------------last changed: -----------------------------Sa 9. Feb 11:51:09 2013-----------*/
    CdmSettings* GetSettings() const;
    public slots:
         /** +-=---------------------------------------------------------Fr 23. Nov 14:47:04 2012-------*
    * @method  CdmModelElementBase::GetSchemeId            // public, const, slots              *
    * @return qint64                                          //                                   *
    * @comment This method returns the DatabaseId.                                                *
    *----------------last changed: -----------------------------Fr 23. Nov 14:47:04 2012----------*/
qint64 GetSchemeId( ) const;
   public:
   /** +-=---------------------------------------------------------Fr 23. Nov 14:50:16 2012-------*
    * @method  CdmModelElementBase::GetClassManager          // public, const                     *
    * @return  CdmClassManager*                              //                                   *
    * @comment This method returns the CdmClassManager of this Database.                          *
    *----------------last changed: -----------------------------Fr 23. Nov 14:50:16 2012----------*/
    CdmClassManager* GetClassManager() const;
   public:
   /** +-=---------------------------------------------------------Sa 9. Feb 11:51:39 2013--------*
    * @method  CdmModelElementBase::GetContainerManager     // public, const                     *
    * @return  CdmContainerManager*                         //                                   *
    * @comment This method returns the ObjectListManager of this Database.                        *
    *----------------last changed: -----------------------------Sa 9. Feb 11:51:39 2013-----------*/
    CdmContainerManager* GetContainerManager() const;
   public:
   /** +-=---------------------------------------------------------Sa 9. Feb 11:51:47 2013--------*
    * @method  CdmModelElementBase::GetDataAccess            // public, const                     *
    * @return  IdmDataAccess*                                //                                   *
    * @comment This method returns the DataAccess of this Database.                               *
    *----------------last changed: -----------------------------Sa 9. Feb 11:51:47 2013-----------*/
    IdmDataAccess* GetDataAccess() const;

   public:
   /** +-=---------------------------------------------------------Sa 9. Feb 11:51:57 2013--------*
    * @method  CdmModelElementBase::GetSessionId             // public, const                     *
    * @return qint64                                          //                                   *
    * @comment This method returns the userId.                                                    *
    *----------------last changed: -----------------------------Sa 9. Feb 11:51:57 2013-----------*/
   qint64 GetSessionId() const;

    public slots:
         /** +-=---------------------------------------------------------Sa 9. Feb 11:49:29 2013--------*
    * @method  CdmModelElementBase::GetDatabaseName          // public, const, slots              *
    * @return  QString                                       //                                   *
    * @comment returns the name of the database.                                                  *
    *----------------last changed: -----------------------------Sa 9. Feb 11:49:29 2013-----------*/
QString GetSchemeName( ) const;


   public:
   /** +-=---------------------------------------------------------Fr 12. Aug 00:36:58 2005*
    * @method  CdmModelElementBase::GetUserId                     // public, const                     *
    * @return qint64                                          //                                   *
    * @comment This method returns the Id of the logged in user.                                  *
    *----------------last changed: -----------------------------Fr 12. Aug 00:36:58 2005----------*/
qint64 GetUserId(  ) const;

   public:
   /** +-=---------------------------------------------------------Fr 23. Nov 14:24:16 2012-------*
    * @method  CdmModelElementBase::CdmModelElementBase                // public                            *
    * @return                                                //                                   *
    * @param  qint64 p_lDbId                                  //                                   *
    * @comment The cosntructor.                                                                   *
    *----------------last changed: -----------------------------Fr 23. Nov 14:24:16 2012----------*/
    CdmModelElementBase(qint64 p_lDbId);

   public:
   /** +-=---------------------------------------------------------Fr 23. Nov 14:53:44 2012-------*
    * @method  CdmModelElementBase::SetSchemeId            // public                            *
    * @return  void                                          //                                   *
    * @param  qint64 p_lDbId                                  //                                   *
    * @comment sets the db id in the base object.                                                 *
    *----------------last changed: -----------------------------Fr 23. Nov 14:53:44 2012----------*/
    void SetSchemeId(qint64 p_lDbId);

    public slots:
         /** +-=---------------------------------------------------------Sa 9. Feb 11:50:37 2013--------*
    * @method  CdmModelElementBase::GetScheme              // public, const, slots              *
    * @return  CdmScheme*                                  //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Sa 9. Feb 11:50:37 2013-----------*/
CdmScheme* GetScheme( ) const;

   public:
   /** +-=---------------------------------------------------------So 10. Feb 18:33:32 2013-------*
    * @method  CdmModelElementBase::CreateUri                // public, const                     *
    * @return  QString                                       //                                   *
    * @param   QString p_qstrKey                             //                                   *
    * @param   QString p_qstrKeyname                         //                                   *
    * @param   QString p_qstrValueKeyname = ""               //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 10. Feb 18:33:32 2013----------*/
    QString CreateUri(QString p_qstrKey,
                      QString p_qstrKeyname,
                      QString p_qstrKeyname2 = "",
                      QString p_qstrKeyname3 = "") const;

   protected:
   /** +-=---------------------------------------------------------Mo 18. Feb 11:47:09 2013-------*
    * @method  CdmModelElementBase::IsInDeploymentMode       // protected, const                  *
    * @return  bool                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 18. Feb 11:47:09 2013----------*/
    bool IsInDeploymentMode() const;
};
#endif // //CDMBASEMANAGER_H
