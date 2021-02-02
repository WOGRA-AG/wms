/******************************************************************************
 ** WOGRA technologies GmbH & Co. KG Modul Information
 ** Modulename: CwnHelper.cpp
 ** Started Implementation: 2012/08/30
 ** Description:
 **
 **
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 **(C) copyright by WOGRA technologies GmbH & Co. KG All rights reserved
 *****************************************************************************/

// System and QT Includes
#include <QByteArray>
#include <QBitArray>
#include <QString>
#include <QCryptographicHash>
// WMS Includes
#include "CdmLogging.h"

// own Includes
#include "CwnHelper.h"


QString CwnHelper::MakeValueSave(QString p_qstrValue)
{
    p_qstrValue = p_qstrValue.replace("^", "\\^");
    p_qstrValue = p_qstrValue.replace("$", "\\$");
    p_qstrValue = p_qstrValue.replace(".", "\\\\\\\\.");
    p_qstrValue = p_qstrValue.replace("*", "\\*");
    p_qstrValue = p_qstrValue.replace("+", "\\+");
    p_qstrValue = p_qstrValue.replace("?", "\\?");
    p_qstrValue = p_qstrValue.replace("(", "\\(");
    p_qstrValue = p_qstrValue.replace(")", "\\)");
    p_qstrValue = p_qstrValue.replace("[", "\\[");
    p_qstrValue = p_qstrValue.replace("]", "\\]");
    p_qstrValue = p_qstrValue.replace("{", "\\{");
    p_qstrValue = p_qstrValue.replace("}", "\\}");
    p_qstrValue = p_qstrValue.replace("|", "\\|");

    return p_qstrValue;
}

QString CwnHelper::MakeValueSaveForNotRegex(QString qstrValue)
{
    qstrValue = qstrValue.replace("^", "\\^");
    qstrValue = qstrValue.replace("$", "\\$");
    qstrValue = qstrValue.replace(".", "\\\\\\\\.");
    qstrValue = qstrValue.replace("*", "\\*");
    qstrValue = qstrValue.replace("+", "\\+");
    qstrValue = qstrValue.replace("?", "\\?");
    qstrValue = qstrValue.replace("(", "\\(");
    qstrValue = qstrValue.replace(")", "\\)");
    qstrValue = qstrValue.replace("[", "\\[");
    qstrValue = qstrValue.replace("]", "\\]");
    qstrValue = qstrValue.replace("{", "\\{");
    qstrValue = qstrValue.replace("}", "\\}");
    qstrValue = qstrValue.replace("|", "\\|");

    return qstrValue;

}

QString CwnHelper::base64_encode(QString data)
{
    QByteArray ba;
    ba.append(data);
    return ba.toBase64();

}

QString CwnHelper::base64_decode(QString data)
{
    QByteArray ba;
    ba.append(data);
    return QByteArray::fromBase64(ba);

}
