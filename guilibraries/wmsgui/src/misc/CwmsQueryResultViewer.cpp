// System and QT Includes
#include <QStandardItemModel>

// WMS Includes
#include "CdmLogging.h"
#include "CdmQuery.h"

#include "CwmsView.h"
#include "CwmsQueryModelExportCsv.h"

// own Includes
#include "CwmsTreeWidgetHelper.h"
#include "CwmsQueryResultViewer.h"

CwmsQueryResultViewer::CwmsQueryResultViewer(QWidget* p_pqwParent)
    : QWidget(p_pqwParent),
      m_pModel(nullptr),
      m_View(nullptr)
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

void CwmsQueryResultViewer::SetQuery(CdmQuery* p_pQuery)
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

    auto pModel = dynamic_cast<CdmQueryModel*>(m_pModel);

    if (!pModel && !m_View.IsValid())
    {
        m_pqpbRefresh->hide();
    }
}

void CwmsQueryResultViewer::SetView(CwmsView p_pView)
{
    m_View = p_pView;

    if (m_View.IsValid())
    {
        if (m_View.IsWql())
        {
            SetQuery(m_View.GetViewCommand());
        }
        else if (m_View.IsModel())
        {
            SetModel(m_View.GetModel());
        }
    }
}

void CwmsQueryResultViewer::SaveAsCsvClickedSlot()
{
    CwmsQueryModelExportCsv::SaveModel(*m_pModel);
}

void CwmsQueryResultViewer::RefreshClickedSlot()
{
     auto pModel = dynamic_cast<CdmQueryModel*>(m_pModel);

     if (pModel)
     {
         pModel->Execute();
     }
     else if (m_View.IsValid())
     {
         if (m_View.IsModel())
         {
             SetModel(m_View.GetModel());
         }
     }
}
