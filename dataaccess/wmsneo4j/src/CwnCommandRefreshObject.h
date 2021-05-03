#ifndef CWNCOMMANDREFRESHOBJECT_H
#define CWNCOMMANDREFRESHOBJECT_H

#include <QList>

#include "CwnCommandBase.h"
#include "CdmModelElement.h"

// Forwards
class CdmValueCharacterDocument;
class CdmObject;

class CwnCommandRefreshObject : public CwnCommandBase
{
private:
    CdmObject* m_rpObject;

    EdmValueType m_eType = eDmValueNone;

    CdmValueCharacterDocument *CreateCharDocValue(long p_lDatabaseId, long p_lId, QString p_qstrKeyname);

    long ReadValues();

    QString GetLoadAllObjectQuery();

    bool interpretAnswerForLoadObjects(const QVariantList *list);
    bool interpretAnswerForBools(const QVariantList *list);
    bool interpretAnswerForBinDoc(const QVariantList *list);
    bool interpretAnswerForCharDoc(const QVariantList *list);
    bool interpretAnswerForCounters(const QVariantList *list);
    bool interpretAnswerForDates(const QVariantList *list);
    bool interpretAnswerForDateTimes(const QVariantList *list);
    bool interpretAnswerForDoubles(const QVariantList *list);
    bool interpretAnswerForFloats(const QVariantList *list);
    bool interpretAnswerForInts(const QVariantList *list);
    bool interpretAnswerForLongs(const QVariantList *list);
    bool interpretAnswerForObjectRefs(const QVariantList *list);
    bool interpretAnswerForObjectListRefs(const QVariantList *list);
    bool interpretAnswerForStrings(const QVariantList *list);
    bool interpretAnswerForTimes(const QVariantList *list);

public:
    CwnCommandRefreshObject(CdmObject* p_pCdmObject, CwnDataAccess* p_pDataAccess);
    virtual ~CwnCommandRefreshObject();
    QString queryCausedError;

protected:
    void interpretAnswer(QVariant& Ret);
    virtual int Execute();
    virtual bool CheckValid();
};

#endif // CWNCOMMANDREFRESHOBJECT_H
