/******************************************************************************
 ** WOGRA Middleware Server Data Manager Module
 **
 ** @Author Wolfgang Graßhof
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 **(C) copyright by WOGRA technologies All rights reserved
 ******************************************************************************/

#ifndef CSAQUERY_H
#define CSAQUERY_H

// System and Qt Includes
#include <QVector>

// own Includes
#include "datamanager.h"
#include "CsaLocatedElement.h"

// forwards
class CsaObjectContainer;
class CsaObject;
class CsaScheme;
class CdmQueryEnhanced;
class CdmQuery;


class WMSMANAGER_API CsaQuery : public CsaLocatedElement
{
   Q_OBJECT

    friend class CsaFactory;

private:
    CsaQuery();
    ~CsaQuery();
   CdmQuery* m_pQuery;


public:

   CdmQuery* getInternals();

public slots:
   bool containsGrouping();
   QObject* getObjectAt(int p_iIndex);
  qint64 getObjectIdAt(int p_iIndex);
   QString getResultAsStringAt(int p_iIndex);
   QVariant getResultAt(QModelIndex& p_index);
   QVariant getResultAt(QString p_qstrKeyname, int p_iPos);
   QVariant getResultAt(int p_iColumn, int p_iRow);
   int getRowPosOfObjectInResultTree(qint64 p_lObjectId);
   bool isObjectInResultTree(qint64 p_lObejctId);
   void addGroupByElement(QString p_qstrElement);
   QObject *getFirstResultObject();
   int execute();
   void setContainer(CsaObjectContainer* p_pContainer);
   void clear();
   QObject* getContainer();
   void setContainerId(qint64 p_lId);
   const QVariantList getResultList();
   bool containsResultObject(CsaObject* p_pObject);
   bool containsResultObject(qint64 p_lObjectId);
   int getResultCount();
   int getColumnCount();
   QString getKeynameAt(int p_iSection);
   QVector<QString> getResultElements();
   void setQuery(CdmQuery* p_pEnhanced);
   // CsaLocatedElement interface
   QString getResultAsDisplayStringAt(int p_iColumn, int p_iRow);
public:
   virtual QVariant getDetailedVariant();

};


#endif


