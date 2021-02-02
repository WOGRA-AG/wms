#ifndef CWNDATASTRUCTUREHELPER_H
#define CWNDATASTRUCTUREHELPER_H

#include <QString>

class CwnDataStructureHelper
{

public:
/** +-=---------------------------------------------------------Sa 7. Mai 11:22:07 2011--------*
 * @method  CdbDataStructureHelper::GetFirstMember      // public, static                    *
 * @return  QString                                       //                                   *
 * @param   QString p_qstrMemberChain                     //                                   *
 * @comment                                                                                    *
 *----------------last changed: -----------------------------Sa 7. Mai 11:22:07 2011-----------*/
 static QString GetFirstMember(QString p_qstrMemberChain);

public:
/** +-=---------------------------------------------------------Sa 7. Mai 11:48:45 2011--------*
 * @method  CdbDataStructureHelper::GetLastMember       // public, static                    *
 * @return  QString                                       //                                   *
 * @param   QString p_qstrMemberChain                     //                                   *
 * @comment                                                                                    *
 *----------------last changed: -----------------------------Sa 7. Mai 11:48:45 2011-----------*/
 static QString GetLastMember(QString p_qstrMemberChain);

};

#endif // CWNDATASTRUCTUREHELPER_H
