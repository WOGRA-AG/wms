// Header is missing impl started on 3.1.2005


// System and QT Includes
#include <qsqlquery.h>
#include <qstring.h>


// own Includes
#include "CdmError.h"
#include "CftlDataAccess.h"
#include "CftlCommentAccess.h"


/** +-=---------------------------------------------------------Mo 3. Jan 19:44:15 2005-----------*
 * @method  CftlCommentAccess::CftlCommentAccess           // public                            *
 * @return                                                   //                                   *
 * @param   CftlDataAccess* p_pCftlDataAccess              //                                   *
 * @comment The Constructor of the Comment Access.                                                *
 *----------------last changed: --------------------------------Mo 3. Jan 19:44:15 2005-----------*/
CftlCommentAccess::CftlCommentAccess(  CftlDataAccess* p_pCftlDataAccess )
   : m_rpCdmDataAccess(p_pCftlDataAccess)
{
}

/** +-=---------------------------------------------------------Mo 3. Jan 19:26:47 2005-----------*
 * @method  CftlCommentAccess::~CftlCommentAccess          // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CftlCommentAccess                                            *
 *                                                                                                *
 *----------------last changed: --------------------------------Mo 3. Jan 19:26:47 2005-----------*/
CftlCommentAccess::~CftlCommentAccess(  )
{
   // nothing to do 
}


/** +-=---------------------------------------------------------Mo 3. Jan 20:29:32 2005-----------*
 * @method  CftlCommentAccess::InsertComment                // public                            *
 * @return  long                                             //                                   *
 * @param   long p_lId                                       //                                   *
 * @param   QString p_qstrComment                            //                                   *
 * @comment This method adds a comment to the comment table.                                      *
 *----------------last changed: --------------------------------Mo 3. Jan 20:29:32 2005-----------*/
long CftlCommentAccess::InsertComment(  long p_lId, QString p_qstrComment )
{
   long lRet = -1;

   QSqlQuery cQSqlQuery;
   QString qstrQuery;
   
   qstrQuery = QString("insert into WMS_Comment (BaseId, Comment) values(%1, '%2')")
                       .arg(p_lId)
                       .arg(p_qstrComment);
   
   lRet = m_rpCdmDataAccess->ExecuteQuery(qstrQuery, cQSqlQuery);
   
   if(lRet < 0)
   {
      ERR("Insert not possible for Comments!!");
   }

   return lRet;
}

/** +-=---------------------------------------------------------Mo 3. Jan 20:29:40 2005-----------*
 * @method  CftlCommentAccess::UpdateComment                // public                            *
 * @return  long                                             //                                   *
 * @param   long p_lId                                       //                                   *
 * @param   QString p_qstrComment                            //                                   *
 * @comment This method adds a comment to the comment table.                                      *
 *----------------last changed: --------------------------------Mo 3. Jan 20:29:40 2005-----------*/
long CftlCommentAccess::UpdateComment(  long p_lId, QString p_qstrComment )
{
   long lRet = -1;

   QSqlQuery cQSqlQuery;
   QString qstrQuery;
   
   qstrQuery = QString("delete from WMS_Comment where BaseId = %1")
                       .arg(p_lId);
   
   lRet = m_rpCdmDataAccess->ExecuteQuery(qstrQuery, cQSqlQuery);
   
   if(lRet < 0)
   {
      ERR("Update not possible for Comment!!");
   }
   else
   {
      lRet = InsertComment(p_lId, p_qstrComment);
   }
   
   return lRet;
}


/** +-=---------------------------------------------------------Mo 3. Jan 20:24:30 2005-----------*
 * @method  CftlCommentAccess::InsertOrUpdateComment        // public                            *
 * @return  long                                             //                                   *
 * @param   long p_lId                                       //                                   *
 * @param   QString p_qstrComment                            //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 3. Jan 20:24:30 2005-----------*/
long CftlCommentAccess::InsertOrUpdateComment(  long p_lId, QString p_qstrComment )
{
   long lRet = -1;

   QSqlQuery cQSqlQuery;
   QString qstrQuery;
   
   qstrQuery = QString("select BaseId from WMS_Comment  where BaseId = %1")
                       .arg(p_lId);
   
   lRet = m_rpCdmDataAccess->ExecuteQuery(qstrQuery, cQSqlQuery);
   
   if(lRet > 0)
   {
      if(cQSqlQuery.numRowsAffected() == 1)
      {
         lRet = UpdateComment(p_lId, p_qstrComment);
      }
      else
      {
         lRet = InsertComment(p_lId, p_qstrComment);
      }
   }

   return lRet;
}

/** +-=---------------------------------------------------------Mo 3. Jan 21:27:27 2005-----------*
 * @method  CftlCommentAccess::GetComment                   // public                            *
 * @return  long                                             //                                   *
 * @param   long p_lId                                       //                                   *
 * @param   QString& p_qstrComment                           //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 3. Jan 21:27:27 2005-----------*/
long CftlCommentAccess::GetComment(  long p_lId, QString& p_qstrComment )
{
   long lRet = -1;

   QSqlQuery cQSqlQuery;
   QString qstrQuery;
   
   qstrQuery = QString("select Comment from WMS_Comment where BaseId = %1")
                       .arg(p_lId);
   
   lRet = m_rpCdmDataAccess->ExecuteQuery(qstrQuery, cQSqlQuery);
   
   if(lRet > 0)
   {
      if(cQSqlQuery.numRowsAffected() == 1)
      {
         cQSqlQuery.first();
         p_qstrComment = cQSqlQuery.value(0).toString();

      }
   }

   return lRet;
}