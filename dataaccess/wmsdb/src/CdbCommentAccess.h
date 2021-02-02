// Header is missing impl started on 3.1.2005

#ifndef CODBCCOMMENTACCESS_H
#define CODBCCOMMENTACCESS_H

// System and QT includes


// own Includes
#include "CdbDataAccess.h"


// forwards
class CdbDataAccess;


class CdbCommentAccess
{

   private:
      CdbDataAccess* m_rpCdmDataAccess;


   public:
   /** +-=---------------------------------------------------------Mo 3. Jan 19:26:47 2005*
    * @method  CdbCommentAccess::~CdbCommentAccess       // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CdbCommentAccess                                         *
    *                                                                                             *
    *----------------last changed: -----------------------------Mo 3. Jan 19:26:47 2005-----------*/
virtual ~CdbCommentAccess(  );

   public:
   /** +-=---------------------------------------------------------Mo 3. Jan 20:29:32 2005*
    * @method  CdbCommentAccess::InsertComment             // public                            *
    * @return  long                                          //                                   *
    * @param   long p_lId                                    //                                   *
    * @param   QString p_qstrComment                         //                                   *
    * @comment This method adds a comment to the comment table.                                   *
    *----------------last changed: -----------------------------Mo 3. Jan 20:29:32 2005-----------*/
long InsertComment(  long p_lId, QString p_qstrComment );

   public:
   /** +-=---------------------------------------------------------Mo 3. Jan 20:29:40 2005*
    * @method  CdbCommentAccess::UpdateComment             // public                            *
    * @return  long                                          //                                   *
    * @param   long p_lId                                    //                                   *
    * @param   QString p_qstrComment                         //                                   *
    * @comment This method adds a comment to the comment table.                                   *
    *----------------last changed: -----------------------------Mo 3. Jan 20:29:40 2005-----------*/
long UpdateComment(  long p_lId, QString p_qstrComment );

   public:
   /** +-=---------------------------------------------------------Mo 3. Jan 19:44:15 2005*
    * @method  CdbCommentAccess::CdbCommentAccess        // public                            *
    * @return                                                //                                   *
    * @param   CdbDataAccess* p_pCdbDataAccess           //                                   *
    * @comment The Constructor of the Comment Access.                                             *
    *----------------last changed: -----------------------------Mo 3. Jan 19:44:15 2005-----------*/
CdbCommentAccess(  CdbDataAccess* p_pCdbDataAccess );

   public:
   /** +-=---------------------------------------------------------Mo 3. Jan 20:24:30 2005*
    * @method  CdbCommentAccess::InsertOrUpdateComment     // public                            *
    * @return  long                                          //                                   *
    * @param   long p_lId                                    //                                   *
    * @param   QString p_qstrComment                         //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 3. Jan 20:24:30 2005-----------*/
long InsertOrUpdateComment(  long p_lId, QString p_qstrComment );

   public:
   /** +-=---------------------------------------------------------Mo 3. Jan 21:27:27 2005*
    * @method  CdbCommentAccess::GetComment                // public                            *
    * @return  long                                          //                                   *
    * @param   long p_lId                                    //                                   *
    * @param   QString& p_qstrComment                        //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 3. Jan 21:27:27 2005-----------*/
long GetComment(  long p_lId, QString& p_qstrComment );
};

#endif
