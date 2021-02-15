/******************************************************************************
 ** WOGRA technologies Gmbh & Co KG Modul Information
 ** Modulename: CwmsQueryResultViewer.h
 ** Started Implementation: 2012/08/24
 ** Description:
 ** 
 ** Implements the viewer for query results
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co KG All rights reserved
 *****************************************************************************/ 

#ifndef CWMSQUERYRESULTVIEWER_H
#define CWMSQUERYRESULTVIEWER_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes

//WMS INcludes
#include "CdmQueryModel.h"

// Own Includes
#include "ui_CwmsQueryResultViewer.h"
#include "wmsgui.h"

// Forwards


// TypeDefs


/* 
 * This class implements the viewer for query results
 */
class WMSGUI_API CwmsQueryResultViewer : public QWidget, public Ui::CwmsQueryResultViewerClass
{
   Q_OBJECT

   private:
      QAbstractItemModel* m_pModel;

   public:
    CwmsQueryResultViewer( QWidget* p_pqwParent);
    virtual ~CwmsQueryResultViewer( );
    void SetQuery(QString p_qstrQuery);
    void SetQuery(CdmQueryEnhanced* p_pQuery);
    void SetModel(QAbstractItemModel *p_pModel);
public slots:
    void SaveAsCsvClickedSlot();
};

#endif // CWMSQUERYRESULTVIEWER_H
