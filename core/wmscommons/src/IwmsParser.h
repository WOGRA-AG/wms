/******************************************************************************
 ** WOGRA technologies Gmbh & Co KG Modul Information
 ** Modulename: IbmscomSerializer.h
 ** Started Implementation: 2012/04/09
 ** Description:
 ** 
 ** Implements the serializes for the handler
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co KG All rights reserved
 *****************************************************************************/ 

#ifndef IWMSPARSER_H
#define IWMSPARSER_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes
#include <QByteArray>
#include <QVariant>

// Own Includes


// Forwards


// TypeDefs


/* 
 * This class implements the serializes for the handler
 */
class IwmsParser
{
   public:
      virtual ~IwmsParser(){}
      virtual QVariant parse(const QString &data) = 0;
};

#endif // IBMSCOMSERIALIZER_H
