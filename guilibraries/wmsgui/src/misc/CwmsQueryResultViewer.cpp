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
#include "CdmLogging.h"
#include "CdmQueryEnhanced.h"

#include "CwmsQueryModelExportCsv.h"

// own Includes
#include "CwmsTreeWidgetHelper.h"
#include "CwmsQueryResultViewer.h"

CwmsQueryResultViewer::CwmsQueryResultViewer(QWidget* p_pqwParent)
    : QWidget(p_pqwParent),
      m_pModel(nullptr)
{
    setupUi(this);

}

CwmsQueryResultViewer::~CwmsQueryResultViewer()
{
    DELPTR(m_pModel);
}

void CwmsQueryResultViewer::SetQuery(QString p_qstrQuery)
{
    DELPTR(m_pModel)
    m_pModel = new CdmQueryModel();
    dynamic_cast<CdmQueryModel*>(m_pModel)->Execute(p_qstrQuery);
    m_pqtwResult->setModel(m_pModel);
    CwmsTreeWidgetHelper::ResizeColumnsToContent(m_pqtwResult);
}

void CwmsQueryResultViewer::SetQuery(CdmQueryEnhanced* p_pQuery)
{
    DELPTR(m_pModel)
    m_pModel = new CdmQueryModel();
    dynamic_cast<CdmQueryModel*>(m_pModel)->Execute(p_pQuery);
    m_pqtwResult->setModel(m_pModel);
    CwmsTreeWidgetHelper::ResizeColumnsToContent(m_pqtwResult);
}

void CwmsQueryResultViewer::SetModel(QAbstractItemModel* p_pModel)
{
    DELPTR(m_pModel)
    m_pModel = p_pModel;
    m_pqtwResult->setModel(m_pModel);
    CwmsTreeWidgetHelper::ResizeColumnsToContent(m_pqtwResult);
}

void CwmsQueryResultViewer::SaveAsCsvClickedSlot()
{
    CwmsQueryModelExportCsv::SaveModel(*m_pModel);
}
