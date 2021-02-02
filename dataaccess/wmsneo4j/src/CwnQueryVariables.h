#ifndef CWNQUERYVARIABLES_H
#define CWNQUERYVARIABLES_H

#include <QMap>
#include <QString>

class CwnQueryVariables
{
public:
    static int s_value;
    static int u_value;
    static int ug_value;
    static int or_value;
    static int olr_value;
    static int e_value;
    static int vc_ro_value;
    static int rv_value;
    static int rm_value;
    static QMap<QString,int> referenceObjects;
};

#endif // CWNQUERYVARIABLES_H
