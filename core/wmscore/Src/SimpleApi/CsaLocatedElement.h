/******************************************************************************
 ** WOGRA Middleware Server Data Manager Module
 **
 ** @Author Wolfgang Graßhof
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 **(C) copyright by WOGRA technologies All rights reserved
 ******************************************************************************/

#ifndef CSALOCATEDELEMENT_H
#define CSALOCATEDELEMENT_H

// System and QT Includes
#include <QObject>

#include "CwsHttpRequest.h"
#include "CwsHttpResponse.h"

// own Includes
#include "../../Src/DataManagement/datamanager.h"
#include "../../Src/DataManagement/CdmLogging.h"
#include "IsaLocatedElement.h"

// Forwards
class IdmExecutorEngine;
class CsaFactory;
class CdmLocatedElement;

class WMSMANAGER_API CsaLocatedElement : public QObject, public IsaLocatedElement
{
    Q_OBJECT
    friend class CsaFactory;


protected:
    CsaFactory* m_rpFactory;
    QString m_qstrUriInternal;


protected:
    CsaLocatedElement(QObject* parent = NULL);
    virtual ~CsaLocatedElement();
    virtual QVariant generateLinkRestSection();
    QVariant generateLinkMap(QString qstrLinkName, const CdmLocatedElement *p_pElement);
    QVariant generateLinkMap(QString qstrLinkName, const CdmLocatedElement *p_pElement, QString p_qstrLink);
    QVariant generateLinkMap(QString qstrLinkName, QString qstrLink);

public slots:
    virtual CsaFactory* getFactory();
    virtual QObject* getManager();
    virtual QObject* getContainerManager();
    virtual QObject* getClassManager();
    virtual QObject* getScheme();
    virtual bool isValue();
    virtual bool isMember();
    virtual bool isClass();
    virtual bool isContainer();
    virtual bool isObject();
    virtual bool isModelElement();
    virtual bool isReference();

    virtual QString getUri() const;
public:
    IdmExecutorEngine* getEngine();
    virtual void setFactory(CsaFactory* p_pFactory);
    void setElement(CdmLocatedElement *p_pElement);
    virtual CdmLocatedElement *getElement();
    virtual QVariant getDetailedVariant() = 0;
    void setElement(QString p_qstrUri);
    virtual QString getUriInternal() const;
};

#endif //
