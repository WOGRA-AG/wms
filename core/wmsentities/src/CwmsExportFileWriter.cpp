/******************************************************************************
 ** WOGRA Middleware Tools Exportsettings Module
 **
 ** @Author Wolfgang Graßhof 
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies All rights reserved
 ******************************************************************************/


// System and QT Includes
#include <QDomDocument>
#include <QApplication>
#include <QTextStream>
#include <QLinkedList>
#include <QFileInfo>

// WMS Includes
#include "CdmClass.h"
#include "CdmMember.h"
#include "CdmQuery.h"
#include "CdmValueBinaryDocument.h"
#include "CdmDataProvider.h"
#include "CdmSessionManager.h"
#include "CdmValue.h"
#include "CdmObject.h"
#include "CdmObjectContainer.h"
#include "CdmContainerManager.h"
#include "CdmObject.h"
#include "CdmLogging.h"
#include "CdmMessageManager.h"

// own Includes
#include "CwmsExportFileWriter.h"
#include "CwmsExportSettings.h"

/** +-=---------------------------------------------------------Sa 17. Nov 13:34:07 2007----------*
 * @method  CwmsExportWriter::CwmsExportWriter       // public                            *
 * @return                                                   //                                   *
 * @param   CwmsExportSettings p_cCwmsExportSettings         //                                   *
 * @comment                                                                                       *
 *----------------last changed: Wolfgang Graßhof----------------Sa 17. Nov 13:34:07 2007----------*/
CwmsExportWriter::CwmsExportWriter(CwmsExportSettings p_cCwmsExportSettings)
: m_pqDevice(nullptr)
{
   m_rCwmsSettings = p_cCwmsExportSettings;
}

/** +-=---------------------------------------------------------Do 15. Nov 23:13:05 2007----------*
 * @method  CwmsExportWriter::~CwmsExportWriter      // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CwmsExportWriter                                          *
 *----------------last changed: Wolfgang Graßhof----------------Do 15. Nov 23:13:05 2007----------*/
CwmsExportWriter::~CwmsExportWriter()
{
   // nothing to do here :-)
}

/** +-=---------------------------------------------------------So 18. Nov 11:34:32 2007----------*
 * @method  CwmsExportWriter::Export                     // public                            *
 * @return  bool                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: Wolfgang Graßhof----------------So 18. Nov 11:34:32 2007----------*/
bool CwmsExportWriter::Export()
{
   bool bRet = false;
   QTextStream qtsStream;

   INFO("Open File");
   if (OpenDevice(qtsStream))
   {
      INFO("Load ObjectList");

      CdmObjectContainer* pContainer = GetObjectList();
      if (CHKPTR(pContainer))
      {
         QLinkedList<long> qvlObjects;
         INFO("Execute Query");
         bool bQueryResult = GetQueryObjects(qvlObjects, pContainer);

         if (!bQueryResult ||
             (bQueryResult && qvlObjects.count() >0))
         {
            INFO("Start Export");
            switch(m_rCwmsSettings.GetExportType())
            {
            case eWmsExportTypeCsv:
               INFO("Exporting CSV Data");
               ExportCsv(qtsStream, pContainer, qvlObjects);
               break;
            case eWmsExportTypeHtml:
               INFO("Exporting HTML Data");
               ExportHtml(qtsStream, pContainer, qvlObjects);
               break;
            case eWmsExportTypeXml:
               INFO("Exporting XML Data");
               ExportXml(qtsStream, pContainer, qvlObjects);
               break;
            }
         }
         else
         {
            ERR("No valid results from Query");
         }

         INFO("Closing file");
         CloseDevice();
         INFO("Export finished");
      }
   }

   return bRet;
}

/** +-=---------------------------------------------------------So 18. Nov 11:15:47 2007----------*
 * @method  CwmsExportWriter::GetObjectList              // private                           *
 * @return  CdmObjectContainer*                                   //                                   *
 * @comment finds the objectlist dependent from the settings.                                     *
 *----------------last changed: Wolfgang Graßhof----------------So 18. Nov 11:15:47 2007----------*/
CdmObjectContainer* CwmsExportWriter::GetObjectList()
{
   CdmObjectContainer* pContainer = nullptr;

   CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();

   if (CHKPTR(pCdmManager))
   {
      CdmContainerManager* pContainerManager = nullptr;

      if (m_rCwmsSettings.GetSchemeId())
      {
         pContainerManager = pCdmManager->GetContainerManager(m_rCwmsSettings.GetSchemeId());
      }
      else if (!m_rCwmsSettings.GetSchemeName().isEmpty())
      {
          QString qstrScheme = m_rCwmsSettings.GetSchemeName();
         pContainerManager = pCdmManager->GetContainerManager(qstrScheme);
      }

      if (CHKPTR(pContainerManager))
      {
         pContainer = pContainerManager->FindContainerById(m_rCwmsSettings.GetContainerId());
      }

      if (m_rCwmsSettings.GetQuery().isEmpty())
      {
          pContainerManager->ReloadContainerComplete(pContainer);
      }
    }

    return pContainer;
}

/** +-=---------------------------------------------------------So 18. Nov 11:15:39 2007----------*
 * @method  CwmsExportWriter::GetQueryObjects            // private                           *
 * @return  bool                                             // successflag                       *
 * @param   QLinkedList<long>& p_rqvlObjects                  //                                   *
 * @param   CdmObjectContainer* p_pContainer                  //                                   *
 * @comment This method returns the query objects which are the result of the query.              *
 *----------------last changed: Wolfgang Graßhof----------------So 18. Nov 11:15:39 2007----------*/
bool CwmsExportWriter::GetQueryObjects(QLinkedList<long>& p_rqvlObjects,
                                       CdmObjectContainer* p_pContainer)
{
   bool bRet = false;
    Q_UNUSED(p_pContainer);

    QString qstrQuery = m_rCwmsSettings.GetQuery();
    QLinkedList<long> qllExportList = m_rCwmsSettings.GetExportList();

    if (!qstrQuery.isEmpty())
    {
        INFO("Query found create it over xmlimport");
        CdmQuery* pCdmQuery = m_rCwmsSettings.GetQueryObject();

        if (CHKPTR(pCdmQuery) && SUCCESSFULL(pCdmQuery->Execute()))
        {
            bRet = true;

            const QLinkedList<long> qvlResult = pCdmQuery->GetResultList();

            QLinkedList<long>::const_iterator qvlIt = qvlResult.begin();
            QLinkedList<long>::const_iterator qvlItEnd = qvlResult.end();

            for(; qvlIt != qvlItEnd; ++ qvlIt)
            {
                long lValue = (*qvlIt);
                p_rqvlObjects.append(lValue);
            }

            INFO("Query executed successfully. Number of Results:" + QString::number(p_rqvlObjects.count()));
        }
        else
        {
            ERR("Query execution failed!");
        }
    }
    else if(qllExportList.count() > 0)
    {
        p_rqvlObjects = qllExportList;
        bRet = true;
    }
    else
    {
        INFO("No query used");
    }

    return bRet;
}

/** +-=---------------------------------------------------------Do 28. Feb 11:21:54 2013----------*
 * @method  CwmsExportWriter::SetDevice                  // public                            *
 * @return  void                                             //                                   *
 * @param   QIODevice* p_pDevice                             // change of ownership will be deleted*
 *                                                           //  after export is finished         *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 28. Feb 11:21:54 2013----------*/
void CwmsExportWriter::SetDevice(QIODevice* p_pDevice)
{
   m_pqDevice = p_pDevice;
}

/** +-=---------------------------------------------------------Mo 29. Okt 10:38:10 2012----------*
 * @method  CwmsExportWriter::OpenDevice                   // private                           *
 * @return  bool                                             //                                   *
 * @param   QTextStream& p_rqtStream                         //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 29. Okt 10:38:10 2012----------*/
bool CwmsExportWriter::OpenDevice(QTextStream& p_rqtStream)
{
   bool bRet = false;

   if (!m_pqDevice)
   {
       QString qstrFilename = m_rCwmsSettings.GetFilename();

       if (qstrFilename.isEmpty())
       {
           qstrFilename = CdmMessageManager::GetMessenger()->AskForSaveFile(QObject::tr("Bitte geben Sie die Datei an, in der die Daten exportiert werden sollen."));
       }

       if (!qstrFilename.isEmpty())
       {
          m_pqDevice = new QFile(qstrFilename);
       }
   }


   if (m_pqDevice && m_pqDevice->open(QIODevice::WriteOnly))
   {
       if (!m_rCwmsSettings.GetEncoding().isEmpty())
       {
           p_rqtStream.setCodec(m_rCwmsSettings.GetEncoding().toLocal8Bit());
       }


      p_rqtStream.setDevice(m_pqDevice);
      bRet = true;
   }
   else
   {
      ERR("Unable to open file for writting.");
   }

   return bRet;
}

/** +-=---------------------------------------------------------Sa 17. Nov 14:29:34 2007----------*
 * @method  CwmsExportWriter::CloseDevice                  // private                           *
 * @return  void                                             //                                   *
 * @comment This method closes the file.                                                          *
 *----------------last changed: Wolfgang Graßhof----------------Sa 17. Nov 14:29:34 2007----------*/
void CwmsExportWriter::CloseDevice()
{
   if (CHKPTR(m_pqDevice))
   {
      m_pqDevice->close();
      DELPTR(m_pqDevice);
   }
}

/** +-=---------------------------------------------------------Mo 29. Okt 10:37:11 2012----------*
 * @method  CwmsExportWriter::ExportCsv                  // private                           *
 * @return  bool                                             //                                   *
 * @param   QTextStream& p_rqtStream                         //                                   *
 * @param   CdmObjectContainer* p_pContainer                  //                                   *
 * @param   QLinkedList<long> p_rqvlObjects                   //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 29. Okt 10:37:11 2012----------*/
bool CwmsExportWriter::ExportCsv(QTextStream& p_rqtStream,
                                 CdmObjectContainer* p_pContainer,
                                 QLinkedList<long> p_rqvlObjects)
{
   bool bRet = false;

   if (CHKPTR(p_pContainer))
   {
      if (p_rqvlObjects.count() == 0)
      {
         CdmContainerManager* pContainerManager = p_pContainer->GetContainerManager();

         if (CHKPTR(pContainerManager))
         {
            long lObjectListId = p_pContainer->GetId();
            pContainerManager->RemoveContainerLocally(p_pContainer->GetId());
            p_pContainer = pContainerManager->FindContainerById(lObjectListId);
            if (CHKPTR(p_pContainer))
            {
                p_pContainer->GetObjectList(p_rqvlObjects);
            }
         }
      }

      if (m_rCwmsSettings.GetExportHeader())
      {
         INFO("Exporting Header");
         QString qstrHeader;
         qstrHeader = GetCsvHeader(p_pContainer);
         p_rqtStream << qstrHeader;
      }
       
      QLinkedList<QString> qvlMembers = m_rCwmsSettings.GetMemberList();

      QLinkedList<long>::iterator qvlIt = p_rqvlObjects.begin();
      QLinkedList<long>::iterator qvlItEnd = p_rqvlObjects.end();
      
      INFO("Exporting " + QString::number(p_rqvlObjects.count()) + " Objects:");
      int iCounter = 0;

      for (; qvlIt != qvlItEnd; ++qvlIt)
      {
         long lObjectId = (*qvlIt);
         ++iCounter;
         INFO("Exporting Object " + QString::number(iCounter));

         CdmObject* pCdmObject = p_pContainer->FindObjectById(lObjectId);

         if (CHKPTR(pCdmObject))
         {
            QString qstrLine;
            QLinkedList<QString>::iterator qvlMemberIt = qvlMembers.begin();
            QLinkedList<QString>::iterator qvlMemberItEnd = qvlMembers.end();
            bool bFirst = true;

            for (; qvlMemberIt != qvlMemberItEnd; ++qvlMemberIt)
            {
               if (bFirst == true)
               {
                  bFirst = false;
               }
               else
               {
                  qstrLine += m_rCwmsSettings.GetCsvSeperator();
               }

               QString qstrMember = (*qvlMemberIt); 
               
               CdmValue* pCdmValue = pCdmObject->GetValue(qstrMember);

               if (pCdmValue)
               {
                  if (pCdmValue->GetValueType() == eDmValueString ||
                      pCdmValue->GetValueType() == eDmValueCharacterDocument)
                  {
                     qstrLine += m_rCwmsSettings.GetCsvStringEnclosing();
                  }

                  if (pCdmValue->GetValueType() == eDmValueCharacterDocument)
                  {
                     QString qstrContent = pCdmValue->GetDisplayString();
                     qstrLine += qstrContent.replace("\n", " ");
                  }
                  else if (pCdmValue->GetValueType() == eDmValueBinaryDocument)
                  {
                     qstrLine += GetBinDocExport(pCdmValue);
                  }
                  else
                  {
                     QString qstrContent = pCdmValue->GetValueAsString();
                     qstrLine += qstrContent.replace("\n", " ");
                  }
                  

                  if (pCdmValue->GetValueType() == eDmValueString ||
                      pCdmValue->GetValueType() == eDmValueCharacterDocument)
                  {
                     qstrLine += m_rCwmsSettings.GetCsvStringEnclosing();
                  }
               }
               else
               {
                  qstrLine += "Unknown Member";
                  WARNING("Member " + qstrMember + " is Unknown.");
               }
            }

            qstrLine += "\n";
            p_rqtStream << qstrLine;
         }
      }
   
   }

   return bRet;
}

/** +-=---------------------------------------------------------Mi 19. Aug 19:55:39 2009----------*
 * @method  CwmsExportWriter::GetBinDocExportXml         // private                           *
 * @return  void                                             //                                   *
 * @param   QDomElement& p_rqdElement                        //                                   *
 * @param   CdmValue* p_pCdmValue                            //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 19. Aug 19:55:39 2009----------*/
void CwmsExportWriter::GetBinDocExportXml(QDomElement& p_rqdElement, CdmValue* p_pCdmValue)
{
   if (CHKPTR(p_pCdmValue))
   {
      QString qstrFile = GetBinDocExport(p_pCdmValue);
      p_rqdElement.setAttribute("Value", qstrFile);
   }
}

/** +-=---------------------------------------------------------Mi 19. Aug 19:26:00 2009----------*
 * @method  CwmsExportWriter::GetBinDocExport            // private                           *
 * @return  QString                                          //                                   *
 * @param   CdmValue* p_pCdmValue                            //                                   *
 * @param   bool p_bHtml = false                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 19. Aug 19:26:00 2009----------*/
QString CwmsExportWriter::GetBinDocExport(CdmValue* p_pCdmValue, bool p_bHtml)
{
   QString qstrRet;

   if (CHKPTR(p_pCdmValue) && 
       p_pCdmValue->GetValueType() == eDmValueBinaryDocument)
   {

      QFileInfo qfInfo(m_rCwmsSettings.GetFilename());
      QString qstrPath = qfInfo.absolutePath();
      CdmValueBinaryDocument* pCdmBinDoc = ((CdmValueBinaryDocument*)p_pCdmValue);
      QString qstrFilename = pCdmBinDoc->GetFilename() + "." + pCdmBinDoc->GetFileType();

      QString qstrFilepath = qstrPath + "/" + qstrFilename;

      if (p_bHtml)
      {
         qstrRet = "<a href=\"" + qstrFilepath +"\">";
         qstrRet += qstrFilename;
         qstrRet += "</a>";
      }
      else
      {
         qstrRet += qstrFilepath;
      }
      
      pCdmBinDoc->SaveFileTo(qstrFilepath);
   }

   return qstrRet;
}

/** +-=---------------------------------------------------------So 18. Nov 11:15:23 2007----------*
 * @method  CwmsExportWriter::GetCsvHeader               // private                           *
 * @return  QString                                          //                                   *
 * @param   CdmObjectContainer* p_pContainer                  //                                   *
 * @comment                                                                                       *
 *----------------last changed: Wolfgang Graßhof----------------So 18. Nov 11:15:23 2007----------*/
QString CwmsExportWriter::GetCsvHeader(CdmObjectContainer* p_pContainer)
{
   QString qstrHeader;
   QString qstrSeperator = GetCsvSeperator();

   if (CHKPTR(p_pContainer))
   {
      QLinkedList<QString> qvlMembers = m_rCwmsSettings.GetMemberList();
      const CdmClass* pCdmClass = p_pContainer->GetClass();

      if (CHKPTR(pCdmClass))
      {
         QLinkedList<QString>::iterator qvlIt = qvlMembers.begin();
         QLinkedList<QString>::iterator qvlItEnd = qvlMembers.end();
         bool bFirst = true;

         for (; qvlIt != qvlItEnd; ++qvlIt)
         {
            if (bFirst)
            {
               bFirst = false;
            }
            else
            {
               qstrHeader += ";";
            }

            QString qstrMember = (*qvlIt);
            const CdmMember* pCdmMember = pCdmClass->FindMember(qstrMember);

            if (CHKPTR(pCdmMember))
            {
               qstrHeader += pCdmMember->GetCaption();
            }
            else
            {
               qstrHeader += "Unknown Member";
               ERR("Member " + qstrMember + " is Unknown.");
            }
         }
      }
   }

   return qstrHeader + "\n";
}

/** +-=---------------------------------------------------------So 18. Nov 11:15:18 2007----------*
 * @method  CwmsExportWriter::GetCsvSeperator            // private                           *
 * @return  QString                                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: Wolfgang Graßhof----------------So 18. Nov 11:15:18 2007----------*/
QString CwmsExportWriter::GetCsvSeperator()
{
   QString qstrSeperator;

   qstrSeperator = m_rCwmsSettings.GetCsvSeperator();

   if (qstrSeperator.isEmpty())
   {
      qstrSeperator = ";";
   }

   return qstrSeperator;
}


/** +-=---------------------------------------------------------Mo 29. Okt 10:37:36 2012----------*
 * @method  CwmsExportWriter::ExportHtml                 // private                           *
 * @return  bool                                             //                                   *
 * @param   QTextStream& p_rqtStream                         //                                   *
 * @param   CdmObjectContainer* p_pContainer                  //                                   *
 * @param   QLinkedList<long> p_rqvlObjects                   //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 29. Okt 10:37:36 2012----------*/
bool CwmsExportWriter::ExportHtml(QTextStream& p_rqtStream,
                                      CdmObjectContainer* p_pContainer,
                                      QLinkedList<long> p_rqvlObjects)
{

   bool bRet = false;

   if (CHKPTR(p_pContainer))
   {
      if (p_rqvlObjects.count() == 0)
      {
         CdmContainerManager* pContainerManager = p_pContainer->GetContainerManager();

         if (CHKPTR(pContainerManager))
         {
            long lObjectListId = p_pContainer->GetId();
            pContainerManager->RemoveContainerLocally(p_pContainer->GetId());
            p_pContainer = pContainerManager->FindContainerById(lObjectListId);

            if (CHKPTR(p_pContainer))
            {
               p_pContainer->GetObjectList(p_rqvlObjects);
            }
         }
      }

      if (p_rqvlObjects.count() > 0)
      {
         QString qstrHeader = GetHtmlHeader(p_pContainer);
         p_rqtStream << qstrHeader;

         QLinkedList<QString> qvlMembers = m_rCwmsSettings.GetMemberList();

         QLinkedList<long>::iterator qvlIt = p_rqvlObjects.begin();
         QLinkedList<long>::iterator qvlItEnd = p_rqvlObjects.end();
         INFO("Exporting " + QString::number(p_rqvlObjects.count()) + " Objects:");
         int iCounter = 0;
         
         for (; qvlIt != qvlItEnd; ++qvlIt)
         {
            long lObjectId = (*qvlIt);
            ++iCounter;
            INFO("Exporting Object " + QString::number(iCounter));
            CdmObject* pCdmObject = p_pContainer->FindObjectById(lObjectId);

            if (CHKPTR(pCdmObject))
            {
               QString qstrLine = "<tr>";
               QLinkedList<QString>::iterator qvlMemberIt = qvlMembers.begin();
               QLinkedList<QString>::iterator qvlMemberItEnd = qvlMembers.end();
               
               for (; qvlMemberIt != qvlMemberItEnd; ++qvlMemberIt)
               {
                  qstrLine += "<td>";
                  QString qstrMember = (*qvlMemberIt);
                  
                  CdmValue* pCdmValue = pCdmObject->GetValue(qstrMember);

                  if (CHKPTR(pCdmValue))
                  {
                     if (pCdmValue->GetValueType() != eDmValueBinaryDocument)
                     {
                        qstrLine += pCdmValue->GetDisplayString();
                     }
                     else
                     {
                        qstrLine += GetBinDocExport(pCdmValue, true);
                     }
                  }
                  else
                  {
                     qstrLine += "Unknown Member";
                     ERR("Member " + qstrMember + " is Unknown.");
                  }

                  qstrLine += "</td>";
               }

               qstrLine += "</tr>\n";
               p_rqtStream << qstrLine;
            }
         }
      }

      QString qstrFooter = GetHtmlFooter();
      p_rqtStream << qstrFooter;
   }

   return bRet;
}

/** +-=---------------------------------------------------------So 18. Nov 11:15:12 2007----------*
 * @method  CwmsExportWriter::GetHtmlHeader              // private                           *
 * @return  QString                                          //                                   *
 * @param   CdmObjectContainer* p_pContainer                  //                                   *
 * @comment                                                                                       *
 *----------------last changed: Wolfgang Graßhof----------------So 18. Nov 11:15:12 2007----------*/
QString CwmsExportWriter::GetHtmlHeader(CdmObjectContainer* p_pContainer)
{
   QString qstrHeader;

   qstrHeader = "<html>\n";
   qstrHeader += "<head>\n";
   qstrHeader += "<title>" + p_pContainer->GetCaption() + "</title>";
   qstrHeader += "<meta http-equiv=\"Content-Type\" content=\"text/html; charset=iso-8859-1\">\n";
   qstrHeader += "</head>\n";
   qstrHeader += "<body>\n";

   qstrHeader += "<table width=\"100%\" border=\"0\">\n";
   qstrHeader += "<tr>";
   QString qstrSeperator = GetCsvSeperator();

   if (CHKPTR(p_pContainer))
   {
      QLinkedList<QString> qvlMembers = m_rCwmsSettings.GetMemberList();
      const CdmClass* pCdmClass = p_pContainer->GetClass();

      if (CHKPTR(pCdmClass))
      {
         QLinkedList<QString>::iterator qvlIt = qvlMembers.begin();
         QLinkedList<QString>::iterator qvlItEnd = qvlMembers.end();
         
         for (; qvlIt != qvlItEnd; ++qvlIt)
         {
            QString qstrMember = (*qvlIt);
            const CdmMember* pCdmMember = pCdmClass->FindMember(qstrMember);
            qstrHeader += "<td><div align=\"center\">";

            if (CHKPTR(pCdmMember))
            {
               qstrHeader += pCdmMember->GetCaption();
            }
            else
            {
               qstrHeader += "Unknown Member";
               ERR("Member " + qstrMember + " is Unknown.");
            }

            qstrHeader += "</div></td>";
         }
      }
   }

   qstrHeader += "</tr>";
   return qstrHeader;
}

/** +-=---------------------------------------------------------So 18. Nov 11:24:44 2007----------*
 * @method  CwmsExportWriter::GetHtmlFooter              // private                           *
 * @return  QString                                          //                                   *
 * @comment returns the Html footer.                                                              *
 *----------------last changed: Wolfgang Graßhof----------------So 18. Nov 11:24:44 2007----------*/
QString CwmsExportWriter::GetHtmlFooter()
{
   return "</table>\n</body>\n";
}


/** +-=---------------------------------------------------------Mo 29. Okt 10:37:44 2012----------*
 * @method  CwmsExportWriter::ExportXml                  // private                           *
 * @return  bool                                             //                                   *
 * @param   QTextStream& p_rqtStream                         //                                   *
 * @param   CdmObjectContainer* p_pContainer                  //                                   *
 * @param   QLinkedList<long> p_rqvlObjects                   //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 29. Okt 10:37:44 2012----------*/
bool CwmsExportWriter::ExportXml(QTextStream& p_rqtStream,
                                     CdmObjectContainer* p_pContainer,
                                     QLinkedList<long> p_rqvlObjects)
{
   bool bRet = false;

   if (CHKPTR(p_pContainer))
   {
      if (p_rqvlObjects.count() == 0)
      {
         CdmContainerManager* pContainerManager = p_pContainer->GetContainerManager();

         if (CHKPTR(pContainerManager))
         {
            long lObjectListId = p_pContainer->GetId();
            pContainerManager->RemoveContainerLocally(p_pContainer->GetId());
            p_pContainer = pContainerManager->FindContainerById(lObjectListId);
            if (CHKPTR(p_pContainer))
            {
               p_pContainer->GetObjectList(p_rqvlObjects);
            }
         }
      }

      QLinkedList<QString> qvlMembers = m_rCwmsSettings.GetMemberList();
      QLinkedList<long>::iterator qvlIt = p_rqvlObjects.begin();
      QLinkedList<long>::iterator qvlItEnd = p_rqvlObjects.end();
      INFO("Exporting " + QString::number(p_rqvlObjects.count()) + " Objects:");
      int iCounter = 0;
      QDomDocument qddDocument;
      QDomElement qdeRoot = qddDocument.createElement("ObjectList");
      qddDocument.appendChild(qdeRoot);
      qdeRoot.setAttribute("ClassId", QString::number(p_pContainer->GetClassId()));
      qdeRoot.setAttribute("Comment", p_pContainer->GetComment());
      QDomElement qdeTag = qddDocument.createElement("Objects");
      qdeRoot.appendChild(qdeTag);

      for (; qvlIt != qvlItEnd; ++qvlIt)
      {
         long lObjectId = (*qvlIt);
         ++iCounter;
         INFO("Exporting Object " + QString::number(iCounter));
         CdmObject* pCdmObject = p_pContainer->FindObjectById(lObjectId);

         if (CHKPTR(pCdmObject))
         {
            QDomElement qdeObject = qddDocument.createElement("Object");
            qdeTag.appendChild(qdeObject);

            QLinkedList<QString>::iterator qvlMemberIt = qvlMembers.begin();
            QLinkedList<QString>::iterator qvlMemberItEnd = qvlMembers.end();
            
            for (; qvlMemberIt != qvlMemberItEnd; ++qvlMemberIt)
            {
               QString qstrMember = (*qvlMemberIt);
               CdmValue* pCdmValue = pCdmObject->GetValue(qstrMember);

               if (CHKPTR(pCdmValue))
               {
                  QDomElement qdeValueTag = qddDocument.createElement("Value");
                  qdeObject.appendChild(qdeValueTag);

                  if (pCdmValue->GetValueType() != eDmValueBinaryDocument)
                  {
                     pCdmValue->XmlExport(qdeValueTag);
                  }
                  else
                  {
                     GetBinDocExportXml(qdeValueTag, pCdmValue);
                  }
               }
            }
         }       
      }

      p_rqtStream << qddDocument.toString();
   }

   return bRet;
}
