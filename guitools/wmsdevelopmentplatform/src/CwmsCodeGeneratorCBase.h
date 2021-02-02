/******************************************************************************
 ** WOGRA technologies Gmbh & Co KG Modul Information
 ** Modulename: CwmsCodeGeneratorCBase.h
 ** Started Implementation: 2011/11/21
 ** Description:
 ** 
 ** The base class for c++ code generation
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co KG All rights reserved
 *****************************************************************************/ 

#ifndef CWMSCODEGENERATORCBASE_H
#define CWMSCODEGENERATORCBASE_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes
#include <QString>
#include <QStringList>
#include <QMap>

// Own Includes
#include "CwmsCodeGeneratorBase.h"
// Forwards


// TypeDefs


/* 
 * This class implements the base class for c++ code generation
 */
class CwmsCodeGeneratorCBase : public CwmsCodeGeneratorBase
{
   protected:
      QString m_qstrSource;
      QString m_qstrHeader;
      QString m_qstrFilename;
      QString m_qstrClassName;
      QString m_qstrDllExportDeclaration;
      QStringList m_qstrlSourceIncludes;
      QStringList m_qstrlHeaderIncludes;
      QStringList m_qstrlForwards;
      QMap<QString, QString> m_qmBaseClasses; // <ClassName, Filename>

   private:
   /** +-=---------------------------------------------------------Mo 21. Nov 17:03:48 2011-------*
    * @method  CwmsCodeGeneratorCBase::SaveSourceFile        // private                           *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 21. Nov 17:03:48 2011----------*/
    void SaveSourceFile();

   protected:
   /** +-=---------------------------------------------------------Di 22. Nov 18:54:27 2011-------*
    * @method  CwmsCodeGeneratorCBase::SaveHeaderFile        // protected                         *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 22. Nov 18:54:27 2011----------*/
    void SaveHeaderFile();


   protected:
   /** +-=---------------------------------------------------------Mo 21. Nov 17:03:32 2011-------*
    * @method  CwmsCodeGeneratorCBase::SaveFiles             // protected                         *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 21. Nov 17:03:32 2011----------*/
    void SaveFiles();

   public:
   /** +-=---------------------------------------------------------Di 22. Nov 19:06:26 2011-------*
    * @method  CwmsCodeGeneratorCBase::CwmsCodeGeneratorCBase // public                           *
    * @return                                                //                                   *
    * @param   QString p_qstrFilename                        //                                   *
    * @param   QString p_qstrClassName                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 22. Nov 19:06:26 2011----------*/
    CwmsCodeGeneratorCBase( QString p_qstrFilename, QString p_qstrClassName);

   public:
   /** +-=---------------------------------------------------------Mo 21. Nov 17:03:14 2011-------*
    * @method  CwmsCodeGeneratorCBase::~CwmsCodeGeneratorCBase // public, virtual                 *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CwmsCodeGeneratorCBase                                     *
    *----------------last changed: -----------------------------Mo 21. Nov 17:03:14 2011----------*/
    virtual ~CwmsCodeGeneratorCBase( );

   protected:
   /** +-=---------------------------------------------------------Di 22. Nov 18:54:51 2011-------*
    * @method  CwmsCodeGeneratorCBase::GenerateMethodHeadSource // protected                      *
    * @return  QString                                       //                                   *
    * @param   QString p_qstrReturnType                      //                                   *
    * @param   QString p_qstrClassName                       //                                   *
    * @param   QString p_qstrMethodName                      //                                   *
    * @param   QString p_qstrParameters                      //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 22. Nov 18:54:51 2011----------*/
    QString GenerateMethodHeadSource(QString p_qstrReturnType,
                                     QString p_qstrClassName,
                                     QString p_qstrMethodName,
                                     QString p_qstrParameters);

   protected:
   /** +-=---------------------------------------------------------Di 22. Nov 18:54:43 2011-------*
    * @method  CwmsCodeGeneratorCBase::GenerateMethodHeadHeader // protected                      *
    * @return  QString                                       //                                   *
    * @param   QString p_qstrAccessType                      //                                   *
    * @param   QString p_qstrReturnType                      //                                   *
    * @param   QString p_qstrMethodName                      //                                   *
    * @param   QString p_qstrParameters                      //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 22. Nov 18:54:43 2011----------*/
    QString GenerateMethodHeadHeader(QString p_qstrAccessType,
                                     QString p_qstrReturnType,
                                     QString p_qstrMethodName,
                                     QString p_qstrParameters);

   protected:
   /** +-=---------------------------------------------------------Di 22. Nov 19:20:44 2011-------*
    * @method  CwmsCodeGeneratorCBase::GenerateConstructorSourceHead // protected                 *
    * @return  QString                                       //                                   *
    * @param   QString p_qstrClassName                       //                                   *
    * @param   QString p_qstrParameter                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 22. Nov 19:20:44 2011----------*/
    QString GenerateConstructorSourceHead(QString p_qstrClassName, QString p_qstrParameter);

   protected:
   /** +-=---------------------------------------------------------Di 22. Nov 18:55:12 2011-------*
    * @method  CwmsCodeGeneratorCBase::GenerateConstructorHeader // protected                     *
    * @return  QString                                       //                                   *
    * @param   QString p_qstrClassName                       //                                   *
    * @param   QString p_qstrParameter                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 22. Nov 18:55:12 2011----------*/
    QString GenerateConstructorHeader(QString p_qstrClassName, QString p_qstrParameter);

   protected:
   /** +-=---------------------------------------------------------Di 22. Nov 18:55:00 2011-------*
    * @method  CwmsCodeGeneratorCBase::GenerateDestructorHeader // protected                      *
    * @return  QString                                       //                                   *
    * @param   QString p_qstrClassName                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 22. Nov 18:55:00 2011----------*/
    QString GenerateDestructorHeader(QString p_qstrClassName);

   protected:
   /** +-=---------------------------------------------------------Di 22. Nov 18:55:05 2011-------*
    * @method  CwmsCodeGeneratorCBase::GenerateDestructorSource // protected                      *
    * @return  QString                                       //                                   *
    * @param   QString p_qstrClassName                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 22. Nov 18:55:05 2011----------*/
    QString GenerateDestructorSource(QString p_qstrClassName);


   protected:
   /** +-=---------------------------------------------------------Di 22. Nov 19:05:56 2011-------*
    * @method  CwmsCodeGeneratorCBase::CloseClass            // protected                         *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 22. Nov 19:05:56 2011----------*/
    void CloseClass();

   protected:
   /** +-=---------------------------------------------------------Di 22. Nov 19:06:07 2011-------*
    * @method  CwmsCodeGeneratorCBase::OpenClass             // protected                         *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 22. Nov 19:06:07 2011----------*/
    void OpenClass();

   protected:
   /** +-=---------------------------------------------------------Di 22. Nov 19:17:29 2011-------*
    * @method  CwmsCodeGeneratorCBase::GenerateSourceHeader  // protected                         *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 22. Nov 19:17:29 2011----------*/
    void GenerateSourceHeader();

   protected:
   /** +-=---------------------------------------------------------Di 22. Nov 19:22:55 2011-------*
    * @method  CwmsCodeGeneratorCBase::AddMemberVariable     // protected                         *
    * @return  void                                          //                                   *
    * @param   QString p_qstrType                            //                                   *
    * @param   QString p_qstrName                            //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 22. Nov 19:22:55 2011----------*/
    void AddMemberVariable(QString p_qstrType, QString p_qstrName);

   protected:
   /** +-=---------------------------------------------------------Mi 23. Nov 11:40:10 2011-------*
    * @method  CwmsCodeGeneratorCBase::AddSourceInclude      // protected                         *
    * @return  void                                          //                                   *
    * @param   QString p_qstrInclude                         //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 23. Nov 11:40:10 2011----------*/
    void AddSourceInclude(QString p_qstrInclude);

   protected:
   /** +-=---------------------------------------------------------Mi 23. Nov 11:40:21 2011-------*
    * @method  CwmsCodeGeneratorCBase::AddForward            // protected                         *
    * @return  void                                          //                                   *
    * @param   QString p_qstrForward                         //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 23. Nov 11:40:21 2011----------*/
    void AddForward(QString p_qstrForward);

   protected:
   /** +-=---------------------------------------------------------Mi 23. Nov 11:40:15 2011-------*
    * @method  CwmsCodeGeneratorCBase::AddHeaderInclude      // protected                         *
    * @return  void                                          //                                   *
    * @param   QString p_qstrInclude                         //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 23. Nov 11:40:15 2011----------*/
    void AddHeaderInclude(QString p_qstrInclude);


   public:
   /** +-=---------------------------------------------------------Mi 23. Nov 11:02:32 2011-------*
    * @method  CwmsCodeGeneratorCBase::AddBaseClassData      // public                            *
    * @return  void                                          //                                   *
    * @param   QString p_qstrBaseClassName                   //                                   *
    * @param   QString p_qstrBaseClassFilename               //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 23. Nov 11:02:32 2011----------*/
    void AddBaseClassData(QString p_qstrBaseClassName, QString p_qstrBaseClassFilename);

   public:
   /** +-=---------------------------------------------------------Mo 5. Dez 11:38:54 2011--------*
    * @method  CwmsCodeGeneratorCBase::GetClassName          // public                            *
    * @return  QString                                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 5. Dez 11:38:54 2011-----------*/
    QString GetClassName();

   protected:
   /** +-=---------------------------------------------------------Mo 5. Dez 11:48:46 2011--------*
    * @method  CwmsCodeGeneratorCBase::GenerateSlotHeadHeader // protected                        *
    * @return  QString                                       //                                   *
    * @param   QString p_qstrAccessType                      //                                   *
    * @param   QString p_qstrReturnType                      //                                   *
    * @param   QString p_qstrMethodName                      //                                   *
    * @param   QString p_qstrParameters                      //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 5. Dez 11:48:46 2011-----------*/
    QString GenerateSlotHeadHeader(QString p_qstrAccessType,
                                   QString p_qstrReturnType,
                                   QString p_qstrMethodName,
                                   QString p_qstrParameters);

   public:
   /** +-=---------------------------------------------------------Di 5. Jun 11:36:50 2012--------*
    * @method  CwmsCodeGeneratorCBase::SetDllExportDeclaration // public                          *
    * @return  void                                          //                                   *
    * @param   QString p_qstrDeclaration                     //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 5. Jun 11:36:50 2012-----------*/
    void SetDllExportDeclaration(QString p_qstrDeclaration);

   protected:
   /** +-=---------------------------------------------------------Mi 6. Jun 13:44:08 2012--------*
    * @method  CwmsCodeGeneratorCBase::GenerateDefaultConstructorHeader // protected              *
    * @return  void                                          //                                   *
    * @param   QString p_qstrClassName                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 6. Jun 13:44:08 2012-----------*/
    void GenerateDefaultConstructorHeader(QString p_qstrClassName);

   protected:
   /** +-=---------------------------------------------------------Mi 6. Jun 13:44:13 2012--------*
    * @method  CwmsCodeGeneratorCBase::GenerateDefaultConstructorSourceWithoutBaseClasses // protected*
    * @return  void                                          //                                   *
    * @param   QString p_qstrClassName                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 6. Jun 13:44:13 2012-----------*/
    void GenerateDefaultConstructorSourceWithoutBaseClasses(QString p_qstrClassName);

   protected:
   /** +-=---------------------------------------------------------Fr 13. Jul 15:38:51 2012-------*
    * @method  CwmsCodeGeneratorCBase::GetParameter          // protected                         *
    * @return  QString                                       //                                   *
    * @param   EdmValue p_eDmValue                           //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 13. Jul 15:38:51 2012----------*/
    QString GetParameter(EdmValueType p_eDmValue);

   protected:
   /** +-=---------------------------------------------------------Fr 13. Jul 13:37:35 2012-------*
    * @method  CwmsCodeGeneratorCBase::GetReturnType         // protected                         *
    * @return  QString                                       //                                   *
    * @param   EdmValue p_eDmValue                           //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 13. Jul 13:37:35 2012----------*/
    QString GetReturnType(EdmValueType p_eDmValue);
};

#endif // CWMSCODEGENERATORCBASE_H
