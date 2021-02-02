// System and Qt Includes
#include <QFile>
#include <QDir>
#include <QTextStream>

// WMS Includes
#include "CdmLogging.h"

#include "CwmsScriptableFile.h"

CwmsScriptableFile::CwmsScriptableFile()
{
    // nothing to do
}

CwmsScriptableFile::~CwmsScriptableFile()
{
    // nothing to do
}

QString CwmsScriptableFile::loadFile(QString p_qstrFile)
{
    QString qstrResult;
    QFile qFile(p_qstrFile);

    if (qFile.open(QIODevice::ReadOnly))
    {
        QTextStream stream(&qFile);
        qstrResult = stream.readAll();
    }
    else
    {
        ERR("Could not open file " + p_qstrFile);
    }

    return qstrResult;
}

bool CwmsScriptableFile::saveFile(QString p_qstrFile, QByteArray p_qbaContent)
{
    bool bSuccess = false;
    QFile qFile(p_qstrFile);

    if (qFile.open(QIODevice::WriteOnly))
    {
        QTextStream stream(&qFile);
        stream << p_qbaContent;
        bSuccess = true;
    }
    else
    {
        ERR("Could not open file " + p_qstrFile + " for saving.");
    }

    return bSuccess;
}

bool CwmsScriptableFile::deleteFile(QString p_qstrFile)
{
    return QFile::remove(p_qstrFile);
}

bool CwmsScriptableFile::existFile(QString p_qstrFile)
{
    return QFile::exists(p_qstrFile);
}

bool CwmsScriptableFile::createDirectory(QString p_qstrFile)
{
    QDir dir;
    return dir.mkpath(p_qstrFile);
}

bool CwmsScriptableFile::existDirectory(QString p_qstrFile)
{
    QDir dir(p_qstrFile);
    return dir.exists();
}

bool CwmsScriptableFile::deleteDirectory(QString p_qstrFile)
{
    QDir dir(p_qstrFile);
    return dir.removeRecursively();
}

bool CwmsScriptableFile::renameFile(QString qstrOldName, QString p_qstrNewName)
{
    return QFile::rename(qstrOldName, p_qstrNewName);
}

bool CwmsScriptableFile::copyFile(QString qstrSource, QString p_qstrTarget)
{
    return QFile::copy(qstrSource, p_qstrTarget);
}

QString CwmsScriptableFile::getCurrentPath()
{
    return QDir::currentPath();
}

QString CwmsScriptableFile::getHomePath()
{
    return QDir::homePath();
}

QString CwmsScriptableFile::getTempPath()
{
    return QDir::tempPath();
}

QString CwmsScriptableFile::getRootPath()
{
    return QDir::rootPath();
}



