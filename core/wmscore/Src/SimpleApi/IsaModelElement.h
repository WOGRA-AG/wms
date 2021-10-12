#ifndef ISAMODELELEMENT_H
#define ISAMODELELEMENT_H

//Qt includes
#include <QDateTime>
#include <QString>

class IsaModelElement
{
public slots:
    virtual QString getKeyname() = 0;
    virtual QString getCaption() = 0;
    virtual void setCaption(QString p_qstrCaption) = 0;
    virtual bool isModified() = 0;
    virtual bool isDeleted() = 0;
    virtual QDateTime getLastChanged() = 0;
    virtual int getCreatorId() = 0;
    virtual int getModifierId() = 0;
    virtual qint64 getId() = 0;
};

#endif // ISAMODELELEMENT_H
