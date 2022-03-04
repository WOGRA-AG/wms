#ifndef CWMSSCRIPTABLEUI_H
#define CWMSSCRIPTABLEUI_H

// System and QT Includes
#include <QScriptable>
#include <QObject>

// Own Includes
#include "CwmsScriptableBase.h"
#include "wmsgui.h"

// Forwards
class CdmObject;
class CdmObjectContainer;
class CdmClass;
class CsaObjectContainer;
class CsaClass;
class CsaObject;


/* 
 * This class implements ui calls for the script environment.
 */
class WMSGUI_API CwmsScriptableUi: public CwmsScriptableBase
{
    Q_OBJECT
public:
    CwmsScriptableUi( );
    virtual ~CwmsScriptableUi( );
public slots:
    QObject* selectObject(CsaObjectContainer *p_pContainer, QWidget *parent);
    QObject* selectObjectList(CsaClass *p_pCdmClass, QWidget *parent);
    QObject* selectClass(QWidget *parent);
    void openUi(QString p_qstrName, CsaObject *p_pCdmObject, QWidget *parent);
    void openUi(QString p_qstrName, CsaObjectContainer *p_pContainer, QWidget *parent);
    void openUi(QString p_qstrName, QWidget *parent);
    void openUi(CsaObject *p_pCdmObject, QWidget *parent);
    void openUi(CsaObjectContainer *p_pContainer, QWidget *parent);
    void openSearch(CsaObjectContainer *p_pContainer, QWidget *parent);
    void openImport(CsaObjectContainer *p_pContainer, QWidget *parent);
    void openExport(CsaObjectContainer* p_pContainer, QWidget *parent);
    void openHistory(CsaObjectContainer *p_pContainer, QWidget *parent);
    void openHistory(QObject *p_pCdmObject, QObject *parent);
    void editPrintingTemplate(CsaObject *p_pCdmObject, QWidget *parent);
    void editPrintingTemplate(CsaObjectContainer *p_pContainer, QWidget *parent);
    void createPrintingTemplate(QWidget *parent);
};

#endif // CWMSSCRIPTABLEUI_H

