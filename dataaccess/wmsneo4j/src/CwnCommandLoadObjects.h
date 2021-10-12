#ifndef CWNCOMMANDLOADOBJECTS_H
#define CWNCOMMANDLOADOBJECTS_H

#include <QList>

#include "CwnCommandBase.h"
#include "CdmModelElement.h"

// Forwards
class CdmValueCharacterDocument;
class CdmObjectContainer;

class CwnCommandLoadObjects : public CwnCommandBase
{
private:
    CdmObjectContainer* m_rpContainer;
    QList<qint64> &m_qvlObjectIds;
    QMap<qint64, CdmObject*> qmObjects;
    QString qstrObjectInString;
    QMap<CdmObject*, QDateTime> qmLastChange;

    EdmValueType m_eType = eDmValueNone;

    CdmValueCharacterDocument *CreateCharDocValue(qint64 p_lDatabaseId,qint64 p_lId, QString p_qstrKeyname, CdmObject *p_pCdmObjectOwner);

   qint64 ReadValues();

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
    CwnCommandLoadObjects(CdmObjectContainer* p_pContainer, QList<qint64> &p_qlObjectIds, CwnDataAccess* p_pDataAccess);
    virtual ~CwnCommandLoadObjects();
    QString queryCausedError;

protected:
    void interpretAnswer(QVariant& Ret);
    virtual int Execute();
    virtual bool CheckValid();
};

#endif // CWNCOMMANDLOADOBJECTS_H
