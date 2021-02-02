#ifndef CWMSQMLENGINEINITIALIZER_H
#define CWMSQMLENGINEINITIALIZER_H

// System and Qt Includes
#include <QObject>
#include <QUrl>

// forwards
class QQmlApplicationEngine;
class QQmlContext;
class QQuickItem;
class CsaFactory;
class QQuickWindow;
class CdmObjectContainer;
class CdmObject;
class CsaObjectContainer;
class CsaObject;
class CdmModelElement;

class CwmsQmlEngineInitializer : public QObject
{
    Q_OBJECT

private:
    void fillTypes();
    void fillDefaultProperties();
    QQmlContext *getRootContext();

protected:
    QQmlApplicationEngine* m_pEngine;
    CsaFactory* m_pFactory;
    QQuickWindow* m_pCentralWindow;

    int prepareEngine();
    void showCreatedWindow(QObject *pFirstTopLevelObject);
    void addElements(CdmModelElement *p_pElement);
public:
    CwmsQmlEngineInitializer(QObject* parent = NULL);
    virtual ~CwmsQmlEngineInitializer();
    void addContextPropertyToEngine(QString p_qstrName, QObject *p_pObject);
    void addContextPropertyToEngine(QString p_qstrName, QVariant p_qvValue);
    void showWindow(bool p_bModal, QQuickWindow *p_pWindow);
    void showWindowNotModal(QQuickWindow *p_pWindow);
    void showWindowModal(QQuickWindow *p_pWindow);
public slots:
	QString loadWmsLibrary(QString p_qstrName, QString p_qstrVersion); 
	QObject* initWmsLibrary(QString p_qstrName, QString p_qstrVersion);
    QString loadUi(QUrl p_Url);
	QObject* openUi(QUrl p_Url);
    QString loadUi(QString p_qstrName);
	QObject* openUi(QString p_qstrName);
    QString loadUi(CdmObjectContainer *p_pElement);
	QObject* openUi(CdmObjectContainer *p_pElement);
    QString loadUi(CdmObject *p_pElement);
	QObject* openUi(CdmObject *p_pElement);
    QString loadUi(CsaObjectContainer *p_pContainer);
	QObject* openUi(CsaObjectContainer *p_pElement);
    QString loadUi(CsaObject *p_pObject);
	QObject* openUi(CsaObject *p_pElement);
    void showWindowUi(QUrl p_qFilename);
};

#endif // CWMSQMLENGINEINITIALIZER_H
