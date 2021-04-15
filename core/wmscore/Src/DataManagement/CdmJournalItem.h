/******************************************************************************
 ** WOGRA technologies Gmbh & Co KG Modul Information
 ** Modulename: CdmJournalItem.h
 ** Started Implementation: 2012/08/29
 ** Description:
 **
 ** implements the item of a change on a dataobject
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 **(C) copyright by WOGRA technologies GmbH & Co KG All rights reserved
 *****************************************************************************/

#ifndef CDMJOURNALITEM_H
#define CDMJOURNALITEM_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes
#include <QString>
#include <QDateTime>
#include <QObject>
#include <QVariant>

// Own Includes
#include "datamanager.h"

// Forwards
class CdmObject;

// TypeDefs

// enums
enum EdmChangeMode
{
    eDmChangeModeNew,
    eDmChangeModeModified,
    eDmChangeModeDeleted
};


/* 
 * This class implements the item of a change on a dataobject
 */
class WMSMANAGER_API CdmJournalItem : public QObject
{
    Q_OBJECT

private:
    int       m_iUserId;
    int       m_iSessionId;
    QDateTime m_qdtModified;
    EdmChangeMode m_eChangeMode;
    int       m_iObjectId;
    int       m_iContainerId;
    int       m_iMemberId;
    QString   m_qstrChanges;
    QString   m_qstrDisplayString;

public:
    CdmJournalItem( );
    CdmJournalItem( QVariantMap& p_rqvHash);
    QVariantMap GetVariant() const;
    void SetUserId(int p_iUserId);
    void SetSessionId(int p_iSessionId);
    void SetModified(QDateTime p_qdModified);
    void SetChangeMode(EdmChangeMode p_eMode);
    void SetObjectId(int p_iId);
    void SetObjectListId(int p_iId);
    void SetMemberId(int p_iId);
    void SetChanges(QString p_qstrChanges);
    void SetDisplayString(QString p_qstrValue);
    void RestoreValue();

public slots:
    int GetUserId( ) const;
    int GetSessionId( ) const;
    QDateTime GetModified( ) const;
    EdmChangeMode GetChangeMode( ) const;
    int GetObjectId( ) const;
    int GetObjectListId( ) const;
    int GetMemberId( ) const;
    QString GetChanges( ) const;
    QString GetDisplayString( ) const;
    QString GetUserString( ) const;
    QString GetChangeModeAsString( ) const;
    QString GetMemberAsString( CdmObject* p_pCdmObject) const;
};

#endif // CDMJOURNALITEM_H
