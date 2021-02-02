/******************************************************************************
 ** WOGRA Middleware Server Data Manager Module
 **
 ** @Author Wolfgang Graßhof 
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies All rights reserved
 ******************************************************************************/


#ifndef CUMACCESSORRIGHT_H
#define CUMACCESSORRIGHT_H

// System and QT Includes
#include <QVariant>

// own Includes
#include "../../Src/DataManagement/datamanager.h"


// forwards
class QDomElement;
class CumAccessor;


// Enumerations
enum EumAccessRight
{
   eUmAccessRightNone,
    eUmAccessRightRead,
    eUmAccessRightWrite,
};

/*
 * This class implements the rights of an accessor
 * read, or read and write
 */
class WMSMANAGER_API CumAccessorRight
{
   private:
      /*
       * The Accessor Id
       */
      long           m_lAccessorId;

      /*
       * The right of the accessor
       */
      EumAccessRight m_eUmAccessRight;


   public:
   /** +-=---------------------------------------------------------Sa 20. Aug 11:21:11 2005*
    * @method  CumAccessorRight::CumAccessorRight            // public                            *
    * @return                                                //                                   *
    * @comment The cosntructor of accessor rights.                                                *
    *----------------last changed: -----------------------------Sa 20. Aug 11:21:11 2005----------*/
CumAccessorRight(  );
   public:
   /** +-=---------------------------------------------------------Sa 20. Aug 12:49:32 2005*
    * @method  CumAccessorRight::~CumAccessorRight           // public, virtual                   *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CumAccessorRight                                           *
    *----------------last changed: -----------------------------Sa 20. Aug 12:49:32 2005----------*/
virtual ~CumAccessorRight(  );
   public:
   /** +-=---------------------------------------------------------So 10. Feb 11:44:08 2013-------*
    * @method  CumAccessorRight::HasReadAccess               // public, const                     *
    * @return  bool                                          //                                   *
    * @comment This method checks if the user has the right to access this objectlist.            *
    *----------------last changed: -----------------------------So 10. Feb 11:44:08 2013----------*/
    bool HasReadAccess() const;
   public:
   /** +-=---------------------------------------------------------So 10. Feb 11:44:16 2013-------*
    * @method  CumAccessorRight::HasWriteAccess              // public, const                     *
    * @return  bool                                          //                                   *
    * @comment This method checks if this user has write access to the objectlist.                *
    *----------------last changed: -----------------------------So 10. Feb 11:44:16 2013----------*/
    bool HasWriteAccess() const;

   public:
   /** +-=---------------------------------------------------------Sa 20. Aug 11:21:22 2005*
    * @method  CumAccessorRight::CumAccessorRight            // public                            *
    * @return                                                //                                   *
    * @param   long p_lAccessorId                            //                                   *
    * @param   EumAccessRight p_eUmAccessRight               //                                   *
    * @comment The cosntructor of accessor rights.                                                *
    *----------------last changed: -----------------------------Sa 20. Aug 11:21:22 2005----------*/
CumAccessorRight(  long p_lAccessorId, EumAccessRight p_eUmAccessRight );

   public:
   /** +-=---------------------------------------------------------So 10. Feb 11:44:33 2013-------*
    * @method  CumAccessorRight::GetAccessRight              // public, const                     *
    * @return  EumAccessRight                                //                                   *
    * @comment returns the Access Right of this accessor.                                         *
    *----------------last changed: -----------------------------So 10. Feb 11:44:33 2013----------*/
    EumAccessRight GetAccessRight() const;

   public:
   /** +-=---------------------------------------------------------Sa 20. Aug 11:21:45 2005*
    * @method  CumAccessorRight::SetAccessRight              // public                            *
    * @return  void                                          //                                   *
    * @param   EumAccessRight p_eUmAccessRight               //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Sa 20. Aug 11:21:45 2005----------*/
void SetAccessRight(  EumAccessRight p_eUmAccessRight );

   public:
   /** +-=---------------------------------------------------------Sa 20. Aug 11:21:40 2005*
    * @method  CumAccessorRight::SetAccessorId               // public                            *
    * @return  void                                          //                                   *
    * @param   long p_lAccessorId                            //                                   *
    * @comment This method sets the accessorid of this accessorright.                             *
    *----------------last changed: -----------------------------Sa 20. Aug 11:21:40 2005----------*/
void SetAccessorId(  long p_lAccessorId );

   public:
   /** +-=---------------------------------------------------------So 10. Feb 11:44:25 2013-------*
    * @method  CumAccessorRight::GetAccessorId               // public, const                     *
    * @return  long                                          //                                   *
    * @comment This method returns the accessorid of this right.                                  *
    *----------------last changed: -----------------------------So 10. Feb 11:44:25 2013----------*/
    long GetAccessorId() const;

   public:
   /** +-=---------------------------------------------------------So 10. Feb 11:44:41 2013-------*
    * @method  CumAccessorRight::XmlExport                   // public, const                     *
    * @return  void                                          //                                   *
    * @param   QDomElement& p_rqdeAccessRights               //                                   *
    * @comment exports the database to a xml file.                                                *
    *----------------last changed: -----------------------------So 10. Feb 11:44:41 2013----------*/
    void XmlExport(QDomElement& p_rqdeAccessRights) const;

   public:
   /** +-=---------------------------------------------------------Mo 16. Apr 15:09:16 2012-------*
    * @method  CumAccessorRight::CumAccessorRight            // public                            *
    * @return                                                //                                   *
    * @param   QVariantMap& p_rqvHash                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------Mo 16. Apr 15:09:16 2012----------*/
    CumAccessorRight( QVariantMap& p_rqvHash);

   public:
   /** +-=---------------------------------------------------------So 10. Feb 11:44:00 2013-------*
    * @method  CumAccessorRight::GetVariant                  // public, const                     *
    * @return  QVariant                                      //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 10. Feb 11:44:00 2013----------*/
    QVariant GetVariant() const;
};
#endif // //CUMACCESSORRIGHT_H
