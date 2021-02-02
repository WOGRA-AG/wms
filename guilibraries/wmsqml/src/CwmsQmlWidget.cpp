
// System and Qt Includes
#include <QtQml>

// WMS Includes
#include "CdmLogging.h"
#include "CdmObject.h"
#include "CdmObjectContainer.h"

// own Includes
#include "CwmsQmlWidget.h"



CwmsQmlWidget::CwmsQmlWidget()
: m_lModuleId(0)
{
}

CwmsQmlWidget::~CwmsQmlWidget()
{
}

CdmLocatedElement* CwmsQmlWidget::getLocatedElement() const
{
    return m_rpElement;
}

void CwmsQmlWidget::setLocatedElement(CdmLocatedElement* p_pElement)
{
    m_rpElement = p_pElement;
}

bool CwmsQmlWidget::isObjectEditor() const
{
    bool bRet = false;

    if (CHKPTR(m_rpElement))
    {
        bRet = m_rpElement->IsObject();
    }

    return bRet;
}

bool CwmsQmlWidget::isContainerEditor() const
{
    bool bRet = false;

    if (CHKPTR(m_rpElement))
    {
        bRet = m_rpElement->IsContainer();
    }

    return bRet;
}

bool CwmsQmlWidget::isMainWindow() const
{
    return m_bMainWindow;
}

void CwmsQmlWidget::setMainWindow(bool bMainWindow)
{
    m_bMainWindow = bMainWindow;
}

QString CwmsQmlWidget::getUiName() const
{
    return m_qstrUiName;
}

void CwmsQmlWidget::setUiName(const QString &value)
{
    m_qstrUiName = value;
}

long CwmsQmlWidget::getModuleId() const
{
    return m_lModuleId;
}

void CwmsQmlWidget::setModuleId(const long &value)
{
    m_lModuleId = value;
}

void CwmsQmlWidget::registerToQml()
{
    qmlRegisterType<CwmsQmlWidget>("com.wogra.wmsqml", 1, 0, "WmsWidgetInfo");
}
