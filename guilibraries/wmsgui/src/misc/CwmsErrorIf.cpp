/******************************************************************************
 ** WOGRA Middleware Server GUI Module
 **
 ** @Author Wolfgang Graßhof 
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies All rights reserved
 ******************************************************************************/



// System and QT Includes
#include <qcheckbox.h>
#include <qlineedit.h>
#include <qdatetime.h>

// own Includes
#include "CwmsTreeWidgetHelper.h"
#include "CwmsErrorSettingsIf.h"
#include "CwmsErrorIf.h"



/** +-=---------------------------------------------------------Di 28. Sep 14:36:13 2010----------*
 * @method  CwmsErrorIf::CwmsErrorIf                         // public                            *
 * @return                                                   //                                   *
 * @param   QWidget* parent = nullptr                           //                                   *
 * @param   Qt::WFlags fl = 0                                //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 28. Sep 14:36:13 2010----------*/
CwmsErrorIf::CwmsErrorIf(QWidget* parent)
: QDialog(parent),
  m_iInfoMessageCount(0),
  m_iWarningMessageCount(0),
  m_iErrorMessageCount(0),
  m_iFatalMessageCount(0)
{
   setupUi(this);
   m_pqchbError->setChecked(true);
   m_pqchbFatal->setChecked(true);
   m_pqpbConfig->hide();
}

/** +-=---------------------------------------------------------Mo 2. Jul 20:26:31 2007-----------*
 * @method  CwmsErrorIf::~CwmsErrorIf                        // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CwmsErrorIf                                                   *
 *----------------last changed: Wolfgang Graßhof----------------Mo 2. Jul 20:26:31 2007-----------*/
CwmsErrorIf::~CwmsErrorIf()
{
}

/** +-=---------------------------------------------------------Mo 2. Jul 21:19:51 2007-----------*
 * @method  CwmsErrorIf::AddError                            // public                            *
 * @return  void                                             //                                   *
 * @param   QTime p_qdtTimestamp                             //                                   *
 * @param   QString p_qstrModule                             //                                   *
 * @param   QString p_qstrMessage                            //                                   *
 * @param   int p_iLine                                      //                                   *
 * @comment Adds an error message to the adaptor must be reimplemented by derived class.          *
 *----------------last changed: Wolfgang Graßhof----------------Mo 2. Jul 21:19:51 2007-----------*/
void CwmsErrorIf::AddError(CdmLogEntry& p_Entry)
{
   if (m_pqchbError->isChecked())
   {
      QTreeWidgetItem* pqlviItem = new QTreeWidgetItem(m_pqlvErrors);
      pqlviItem->setText(0, p_Entry.GetTimestamp().toString("hh:mm:ss.zzz"));
      pqlviItem->setText(1, tr("Fehler"));
      pqlviItem->setText(2, p_Entry.GetErrorModule());
      pqlviItem->setText(3, QString::number(p_Entry.GetLine()));
      pqlviItem->setText(4, p_Entry.GetEventText());
      ++m_iErrorMessageCount;
      UpdateCounter();
   
      if (!m_qmDisplayFilesSeverity.contains(p_Entry.GetErrorModule()))
      {
         m_qmDisplayFilesSeverity[p_Entry.GetErrorModule()] = (eDmInfo | eDmWarning | eDmError | eDmFatal);
      }

      if (!isVisible())
      {
          //show();
      }
   }
   else
   {
      ++m_iErrorMessageCount;
   }
}

/** +-=---------------------------------------------------------Mo 2. Jul 21:20:00 2007-----------*
 * @method  CwmsErrorIf::AddInfo                             // public                            *
 * @return  void                                             //                                   *
 * @param   QTime p_qdtTimestamp                             //                                   *
 * @param   QString p_qstrModule                             //                                   *
 * @param   QString p_qstrMessage                            //                                   *
 * @param   int p_iLine                                      //                                   *
 * @comment Adds an error message to the adaptor must be reimplemented by derived class.          *
 *----------------last changed: Wolfgang Graßhof----------------Mo 2. Jul 21:20:00 2007-----------*/
void CwmsErrorIf::AddInfo(CdmLogEntry& p_Entry)
{
   if (m_pqchbInfo->isChecked() == true)
   {
      QTreeWidgetItem* pqlviItem = new QTreeWidgetItem(m_pqlvErrors);
      pqlviItem->setText(0, p_Entry.GetTimestamp().toString("hh:mm:ss.zzz"));
      pqlviItem->setText(1, tr("Info"));
      pqlviItem->setText(2, p_Entry.GetErrorModule());
      pqlviItem->setText(3, QString::number(p_Entry.GetLine()));
      pqlviItem->setText(4, p_Entry.GetEventText());
      ++m_iInfoMessageCount;
      UpdateCounter();

      if (!m_qmDisplayFilesSeverity.contains(p_Entry.GetErrorModule()))
      {
         m_qmDisplayFilesSeverity[p_Entry.GetErrorModule()] = (eDmInfo | eDmWarning | eDmError | eDmFatal);
      }

      if (!isVisible())
      {
          //show();
      }
   }
   else
   {
      ++m_iInfoMessageCount;
   }
}

/** +-=---------------------------------------------------------Mo 2. Jul 21:20:10 2007-----------*
 * @method  CwmsErrorIf::AddWarning                          // public                            *
 * @return  void                                             //                                   *
 * @param   QTime p_qdtTimestamp                             //                                   *
 * @param   QString p_qstrModule                             //                                   *
 * @param   QString p_qstrMessage                            //                                   *
 * @param   int p_iLine                                      //                                   *
 * @comment Adds an error message to the adaptor must be reimplemented by derived class.          *
 *----------------last changed: Wolfgang Graßhof----------------Mo 2. Jul 21:20:10 2007-----------*/
void CwmsErrorIf::AddWarning(CdmLogEntry& p_Entry)
{
   if (m_pqchbWarning->isChecked() == true)
   {
      QTreeWidgetItem* pqlviItem = new QTreeWidgetItem(m_pqlvErrors);
      pqlviItem->setText(0, p_Entry.GetTimestamp().toString("hh:mm:ss.zzz"));
      pqlviItem->setText(1, tr("Warnung"));
      pqlviItem->setText(2, p_Entry.GetErrorModule());
      pqlviItem->setText(3, QString::number(p_Entry.GetLine()));
      pqlviItem->setText(4, p_Entry.GetEventText());
      ++m_iWarningMessageCount;
      UpdateCounter();

      if (!m_qmDisplayFilesSeverity.contains(p_Entry.GetErrorModule()))
      {
         m_qmDisplayFilesSeverity[p_Entry.GetErrorModule()] = (eDmInfo | eDmWarning | eDmError | eDmFatal);
      }

      if (!isVisible())
      {
         // show();
      }
   }
   else
   {
      ++m_iWarningMessageCount;
   }
}

/** +-=---------------------------------------------------------Mo 2. Jul 21:20:19 2007-----------*
 * @method  CwmsErrorIf::AddFatal                            // public                            *
 * @return  void                                             //                                   *
 * @param   QTime p_qdtTimestamp                             //                                   *
 * @param   QString p_qstrModule                             //                                   *
 * @param   QString p_qstrMessage                            //                                   *
 * @param   int p_iLine                                      //                                   *
 * @comment Adds an error message to the adaptor must be reimplemented by derived class.          *
 *----------------last changed: Wolfgang Graßhof----------------Mo 2. Jul 21:20:19 2007-----------*/
void CwmsErrorIf::AddFatal(CdmLogEntry& p_Entry)
{
   if (m_pqchbFatal->isChecked() == true)
   {
      QTreeWidgetItem* pqlviItem = new QTreeWidgetItem(m_pqlvErrors);

      pqlviItem->setText(0, p_Entry.GetTimestamp().toString("hh:mm:ss.zzz"));
      pqlviItem->setText(1, tr("Fataler Fehler"));
      pqlviItem->setText(2, p_Entry.GetErrorModule());
      pqlviItem->setText(3, QString::number(p_Entry.GetLine()));
      pqlviItem->setText(4, p_Entry.GetEventText());
      ++m_iFatalMessageCount;
      UpdateCounter();

      if (!m_qmDisplayFilesSeverity.contains(p_Entry.GetErrorModule()))
      {
         m_qmDisplayFilesSeverity[p_Entry.GetErrorModule()] = (eDmInfo | eDmWarning | eDmError | eDmFatal);
      }

      if (!isVisible())
      {
       //   show();
      }
   }
   else
   {
      ++m_iFatalMessageCount;
   }
}

/** +-=---------------------------------------------------------Mo 2. Jul 20:27:59 2007-----------*
 * @method  CwmsErrorIf::AddErrorCode                        // public                            *
 * @return  void                                             //                                   *
 * @param   QDateTime p_qdtTimeStamp                         //                                   *
 * @param   int p_iCode                                      //                                   *
 * @comment This method adds an error code to the adaptor.                                        *
 *----------------last changed: Wolfgang Graßhof----------------Mo 2. Jul 20:27:59 2007-----------*/
void CwmsErrorIf::AddErrorCode(QDateTime p_qdtTimeStamp, int p_iCode)
{
   Q_UNUSED(p_qdtTimeStamp);
   Q_UNUSED(p_iCode);
}

/** +-=---------------------------------------------------------Do 13. Sep 11:50:11 2012----------*
 * @method  CwmsErrorIf::SetItemVisible                      // public                            *
 * @return  void                                             //                                   *
 * @param   QTreeWidgetItem* p_pqlviItem                     //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 13. Sep 11:50:11 2012----------*/
void CwmsErrorIf::SetItemVisible(QTreeWidgetItem* p_pqlviItem)
{
   if (CHKPTR(p_pqlviItem))
   {
      p_pqlviItem->setSelected(true);
      m_pqlvErrors->scrollToItem(p_pqlviItem);
   }
}

/** +-=---------------------------------------------------------Sa 7. Jul 17:40:48 2007-----------*
 * @method  CwmsErrorIf::show                                // public                            *
 * @return  void                                             //                                   *
 * @comment overwritten to update some fields in the dialog.                                      *
 *----------------last changed: Wolfgang Graßhof----------------Sa 7. Jul 17:40:48 2007-----------*/
void CwmsErrorIf::show()
{
   UpdateCounter();
   QDialog::show();
}

/** +-=---------------------------------------------------------Fr 27. Jul 08:31:23 2007----------*
 * @method  CwmsErrorIf::UpdateCounter                       // public                            *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: Wolfgang Graßhof----------------Fr 27. Jul 08:31:23 2007----------*/
void CwmsErrorIf::UpdateCounter()
{
    if (isVisible())
    {
       m_pqleInterfaceCalls->setText(QString::number(CdmLoggingAdaptor::GetDataAccessCallCounter()));
       m_pqleInfoMessageCount->setText(QString::number(m_iInfoMessageCount));
       m_pqleWarningMessageCount->setText(QString::number(m_iWarningMessageCount));
       m_pqleErrorMessageCount->setText(QString::number(m_iErrorMessageCount));
       m_pqleFatalMessageCount->setText(QString::number(m_iFatalMessageCount));
       m_pqleCompleteMessageCount->setText(QString::number(m_iFatalMessageCount + m_iErrorMessageCount + m_iWarningMessageCount + m_iInfoMessageCount));
    }
}

/** +-=---------------------------------------------------------Fr 27. Jul 08:33:52 2007----------*
 * @method  CwmsErrorIf::ConfigClickedSlot                   // protected, slots                  *
 * @return  void                                             //                                   *
 * @comment This slot will be called to edit the messageconfiguration.                            *
 *----------------last changed: Wolfgang Graßhof----------------Fr 27. Jul 08:33:52 2007----------*/
void CwmsErrorIf::ConfigClickedSlot()
{
   CwmsErrorSettingsIf* pCwmsErrorSettings = new CwmsErrorSettingsIf(this);
   pCwmsErrorSettings->SetFileSeverities(m_qmDisplayFilesSeverity);
   pCwmsErrorSettings->exec();
   delete pCwmsErrorSettings;
}

/** +-=---------------------------------------------------------Do 13. Sep 11:48:59 2012----------*
 * @method  CwmsErrorIf::ItemSelectedSlot                    // public, slots                     *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 13. Sep 11:48:59 2012----------*/
void CwmsErrorIf::ItemSelectedSlot()
{
   QTreeWidgetItem* pItem = CwmsTreeWidgetHelper::GetSelectedItem(m_pqlvErrors);

   if (pItem)
   {
      m_pqtText->setPlainText(pItem->text(4));
   }
   else
   {
      m_pqtText->setPlainText("");
   }
}

/** +-=---------------------------------------------------------Di 8. Okt 20:31:04 2013-----------*
 * @method  CwmsErrorIf::SeverityChangedSlot                 // private, slots                    *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 8. Okt 20:31:04 2013-----------*/
void CwmsErrorIf::SeverityChangedSlot()
{ 
   int iErrorCode = 0;
   
   if (m_pqchbInfo->isChecked())
   {
      iErrorCode = iErrorCode | eDmInfo;
   }

   if (m_pqchbWarning->isChecked())
   {
      iErrorCode = iErrorCode | eDmWarning;
   }

   if (m_pqchbError->isChecked())
   {
      iErrorCode = iErrorCode | eDmError;
   }

   if (m_pqchbFatal->isChecked())
   {
      iErrorCode = iErrorCode | eDmFatal;
   }

   CdmLogging::SetLoggingMode(iErrorCode);
}
