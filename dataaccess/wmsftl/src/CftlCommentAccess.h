// Header is missing impl started on 3.1.2005

#ifndef CODBCCOMMENTACCESS_H
#define CODBCCOMMENTACCESS_H

// System and QT includes


// own Includes
#include "CftlDataAccess.h"


// forwards
class CftlDataAccess;


class CftlCommentAccess
{

   private:
      CftlDataAccess* m_rpCdmDataAccess;


   public:
   /** +-=---------------------------------------------------------Mo 3. Jan 19:26:47 2005*
    * @method  CftlCommentAccess::~CftlCommentAccess       // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CftlCommentAccess                                         *
    *                                                                                             *
    *----------------last changed: -----------------------------Mo 3. Jan 19:26:47 2005-----------*/
virtual ~CftlCommentAccess(  );

   public:
   /** +-=---------------------------------------------------------Mo 3. Jan 20:29:32 2005*
    * @method  CftlCommentAccess::InsertComment             // public                            *
    * @return  long                                          //                                   *
    * @param   long p_lId                                    //                                   *
    * @param   QString p_qstrComment                         //                                   *
    * @comment This method adds a comment to the comment table.                                   *
    *----------------last changed: -----------------------------Mo 3. Jan 20:29:32 2005-----------*/
long InsertComment(  long p_lId, QString p_qstrComment );

   public:
   /** +-=---------------------------------------------------------Mo 3. Jan 20:29:40 2005*
    * @method  CftlCommentAccess::UpdateComment             // public                            *
    * @return  long                                          //                                   *
    * @param   long p_lId                                    //                                   *
    * @param   QString p_qstrComment                         //                                   *
    * @comment This method adds a comment to the comment table.                                   *
    *----------------last changed: -----------------------------Mo 3. Jan 20:29:40 2005-----------*/
long UpdateComment(  long p_lId, QString p_qstrComment );

   public:
   /** +-=---------------------------------------------------------Mo 3. Jan 19:44:15 2005*
    * @method  CftlCommentAccess::CftlCommentAccess        // public                            *
    * @return                                                //                                   *
    * @param   CftlDataAccess* p_pCftlDataAccess           //                                   *
    * @comment The Constructor of the Comment Access.                                             *
    *----------------last changed: -----------------------------Mo 3. Jan 19:44:15 2005-----------*/
CftlCommentAccess(  CftlDataAccess* p_pCftlDataAccess );

   public:
   /** +-=---------------------------------------------------------Mo 3. Jan 20:24:30 2005*
    * @method  CftlCommentAccess::InsertOrUpdateComment     // public                            *
    * @return  long                                          //                                   *
    * @param   long p_lId                                    //                                   *
    * @param   QString p_qstrComment                         //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 3. Jan 20:24:30 2005-----------*/
long InsertOrUpdateComment(  long p_lId, QString p_qstrComment );

   public:
   /** +-=---------------------------------------------------------Mo 3. Jan 21:27:27 2005*
    * @method  CftlCommentAccess::GetComment                // public                            *
    * @return  long                                          //                                   *
    * @param   long p_lId                                    //                                   *
    * @param   QString& p_qstrComment                        //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 3. Jan 21:27:27 2005-----------*/
long GetComment(  long p_lId, QString& p_qstrComment );
};

#endif
