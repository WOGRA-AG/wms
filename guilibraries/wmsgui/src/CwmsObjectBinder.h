#ifndef CWMSOBJECTBINDER_H
#define CWMSOBJECTBINDER_H

#include "CdmObjectAdaptor.h"

#include "wmsgui.h"

class CdmValueInt;
class CdmValueLong;
class CdmValueFloat;
class CdmValueDouble;
class CdmValueEnum;
class CdmValueBool;
class CdmValueString;
class CdmValueTime;
class CdmValueDate;
class CdmValueDateTime;
class CdmValueCharacterDocument;
class CdmValueCounter;
class CdmValueFormula;
class CdmValueUser;
class CdmValueUserGroup;
class CdmValueObjectRef;

class QLabel;


class WMSGUI_API CwmsObjectBinder
{
private:
    CdmObjectAdaptor m_cObjectAdaptor;
    QMap<QWidget*,QString> m_qmBindings;
    bool m_bUseLableForCaption;

public:
    CwmsObjectBinder(CdmObject* p_pObject);
    virtual ~CwmsObjectBinder();
    void BindValue(QWidget* p_pqwWidget);
    void BindValue(QString p_qstrValue, QWidget *p_pqwWidget);
    void FillData();
    void RefreshValue(QString& p_qstrMemberName);
    void SaveData();
    void SetUseLabelForCaption(bool p_bFlag);
    bool GetUseLabelForCaption();
    CdmObject* GetObject();
    void SetObject(CdmObject* p_pObject);
    CdmObject *GetSelectedObject(QWidget *p_pWidget, QString p_qstrKeyname);
    void UpdateDataWithoutCommit();
    void CommitChanges();
    void BindWidgetHierarchy(QWidget *p_pqwWidget);
    static CdmObject *SearchValueObject(CdmValueObjectRef *p_pValue, QString qstrValue);

private:
    void FillData(QString p_qstrValue, QWidget *p_pqwWidget);
    void FillData(CdmValueInt *p_pValue, QWidget *p_pWidget);
    void FillData(CdmValueLong *p_pValue, QWidget *p_pWidget);
    void FillData(CdmValueFloat *p_pValue, QWidget *p_pWidget);
    void FillData(CdmValueDouble *p_pValue, QWidget *p_pWidget);
    void FillData(CdmValueEnum *p_pValue, QWidget *p_pWidget);
    void FillData(CdmValueBool *p_pValue, QWidget *p_pWidget);
    void FillData(CdmValueString *p_pValue, QWidget *p_pWidget);
    void FillData(CdmValueTime *p_pValue, QWidget *p_pWidget);
    void FillData(CdmValueDate *p_pValue, QWidget *p_pWidget);
    void FillData(CdmValueDateTime *p_pValue, QWidget *p_pWidget);
    void FillData(CdmValueCharacterDocument *p_pValue, QWidget *p_pWidget);
    void FillData(CdmValueCounter *p_pValue, QWidget *p_pWidget);
    void FillData(CdmValueFormula *p_pValue, QWidget *p_pWidget);
    void FillData(CdmValueUser *p_pValue, QWidget *p_pWidget);
    void FillData(CdmValueUserGroup *p_pValue, QWidget *p_pWidget);
    void FillData(CdmValueObjectRef *p_pValue, QWidget *p_pWidget);

    void SaveData(CdmValueInt *p_pValue, QWidget *p_pWidget);
    void SaveData(CdmValueLong *p_pValue, QWidget *p_pWidget);
    void SaveData(CdmValueFloat *p_pValue, QWidget *p_pWidget);
    void SaveData(CdmValueDouble *p_pValue, QWidget *p_pWidget);
    void SaveData(CdmValueEnum *p_pValue, QWidget *p_pWidget);
    void SaveData(CdmValueBool *p_pValue, QWidget *p_pWidget);
    void SaveData(CdmValueString *p_pValue, QWidget *p_pWidget);
    void SaveData(CdmValueTime *p_pValue, QWidget *p_pWidget);
    void SaveData(CdmValueDate *p_pValue, QWidget *p_pWidget);
    void SaveData(CdmValueDateTime *p_pValue, QWidget *p_pWidget);
    void SaveData(CdmValueCharacterDocument *p_pValue, QWidget *p_pWidget);
    void SaveData(CdmValueUser *p_pValue, QWidget *p_pWidget);
    void SaveData(CdmValueUserGroup *p_pValue, QWidget *p_pWidget);
    void SaveData(QString p_qstrValue, QWidget *p_pqwWidget);
    void SaveData(CdmValueObjectRef *p_pValue, QWidget *p_pWidget);
    void FillLabelData(CdmValue *p_pValue, QLabel *p_pWidget);
    bool IsReadOnly(CdmValue *p_pValue);
    bool IsAccessible(CdmValue *p_pValue);
    bool IsChangeable(CdmValue *p_pValue);

};

#endif // CWMSOBJECTBINDER_H
