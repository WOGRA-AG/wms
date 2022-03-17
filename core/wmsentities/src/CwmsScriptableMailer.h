#ifndef CWMSSCRIPTABLEMAILER_H
#define CWMSSCRIPTABLEMAILER_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes
#include <QScriptable>
#include <QObject>

// Own Includes
#include "CwmsScriptableBase.h"
#include "basetools.h"

// Forwards
class CwmsbtMailMessage;

// TypeDefs


/* 
 * This class implements the the script interface for js methods
 */
class BASETOOLS_API CwmsScriptableMailer: public CwmsScriptableBase
{
    Q_OBJECT

   public:
   /** +-=---------------------------------------------------------Fr 9. Nov 10:59:32 2012--------*
    * @method  CwmsScriptableMailer::CwmsScriptableMailer    // public                            *
    * @return                                                //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 9. Nov 10:59:32 2012-----------*/
    CwmsScriptableMailer( );

   public:
   /** +-=---------------------------------------------------------Fr 9. Nov 10:59:40 2012--------*
    * @method  CwmsScriptableMailer::~CwmsScriptableMailer   // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CwmsScriptableMailer                                       *
    *----------------last changed: -----------------------------Fr 9. Nov 10:59:40 2012-----------*/
    virtual ~CwmsScriptableMailer( );

   public slots:
   /** +-=---------------------------------------------------------Di 27. Nov 16:28:49 2012-------*
    * @method  CwmsScriptableMailer::CreateMailObject        // public                            *
    * @return  QObject*                                      //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 27. Nov 16:28:49 2012----------*/
    QObject* createMailObject();
};

#endif // CWMSSCRIPTABLEMAILER_H
