#include "CwnDataStructureHelper.h"

/** +-=---------------------------------------------------------Sa 7. Mai 11:22:07 2011-----------*
 * @method  CdbDataStructureHelper::GetFirstMember         // public, static                    *
 * @return  QString                                          //                                   *
 * @param   QString p_qstrMemberChain                        //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 7. Mai 11:22:07 2011-----------*/
QString CwnDataStructureHelper::GetFirstMember(QString p_qstrMemberChain)
{
   QString qstrRet;

   if (p_qstrMemberChain.contains("."))
   {
      int iPos = p_qstrMemberChain.indexOf(".");
      qstrRet = p_qstrMemberChain.left(iPos);
   }
   else
   {
      qstrRet = p_qstrMemberChain;
   }

   return qstrRet;
}

/** +-=---------------------------------------------------------Sa 7. Mai 11:48:45 2011-----------*
 * @method  CdbDataStructureHelper::GetLastMember          // public, static                    *
 * @return  QString                                          //                                   *
 * @param   QString p_qstrMemberChain                        //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 7. Mai 11:48:45 2011-----------*/
QString CwnDataStructureHelper::GetLastMember(QString p_qstrMemberChain)
{
   QString qstrRet;

   if (p_qstrMemberChain.contains("."))
   {
      int iPos = p_qstrMemberChain.lastIndexOf('.');
      qstrRet = p_qstrMemberChain.mid(iPos, p_qstrMemberChain.length() - iPos);
   }
   else
   {
      qstrRet = p_qstrMemberChain;
   }

   return qstrRet;
}
