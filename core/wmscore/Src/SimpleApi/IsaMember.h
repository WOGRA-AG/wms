#ifndef ISAMEMBER_H
#define ISAMEMBER_H

//Qt includes
#include <QString>
#include <QVariant>

class IsaMember
{
public slots:
    virtual int getType() = 0;
    virtual QString getTypeAsString() = 0;
    virtual int getAccessMode() = 0;
    virtual bool isPrivate() = 0;
    virtual bool isProtected() = 0;
    virtual bool isPublic() = 0;
    virtual bool isMust() = 0;
    virtual bool isTree() = 0;
    virtual bool isPersistent() = 0;
    virtual bool isUnique() = 0;
    virtual bool isSystemMember() = 0;
    virtual int getSize() = 0;
    virtual int getCounterStart() = 0;
    virtual int getDecimalCountOutput() = 0;
    virtual int getDecimalCountInput() = 0;
    virtual QString getPrefix() = 0;
    virtual QString getSufffix() = 0;
    virtual QString getGroupName() = 0;
    virtual QVariant getDefault() = 0;
};

#endif // ISAMEMBER_H
