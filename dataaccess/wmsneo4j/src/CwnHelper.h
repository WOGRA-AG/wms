/******************************************************************************
 ** WOGRA technologies Gmbh & Co KG Modul Information
 ** Modulename: CdbHelper.h
 ** Started Implementation: 2012/08/30
 ** Description:
 **
 ** Helper class with static functions
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 **(C) copyright by WOGRA technologies GmbH & Co KG All rights reserved
 *****************************************************************************/

#ifndef CWNHELPER_H
#define CWNHELPER_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes
#include <QString>
#include <QDateTime>
#include <QVector>
#include <QMap>

// WMS Commons Includes
#include "CwmsUtilities.h"

// Own Includes
#include "CwnDataAccess.h"

// Forwards


// TypeDefs




/*
 * This classis a helper class with static functions
 */
class CwnHelper : public CwmsUtilities
{
public:
    static QString MakeValueSave(QString qstrValue);
    static QString MakeValueSaveForNotRegex(QString qstrValue);
    static QString base64_encode(QString data);
    static QString base64_decode(QString data);

};

#endif // CWNHELPER_H
