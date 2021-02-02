#ifndef CWMSSCRIPTABLEFILE_H
#define CWMSSCRIPTABLEFILE_H

// own Includes
#include "basetools.h"
#include "CwmsScriptableBase.h"

class BASETOOLS_API CwmsScriptableFile : public CwmsScriptableBase
{
    Q_OBJECT

public:
    CwmsScriptableFile();
    virtual ~CwmsScriptableFile();
public slots:
    QString loadFile(QString p_qstrFile);
    bool saveFile(QString p_qstrFile, QByteArray p_qbaContent);
    bool deleteFile(QString p_qstrFile);
    bool existFile(QString p_qstrFile);
    bool createDirectory(QString p_qstrFile);
    bool existDirectory(QString p_qstrFile);
    bool deleteDirectory(QString p_qstrFile);
    bool renameFile(QString qstrOldName, QString p_qstrNewName);
    bool copyFile(QString qstrSource, QString p_qstrTarget);
    QString getCurrentPath();
    QString getHomePath();
    QString getTempPath();
    QString getRootPath();
};

#endif // CWMSSCRIPTABLEFILE_H
