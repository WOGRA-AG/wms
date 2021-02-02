#ifndef IDMHANDLEDISPLAYDATA_H
#define IDMHANDLEDISPLAYDATA_H

#include <QVariant>
#include <QModelIndex>

class IdmHandleDisplayData
{
public:
    virtual ~IdmHandleDisplayData(){};
    virtual QVariant data(const QModelIndex & p_qmIndex, int p_iRole) = 0;
};

#endif // IDMHANDLEDISPLAYDATA_H
