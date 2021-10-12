/******************************************************************************
 ** WOGRA Middleware Server Data Manager Module
 **
 ** @Author Wolfgang Graßhof 
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies All rights reserved
 ******************************************************************************/

#ifndef CDMLOCKING_H
#define CDMLOCKING_H

// System and QT Includes

#include <qobject.h>
#include <qmutex.h>
#include <QScriptable>
#include <QAtomicInt>
#include <QAtomicPointer>

// WMS Commons Includes
#include "CwmsSynchronizable.h"

// own Includes
#include "datamanager.h"


// forwards
class QDateTime;
class CdmDataProvider;

// enumeration
enum EdmLockingMode
{
   eDmLockingModeNone,
   eDmLockingModeWrite,
   eDmLockingModeRead
};


/* 
 * This class implements the locking in this
 * framework. It is needed for multithreaded 
 * dataaccess in this framework.
 */
class WMSMANAGER_API CdmLocatedElement : public QObject, protected QScriptable, public CwmsSynchronizable
{
   Q_OBJECT

   private:    
      static QAtomicInt ms_iInstantCount;
      static QMutex ms_qMutex;
      // QString m_qstrUUid;


      static QString ExtendUriPath(QString p_qstrExtension);
public:

	   CdmLocatedElement(QObject* p) : QObject(p){}
   /** +-=---------------------------------------------------------Sa 20. Aug 12:46:22 2005*
    * @method  CdmLocatedElement::~CdmLocatedElement                       // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CdmLocatedElement                                                 *
    *----------------last changed: -----------------------------Sa 20. Aug 12:46:22 2005----------*/
virtual ~CdmLocatedElement(  );


  
  public:
   /** +-=---------------------------------------------------------Sa 20. Aug 12:46:17 2005*
    * @method  CdmLocatedElement::CdmLocatedElement                        // public                            *
    * @return  void                                          //                                   *
    * @comment The cosntructor.                                                                   *
    *----------------last changed: -----------------------------Sa 20. Aug 12:46:17 2005----------*/
CdmLocatedElement(  );


   public:
   /** +-=---------------------------------------------------------Fr 25. Mai 15:17:16 2012-------*
    * @method  CdmLocatedElement::GetInstanceCount                  // public, static                    *
    * @return  int                                           //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 25. Mai 15:17:16 2012----------*/
    static int GetInstanceCount();

   protected:
   /** +-=---------------------------------------------------------Di 20. Nov 14:28:39 2012-------*
    * @method  CdmLocatedElement::CdmLocatedElement                        // protected                           *
    * @return                                                //                                   *
    * @param   const CdmLocatedElement&                             //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 20. Nov 14:28:39 2012----------*/
    CdmLocatedElement( const CdmLocatedElement&);


public:
   /** +-=---------------------------------------------------------Fr 7. Dez 15:14:00 2012--------*
    * @method  CdmLocatedElement::CreateUri                  // public, static                    *
    * @return  QString                                       //                                   *
    * @param  qint64 p_lDbId                                  //                                   *
    * @param   QString p_qstrKey                             //                                   *
    * @param   QString p_qstrKeyname                         //                                   *
    * @param   QString p_qstrValueKeyname = ""               //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 7. Dez 15:14:00 2012-----------*/
    static QString CreateUri(QString p_qstrKey,
                             QString p_qstrKeyname,
                             QString p_qstrKeyname2 = "",
                             QString p_qstrKeyname3 = "");


        //QString () const;
    public slots:
         /** +-=---------------------------------------------------------Sa 9. Feb 11:44:24 2013--------*
    * @method  CdmLocatedElement::GetUri                     // public, const, virtual, slots     *
    * @return  QString                                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Sa 9. Feb 11:44:24 2013-----------*/
      virtual QString GetUri( ) const;

    public slots:
         /** +-=---------------------------------------------------------Sa 9. Feb 11:44:07 2013--------*
    * @method  CdmLocatedElement::IsMember                   // public, const, virtual, slots     *
    * @return  bool                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Sa 9. Feb 11:44:07 2013-----------*/
      virtual bool IsMember( ) const;

    public slots:
         /** +-=---------------------------------------------------------Sa 9. Feb 11:44:03 2013--------*
    * @method  CdmLocatedElement::IsValue                    // public, const, virtual, slots     *
    * @return  bool                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Sa 9. Feb 11:44:03 2013-----------*/
      virtual bool IsValue( ) const;

    public slots:
         /** +-=---------------------------------------------------------Sa 9. Feb 11:43:58 2013--------*
    * @method  CdmLocatedElement::IsClass                    // public, const, virtual, slots     *
    * @return  bool                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Sa 9. Feb 11:43:58 2013-----------*/
      virtual bool IsClass( ) const;

    public slots:
         /** +-=---------------------------------------------------------Sa 9. Feb 11:43:52 2013--------*
    * @method  CdmLocatedElement::IsContainer               // public, const, virtual, slots     *
    * @return  bool                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Sa 9. Feb 11:43:52 2013-----------*/
      virtual bool IsContainer( ) const;

    public slots:
         /** +-=---------------------------------------------------------Sa 9. Feb 11:43:47 2013--------*
    * @method  CdmLocatedElement::IsObject                   // public, const, virtual, slots     *
    * @return  bool                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Sa 9. Feb 11:43:47 2013-----------*/
      virtual bool IsObject( ) const;
public:
   /** +-=---------------------------------------------------------Sa 9. Feb 11:44:13 2013--------*
    * @method  CdmLocatedElement::IsUser                     // public, const, virtual            *
    * @return  bool                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Sa 9. Feb 11:44:13 2013-----------*/
    virtual bool IsUser() const;

	virtual bool IsMethod() const;
   public:
   /** +-=---------------------------------------------------------Sa 9. Feb 11:44:18 2013--------*
    * @method  CdmLocatedElement::IsUserGroup                // public, const, virtual            *
    * @return  bool                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Sa 9. Feb 11:44:18 2013-----------*/
        virtual bool IsUserGroup() const;
        virtual bool IsPackage() const;
        virtual bool IsModelElement() const;
        virtual QVariant GetVariant() const = 0;
        static QString CreateUriHost();
        virtual bool IsScheme() const;
        virtual bool IsClassManager() const;
        virtual bool IsContainerManager() const;
        static QString CreateUriPath(QString p_qstrType, QString p_qstrKeyname1, QString p_qstrKeyname2, QString p_qstrKeyname3);
        virtual bool IsDataProvider() const;
        virtual QString GetUriInternal() const;
};

#endif // //CDMLOCKING_H
