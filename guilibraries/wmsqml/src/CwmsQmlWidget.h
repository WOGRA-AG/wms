#ifndef CWMSQMLWIDGET_H
#define CWMSQMLWIDGET_H

// system and Qt Includes
#include <QObject>

// own Includes


// Forwards
class CdmLocatedElement;
class CdmObject;
class CdmObjectContainer;


class CwmsQmlWidget : public QObject
{
    Q_OBJECT
private:
    CdmLocatedElement* m_rpElement;
    bool m_bMainWindow;
    QString m_qstrUiName;
    long m_lModuleId;


public:
    CwmsQmlWidget();
    ~CwmsQmlWidget();

    static void registerToQml();
public slots:
    CdmLocatedElement* getLocatedElement() const;
    void setLocatedElement(CdmLocatedElement* p_pElement);
    bool isMainWindow() const;
    void setMainWindow(bool bMainWindow);
    QString getUiName() const;
    void setUiName(const QString &value);
    long getModuleId() const;
    void setModuleId(const long &value);
    bool isContainerEditor() const;
    bool isObjectEditor() const;
};

#endif // CWMSQMLWIDGET_H
