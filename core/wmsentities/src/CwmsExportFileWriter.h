/******************************************************************************
 ** WOGRA Middleware Tools Exportsettings Module
 **
 ** @Author Wolfgang Graßhof 
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies All rights reserved
 ******************************************************************************/



#ifndef CWMSEXPORTFILEWRITER_H
#define CWMSEXPORTFILEWRITER_H

// System and QT Includes
#include <QTextStream>
#include <QFile>
#include <QLinkedList>

// own Includes
#include "basetools.h"
#include "CwmsExportSettings.h"

// forwards
class CdmValue;
class CdmObjectContainer;
class QDomElement;

class BASETOOLS_API CwmsExportWriter
{
   private:
      /*
       * The settings which must be written
       */
      CwmsExportSettings m_rCwmsSettings;
      QIODevice* m_pqDevice;


   public:
   /** +-=---------------------------------------------------------Sa 17. Nov 13:34:07 2007-------*
    * @method  CwmsExportWriter::CwmsExportWriter    // public                            *
    * @return                                                //                                   *
    * @param   CwmsExportSettings p_cCwmsExportSettings      //                                   *
    * @comment                                                                                    *
    *----------------last changed: Wolfgang Graßhof-------------Sa 17. Nov 13:34:07 2007----------*/
    CwmsExportWriter( CwmsExportSettings p_cCwmsExportSettings);

   public:
   /** +-=---------------------------------------------------------Do 15. Nov 23:13:05 2007-------*
    * @method  CwmsExportWriter::~CwmsExportWriter   // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CwmsExportWriter                                       *
    *----------------last changed: Wolfgang Graßhof-------------Do 15. Nov 23:13:05 2007----------*/
    virtual ~CwmsExportWriter( );

   public:
   /** +-=---------------------------------------------------------So 18. Nov 11:34:32 2007-------*
    * @method  CwmsExportWriter::Export                  // public                            *
    * @return  bool                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: Wolfgang Graßhof-------------So 18. Nov 11:34:32 2007----------*/
    bool Export();


   private:
   /** +-=---------------------------------------------------------So 18. Nov 11:15:47 2007-------*
    * @method  CwmsExportWriter::GetObjectList           // private                           *
    * @return  CdmObjectContainer*                                //                                   *
    * @comment finds the objectlist dependent from the settings.                                  *
    *----------------last changed: Wolfgang Graßhof-------------So 18. Nov 11:15:47 2007----------*/
    CdmObjectContainer* GetObjectList();

   private:
   /** +-=---------------------------------------------------------Mo 29. Okt 10:37:11 2012-------*
    * @method  CwmsExportWriter::ExportCsv               // private                           *
    * @return  bool                                          //                                   *
    * @param   QTextStream& p_rqtStream                      //                                   *
    * @param   CdmObjectContainer* p_pContainer               //                                   *
    * @param   QLinkedList<long> p_rqvlObjects                //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 29. Okt 10:37:11 2012----------*/
    bool ExportCsv(QTextStream& p_rqtStream,
                   CdmObjectContainer* p_pContainer,
                   QLinkedList<long> p_rqvlObjects);

   private:
   /** +-=---------------------------------------------------------Mo 29. Okt 10:38:10 2012-------*
    * @method  CwmsExportWriter::OpenDevice                // private                           *
    * @return  bool                                          //                                   *
    * @param   QTextStream& p_rqtStream                      //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 29. Okt 10:38:10 2012----------*/
    bool OpenDevice(QTextStream& p_rqtStream);

   private:
   /** +-=---------------------------------------------------------Sa 17. Nov 14:29:34 2007-------*
    * @method  CwmsExportWriter::CloseDevice               // private                           *
    * @return  void                                          //                                   *
    * @comment This method closes the file.                                                       *
    *----------------last changed: Wolfgang Graßhof-------------Sa 17. Nov 14:29:34 2007----------*/
    void CloseDevice();

   private:
   /** +-=---------------------------------------------------------So 18. Nov 11:15:39 2007-------*
    * @method  CwmsExportWriter::GetQueryObjects         // private                           *
    * @return  bool                                          // successflag                       *
    * @param   QLinkedList<long>& p_rqvlObjects               //                                   *
    * @param   CdmObjectContainer* p_pContainer               //                                   *
    * @comment This method returns the query objects which are the result of the query.           *
    *----------------last changed: Wolfgang Graßhof-------------So 18. Nov 11:15:39 2007----------*/
    bool GetQueryObjects(QLinkedList<long>& p_rqvlObjects, CdmObjectContainer* p_pContainer);

   private:
   /** +-=---------------------------------------------------------Mo 29. Okt 10:37:36 2012-------*
    * @method  CwmsExportWriter::ExportHtml              // private                           *
    * @return  bool                                          //                                   *
    * @param   QTextStream& p_rqtStream                      //                                   *
    * @param   CdmObjectContainer* p_pContainer               //                                   *
    * @param   QLinkedList<long> p_rqvlObjects                //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 29. Okt 10:37:36 2012----------*/
    bool ExportHtml(QTextStream& p_rqtStream,
                    CdmObjectContainer* p_pContainer,
                    QLinkedList<long> p_rqvlObjects);

   private:
   /** +-=---------------------------------------------------------Mo 29. Okt 10:37:44 2012-------*
    * @method  CwmsExportWriter::ExportXml               // private                           *
    * @return  bool                                          //                                   *
    * @param   QTextStream& p_rqtStream                      //                                   *
    * @param   CdmObjectContainer* p_pContainer               //                                   *
    * @param   QLinkedList<long> p_rqvlObjects                //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 29. Okt 10:37:44 2012----------*/
    bool ExportXml(QTextStream& p_rqtStream,
                   CdmObjectContainer* p_pContainer,
                   QLinkedList<long> p_rqvlObjects);

   private:
   /** +-=---------------------------------------------------------So 18. Nov 11:15:23 2007-------*
    * @method  CwmsExportWriter::GetCsvHeader            // private                           *
    * @return  QString                                       //                                   *
    * @param   CdmObjectContainer* p_pContainer               //                                   *
    * @comment                                                                                    *
    *----------------last changed: Wolfgang Graßhof-------------So 18. Nov 11:15:23 2007----------*/
    QString GetCsvHeader(CdmObjectContainer* p_pContainer);

   private:
   /** +-=---------------------------------------------------------So 18. Nov 11:15:18 2007-------*
    * @method  CwmsExportWriter::GetCsvSeperator         // private                           *
    * @return  QString                                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: Wolfgang Graßhof-------------So 18. Nov 11:15:18 2007----------*/
    QString GetCsvSeperator();

   private:
   /** +-=---------------------------------------------------------So 18. Nov 11:15:12 2007-------*
    * @method  CwmsExportWriter::GetHtmlHeader           // private                           *
    * @return  QString                                       //                                   *
    * @param   CdmObjectContainer* p_pContainer               //                                   *
    * @comment                                                                                    *
    *----------------last changed: Wolfgang Graßhof-------------So 18. Nov 11:15:12 2007----------*/
    QString GetHtmlHeader(CdmObjectContainer* p_pContainer);

   private:
   /** +-=---------------------------------------------------------So 18. Nov 11:24:44 2007-------*
    * @method  CwmsExportWriter::GetHtmlFooter           // private                           *
    * @return  QString                                       //                                   *
    * @comment returns the Html footer.                                                           *
    *----------------last changed: Wolfgang Graßhof-------------So 18. Nov 11:24:44 2007----------*/
    QString GetHtmlFooter();

   private:
   /** +-=---------------------------------------------------------Mi 19. Aug 19:26:00 2009-------*
    * @method  CwmsExportWriter::GetBinDocExport         // private                           *
    * @return  QString                                       //                                   *
    * @param   CdmValue* p_pCdmValue                         //                                   *
    * @param   bool p_bHtml = false                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 19. Aug 19:26:00 2009----------*/
    QString GetBinDocExport(CdmValue* p_pCdmValue, bool p_bHtml = false);

   private:
   /** +-=---------------------------------------------------------Mi 19. Aug 19:55:39 2009-------*
    * @method  CwmsExportWriter::GetBinDocExportXml      // private                           *
    * @return  void                                          //                                   *
    * @param   QDomElement& p_rqdElement                     //                                   *
    * @param   CdmValue* p_pCdmValue                         //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 19. Aug 19:55:39 2009----------*/
    void GetBinDocExportXml(QDomElement& p_rqdElement, CdmValue* p_pCdmValue);

   public:
   /** +-=---------------------------------------------------------Do 28. Feb 11:21:54 2013-------*
    * @method  CwmsExportWriter::SetDevice               // public                            *
    * @return  void                                          //                                   *
    * @param   QIODevice* p_pDevice                          // change of ownership will be deleted*
    *                                                        //  after export is finished         *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 28. Feb 11:21:54 2013----------*/
    void SetDevice(QIODevice* p_pDevice);
};

#endif //
