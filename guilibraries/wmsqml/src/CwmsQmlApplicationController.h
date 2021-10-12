#ifndef CWMSQMLAPPLICATIONCONTROLLER_H
#define CWMSQMLAPPLICATIONCONTROLLER_H

// System and QT Includes
#include <QString>
#include <qqmlapplicationengine.h>
#include <QList>
#include <QStack>
#include <QObject>
#include <QUrl>

// WMS Includes
#include "CsaFactory.h"
#include "CdmModelElement.h"

// Basetools Includes


// own Includes
#include "CwmsQmlLogin.h"
#include "CwmsQmlEngineInitializer.h"
#include "CwmsDataAccessConfiguration.h"
#include "wmsqml_global.h"

// Forwards
class CwmsQmlStyle;
class CwmsQmlWidget;
class CwmsqmlApplication;
class QQmlContext;
class QQuickWindow;
class QQuickView;
class CdmQueryModel;
class QQuickItem;
class CwmsApplication;
class CdmObject;
class CdmObjectContainer;
class CsaObject;
class CsaObjectContainer;

// TypeDefs

// enums

class WMSQML_EXPORT CwmsQmlApplicationController : public CwmsQmlEngineInitializer
{
   Q_OBJECT

private:
     static CwmsQmlApplicationController* m_spController;
     bool m_bDevelopmentMode;
     QStack<CwmsQmlWidget*> m_qlWidgetStack;
     CwmsQmlLogin m_cLogin;
     QQuickItem* m_rpItem;
     CwmsDataAccessConfiguration m_cDataAccessConfiguration;
     CwmsInitApplication* m_rpInit;
     CwmsQmlStyle* m_pStyle;
     CwmsqmlApplication* m_pApplication;
     CdmQueryModel* pModel;

private:
	// Singleton
    CwmsQmlApplicationController(QString p_qstrApplication, CwmsInitApplication* p_pInit, QObject* p_pParent = NULL);

public:
	virtual ~CwmsQmlApplicationController();
    static CwmsQmlApplicationController* createController(QString p_qstrApplication, CwmsInitApplication* p_pInit, QObject* p_pParent = NULL);
    static CwmsQmlApplicationController* getController();
    void setDevelopmentMode(bool bDevelopmentMode);
    void showWindow(bool p_bModal, QQuickWindow* p_pWindow);
    void openWindow();
    void createCustomMainWindow(QString p_qstrName, QString p_qstrQml);
    void initApplication();
    

    CsaObject *convertObject(CdmObject *p_pObject);
    CsaObjectContainer *convertContainer(CdmObjectContainer *p_pContainer);
public slots:
    void goBack();
    QQuickWindow* getCentralWindow();
    QString loadCustomMainWindow();
    QStringList getDatabaseList();
    QStringList getApplicationList();
    void setCurrentContent(QQuickItem* p_pItem);
    QQuickItem* getCurrentContent();
    void loginSuccessfull();
    void selectionSuccessfull();
    QStringList getSelectionList();
    void loadSelection(QString p_qstrSelection);
    bool needsApplicationSelection();
    bool needsDatabaseSelection();
    bool needsSelection();
    bool hasCustomMainWindow();
    QString getDefaultMainWindowName();
    bool isMobile();
    QString getClientConfigurationQmlDialog(QString p_qstrConfig);
    QStringList getModuleList();
    CwmsqmlApplication *getApplication();
    CsaObject *getDefaultModule();
    void quit();
    QString getContainerEditorName();
    CwmsQmlWidget *popViewFromStack();
    void pushViewToStack(qint64 p_lModuleId, QString p_qstrUiName, QString p_qstrElementUri);
    CsaFactory *getFactory();
};

#endif // CWMSQMLAPPLICATIONCONTROLLER_H
