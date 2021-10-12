#ifndef CODBCCLASSACCESS_H
#define CODBCCLASSACCESS_H

// System and QT Includes
#include <qstring.h>
#include <QList>


// own Includes
#include "CdmLocatedElement.h"
#include "CftlDataAccess.h"

// forwards
class CdmClass;
class CdmMember;
class CdmClassManager;
class CftlDataAccess;
class CdmClassGroup;


/*
 * This class implements the access to class over odbc
 */
class CftlClassAccess
{

   protected:
      /*
       * The DataAccess
       */
      CftlDataAccess* m_rpCftlDataAccess;

      /*
       * The new class counter
       */
      int m_iNewClassCounter;



   public:
   /** +-=---------------------------------------------------------Sa 20. Aug 11:40:53 2005*
    * @method  CftlClassAccess::CftlClassAccess            // public                            *
    * @return                                                //                                   *
    * @param   CftlDataAccess* p_pCftlDataAccess           //                                   *
    * @comment The constructor.                                                                   *
    *----------------last changed: -----------------------------Sa 20. Aug 11:40:53 2005----------*/
CftlClassAccess(CftlDataAccess* p_pCftlDataAccess);

   public:
   /** +-=---------------------------------------------------------Sa 20. Aug 11:41:01 2005*
    * @method  CftlClassAccess::~CftlClassAccess           // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CftlClassAccess                                           *
    *----------------last changed: -----------------------------Sa 20. Aug 11:41:01 2005----------*/
virtual ~CftlClassAccess();

   public:
   /** +-=---------------------------------------------------------Fr 25. Jun 13:27:50 2004*
    * @method  CftlClassAccess::GetNewClassId               // public                            *
    * @return qint64                                          //                                   *
    * @param  qint64 p_lDbId                                  //                                   *
    * @comment This mehtod returns a new class id for a new class.                                *
    *----------------last changed: Wolfgang Graßhof-------------Fr 25. Jun 13:27:50 2004----------*/
qint64 GetNewClassId(qint64 p_lDbId);

   public:
   /** +-=---------------------------------------------------------Fr 25. Jun 13:31:50 2004*
    * @method  CftlClassAccess::ExistClass                  // public                            *
    * @return qint64                                          //                                   *
    * @param  qint64 p_lDbId                                  //                                   *
    * @param   QString p_qstrKeyname                         //                                   *
    * @param   bool& p_bRet                                  //                                   *
    * @comment This method checks if the class with the overgiven keyname exists.                 *
    *----------------last changed: Wolfgang Graßhof-------------Fr 25. Jun 13:31:50 2004----------*/
qint64 ExistClass(qint64 p_lDbId, QString p_qstrKeyname, bool& p_bRet);

   public:
   /** +-=---------------------------------------------------------Fr 25. Jun 13:37:36 2004*
    * @method  CftlClassAccess::LoadClassManager            // public                            *
    * @return qint64                                          //                                   *
    * @param  qint64 p_lDbId                                  //                                   *
    * @param   CdmClassManager*& p_rpCdmClassManager         //                                   *
    * @comment This method loads the complete class manager of a class.                           *
    *----------------last changed: Wolfgang Graßhof-------------Fr 25. Jun 13:37:36 2004----------*/
qint64 LoadClassManager( qint64 p_lDbId, CdmClassManager*& p_rpCdmClassManager );

   public:
   /** +-=---------------------------------------------------------Mo 9. Jun 14:56:10 2008--------*
    * @method  CftlClassAccess::DeleteMember                // public                            *
    * @return qint64                                          //                                   *
    * @param  qint64 p_lMemberId                              //                                   *
    * @comment This method deletes a Member.                                                      *
    *----------------last changed: -----------------------------Mo 9. Jun 14:56:10 2008-----------*/
   qint64 DeleteMember(qint64 p_lMemberId);

   public:
   /** +-=---------------------------------------------------------So 11. Sep 11:41:31 2005*
    * @method  CftlClassAccess::GetNewClassId               // public, virtual                   *
    * @return qint64                                          //                                   *
    * @param  qint64 p_lDataBaseId                            //                                   *
    * @param  qint64 p_lSessionId                             //                                   *
    * @comment This mehtod returns a new class id for a new class.                                *
    *----------------last changed: -----------------------------So 11. Sep 11:41:31 2005----------*/
virtual qint64 GetNewClassId(qint64 p_lDataBaseId,qint64 p_lSessionId);


   public:
   /** +-=---------------------------------------------------------Fr 8. Aug 21:18:37 2008--------*
    * @method  CftlClassAccess::UpdateClass                 // public, virtual                   *
    * @return qint64                                          //                                   *
    * @param   CdmClass*& p_rpCdmClass                       //                                   *
    * @comment This method updates a class.                                                       *
    *----------------last changed: -----------------------------Fr 8. Aug 21:18:37 2008-----------*/
    virtual qint64 UpdateClass(CdmClass*& p_rpCdmClass);

   public:
   /** +-=---------------------------------------------------------Di 23. Aug 15:49:41 2005*
    * @method  CftlClassAccess::DeleteClass                 // public, virtual                   *
    * @return qint64                                          //                                   *
    * @param  qint64 p_lClassId                               //                                   *
    * @comment This method deletes a class from db.                                               *
    *----------------last changed: -----------------------------Di 23. Aug 15:49:41 2005----------*/
    virtual qint64 DeleteClass( qint64 p_lClassId );
    int CreatePackage(CdmPackage *&p_pCdmPackage);
    int UpdatePackageP(CdmPackage *&p_pCdmPackage);
    int DeletePackage(CdmPackage *&p_pCdmPackage);
    void ResolvePackages(QList<CdmPackage *> &p_rqlUnresolvedPackages);
    void ResolvePackage(CdmPackage *p_pPackage, QList<CdmPackage *> &p_rqlUnresolvedPackages);
    bool LockMethod(int p_lMethodId);
    bool UnlockMethod(int p_lMethodId);
    int UpdatePackage(CdmPackage*& p_pCdmPackage);
    void LoadPackages(CdmClassManager* p_pClassManager);
};

#endif //
