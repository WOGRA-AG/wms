#ifndef CWMSSYMBOLSEARCH_H
#define CWMSSYMBOLSEARCH_H

// System and QT Includes
#include <QList>

// Own Includes

// Forwards
class CdmClass;
class CdmMember;
class CdmClassMethod;

class CwmsSymbolSearch
{
private:
    QString m_qstrSearch;
    bool m_bClass;
    bool m_bMembers;
    bool m_bMethods;

    QList<CdmClass*> m_qlFoundClasses;
    QList<CdmMember*> m_qlFoundMembers;
    QList<CdmClassMethod*> m_qlFoundMethods;

    void ClassSearch();
    void MethodSearch(CdmClass *p_pClass);
    void MemberSearch(CdmClass *p_pClass);
    bool CheckElement(CdmModelElement *p_pElement);
public:
    CwmsSymbolSearch(QString p_qstrSearch, bool p_bClass, bool p_bMembers, bool p_bMethods);
    ~CwmsSymbolSearch();
    void Execute();
    QList<CdmClass*> GetFoundClasses() const { return m_qlFoundClasses; }
    QList<CdmMember*> GetFoundMembers() const { return m_qlFoundMembers; }
    QList<CdmClassMethod*> GetFoundMethods() const { return m_qlFoundMethods; }

};

#endif // CWMSSYMBOLSEARCH_H
