/******************************************************************************
 ** WOGRA Middleware Server Data Manager Module
 **
 ** @Author Wolfgang Graßhof
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 **(C) copyright by WOGRA technologies All rights reserved
 ******************************************************************************/


#ifndef CSCRIPTCLASSMANAGER
#define CSCRIPTCLASSMANAGER

// System and QT Includes

// own Includes
#include "datamanager.h"
#include "CsaLocatedElement.h"

// Forwards
class CdmClassManager;

class WMSMANAGER_API CsaClassManager : public CsaLocatedElement
{
    Q_OBJECT

friend class CsaFactory;

    private:
        CdmClassManager* m_pClassManager;
        CsaClassManager(CdmClassManager* p_pClassManager);
        virtual ~CsaClassManager();

    public slots:
        QObject *findClass(QString p_qstrKeyname);
        QVariantList getClassList();
        bool existClass(QString p_qstrKeyname);

    public:
        CdmClassManager* getInternals();



        // CsaLocatedElement interface
public:
        virtual QVariant getDetailedVariant();

};

#endif //
