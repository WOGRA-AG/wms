/******************************************************************************
 ** WOGRA technologies Gmbh & Co KG Modul Information
 ** Modulename: CdbJournal.h
 ** Started Implementation: 2012/08/29
 ** Description:
 ** 
 ** implements the journal for wms
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co KG All rights reserved
 *****************************************************************************/ 

#ifndef CODBCJOURNAL_H
#define CODBCJOURNAL_H

#ifdef WURZELBLA
#define slots
#endif //

// Forwards
class CdbDataAccess;
class CdmJournalItem;
class CdmObject;
class CdmObjectContainer;
class CdmValue;

/*
 * This class implements the journal for wms
 */
class CdbJournal
{
   public:
    CdbJournal( CdbDataAccess*);
   qint64 ValueModified(CdmValue*);
   qint64 ObjectModified(CdmObject*);
   qint64 ObjectListModified(CdmObjectContainer*);
   qint64 GetDatabaseModifications(int p_iDatabaseId, QDate p_qdFrom, QDate p_qdTo, QList<CdmJournalItem*>& p_rqlItems);
   qint64 GetContainerModifications(int p_iObjectListId, QDate p_qdFrom, QDate p_qdTo, QList<CdmJournalItem*>& p_rqlItems);
   qint64 GetObjectModifications(const CdmObject *p_pObject, QDate p_qdFrom, QDate p_qdTo, QList<CdmJournalItem*>& p_rqlItems);
   qint64 ObjectListDeleted(int p_iObjectListId);
   qint64 ObjectDeleted(int p_iObjectId);

protected:
   CdbDataAccess* m_rpCdbDataAccess;
};

#endif // CODBCJOURNAL_H
