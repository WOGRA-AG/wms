﻿/******************************************************************************
 ** WOGRA technologies GmbH & Co. KG Modul Information
 ** Modulename: CwmsJson.cpp
 ** Started Implementation: 2012/09/06
 ** Description:
 **
 **
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co. KG All rights reserved
 *****************************************************************************/

// System and QT Includes
#include <QDate>
#include <QDateTime>
#include <QTime>


// own Includes
#include "CwmsJson.h"

/** +-=---------------------------------------------------------Mo 9. Apr 12:01:48 2012-----------*
 * @method  CwmsJson::CwmsJson                         // public                            *
 * @return                                                   //                                   *
 * @comment                                                                                       *
 *----------------last changed: --------------------------------Mo 9. Apr 12:01:48 2012-----------*/
CwmsJson::CwmsJson()
{

}

/** +-=---------------------------------------------------------Mo 9. Apr 12:01:55 2012-----------*
 * @method  CwmsJson::~CwmsJson                        // public, virtual                   *
 * @return  void                                             //                                   *
 * @comment The Destructor of Class CwmsJson                                                   *
 *----------------last changed: --------------------------------Mo 9. Apr 12:01:55 2012-----------*/
CwmsJson::~CwmsJson()
{

}

static QString sanitizeString(QString str)
{
   str.replace(QLatin1String("\\"), QLatin1String("\\\\"));
   str.replace(QLatin1String("\""), QLatin1String("\\\""));
   str.replace(QLatin1String("\b"), QLatin1String("\\b"));
   str.replace(QLatin1String("\f"), QLatin1String("\\f"));
   str.replace(QLatin1String("\n"), QLatin1String("\\n"));
   str.replace(QLatin1String("\r"), QLatin1String("\\r"));
   str.replace(QLatin1String("\t"), QLatin1String("\\t"));
   return QString(QLatin1String("\"%1\"")).arg(str);
}

static QByteArray join(const QList<QByteArray> &list, const QByteArray &sep)
{
   QByteArray res;
   Q_FOREACH(const QByteArray &i, list)
   {
      if(!res.isEmpty())
      {
         res += sep;
      }
      res += i;
   }
   return res;
}

/**
* parse
*/
QVariant CwmsJson::parse(const QString &json)
{
   bool success = true;
   return CwmsJson::parse(json, success);
}

/**
* parse
*/
QVariant CwmsJson::parse(const QString &json, bool &success)
{
   success = true;

   //Return an empty QVariant if the JSON data is either nullptr or empty
   if(!json.isNull() || !json.isEmpty())
   {
      QString data = json;
      //We'll start from index 0
      int index = 0;

      //Parse the first value
      QVariant value = CwmsJson::parseValue(data, index, success);

      //Return the parsed value
      return value;
   }
   else
   {
      //Return the empty QVariant
      return QVariant();
   }
}

QByteArray CwmsJson::serialize(const QVariant &data)
{
   bool success = true;
   return CwmsJson::serialize(data, success);
}

QByteArray CwmsJson::serialize(const QVariant &data, bool &success)
{
   QByteArray str;
   success = true;
   if(!data.isValid()) // invalid or NULL?
   {
      str = "NULL";
   }
   else if((data.type() == QVariant::List) || (data.type() == QVariant::StringList)) // variant is a list?
   {
      QList<QByteArray> values;
      const QVariantList list = data.toList();
      Q_FOREACH(const QVariant& v, list)
      {
         QByteArray serializedValue = serialize(v);
         if(serializedValue.isNull())
         {
            success = false;
            break;
         }
         values << serializedValue;
      }

      str = "[ " + join( values, ", " ) + " ]";
   }
   else if(data.type() == QVariant::Map) // variant is a map?
   {
      const QVariantMap vmap = data.toMap();
      QMapIterator<QString, QVariant> it( vmap );
      str = "{ ";
      QList<QByteArray> pairs;
      while(it.hasNext())
      {
         it.next();
         QByteArray serializedValue = serialize(it.value());
         if(serializedValue.isNull())
         {
            success = false;
            break;
         }
         pairs << sanitizeString(it.key()).toUtf8() + " : " + serializedValue;
      }
      str += join(pairs, ", ");
      str += " }";
   }
   else if((data.type() == QVariant::String) || (data.type() == QVariant::ByteArray)) // a string or a byte array?
   {
      str = sanitizeString(data.toString()).toUtf8();
   }
   else if(data.type() == QVariant::Double) // double?
   {
      str = QByteArray::number(data.toDouble(), 'f', 15);
      if(!str.contains(".") && ! str.contains("e"))
      {
         str += ".0";
      }
   }
   else if (data.userType() == QMetaType::Float)
   {
       str = QByteArray::number(data.toFloat(), 'f', 15);
       if(!str.contains(".") && ! str.contains("e"))
       {
          str += ".0";
       }
   }
   else if (data.type() == QVariant::Bool) // boolean value?
   {
      str = data.toBool() ? "true" : "false";
   }
   else if (data.type() == QVariant::ULongLong) // large unsigned number?
   {
      str = QByteArray::number(data.value<qulonglong>());
   }
   else if ( data.canConvert<qlonglong>() ) // any signed number?
   {
      str = QByteArray::number(data.value<qlonglong>());
   }
   else if (data.canConvert<qint64>())
   {
      str = QString::number(data.value<qint64>()).toUtf8();
   }
   else if (data.type() == QVariant::Date)
   {
       str = sanitizeString(data.toDate().toString(Qt::ISODate)).toUtf8();
   }
   else if (data.type() == QVariant::DateTime)
   {
       str = sanitizeString(data.toDateTime().toString(Qt::ISODate)).toUtf8();
   }
   else if (data.type() == QVariant::Time)
   {
       str = sanitizeString(data.toTime().toString(Qt::ISODate)).toUtf8();
   }
   else if (data.canConvert<QString>()) // can value be converted to string?
   {
      // this will catch QUrl, ...
      str = sanitizeString(data.toString()).toUtf8();
   }
   else
   {
      success = false;
   }
   if (success)
   {
      return str;
   }
   else
   {
      return QByteArray();
   }
}

/**
* parseValue
*/
QVariant CwmsJson::parseValue(const QString &json, int &index, bool &success)
{
   //Determine what kind of data we should parse by
   //checking out the upcoming token
   switch(CwmsJson::lookAhead(json, index))
   {
   case JsonTokenString:
      return CwmsJson::parseString(json, index, success);
   case JsonTokenNumber:
      return CwmsJson::parseNumber(json, index);
   case JsonTokenCurlyOpen:
      return CwmsJson::parseObject(json, index, success);
   case JsonTokenSquaredOpen:
      return CwmsJson::parseArray(json, index, success);
   case JsonTokenTrue:
      CwmsJson::nextToken(json, index);
      return QVariant(true);
   case JsonTokenFalse:
      CwmsJson::nextToken(json, index);
      return QVariant(false);
   case JsonTokenNull:
      CwmsJson::nextToken(json, index);
      return QVariant();
   case JsonTokenNone:
      break;
   }

   //If there were no tokens, flag the failure and return an empty QVariant
   success = false;
   return QVariant();
}

/**
* parseObject
*/
QVariant CwmsJson::parseObject(const QString &json, int &index, bool &success)
{
   QVariantMap map;
   int token;

   //Get rid of the whitespace and increment index
   CwmsJson::nextToken(json, index);

   //Loop through all of the key/value pairs of the object
   bool done = false;
   while(!done)
   {
      //Get the upcoming token
      token = CwmsJson::lookAhead(json, index);

      if(token == JsonTokenNone)
      {
         success = false;
         return QVariantMap();
      }
      else if(token == JsonTokenComma)
      {
         CwmsJson::nextToken(json, index);
      }
      else if(token == JsonTokenCurlyClose)
      {
         CwmsJson::nextToken(json, index);
         return map;
      }
      else
      {
         //Parse the key/value pair's name
         QString name = CwmsJson::parseString(json, index, success).toString();

         if(!success)
         {
            return QVariantMap();
         }

         //Get the next token
         token = CwmsJson::nextToken(json, index);

         //If the next token is not a colon, flag the failure
         //return an empty QVariant
         if(token != JsonTokenColon)
         {
            success = false;
            return QVariant(QVariantMap());
         }

         //Parse the key/value pair's value
         QVariant value = CwmsJson::parseValue(json, index, success);

         if(!success)
         {
            return QVariantMap();
         }

         //Assign the value to the key in the map
         map[name] = value;
      }
   }

   //Return the map successfully
   return QVariant(map);
}

/**
* parseArray
*/
QVariant CwmsJson::parseArray(const QString &json, int &index, bool &success)
{
   QVariantList list;

   CwmsJson::nextToken(json, index);

   bool done = false;
   while(!done)
   {
      int token = CwmsJson::lookAhead(json, index);

      if(token == JsonTokenNone)
      {
         success = false;
         return QVariantList();
      }
      else if(token == JsonTokenComma)
      {
         CwmsJson::nextToken(json, index);
      }
      else if(token == JsonTokenSquaredClose)
      {
         CwmsJson::nextToken(json, index);
         break;
      }
      else
      {
         QVariant value = CwmsJson::parseValue(json, index, success);

         if(!success)
         {
            return QVariantList();
         }

         list.push_back(value);
      }
   }

   return QVariant(list);
}

/**
* parseString
*/
QVariant CwmsJson::parseString(const QString &json, int &index, bool &success)
{
   QString s;
   QChar c;

   CwmsJson::eatWhitespace(json, index);

   c = json[index++];

   bool complete = false;
   while(!complete)
   {
      if(index == json.size())
      {
         break;
      }

      c = json[index++];

      if(c == '\"')
      {
         complete = true;
         break;
      }
      else if(c == '\\')
      {
         if(index == json.size())
         {
            break;
         }

         c = json[index++];

         if(c == '\"')
         {
            s.append('\"');
         }
         else if(c == '\\')
         {
            s.append('\\');
         }
         else if(c == '/')
         {
            s.append('/');
         }
         else if(c == 'b')
         {
            s.append('\b');
         }
         else if(c == 'f')
         {
            s.append('\f');
         }
         else if(c == 'n')
         {
            s.append('\n');
         }
         else if(c == 'r')
         {
            s.append('\r');
         }
         else if(c == 't')
         {
            s.append('\t');
         }
         else if(c == 'u')
         {
            int remainingLength = json.size() - index;

            if(remainingLength >= 4)
            {
               QString unicodeStr = json.mid(index, 4);

               int symbol = unicodeStr.toInt(0, 16);

               s.append(QChar(symbol));

               index += 4;
            }
            else
            {
               break;
            }
         }
      }
      else
      {
         s.append(c);
      }
   }

   if(!complete)
   {
      success = false;
      return QVariant();
   }

   return QVariant(s);
}

/**
* parseNumber
*/
QVariant CwmsJson::parseNumber(const QString &json, int &index)
{
   CwmsJson::eatWhitespace(json, index);
   int lastIndex = CwmsJson::lastIndexOfNumber(json, index);
   int charLength = (lastIndex - index) + 1;
   QString numberStr;

   numberStr = json.mid(index, charLength);

   index = lastIndex + 1;

   if (numberStr.contains('.')) {
      return QVariant(numberStr.toDouble(nullptr));
   } else if (numberStr.startsWith('-')) {
      return QVariant(numberStr.toLongLong(nullptr));
   } else {
      return QVariant(numberStr.toULongLong(nullptr));
   }
}

/**
* lastIndexOfNumber
*/
int CwmsJson::lastIndexOfNumber(const QString &json, int index)
{
   int lastIndex;

   for(lastIndex = index; lastIndex < json.size(); lastIndex++)
   {
      if(QString("0123456789+-.eE").indexOf(json[lastIndex]) == -1)
      {
         break;
      }
   }

   return lastIndex -1;
}

/**
* eatWhitespace
*/
void CwmsJson::eatWhitespace(const QString &json, int &index)
{
   for(; index < json.size(); index++)
   {
      if(QString(" \t\n\r").indexOf(json[index]) == -1)
      {
         break;
      }
   }
}

/**
* lookAhead
*/
int CwmsJson::lookAhead(const QString &json, int index)
{
   int saveIndex = index;
   return CwmsJson::nextToken(json, saveIndex);
}

/**
* nextToken
*/
int CwmsJson::nextToken(const QString &json, int &index)
{
   CwmsJson::eatWhitespace(json, index);

   if(index == json.size())
   {
      return JsonTokenNone;
   }

   QChar c = json[index];
   index++;
   switch(c.toLatin1())
   {
   case '{': return JsonTokenCurlyOpen;
   case '}': return JsonTokenCurlyClose;
   case '[': return JsonTokenSquaredOpen;
   case ']': return JsonTokenSquaredClose;
   case ',': return JsonTokenComma;
   case '"': return JsonTokenString;
   case '0': case '1': case '2': case '3': case '4':
   case '5': case '6': case '7': case '8': case '9':
   case '-': return JsonTokenNumber;
   case ':': return JsonTokenColon;
   }

   index--;

   int remainingLength = json.size() - index;

   //True
   if(remainingLength >= 4)
   {
      if (json[index] == 't' && json[index + 1] == 'r' &&
         json[index + 2] == 'u' && json[index + 3] == 'e')
      {
         index += 4;
         return JsonTokenTrue;
      }
   }

   //False
   if (remainingLength >= 5)
   {
      if (json[index] == 'f' && json[index + 1] == 'a' &&
         json[index + 2] == 'l' && json[index + 3] == 's' &&
         json[index + 4] == 'e')
      {
         index += 5;
         return JsonTokenFalse;
      }
   }

   //nullptr
   if (remainingLength >= 4)
   {
      if (json[index] == 'n' && json[index + 1] == 'u' &&
         json[index + 2] == 'l' && json[index + 3] == 'l')
      {
         index += 4;
         return JsonTokenNull;
      }
   }

   return JsonTokenNone;
}
