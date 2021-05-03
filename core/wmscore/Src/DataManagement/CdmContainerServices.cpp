/******************************************************************************
 ** WOGRA technologies Modul Information
 ** Modulename: CdmContainerServices.cpp
 ** Started Implementation: 2009/04/04
 ** Description:
 ** 
 ** Implements services for objectlists.
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies All rights reserved
 *****************************************************************************/ 

// System and QT Includes
#include <QList>

// Own Includes
#include "CdmLogging.h"
#include "CdmValue.h"
#include "CdmValueInt.h"
#include "CdmValueFloat.h"
#include "CdmValueDouble.h"
#include "CdmValueDate.h"
#include "CdmValueDateTime.h"
#include "CdmValueTime.h"
#include "CdmContainerManager.h"
#include "CdmObjectContainer.h"
#include "CdmObject.h"
#include "CdmContainerServices.h"


/** +-=---------------------------------------------------------Sa 4. Apr 12:18:52 2009-----------*
 * @method  CdmContainerServices::CdmContainerServices     // private                           *
 * @return                                                   //                                   *
 * @comment SHOULD NOT BE CONSTRUCTED ALL METHODS AND FUNCTIONS ARE STATIC                        *
 *----------------last changed: --------------------------------Sa 4. Apr 12:18:52 2009-----------*/
CdmContainerServices::CdmContainerServices()
{
}

/** +-=---------------------------------------------------------Sa 4. Apr 12:19:08 2009-----------*
 * @method  CdmContainerServices::~CdmContainerServices    // private, virtual                  *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CdmContainerServices                                         *
 *----------------last changed: --------------------------------Sa 4. Apr 12:19:08 2009-----------*/
CdmContainerServices::~CdmContainerServices()
{
}

/** +-=---------------------------------------------------------Di 7. Apr 19:14:19 2009-----------*
 * @method  CdmContainerServices::EvaluateSum               // public, static                    *
 * @return  QString                                          // value as string for conversion issues*
 * @param   CdmObjectContainer* p_pContainer                  //                                   *
 * @param   QString p_qstrMember                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 7. Apr 19:14:19 2009-----------*/
QString CdmContainerServices::EvaluateSum(CdmObjectContainer* p_pContainer, QString p_qstrMember)
{
   QString qstrRet;

   if (CHKPTR(p_pContainer))
   {
      QList<CdmObject*> qllList;
      p_pContainer->GetObjectList(qllList);
      qstrRet = EvaluateSum(qllList, p_qstrMember);
   }

   return qstrRet;
}

/** +-=---------------------------------------------------------Di 7. Apr 19:14:39 2009-----------*
 * @method  CdmContainerServices::EvaluateSum               // public, static                    *
 * @return  QString                                          // value as string for conversion issues*
 * @param   QList<CdmObject*>& p_rqvlObjects           //                                   *
 * @param   QString p_qstrMember                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 7. Apr 19:14:39 2009-----------*/
QString CdmContainerServices::EvaluateSum(QList<CdmObject*>& p_rqvlObjects,
                                           QString p_qstrMember)
{
   QString qstrRet;
   bool bContinue = true;
   EdmValueType m_eDmType = eDmValueNone;
   int m_iValue = 0;
   double m_dValue = 0.0;
   QDate m_qdValue; 
   QDateTime m_qdtValue;
   QTime m_qtValue;

   QList<CdmObject*>::iterator qllIt = p_rqvlObjects.begin();
   QList<CdmObject*>::iterator qllItEnd = p_rqvlObjects.end();

   for(; qllIt != qllItEnd; ++qllIt)
   {
      CdmObject* pCdmObject = (*qllIt);

      if (CHKPTR(pCdmObject))
      {
         CdmValue* pCdmValue = pCdmObject->GetValue(p_qstrMember);

         switch (pCdmValue->GetValueType())
         {
         case eDmValueInt:
            {
               int iValue = ((CdmValueInt*)pCdmValue)->GetValue();
               m_iValue += iValue;
            }

            m_eDmType = eDmValueInt;
            break;
         case eDmValueDouble:
            {
               double dValue = ((CdmValueDouble*)pCdmValue)->GetValue();
               m_dValue += dValue;
            }

            m_eDmType = eDmValueDouble;
            break;
         case eDmValueFloat:
            {
               float fValue = ((CdmValueFloat*)pCdmValue)->GetValue();
               m_dValue += fValue;
            }

            m_eDmType = eDmValueFloat;
            break;
         default:
            ERR("Invalid Type Only Int, Double, Float are allowed!!!")
            bContinue = false;
            break;
         }
      }

      if (!bContinue)
      {
         qstrRet = "ERROR";
         break;
      }
   }

   if (bContinue)
   {
      switch (m_eDmType)
      {
      case eDmValueInt:
         qstrRet = QString::number(m_iValue);
         break;
      case eDmValueDouble:
      case eDmValueFloat:
         qstrRet = QString::number(m_dValue, 'f', 2);
         break;
      default:
         qstrRet = "ERROR";
         break;

      }
   }

   return qstrRet;
}


/** +-=---------------------------------------------------------Di 7. Apr 19:15:17 2009-----------*
 * @method  CdmContainerServices::EvaluateAverage           // public, static                    *
 * @return  QString                                          // value as string for conversion issues*
 * @param   CdmObjectContainer* p_pContainer                  //                                   *
 * @param   QString p_qstrMember                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 7. Apr 19:15:17 2009-----------*/
QString CdmContainerServices::EvaluateAverage(CdmObjectContainer* p_pContainer,
                                               QString p_qstrMember)
{
   QString qstrRet;

   if (CHKPTR(p_pContainer))
   {
      QList<CdmObject*> qllList;
      p_pContainer->GetObjectList(qllList);
      qstrRet = EvaluateAverage(qllList, p_qstrMember);
   }

   return qstrRet;
}

/** +-=---------------------------------------------------------Di 7. Apr 20:33:56 2009-----------*
 * @method  CdmContainerServices::EvaluateAverage           // public, static                    *
 * @return  QString                                          // value as string for conversion issues*
 * @param   QList<CdmObject*>& p_rqvlObjects           //                                   *
 * @param   QString p_qstrMember                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 7. Apr 20:33:56 2009-----------*/
QString CdmContainerServices::EvaluateAverage(QList<CdmObject*>& p_rqvlObjects,
                                               QString p_qstrMember)
{
   QString qstrRet;

   qstrRet = EvaluateSum(p_rqvlObjects, p_qstrMember);
   qstrRet = QString::number(qstrRet.toDouble() / p_rqvlObjects.count(), 'f', 2);

   return qstrRet;
}

/** +-=---------------------------------------------------------Di 7. Apr 19:16:13 2009-----------*
 * @method  CdmContainerServices::EvaluateMin               // public, static                    *
 * @return  QString                                          // value as string for conversion issues*
 * @param   CdmObjectContainer* p_pContainer                  //                                   *
 * @param   QString p_qstrMember                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 7. Apr 19:16:13 2009-----------*/
QString CdmContainerServices::EvaluateMin(CdmObjectContainer* p_pContainer, QString p_qstrMember)
{
   QString qstrRet;

   if (CHKPTR(p_pContainer))
   {
      QList<CdmObject*> qllList;
      p_pContainer->GetObjectList(qllList);
      qstrRet = EvaluateMin(qllList, p_qstrMember);
   }

   return qstrRet;
}

/** +-=---------------------------------------------------------Di 7. Apr 19:16:30 2009-----------*
 * @method  CdmContainerServices::EvaluateMin               // public, static                    *
 * @return  QString                                          // value as string for conversion issues*
 * @param   QList<CdmObject*>& p_rqvlObjects           //                                   *
 * @param   QString p_qstrMember                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 7. Apr 19:16:30 2009-----------*/
QString CdmContainerServices::EvaluateMin(QList<CdmObject*>& p_rqvlObjects,
                                           QString p_qstrMember)
{
   QString qstrRet;
   bool bContinue = true;
   bool bFirst = true;
   EdmValueType m_eDmType = eDmValueNone;
   int m_iValue = 0;
   double m_dValue = 0.0;
   QDate m_qdValue; 
   QDateTime m_qdtValue;
   QTime m_qtValue;

   QList<CdmObject*>::iterator qllIt = p_rqvlObjects.begin();
   QList<CdmObject*>::iterator qllItEnd = p_rqvlObjects.end();

   for(; qllIt != qllItEnd; ++qllIt)
   {
      CdmObject* pCdmObject = (*qllIt);

      if (CHKPTR(pCdmObject))
      {
         CdmValue* pCdmValue = pCdmObject->GetValue(p_qstrMember);

         switch (pCdmValue->GetValueType())
         {
         case eDmValueInt:
            {
               int iValue = ((CdmValueInt*)pCdmValue)->GetValue();

               if (bFirst)
               {
                  m_iValue = iValue;
               }
               else if (iValue < m_iValue)
               {
                  m_iValue = iValue;
               }
            }

            m_eDmType = eDmValueInt;
            break;
         case eDmValueDouble:
            {
               double dValue = ((CdmValueDouble*)pCdmValue)->GetValue();
               
               if (bFirst)
               {
                  m_dValue = dValue;
               }
               else if (dValue < m_dValue)
               {
                  m_dValue = dValue;
               }
            }

            m_eDmType = eDmValueDouble;
            break;
         case eDmValueFloat:
            {
               float fValue = ((CdmValueFloat*)pCdmValue)->GetValue();
               
               if (bFirst)
               {
                  m_dValue = fValue;
               }
               else if (fValue < m_dValue)
               {
                  m_dValue = fValue;
               }
            }

            m_eDmType = eDmValueFloat;
            break;
         case eDmValueDate:
            {
               QDate qdValue = ((CdmValueDate*)pCdmValue)->GetValue();

               if (bFirst)
               {
                  m_qdValue = qdValue;
               }
               else if (qdValue < m_qdValue)
               {
                  m_qdValue = qdValue;
               }
            }

            m_eDmType = eDmValueDate;
            break;
         case eDmValueDateTime:
            {
               QDateTime qdtValue = ((CdmValueDateTime*)pCdmValue)->GetValue();

               if (bFirst)
               {
                  m_qdtValue = qdtValue;
               }
               else if (qdtValue < m_qdtValue)
               {
                  m_qdtValue = qdtValue;
               }
            }

            m_eDmType = eDmValueDateTime;
            break;
         case eDmValueTime:
            {
               QTime qtValue = ((CdmValueTime*)pCdmValue)->GetValue();

               if (bFirst)
               {
                  m_qtValue = qtValue;
               }
               else if (qtValue < m_qtValue)
               {
                  m_qtValue = qtValue;
               }
            }

            m_eDmType = eDmValueTime;
            break;
         default:
            ERR("Invalid Type Only Int, Double, Float, Date, DateTime, Time are allowed!!!")
               bContinue = false;
            break;
         }
      }

      if (!bContinue)
      {
         qstrRet = "ERROR";
         break;
      }

      bFirst = false;
   }

   if (bContinue)
   {
      switch (m_eDmType)
      {
      case eDmValueInt:
         qstrRet = QString::number(m_iValue);
         break;
      case eDmValueDouble:
      case eDmValueFloat:
         qstrRet = QString::number(m_dValue, 'f', 2);
         break;
      case eDmValueDate:
         qstrRet = m_qdValue.toString();
         break;
      case eDmValueDateTime:
         qstrRet = m_qdtValue.toString();
         break;
      case eDmValueTime:
         qstrRet = m_qtValue.toString();
         break;
      default:
         qstrRet = "ERROR";
         break;
      }
   }

   return qstrRet;
}

/** +-=---------------------------------------------------------Di 7. Apr 19:17:08 2009-----------*
 * @method  CdmContainerServices::EvaluateMax               // public, static                    *
 * @return  QString                                          // value as string for conversion issues*
 * @param   CdmObjectContainer* p_pContainer                  //                                   *
 * @param   QString p_qstrMember                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 7. Apr 19:17:08 2009-----------*/
QString CdmContainerServices::EvaluateMax(CdmObjectContainer* p_pContainer, QString p_qstrMember)
{
   QString qstrRet;

   if (CHKPTR(p_pContainer))
   {
      QList<CdmObject*> qllList;
      p_pContainer->GetObjectList(qllList);
      qstrRet = EvaluateMax(qllList, p_qstrMember);
   }

   return qstrRet;

}

/** +-=---------------------------------------------------------Di 7. Apr 19:17:30 2009-----------*
 * @method  CdmContainerServices::EvaluateMax               // public, static                    *
 * @return  QString                                          // value as string for conversion issues*
 * @param   QList<CdmObject*>& p_rqvlObjects           //                                   *
 * @param   QString p_qstrMember                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Di 7. Apr 19:17:30 2009-----------*/
QString CdmContainerServices::EvaluateMax(QList<CdmObject*>& p_rqvlObjects,
                                           QString p_qstrMember)
{
   QString qstrRet;
   bool bContinue = true;
   bool bFirst = true;
   EdmValueType m_eDmType = eDmValueNone;
   int m_iValue = 0;
   double m_dValue = 0.0;
   QDate m_qdValue; 
   QDateTime m_qdtValue;
   QTime m_qtValue;

   QList<CdmObject*>::iterator qllIt = p_rqvlObjects.begin();
   QList<CdmObject*>::iterator qllItEnd = p_rqvlObjects.end();

   for(; qllIt != qllItEnd; ++qllIt)
   {
      CdmObject* pCdmObject = (*qllIt);

      if (CHKPTR(pCdmObject))
      {
         CdmValue* pCdmValue = pCdmObject->GetValue(p_qstrMember);

         switch (pCdmValue->GetValueType())
         {
         case eDmValueInt:
            {
               int iValue = ((CdmValueInt*)pCdmValue)->GetValue();

               if (bFirst)
               {
                  m_iValue = iValue;
               }
               else if (iValue > m_iValue)
               {
                  m_iValue = iValue;
               }
            }

            m_eDmType = eDmValueInt;
            break;
         case eDmValueDouble:
            {
               double dValue = ((CdmValueDouble*)pCdmValue)->GetValue();

               if (bFirst)
               {
                  m_dValue = dValue;
               }
               else if (dValue > m_dValue)
               {
                  m_dValue = dValue;
               }
            }

            m_eDmType = eDmValueDouble;
            break;
         case eDmValueFloat:
            {
               float fValue = ((CdmValueFloat*)pCdmValue)->GetValue();

               if (bFirst)
               {
                  m_dValue = fValue;
               }
               else if (fValue > m_dValue)
               {
                  m_dValue = fValue;
               }
            }

            m_eDmType = eDmValueFloat;
            break;
         case eDmValueDate:
            {
               QDate qdValue = ((CdmValueDate*)pCdmValue)->GetValue();

               if (bFirst)
               {
                  m_qdValue = qdValue;
               }
               else if (qdValue > m_qdValue)
               {
                  m_qdValue = qdValue;
               }
            }

            m_eDmType = eDmValueDate;
            break;
         case eDmValueDateTime:
            {
               QDateTime qdtValue = ((CdmValueDateTime*)pCdmValue)->GetValue();

               if (bFirst)
               {
                  m_qdtValue = qdtValue;
               }
               else if (qdtValue > m_qdtValue)
               {
                  m_qdtValue = qdtValue;
               }
            }

            m_eDmType = eDmValueDateTime;
            break;
         case eDmValueTime:
            {
               QTime qtValue = ((CdmValueTime*)pCdmValue)->GetValue();

               if (bFirst)
               {
                  m_qtValue = qtValue;
               }
               else if (qtValue > m_qtValue)
               {
                  m_qtValue = qtValue;
               }
            }

            m_eDmType = eDmValueTime;
            break;
         default:
            ERR("Invalid Type Only Int, Double, Float, Date, DateTime, Time are allowed!!!")
               bContinue = false;
            break;
         }
      }

      if (!bContinue)
      {
         qstrRet = "ERROR";
         break;
      }

      bFirst = false;
   }

   if (bContinue)
   {
      switch (m_eDmType)
      {
      case eDmValueInt:
         qstrRet = QString::number(m_iValue);
            break;
      case eDmValueDouble:
      case eDmValueFloat:
         qstrRet = QString::number(m_dValue, 'f', 2);
            break;
      case eDmValueDate:
         qstrRet = m_qdValue.toString();
         break;
      case eDmValueDateTime:
         qstrRet = m_qdtValue.toString();
         break;
      case eDmValueTime:
         qstrRet = m_qtValue.toString();
         break;
      default:
         qstrRet = "ERROR";
         break;
      }
   }

   return qstrRet;
}
