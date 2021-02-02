/******************************************************************************
 ** WOGRA Middleware Server Data Manager Module
 **
 ** @Author Wolfgang Graßhof 
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies All rights reserved
 ******************************************************************************/


// System and QT Includes
#include <qdom.h>
#include <QLinkedList>


// own Includes
#include "wmsdefines.h"
#include "CdmLogging.h"
#include "CdmValueListDouble.h"


/** +-=---------------------------------------------------------Mo 13. Aug 15:45:43 2007----------*
 * @method  CdmValueListDouble::CdmValueListDouble                     // public                            *
 * @return                                                   //                                   *
 * @param   long p_lDatabaseId                               //                                   *
 * @param   long p_lId                                       //                                   *
 * @param   QString p_qstrKeyname                            //                                   *
 * @param   CdmObject* p_pCdmObject                          //                                   *
 * @comment The constructor of the stringlist.                                                    *
 *----------------last changed: --------------------------------Mo 13. Aug 15:45:43 2007----------*/
CdmValueListDouble::CdmValueListDouble(long p_lDatabaseId,
                             long p_lId,
                             QString p_qstrKeyname,
                             CdmObject* p_pCdmObject)
: CdmValueCharacterDocument(p_lDatabaseId, p_lId, p_qstrKeyname, eDmValueListDouble, p_pCdmObject)
{
}

/** +-=---------------------------------------------------------Mo 13. Aug 16:25:49 2007----------*
 * @method  CdmValueListDouble::CdmValueListDouble                     // public                            *
 * @return                                                   //                                   *
 * @param   QDomElement& p_rqDomElement                      //                                   *
 * @param   CdmObject* p_pCdmObject                          //                                   *
 * @comment The constructor.                                                                      *
 *----------------last changed: --------------------------------Mo 13. Aug 16:25:49 2007----------*/
CdmValueListDouble::CdmValueListDouble(QDomElement& p_rqDomElement, CdmObject* p_pCdmObject)
   : CdmValueCharacterDocument(p_rqDomElement, p_pCdmObject)
{
}

/** +-=---------------------------------------------------------Mo 16. Apr 11:48:20 2012----------*
 * @method  CdmValueListDouble::CdmValueListDouble           // public                            *
 * @return                                                   //                                   *
 * @param   QVariantMap& p_rqvHash                          //                                   *
 * @param   CdmObject* p_pCdmObject                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 16. Apr 11:48:20 2012----------*/
CdmValueListDouble::CdmValueListDouble(QVariantMap& p_rqvHash, CdmObject* p_pCdmObject)
: CdmValueCharacterDocument(p_rqvHash, p_pCdmObject)
{
   Deserialize();
}

/** +-=---------------------------------------------------------Mo 13. Aug 15:45:48 2007----------*
 * @method  CdmValueListDouble::~CdmValueListDouble                    // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CdmIntList                                                    *
 *----------------last changed: --------------------------------Mo 13. Aug 15:45:48 2007----------*/
CdmValueListDouble::~CdmValueListDouble()
{
}

/** +-=---------------------------------------------------------Mo 3. Dez 15:36:42 2012-----------*
 * @method  CdmValueListDouble::Deploy                       // public, virtual                   *
 * @return  void                                             //                                   *
 * @param   QVariantMap& p_rqvHash                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 3. Dez 15:36:42 2012-----------*/
void CdmValueListDouble::Deploy(QVariantMap& p_rqvHash)
{
   CdmValueCharacterDocument::Deploy(p_rqvHash);
   Deserialize();
}

/** +-=---------------------------------------------------------Sa 14. Jun 18:45:40 2008----------*
 * @method  CdmValueListDouble::SetValue                     // public, virtual                   *
 * @return  void                                             //                                   *
 * @param   QString p_qstrValue                              //                                   *
 * @comment This method sets the value of this Value.                                             *
 *----------------last changed: --------------------------------Sa 14. Jun 18:45:40 2008----------*/
void CdmValueListDouble::SetValue(QString p_qstrValue)
{
   CdmValueCharacterDocument::SetValue(p_qstrValue);
   Deserialize();
}

/** +-=---------------------------------------------------------Di 12. Feb 10:53:30 2013----------*
 * @method  CdmValueListDouble::GetValue                     // public, const, virtual            *
 * @return  QString                                          //                                   *
 * @comment returns the value.                                                                    *
 *----------------last changed: --------------------------------Di 12. Feb 10:53:30 2013----------*/
QString CdmValueListDouble::GetValue() const
{

   Serialize();
   return m_qstrDocument;
}

/** +-=---------------------------------------------------------Di 12. Feb 10:53:34 2013----------*
 * @method  CdmValueListDouble::Serialize                    // private, const                    *
 * @return  void                                             //                                   *
 * @comment This method serializes the list to xml document.                                      *
 *----------------last changed: --------------------------------Di 12. Feb 10:53:34 2013----------*/
void CdmValueListDouble::Serialize() const
{
   QDomDocument qddDocument(WMS_LIST);

   QLinkedList<double>::const_iterator qvlIt = m_qvlDoubles.begin();
   QLinkedList<double>::const_iterator qvlItEnd = m_qvlDoubles.end();

   QDomElement qdeElement = qddDocument.createElement(WMS_LISTENTRIES);
   qddDocument.appendChild(qdeElement);
   int iCounter = 1;

   for (; qvlIt != qvlItEnd; ++qvlIt)
   {
      QDomElement qdeMapEntry = qddDocument.createElement(WMS_ENTRY);
      qdeMapEntry.setAttribute(WMS_COUNT, iCounter);
      qdeMapEntry.setAttribute(WMS_DATA, QString::number(*qvlIt, 'f', 16));
      qdeElement.appendChild(qdeMapEntry);
      ++iCounter;
   }

   m_qstrDocument = qddDocument.toString();
}

/** +-=---------------------------------------------------------Mo 13. Aug 15:35:13 2007----------*
 * @method  CdmValueListDouble::Deserialize                       // private                           *
 * @return  void                                             //                                   *
 * @comment This mehtod deserialize the xml document to the list.                                 *
 *----------------last changed: --------------------------------Mo 13. Aug 15:35:13 2007----------*/
void CdmValueListDouble::Deserialize()
{
    CdmValueListDouble::DeserializeXmlToDoubleList(m_qstrDocument, m_qvlDoubles);
}

void CdmValueListDouble::DeserializeXmlToDoubleList(QString& p_qstrXml, QLinkedList<double>& p_qllList)
{
    p_qllList.clear();
    QDomDocument qddDocument;
    QString qstrKey;
    QString qstrData;
    qddDocument.setContent(p_qstrXml);
    QDomElement qdeElement = qddDocument.documentElement();
    QDomNode qdnNode = qdeElement.firstChild();

    while(!qdnNode.isNull())
    {
       qstrData = "";
       qstrKey = "";
       QDomElement qdeElement = qdnNode.toElement(); // try to convert the node to an element.
       qstrData = qdeElement.attribute(WMS_DATA);
       p_qllList.append(qstrData.toDouble());
       qdnNode = qdnNode.nextSibling();
    }
}

/** +-=---------------------------------------------------------Di 20. Nov 09:40:35 2012----------*
 * @method  CdmValueListDouble::AddValue                     // public, slots                     *
 * @return  void                                             //                                   *
 * @param   double p_dValue                                  //                                   *
 * @comment This method adds an value to the list.                                                *
 *----------------last changed: --------------------------------Di 20. Nov 09:40:35 2012----------*/
void CdmValueListDouble::AddValue(double p_dValue)
{
   if (!m_qvlDoubles.contains(p_dValue))
   {
      m_qvlDoubles.append(p_dValue);
      ValueChanged();
   }
}


/** +-=---------------------------------------------------------Di 20. Nov 09:40:41 2012----------*
 * @method  CdmValueListDouble::RemoveValue                  // public, slots                     *
 * @return  void                                             //                                   *
 * @param   double p_dValue                                  //                                   *
 * @comment This method removes a value from list.                                                *
 *----------------last changed: --------------------------------Di 20. Nov 09:40:41 2012----------*/
void CdmValueListDouble::RemoveValue(double p_dValue)
{
   m_qvlDoubles.removeOne(p_dValue);
   ValueChanged();
}

/** +-=---------------------------------------------------------So 10. Feb 09:07:28 2013----------*
 * @method  CdmValueListDouble::GetList                      // public, const, slots              *
 * @return  QLinkedList<double>                              //                                   *
 * @comment This method returns a copy of the list.                                               *
 *----------------last changed: --------------------------------So 10. Feb 09:07:28 2013----------*/
QLinkedList<double> CdmValueListDouble::GetList() const
{
   return m_qvlDoubles;
}

/** +-=---------------------------------------------------------Di 20. Nov 09:41:06 2012----------*
 * @method  CdmValueListDouble::SetList                      // public, slots                     *
 * @return  void                                             //                                   *
 * @param   QLinkedList<double> p_qllDoubles                 //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 20. Nov 09:41:06 2012----------*/
void CdmValueListDouble::SetList(QLinkedList<double> p_qllDoubles)
{
   m_qvlDoubles = p_qllDoubles;
   ValueChanged();
}

/** +-=---------------------------------------------------------So 10. Feb 09:07:36 2013----------*
 * @method  CdmValueListDouble::GetValueAsString             // public, const, virtual, slots     *
 * @return  QString                                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 10. Feb 09:07:36 2013----------*/
QString CdmValueListDouble::GetValueAsString() const
{
   QString qstrList;

   QLinkedList<double>::const_iterator qvlIt = m_qvlDoubles.begin();
   QLinkedList<double>::const_iterator qvlItEnd = m_qvlDoubles.end();

   for (; qvlIt != qvlItEnd; ++qvlIt)
   {
      qstrList += QString::number(*qvlIt) + "\n";
   }

   return qstrList;
}

/** +-=---------------------------------------------------------So 10. Feb 09:07:56 2013----------*
 * @method  CdmValueListDouble::GetValueVariant              // public, const, virtual            *
 * @return  QVariant                                         //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------So 10. Feb 09:07:56 2013----------*/
QVariant CdmValueListDouble::GetValueVariant() const
{
    QVariantList qvVariant;
    QString qstrValue = GetValueAsString();
    QStringList qList = qstrValue.split("\n", QString::SkipEmptyParts);

    for (int iPos = 0; iPos < qList.count(); ++iPos)
    {
        qvVariant.append(qList[iPos]);
    }
   return qvVariant;
}

void CdmValueListDouble::SetValueVariant(QVariant& p_rVariant)
{
    QVariantList values = p_rVariant.toList();
    m_qvlDoubles.clear();
    for(QVariant v: values) {
        bool success;
        double iVal = v.toDouble(&success);
        if(success){
            m_qvlDoubles.append(iVal);
        }
    }
}
