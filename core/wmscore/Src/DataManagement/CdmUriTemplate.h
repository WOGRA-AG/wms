#ifndef CSRAURITEMPLATE_H
#define CSRAURITEMPLATE_H

#include <QString>
#include <QMap>

class CdmUriTemplate
{
private:
    QString m_qstrTemplate;

public:
    CdmUriTemplate(QString qstrTemplate);
    virtual ~CdmUriTemplate();
    QString getTemplate();
    QString expand(QMap<QString, QString> qmUriVariables);
    QMap<QString, QString> match(QString qstrUri);
};

#endif // CSRAURITEMPLATE_H
