/******************************************************************************
 ** WOGRA Middleware Server Data Manager Module
 **
 ** @Author Wolfgang Graßhof 
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies All rights reserved
 ******************************************************************************/

#ifndef CWMSDATAACCESS_H
#define CWMSDATAACCESS_H

// System and QT Includes
#include <qstring.h>
#include <qdatetime.h>
#include <QString>

// own Includes
#include "CdmLocatedElement.h"
#include "CdmModelElement.h"
#include "CdmUriTemplate.h"

// forwards
class CdmObject;
class CdmObjectContainer;


/**
 * The CdmObjectAdaptor class implements the adaptor for objects
 * it can be used for accessing object data and
 * reduce sourcecode size in client applications.
 */
class WMSMANAGER_API CdmObjectAdaptor : public CdmLocatedElement
{
private:
    // Datbase ID
    long m_lDbId;

    // Object ID
    long m_lObjectId;

    // ObjectList ID
    long m_lObjectListId;

public:
   /** +-=---------------------------------------------------------Sa 20. Aug 10:08:22 2005*
    * @method  CdmObjectAdaptor::CdmObjectAdaptor            // public                            *
    * @return                                                //                                   *
    * @param   long p_lDbId                                  //                                   *
    * @param   long p_lObjectId                              //                                   *
    * @param   long p_lObjectListId                          //                                   *
    * @comment the cosntructor of dataccess.                                                      *
    *----------------last changed: -----------------------------Sa 20. Aug 10:08:22 2005----------*/
CdmObjectAdaptor(  long p_lDbId, long p_lObjectId, long p_lObjectListId );

public:
   /** +-=---------------------------------------------------------Sa 20. Aug 10:08:34 2005*
    * @method  CdmObjectAdaptor::CdmObjectAdaptor            // public                            *
    * @return                                                //                                   *
    * @param   CdmObject* p_pCdmObject                       //                                   *
    * @comment The constructor f the object adaptor.                                              *
    *----------------last changed: -----------------------------Sa 20. Aug 10:08:34 2005----------*/
CdmObjectAdaptor(  CdmObject* p_pCdmObject );

public:
   /** +-=---------------------------------------------------------Sa 20. Aug 12:47:25 2005*
    * @method  CdmObjectAdaptor::~CdmObjectAdaptor           // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CwmsDataAccess                                             *
    *----------------last changed: -----------------------------Sa 20. Aug 12:47:25 2005----------*/
virtual ~CdmObjectAdaptor(  );

public:
    CdmObject* GetObject(); // deprecated since everyone defines a "GetObject" -> GetObjectA GetObjectW stuff
    CdmObject* GetDataObject();
    CdmObject* GetDataObjectConst() const;
    const CdmObject* GetConstDataObjectConst() const;

   public:
   /** +-=---------------------------------------------------------So 10. Feb 09:38:10 2013-------*
    * @method  CdmObjectAdaptor::GetObjectId                 // public, const                     *
    * @return  long                                          //                                   *
    * @comment returns the object id of this obejct.                                              *
    *----------------last changed: -----------------------------So 10. Feb 09:38:10 2013----------*/
    long GetObjectId() const;

   public:
   /** +-=---------------------------------------------------------So 10. Feb 09:38:24 2013-------*
    * @method  CdmObjectAdaptor::GetString                   // public, const                     *
    * @return  QString                                       //                                   *
    * @param   QString p_qstrKeyname                         //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 10. Feb 09:38:24 2013----------*/
    QString GetString(QString p_qstrKeyname) const;

   public:
   /** +-=---------------------------------------------------------So 10. Feb 09:38:49 2013-------*
    * @method  CdmObjectAdaptor::GetTime                     // public, const                     *
    * @return  QTime                                         //                                   *
    * @param   QString p_qstrKeyname                         //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 10. Feb 09:38:49 2013----------*/
    QTime GetTime(QString p_qstrKeyname) const;

   public:
   /** +-=---------------------------------------------------------So 10. Feb 09:38:57 2013-------*
    * @method  CdmObjectAdaptor::GetDate                     // public, const                     *
    * @return  QDate                                         //                                   *
    * @param   QString p_qstrKeyname                         //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 10. Feb 09:38:57 2013----------*/
    QDate GetDate(QString p_qstrKeyname) const;

   public:
   /** +-=---------------------------------------------------------So 10. Feb 09:39:13 2013-------*
    * @method  CdmObjectAdaptor::GetFloat                    // public, const                     *
    * @return  float                                         //                                   *
    * @param   QString p_qstrKeyname                         //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 10. Feb 09:39:13 2013----------*/
    float GetFloat(QString p_qstrKeyname) const;

   public:
   /** +-=---------------------------------------------------------So 10. Feb 09:39:22 2013-------*
    * @method  CdmObjectAdaptor::GetBool                     // public, const                     *
    * @return  bool                                          //                                   *
    * @param   QString p_qstrKeyname                         //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 10. Feb 09:39:22 2013----------*/
    bool GetBool(QString p_qstrKeyname) const;

   public:
   /** +-=---------------------------------------------------------Di 8. Feb 16:20:28 2011--------*
    * @method  CdmObjectAdaptor::SetValue                    // public                            *
    * @return  void                                          //                                   *
    * @param   QString p_qstrKeyname                         //                                   *
    * @param   QString p_qstrValue                           //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 8. Feb 16:20:28 2011-----------*/
    void SetValue(QString p_qstrKeyname, QString p_qstrValue);

   public:
   /** +-=---------------------------------------------------------Di 8. Feb 16:20:34 2011--------*
    * @method  CdmObjectAdaptor::SetValue                    // public                            *
    * @return  void                                          //                                   *
    * @param   QString p_qstrKeyname                         //                                   *
    * @param   QDate p_qdDate                                //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 8. Feb 16:20:34 2011-----------*/
    void SetValue(QString p_qstrKeyname, QDate p_qdDate);

   public:
   /** +-=---------------------------------------------------------Di 8. Feb 16:20:40 2011--------*
    * @method  CdmObjectAdaptor::SetValue                    // public                            *
    * @return  void                                          //                                   *
    * @param   QString p_qstrKeyname                         //                                   *
    * @param   QDateTime p_qdtDateTime                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 8. Feb 16:20:40 2011-----------*/
    void SetValue(QString p_qstrKeyname, QDateTime p_qdtDateTime);

   public:
   /** +-=---------------------------------------------------------Di 8. Feb 16:20:46 2011--------*
    * @method  CdmObjectAdaptor::SetValue                    // public                            *
    * @return  void                                          //                                   *
    * @param   QString p_qqstrkeyname                        //                                   *
    * @param   QTime p_qtTime                                //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 8. Feb 16:20:46 2011-----------*/
    void SetValue(QString p_qqstrkeyname, QTime p_qtTime);

   public:
   /** +-=---------------------------------------------------------Di 8. Feb 16:20:51 2011--------*
    * @method  CdmObjectAdaptor::SetValue                    // public                            *
    * @return  void                                          //                                   *
    * @param   QString p_qstrKeyname                         //                                   *
    * @param   float p_fValue                                //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 8. Feb 16:20:51 2011-----------*/
    void SetValue(QString p_qstrKeyname, float p_fValue);

   public:
   /** +-=---------------------------------------------------------Di 8. Feb 16:21:04 2011--------*
    * @method  CdmObjectAdaptor::SetValue                    // public                            *
    * @return  void                                          //                                   *
    * @param   QString p_qstrKeyname                         //                                   *
    * @param   int p_iValue                                  //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 8. Feb 16:21:04 2011-----------*/
    void SetValue(QString p_qstrKeyname, int p_iValue);

   public:
   /** +-=---------------------------------------------------------Di 8. Feb 16:21:15 2011--------*
    * @method  CdmObjectAdaptor::SetValue                    // public                            *
    * @return  void                                          //                                   *
    * @param   QString p_qstrKeyname                         //                                   *
    * @param   long p_lValue                                 //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 8. Feb 16:21:15 2011-----------*/
    void SetValue(QString p_qstrKeyname, long p_lValue);

   public:
   /** +-=---------------------------------------------------------Di 8. Feb 16:21:21 2011--------*
    * @method  CdmObjectAdaptor::SetValue                    // public                            *
    * @return  void                                          //                                   *
    * @param   QString p_qstrKeyname                         //                                   *
    * @param   bool p_bValue                                 //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 8. Feb 16:21:21 2011-----------*/
    void SetValue(QString p_qstrKeyname, bool p_bValue);

   public:
   /** +-=---------------------------------------------------------Di 8. Feb 16:21:27 2011--------*
    * @method  CdmObjectAdaptor::GetObjectRefValue           // public                            *
    * @return  CdmObject*                                    //                                   *
    * @param   QString p_qstrKeyname                         //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 8. Feb 16:21:27 2011-----------*/
    CdmObject* GetObjectRefValue(QString p_qstrKeyname);

   public:
   /** +-=---------------------------------------------------------Di 8. Feb 16:21:35 2011--------*
    * @method  CdmObjectAdaptor::GetObjectRef                // public                            *
    * @return  long                                          //                                   *
    * @param   QString p_qstrKeyname                         //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 8. Feb 16:21:35 2011-----------*/
    long GetObjectRef(QString p_qstrKeyname);

   public:
   /** +-=---------------------------------------------------------Di 8. Feb 16:21:42 2011--------*
    * @method  CdmObjectAdaptor::GetObjectListRef            // public                            *
    * @return  long                                          //                                   *
    * @param   QString p_qstrKeyname                         //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 8. Feb 16:21:42 2011-----------*/
    long GetContainerRef(QString p_qstrKeyname);

   public:
   /** +-=---------------------------------------------------------Di 8. Feb 16:21:48 2011--------*
    * @method  CdmObjectAdaptor::SetContainerRefValue       // public                            *
    * @return  void                                          //                                   *
    * @param   QString p_qstrKeyname                         //                                   *
    * @param   long p_lObjectListId                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 8. Feb 16:21:48 2011-----------*/
    void SetContainerRefValue(QString p_qstrKeyname, long p_lObjectListId);


   public:
   /** +-=---------------------------------------------------------Do 25. Mai 12:56:27 2006-------*
    * @method  CdmObjectAdaptor::GetEmptyContainerRefValue  // public                            *
    * @return  CdmObjectContainer*                                //                                   *
    * @param   QString p_qstrKeyname                         //                                   *
    * @comment This method returns the objectlistvalueref CdmObjectContainer* of a given value         *
    *----------------last changed: Wolfgang Graßhof-------------Do 25. Mai 12:56:27 2006----------*/
    CdmObjectContainer* GetEmptyContainerRefValue(QString p_qstrKeyname);

   public:
    int CommitObject();

   public:
   /** +-=---------------------------------------------------------So 10. Feb 09:39:05 2013-------*
    * @method  CdmObjectAdaptor::GetDateTime                 // public, const                     *
    * @return  QDateTime                                     //                                   *
    * @param   QString p_qstrKeyname                         //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 10. Feb 09:39:05 2013----------*/
    QDateTime GetDateTime(QString p_qstrKeyname) const;

   public:
   /** +-=---------------------------------------------------------So 10. Feb 09:39:40 2013-------*
    * @method  CdmObjectAdaptor::GetInt                      // public, const                     *
    * @return  int                                           //                                   *
    * @param   QString p_qstrKeyname                         //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 10. Feb 09:39:40 2013----------*/
    int GetInt(QString p_qstrKeyname) const;

   public:
   /** +-=---------------------------------------------------------So 10. Feb 09:40:09 2013-------*
    * @method  CdmObjectAdaptor::GetDouble                   // public, const                     *
    * @return  double                                        //                                   *
    * @param   QString p_qstrKeyname                         //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 10. Feb 09:40:09 2013----------*/
    double GetDouble(QString p_qstrKeyname) const;

   public:
   /** +-=---------------------------------------------------------Di 8. Feb 16:20:57 2011--------*
    * @method  CdmObjectAdaptor::SetValue                    // public                            *
    * @return  void                                          //                                   *
    * @param   QString p_qstrKeyname                         //                                   *
    * @param   double p_dValue                               //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 8. Feb 16:20:57 2011-----------*/
    void SetValue(QString p_qstrKeyname, double p_dValue);

   public:
   /** +-=---------------------------------------------------------So 10. Feb 09:37:59 2013-------*
    * @method  CdmObjectAdaptor::GetCaption                  // public, const                     *
    * @return  QString                                       //                                   *
    * @comment This method returns the caption of the object.                                     *
    *----------------last changed: -----------------------------So 10. Feb 09:37:59 2013----------*/
    QString GetCaption() const;

   public:
   /** +-=---------------------------------------------------------So 10. Feb 09:37:50 2013-------*
    * @method  CdmObjectAdaptor::GetKeyname                  // public, const                     *
    * @return  QString                                       //                                   *
    * @comment This method returns the caption of the object.                                     *
    *----------------last changed: -----------------------------So 10. Feb 09:37:50 2013----------*/
    QString GetKeyname() const;

   public:
   /** +-=---------------------------------------------------------So 10. Feb 09:41:18 2013-------*
    * @method  CdmObjectAdaptor::GetDisplayString            // public, const                     *
    * @return  QString                                       //                                   *
    * @param   QString p_qstrKeyname                         //                                   *
    * @comment This method returns the displaystring to an value.                                 *
    *----------------last changed: -----------------------------So 10. Feb 09:41:18 2013----------*/
    QString GetDisplayString(QString p_qstrKeyname) const;

   public:
   /** +-=---------------------------------------------------------So 10. Feb 09:37:40 2013-------*
    * @method  CdmObjectAdaptor::IsValid                     // public, const                     *
    * @return  bool                                          //                                   *
    * @comment returns if this adaptor is valid or not.                                           *
    *----------------last changed: -----------------------------So 10. Feb 09:37:40 2013----------*/
    bool IsValid() const;


   public:
   /** +-=---------------------------------------------------------Di 8. Feb 16:22:11 2011--------*
    * @method  CdmObjectAdaptor::SetObjectRefValue           // public                            *
    * @return  void                                          //                                   *
    * @param   QString p_qstrKeyname                         //                                   *
    * @param   CdmObject* p_pCdmObject                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 8. Feb 16:22:11 2011-----------*/
    void SetObjectRefValue(QString p_qstrKeyname, CdmObject* p_pCdmObject);

   public:
   /** +-=---------------------------------------------------------Di 8. Feb 16:21:56 2011--------*
    * @method  CdmObjectAdaptor::SetContainerRefValue       // public                            *
    * @return  void                                          //                                   *
    * @param   QString p_qstrKeyname                         //                                   *
    * @param   CdmObjectContainer* p_pContainer               //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 8. Feb 16:21:56 2011-----------*/
    void SetContainerRefValue(QString p_qstrKeyname, CdmObjectContainer* p_pContainer);
    void ReloadContainerComplete(CdmObjectContainer*& p_pContainer);


   /** +-=---------------------------------------------------------Sa 5. Jun 14:23:41 2010--------*
    * @method  CdmObjectAdaptor::SetObject                   // public, virtual                   *
    * @return  void                                          //                                   *
    * @param   CdmObject* p_pCdmObject                       //                                   *
    * @comment With the help of this method it is possible to set the object after creating the   *
    *          adaptor.                                                                           *
    *----------------last changed: -----------------------------Sa 5. Jun 14:23:41 2010-----------*/
    virtual void SetObject(CdmObject* p_pCdmObject);

   public:
   /** +-=---------------------------------------------------------Mo 27. Feb 11:38:44 2006-------*
    * @method  CdmObjectAdaptor::CdmObjectAdaptor            // public                            *
    * @return                                                //                                   *
    * @comment The default constructor. it creates an invalid objectadaptor. if you want to       *
    *          change it to a valid adaptor you have to call SetObject() with a valid             *
    *          CdmObject.                                                                         *
    *----------------last changed: Wolfgang Graßhof-------------Mo 27. Feb 11:38:44 2006----------*/
    CdmObjectAdaptor( );


   public:
   /** +-=---------------------------------------------------------Di 8. Feb 16:22:17 2011--------*
    * @method  CdmObjectAdaptor::GetContainerRefValue       // public                            *
    * @return  CdmObjectContainer*                                //                                   *
    * @param   QString p_qstrKeyname                         //                                   *
    * @comment This method returns the objectlistvalueref CdmObjectContainer* of a given value         *
    *----------------last changed: -----------------------------Di 8. Feb 16:22:17 2011-----------*/
    CdmObjectContainer* GetContainerRefValue(QString p_qstrKeyname);

   public:
   /** +-=---------------------------------------------------------So 10. Feb 09:40:00 2013-------*
    * @method  CdmObjectAdaptor::GetLong                     // public, const                     *
    * @return  long                                          //                                   *
    * @param   QString p_qstrKeyname                         //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 10. Feb 09:40:00 2013----------*/
    long GetLong(QString p_qstrKeyname) const;

   public:
   /** +-=---------------------------------------------------------So 19. Nov 16:11:29 2006-------*
    * @method  CdmObjectAdaptor::CdmObjectAdaptor            // public                            *
    * @return                                                //                                   *
    * @param   const CdmObjectAdaptor& p_rCdmObjectAdaptor   //                                   *
    * @comment                                                                                    *
    *----------------last changed: Wolfgang Graßhof-------------So 19. Nov 16:11:29 2006----------*/
    CdmObjectAdaptor( const CdmObjectAdaptor& p_rCdmObjectAdaptor);

   public:
   /** +-=---------------------------------------------------------So 19. Nov 16:36:24 2006-------*
    * @method  CdmObjectAdaptor::operator=                   // public                            *
    * @return  void                                          //                                   *
    * @param   const CdmObjectAdaptor& p_rCdmObjectAdaptor   //                                   *
    * @comment                                                                                    *
    *----------------last changed: Wolfgang Graßhof-------------So 19. Nov 16:36:24 2006----------*/
    void operator=(const CdmObjectAdaptor& p_rCdmObjectAdaptor);

   public:
   /** +-=---------------------------------------------------------Mo 31. Dez 11:01:49 2007-------*
    * @method  CdmObjectAdaptor::GetValue                    // public                            *
    * @return  CdmValue*                                     //                                   *
    * @param   QString p_qstrKeyname                         //                                   *
    * @comment returns the valueobject.                                                           *
    *----------------last changed: Wolfgang Graßhof-------------Mo 31. Dez 11:01:49 2007----------*/
    CdmValue* GetValue(QString p_qstrKeyname);
    CdmValue* GetEventValue(QString p_qstrKeyname, CdmObject *pCdmEventObject);

   public:
   /** +-=---------------------------------------------------------Mo 18. Aug 11:59:48 2008-------*
    * @method  CdmObjectAdaptor::SetBinDocNewFilename        // public                            *
    * @return  void                                          //                                   *
    * @param   QString p_qstrKeyname                         //                                   *
    * @param   QString p_qstrFilename                        //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 18. Aug 11:59:48 2008----------*/
    void SetBinDocNewFilename(QString p_qstrKeyname, QString p_qstrFilename);

   public:
   /** +-=---------------------------------------------------------Mo 18. Aug 12:09:50 2008-------*
    * @method  CdmObjectAdaptor::GetBinDocCurrentFilename    // public                            *
    * @return  QString                                       //                                   *
    * @param   QString p_qstrKeyname                         //                                   *
    * @comment returns the current filename of the bindoc for open the file.                      *
    *----------------last changed: -----------------------------Mo 18. Aug 12:09:50 2008----------*/
    QString GetBinDocCurrentFilename(QString p_qstrKeyname);

   public:
   /** +-=---------------------------------------------------------Mo 18. Aug 12:15:20 2008-------*
    * @method  CdmObjectAdaptor::OpenBinDoc                  // public                            *
    * @return  void                                          //                                   *
    * @param   QString p_qstrKeyname                         //                                   *
    * @comment This method opens the bindoc.                                                      *
    *----------------last changed: -----------------------------Mo 18. Aug 12:15:20 2008----------*/
    void OpenBinDoc(QString p_qstrKeyname);

   public:
   /** +-=---------------------------------------------------------Di 28. Apr 18:28:30 2009-------*
    * @method  CdmObjectAdaptor::SaveBinDocTo                // public                            *
    * @return  void                                          //                                   *
    * @param   QString p_qstrKeyname                         //                                   *
    * @param   QString p_qstrPath                            //                                   *
    * @comment savesthe specified bindoc in the specified path. It does not oberride files.       *
    *----------------last changed: -----------------------------Di 28. Apr 18:28:30 2009----------*/
    void SaveBinDocTo(QString p_qstrKeyname, QString p_qstrPath);

   public:
   /** +-=---------------------------------------------------------Mo 12. Okt 18:22:23 2009-------*
    * @method  CdmObjectAdaptor::DeleteObject                // public                            *
    * @return  bool                                          //                                   *
    * @comment This method sets the deleted flag of the object.                                   *
    *----------------last changed: -----------------------------Mo 12. Okt 18:22:23 2009----------*/
    bool DeleteObject();

   public:
   /** +-=---------------------------------------------------------So 10. Feb 09:44:23 2013-------*
    * @method  CdmObjectAdaptor::IsTypeOf                    // public, const                     *
    * @return  bool                                          //                                   *
    * @param   QString p_qstrType                            //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 10. Feb 09:44:23 2013----------*/
    bool IsTypeOf(QString p_qstrType) const;

   public:
   /** +-=---------------------------------------------------------So 10. Feb 09:41:46 2013-------*
    * @method  CdmObjectAdaptor::GetStringList               // public, const                     *
    * @return  QLinkedList<QString>                          //                                   *
    * @param   QString p_qstrMember                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 10. Feb 09:41:46 2013----------*/
    QLinkedList<QString> GetStringList(QString p_qstrMember) const;

   public:
   /** +-=---------------------------------------------------------Di 14. Jun 10:02:51 2011-------*
    * @method  CdmObjectAdaptor::AddStringListValue          // public                            *
    * @return  void                                          //                                   *
    * @param   QString p_qstrMember                          //                                   *
    * @param   QString p_qstrValue                           //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 14. Jun 10:02:51 2011----------*/
    void AddStringListValue(QString p_qstrMember, QString p_qstrValue);

   public:
   /** +-=---------------------------------------------------------Di 14. Jun 10:04:56 2011-------*
    * @method  CdmObjectAdaptor::RemoveStringListValue       // public                            *
    * @return  void                                          //                                   *
    * @param   QString p_qstrMember                          //                                   *
    * @param   QString p_qstrValue                           //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 14. Jun 10:04:56 2011----------*/
    void RemoveStringListValue(QString p_qstrMember, QString p_qstrValue);

   public:
   /** +-=---------------------------------------------------------So 10. Feb 09:38:41 2013-------*
    * @method  CdmObjectAdaptor::GetUser                     // public, const                     *
    * @return  CumUser*                                      //                                   *
    * @param   QString p_qstrKeyname                         //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 10. Feb 09:38:41 2013----------*/
    CumUser* GetUser(QString p_qstrKeyname) const;

   public:
   /** +-=---------------------------------------------------------Di 14. Jun 16:42:01 2011-------*
    * @method  CdmObjectAdaptor::SetValue                    // public                            *
    * @return  void                                          //                                   *
    * @param   QString p_qstrKeyname                         //                                   *
    * @param   CumUser* p_pCumUser                           //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 14. Jun 16:42:01 2011----------*/
    void SetValue(QString p_qstrKeyname, CumUser* p_pCumUser);

   protected:
   /** +-=---------------------------------------------------------Mi 21. Sep 18:57:03 2011-------*
    * @method  CdmObjectAdaptor::ValidateObjectData          // protected, virtual                *
    * @return  bool                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 21. Sep 18:57:03 2011----------*/
    virtual bool ValidateObjectData();

    virtual void AfterCommit();
    virtual void BeforeCommit();
public:
   /** +-=---------------------------------------------------------So 10. Feb 09:41:53 2013-------*
    * @method  CdmObjectAdaptor::GetDoubleList               // public, const                     *
    * @return  QLinkedList<double>                           //                                   *
    * @param   QString p_qstrMember                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 10. Feb 09:41:53 2013----------*/
    QLinkedList<double> GetDoubleList(QString p_qstrMember) const;

   public:
   /** +-=---------------------------------------------------------So 10. Feb 09:42:02 2013-------*
    * @method  CdmObjectAdaptor::GetIntList                  // public, const                     *
    * @return  QLinkedList<int>                              //                                   *
    * @param   QString p_qstrMember                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 10. Feb 09:42:02 2013----------*/
    QLinkedList<int> GetIntList(QString p_qstrMember) const;

   public:
   /** +-=---------------------------------------------------------Do 10. Nov 16:14:22 2011-------*
    * @method  CdmObjectAdaptor::GetListObjects              // public                            *
    * @return  QLinkedList<CdmObject*>                       //                                   *
    * @param   QString p_qstrMember                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 10. Nov 16:14:22 2011----------*/
    QLinkedList<CdmObject*> GetListObjects(QString p_qstrMember);

   public:
   /** +-=---------------------------------------------------------Do 10. Nov 16:31:36 2011-------*
    * @method  CdmObjectAdaptor::AddDoubleListValue          // public                            *
    * @return  void                                          //                                   *
    * @param   QString p_qstrMember                          //                                   *
    * @param   double p_dValue                               //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 10. Nov 16:31:36 2011----------*/
    void AddDoubleListValue(QString p_qstrMember, double p_dValue);

   public:
   /** +-=---------------------------------------------------------Do 10. Nov 16:30:58 2011-------*
    * @method  CdmObjectAdaptor::AddIntListValue             // public                            *
    * @return  void                                          //                                   *
    * @param   QString p_qstrMember                          //                                   *
    * @param   int p_iValue                                  //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 10. Nov 16:30:58 2011----------*/
    void AddIntListValue(QString p_qstrMember, int p_iValue);

   public:
   /** +-=---------------------------------------------------------Do 10. Nov 16:32:13 2011-------*
    * @method  CdmObjectAdaptor::AddListObjectsValue         // public                            *
    * @return  void                                          //                                   *
    * @param   QString p_qstrMember                          //                                   *
    * @param   CdmObject* p_pCdmObject                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 10. Nov 16:32:13 2011----------*/
    void AddListObjectsValue(QString p_qstrMember, CdmObject* p_pCdmObject);

   public:
   /** +-=---------------------------------------------------------Do 10. Nov 16:39:29 2011-------*
    * @method  CdmObjectAdaptor::RemoveDoubleListValue       // public                            *
    * @return  void                                          //                                   *
    * @param   QString p_qstrMember                          //                                   *
    * @param   double p_dValue                               //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 10. Nov 16:39:29 2011----------*/
    void RemoveDoubleListValue(QString p_qstrMember, double p_dValue);

   public:
   /** +-=---------------------------------------------------------Do 10. Nov 16:40:08 2011-------*
    * @method  CdmObjectAdaptor::RemoveIntListValue          // public                            *
    * @return  void                                          //                                   *
    * @param   QString p_qstrMember                          //                                   *
    * @param   int p_iValue                                  //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 10. Nov 16:40:08 2011----------*/
    void RemoveIntListValue(QString p_qstrMember, int p_iValue);

   public:
   /** +-=---------------------------------------------------------Do 10. Nov 16:40:51 2011-------*
    * @method  CdmObjectAdaptor::RemoveListObjectsValue      // public                            *
    * @return  void                                          //                                   *
    * @param   QString p_qstrMember                          //                                   *
    * @param   CdmObject* p_pCdmObject                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 10. Nov 16:40:51 2011----------*/
    void RemoveListObjectsValue(QString p_qstrMember, CdmObject* p_pCdmObject);
    void RemoveListObjectsComplete(QString p_qstrMember);

   public:
   /** +-=---------------------------------------------------------Do 15. Dez 18:24:20 2011-------*
    * @method  CdmObjectAdaptor::SetDeleted                  // public                            *
    * @return  void                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 15. Dez 18:24:20 2011----------*/
    void SetDeleted();

   public:
   /** +-=---------------------------------------------------------So 10. Feb 09:42:51 2013-------*
    * @method  CdmObjectAdaptor::GetStringStringDict         // public, const                     *
    * @return  QMap<QString, QString>                        //                                   *
    * @param   QString p_qstrValue                           //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 10. Feb 09:42:51 2013----------*/
    QMap<QString, QString> GetStringStringDict(QString p_qstrValue) const;

   public:
   /** +-=---------------------------------------------------------So 10. Feb 09:43:11 2013-------*
    * @method  CdmObjectAdaptor::GetStringIntDict            // public, const                     *
    * @return  QMap<QString, int>                            //                                   *
    * @param   QString p_qstrValue                           //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 10. Feb 09:43:11 2013----------*/
    QMap<QString, int> GetStringIntDict(QString p_qstrValue) const;

   public:
   /** +-=---------------------------------------------------------So 10. Feb 09:43:23 2013-------*
    * @method  CdmObjectAdaptor::GetStringDoubleDict         // public, const                     *
    * @return  QMap<QString, double>                         //                                   *
    * @param   QString p_qstrValue                           //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 10. Feb 09:43:23 2013----------*/
    QMap<QString, double> GetStringDoubleDict(QString p_qstrValue) const;

   public:
   /** +-=---------------------------------------------------------So 10. Feb 09:44:01 2013-------*
    * @method  CdmObjectAdaptor::GetIntDoubleDict            // public, const                     *
    * @return  QMap<int, double>                             //                                   *
    * @param   QString p_qstrValue                           //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 10. Feb 09:44:01 2013----------*/
    QMap<int, double> GetIntDoubleDict(QString p_qstrValue) const;

   public:
   /** +-=---------------------------------------------------------So 10. Feb 09:43:53 2013-------*
    * @method  CdmObjectAdaptor::GetIntIntDict               // public, const                     *
    * @return  QMap<int, int>                                //                                   *
    * @param   QString p_qstrValue                           //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 10. Feb 09:43:53 2013----------*/
    QMap<int, int> GetIntIntDict(QString p_qstrValue) const;

   public:
   /** +-=---------------------------------------------------------So 10. Feb 09:43:33 2013-------*
    * @method  CdmObjectAdaptor::GetIntStringDict            // public, const                     *
    * @return  QMap<int, QString>                            //                                   *
    * @param   QString p_qstrValue                           //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 10. Feb 09:43:33 2013----------*/
    QMap<int, QString> GetIntStringDict(QString p_qstrValue) const;

   public:
   /** +-=---------------------------------------------------------Mo 23. Jan 14:32:42 2012-------*
    * @method  CdmObjectAdaptor::AddIntStringEntry           // public                            *
    * @return  void                                          //                                   *
    * @param   QString p_qstrMember                          //                                   *
    * @param   int p_iKey                                    //                                   *
    * @param   QString p_qstrValue                           //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 23. Jan 14:32:42 2012----------*/
    void AddIntStringEntry(QString p_qstrMember, int p_iKey, QString p_qstrValue);

   public:
   /** +-=---------------------------------------------------------Mo 23. Jan 14:29:56 2012-------*
    * @method  CdmObjectAdaptor::AddStringIntEntry           // public                            *
    * @return  void                                          //                                   *
    * @param   QString p_qstrMember                          //                                   *
    * @param   QString p_qstrKey                             //                                   *
    * @param   int p_iValue                                  //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 23. Jan 14:29:56 2012----------*/
    void AddStringIntEntry(QString p_qstrMember, QString p_qstrKey, int p_iValue);

   public:
   /** +-=---------------------------------------------------------Mo 23. Jan 14:30:39 2012-------*
    * @method  CdmObjectAdaptor::AddStringDoubleEntry        // public                            *
    * @return  void                                          //                                   *
    * @param   QString p_qstrMember                          //                                   *
    * @param   QString p_qstrKey                             //                                   *
    * @param   double p_dValue                               //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 23. Jan 14:30:39 2012----------*/
    void AddStringDoubleEntry(QString p_qstrMember, QString p_qstrKey, double p_dValue);

   public:
   /** +-=---------------------------------------------------------Mo 23. Jan 14:31:59 2012-------*
    * @method  CdmObjectAdaptor::AddIntDoubleEntry           // public                            *
    * @return  void                                          //                                   *
    * @param   QString p_qstrMember                          //                                   *
    * @param   int p_iKey                                    //                                   *
    * @param   double p_dValue                               //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 23. Jan 14:31:59 2012----------*/
    void AddIntDoubleEntry(QString p_qstrMember, int p_iKey, double p_dValue);

   public:
   /** +-=---------------------------------------------------------Mo 23. Jan 14:32:20 2012-------*
    * @method  CdmObjectAdaptor::AddIntIntEntry              // public                            *
    * @return  void                                          //                                   *
    * @param   QString p_qstrMember                          //                                   *
    * @param   int p_iKey                                    //                                   *
    * @param   int p_iValue                                  //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 23. Jan 14:32:20 2012----------*/
    void AddIntIntEntry(QString p_qstrMember, int p_iKey, int p_iValue);

   public:
   /** +-=---------------------------------------------------------Mo 23. Jan 14:37:32 2012-------*
    * @method  CdmObjectAdaptor::RemoveIntDoubleEntry        // public                            *
    * @return  void                                          //                                   *
    * @param   QString p_qstrMember                          //                                   *
    * @param   int p_iKey                                    //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 23. Jan 14:37:32 2012----------*/
    void RemoveIntDoubleEntry(QString p_qstrMember, int p_iKey);

   public:
   /** +-=---------------------------------------------------------Mo 23. Jan 14:38:12 2012-------*
    * @method  CdmObjectAdaptor::RemoveIntIntEntry           // public                            *
    * @return  void                                          //                                   *
    * @param   QString p_qstrMember                          //                                   *
    * @param   int p_iKey                                    //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 23. Jan 14:38:12 2012----------*/
    void RemoveIntIntEntry(QString p_qstrMember, int p_iKey);

   public:
   /** +-=---------------------------------------------------------Mo 23. Jan 14:38:38 2012-------*
    * @method  CdmObjectAdaptor::RemoveIntStringEntry        // public                            *
    * @return  void                                          //                                   *
    * @param   QString p_qstrMember                          //                                   *
    * @param   int p_iKey                                    //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 23. Jan 14:38:38 2012----------*/
    void RemoveIntStringEntry(QString p_qstrMember, int p_iKey);

   public:
   /** +-=---------------------------------------------------------Mo 23. Jan 14:39:02 2012-------*
    * @method  CdmObjectAdaptor::RemoveStringDoubleEntry     // public                            *
    * @return  void                                          //                                   *
    * @param   QString p_qstrMember                          //                                   *
    * @param   QString p_qstrKey                             //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 23. Jan 14:39:02 2012----------*/
    void RemoveStringDoubleEntry(QString p_qstrMember, QString p_qstrKey);

   public:
   /** +-=---------------------------------------------------------Mo 23. Jan 14:39:31 2012-------*
    * @method  CdmObjectAdaptor::RemoveStringIntEntry        // public                            *
    * @return  void                                          //                                   *
    * @param   QString p_qstrMember                          //                                   *
    * @param   QString p_qstrKey                             //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 23. Jan 14:39:31 2012----------*/
    void RemoveStringIntEntry(QString p_qstrMember, QString p_qstrKey);

   public:
   /** +-=---------------------------------------------------------Mo 23. Jan 14:39:58 2012-------*
    * @method  CdmObjectAdaptor::RemoveStringStringEntry     // public                            *
    * @return  void                                          //                                   *
    * @param   QString p_qstrMember                          //                                   *
    * @param   QString p_qstrKey                             //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 23. Jan 14:39:58 2012----------*/
    void RemoveStringStringEntry(QString p_qstrMember, QString p_qstrKey);

   public:
   /** +-=---------------------------------------------------------Mo 23. Jan 14:41:12 2012-------*
    * @method  CdmObjectAdaptor::AddStringStringEntry        // public                            *
    * @return  void                                          //                                   *
    * @param   QString p_qstrMember                          //                                   *
    * @param   QString p_qstrKey                             //                                   *
    * @param   QString p_qstrValue                           //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 23. Jan 14:41:12 2012----------*/
    void AddStringStringEntry(QString p_qstrMember, QString p_qstrKey, QString p_qstrValue);

   public:
   /** +-=---------------------------------------------------------So 10. Feb 09:44:37 2013-------*
    * @method  CdmObjectAdaptor::GetVariant                  // public, const                     *
    * @return  QVariant                                      //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 10. Feb 09:44:37 2013----------*/
    QVariant GetVariant() const;

   public:
   /** +-=---------------------------------------------------------Mo 4. Jun 16:23:07 2012--------*
    * @method  CdmObjectAdaptor::SetVariant                  // public                            *
    * @return  void                                          //                                   *
    * @param   QVariant& p_rqVariant                         //                                   *
    * @param   QString p_qstrOLKeyname                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 4. Jun 16:23:07 2012-----------*/
    void SetVariant(QVariant& p_rqVariant, QString p_qstrOLKeyname);

   public:
   /** +-=---------------------------------------------------------Mo 4. Jun 16:18:23 2012--------*
    * @method  CdmObjectAdaptor::GetObjectContainer               // public, static                    *
    * @return  CdmObjectContainer*                                //                                   *
    * @param   QString p_qstrKeyname                         //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 4. Jun 16:18:23 2012-----------*/
    static CdmObjectContainer* GetObjectContainer(QString p_qstrKeyname);

   private:
   /** +-=---------------------------------------------------------Mo 4. Jun 16:37:16 2012--------*
    * @method  CdmObjectAdaptor::UpdateObject                // private                           *
    * @return  void                                          //                                   *
    * @param   QVariantMap& p_rqVariant                     //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 4. Jun 16:37:16 2012-----------*/
    void UpdateObject(QVariantMap& p_rqVariant);

    void AppendLinksToChildVariant(CdmObject *pObject, QVariantMap &childVariant) const;
public:
   /** +-=---------------------------------------------------------Mo 10. Sep 16:18:34 2012-------*
    * @method  CdmObjectAdaptor::SetStringList               // public                            *
    * @return  void                                          //                                   *
    * @param   QString p_qstrMember                          //                                   *
    * @param   QLinkedList<QString> p_rqstrlList             //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 10. Sep 16:18:34 2012----------*/
    void SetStringList(QString p_qstrMember, QLinkedList<QString> p_rqstrlList);

   public:
   /** +-=---------------------------------------------------------Mi 12. Sep 11:54:42 2012-------*
    * @method  CdmObjectAdaptor::SetStringStringDict         // public                            *
    * @return  void                                          //                                   *
    * @param   QString p_qstrValue                           //                                   *
    * @param   QMap<QString, QString> p_qmValue              //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 12. Sep 11:54:42 2012----------*/
    void SetStringStringDict(QString p_qstrValue, QMap<QString, QString> p_qmValue);

   public:
   /** +-=---------------------------------------------------------Mi 12. Sep 13:38:07 2012-------*
    * @method  CdmObjectAdaptor::SetStringIntDict            // public                            *
    * @return  void                                          //                                   *
    * @param   QString p_qstrValue                           //                                   *
    * @param   QMap<QString, int> p_qmValue                  //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 12. Sep 13:38:07 2012----------*/
    void SetStringIntDict(QString p_qstrValue, QMap<QString, int> p_qmValue);

   public:
   /** +-=---------------------------------------------------------Do 13. Sep 10:21:00 2012-------*
    * @method  CdmObjectAdaptor::GetObjectContainer               // public                            *
    * @return  CdmObjectContainer*                                //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 13. Sep 10:21:00 2012----------*/
    CdmObjectContainer* GetObjectContainer();

   public:
   /** +-=---------------------------------------------------------So 14. Okt 09:45:03 2012-------*
    * @method  CdmObjectAdaptor::GetParentObject             // public                            *
    * @return  CdmObject*                                    //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 14. Okt 09:45:03 2012----------*/
    CdmObject* GetParentObject();

   public:
   /** +-=---------------------------------------------------------So 14. Okt 09:45:19 2012-------*
    * @method  CdmObjectAdaptor::GetParentObjectId           // public                            *
    * @return  long                                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 14. Okt 09:45:19 2012----------*/
    long GetParentObjectId();

   public:
   /** +-=---------------------------------------------------------Do 25. Okt 13:54:43 2012-------*
    * @method  CdmObjectAdaptor::SetListObjects              // public                            *
    * @return  void                                          //                                   *
    * @param   QString p_qstrMember                          //                                   *
    * @param   QLinkedList<CdmObject*> p_qlObjects           //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Do 25. Okt 13:54:43 2012----------*/
    void SetListObjects(QString p_qstrMember, QLinkedList<CdmObject*> p_qlObjects);

   public:
   /** +-=---------------------------------------------------------Mo 11. Feb 16:37:43 2013-------*
    * @method  CdmObjectAdaptor::Execute                     // public                            *
    * @return  QVariant                                      //                                   *
    * @param   QString p_qstrFunction                        //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 11. Feb 16:37:43 2013----------*/
    QVariant Execute(QString p_qstrFunction);

   public:
   /** +-=---------------------------------------------------------Di 28. Mai 14:35:56 2013-------*
    * @method  CdmObjectAdaptor::SetIntList                  // public                            *
    * @return  void                                          //                                   *
    * @param   QString p_qstrMember                          //                                   *
    * @param   QLinkedList<int> p_rqstrlList                 //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 28. Mai 14:35:56 2013----------*/
    void SetIntList(QString p_qstrMember, QLinkedList<int> p_rqstrlList);

   public:
   /** +-=---------------------------------------------------------Di 28. Mai 14:36:26 2013-------*
    * @method  CdmObjectAdaptor::SetDoubleList               // public                            *
    * @return  void                                          //                                   *
    * @param   QString p_qstrMember                          //                                   *
    * @param   QLinkedList<double> p_rqstrlList              //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 28. Mai 14:36:26 2013----------*/
    void SetDoubleList(QString p_qstrMember, QLinkedList<double> p_rqstrlList);

   public:
   /** +-=---------------------------------------------------------Di 28. Mai 14:38:57 2013-------*
    * @method  CdmObjectAdaptor::SetStringDoubleDict         // public                            *
    * @return  void                                          //                                   *
    * @param   QString p_qstrValue                           //                                   *
    * @param   QMap<QString, double> p_qmValue               //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 28. Mai 14:38:57 2013----------*/
    void SetStringDoubleDict(QString p_qstrValue, QMap<QString, double> p_qmValue);

   public:
   /** +-=---------------------------------------------------------Di 28. Mai 14:39:28 2013-------*
    * @method  CdmObjectAdaptor::SetIntDoubleDict            // public                            *
    * @return  void                                          //                                   *
    * @param   QString p_qstrValue                           //                                   *
    * @param   QMap<int, double> p_qmValue                   //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 28. Mai 14:39:28 2013----------*/
    void SetIntDoubleDict(QString p_qstrValue, QMap<int, double> p_qmValue);

   public:
   /** +-=---------------------------------------------------------Di 28. Mai 14:39:52 2013-------*
    * @method  CdmObjectAdaptor::SetIntIntDict               // public                            *
    * @return  void                                          //                                   *
    * @param   QString p_qstrValue                           //                                   *
    * @param   QMap<int, int> p_qmValue                      //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 28. Mai 14:39:52 2013----------*/
    void SetIntIntDict(QString p_qstrValue, QMap<int, int> p_qmValue);

   public:
   /** +-=---------------------------------------------------------Di 28. Mai 14:41:45 2013-------*
    * @method  CdmObjectAdaptor::SetIntStringDict            // public                            *
    * @return  void                                          //                                   *
    * @param   QString p_qstrValue                           //                                   *
    * @param   QMap<int, QString> p_qmValue                  //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Di 28. Mai 14:41:45 2013----------*/
    void SetIntStringDict(QString p_qstrValue, QMap<int, QString> p_qmValue);
    public:
    virtual QString GetUri();
    QByteArray LoadBinDoc(QString p_qstrKeyname);
    QString GetUriInternal() const;
    CdmContainerManager *GetContainerManager();
    CdmClassManager *GetClassManager();
    QVariantMap GetVariantGraph(bool p_bFollowNonOwnerObjectlist, bool p_bFollowNonOwnerObject, QStringList p_qstrExcludedKeynames, int p_iMaxDepth, int p_iMaxObjects) const;
    QVariant GetVariant(QString &p_qstrValue) const;
    void Refresh();
    void SetObjectRefValue(QString p_qstrKeyname, QString qstrSelfLink);
    void SetListObjectsValues(QString p_qstrMember, QVariantList selfLinks);
    CdmObject *FindObjectBySelfLink(QString qstrSelfLink);
	QString GetBinDocCurrentCompletePath(QString p_qstrKeyname);
};

#endif //
