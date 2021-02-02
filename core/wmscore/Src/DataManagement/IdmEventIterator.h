#ifndef IDMEVENTITERATOR_H
#define IDMEVENTITERATOR_H

#include <QObject>

class IdmEventIterator
{
public:
    virtual bool hasNext() = 0;
    virtual QObject* next() = 0;
    virtual void setBacktoFirstElement() = 0;
};

#endif // IDMEVENTITERATOR_H
