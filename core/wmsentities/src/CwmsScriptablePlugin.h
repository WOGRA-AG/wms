#ifndef CWMSSCRIPTABLEPLUGIN_H
#define CWMSSCRIPTABLEPLUGIN_H

// System abd Qt Includes
#include <QObject>

// own Includes
#include "CwmsScriptableBase.h"
#include "basetools.h"

class BASETOOLS_API CwmsScriptablePlugin: public CwmsScriptableBase
{
    Q_OBJECT
public:
    CwmsScriptablePlugin();
    virtual ~CwmsScriptablePlugin();


public slots:
    QObject* getPlugin(QString p_qstrName);
};

#endif // CWMSSCRIPTABLEPLUGIN_H
