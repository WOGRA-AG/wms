#ifndef CWNQUERYELEMENT_H
#define CWNQUERYELEMENT_H

#include "CwnQueryVariables.h"
#include "CwnHelper.h"

// System and QT Includes
#include <QLinkedList>

#include "CdmQueryElement.h"


// forwards
class CwnDataAccess;
class CdmQuery;

class CwnQueryElement
{

private:

   /*
    * The dataaccess
    */
   CwnDataAccess* m_rpCwnDataAccess;
   CdmQueryElement* pElement = nullptr;


   // The Children
   QLinkedList<CwnQueryElement*> m_qvlChildren;

   QString query;
   QString getLabel(EdmValueType type);

public:
    //The source query element
    CdmQueryElement* m_rpCdmQueryElement;
    CwnQueryElement(CwnDataAccess* p_pCwnDataAccess, CdmQueryElement* p_pCdmQueryElement);
    virtual ~CwnQueryElement();
    QString GenerateQuery();
    void GenerateVariablesForLaterUse(QString& qstrQuery);


private:
    bool con_reference=false;
    void CreateChildren(QLinkedList<CdmQueryElement*>& p_qvlChildren);
    QString GenerateAndQuery();
    QString GenerateOrQuery();
    QString GenerateValueQuery();
    QString GetCompareValueAsString();
    QString GetCompareSign();
    QString GetVariableAndPropertyName();
    QString GenerateStatement();
};

#endif // CWNQUERYELEMENT_H
