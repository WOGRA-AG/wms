/******************************************************************************
 ** WOGRA technologies GmbH & Co. KG Modul Information
 ** Modulename: CwmsQueryResultViewer.cpp
 ** Started Implementation: 2012/08/24
 ** Description:
 **
 ** Implements the viewer for query results
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co. KG All rights reserved
 *****************************************************************************/

// System and QT Includes

// WMS Includes
#include "CdmQueryEnhanced.h"

#include "CwmsQueryModelExportCsv.h"

// own Includes
#include "CwmsTreeWidgetHelper.h"
#include "CwmsQueryResultViewer.h"

CwmsQueryResultViewer::CwmsQueryResultViewer(QWidget* p_pqwParent)
: QWidget(p_pqwParent)
{
   setupUi(this);
   m_pqtwResult->setModel(&m_cCdmQueryModel);
}

CwmsQueryResultViewer::~CwmsQueryResultViewer()
{
}

void CwmsQueryResultViewer::SetQuery(QString p_qstrQuery)
{
   m_cCdmQueryModel.Execute(p_qstrQuery);
   CwmsTreeWidgetHelper::ResizeColumnsToContent(m_pqtwResult);
}

void CwmsQueryResultViewer::SetQuery(CdmQueryEnhanced* p_pQuery)
{
   m_cCdmQueryModel.Execute(p_pQuery);
   CwmsTreeWidgetHelper::ResizeColumnsToContent(m_pqtwResult);
}

void CwmsQueryResultViewer::SaveAsCsvClickedSlot()
{
    CwmsQueryModelExportCsv::SaveModel(m_cCdmQueryModel);
}
