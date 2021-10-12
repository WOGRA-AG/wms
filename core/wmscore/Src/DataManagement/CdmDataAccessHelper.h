/******************************************************************************
 ** WOGRA Middleware Server Data Manager Module
 **
 ** @Author Wolfgang Graßhof 
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies All rights reserved
 ******************************************************************************/

#ifndef CdmDataAccessHelper_H
#define CdmDataAccessHelper_H

// System and QT Includes
#include <qstring.h>
#include <qmap.h>
#include <QSettings>
#include <qdatetime.h>
#include <QList>



// own Includes
#include "datamanager.h"
#include "IdmDataAccess.h"

// forwards
class CdmDataProvider;
class CdmObject;
class CdmObjectContainer;
class CdmClass;
class CdmValue;
class CdmLogging;
class CdmModelElement;
class CdmValueBinaryDocument;
class CdmMember;
class CdmSettings;
class CdmScheme;
class CumUser;
class CumUserGroup;
class CdmQuery;
class CdmClassManager;
class CdmJournalItem;
class QVariant;
class QSqlDatabase;
class CdmPackage;
class CdmQueryEnhanced;

/*
 * This is the helper class for the dataaccesses like
 * sqllite, odbc, client or server. 
 * This class contains methods to manipulate and create objects
 * These method are only for internal use. They are not part of
 * the public interface!!!!!
 */
class WMSMANAGER_API CdmDataAccessHelper
{
   public:
   /** +-=---------------------------------------------------------Sa 13. Aug 21:23:31 2005*
    * @method  CdmDataAccessHelper::CdmDataAccessHelper                  // public                            *
    * @return                                                //                                   *
    * @comment The constructor                                                                    *
    *----------------last changed: -----------------------------Sa 13. Aug 21:23:31 2005----------*/
CdmDataAccessHelper(  );
   public:
   /** +-=---------------------------------------------------------Sa 20. Aug 12:43:37 2005*
    * @method  CdmDataAccessHelper::~CdmDataAccessHelper                 // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CdmDataAccessHelper                                              *
    *----------------last changed: -----------------------------Sa 20. Aug 12:43:37 2005----------*/
virtual ~CdmDataAccessHelper(  );
   public:
   /** +-=---------------------------------------------------------Sa 9. Feb 12:28:26 2013--------*
    * @method  CdmDataAccessHelper::GetManager                     // public, const                     *
    * @return  CdmManager*                                   //                                   *
    * @comment returns the Manager object to get access to him.                                   *
    *----------------last changed: -----------------------------Sa 9. Feb 12:28:26 2013-----------*/
    static CdmDataProvider* GetManager();
   public:
   /** +-=---------------------------------------------------------Sa 9. Feb 12:28:34 2013--------*
    * @method  CdmDataAccessHelper::GetSettings                    // public, const                     *
    * @return  CdmSettings*                                  //                                   *
    * @comment returns the system settings.                                                       *
    *----------------last changed: -----------------------------Sa 9. Feb 12:28:34 2013-----------*/
    static CdmSettings* GetSettings();




   public:
   /** +-=---------------------------------------------------------Sa 13. Aug 21:27:47 2005*
    * @method  CdmDataAccessHelper::SetId                          // public                            *
    * @return  int                                           //                                   *
    * @param   CdmModelElement* p_pCdmBase                           //                                   *
    * @param  qint64 p_lId                                    //                                   *
    * @comment ONLY FOR INTERNAL USE!!!                                                           *
    *          Sets the Id in base objects.                                                       *
    *----------------last changed: -----------------------------Sa 13. Aug 21:27:47 2005----------*/
static int SetId(  CdmModelElement* p_pCdmBase,qint64 p_lId );
   public:
   /** +-=---------------------------------------------------------Sa 13. Aug 21:28:29 2005*
    * @method  CdmDataAccessHelper::SetKeyname                     // public                            *
    * @return  int                                           //                                   *
    * @param   CdmModelElement* p_pCdmBase                           //                                   *
    * @param   QString p_qstrKeyname                         //                                   *
    * @comment ONLY FOR INTERNAL USE!!!                                                           *
    *          Sets the keyname in base objects.                                                  *
    *----------------last changed: -----------------------------Sa 13. Aug 21:28:29 2005----------*/
static int SetKeyname(  CdmModelElement* p_pCdmBase, QString p_qstrKeyname );
   public:
   /** +-=---------------------------------------------------------Sa 13. Aug 21:28:17 2005*
    * @method  CdmDataAccessHelper::AddClass                       // public                            *
    * @return  int                                           //                                   *
    * @param   CdmClassManager* p_pCdmClassManager           //                                   *
    * @param   CdmClass* p_pCdmClass                         //                                   *
    * @comment ONLY FOR INTERNAL USE!!!!                                                          *
    *          This emthod adds a class to the overgiven classmanager.                            *
    *----------------last changed: -----------------------------Sa 13. Aug 21:28:17 2005----------*/
static int AddClass(  CdmClassManager* p_pCdmClassManager, CdmClass* p_pCdmClass );
public:
static int AddPackageToClass(CdmClassManager* p_pCdmClassManager, CdmClass* p_pCdmClass, QString p_qstrPackage);
public:
   /** +-=---------------------------------------------------------Sa 13. Aug 21:26:47 2005*
    * @method  CdmDataAccessHelper::AddObjectToObjectList          // public                            *
    * @return  int                                           //                                   *
    * @param   CdmObject* p_pCdmObject                       //                                   *
    * @param   CdmObjectContainer* p_pContainer               //                                   *
    * @comment ONLY FOR INTERNAL USE!!!!                                                          *
    *          This method adds an object to it's objectlist.                                     *
    *----------------last changed: -----------------------------Sa 13. Aug 21:26:47 2005----------*/
static int AddObjectToObjectList(  CdmObject* p_pCdmObject, CdmObjectContainer* p_pContainer );

   public:
   /** +-=---------------------------------------------------------Sa 13. Aug 21:28:01 2005*
    * @method  CdmDataAccessHelper::InitializeObject               // public                            *
    * @return  int                                           //                                   *
    * @param   CdmObject* p_pCdmObject                       //                                   *
    * @param   CdmClass* p_pCdmClass                         //                                   *
    * @comment ONLY FOR INTERNAL USE!!!                                                           *
    *          This method initialize object afterwards.                                          *
    *----------------last changed: -----------------------------Sa 13. Aug 21:28:01 2005----------*/
static int InitializeObject(  CdmObject* p_pCdmObject, CdmClass* p_pCdmClass );

   public:
   /** +-=---------------------------------------------------------Sa 13. Aug 21:29:49 2005*
    * @method  CdmDataAccessHelper::SetModified                    // public                            *
    * @return  int                                           //                                   *
    * @param   CdmModelElement* p_pCdmBase                           //                                   *
    * @comment ONLY FOR INTERNAL USE!!!                                                           *
    *          This method sets the modified flag                                                 *
    *----------------last changed: -----------------------------Sa 13. Aug 21:29:49 2005----------*/
static int SetModified(  CdmModelElement* p_pCdmBase );

   public:
   /** +-=---------------------------------------------------------Sa 13. Aug 21:30:11 2005*
    * @method  CdmDataAccessHelper::SetNew                         // public                            *
    * @return  int                                           //                                   *
    * @param   CdmModelElement* p_pCdmBase                           //                                   *
    * @comment ONLY FOR INTERNAL USE!!!                                                           *
    *          This method sets the new flag.                                                     *
    *----------------last changed: -----------------------------Sa 13. Aug 21:30:11 2005----------*/
static int SetNew(  CdmModelElement* p_pCdmBase );

   public:
   /** +-=---------------------------------------------------------Sa 13. Aug 21:31:06 2005*
    * @method  CdmDataAccessHelper::SetDeleted                     // public                            *
    * @return  int                                           //                                   *
    * @param   CdmModelElement* p_pCdmBase                           //                                   *
    * @comment ONLY FOR INTERNAL USE!!!                                                           *
    *          This method sets the deleted flag.                                                 *
    *----------------last changed: -----------------------------Sa 13. Aug 21:31:06 2005----------*/
static int SetDeleted(  CdmModelElement* p_pCdmBase );

   public:
   /** +-=---------------------------------------------------------Sa 13. Aug 21:31:26 2005*
    * @method  CdmDataAccessHelper::SetDatabaseId                  // public                            *
    * @return  int                                           //                                   *
    * @param   CdmModelElement* p_pCdmBase                           //                                   *
    * @param  qint64 p_lDbId                                  //                                   *
    * @comment ONLY FOR INTERNAL USE!!!                                                           *
    *          Sets the databseid in the Data Access.                                             *
    *----------------last changed: -----------------------------Sa 13. Aug 21:31:26 2005----------*/
static int SetDatabaseId(  CdmModelElement* p_pCdmBase,qint64 p_lDbId );

   public:
   /** +-=---------------------------------------------------------Sa 13. Aug 21:31:40 2005*
    * @method  CdmDataAccessHelper::GetValueMap                    // public                            *
    * @return  int                                           //                                   *
    * @param   CdmObject* p_pCdmObject                       //                                   *
    * @param   QMap<QString,CdmValue*>& p_pqmValues          //                                   *
    * @comment ONLY FOR INTERNAL USE!!!                                                           *
    *          This method returns the Value Map of the overgiven Object.                         *
    *----------------last changed: -----------------------------Sa 13. Aug 21:31:40 2005----------*/
static int GetValueMap(  CdmObject* p_pCdmObject, QMap<QString,CdmValue*>& p_pqmValues );


   public:
   /** +-=---------------------------------------------------------Sa 13. Aug 21:26:58 2005*
    * @method  CdmDataAccessHelper::AddValueToObject               // public                            *
    * @return  int                                           //                                   *
    * @param   CdmObject* p_pCdmObject                       //                                   *
    * @param   CdmValue* p_pCdmValue                         //                                   *
    * @comment ONLY FOR INTERNAL USE!!!!                                                          *
    *          This method adds a Value to an object.                                             *
    *----------------last changed: -----------------------------Sa 13. Aug 21:26:58 2005----------*/
static int AddValueToObject(  CdmObject* p_pCdmObject, CdmValue* p_pCdmValue );

   public:
   /** +-=---------------------------------------------------------Sa 13. Aug 21:27:18 2005*
    * @method  CdmDataAccessHelper::AddMemberToClass               // public                            *
    * @return  int                                           //                                   *
    * @param   CdmClass* pCdmClass                           //                                   *
    * @param   CdmMember* p_pCdmMember                       //                                   *
    * @comment ONLY FOR INTERNAL USE!!!!                                                          *
    *          This m4ethod adds member to classes                                                *
    *----------------last changed: -----------------------------Sa 13. Aug 21:27:18 2005----------*/
static int AddMemberToClass(  CdmClass* pCdmClass, CdmMember* p_pCdmMember );

   public:
   /** +-=---------------------------------------------------------Sa 13. Aug 21:27:32 2005*
    * @method  CdmDataAccessHelper::AddQueryResult                 // public                            *
    * @return  int                                           //                                   *
    * @param   CdmQuery* p_pCdmQuery                         //                                   *
    * @param  qint64 p_lObjectId                              //                                   *
    * @comment ONLY FOR INTERNAL USE!!!!                                                          *
    *          This method adds an result object to the overgiven query.                          *
    *----------------last changed: -----------------------------Sa 13. Aug 21:27:32 2005----------*/
static int AddQueryResult(CdmQuery* p_pCdmQuery,qint64 p_lObjectId,qint64 p_lContainerId);

   public:
   /** +-=---------------------------------------------------------Sa 13. Aug 21:25:14 2005*
    * @method  CdmDataAccessHelper::CreateClass                    // public                            *
    * @return  CdmClass*                                     //                                   *
    * @param  qint64 p_lDbId                                  //                                   *
    * @param  qint64 p_lId                                    //                                   *
    * @param   QString p_qstrKeyname                         //                                   *
    * @comment ONLY FOR INTERNAL USE!!!!                                                          *
    *          This method is a helper function for creating classes.                             *
    *----------------last changed: -----------------------------Sa 13. Aug 21:25:14 2005----------*/
static CdmClass* CreateClass( qint64 p_lDbId,qint64 p_lId, QString p_qstrKeyname );

   public:
   /** +-=---------------------------------------------------------Sa 13. Aug 21:29:19 2005*
    * @method  CdmDataAccessHelper::GetValue                       // public                            *
    * @return  CdmValue*                                     //                                   *
    * @param   CdmObject* p_pCdmObject                       //                                   *
    * @param   QString p_qstrKeyname                         //                                   *
    * @comment ONLY FOR INTERNAL USE!!!!                                                          *
    *          This method retunrs a value of an object.                                          *
    *----------------last changed: -----------------------------Sa 13. Aug 21:29:19 2005----------*/
static CdmValue* GetValue(  CdmObject* p_pCdmObject, QString p_qstrKeyname );



   public:
   /** +-=---------------------------------------------------------Sa 13. Aug 21:26:09 2005*
    * @method  CdmDataAccessHelper::CreateMember                   // public                            *
    * @return  CdmMember*                                    //                                   *
    * @param  qint64 p_lDbId                                  // database Id                       *
    * @param  qint64 p_lId                                    // Member Id                         *
    * @param   QString p_qstrkeyname                         // Member Keyname                    *
    * @param   int p_iType                                   // Value Type                        *
    * @param   bool p_bMust                                  // Is Must Value                     *
    * @param   int p_iSize                                   // Value Size                        *
    * @comment ONLY FOR INTERNAL USE!!!!                                                          *
    *          This method is a helper function for creating Members in derived classes.          *
    *----------------last changed: -----------------------------Sa 13. Aug 21:26:09 2005----------*/
static CdmMember* CreateMember( qint64 p_lDbId,
                        qint64 p_lId,
                         QString p_qstrkeyname,
                         int p_iType,
                         bool p_bMust,
                         int p_iSize );

   public:
   /** +-=---------------------------------------------------------Sa 13. Aug 21:34:35 2005*
    * @method  CdmDataAccessHelper::SetMemberSize                  // public                            *
    * @return  int                                           //                                   *
    * @param   CdmMember* p_pCdmMember                       //                                   *
    * @param  qint64 m_lSize                                  //                                   *
    * @comment ONLY FOR INTERNAL USE!!!!                                                          *
    *          This method sets the Value size.                                                   *
    *----------------last changed: -----------------------------Sa 13. Aug 21:34:35 2005----------*/
static int SetMemberSize(  CdmMember* p_pCdmMember,qint64 m_lSize );

   public:
   /** +-=---------------------------------------------------------Sa 13. Aug 21:35:05 2005*
    * @method  CdmDataAccessHelper::SetMemberMustValue             // public                            *
    * @return  int                                           //                                   *
    * @param   CdmMember* p_pCdmMember                       //                                   *
    * @param   bool p_bMustValue                             //                                   *
    * @comment ONLY FOR INTERNAL USE!!!!                                                          *
    *          This method sets the msut value flag                                               *
    *----------------last changed: -----------------------------Sa 13. Aug 21:35:05 2005----------*/
static int SetMemberMustValue(  CdmMember* p_pCdmMember, bool p_bMustValue );

   public:
   /** +-=---------------------------------------------------------Sa 13. Aug 21:36:13 2005*
    * @method  CdmDataAccessHelper::UpdateObjectWithClass          // public                            *
    * @return  int                                           //                                   *
    * @param   CdmObject* p_pCdmObject                       //                                   *
    * @param   CdmClass* p_pCdmClass                         //                                   *
    * @comment ONLY FOR INTERNAL USE!!!                                                           *
    *          This method updates an object with class.                                          *
    *          This means if a class has a new member a                                           *
    *          value must be created for the new member                                           *
    *          in the class.                                                                      *
    *----------------last changed: -----------------------------Sa 13. Aug 21:36:13 2005----------*/
static int UpdateObjectWithClass(  CdmObject* p_pCdmObject, CdmClass* p_pCdmClass );

   public:
   /** +-=---------------------------------------------------------Sa 13. Aug 21:32:00 2005*
    * @method  CdmDataAccessHelper::SetCreatorId                   // public                            *
    * @return  int                                           //                                   *
    * @param   CdmModelElement* p_pCdmBase                           //                                   *
    * @param  qint64 p_lId                                    //                                   *
    * @comment ONLY FOR INTERNAL USE!!!                                                           *
    *          This emthod sets the creator Id.                                                   *
    *----------------last changed: -----------------------------Sa 13. Aug 21:32:00 2005----------*/
static int SetCreatorId(  CdmModelElement* p_pCdmBase,qint64 p_lId );

   public:
   /** +-=---------------------------------------------------------Sa 13. Aug 21:32:20 2005*
    * @method  CdmDataAccessHelper::SetModifierId                  // public                            *
    * @return  int                                           //                                   *
    * @param   CdmModelElement* p_pCdmBase                           //                                   *
    * @param  qint64 p_lId                                    //                                   *
    * @comment ONLY FOR INTERNAL USE!!!                                                           *
    *          This method sets the modifier Id.                                                  *
    *----------------last changed: -----------------------------Sa 13. Aug 21:32:20 2005----------*/
static int SetModifierId(  CdmModelElement* p_pCdmBase,qint64 p_lId );

   public:
   /** +-=---------------------------------------------------------Sa 13. Aug 21:30:49 2005*
    * @method  CdmDataAccessHelper::SetValid                       // public                            *
    * @return  int                                           //                                   *
    * @param   CdmModelElement* p_pCdmBase                           //                                   *
    * @comment ONLY FOR INTERNAL USE!!!                                                           *
    *          This method sets the valid flag.                                                   *
    *----------------last changed: -----------------------------Sa 13. Aug 21:30:49 2005----------*/
static int SetValid(  CdmModelElement* p_pCdmBase );

   public:
   /** +-=---------------------------------------------------------Sa 13. Aug 21:34:16 2005*
    * @method  CdmDataAccessHelper::RemoveObjectFromObjectList     // public                            *
    * @return  int                                           //                                   *
    * @param   CdmObjectContainer* p_pContainer               //                                   *
    * @param  qint64 p_lObjectId                              //                                   *
    * @comment ONLY FOR INTERNAL USE!!!!!!                                                        *
    *          This method removes anobject from objectlist.                                      *
    *----------------last changed: -----------------------------Sa 13. Aug 21:34:16 2005----------*/
static int RemoveObjectFromObjectList(  CdmObjectContainer* p_pContainer,qint64 p_lObjectId );

   public:
   /** +-=---------------------------------------------------------Sa 13. Aug 21:32:35 2005*
    * @method  CdmDataAccessHelper::SetObjectInitialized           // public                            *
    * @return  int                                           //                                   *
    * @param   CdmObject* p_pCdmObject                       //                                   *
    * @comment ONLY FOR INTERNAL USE!!!                                                           *
    *          This method sets the initialized flag in the object.                               *
    *----------------last changed: -----------------------------Sa 13. Aug 21:32:35 2005----------*/
static int SetObjectInitialized(  CdmObject* p_pCdmObject );

   public:
   /** +-=---------------------------------------------------------Sa 13. Aug 21:33:46 2005*
    * @method  CdmDataAccessHelper::SetMemberClassId               // public                            *
    * @return  int                                           //                                   *
    * @param   CdmMember* p_pCdmMember                       //                                   *
    * @param  qint64 p_lClassId                               //                                   *
    * @comment ONLY FOR INTERNAL USE!!!                                                           *
    *          This method sets the clasid of the member.                                         *
    *----------------last changed: -----------------------------Sa 13. Aug 21:33:46 2005----------*/
static int SetMemberClassId(  CdmMember* p_pCdmMember,qint64 p_lClassId );


   public:
   /** +-=---------------------------------------------------------Sa 13. Aug 21:33:32 2005*
    * @method  CdmDataAccessHelper::SetObjectValueIdCounter        // public                            *
    * @return  int                                           //                                   *
    * @param   int p_iCounter                                //                                   *
    * @param   CdmObject* p_pCdmObject                       //                                   *
    * @comment ONLY FOR INTERNAL USE!!!!                                                          *
    *          This method sets the valueidcounter for the object.                                *
    *----------------last changed: -----------------------------Sa 13. Aug 21:33:32 2005----------*/
static int SetObjectValueIdCounter(  int p_iCounter, CdmObject* p_pCdmObject );

   public:
   /** +-=---------------------------------------------------------Sa 13. Aug 21:24:49 2005*
    * @method  CdmDataAccessHelper::SetNameAndIdOfDatabase         // public                            *
    * @return  int                                           //                                   *
    * @param  qint64 p_lId                                    // Database Id                       *
    * @param   QString p_qstrName                            // Database name                     *
    * @param   CdmScheme* p_pCdmDatabase                   // Database Object                   *
    * @comment ONLY FOR INTERNAL USE!!!!!!!                                                       *
    *          This method sets the name and id for a database                                    *
    *----------------last changed: -----------------------------Sa 13. Aug 21:24:49 2005----------*/
static int SetNameAndIdOfDatabase( qint64 p_lId, QString p_qstrName, CdmScheme* p_pCdmDatabase );


   public:
   /** +-=---------------------------------------------------------Do 1. Mai 16:36:53 2008--------*
    * @method  CdmDataAccessHelper::ValidateLicence                // public, static                    *
    * @return  int                                           // the number of licences            *
    * @param   QString p_qstrSoftware                        //                                   *
    * @param   QString p_qstrLicencee                        //                                   *
    * @param   QString p_qstrLicenceKey                      //                                   *
    * @param   int& p_iModules                               //                                   *
    * @param   QString p_qstrVersion                         //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 1. Mai 16:36:53 2008-----------*/
    static int ValidateLicence(QString p_qstrSoftware,
                               QString p_qstrLicencee,
                               QString p_qstrLicenceKey,
                               int& p_iModules,
                               QString p_qstrVersion);

   private:
   /** +-=---------------------------------------------------------Di 27. Dez 15:14:21 2005*
    * @method  CdmDataAccessHelper::DecodeInt                      // private, static                   *
    * @return  int                                           //                                   *
    * @param   QString p_qstrValue                           //                                   *
    * @comment this method decodes the integer.                                                   *
    *----------------last changed: Wolfgang Graßhof-------------Di 27. Dez 15:14:21 2005----------*/
static int DecodeInt(  QString p_qstrValue );

   private:
   /** +-=---------------------------------------------------------Di 27. Dez 15:14:28 2005*
    * @method  CdmDataAccessHelper::DecodeString                   // private, static                   *
    * @return  bool                                          //                                   *
    * @param   QString p_qstrString                          //                                   *
    * @param   QString p_qstrSource                          //                                   *
    * @comment This method decodes an string.                                                     *
    *----------------last changed: Wolfgang Graßhof-------------Di 27. Dez 15:14:28 2005----------*/
static bool DecodeString(  QString p_qstrString, QString p_qstrSource );

   public:
   /** +-=---------------------------------------------------------Do 29. Dez 12:11:30 2005*
    * @method  CdmDataAccessHelper::GetLicenceExpirationDate       // public, static                    *
    * @return  QDate                                         //                                   *
    * @param   QString p_qstrLicenceKey                      //                                   *
    * @comment This method returns the expirationdate of the licence.                             *
    *----------------last changed: Wolfgang Graßhof-------------Do 29. Dez 12:11:30 2005----------*/
static QDate GetLicenceExpirationDate(  QString p_qstrLicenceKey );

   public:
   /** +-=---------------------------------------------------------Fr 23. Mai 17:20:56 2008-------*
    * @method  CdmDataAccessHelper::RemoveMemberFromClass          // public                            *
    * @return qint64                                          //                                   *
    * @param   CdmClass* p_pCdmClass                         //                                   *
    * @param   CdmMember* p_pCdmMember                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 23. Mai 17:20:56 2008----------*/
    static qint64 RemoveMemberFromClass(CdmClass* p_pCdmClass, CdmMember* p_pCdmMember);

   public:
   /** +-=---------------------------------------------------------Mo 15. Okt 10:32:42 2012-------*
    * @method  CdmDataAccessHelper::SetQueryEnhancedResult         // public                            *
    * @return  void                                          //                                   *
    * @param   CdmQueryEnhanced* p_pCdmQuery                 //                                   *
    * @param   int p_iColumn                                 //                                   *
    * @param   QVariant p_qvValue                            //                                   *
    * @param  qint64 p_lObjectId                              //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 15. Okt 10:32:42 2012----------*/
    static void SetQueryEnhancedResult(CdmQueryEnhanced* p_pCdmQuery,
                                int p_iColumn,
                                QVariant p_qvValue,
                               qint64 p_lObjectId,
                               qint64 p_lContainerId);

   public:
   /** +-=---------------------------------------------------------Do 15. Nov 14:40:05 2012-------*
    * @method  CdmDataAccessHelper::UpdateMemberId                 // public                            *
    * @return  void                                          //                                   *
    * @param   CdmClass* p_pCdmClass                         //                                   *
    * @param   CdmMember* p_pCdmMember                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 15. Nov 14:40:05 2012----------*/
    static void UpdateMemberId(CdmClass* p_pCdmClass, CdmMember* p_pCdmMember);
    static void AddBaseClassToClass(CdmClass *p_pClass,qint64 p_lBaseClassId);

    static CdmPackage* CreatePackage(qint64 p_lSchemeId, QString p_qstrKeyname);
    static void AddPackageToClassManager(CdmClassManager* p_pClassManager, CdmPackage* p_pPackage);
    static void SetOriginalPackageName(CdmPackage *p_pPackage, QString p_qstrName);
    static void SetCurrentScheme(CdmScheme* p_pScheme);
    static CdmClass* CreateNewTestClass(qint64 scheme,qint64 classid, QString name);
    static CdmSession *CreateNewSession(qint64 p_lSessionId,qint64 p_lUser, IdmDataAccess *p_pDataAccess);
    static CdmClassManager *CreateClassManager(qint64 p_lSchemeId);
    static CdmClass *CreateClass(QVariantMap &p_qvMap);
    static CdmObjectContainer *CreateObjectContainer(qint64 p_lSchemeId,qint64 p_lContainerId, QString &p_qstrKeyname,qint64 p_lClassId);
    static CdmObjectContainer *CreateObjectContainer(QVariantMap &p_rMap);
    static void DeleteObjectContainer(CdmObjectContainer*& p_pContainer);
    static CdmObject* CreateObject(QVariantMap& p_rMap);
    static void DeleteObject(CdmObject*& p_pObject);
    static CdmObject *CreateObject(qint64 p_lSchemeId,qint64 p_lObjectId,qint64 p_lClassId,qint64 p_lContainerId);
};
#endif // //IdmDataAccess_H
