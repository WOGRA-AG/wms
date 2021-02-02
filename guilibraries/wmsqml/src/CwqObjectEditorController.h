#ifndef CWQOBJECTEDITORCONTROLLER_H
#define CWQOBJECTEDITORCONTROLLER_H

// System and QT Includes
#include <QObject>

// WMS Manager Includes
#include "CdmObjectAdaptor.h"

// Own Includes
#include "wmsqml_global.h"


// Forwards
class CdmClassGroup;
class CdmObject;
class CsaObject;
class CsaValue;
class CdmValue;

class WMSQML_EXPORT CwqObjectEditorController : public QObject
{
    Q_OBJECT

    private:
    CdmObjectAdaptor m_Adaptor;
    bool m_bNew;


private:
    CdmClassGroup *getGroupByName(QString p_qstrName);

public:
    CwqObjectEditorController(QObject *parent = NULL);
    CwqObjectEditorController(CdmObject* p_pObject, QObject* parent = NULL);
    virtual ~CwqObjectEditorController();
    static void registerToQml();

public slots:

    QStringList getGroups();
    void setObject(CsaObject *p_pObject, bool p_bNew);
    CsaObject* getObjectW();
    int getGroupCount();
    QList<QObject*> getValuesOfGroup(QString p_qstrGroupName, bool p_bComplex = false);
    QList<QObject*> getValues(bool p_bComplex = false);
    QString getQmlElementByValue(CsaValue *p_pValue);
    bool isComplexUiType(CsaValue *p_pValue);
    int countComplexTypesOfGroup(QString p_qstrGroupName);
    int countComplexTypesOfObject();
    void okClicked();
    void cancelClicked();
    int countPagesOfGroup(QString p_qstrGroupName);
    bool needsMultiPageView(QString p_qstrGroupName);
    QObject *getComplexValueAt(QString p_qstrGroupName, int p_iPageNumber);
    bool isComplexUiType(EdmValueType p_eType);
    bool hasSimpleTypes(QString p_qstrGroupName);
};

#endif // CWQOBJECTEDITORCONTROLLER_H
