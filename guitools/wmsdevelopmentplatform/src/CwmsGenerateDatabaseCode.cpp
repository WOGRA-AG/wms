/******************************************************************************
 ** WOGRA technologies GmbH & Co. KG Modul Information
 ** Modulename: CwmsGenerateDatabaseCode.cpp
 ** Started Implementation: 2011/11/10
 ** Description:
 **
 ** This class generates the interface for the complete database
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co. KG All rights reserved
 *****************************************************************************/

// System and QT Includes


// WMS Includes
#include "CdmClassManager.h"
#include "CdmClass.h"
#include "CdmLogging.h"

// own Includes
#include "CwmsCodeGeneratorC.h"
#include "CwmsGenerateDatabaseCode.h"


/** +-=---------------------------------------------------------Fr 11. Nov 18:16:09 2011----------*
 * @method  CwmsGenerateDatabaseCode::CwmsGenerateDatabaseCode // public                          *
 * @return                                                   //                                   *
 * @param   CdmClassManager* p_pCdmClassManager              //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Fr 11. Nov 18:16:09 2011----------*/
CwmsGenerateDatabaseCode::CwmsGenerateDatabaseCode(CdmClassManager* p_pCdmClassManager)
   : m_rpCdmClassManager(p_pCdmClassManager)
{
}

/** +-=---------------------------------------------------------Fr 11. Nov 18:16:24 2011----------*
 * @method  CwmsGenerateDatabaseCode::~CwmsGenerateDatabaseCode // public, virtual                *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CwmsGenerateDatabaseCode                                      *
 *----------------last changed: --------------------------------Fr 11. Nov 18:16:24 2011----------*/
CwmsGenerateDatabaseCode::~CwmsGenerateDatabaseCode()
{
}

/** +-=---------------------------------------------------------Do 10. Nov 19:03:59 2011----------*
 * @method  CwmsGenerateDatabaseCode::SetClassPrefix         // public                            *
 * @return  void                                             //                                   *
 * @param   QString p_qstrPrefix                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 10. Nov 19:03:59 2011----------*/
void CwmsGenerateDatabaseCode::SetClassPrefix(QString p_qstrPrefix)
{
   m_qstrClassPrefix = p_qstrPrefix;
}

/** +-=---------------------------------------------------------Do 10. Nov 19:06:05 2011----------*
 * @method  CwmsGenerateDatabaseCode::GenerateClassName      // private                           *
 * @return  QString                                          //                                   *
 * @param   QString p_qstrClass                              //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 10. Nov 19:06:05 2011----------*/
QString CwmsGenerateDatabaseCode::GenerateClassName(QString p_qstrClass)
{
   QString qstrRet = m_qstrClassPrefix;
   qstrRet += p_qstrClass;
   qstrRet = qstrRet.remove("_");
   qstrRet = qstrRet.remove(" ");
   return qstrRet;
}


/** +-=---------------------------------------------------------Do 10. Nov 19:03:30 2011----------*
 * @method  CwmsGenerateDatabaseCode::GenerateDatabaseCode   // public                            *
 * @return  void                                             //                                   *
 * @param   QString p_qstrDirectory                          //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 10. Nov 19:03:30 2011----------*/
void CwmsGenerateDatabaseCode::GenerateDatabaseCode(QString p_qstrDirectory)
{
   if (CHKPTR(m_rpCdmClassManager))
   {
      m_qstrDirectory = p_qstrDirectory;
      QLinkedList<CdmClass*> qllClasses;
      m_rpCdmClassManager->GetClassList(qllClasses);
      QLinkedList<CdmClass*>::iterator qllIt = qllClasses.begin();
      QLinkedList<CdmClass*>::iterator qllItEnd = qllClasses.end();

      for (; qllIt != qllItEnd; ++qllIt)
      {
         CdmClass* pCdmClass = *qllIt;

         if (CHKPTR(pCdmClass))
         {
            QMap<long, long> qmBaseClasses = pCdmClass->GetBaseClasses();
            
            if (AreAllBaseClassesGenerated(qmBaseClasses.keys()))
            {
               GenerateClassCode(pCdmClass);
            }
            else
            {
               m_qllNotGeneratedClasses.append(pCdmClass);
            }
         }
      }

      GenerateNotCreatedClasses();
   }
}


/** +-=---------------------------------------------------------Do 10. Nov 19:17:36 2011----------*
 * @method  CwmsGenerateDatabaseCode::AreAllBaseClassesGenerated // private                       *
 * @return  bool                                             //                                   *
 * @param   QList<long> p_qllBaseClasses                     //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 10. Nov 19:17:36 2011----------*/
bool CwmsGenerateDatabaseCode::AreAllBaseClassesGenerated(QList<long> p_qllBaseClasses)
{
   bool bRet = true;

   for (int iPos = 0; iPos < p_qllBaseClasses.count(); ++iPos)
   {
      if (!m_qvGeneratedClasses.contains(p_qllBaseClasses[iPos]))
      {
         bRet = false;
         break;
      }
   }

   return bRet;
}

/** +-=---------------------------------------------------------Do 10. Nov 19:26:05 2011----------*
 * @method  CwmsGenerateDatabaseCode::GenerateClassCode      // private                           *
 * @return  void                                             //                                   *
 * @param   CdmClass* p_pCdmClass                            //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 10. Nov 19:26:05 2011----------*/
void CwmsGenerateDatabaseCode::GenerateClassCode(CdmClass* p_pCdmClass)
{
   if (CHKPTR(p_pCdmClass))
   {
      QString qstrKeyname = p_pCdmClass->GetKeyname();
      QString qstrClassName = GenerateClassName(qstrKeyname);
      CwmsCodeGeneratorC cCwmsCodeGenerator(p_pCdmClass, qstrClassName, m_qstrDirectory);
      AddBaseClassData(p_pCdmClass, cCwmsCodeGenerator);
      cCwmsCodeGenerator.GenerateCode();
      m_qmClassNames.insert(p_pCdmClass->GetId(), qstrClassName);
      m_qmFilenames.insert(p_pCdmClass->GetId(), qstrClassName);

      if (m_qllNotGeneratedClasses.contains(p_pCdmClass))
      {
         m_qllNotGeneratedClasses.removeAll(p_pCdmClass);
      }
   }
}

/** +-=---------------------------------------------------------Do 10. Nov 19:30:50 2011----------*
 * @method  CwmsGenerateDatabaseCode::AddBaseClassData       // private                           *
 * @return  void                                             //                                   *
 * @param   CdmClass* p_pCdmClass                            //                                   *
 * @param   CwmsCodeGeneratorC& p_rCwmsGenerator             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 10. Nov 19:30:50 2011----------*/
void CwmsGenerateDatabaseCode::AddBaseClassData(CdmClass* p_pCdmClass,
                                                CwmsCodeGeneratorC& p_rCwmsGenerator)
{
   QMap<long, long> qmBaseClasses = p_pCdmClass->GetBaseClasses();
   QMap<long, long>::iterator qmIt = qmBaseClasses.begin();
   QMap<long, long>::iterator qmItEnd = qmBaseClasses.end();

   for (; qmIt != qmItEnd; ++qmIt)
   {
      if (m_qmClassNames.contains(qmIt.key()) && m_qmFilenames.contains(qmIt.key()))
      {
         p_rCwmsGenerator.AddBaseClassData(m_qmClassNames[qmIt.key()], m_qmFilenames[qmIt.key()]);
      }
   }
}

/** +-=---------------------------------------------------------Do 10. Nov 19:38:55 2011----------*
 * @method  CwmsGenerateDatabaseCode::GenerateNotCreatedClasses // private                        *
 * @return  void                                             //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Do 10. Nov 19:38:55 2011----------*/
void CwmsGenerateDatabaseCode::GenerateNotCreatedClasses()
{
   QLinkedList<CdmClass*>::iterator qllIt = m_qllNotGeneratedClasses.begin();

   while (qllIt != m_qllNotGeneratedClasses.end())
   {
      CdmClass* pCdmClass = *qllIt;

      if (CHKPTR(pCdmClass))
      {
         QMap<long, long> qmBaseClasses = pCdmClass->GetBaseClasses();

         if (AreAllBaseClassesGenerated(qmBaseClasses.keys()))
         {
            GenerateClassCode(pCdmClass);
            qllIt = m_qllNotGeneratedClasses.begin();
         }
         else
         {
            ++qllIt;
         }  
      }
   }
}