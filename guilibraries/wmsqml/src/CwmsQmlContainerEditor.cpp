
// System and Qt Includes
#include <QtQml>
#include <QQuickWindow>
#include <CdmClass.h>


// WMS Includes
#include "CdmLogging.h"
#include "CsaClass.h"
#include "CsaObjectContainer.h"
#include "CdmQueryBuilder.h"

// WMS Basetools Includes
#include "CwmsReportManager.h"

// own Includes
#include "CwmsQmlApplicationController.h"
#include "CwmsQmlContainerEditor.h"

CwmsQmlContainerEditor::CwmsQmlContainerEditor(CsaObjectContainer* p_pContainer)
    : QObject(nullptr),
      CdmContainerAdaptor(p_pContainer->getInternals()),
      m_pModel(nullptr)
{

}

CwmsQmlContainerEditor::CwmsQmlContainerEditor()
    : QObject(nullptr),
      CdmContainerAdaptor(),
      m_pModel(nullptr)
{

}

CwmsQmlContainerEditor::~CwmsQmlContainerEditor()
{
    DELPTR(m_pModel);
}

void CwmsQmlContainerEditor::setQuery(QString p_qstrQuery)
{
    m_pModel = new CdmQueryModel();
    dynamic_cast<CdmQueryModel*>(m_pModel)->Execute(p_qstrQuery);
}

void CwmsQmlContainerEditor::setContainer(CsaObjectContainer* p_pContainer)
{
    if (getContainer() != p_pContainer)
    {
        CdmContainerAdaptor::SetContainer(p_pContainer->getInternals());
        DELPTR(m_pModel);
    }
}

CsaObjectContainer* CwmsQmlContainerEditor::getContainer()
{
    return CwmsQmlApplicationController::getController()->convertContainer(CdmContainerAdaptor::GetContainer());
}

QAbstractItemModel *CwmsQmlContainerEditor::getModel()
{
    if (!m_pModel)
    {
        createModelFromContainer();
    }

    return m_pModel;
}

QString CwmsQmlContainerEditor::getColumnCode(int p_iColumn)
{
    QString qstrCode;

    CwmsQmlApplicationController* pController = CwmsQmlApplicationController::getController();

    if (CHKPTR(pController) && CHKPTR(m_pModel))
    {
        if (pController->isMobile())
        {

        }
        else
        {
            QHash<int, QByteArray> roles = m_pModel->roleNames();
            int rolePos = p_iColumn + Qt::UserRole + 1;
            //TODO
            int qstrTableWidth = pController->getCentralWindow()->width() / getColumnCount() - 2;

            if (roles.count() >= p_iColumn)
            {
                QString qstrRole(roles[rolePos]);
                QString qstrTitle = m_pModel->headerData(p_iColumn, Qt::Horizontal ).toString();

                qstrCode = "import QtQuick 2.3;\nimport QtQuick.Controls 1.2;\nimport QtQuick.Layouts 1.1;\n";
                qstrCode += QString("TableViewColumn{id:%1;\n").arg(qstrRole.toLower());
                qstrCode += QString("role: \"%1\" ;\n").arg(qstrRole);
                qstrCode += QString("title: \"%1\" ;\n").arg(qstrTitle);
                qstrCode += QString("width: %1 ;\n}").arg(qstrTableWidth);
            }
        }
    }



    return qstrCode;
}

int CwmsQmlContainerEditor::getColumnCount()
{
    int iColumns = 0;
    if (!m_pModel)
    {
        createModelFromContainer();
    }

    if (m_pModel)
    {
        iColumns = m_pModel->columnCount();
    }

    return iColumns;
}

void CwmsQmlContainerEditor::setModel(QAbstractItemModel *p_pModel)
{
    DELPTR(m_pModel);
    m_pModel = p_pModel;
    m_pModel->setParent(this);
}

void CwmsQmlContainerEditor::createModelFromContainer()
{
    DELPTR(m_pModel);

    if (CHKPTR(GetContainer()))
    {
        m_pModel = new CdmQueryModel(CwmsQmlApplicationController::getController()->getFactory());
        m_pModel->setParent(this);
        dynamic_cast<CdmQueryModel*>(m_pModel)->SetContainer(CdmContainerAdaptor::GetContainer());
        dynamic_cast<CdmQueryModel*>(m_pModel)->AddAllMembers();
        dynamic_cast<CdmQueryModel*>(m_pModel)->Execute();
    }
}

bool CwmsQmlContainerEditor::hasPrinting()
{
    bool hasPrinting = false;
    CdmQueryModel* pModel = dynamic_cast<CdmQueryModel*>(m_pModel);

    if (pModel)
    {
        CwmsReportManager cReportManager;
        CdmQueryEnhanced* pQuery = nullptr;
        const CdmClass* pClass = pModel->GetClass();

        if (CHKPTR(pClass))
        {
            pQuery = cReportManager.GetReportsByClassKeyname(pClass->GetKeyname(), eWmsTemplateTypeList);
        }

        if (pQuery && pQuery->GetResultCount() > 0)
        {
            hasPrinting = true;
        }
    }
    return hasPrinting;
}

void CwmsQmlContainerEditor::registerToQml()
{
    qmlRegisterType<CwmsQmlContainerEditor>("com.wogra.wmsqml", 1, 0, "WmsContainerEditorController");
}
