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
   qint64 ValueModified(CdmValue* p_pCdmValue);
   qint64 ObjectDeleted(int p_iObjectId);
   qint64 ObjectModified(CdmObject* p_pCdmObject);
   qint64 ObjectListModified(CdmObjectContainer* p_pContainer);
   qint64 ObjectListDeleted(int p_iObjectListId);
   qint64 GetObjectModifications(int p_iObjectId,
                                QDate p_qdFrom,
                                QDate p_qdTo,
                                QList<CdmJournalItem*>& p_rqlItems);
   qint64 GetObjectListModifications(int p_iObjectListId,
                                    QDate p_qdFrom,
                                    QDate p_qdTo,
                                    QList<CdmJournalItem*>& p_rqlItems);
   qint64 GetSchemeModifications(int p_iDatabaseId, QDate p_qdFrom, QDate p_qdTo, QList<CdmJournalItem*>& p_rqlItems);



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
