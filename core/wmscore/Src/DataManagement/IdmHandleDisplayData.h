#ifndef IDMHANDLEDISPLAYDATA_H
#define IDMHANDLEDISPLAYDATA_H

#include <QVariant>
#include <QModelIndex>


// this handler is able to handle view options over multi columns
// if you need handling o8f one specific column use IwmsViewProxy
class IdmHandleDisplayData
{
public:
    virtual ~IdmHandleDisplayData(){};
    virtual QVariant data(const QModelIndex & p_qmIndex, int p_iRole) = 0;
};

#endif // IDMHANDLEDISPLAYDATA_H
