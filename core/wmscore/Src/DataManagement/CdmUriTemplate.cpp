#include "CdmUriTemplate.h"

CdmUriTemplate::CdmUriTemplate(QString qstrTemplate)
    : m_qstrTemplate(qstrTemplate)
{

}

CdmUriTemplate::~CdmUriTemplate()
{

}

QString CdmUriTemplate::getTemplate()
{
    return m_qstrTemplate;
}

QString CdmUriTemplate::expand(QMap<QString, QString> qmUriVariables)
{
    for(auto key : qmUriVariables.keys())
    {
        if(m_qstrTemplate.contains("{"+key+"}"))
        {
            m_qstrTemplate.replace("{"+key+"}", qmUriVariables.value(key));
        }
    }
    return m_qstrTemplate;
}

QMap<QString,QString> CdmUriTemplate::match(QString qstrUri)
{
    QMap<QString, QString> matches;

    QStringList qstrlTemplateElements;
    qstrlTemplateElements.append(m_qstrTemplate.split("/"));

    QStringList qstrlUriElements;
    qstrlUriElements.append(qstrUri.split("/"));

    for(int i = 0; i < qstrlTemplateElements.size(); i++)
    {
        QString element = qstrlTemplateElements.at(i);
        if(element.startsWith("{") && element.endsWith("}") && qstrlUriElements.size() >= i)
        {
            element = element.mid(1, element.length()-2);
            matches.insert(element, qstrlUriElements.at(i));
        }
    }
    return matches;
}

