
// System and QT Includes
#include <QCoreApplication>
#include <QDir>

// own Includes
#include "CdmLogging.h"
#include "CwmsTranslatorConfiguration.h"

CwmsTranslatorConfiguration::CwmsTranslatorConfiguration(QString p_qstrProjectName)
    : m_qstrProjectName(p_qstrProjectName)
{
}

void CwmsTranslatorConfiguration::InstallTranslation()
{
    QString qstrName = m_qstrProjectName;
    QString qstrLanguage = GetLanguage();

      qstrName += "_" + qstrLanguage;
      // NO MEM LEAK!!! (we can take it from app and delete the pointer)
      QTranslator* pTranslator = new QTranslator();
      pTranslator->load(qstrName);

      if (!pTranslator->isEmpty())
      {
         qApp->installTranslator(pTranslator);
         INFO("Translator for Project " + m_qstrProjectName + "installed.");
      }
      else
      {
         ERR("Translator for Project " + m_qstrProjectName + " is empty.");
      }
}

void CwmsTranslatorConfiguration::InstallAllTranslationFiles()
{
    QString qstrLanguage = GetLanguage();
    QString qstrPath = QCoreApplication::applicationDirPath() + "/translations/";
    QDir appDir(qstrPath);
    QStringList qstrlFilters;
    qstrlFilters.append("*" + qstrLanguage + ".qm");
    appDir.setNameFilters(qstrlFilters);

    if (appDir.count() == 0) // if nothing found use english
    {
       qstrlFilters.clear();
       qstrlFilters.append("*en.qm");
       appDir.setNameFilters(qstrlFilters);
    }

    for (uint iCounter = 0; iCounter < appDir.count(); ++iCounter)
    {
        QString qstrTranslationFile = appDir[iCounter];

        QTranslator* pTranslator = new QTranslator();
        pTranslator->load(qstrTranslationFile);

        if (!pTranslator->isEmpty())
        {
            qApp->installTranslator(pTranslator);
        }
    }
}



QString CwmsTranslatorConfiguration::GetLanguage()
{
    if (m_qstrLanguage == "")
    {
        // read from os;
        QLocale locale = QLocale::system();
        m_qstrLanguage = locale.name();
        m_qstrLanguage = m_qstrLanguage.left(2);
    }

    return m_qstrLanguage;
}

void CwmsTranslatorConfiguration::SetLanguage(const QString &value)
{
    m_qstrLanguage = value;
}
