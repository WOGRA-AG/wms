#ifndef CSCRIPTBASE_H
#define CSCRIPTBASE_H

// System and QT Includes
#include <QDateTime>

// own Includes
#include "datamanager.h"
#include "CsaLocatedElement.h"
#include "IsaModelElement.h"

// Forwards
class CsaFactory;
class CdmModelElement;

class WMSMANAGER_API CsaModelElement : public CsaLocatedElement, public IsaModelElement
{
    Q_OBJECT
    friend class CsaFactory;

protected:
    CsaModelElement(CdmModelElement* p_pElement, QObject* parent = NULL);
    virtual ~CsaModelElement();

    void addMainRestLinks(QVariantList &p_rqVariantList);
    virtual QVariant generateLinkRestSection();
    void addVariantData(QVariantMap &p_qvm);
    bool isSessionUserAdmin();
public slots:
    virtual QString getKeyname();
    virtual QString getCaption();
    virtual void setCaption(QString p_qstrCaption);
    virtual bool isModified();
    virtual bool isDeleted();
    virtual QDateTime getLastChanged();
    virtual int getCreatorId();
    virtual int getModifierId();
    virtual qint64 getId();
};

#endif //
