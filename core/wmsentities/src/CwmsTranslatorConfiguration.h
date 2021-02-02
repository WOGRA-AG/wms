#ifndef CWMSTRANSLATORCONFIGURATION_H
#define CWMSTRANSLATORCONFIGURATION_H

// System and QT Includes
#include <QLocale>
#include <QTranslator>
#include <QString>
#include <QCoreApplication>

// own Includes
#include "basetools.h"

class BASETOOLS_API CwmsTranslatorConfiguration
{
public:
    CwmsTranslatorConfiguration(QString p_qstrProjectName);

private:
    QString m_qstrLanguage;
    QString m_qstrProjectName;

public:
    void InstallTranslation();
    void InstallAllTranslationFiles();

    QString GetLanguage();
    void SetLanguage(const QString &value);
};

#endif // // CWMSTRANSLATOR_H
