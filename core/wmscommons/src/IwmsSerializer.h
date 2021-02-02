/******************************************************************************
 ** WOGRA technologies Gmbh & Co KG Modul Information
 ** Modulename: IbmscomParser.h
 ** Started Implementation: 2012/04/09
 ** Description:
 ** 
 ** implements the interface for the parser.
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co KG All rights reserved
 *****************************************************************************/ 

#ifndef IWMSSERIALIZER_H
#define IWMSSERIALIZER_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes
#include <QVariant>

// Own Includes


// Forwards


// TypeDefs


/* 
 * This class implements the interface for the parser.
 */
class IwmsSerializer
{
   public:
    virtual ~IwmsSerializer(){}
      virtual QByteArray serialize(const QVariant &json) = 0;
};

#endif // IBMSCOMPARSER_H
