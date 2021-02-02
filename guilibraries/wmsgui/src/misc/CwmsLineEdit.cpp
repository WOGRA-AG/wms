// System and Qt Includes
#include <QDesktopServices>
#include <QUrl>
#include <QRegExp>
#include <QApplication>
#include <QMenu>
#include <QAction>

//wms Includes
#include "CdmLogging.h"

// own Includes
#include "CwmsLineEdit.h"

CwmsLineEdit::CwmsLineEdit(QWidget * parent)
    : QLineEdit(parent),
      m_bHandleDefaultDesktopService(true)
{
    installEventFilter(this);
}

CwmsLineEdit::~CwmsLineEdit()
{
    //nothing to do
}

void CwmsLineEdit::SetHandleDefaultDesktopService(bool bHandleDefaultDesktopService)
{
    m_bHandleDefaultDesktopService = bHandleDefaultDesktopService;
}

bool CwmsLineEdit::eventFilter(QObject *pObject, QEvent *pEvent)
{
    bool bRet = false;

    if(m_bHandleDefaultDesktopService)
    {
        if(pObject == this && pEvent->type() == QEvent::MouseButtonRelease)
        {
            QMouseEvent *pMouseEvent = static_cast<QMouseEvent*> (pEvent);

            if(CHKPTR(pMouseEvent))
            {
                bRet = HandleMouseEvent(pMouseEvent);
            }
        }
    }
    else
    {
        //Signals and slot must be implemented + connected by the classwidget, if specific behavior is needed
        emit HandleMouseReleasedSignal(this);
    }

    return bRet;
}

bool CwmsLineEdit::HandleMouseEvent(QMouseEvent *pMouseEvent)
{
    bool bRet = false;

    if(pMouseEvent->button() == Qt::RightButton)
    {
        QAction* pAction = StartContextMenu();

        if(CHKPTR(pAction))
        {
            HandleInput();
            bRet = true;
        }
    }

    return bRet;
}

QAction * CwmsLineEdit::StartContextMenu()
{
    QMenu qMenu(NULL);
    QAction* pAction = NULL;
    pAction = qMenu.addAction(qApp->tr("Öffnen"));
    pAction = qMenu.exec(QCursor::pos());

    return pAction;
}

void CwmsLineEdit::HandleInput()
{
    if(isInputMail("^[a-zA-Z0-9.!#$%&'*+/=?^_`{|}~-]+@[a-zA-Z0-9](?:[a-zA-Z0-9-]{0,61}[a-zA-Z0-9])?(?:\\.[a-zA-Z0-9](?:[a-zA-Z0-9-]{0,61}[a-zA-Z0-9])?)*$", text()))
    {
        QString qstrMailTo = "mailto:" + text() + "?subject=";
        QDesktopServices::openUrl(QUrl(qstrMailTo));
    }
    else
    {
        QDesktopServices::openUrl(QUrl(text()));
    }
}

bool CwmsLineEdit::isInputMail(QString qstrPattern, QString qstrText)
{
    bool bRet = false;

    QRegExp regex;
    regex.setPattern(qstrPattern);
    if(regex.exactMatch(qstrText))
    {
        bRet = true;
    }

    return bRet;
}
