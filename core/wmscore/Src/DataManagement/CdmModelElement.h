/******************************************************************************
 ** WOGRA Middleware Server Data Manager Module
 **
 ** @Author Wolfgang Graßhof 
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies All rights reserved
 ******************************************************************************/

#ifndef CDMBASE_H
#define CDMBASE_H


// System and QT Includes
#include <QDateTime>
#include <QVariant>

// own Includes
#include "datamanager.h"
#include "CdmLocatedElement.h"
#include "CdmClassManager.h"

 

// forwards
class QString;
class QDateTime;
class QDomElement;
class CdmDataProvider;
class CdmSettings;
class CdmLogging;

class CdmContainerManager;
class IdmDataAccess;


// enumerations
enum EdmStringDisplayType
{
   edmStringDisplayTypeFormatted,  // formatted (HTML) display
   edmStringDisplayTypeUnFormatted,// unformatted (plain text) display
   edmStringDisplayTypeDirectory,  // for strings with directory dialog
   edmStringDisplayTypeFile,       // for strings with file choice dialog
   edmStringDisplayTypeEncrypted,  // Hidden Passwords
   edmStringDisplayTypeLink,       // Web links
   edmStringDisplayTypeJson,       // Json Content --> can be used for chardocs
   edmStringDisplayTypeXml,        // XML Content --> can be used for chardocs
};

/*
 * The values types in WMS
 */
enum EdmValueType
{
    eDmValueNone              = 0,
    eDmValueBool              = 1,
    eDmValueInt               = 2,
    eDmValueLong              = 3,
    eDmValueFloat             = 4,
    eDmValueDouble            = 5,
    eDmValueString            = 6,
    eDmValueDate              = 7,
    eDmValueTime              = 8,
    eDmValueDateTime          = 9,
    eDmValueObjectRef         = 10,
    eDmValueContainerRef      = 11,
    eDmValueCounter           = 12,
    eDmValueBinaryDocument    = 13,
    eDmValueCharacterDocument = 14,
    eDmValueListInt           = 15,
    eDmValueListDouble        = 16,
    eDmValueListString        = 17,
    eDmValueDictStringInt     = 18,
    eDmValueDictStringString  = 19,
    eDmValueDictStringDouble  = 20,
    eDmValueDictIntInt        = 21,
    eDmValueDictIntString     = 22,
    eDmValueDictIntDouble     = 23,
    eDmValueListObjects       = 24,
    eDmValueObjectTree        = 25,
    eDmValueFormula           = 26,
    eDmValueUser              = 27,
    eDmValueEnum              = 28,
    eDmValueUserGroup         = 29,
    eDmValueArray             = 30,// no wms type will be used for function parameter
    eDmValueGeoPos            = 31, // not yet implemented
    eDmValueDimDouble         = 32, // not yet implemented
    eDmValueURI               = 33,// not yet implemented
    eDmValueQObject           = 34,// no wms type will be used for function parameter or return type
};


enum EdmChangeFlag
{
    edmChangeFlagNone = 0,
    edmChangeFlagKeyname = 1,
    edmChangeFlagType = 2,
    edmChangeFlagUniqueProperty = 4,
    edmChangeFlagAbstract = 8,
    edmChangeFlagPersistent = 16,
    eDmChangeFlagBaseClass = 32,
};


/*
 * The base class for the most datamanager class
 * except manager classes
 */
class WMSMANAGER_API CdmModelElement : public CdmModelElementBase
{
   Q_OBJECT

   friend class IdmDataAccess;
   friend class CdmDataAccessHelper;
   friend class CdmClass;
   friend class CdmObjectContainer;
   friend class CdmContainerManager;
   friend class CdmClassManager;
    
private:    
    /*
     * The Id of the Base object it will be used for referencing
     */
    QAtomicInteger<long> m_lId;

    /*
     * The User Id of the latest person who modified this object
     */
    QAtomicInteger<long>        m_lModifierId;

    /*
     * The User Id of the creator of this object
     */
    QAtomicInteger<long>        m_lCreatorId;

    /*
     * The Object keyname
     */
    QString     m_qstrKeyname;

    /*
     * The object caption
     */
    QString     m_qstrCaption;

    /*
     * The timestamp of the lastchange
     */
    QDateTime   m_qdtLastChange;

    /*
     * Shows if this object is modified
     */
    QAtomicInteger<bool>        m_bModified;

    /*
     * Shows if this object is valid
     */
    QAtomicInteger<bool>        m_bValid;

    /*
     * Shows if the user wants to delete this object
     */
    QAtomicInteger<bool>        m_bDeleted;

    /*
     * Show if this object was created at the moment
     */
    QAtomicInteger<bool>        m_bNew;

    /*
     * if the keyname has changed here you will find the old one
     */
    QString m_qstrOriginalKeyname;

  
   public:
   /** +-=---------------------------------------------------------Sa 20. Aug 12:35:45 2005*
    * @method  CdmModelElement::~CdmModelElement                             // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CdmModelElement                                                    *
    *----------------last changed: -----------------------------Sa 20. Aug 12:35:45 2005----------*/
virtual ~CdmModelElement(  );

    public slots:
         /** +-=---------------------------------------------------------Fr 13. Sep 13:12:51 2013-------*
    * @method  CdmModelElement::GetKeyname                   // public, const, virtual, slots     *
    * @return  QString                                       //                                   *
    * @comment returns the Keyname of this base object.                                           *
    *----------------last changed: -----------------------------Fr 13. Sep 13:12:51 2013----------*/
    virtual QString GetKeyname( ) const;
   public:
   /** +-=---------------------------------------------------------Fr 12. Aug 00:30:46 2005*
    * @method  CdmModelElement::CdmModelElement                              // public                            *
    * @return                                                //                                   *
    * @param   long p_lDatabaseId                            //                                   *
    * @param   long p_lId                                    //                                   *
    * @param   QString p_qstrKeyname                         //                                   *
    * @param   QString p_qstrCaption = ""                    //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 12. Aug 00:30:46 2005----------*/
CdmModelElement(  long p_lDatabaseId, long p_lId, QString p_qstrKeyname, QString p_qstrCaption = "" );
   public:
   /** +-=---------------------------------------------------------Fr 12. Aug 00:31:35 2005*
    * @method  CdmModelElement::GetLastChange                        // public, const                     *
    * @return  QDateTime                                     //                                   *
    * @comment returns the DateTime of the last change in this object.                            *
    *----------------last changed: -----------------------------Fr 12. Aug 00:31:35 2005----------*/
QDateTime GetLastChange(  ) const;
   public:
   /** +-=---------------------------------------------------------Fr 12. Aug 00:31:41 2005*
    * @method  CdmModelElement::SetLastChange                        // public                            *
    * @return  void                                          //                                   *
    * @param   QDateTime& p_qdDateTime                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 12. Aug 00:31:41 2005----------*/
void SetLastChange(  QDateTime& p_qdDateTime );
   public:
   /** +-=---------------------------------------------------------Fr 17. Aug 15:09:01 2012-------*
    * @method  CdmModelElement::SetModified                          // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment This method will be called if the object has been modified.                        *
    *----------------last changed: -----------------------------Fr 17. Aug 15:09:01 2012----------*/
    virtual void SetModified();

    public slots:
         /** +-=---------------------------------------------------------Sa 9. Feb 11:45:59 2013--------*
    * @method  CdmModelElement::IsValid                      // public, const, virtual, slots     *
    * @return  bool                                          //                                   *
    * @comment This method returns if this object is a valid object or not.                       *
    *----------------last changed: -----------------------------Sa 9. Feb 11:45:59 2013-----------*/
      virtual bool IsValid( ) const;
   protected:
   /** +-=---------------------------------------------------------Fr 12. Aug 00:32:23 2005*
    * @method  CdmModelElement::SetInvalid                           // protected                         *
    * @return  void                                          //                                   *
    * @comment This method sets this object as invalid object. This is only possibled to set from *
    *          derived classes.                                                                   *
    *----------------last changed: -----------------------------Fr 12. Aug 00:32:23 2005----------*/
void SetInvalid(  );
   protected:
   /** +-=---------------------------------------------------------Fr 12. Aug 00:32:26 2005*
    * @method  CdmModelElement::SetValid                             // protected                         *
    * @return  void                                          //                                   *
    * @comment This method sets the Base Object valid.                                            *
    *----------------last changed: -----------------------------Fr 12. Aug 00:32:26 2005----------*/
void SetValid(  );
   protected:
   /** +-=---------------------------------------------------------Do 9. Mai 18:30:18 2013--------*
    * @method  CdmModelElement::SetDeleted                   // protected, virtual                *
    * @return  void                                          //                                   *
    * @comment This method sets this base object deleted.                                         *
    *----------------last changed: -----------------------------Do 9. Mai 18:30:18 2013-----------*/
    virtual void SetDeleted();
    public slots:
         /** +-=---------------------------------------------------------Do 9. Mai 18:29:46 2013--------*
    * @method  CdmModelElement::IsDeleted                    // public, const, virtual, slots     *
    * @return  bool                                          //                                   *
    * @comment This emthod returns if this base object is deleted.                                *
    *----------------last changed: -----------------------------Do 9. Mai 18:29:46 2013-----------*/
      virtual bool IsDeleted( ) const;
   public:
   /** +-=---------------------------------------------------------Fr 12. Aug 00:33:03 2005*
    * @method  CdmModelElement::GetCreatorId                         // public, const                     *
    * @return  long                                          //                                   *
    * @comment returns the Id of the creator or null if the system has created this object.       *
    *----------------last changed: -----------------------------Fr 12. Aug 00:33:03 2005----------*/
long GetCreatorId(  ) const;
   public:
   /** +-=---------------------------------------------------------Fr 12. Aug 00:33:06 2005*
    * @method  CdmModelElement::SetModifierId                        // public                            *
    * @return  void                                          //                                   *
    * @param   long p_lUserId                                //                                   *
    * @comment Sets the Modifier Id.                                                              *
    *----------------last changed: -----------------------------Fr 12. Aug 00:33:06 2005----------*/
void SetModifierId(  long p_lUserId );
   public:
   /** +-=---------------------------------------------------------Fr 12. Aug 00:33:00 2005*
    * @method  CdmModelElement::SetCreatorId                         // public                            *
    * @return  void                                          //                                   *
    * @param   long p_lUserId                                //                                   *
    * @comment This method sets the creator of this object.                                       *
    *----------------last changed: -----------------------------Fr 12. Aug 00:33:00 2005----------*/
void SetCreatorId(  long p_lUserId );
    public slots:
         /** +-=---------------------------------------------------------Mo 19. Nov 15:49:09 2012-------*
    * @method  CdmModelElement::GetModifierId                        // public, const, slots              *
    * @return  long                                          //                                   *
    * @comment returns the id of the modifier or 0 for system modifier.                           *
    *----------------last changed: -----------------------------Mo 19. Nov 15:49:09 2012----------*/
long GetModifierId( ) const;
   protected:
   /** +-=---------------------------------------------------------Fr 13. Sep 13:13:07 2013-------*
    * @method  CdmModelElement::SetKeyname                   // protected, virtual                *
    * @return  void                                          //                                   *
    * @param   QString p_qstrKeyname                         //                                   *
    * @comment sets the keyname of this baseobject.                                               *
    *----------------last changed: -----------------------------Fr 13. Sep 13:13:07 2013----------*/
    virtual void SetKeyname(QString p_qstrKeyname);

   protected:
   /** +-=---------------------------------------------------------Mo 20. Jul 21:03:11 2009-------*
    * @method  CdmModelElement::SetNew                               // protected, virtual                *
    * @return  void                                          //                                   *
    * @comment This method sets the new flag on this base object.                                 *
    *----------------last changed: -----------------------------Mo 20. Jul 21:03:11 2009----------*/
    virtual void SetNew();
    public slots:
         /** +-=---------------------------------------------------------Mo 19. Nov 15:49:20 2012-------*
    * @method  CdmModelElement::IsNew                                // public, const, slots              *
    * @return  bool                                          //                                   *
    * @comment returns if this base object is new.                                                *
    *----------------last changed: -----------------------------Mo 19. Nov 15:49:20 2012----------*/
bool IsNew( ) const;
   public:
   /** +-=---------------------------------------------------------Fr 12. Aug 00:33:36 2005*
    * @method  CdmModelElement::ResetNewModified                     // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment This method resets the new and modified value at this base object. This is needed  *
    *          for after updating this object.                                                    *
    *----------------last changed: -----------------------------Fr 12. Aug 00:33:36 2005----------*/
virtual void ResetNewModified(  );
    public slots:
         /** +-=---------------------------------------------------------Mo 19. Nov 15:45:35 2012-------*
    * @method  CdmModelElement::GetId                                // public, const, slots              *
    * @return  long                                          //                                   *
    * @comment returns the Id of this base object.                                                *
    *----------------last changed: -----------------------------Mo 19. Nov 15:45:35 2012----------*/
long GetId( ) const;
   private:
   /** +-=---------------------------------------------------------Fr 12. Aug 00:31:19 2005*
    * @method  CdmModelElement::SetId                                // private                           *
    * @return  void                                          //                                   *
    * @param   long p_lId                                    //                                   *
    * @comment sets the Id of this base object.                                                   *
    *----------------last changed: -----------------------------Fr 12. Aug 00:31:19 2005----------*/
void SetId(  long p_lId );
    public slots:
         /** +-=---------------------------------------------------------Do 9. Mai 18:30:03 2013--------*
    * @method  CdmModelElement::IsModified                   // public, const, virtual, slots     *
    * @return  bool                                          //                                   *
    * @comment returns if an object is modified or not.                                           *
    *----------------last changed: -----------------------------Do 9. Mai 18:30:03 2013-----------*/
      virtual bool IsModified( ) const;

    public slots:
         /** +-=---------------------------------------------------------Mo 19. Nov 15:49:33 2012-------*
    * @method  CdmModelElement::SetCaption                           // public, slots                     *
    * @return  void                                          //                                   *
    * @param   QString p_qstrCaption                         //                                   *
    * @comment This method sets the caption of this baseobject.                                   *
    *----------------last changed: -----------------------------Mo 19. Nov 15:49:33 2012----------*/
void SetCaption( QString p_qstrCaption);

    public slots:
         /** +-=---------------------------------------------------------Sa 9. Feb 11:46:45 2013--------*
    * @method  CdmModelElement::GetCaption                   // public, const, virtual, slots     *
    * @return  QString                                       //                                   *
    * @comment This method returns the caption of this object.                                    *
    *----------------last changed: -----------------------------Sa 9. Feb 11:46:45 2013-----------*/
      virtual QString GetCaption( ) const;

   public:
   /** +-=---------------------------------------------------------Sa 9. Feb 11:47:12 2013--------*
    * @method  CdmModelElement::ChangeDateToLong             // public, static                    *
    * @return  long                                          //                                   *
    * @param   const QDate p_qdDate                          //                                   *
    * @comment This method changes a date to a long value. This long value means the number of    *
    *          days since 1.1.1900.                                                               *
    *----------------last changed: -----------------------------Sa 9. Feb 11:47:12 2013-----------*/
    static long ChangeDateToLong(const QDate p_qdDate);

   public:
   /** +-=---------------------------------------------------------Fr 12. Aug 00:34:21 2005*
    * @method  CdmModelElement::ChangeLongToDate                     // public, static                    *
    * @return  QDate                                         //                                   *
    * @param   long p_lDate                                  //                                   *
    * @comment This method converts a long value whixh contains the number of days sind 1.1.1970 to a valid qdate.*
    *----------------last changed: -----------------------------Fr 12. Aug 00:34:21 2005----------*/
static QDate ChangeLongToDate(  long p_lDate );

   public:
   /** +-=---------------------------------------------------------Fr 12. Aug 00:34:23 2005*
    * @method  CdmModelElement::ChangeTimeToDouble                   // public, static                    *
    * @return  double                                        //                                   *
    * @param   QTime p_qtTime                                //                                   *
    * @comment This method changes a qtime to a double. The double is a percentage value of the complete day.*
    *----------------last changed: -----------------------------Fr 12. Aug 00:34:23 2005----------*/
static double ChangeTimeToDouble(  QTime p_qtTime );

   public:
   /** +-=---------------------------------------------------------Fr 12. Aug 00:34:26 2005*
    * @method  CdmModelElement::ChangeDoubleToTime                   // public, static                    *
    * @return  QTime                                         //                                   *
    * @param   double p_dTime                                //                                   *
    * @comment This method changes a percentage double value to a time value.                     *
    *----------------last changed: -----------------------------Fr 12. Aug 00:34:26 2005----------*/
static QTime ChangeDoubleToTime(  double p_dTime );

   public:
   /** +-=---------------------------------------------------------So 10. Feb 18:25:16 2013-------*
    * @method  CdmModelElement::ChangeDateTimeToDouble       // public, const                     *
    * @return  double                                        //                                   *
    * @param   QDateTime p_qdtDateTime                       //                                   *
    * @comment This method changes a qdatetime value to a double. It uses the definition of the   *
    *          ChangeDateToLong and ChangeTimeToDouble methods.                                   *
    *----------------last changed: -----------------------------So 10. Feb 18:25:16 2013----------*/
    double ChangeDateTimeToDouble(QDateTime p_qdtDateTime) const;

   public:
   /** +-=---------------------------------------------------------Fr 12. Aug 00:34:32 2005*
    * @method  CdmModelElement::ChangeDoubleToDateTime               // public, static                    *
    * @return  QDateTime                                     //                                   *
    * @param   double p_dDateTime                            //                                   *
    * @comment This method changes a double value to a qdatetime value.                           *
    *----------------last changed: -----------------------------Fr 12. Aug 00:34:32 2005----------*/
static QDateTime ChangeDoubleToDateTime(  double p_dDateTime );

   public:
   /** +-=---------------------------------------------------------Sa 9. Feb 11:45:45 2013--------*
    * @method  CdmModelElement::GetLastChange                // public, const                     *
    * @return  void                                          //                                   *
    * @param   double& p_dLastChange                         //                                   *
    * @comment This method returns the last change date time in a double                          *
    *----------------last changed: -----------------------------Sa 9. Feb 11:45:45 2013-----------*/
    void GetLastChange(double& p_dLastChange) const;

   public:
   /** +-=---------------------------------------------------------Fr 12. Aug 00:31:45 2005*
    * @method  CdmModelElement::SetLastChange                        // public                            *
    * @return  void                                          //                                   *
    * @param   double p_dLastChanged                         //                                   *
    * @comment This method sets the lastchanged date time with a double                           *
    *----------------last changed: -----------------------------Fr 12. Aug 00:31:45 2005----------*/
void SetLastChange(  double p_dLastChanged );


   protected:
   /** +-=---------------------------------------------------------Sa 9. Feb 11:47:50 2013--------*
    * @method  CdmModelElement::XmlExportBase                // protected, const                  *
    * @return  void                                          //                                   *
    * @param   QDomElement& p_rqdeBase                       //                                   *
    * @comment exports the database to a xml file.                                                *
    *----------------last changed: -----------------------------Sa 9. Feb 11:47:50 2013-----------*/
    void XmlExportBase(QDomElement& p_rqdeBase) const;

   public:
   /** +-=---------------------------------------------------------Fr 12. Aug 00:34:42 2005*
    * @method  CdmModelElement::ChangeBoolToString                   // public, static                    *
    * @return  QString                                       //                                   *
    * @param   bool p_bValue                                 //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 12. Aug 00:34:42 2005----------*/
static QString ChangeBoolToString(  bool p_bValue );

   public:
   /** +-=---------------------------------------------------------Fr 12. Aug 00:34:45 2005*
    * @method  CdmModelElement::ChangeStringToBool                   // public, static                    *
    * @return  bool                                          //                                   *
    * @param   QString p_qstrBool                            //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Fr 12. Aug 00:34:45 2005----------*/
static bool ChangeStringToBool(  QString p_qstrBool );

   public:
   /** +-=---------------------------------------------------------Fr 12. Aug 00:30:51 2005*
    * @method  CdmModelElement::CdmModelElement                              // public                            *
    * @return                                                //                                   *
    * @param   QDomElement& p_rqDomElement                   //                                   *
    * @comment This method creates a base object with xml information                             *
    *----------------last changed: -----------------------------Fr 12. Aug 00:30:51 2005----------*/
CdmModelElement(  QDomElement& p_rqDomElement );

   protected:
   /** +-=---------------------------------------------------------Fr 12. Aug 00:34:39 2005*
    * @method  CdmModelElement::XmlImportBase                        // protected                         *
    * @return  void                                          //                                   *
    * @param   QDomElement& p_rqDomElement                   //                                   *
    * @comment This method imports the basedata of this base object from xml to object.           *
    *----------------last changed: -----------------------------Fr 12. Aug 00:34:39 2005----------*/
void XmlImportBase(  QDomElement& p_rqDomElement );

    public slots:
         /** +-=---------------------------------------------------------Sa 9. Feb 11:48:08 2013--------*
    * @method  CdmModelElement::GetInfo                      // public, const, virtual, slots     *
    * @return  QString                                       //                                   *
    * @comment returns the info to the current object.                                            *
    *----------------last changed: -----------------------------Sa 9. Feb 11:48:08 2013-----------*/
      virtual QString GetInfo( ) const;

   public:
   /** +-=---------------------------------------------------------Sa 9. Feb 11:48:21 2013--------*
    * @method  CdmModelElement::GetVariant                   // public, const, virtual            *
    * @return  QVariant                                      //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Sa 9. Feb 11:48:21 2013-----------*/
    virtual QVariant GetVariant() const;

   public:
   /** +-=---------------------------------------------------------So 15. Apr 13:08:14 2012-------*
    * @method  CdmModelElement::CdmModelElement                              // public                            *
    * @return                                                //                                   *
    * @param   QVariant p_qvVariant                          //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 15. Apr 13:08:14 2012----------*/
    CdmModelElement( QVariant p_qvVariant);


   protected:
   /** +-=---------------------------------------------------------Mo 3. Dez 14:56:50 2012--------*
    * @method  CdmModelElement::SetVariant                   // protected, virtual                *
    * @return  void                                          //                                   *
    * @param   QVariantMap& p_rqvHash                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 3. Dez 14:56:50 2012-----------*/
    virtual void SetVariant(QVariantMap& p_rqvHash);


   public:
   /** +-=---------------------------------------------------------Mi 12. Sep 15:22:13 2012-------*
    * @method  CdmModelElement::GetDisplayTypeAsString               // public, static                    *
    * @return  QString                                       //                                   *
    * @param   EdmStringDisplayType p_eType                  //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mi 12. Sep 15:22:13 2012----------*/
    static QString GetDisplayTypeAsString(EdmStringDisplayType p_eType);



protected:
    QString GetUriType() const;

public slots:
         /** +-=---------------------------------------------------------Sa 9. Feb 11:48:48 2013--------*
    * @method  CdmModelElement::GetUri                       // public, const, virtual, slots     *
    * @return  QString                                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Sa 9. Feb 11:48:48 2013-----------*/
     virtual QString GetUri( ) const;

   protected:
   /** +-=---------------------------------------------------------Mo 3. Dez 14:56:57 2012--------*
    * @method  CdmModelElement::Deploy                       // protected, virtual                *
    * @return  void                                          //                                   *
    * @param   QVariantMap& p_rqvHash                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 3. Dez 14:56:57 2012-----------*/
    virtual void Deploy(QVariantMap& p_rqvHash);

    bool HasUserDeleteAccess();
public:
     static bool CheckKeyname(QString p_qstrKeyname);
     QString GenerateKeyname() const;
     CdmModelElement();
     QString GetOriginalKeyname() const;
     virtual bool IsModelElement() const;
     QString GetUriInternal() const;
};

#endif // //CDMBASE_H
