#ifndef CSAQMLREGISTRY_H
#define CSAQMLREGISTRY_H

#include "CsaValue.h"
#include "CsaObject.h"
#include "CsaObjectContainer.h"
#include "CsaMember.h"
#include "CdmObjectAdaptor.h"
#include "CdmObjectContainer.h"
#include "CdmQueryModel.h"
#include "CumUser.h"
#include "CdmValue.h"
#include "CdmObject.h"


class CsaQmlRegistry
{
public:
    static void registerTypes();
private:
    static void registerCreatableTypes();
    static void registerUncreatableTypes();
};

#endif // CSAQMLREGISTRY_H
