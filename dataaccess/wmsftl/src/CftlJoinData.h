#ifndef CFTLJOINDATA_H
#define CFTLJOINDATA_H


// System and QT Includes
#include <QString>
#include <QStringList>


// own Includes


// forwards


class CftlJoinData
{
    QString m_qstrJoin;
    QString m_qstrJoinName;
    QString m_qstrJoinPartner;
    QString m_qstrReferenceMemberName;
    QStringList m_qstrlSearchableMembers;
    static QString JoinTemplate;
    static int sInt;



public:
    CftlJoinData(QString p_qstrJoin, QString p_qstrJoinName, QString p_qstrReferenceMemberName);
    CftlJoinData(QString p_qstrJoin, QString p_qstrJoinName, QString p_qstrReferenceMemberName, QString p_qstrJoinPartner);

    QString GenerateJoin() const;

    void AddJoinMember(QString p_qstrMember);

    QString GetJoinName() const;
    QString GetJoinPartner() const;
    bool HasJoinPartner() const;



private:
    static QString GetJoinTemplate();
};

#endif // CFTLJOINDATA_H
