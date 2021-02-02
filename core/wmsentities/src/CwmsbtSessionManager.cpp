

// System and QT Includes
#include <QFile>
#include <QTextStream>
#include <QFileInfo>

// own Includes
#include "CwmsbtSessionManager.h"

const float  PRECISION_FLOAT  = 1000.0;
const double PRECISION_DOUBLE = 1000000.0;

/** +-=---------------------------------------------------------Mon Aug 26 21:33:56 2002----------*
 * @method  CwmsbtSessionManager::CwmsbtSessionManager             // public                            *
 * @return                                                   //                                   *
 * @comment                                                                                       *
 *---------------------------------------------------------------Mon Aug 26 21:33:56 2002---------*/
CwmsbtSessionManager::CwmsbtSessionManager(  )
{
	m_sFile = "";
}


/** +-=---------------------------------------------------------Mon Aug 26 21:34:09 2002----------*
 * @method  CwmsbtSessionManager::~CwmsbtSessionManager            // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CwmsbtSessionManager                                             *
 *                                                                                                *
 *---------------------------------------------------------------Mon Aug 26 21:34:09 2002---------*/
CwmsbtSessionManager::~CwmsbtSessionManager(  )
{
	m_dictKey.clear();
}


/** +-=---------------------------------------------------------Sat Oct 26 23:33:22 2002----------*
 * @method  CwmsbtSessionManager::Load                          // public                            *
 * @return  bool                                             //                                   *
 * @param   QString sFile                                    //                                   *
 * @comment Loads the Sessionfile.                                                                *
 *---------------------------------------------------------------Sat Oct 26 23:33:22 2002---------*/
bool CwmsbtSessionManager::Load(  QString sFile )
{
	KeyItem pItem;
        QFileInfo fileInfo;
	QTextStream stream;
        m_sFile = sFile;
        QFile file(sFile);
	QString sLine,sKey,sValue,sContent;
	int n1,n2;

	fileInfo.setFile(sFile);
	if (!fileInfo.exists()) return false;

	if (!file.open(QIODevice::ReadOnly|QIODevice::Text)) return false;

	m_dictKey.clear();
	sKey = "";

	stream.setDevice(&file);
	while (!stream.atEnd())
	{
		sLine = stream.readLine();
		if (sLine.isEmpty()) continue;

		n1 = sLine.indexOf('[');
		if (n1!=-1)
		{
			n2 = sLine.indexOf(']');
			if (n2==-1) continue;

			sKey = sLine.mid(n1+1,n2-n1-1);
			if (sKey.isEmpty()) continue;

			if (m_dictKey.contains(sKey)) continue;

			KeyItem pItem;
			m_dictKey[sKey] = pItem;
		}
		else
		{
			if (sKey.isEmpty()) continue;

			n1 = sLine.indexOf('=');
			if (n1==-1) continue;

			sValue = sLine.left(n1);
			sContent = sLine.right(sLine.length()-n1-1);

         if (m_dictKey.contains(sKey))
         {
			   pItem = m_dictKey[sKey];
			   pItem.append(StringPair(sValue,sContent));
         }
		}
	}

	file.close();

	return true;
}

/** +-=---------------------------------------------------------Mon Aug 26 21:35:55 2002----------*
 * @method  CwmsbtSessionManager::Save                          // public                            *
 * @return  bool                                             //                                   *
 * @comment saves the Sessionfile.                                                                *
 *---------------------------------------------------------------Mon Aug 26 21:35:55 2002---------*/
bool CwmsbtSessionManager::Save(  )
{
	if (m_sFile.isEmpty()) 
   {
      return false;
   }

	return SaveAs(m_sFile);
}

/** +-=---------------------------------------------------------Mon Aug 26 21:36:54 2002----------*
 * @method  CwmsbtSessionManager::SaveAs                        // public                            *
 * @return  bool                                             //                                   *
 * @param   QString sFile                                    //                                   *
 * @comment Save the Sessionfile under an other filename.                                         *
 *---------------------------------------------------------------Mon Aug 26 21:36:54 2002---------*/
bool CwmsbtSessionManager::SaveAs(  QString sFile )
{
	KeyItem pItem;
	StringPair sPair;
   QHash<QString, KeyItem>::iterator it = m_dictKey.begin();
   QHash<QString, KeyItem>::iterator itEnd = m_dictKey.end();

   QFile file(sFile);
	QTextStream stream;

	if (!file.open(QIODevice::WriteOnly|QIODevice::Text)) return false;

	stream.setDevice(&file);

	for (;it != itEnd; ++it)
	{
		stream << '[' << it.key() << ']' << endl;

		pItem = it.value();

      for (int iPos = 0; iPos < pItem.count(); ++iPos)
      {
         sPair = pItem[iPos];
         stream << sPair.first << '=' << sPair.second << endl;
      }

		stream << endl;
	}

	file.close();

	return true;
}

/** +-=---------------------------------------------------------Fri Nov 1 09:43:06 2002-----------*
 * @method  CwmsbtSessionManager::AddKey                        // public                            *
 * @return  void                                             //                                   *
 * @param   QString sKey                                     //                                   *
 * @comment Adds a Key to the the session.                                                        *
 *---------------------------------------------------------------Fri Nov 1 09:43:06 2002----------*/
void CwmsbtSessionManager::AddKey(  QString sKey )
{
	if (!m_dictKey.contains(sKey))
	{
		KeyItem pItem;
		m_dictKey.insert(sKey,pItem);
	}
}

/** +-=---------------------------------------------------------Mon Aug 26 21:38:15 2002----------*
 * @method  CwmsbtSessionManager::IsKey                         // public                            *
 * @return  bool                                             //                                   *
 * @param   QString sKey                                     //                                   *
 * @comment returns if this is a key or not.                                                      *
 *---------------------------------------------------------------Mon Aug 26 21:38:15 2002---------*/
bool CwmsbtSessionManager::IsKey(  QString sKey )
{
	return m_dictKey.contains(sKey);
}

/** +-=---------------------------------------------------------Sa 21. Jun 11:58:22 2003----------*
 * @method  CwmsbtSessionManager::SetString                     // public                            *
 * @return  bool                                             //                                   *
 * @param   QString sKey                                     //                                   *
 * @param   QString sValue                                   //                                   *
 * @param   QString sContent                                 //                                   *
 * @comment                                                                                       *
 *----------------last changed: Wolfgang Graßhof----------------Sa 21. Jun 11:58:22 2003----------*/
bool CwmsbtSessionManager::SetString(  QString sKey, QString sValue, QString sContent )
{
	return SetContent(sKey,sValue,sContent);
}


/** +-=---------------------------------------------------------Mon Aug 26 21:41:19 2002----------*
 * @method  CwmsbtSessionManager::SetInteger                    // public                            *
 * @return  bool                                             //                                   *
 * @param   QString sKey                                     //                                   *
 * @param   QString sValue                                   //                                   *
 * @param   int nContent                                     //                                   *
 * @comment Sets the Integer value to session.                                                    *
 *---------------------------------------------------------------Mon Aug 26 21:41:19 2002---------*/
bool CwmsbtSessionManager::SetInteger(  QString sKey, QString sValue, int nContent )
{
	return SetContent(sKey,sValue,QString::number(nContent));	
}

/** +-=---------------------------------------------------------Mon Aug 26 21:46:40 2002----------*
 * @method  CwmsbtSessionManager::SetFloat                      // public                            *
 * @return  bool                                             //                                   *
 * @param   QString sKey                                     //                                   *
 * @param   QString sValue                                   //                                   *
 * @param   float fContent                                   //                                   *
 * @comment                                                                                       *
 *---------------------------------------------------------------Mon Aug 26 21:46:40 2002---------*/
bool CwmsbtSessionManager::SetFloat(  QString sKey, QString sValue, float fContent )
{
	int nContent = static_cast<int>(PRECISION_FLOAT * fContent);
	return SetContent(sKey,sValue,QString::number(nContent));
}

/** +-=---------------------------------------------------------Mon Aug 26 21:47:34 2002----------*
 * @method  CwmsbtSessionManager::SetContent                    // private                           *
 * @return  bool                                             //                                   *
 * @param   QString sKey                                     //                                   *
 * @param   QString sValue                                   //                                   *
 * @param   QString sContent                                 //                                   *
 * @comment                                                                                       *
 *---------------------------------------------------------------Mon Aug 26 21:47:34 2002---------*/
bool CwmsbtSessionManager::SetContent(QString sKey, QString sValue, QString sContent)
{
   bool bRet = false;
	KeyItem pItem;
	StringPair pPair;
	
	if (m_dictKey.contains(sKey))
   {
      pItem = m_dictKey[sKey];
      

      for (int iPos = 0; iPos < pItem.count(); ++iPos)
      {
	      pPair = pItem[iPos];

	      if (pPair.first == sValue)
		   {
			   pPair.second = sContent;
            bRet = true;
			   break;
		   }
	   }

	   if (!bRet)
	   {
		   pItem.append(StringPair(sValue,sContent));
	   }

      m_dictKey.insert(sKey, pItem);
   }

	return true;
}
/** +-=---------------------------------------------------------Mon Aug 26 21:52:19 2002----------*
 * @method  CwmsbtSessionManager::GetString                     // public                            *
 * @return  QString                                          //                                   *
 * @param   QString sKey                                     //                                   *
 * @param   QString sValue                                   //                                   *
 * @param   QString sReturn                                  //                                   *
 * @comment returns the String of the Key and Value.                                              *
 *---------------------------------------------------------------Mon Aug 26 21:52:19 2002---------*/
QString CwmsbtSessionManager::GetString(  QString sKey, QString sValue, QString sReturn )
{
	QString sContent = sReturn;
	GetContent(sKey, sValue, sContent);
   return sContent;
}

/** +-=---------------------------------------------------------Mon Aug 26 21:53:08 2002----------*
 * @method  CwmsbtSessionManager::GetInteger                    // public                            *
 * @return  int                                              //                                   *
 * @param   QString sKey                                     //                                   *
 * @param   QString sValue                                   //                                   *
 * @param   int nReturn                                      //                                   *
 * @comment returns the Integer at Key and Value.                                                 *
 *---------------------------------------------------------------Mon Aug 26 21:53:08 2002---------*/
int CwmsbtSessionManager::GetInteger(  QString sKey, QString sValue, int nReturn )
{
   int iRet = nReturn;
	QString sContent;

	if (GetContent(sKey, sValue, sContent))
   {
      iRet = sContent.toInt();
   }

	return iRet;
}


/** +-=---------------------------------------------------------Mon Aug 26 21:57:54 2002----------*
 * @method  CwmsbtSessionManager::GetFloat                      // public                            *
 * @return  float                                            //                                   *
 * @param   QString sKey                                     //                                   *
 * @param   QString sValue                                   //                                   *
 * @param   float fReturn                                    //                                   *
 * @comment                                                                                       *
 *---------------------------------------------------------------Mon Aug 26 21:57:54 2002---------*/
float CwmsbtSessionManager::GetFloat(QString sKey, QString sValue, float fReturn)
{
   float fRet = fReturn;
	QString sContent;

	if (GetContent(sKey, sValue, sContent))
   {
      fRet = static_cast<float>(sContent.toFloat()/PRECISION_FLOAT);
   }

	return fRet;
}

/** +-=---------------------------------------------------------Mon Aug 26 21:59:04 2002----------*
 * @method  CwmsbtSessionManager::GetContent                    // private                           *
 * @return  bool                                             //                                   *
 * @param   QString sKey                                     //                                   *
 * @param   QString sValue                                   //                                   *
 * @param   QString& sContent                                //                                   *
 * @comment                                                                                       *
 *---------------------------------------------------------------Mon Aug 26 21:59:04 2002---------*/
bool CwmsbtSessionManager::GetContent(  QString sKey, QString sValue, QString& sContent )
{
   bool bRet = false;
	KeyItem pItem;
	StringPair pPair;
	
	pItem = m_dictKey[sKey];

   for (int iPos = 0; iPos < pItem.count(); ++iPos)
   {
      pPair = pItem[iPos];

      if (pPair.first == sValue)
      {
         sContent = pPair.second;
         bRet = true;
         break;
      }
   }
  
   return bRet;
}
