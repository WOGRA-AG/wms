/******************************************************************************
 ** WOGRA Middleware Server Data Manager Module
 **
 ** @Author Wolfgang Graßhof
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 **(C) copyright by WOGRA technologies All rights reserved
 ******************************************************************************/

#ifndef CSCRIPTDATABASE
#define CSCRIPTDATABASE

// System and QT Includes

// own Includes
#include "datamanager.h"
#include "CsaLocatedElement.h"

// Forwards
class CdmScheme;

class WMSMANAGER_API CsaScheme : public CsaLocatedElement
{
    Q_OBJECT
    friend class CsaFactory;

private:
    CdmScheme* m_rpDatabase;

public:
    CdmScheme* getInternals();
    CsaScheme(CdmScheme* p_pDatabase);
    virtual ~CsaScheme();
    CsaScheme(): m_rpDatabase(NULL){}


public slots:

    QString getName();
    int getVersion();

    // CsaLocatedElement interface
public:
    virtual QVariant getDetailedVariant();

};

#endif //
