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
    long ValueModified(CdmValue*);
    long ObjectModified(CdmObject*);
    long ObjectListModified(CdmObjectContainer*);
    long GetDatabaseModifications(int p_iDatabaseId, QDate p_qdFrom, QDate p_qdTo, QList<CdmJournalItem*>& p_rqlItems);
    long GetContainerModifications(int p_iObjectListId, QDate p_qdFrom, QDate p_qdTo, QList<CdmJournalItem*>& p_rqlItems);
    long GetObjectModifications(int p_iObjectId, QDate p_qdFrom, QDate p_qdTo, QList<CdmJournalItem*>& p_rqlItems);
    long ObjectListDeleted(int p_iObjectListId);
    long ObjectDeleted(int p_iObjectId);

protected:
   CdbDataAccess* m_rpCdbDataAccess;
};

#endif // CODBCJOURNAL_H
