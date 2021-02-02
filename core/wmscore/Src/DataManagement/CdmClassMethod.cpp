/******************************************************************************
 ** WOGRA technologies GmbH & Co. KG Modul Information
 ** Modulename: CdmClassMethod.cpp
 ** Started Implementation: 2012/06/18
 ** Description:
 **
 ** Implements a class methods
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 **(C) copyright by WOGRA technologies GmbH & Co. KG All rights reserved
 *****************************************************************************/

// System and QT Includes
#include <QStringList>
#include <QFile>
#include <QPixmap>
#include <QByteArray>
#include <QVariant>

// WMS Commons Includes
#include "CwmsUtilities.h"
#include "wmsdefines.h"

// own Includes
#include "CdmSessionManager.h"
#include "CdmDataProvider.h"
#include "CdmMessageManager.h"
#include "CdmLogging.h"
#include "CdmClass.h"
#include "CdmExecutor.h"
#include "CdmClassMethod.h"

/** +-=---------------------------------------------------------Fr 21. Sep 11:17:35 2012----------*
 * @method  CdmClassMethod::CdmClassMethod                   // public                            *
 * @return                                                   //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 21. Sep 11:17:35 2012----------*/
CdmClassMethod::CdmClassMethod()
: m_eAccess(eDmMemberAccessPrivate),
  m_iVersion(0),
  m_eReturnType(eDmValueNone),
  m_iId(-1),
  m_bStatic(false),
  m_rpCdmClass(nullptr)
{
}

/** +-=---------------------------------------------------------Mi 27. Jun 16:03:30 2012----------*
 * @method  CdmClassMethod::CdmClassMethod                   // public                            *
 * @return                                                   //                                   *
 * @param   int p_iId                                        //                                   *
 * @param   QString p_qstrMethodName                         //                                   *
 * @param   EdmValue p_eReturnType                      //                                   *
 * @param   EdmMemberAccess p_eAccessMode                    //                                   *
 * @param   QString p_qstrCode                               //                                   *
 * @param   int p_iVersion                                   //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 27. Jun 16:03:30 2012----------*/
CdmClassMethod::CdmClassMethod(int p_iId,
                               QString p_qstrMethodName,
                               EdmValueType p_eReturnType,
                               EdmMemberAccess p_eAccessMode,
                               QString p_qstrCode,
                               int p_iVersion)
: m_qstrMethodName(p_qstrMethodName),
  m_qstrSourceCode(""),
  m_eAccess(p_eAccessMode),
  m_iVersion(p_iVersion),
  m_eReturnType(p_eReturnType),
  m_iId(p_iId),
  m_bStatic(false),
  m_rpCdmClass(nullptr)
{
    SetSourceCode(p_qstrCode);
}

/** +-=---------------------------------------------------------Mi 20. Jun 15:04:36 2012----------*
 * @method  CdmClassMethod::CdmClassMethod                   // public                            *
 * @return                                                   //                                   *
 * @param   QVariantMap& p_rvHash                           //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 20. Jun 15:04:36 2012----------*/
CdmClassMethod::CdmClassMethod(QVariantMap& p_rvHash)
: m_eAccess(eDmMemberAccessPrivate),
  m_iVersion(0),
  m_eReturnType(eDmValueNone),
  m_iId(-1),
  m_bStatic(false),
  m_rpCdmClass(nullptr)
{
   SetVariant(p_rvHash);
}

/** +-=---------------------------------------------------------Mo 18. Jun 16:34:05 2012----------*
 * @method  CdmClassMethod::~CdmClassMethod                  // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CdmClassMethod                                                *
 *----------------last changed: --------------------------------Mo 18. Jun 16:34:05 2012----------*/
CdmClassMethod::~CdmClassMethod()
{
}

/** +-=---------------------------------------------------------Sa 9. Feb 12:19:52 2013-----------*
 * @method  CdmClassMethod::GetId                            // public, const, slots              *
 * @return  int                                              //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 9. Feb 12:19:52 2013-----------*/
int CdmClassMethod::GetId() const
{
   return m_iId.load();
}

/** +-=---------------------------------------------------------Mi 27. Jun 16:04:26 2012----------*
 * @method  CdmClassMethod::SetId                            // public                            *
 * @return  void                                             //                                   *
 * @param   int p_iId                                        //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 27. Jun 16:04:26 2012----------*/
void CdmClassMethod::SetId(int p_iId)
{
   m_iId = p_iId;
}

/** +-=---------------------------------------------------------Mi 20. Jun 15:04:53 2012----------*
 * @method  CdmClassMethod::SetVariant                       // public                            *
 * @return  void                                             //                                   *
 * @param   QVariantMap& p_rqvHash                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 20. Jun 15:04:53 2012----------*/
void CdmClassMethod::SetVariant(QVariantMap& p_rqvHash)
{
    SYNCHRONIZED_WRITE;
   QVariantMap qmRights = p_rqvHash[WMS_RIGHTS].toMap();
   m_cCdmRights.SetVariant(qmRights);
   m_qstrMethodName = p_rqvHash[WMS_NAME].toString();
   SetSourceCode(p_rqvHash[WMS_CODE].toString());
   m_eReturnType = (EdmValueType)p_rqvHash[WMS_TYPE].toInt();
   m_bStatic = p_rqvHash[WMS_STATIC].toBool();
   m_eAccess = (EdmMemberAccess)p_rqvHash[WMS_ACCESS].toInt();
   m_iVersion = p_rqvHash[WMS_VERSION].toInt();
   m_qstrComment = p_rqvHash[WMS_COMMENT].toString();
   m_qstrCaption = p_rqvHash[WMS_CAPTION].toString();
   m_qbaIcon = QByteArray::fromBase64(p_rqvHash[WMS_ICON].toString().toLocal8Bit());
   QVariantMap qvParameters = p_rqvHash[WMS_PARAMETERS].toMap();

   QVariantMap::iterator qvIt = qvParameters.begin();
   QVariantMap::iterator qvItEnd = qvParameters.end();
   m_qlParameters.clear();
   for(int i=0; i<qvParameters.size(); i++){
       CdmClassMethodParameter cParam;
       m_qlParameters.append(cParam);
   }

   for (; qvIt != qvItEnd; ++qvIt)
   {
      CdmClassMethodParameter cParam;
      QVariantMap qvParameter = qvIt.value().toMap();
      cParam.SetName(qvParameter[WMS_NAME].toString());
      cParam.m_eType = (EdmValueType)qvParameter[WMS_TYPE].toInt();
      cParam.m_iPos = qvParameter[WMS_POS].toInt();
      cParam.m_lReference = qvParameter[WMS_REFERENCE].toInt();
      m_qlParameters[cParam.m_iPos] = cParam;
   }
}

/** +-=---------------------------------------------------------Mo 12. Nov 11:23:59 2012----------*
 * @method  CdmClassMethod::SetClass                         // public                            *
 * @return  void                                             //                                   *
 * @param   CdmClass* p_pCdmClass                            //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 12. Nov 11:23:59 2012----------*/
void CdmClassMethod::SetClass(CdmClass* p_pCdmClass)
{
    SYNCHRONIZED_WRITE;
   m_rpCdmClass = p_pCdmClass;
}

/** +-=---------------------------------------------------------Sa 9. Feb 12:20:13 2013-----------*
 * @method  CdmClassMethod::GetClass                         // public, const, slots              *
 * @return  CdmClass*                                        //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 9. Feb 12:20:13 2013-----------*/
CdmClass* CdmClassMethod::GetClass() const
{
    SYNCHRONIZED_READ;
   return m_rpCdmClass;
}

/** +-=---------------------------------------------------------Sa 9. Feb 12:20:30 2013-----------*
 * @method  CdmClassMethod::GetVersion                       // public, const, slots              *
 * @return  int                                              //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 9. Feb 12:20:30 2013-----------*/
int CdmClassMethod::GetVersion() const
{
   return m_iVersion.load();
}

/** +-=---------------------------------------------------------Mo 18. Jun 16:34:51 2012----------*
 * @method  CdmClassMethod::SetVersion                       // public                            *
 * @return  void                                             //                                   *
 * @param   int p_iVersion                                   //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 18. Jun 16:34:51 2012----------*/
void CdmClassMethod::SetVersion(int p_iVersion)
{
   m_iVersion = p_iVersion;
}

/** +-=---------------------------------------------------------Mi 27. Jun 15:55:20 2012----------*
 * @method  CdmClassMethod::SetSourceCode                    // public                            *
 * @return  void                                             //                                   *
 * @param   QString p_qstrCode                               //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 27. Jun 15:55:20 2012----------*/
void CdmClassMethod::SetSourceCode(QString p_qstrCode)
{
    SYNCHRONIZED_WRITE;
    if (!CwmsUtilities::IsStringBase64Encode(p_qstrCode))
    {
        QByteArray ba;
        ba.append(p_qstrCode);
        m_qstrSourceCode = ba.toBase64();
    }
    else
    {
        m_qstrSourceCode = p_qstrCode;
    }
}

/** +-=---------------------------------------------------------Sa 9. Feb 12:20:39 2013-----------*
 * @method  CdmClassMethod::GetSourceCode                    // public, const, slots              *
 * @return  QString                                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 9. Feb 12:20:39 2013-----------*/
QString CdmClassMethod::GetSourceCode() const
{
    SYNCHRONIZED_READ;
    QString qstrCode;
    if (CwmsUtilities::IsStringBase64Encode(m_qstrSourceCode))
    {
        QByteArray ba;
        ba.append(m_qstrSourceCode);
        qstrCode = QByteArray::fromBase64(ba);
    }
    else
    {
        qstrCode = m_qstrSourceCode;
    }

    return qstrCode;
}

QString CdmClassMethod::GetSourceCodeBase64() const
{
    SYNCHRONIZED_READ;
    if (!CwmsUtilities::IsStringBase64Encode(m_qstrSourceCode))
    {
        QByteArray ba;
        ba.append(m_qstrSourceCode);
        return ba.toBase64();
    }

    return m_qstrSourceCode;
}

/** +-=---------------------------------------------------------Sa 9. Feb 12:20:46 2013-----------*
 * @method  CdmClassMethod::GetMethodName                    // public, const, slots              *
 * @return  QString                                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 9. Feb 12:20:46 2013-----------*/
QString CdmClassMethod::GetMethodName() const
{
    SYNCHRONIZED_READ;
   return m_qstrMethodName;
}

/** +-=---------------------------------------------------------Mo 18. Jun 16:35:31 2012----------*
 * @method  CdmClassMethod::SetMethodName                    // public                            *
 * @return  void                                             //                                   *
 * @param   QString p_qstrName                               //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 18. Jun 16:35:31 2012----------*/
void CdmClassMethod::SetMethodName(QString p_qstrName)
{
    SYNCHRONIZED_WRITE;
   m_qstrMethodName = p_qstrName;
}

/** +-=---------------------------------------------------------Mo 4. Feb 15:06:20 2013-----------*
 * @method  CdmClassMethod::SetCaption                       // public                            *
 * @return  void                                             //                                   *
 * @param   QString p_qstrCaption                            //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 4. Feb 15:06:20 2013-----------*/
void CdmClassMethod::SetCaption(QString p_qstrCaption)
{
    SYNCHRONIZED_WRITE;
   m_qstrCaption = p_qstrCaption;
}

/** +-=---------------------------------------------------------Sa 9. Feb 12:20:56 2013-----------*
 * @method  CdmClassMethod::GetCaption                       // public, const                     *
 * @return  QString                                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 9. Feb 12:20:56 2013-----------*/
QString CdmClassMethod::GetCaption() const
{
    SYNCHRONIZED_READ;
   QString qstrRet;

   if (m_qstrCaption.isEmpty())
   {
      qstrRet = GetMethodName();
   }
   else
   {
      qstrRet = m_qstrCaption;
   }

   return qstrRet;
}

/** +-=---------------------------------------------------------Mo 4. Feb 15:12:52 2013-----------*
 * @method  CdmClassMethod::SetIcon                          // public                            *
 * @return  void                                             //                                   *
 * @param   QString p_qstrFilename                           //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 4. Feb 15:12:52 2013-----------*/
void CdmClassMethod::SetIcon(QString p_qstrFilename)
{
    SYNCHRONIZED_WRITE;
   QFile qFile(p_qstrFilename);

   if (qFile.open(QIODevice::ReadOnly))
   {
      m_qbaIcon = qFile.readAll();
   }
   else
   {
      ERR(tr("Can not open file for reading"));
   }
}

/** +-=---------------------------------------------------------Mo 4. Feb 15:37:07 2013-----------*
 * @method  CdmClassMethod::SetIcon                          // public                            *
 * @return  void                                             //                                   *
 * @param   QByteArray p_qbArray                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 4. Feb 15:37:07 2013-----------*/
void CdmClassMethod::SetIcon(QByteArray p_qbArray)
{
    SYNCHRONIZED_WRITE;
   m_qbaIcon = p_qbArray;
}

/** +-=---------------------------------------------------------Sa 9. Feb 12:21:07 2013-----------*
 * @method  CdmClassMethod::GetIcon                          // public, const                     *
 * @return  QPixmap                                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 9. Feb 12:21:07 2013-----------*/
QPixmap CdmClassMethod::GetIcon() const
{
    SYNCHRONIZED_READ;
   QPixmap qPixmap;
   qPixmap.loadFromData(m_qbaIcon);
   return qPixmap;
}

/** +-=---------------------------------------------------------Sa 9. Feb 12:21:28 2013-----------*
 * @method  CdmClassMethod::GetIconAsByteArray               // public, const                     *
 * @return  QByteArray                                       //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 9. Feb 12:21:28 2013-----------*/
QByteArray CdmClassMethod::GetIconAsByteArray() const
{
    SYNCHRONIZED_READ;
   return m_qbaIcon;
}


/** +-=---------------------------------------------------------Mo 18. Jun 16:39:49 2012----------*
 * @method  CdmClassMethod::SetAccess                        // public                            *
 * @return  void                                             //                                   *
 * @param   EdmMemberAccess p_eType                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 18. Jun 16:39:49 2012----------*/
void CdmClassMethod::SetAccess(EdmMemberAccess p_eType)
{
    SYNCHRONIZED_WRITE;
   m_eAccess = p_eType;
}

/** +-=---------------------------------------------------------Sa 9. Feb 12:21:35 2013-----------*
 * @method  CdmClassMethod::GetAccess                        // public, const, slots              *
 * @return  EdmMemberAccess                                  //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 9. Feb 12:21:35 2013-----------*/
EdmMemberAccess CdmClassMethod::GetAccess() const
{
    SYNCHRONIZED_READ;
   return m_eAccess;
}

/** +-=---------------------------------------------------------Mo 18. Jun 16:41:19 2012----------*
 * @method  CdmClassMethod::SetMethodType                    // public                            *
 * @return  void                                             //                                   *
 * @param   EdmMethodType p_eType                            //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 18. Jun 16:41:19 2012----------*/
void CdmClassMethod::SetReturnType(EdmValueType p_eType)
{
    SYNCHRONIZED_WRITE;
   m_eReturnType = p_eType;
}

/** +-=---------------------------------------------------------Sa 9. Feb 12:21:44 2013-----------*
 * @method  CdmClassMethod::GetMethodType                    // public, const, slots              *
 * @return  EdmMethodType                                    //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 9. Feb 12:21:44 2013-----------*/
EdmValueType CdmClassMethod::GetReturnType() const
{
    SYNCHRONIZED_READ;
   return m_eReturnType;
}

/** +-=---------------------------------------------------------Do 22. Nov 14:12:49 2012----------*
 * @method  CdmClassMethod::SetParameters                    // public                            *
 * @return  void                                             //                                   *
 * @param   QList<CdmClassMethodParameter> p_qmParameters    //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 22. Nov 14:12:49 2012----------*/
void CdmClassMethod::SetParameters(QList<CdmClassMethodParameter> p_qmParameters)
{
    SYNCHRONIZED_WRITE;
   m_qlParameters = p_qmParameters;
}

/** +-=---------------------------------------------------------Sa 9. Feb 12:21:54 2013-----------*
 * @method  CdmClassMethod::GetParameters                    // public, const, slots              *
 * @return  QList<CdmClassMethodParameter>                   //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 9. Feb 12:21:54 2013-----------*/
QList<CdmClassMethodParameter> CdmClassMethod::GetParameters() const
{
    SYNCHRONIZED_READ;
   return m_qlParameters;
}

/** +-=---------------------------------------------------------Sa 9. Feb 12:22:02 2013-----------*
 * @method  CdmClassMethod::GetParameterCount                // public, const, slots              *
 * @return  int                                              //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 9. Feb 12:22:02 2013-----------*/
int CdmClassMethod::GetParameterCount() const
{
    SYNCHRONIZED_READ;
   return m_qlParameters.count();
}

/** +-=---------------------------------------------------------Sa 9. Feb 12:22:09 2013-----------*
 * @method  CdmClassMethod::HasParameters                    // public, const, slots              *
 * @return  bool                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 9. Feb 12:22:09 2013-----------*/
bool CdmClassMethod::HasParameters() const
{
   return (GetParameterCount() != 0);
}

/** +-=---------------------------------------------------------Mi 20. Jun 15:41:22 2012----------*
 * @method  CdmClassMethod::SetParameters                    // public                            *
 * @return  void                                             //                                   *
 * @param   QString p_qstrParameters                        //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mi 20. Jun 15:41:22 2012----------*/
void CdmClassMethod::SetParameters(QString p_qstrParameters)
{
    SYNCHRONIZED_WRITE;
   if (!p_qstrParameters.isEmpty() && p_qstrParameters != "-")
   {
      QStringList qstrlParameters = p_qstrParameters.split("||");

      for (int iPos = 0; iPos < qstrlParameters.count(); ++iPos)
      {
         QString qstrParameter = qstrlParameters[iPos];
         if (qstrParameter.length() > 0)
         {
            CdmClassMethodParameter cParam;
            QStringList qstrlTemp = qstrParameter.split("|");
            cParam.SetName(qstrlTemp[0]);
            cParam.m_eType = (EdmValueType)qstrlTemp[1].toInt();
            cParam.m_iPos = (EdmValueType)qstrlTemp[2].toInt();

            if (qstrParameter.count() == 4 &&
                (cParam.m_eType == eDmValueContainerRef ||
                 cParam.m_eType == eDmValueObjectRef))
            {
               cParam.m_lReference = qstrlTemp[3].toInt();
            }

            m_qlParameters.append(cParam);
         }
      }
   }
}

/** +-=---------------------------------------------------------Do 22. Nov 16:10:17 2012----------*
 * @method  CdmClassMethod::AddParameter                     // public                            *
 * @return  void                                             //                                   *
 * @param   QString p_qstrName                               //                                   *
 * @param   EdmValue p_eValueType                            //                                   *
 * @param   long p_lClassId = 0                              //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 22. Nov 16:10:17 2012----------*/
void CdmClassMethod::AddParameter(QString p_qstrName, EdmValueType p_eValueType, long p_lClassId)
{
    SYNCHRONIZED_WRITE;
   CdmClassMethodParameter cParam;
   cParam.SetName(p_qstrName);
   cParam.m_eType = p_eValueType;
   cParam.m_lReference = p_lClassId;
   cParam.m_iPos = m_qlParameters.count();
   m_qlParameters.append(cParam);
}

/** +-=---------------------------------------------------------Sa 9. Feb 12:22:33 2013-----------*
 * @method  CdmClassMethod::GetParametersAsString            // public, const                     *
 * @return  QString                                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 9. Feb 12:22:33 2013-----------*/
QString CdmClassMethod::GetParametersAsString() const
{
    SYNCHRONIZED_READ;
   QString qstrRet;

   if (!m_qlParameters.isEmpty())
   {

      for (int iCounter = 0; iCounter < m_qlParameters.count(); ++iCounter)
      {
         CdmClassMethodParameter cParam = m_qlParameters[iCounter];
         qstrRet += cParam.GetName() + "|";
         qstrRet += QString::number(cParam.m_eType) + "|";
         qstrRet += QString::number(cParam.m_iPos);

         if (cParam.m_lReference > 0)
         {
          //   qstrRet +=  "|" + cParam.m_lReference;
         }

         if (iCounter < m_qlParameters.count() - 1)
         {
            qstrRet += "||";
         }
      }
   }


   return qstrRet;
}

/** +-=---------------------------------------------------------Sa 9. Feb 12:22:33 2013-----------*
 * @method  CdmClassMethod::GetParametersAsStringForFunction            // public, const                     *
 * @return  QString                                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 9. Feb 12:22:33 2013-----------*/
QString CdmClassMethod::GetParametersAsStringForFunction() const
{
    SYNCHRONIZED_READ;
   QString qstrRet;

   if (!m_qlParameters.isEmpty())
   {

      for (int iCounter = 0; iCounter < m_qlParameters.count(); ++iCounter)
      {
         CdmClassMethodParameter cParam = m_qlParameters[iCounter];
         qstrRet += cParam.GetName();
         if (iCounter < m_qlParameters.count() - 1)
         {
           qstrRet += ", ";
         }
      }
   }


   return qstrRet;
}

/** +-=---------------------------------------------------------Do 22. Nov 13:40:25 2012----------*
 * @method  CdmClassMethod::DeleteParameter                  // public                            *
 * @return  void                                             //                                   *
 * @param   QString p_qstrName                               //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 22. Nov 13:40:25 2012----------*/
void CdmClassMethod::DeleteParameter(QString p_qstrName)
{
    SYNCHRONIZED_WRITE;
   for (int iCounter = 0; iCounter < m_qlParameters.count(); ++iCounter)
   {
      CdmClassMethodParameter cParam = m_qlParameters[iCounter];

      if (cParam.GetName() == p_qstrName)
      {
         m_qlParameters.removeAt(iCounter);
         break;
      }
   }
}

/** +-=---------------------------------------------------------Do 22. Nov 16:10:43 2012----------*
 * @method  CdmClassMethod::MoveParameterUp                  // public                            *
 * @return  void                                             //                                   *
 * @param   QString p_qstrParam                              //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 22. Nov 16:10:43 2012----------*/
void CdmClassMethod::MoveParameterUp(QString p_qstrParam)
{
    SYNCHRONIZED_WRITE;
   for (int iCounter = 0; iCounter < m_qlParameters.count(); ++iCounter)
   {
      CdmClassMethodParameter cParam = m_qlParameters[iCounter];

      if (cParam.GetName() == p_qstrParam)
      {
         if (iCounter > 0)
         {
            CdmClassMethodParameter cTemp = m_qlParameters[iCounter-1];
            m_qlParameters.removeAt(iCounter-1);
            m_qlParameters.removeAt(iCounter-1);
            cParam.m_iPos = iCounter - 1;
            cTemp.m_iPos = iCounter;
            m_qlParameters.insert(iCounter-1, cParam);
            m_qlParameters.insert(iCounter, cTemp);
            break;
         }
      }
   }
}

/** +-=---------------------------------------------------------Do 22. Nov 16:10:53 2012----------*
 * @method  CdmClassMethod::MoveParameterDown                // public                            *
 * @return  void                                             //                                   *
 * @param   QString p_qstrParam                              //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 22. Nov 16:10:53 2012----------*/
void CdmClassMethod::MoveParameterDown(QString p_qstrParam)
{
    SYNCHRONIZED_WRITE;
   for (int iCounter = 0; iCounter < m_qlParameters.count(); ++iCounter)
   {
      CdmClassMethodParameter cParam = m_qlParameters[iCounter];

      if (cParam.GetName() == p_qstrParam)
      {
         if (iCounter + 1 < m_qlParameters.count())
         {
            CdmClassMethodParameter cTemp = m_qlParameters[iCounter+1];
            m_qlParameters.removeAt(iCounter);
            m_qlParameters.removeAt(iCounter);
            cTemp.m_iPos = iCounter;
            cParam.m_iPos = iCounter + 1;
            m_qlParameters.insert(iCounter, cTemp);
            m_qlParameters.insert(iCounter+1, cParam);
            break;
         }
      }
   }
}
/** +-=---------------------------------------------------------Sa 9. Feb 12:22:46 2013-----------*
 * @method  CdmClassMethod::CheckExecuteAccess               // public, const, slots              *
 * @return  bool                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 9. Feb 12:22:46 2013-----------*/
bool CdmClassMethod::CheckExecuteAccess() const
{
    SYNCHRONIZED_READ;
   return m_cCdmRights.HasCurrentUserWriteAccess();
}

/** +-=---------------------------------------------------------Sa 9. Feb 12:22:56 2013-----------*
 * @method  CdmClassMethod::GetParameterByPos                // public, const                     *
 * @return  CdmClassMethodParameter                          //                                   *
 * @param   int p_iPos                                       //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 9. Feb 12:22:56 2013-----------*/
CdmClassMethodParameter CdmClassMethod::GetParameterByPos(int p_iPos) const
{
    SYNCHRONIZED_READ;
   CdmClassMethodParameter cParam;

   if (p_iPos < m_qlParameters.count())
   {
      cParam = m_qlParameters[p_iPos];
   }
   else
   {
      ERR(tr("Zuviele Parameter für Funktionsaufruf Funktion: ") + GetMethodName());
   }

   return cParam;
}

/** +-=---------------------------------------------------------Mo 19. Nov 18:38:12 2012----------*
 * @method  CdmClassMethod::GetRights                        // public, slots                     *
 * @return  CdmRights&                                       //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 19. Nov 18:38:12 2012----------*/
CdmRights& CdmClassMethod::GetRights()
{
    SYNCHRONIZED_READ;
   return m_cCdmRights;
}

/** +-=---------------------------------------------------------Sa 9. Feb 12:23:08 2013-----------*
 * @method  CdmClassMethod::GetCallInterface                 // public, const, slots              *
 * @return  QString                                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 9. Feb 12:23:08 2013-----------*/
QString CdmClassMethod::GetCallInterface() const
{
    SYNCHRONIZED_READ;
   QString qstrRet = m_qstrMethodName + "(";
   bool bFirst = true;

   for (int iCounter = 0; iCounter < m_qlParameters.count(); ++iCounter)
   {
      CdmClassMethodParameter cParam = m_qlParameters[iCounter];
      QString qstrKey = cParam.GetName();
      EdmValueType eDmValue = cParam.m_eType;

      if (!bFirst)
      {
         qstrRet += ", ";
      }
      else
      {
         bFirst = false;
      }

      qstrRet += CdmMember::GetValueTypeAsString(eDmValue) + " ";
      qstrRet += qstrKey;
   }

   qstrRet += ")";
   return qstrRet;
}

/** +-=---------------------------------------------------------Sa 9. Feb 12:23:16 2013-----------*
 * @method  CdmClassMethod::GetComment                       // public, const, slots              *
 * @return  QString                                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 9. Feb 12:23:16 2013-----------*/
QString CdmClassMethod::GetComment() const
{
    SYNCHRONIZED_READ;
   return m_qstrComment;
}

/** +-=---------------------------------------------------------Do 27. Sep 14:01:58 2012----------*
 * @method  CdmClassMethod::SetComment                       // public                            *
 * @return  void                                             //                                   *
 * @param   QString p_qstrComment                            //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 27. Sep 14:01:58 2012----------*/
void CdmClassMethod::SetComment(QString p_qstrComment)
{
    SYNCHRONIZED_WRITE;
   m_qstrComment = p_qstrComment;
}

/** +-=---------------------------------------------------------Sa 9. Feb 12:23:37 2013-----------*
 * @method  CdmClassMethod::IsStatic                         // public, const, slots              *
 * @return  bool                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 9. Feb 12:23:37 2013-----------*/
bool CdmClassMethod::IsStatic() const
{
   return m_bStatic.load();
}

/** +-=---------------------------------------------------------Mo 1. Okt 09:26:32 2012-----------*
 * @method  CdmClassMethod::SetStatic                        // public                            *
 * @return  void                                             //                                   *
 * @param   bool p_bStatic                                   //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 1. Okt 09:26:32 2012-----------*/
void CdmClassMethod::SetStatic(bool p_bStatic)
{
   m_bStatic = p_bStatic;
}

/** +-=---------------------------------------------------------Sa 9. Feb 12:23:47 2013-----------*
 * @method  CdmClassMethod::GetVariant                       // public, const, virtual            *
 * @return  QVariant                                         //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 9. Feb 12:23:47 2013-----------*/
QVariant CdmClassMethod::GetVariant() const
{
    SYNCHRONIZED_READ;
   QVariantMap qvHash;

   qvHash.insert(WMS_RIGHTS, m_cCdmRights.GetVariant());
   qvHash.insert(WMS_NAME, m_qstrMethodName);
   qvHash.insert(WMS_CODE, GetSourceCodeBase64());
   qvHash.insert(WMS_TYPE, m_eReturnType);
   qvHash.insert(WMS_ACCESS, m_eAccess);
   qvHash.insert(WMS_VERSION, m_iVersion.load());
   qvHash.insert(WMS_COMMENT, m_qstrComment);
   qvHash.insert(WMS_CAPTION, m_qstrCaption);
   qvHash.insert(WMS_STATIC, m_bStatic.load());
   QString qstrIcon(m_qbaIcon.toBase64());
   qvHash.insert(WMS_ICON, qstrIcon);

   QVariantMap qvParameters;

   for (int iCounter = 0; iCounter < m_qlParameters.count(); ++iCounter)
   {
      QVariantMap qvParameter;
      CdmClassMethodParameter cParam = m_qlParameters[iCounter];
      qvParameter.insert(WMS_TYPE, cParam.m_eType);
      qvParameter.insert(WMS_POS, cParam.m_iPos);
      qvParameter.insert(WMS_REFERENCE, (int)cParam.m_lReference);
      qvParameter.insert(WMS_NAME, cParam.GetName());
      qvParameters.insert(cParam.GetName(), qvParameter);
   }

   qvHash.insert(WMS_PARAMETERS, qvParameters);
   return qvHash;
}

QString CdmClassMethod::GenerateScriptCode()
{
    SYNCHRONIZED_READ;
   QString qstrParameters;

   for (int iCounter = 0; iCounter < m_qlParameters.count(); ++iCounter)
   {
      qstrParameters += m_qlParameters[iCounter].GetName();

      if (iCounter < m_qlParameters.count() -1)
      {
         qstrParameters += ",";
      }
   }

   QString qstrCode = "function " + GetMethodName() + "(" + qstrParameters + ")\n";
   qstrCode += "{\n";
   qstrCode += GetSourceCode() + "\n";
   qstrCode += "}\n";


   return qstrCode;

}

bool CdmClassMethod::LockClassMethod()
{
   SYNCHRONIZED_WRITE;
   bool bRet = false;

   CdmDataProvider* pManager = CdmSessionManager::GetDataProvider();

   if (CHKPTR(pManager))
   {
      IdmDataAccess* pDataAccess = pManager->GetDataAccess();

      if (CHKPTR(pDataAccess))
      {
         bRet = pDataAccess->LockClassMethod(GetId());
      }
   }

   return bRet;
}

bool CdmClassMethod::UnlockClassMethod()
{
   SYNCHRONIZED_WRITE;
   bool bRet = false;

   CdmDataProvider* pManager = CdmSessionManager::GetDataProvider();

   if (CHKPTR(pManager))
   {
      IdmDataAccess* pDataAccess = pManager->GetDataAccess();

      if (CHKPTR(pDataAccess))
      {
         bRet = pDataAccess->UnlockClassMethod(GetId());
      }
   }

   return bRet;
}

QString CdmClassMethod::GetUri() const
{
    SYNCHRONIZED_READ;
    QString qstrUri;
    if (CHKPTR(m_rpCdmClass))
    {
        qstrUri = CdmLocatedElement::CreateUri(WMS_URI_METHOD,
                                               m_rpCdmClass->GetFullQualifiedName(),
                                               GetMethodName());
    }

    return qstrUri;
}

QString CdmClassMethod::GetUriInternal() const
{
    return CdmLocatedElement::CreateUriPath(WMS_URI_METHOD,
                                            m_rpCdmClass->GetFullQualifiedName(),
                                            GetMethodName(), "");
}

bool CdmClassMethod::IsMethod() const
{
    return true;
}

QString CdmClassMethod::GetAccessModeAsString() const
{
    switch (m_eAccess)
    {
    case eDmMemberAccessPrivate:
        return WMS_ACCESS_PRIVATE;
        break;
    case eDmMemberAccessProtected:
        return WMS_ACCESS_PROTECTED;
        break;
    case eDmMemberAccessPublic:
        return WMS_ACCESS_PUBLIC;
        break;
    default:
        return "Unknown";
    }


}

// CdmClassMethodParameter CdmClassMethodParameter CdmClassMethodParameter CdmClassMethodParameter
// CdmClassMethodParameter CdmClassMethodParameter CdmClassMethodParameter CdmClassMethodParameter
// CdmClassMethodParameter CdmClassMethodParameter CdmClassMethodParameter CdmClassMethodParameter

/** +-=---------------------------------------------------------Do 22. Nov 14:10:06 2012----------*
 * @method  CdmClassMethodParameter::CdmClassMethodParameter // public                            *
 * @return                                                   //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 22. Nov 14:10:06 2012----------*/
CdmClassMethodParameter::CdmClassMethodParameter()
: m_iPos(0),
  m_eType(eDmValueNone),
  m_lReference(0),
  m_qstrName("")
{
   // does nothing
}

/** +-=---------------------------------------------------------Fr 23. Nov 11:24:07 2012----------*
 * @method  CdmClassMethodParameter::SetName                 // public                            *
 * @return  void                                             //                                   *
 * @param   QString p_qstrName                               //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 23. Nov 11:24:07 2012----------*/
void CdmClassMethodParameter::SetName(QString p_qstrName)
{
   m_qstrName = p_qstrName;
}

/** +-=---------------------------------------------------------Sa 9. Feb 12:24:01 2013-----------*
 * @method  CdmClassMethodParameter::GetName                 // public, const                     *
 * @return  QString                                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Sa 9. Feb 12:24:01 2013-----------*/
QString CdmClassMethodParameter::GetName() const
{
   return m_qstrName;
}
