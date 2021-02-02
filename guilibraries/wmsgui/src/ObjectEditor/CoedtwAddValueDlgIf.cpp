/******************************************************************************
 ** WOGRA technologies Modul Information
 ** Modulename: CoedtwAddValueDlgIf.cpp
 ** Started Implementation: 2008/09/05
 ** Description:
 ** 
 ** Implements the add key/value dialog for adding and editing mapvalues.
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies All rights reserved
 *****************************************************************************/ 

// System and QT Includes

// WMS Includes
#include "CdmMessageManager.h"

// Own Includes
#include "CoedtwAddValueDlgIf.h"


/** +-=---------------------------------------------------------Fr 5. Sep 18:15:15 2008-----------*
 * @method  CoedtwAddValueDlgIf::CoedtwAddValueDlgIf         // public                            *
 * @return                                                   //                                   *
 * @param   QWidget* p_pqwParent = nullptr                      //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 5. Sep 18:15:15 2008-----------*/
CoedtwAddValueDlgIf::CoedtwAddValueDlgIf(QWidget* p_pqwParent)
    : QDialog(p_pqwParent)
{
    setupUi(this);
}

/** +-=---------------------------------------------------------Fr 5. Sep 18:14:56 2008-----------*
 * @method  CoedtwAddValueDlgIf::~CoedtwAddValueDlgIf        // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CoedtwAddValueDlgIf                                           *
 *----------------last changed: --------------------------------Fr 5. Sep 18:14:56 2008-----------*/
CoedtwAddValueDlgIf::~CoedtwAddValueDlgIf()
{
}

/** +-=---------------------------------------------------------Fr 5. Sep 18:16:19 2008-----------*
 * @method  CoedtwAddValueDlgIf::GetKeyAsInt                 // public                            *
 * @return  int                                              //                                   *
 * @comment returns the inserted key as int.                                                      *
 *----------------last changed: --------------------------------Fr 5. Sep 18:16:19 2008-----------*/
int CoedtwAddValueDlgIf::GetKeyAsInt()
{
   return m_pqleKey->text().toInt();
}

/** +-=---------------------------------------------------------Fr 5. Sep 18:16:40 2008-----------*
 * @method  CoedtwAddValueDlgIf::GetKeyAsString              // public                            *
 * @return  QString                                          //                                   *
 * @comment returns the key as sting.                                                             *
 *----------------last changed: --------------------------------Fr 5. Sep 18:16:40 2008-----------*/
QString CoedtwAddValueDlgIf::GetKeyAsString()
{
   return m_pqleKey->text();
}

/** +-=---------------------------------------------------------Fr 5. Sep 18:17:02 2008-----------*
 * @method  CoedtwAddValueDlgIf::GetValueAsString            // public                            *
 * @return  QString                                          //                                   *
 * @comment returns the value as string.                                                          *
 *----------------last changed: --------------------------------Fr 5. Sep 18:17:02 2008-----------*/
QString CoedtwAddValueDlgIf::GetValueAsString()
{
   return m_pqleValue->text();
}

/** +-=---------------------------------------------------------Fr 5. Sep 18:17:20 2008-----------*
 * @method  CoedtwAddValueDlgIf::GetValueAsInt               // public                            *
 * @return  int                                              //                                   *
 * @comment return the value as int.                                                              *
 *----------------last changed: --------------------------------Fr 5. Sep 18:17:20 2008-----------*/
int CoedtwAddValueDlgIf::GetValueAsInt()
{
   return m_pqleValue->text().toInt();
}

/** +-=---------------------------------------------------------Fr 5. Sep 19:01:03 2008-----------*
 * @method  CoedtwAddValueDlgIf::GetValueAsDouble            // public                            *
 * @return  double                                           //                                   *
 * @comment returns the value as double.                                                          *
 *----------------last changed: --------------------------------Fr 5. Sep 19:01:03 2008-----------*/
double CoedtwAddValueDlgIf::GetValueAsDouble()
{
   return m_pqleValue->text().toDouble();
}
/** +-=---------------------------------------------------------Fr 5. Sep 18:18:10 2008-----------*
 * @method  CoedtwAddValueDlgIf::SetValue                    // public                            *
 * @return  void                                             //                                   *
 * @param   QString p_qstrValue                              //                                   *
 * @comment Sets the value in lineedit.                                                           *
 *----------------last changed: --------------------------------Fr 5. Sep 18:18:10 2008-----------*/
void CoedtwAddValueDlgIf::SetValue(QString p_qstrValue)
{
   m_pqleValue->setText(p_qstrValue);
}

/** +-=---------------------------------------------------------Fr 5. Sep 18:18:41 2008-----------*
 * @method  CoedtwAddValueDlgIf::SetKey                      // public                            *
 * @return  void                                             //                                   *
 * @param   QString p_qstrKey                                //                                   *
 * @comment Sets the key in the lineedit.                                                         *
 *----------------last changed: --------------------------------Fr 5. Sep 18:18:41 2008-----------*/
void CoedtwAddValueDlgIf::SetKey(QString p_qstrKey)
{
   m_pqleKey->setText(p_qstrKey);
}

/** +-=---------------------------------------------------------Fr 5. Sep 18:15:54 2008-----------*
 * @method  CoedtwAddValueDlgIf::OKClickedSlot               // private, slots                    *
 * @return  void                                             //                                   *
 * @comment This slot will be called if the ok button was clicked. it checks the data.            *
 *----------------last changed: --------------------------------Fr 5. Sep 18:15:54 2008-----------*/
void CoedtwAddValueDlgIf::OKClickedSlot()
{
   if (m_pqleKey->text().isEmpty() || m_pqleValue->text().isEmpty())
   {
      CdmMessageManager::critical(tr("Eingabefehler"), tr("Bitte fÃ¼llen Sie beiden Felder aus."));
   }
   else
   {
      accept();
   }
}