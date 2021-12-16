#ifndef CWMSOBJECTSELECTIONIF_H
#define CWMSOBJECTSELECTIONIF_H


// System and QT Includes
#include <QDialog>


// WMS Includes
#include "CdmQueryModel.h"

// own Includes

#include "wmsgui.h"
#include "ui_CwmsObjectSelection.h"


// forwards
class CdmEnhancedQueryProxy;



class WMSGUI_API CwmsObjectSelectionIf : public QDialog, public Ui::CwmsObjectSelection
{
    Q_OBJECT

private:
    QString m_qstrDisplayMember;
    CdmQueryModel m_cModel;

public:
    virtual ~CwmsObjectSelectionIf(  );
    CdmObject* GetSelectedObject(  );
    void SetContainer(  CdmObjectContainer* p_pContainer );
    static CdmObject* GetObject(CdmObjectContainer* p_pContainer,
                                CdmEnhancedQueryProxy* p_pCwmsProxy,
                                QWidget* p_pqwParent,
                                QString p_qstrDisplayMember = "");
    void SetProxy(CdmEnhancedQueryProxy* p_pCwmsProxy);
   qint64 GetSelectedObjectId();
    static qint64 GetObjectId(CdmObjectContainer* p_pContainer,
                            CdmEnhancedQueryProxy* p_pCwmsProxy,
                            QWidget* p_pqwParent);
    void SetDisplayMember(QString p_qstrMember);
    bool SetWql(QString p_qstrWql);
    static CdmObject* GetObject(QString p_qstrWql, QWidget* p_pqwParent);

    static QList<CdmObject *> GetListofObjects(CdmObjectContainer *p_pContainer, CdmEnhancedQueryProxy *p_pCwmsProxy, QWidget *p_pqwParent, QString p_qstrDisplayMember);
    QList<CdmObject *> GetSelectedListOfObject();
private:
    CwmsObjectSelectionIf(QWidget* parent = NULL);
    CdmMember *getReferencedClassMemberForEvent(qint64 lReferencedClassId, CdmClassManager *pClassManager);

};


#endif //
