#ifndef CWMSQMLCONTAINEREDITOR_H
#define CWMSQMLCONTAINEREDITOR_H

// System and QT Includes
#include <QObject>

// WMS Includes
#include "CdmContainerAdaptor.h"

// own Includes


// forwards
class CsaObjectContainer;
class QAbstractItemModel;

class CwmsQmlContainerEditor : public QObject, public CdmContainerAdaptor
{
    Q_OBJECT
private:
    QAbstractItemModel* m_pModel;


private:
    void createModelFromContainer();

public:
    CwmsQmlContainerEditor(CsaObjectContainer* p_pContainer);
    CwmsQmlContainerEditor();
    virtual ~CwmsQmlContainerEditor();
    static void registerToQml();

public slots:
    void setQuery(QString p_qstrQuery);
    QAbstractItemModel* getModel();
    QString getColumnCode(int p_iColumn);
    int getColumnCount();
    void setModel(QAbstractItemModel* p_pModel);
    void setContainer(CsaObjectContainer *p_pContainer);
    CsaObjectContainer *getContainer();
    bool hasPrinting();
};

#endif // CWMSQMLCONTAINEREDITOR_H
