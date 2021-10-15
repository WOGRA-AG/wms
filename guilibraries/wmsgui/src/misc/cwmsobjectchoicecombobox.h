#ifndef CWMSOBJECTCHOICECOMBOBOX_H
#define CWMSOBJECTCHOICECOMBOBOX_H


#ifdef WURZELBLA
#define slots
#endif //

// System and Qt Includes
#include <qcombobox.h>
#include <qmap.h>
#include <QKeyEvent>
#include <QList>


// own Includes
#include "CdmContainerAdaptor.h"
#include "wmsgui.h"


// forwards
class CdmObject;
class CdmObjectContainer;
class CdmEnhancedQueryProxy;


class WMSGUI_API CwmsObjectChoiceComboBox : public QComboBox, public CdmContainerAdaptor
{
   Q_OBJECT

private:
   CdmEnhancedQueryProxy* m_rpCdmProxy;
   QMap<QString,qint64> m_qmEntries; // <entry index, Objectid>
   QString m_qstrDisplayName;

public:
   CwmsObjectChoiceComboBox(QWidget* parent = NULL);
   virtual ~CwmsObjectChoiceComboBox();
   void SetContainerAndDisplayValue(CdmObjectContainer* p_pContainer, QString p_qstrValueKeyname);
   void SetContainerAndDisplayFilteredValue(CdmObjectContainer* p_pContainer, QString p_qstrValueKeyname, QString qstrFilter);
   void SetContainerAndDisplayValueByWql(CdmObjectContainer* p_pContainer, QString qstrWql);
   void SetCurrentObject(CdmObject* p_pCdmObject);
   void SetProxy(CdmEnhancedQueryProxy* p_pCdmProxy);
   void AddEntry(CdmObject* p_pCdmObject, QString p_qstrValue);
   void FillEntries();
   void FillWidget(CdmQuery& p_rcCdmQuery);
   void AddEntry(qint64 p_lObjectId, QString p_qstrValue);
   void SetContainerAndDisplayValue(QString p_qstrObjectListKeyname, QString p_qstrValueKeyname);
   void SetCurrentObjectId(qint64 p_lId);
  qint64 GetSelectedObjectId();
   void ClearEntries();
   void FillProxyData();
   CdmObject* GetSelectedObject();

   void SetContainerAndDisplayValueByWql(QString qstrWql);
   CdmObject *GetSelectedObjectByIndex(int iIndex);
public slots:
   void Refresh();

protected:
   void ObjectRefModifiedEvent(qint64 p_lObjectId);
   virtual void ObjectModifiedEvent(qint64 p_lObjectId);
   virtual void ObjectCreatedEvent(qint64 p_lObjectId);
   virtual void ObjectDeletedEvent(qint64 p_lObjectId);
   virtual void ObjectCommitedEvent(qint64 p_lObjectId);

private slots:
   void ComboBoxActivatedSlot();
   void TextChangedSlot();


signals:
   void ObjectSelectedSignal(CdmObject*);
   void ObjectSelectedSignal();
   void PlusPressedSignal();
   void MinusPressedSignal();
   void DivisionPressedSignal();
   void MultiplyPressedSignal();

private:
   void FillDialog(CdmObjectContainer* p_pContainer, QString p_qstrValueKeyname);
   void FillDialog(CdmObjectContainer* p_pContainer,
                   QString p_qstrValueKeyname,
                   QList<qint64>& p_rqvlObjects);

   void keyPressEvent(QKeyEvent * p_pqKeyEvent);
   int FindIndexById(qint64 p_lObjectId);
};

#endif //
