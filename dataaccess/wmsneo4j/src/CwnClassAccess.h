#ifndef CWNCLASSACCESS_H
#define CWNCLASSACCESS_H

/******************************************************************************
 ** WOGRA Middleware Server Data Manager Module
 **
 ** @Author Wolfgang Gra�hof
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 **(C) copyright by WOGRA technologies All rights reserved
 ******************************************************************************/

// System and QT Includes
#include <qstring.h>
#include <QList>


// own Includes
#include "CdmLocatedElement.h"
#include "CwnDataAccess.h"

// forwards
class CdmClass;
class CdmMember;
class CdmClassManager;
class CwnDataAccess;
class CdmClassGroup;


/*
 * This class implements the access to class over neo4j
 */
class CwnClassAccess
{

   protected:
      /*
       * The DataAccess
       */
      CwnDataAccess* m_rpCwnDataAccess;

      /*
       * The new class counter
       */
      int m_iNewClassCounter;



   public:
   /** +-=---------------------------------------------------------Sa 20. Aug 11:40:53 2005*
    * @method  CwnClassAccess::CwnClassAccess            // public                            *
    * @return                                                //                                   *
    * @param   CwnDataAccess* p_pCwnDataAccess           //                                   *
    * @comment The constructor.                                                                   *
    *----------------last changed: -----------------------------Sa 20. Aug 11:40:53 2005----------*/
CwnClassAccess(CwnDataAccess* p_pCwnDataAccess);

   public:
   /** +-=---------------------------------------------------------Sa 20. Aug 11:41:01 2005*
    * @method  CwnClassAccess::~CwnClassAccess           // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CwnClassAccess                                           *
    *----------------last changed: -----------------------------Sa 20. Aug 11:41:01 2005----------*/
virtual ~CwnClassAccess();

   public:
   /** +-=---------------------------------------------------------Fr 25. Jun 13:27:50 2004*
    * @method  CwnClassAccess::GetNewClassId               // public                            *
    * @return  long                                          //                                   *
    * @param   long p_lDbId                                  //                                   *
    * @comment This mehtod returns a new class id for a new class.                                *
    *----------------last changed: Wolfgang Gra�hof-------------Fr 25. Jun 13:27:50 2004----------*/
long GetNewClassId(long p_lDbId);

   public:
   /** +-=---------------------------------------------------------Fr 25. Jun 13:31:50 2004*
    * @method  CwnClassAccess::ExistClass                  // public                            *
    * @return  long                                          //                                   *
    * @param   long p_lDbId                                  //                                   *
    * @param   QString p_qstrKeyname                         //                                   *
    * @param   bool& p_bRet                                  //                                   *
    * @comment This method checks if the class with the overgiven keyname exists.                 *
    *----------------last changed: Wolfgang Gra�hof-------------Fr 25. Jun 13:31:50 2004----------*/
long ExistClass(long p_lDbId, QString p_qstrKeyname, bool& p_bRet);

   public:
   /** +-=---------------------------------------------------------Fr 25. Jun 13:37:36 2004*
    * @method  CwnClassAccess::LoadClassManager            // public                            *
    * @return  long                                          //                                   *
    * @param   long p_lDbId                                  //                                   *
    * @param   CdmClassManager*& p_rpCdmClassManager         //                                   *
    * @comment This method loads the complete class manager of a class.                           *
    *----------------last changed: Wolfgang Gra�hof-------------Fr 25. Jun 13:37:36 2004----------*/
long LoadClassManager(  long p_lDbId, CdmClassManager*& p_rpCdmClassManager );

   public:
   /** +-=---------------------------------------------------------Mo 9. Jun 14:56:10 2008--------*
    * @method  CwnClassAccess::DeleteMember                // public                            *
    * @return  long                                          //                                   *
    * @param   long p_lMemberId                              //                                   *
    * @comment This method deletes a Member.                                                      *
    *----------------last changed: -----------------------------Mo 9. Jun 14:56:10 2008-----------*/
    long DeleteMember(long p_lMemberId);

   public:
   /** +-=---------------------------------------------------------So 11. Sep 11:41:31 2005*
    * @method  CwnClassAccess::GetNewClassId               // public, virtual                   *
    * @return  long                                          //                                   *
    * @param   long p_lDataBaseId                            //                                   *
    * @param   long p_lSessionId                             //                                   *
    * @comment This mehtod returns a new class id for a new class.                                *
    *----------------last changed: -----------------------------So 11. Sep 11:41:31 2005----------*/
virtual long GetNewClassId(long p_lDataBaseId, long p_lSessionId);


   public:
   /** +-=---------------------------------------------------------Fr 8. Aug 21:18:37 2008--------*
    * @method  CwnClassAccess::UpdateClass                 // public, virtual                   *
    * @return  long                                          //                                   *
    * @param   CdmClass*& p_rpCdmClass                       //                                   *
    * @comment This method updates a class.                                                       *
    *----------------last changed: -----------------------------Fr 8. Aug 21:18:37 2008-----------*/
    virtual long UpdateClass(CdmClass*& p_rpCdmClass);

   public:
   /** +-=---------------------------------------------------------Di 23. Aug 15:49:41 2005*
    * @method  CwnClassAccess::DeleteClass                 // public, virtual                   *
    * @return  long                                          //                                   *
    * @param   long p_lClassId                               //                                   *
    * @comment This method deletes a class from db.                                               *
    *----------------last changed: -----------------------------Di 23. Aug 15:49:41 2005----------*/
    virtual long DeleteClass(  long p_lClassId );
    int CreatePackage(CdmPackage *&p_pCdmPackage);
    int UpdatePackageP(CdmPackage *&p_pCdmPackage);
    int DeletePackage(CdmPackage *&p_pCdmPackage);
    void ResolvePackages(QList<CdmPackage *> &p_rqlUnresolvedPackages);
    void ResolvePackage(CdmPackage *p_pPackage, QList<CdmPackage *> &p_rqlUnresolvedPackages);
    bool LockMethod(long p_lSessionId, int p_lMethodId);
    bool UnlockMethod(long p_lSessionId, int p_lMethodId);
    int UpdatePackage(CdmPackage*& p_pCdmPackage);
    void LoadPackages(CdmClassManager* p_pClassManager);
};

#endif // CWNCLASSACCESS_H
