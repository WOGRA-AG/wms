/******************************************************************************
 ** WOGRA Middleware Server Communication Module
 **
 ** @Author Wolfgang Graßhof 
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies All rights reserved
 ******************************************************************************/

// Qt
#include <QDesktopServices>
#include <QDir>
#include <QDomElement>
#include <QFileInfo>
#include <QString>
#include <QThread>
#include <QUrl>
#include <QVariant>

// own Includes
#include "wmsdefines.h"
#include "CdmSettings.h"
#include "CdmObject.h"
#include "CdmObjectContainer.h"
#include "CdmDataProvider.h"
#include "CdmSessionManager.h"
#include "CdmLogging.h"
#include "CdmClassManager.h"
#include "CdmMember.h"
#include "CdmValueBinaryDocument.h"

CdmValueBinaryDocument::CdmValueBinaryDocument(qint64 p_lDatabaseId,
                                    qint64 p_lId,
                                     QString p_qstrKeyname,
                                     QString p_qstrFilename,
                                     QString p_qstrType,
                                     CdmObject* p_pCdmObject)
: CdmValue( p_lDatabaseId, p_lId, p_qstrKeyname, eDmValueBinaryDocument, p_pCdmObject),
  m_qstrFilename(p_qstrFilename),
  m_qstrType(p_qstrType)
{
   // nothing to do here :-)
}

CdmValueBinaryDocument::CdmValueBinaryDocument(QVariantMap& p_qVariant, CdmObject* p_pCdmObject)
: CdmValue(p_qVariant, p_pCdmObject)
{
   SetVariant(p_qVariant);
}

CdmValueBinaryDocument::~CdmValueBinaryDocument(  )
{
}

void CdmValueBinaryDocument::Deploy(QVariantMap& p_rqvHash)
{
   CdmValue::Deploy(p_rqvHash);
   SetVariant(p_rqvHash);
}

void CdmValueBinaryDocument::SetValue(QString p_qstrFilename, QString p_qstrType)
{
  QFileInfo qfInfo(p_qstrFilename);

  if (qfInfo.exists())
  {
     m_qstrFilename = qfInfo.fileName();
     m_qstrCurrentDirectory = qfInfo.absoluteDir().absolutePath();
     m_qstrType = p_qstrType;
  }
  else
  {
     m_qstrFilename = "";
     m_qstrType = "";
  }

  ValueChanged();
}

void CdmValueBinaryDocument::SetFilenameAndTypeWithoutModifyingValue(QString& p_qstrFilename, QString& p_qstrType)
{
    m_qstrFilename = p_qstrFilename;
    m_qstrType = p_qstrType;
}


void CdmValueBinaryDocument::GetValue(QString& p_qstrFilename, QString& p_qstrType) const
{
   p_qstrFilename = m_qstrFilename;
   p_qstrType = m_qstrType;
}

QString CdmValueBinaryDocument::GetFilename() const
{
   QString qstrFilename = m_qstrFilename;
   qstrFilename.remove("'");
   return qstrFilename;
}

QString CdmValueBinaryDocument::GetFileType() const
{
   QString qstrRet = m_qstrType;

   if (qstrRet.isEmpty())
   {
      QString qstrFilename = GetFilename();

      if (!qstrFilename.isEmpty())
      {
         QFileInfo qfInfo(qstrFilename);
         qstrRet = qfInfo.suffix();
      }
   }


   return qstrRet.remove("'");
}

void CdmValueBinaryDocument::ExecuteFile()
{
   QString qstrCommand = StoreToLocalFileSystem();
   QUrl url;

   if (qstrCommand.startsWith("\\\\") || qstrCommand.startsWith("//"))
   {
        url.setUrl(QDir::toNativeSeparators(qstrCommand));
   }
   else
   {
        url = QUrl::fromLocalFile(qstrCommand);
   }

   QDesktopServices::openUrl(url);
}

void CdmValueBinaryDocument::SaveFileTo(QString p_qstrPath)
{
   QString qstrCommand = StoreToLocalFileSystem();
   QFileInfo qfiCommand(qstrCommand);

   if (qstrCommand != p_qstrPath && qfiCommand.exists())
   {
     QFile qfExist(p_qstrPath);

     if (qfExist.exists())
     {
        qfExist.remove();
     }

      QFile qfFile(qstrCommand);

      if (!qfFile.copy(p_qstrPath))
      {
         ERR("Could not Copy File to " + p_qstrPath + ".");
      }

   }
   else
   {
      INFO("Target and source are equal. No copy process started!")
   }
}

QString CdmValueBinaryDocument::StoreToLocalFileSystem()
{
    QString qstrFilename;

    if (!IsModified()) // if it is modified you can not load it from db, because then you find the old document
    {
       QByteArray qByteArray = GetByteArray();

       if(m_qstrCurrentDirectory.isEmpty())
       {
          GetBinaryDocumentDirectory();
       }

       if (!m_qstrFilename.isEmpty())
       {
            qstrFilename = m_qstrFilename.remove("'");
       }
       else
       {
           qstrFilename = "/tempFile";
       }

       WriteByteArrayToFile(qByteArray, qstrFilename);
    }

    QString qstrCommand;

    if (!qstrFilename.isEmpty())
    {
      qstrCommand = m_qstrCurrentDirectory + "/" + qstrFilename;
    }
    else
    {
        WARNING("Unknown filename of Bindoc");
        qstrCommand = m_qstrCurrentDirectory + "/tempFile";
    }
   
    return qstrCommand;
}

void CdmValueBinaryDocument::SetBase64(QString p_qstrFilename, QString p_qstrFiletype, QString& p_qcstrBase64)
{
    if (p_qcstrBase64.length() > 0)
    {
        m_qstrFilename = p_qstrFilename;
        m_qstrType = p_qstrFiletype;
        QByteArray qByteArray(QByteArray::fromBase64(p_qcstrBase64.toLocal8Bit()));
        WriteByteArrayToFile(qByteArray);
        ValueChanged();
    }
}

QString CdmValueBinaryDocument::GetBase64() const
{
   return GetByteArray().toBase64();
}

void CdmValueBinaryDocument::WriteByteArrayToFile(QByteArray& p_qByteArray)
{
      m_qstrFilename = m_qstrFilename.remove("'");
      size_t iThreadId = (size_t)QThread::currentThread();
      m_qstrTempFilename =  QString::number(iThreadId) + m_qstrFilename;
      WriteByteArrayToFile(p_qByteArray, m_qstrTempFilename);
}

void CdmValueBinaryDocument::WriteByteArrayToFile(QByteArray& p_qByteArray, QString p_qstrFilename)
{
      GetBinaryDocumentDirectory();
      m_qstrTempFilename = m_qstrCurrentDirectory + "/" + p_qstrFilename;
      QFile qfFile(m_qstrTempFilename);

      if(qfFile.open(QIODevice::WriteOnly))
      {
        qint64 lLength = qfFile.write(p_qByteArray);

         if(lLength <= 0)
         {
            ERR("File couldn't be written perhaps the file is empty!!!");
        }
    }
    else
    {
        ERR("opening file in write mode not possible!!!");
    }
}

QString CdmValueBinaryDocument::GetCurrentDirectory()
{
    if(m_qstrCurrentDirectory.isEmpty())
    {
        GetBinaryDocumentDirectory();
    }

    return m_qstrCurrentDirectory;
}

QByteArray CdmValueBinaryDocument::GetByteArray() const
{
    if (IsNew() || IsModified()) // never saved before you will find the content on filesystem
    {
        if (!m_qstrFilename.isEmpty())
        {
            return GetByteArrayByMembers();
        }
        else
        {
            WARNING("NO file is here!");
        }
    }
    else if (!IsDeleted()) // already stored in db load it from db
    {
        IdmDataAccess* pIdmDataAccess = GetDataAccess();

        if(CHKPTR(pIdmDataAccess))
        {
           QByteArray qByteArray = pIdmDataAccess->ReadBinaryDocument(GetSchemeId(), const_cast<CdmValueBinaryDocument*>(this));
           return qByteArray;
        }
    }
    else
    {
        WARNING("Deleted value, no bindoc there");
    }

    return QByteArray();
}

QByteArray CdmValueBinaryDocument::GetByteArrayByMembers() const
{
    QString qstrFilePath;
    QByteArray qByteArray;

    if (m_qstrTempFilename.isEmpty())
    {
        qstrFilePath = m_qstrCurrentDirectory + "/" + m_qstrFilename;
    }
    else
    {
        qstrFilePath = m_qstrTempFilename;
    }

    QFile qfFile(qstrFilePath);

    if(qfFile.open(QIODevice::ReadOnly))
    {
        qByteArray = qfFile.readAll();
        qfFile.close();
    }
    else
    {
        ERR("Could not open file. File not found or file is read locked.");
    }

    return qByteArray;
}

void CdmValueBinaryDocument::GetBinaryDocumentDirectory()
{
   CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

   if(CHKPTR(pCdmManager))
   {
      CdmSettings* pCdmSettings = pCdmManager->GetSettings();
      if(CHKPTR(pCdmSettings))
      {
         m_qstrCurrentDirectory = pCdmSettings->GetTemporaryBinaryDirectory();

         QDir qDir(m_qstrCurrentDirectory);

         if (!qDir.exists())
         {
             m_qstrCurrentDirectory = QDir::tempPath();
         }

      }
   }
}

QString CdmValueBinaryDocument::GetDisplayString() const
{
   return m_qstrFilename;
}

void CdmValueBinaryDocument::SetDefaultValue(const CdmMember*)
{

   // there are no default values for this Value it must be ignored
}


QVariant CdmValueBinaryDocument::GetVariant() const
{
   QVariantMap qmVariant = CdmValue::GetVariant().toMap();

   qmVariant.insert(WMS_VALUE, GetBase64());
   qmVariant.insert(WMS_FILENAME, m_qstrFilename);
   qmVariant.insert(WMS_FILETYPE, m_qstrType);
   return qmVariant;
}

void CdmValueBinaryDocument::SetVariant(QVariantMap& p_rqvHash)
{
    m_qstrType = p_rqvHash[WMS_FILETYPE].toString();
    m_qstrFilename = p_rqvHash[WMS_FILENAME].toString();
    QString qstrBase64 = p_rqvHash[WMS_VALUE].toString();

    if (!qstrBase64.isEmpty())
    {
        QByteArray qByteArray = QByteArray::fromBase64(qstrBase64.toLocal8Bit());
        WriteByteArrayToFile(qByteArray);
    }

    ValueChanged();
}

QVariant CdmValueBinaryDocument::GetValueVariant() const
{
   QVariantMap pMap;
   pMap.insert("Filename", GetFilename());
   pMap.insert("Filetype", GetFileType());
   //The value is not returned
   pMap.insert("Value", "-1");
   return pMap;
}

QString CdmValueBinaryDocument::GetValueAsString() const
{
   return m_qstrFilename;
}

void CdmValueBinaryDocument::SetValueVariant(QVariant& p_qvVariant)
{
    QVariantMap map = p_qvVariant.toMap();

    QString content = map["Content"].toString();

    if (!content.isEmpty())
    {
        SetBase64(map["Filename"].toString(), map["Filetype"].toString(), content);
    }
    else
    {
        m_qstrFilename = map["Filename"].toString();
        m_qstrType = map["Filetype"].toString();
    }
}
