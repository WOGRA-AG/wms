#ifndef CWNJOURNAL_H
#define CWNJOURNAL_H

#ifdef WURZELBLA
#define slots
#endif

// System and QT Includes

#include <QString>

#include "CwnCommandBase.h"
#include "CdmValue.h"
#include "CdmObject.h"
#include "CdmObjectContainer.h"

// Own Includes

// Forwards
class CdmValue;
class CwnDataAccess;
class CdmJournalItem;

class CwnJournal : public CwnCommandBase
{

private:
   QString qstrQuery;
   // switcher ObjectModifications=1,ObjectListModifications=2,GetDataBaseModifications=3
   int Execute(QList<CdmJournalItem*>& p_rqlItems);
   void interpretAnswer(QVariant &Ret, QList<CdmJournalItem*>& p_rqlItems);
   QString queryCausedError;

public:
    CwnJournal(CwnDataAccess *m_rpDataAccess);
    virtual ~CwnJournal();
    long ValueModified(CdmValue* p_pCdmValue);
    long ObjectDeleted(int p_iObjectId);
    long ObjectModified(CdmObject* p_pCdmObject);
    long ObjectListModified(CdmObjectContainer* p_pContainer);
    long ObjectListDeleted(int p_iObjectListId);
    long GetObjectModifications(int p_iObjectId,
                                QDate p_qdFrom,
                                QDate p_qdTo,
                                QList<CdmJournalItem*>& p_rqlItems);
    long GetObjectListModifications(int p_iObjectListId,
                                    QDate p_qdFrom,
                                    QDate p_qdTo,
                                    QList<CdmJournalItem*>& p_rqlItems);
    long GetSchemeModifications(int p_iDatabaseId, QDate p_qdFrom, QDate p_qdTo, QList<CdmJournalItem*>& p_rqlItems);



protected:
    /*
    * The dataaccess
    */
    CwnDataAccess* m_rpCwnDataAccess;
    virtual int Execute();
    void interpretAnswer(QVariant &Ret);
    virtual bool CheckValid();
};

#endif // CWNJOURNAL_H
