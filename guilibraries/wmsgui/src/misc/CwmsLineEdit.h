#ifndef CWMSLINEEDIT_H
#define CWMSLINEEDIT_H

//System and Qt Includes
#include <QLineEdit>
#include <QMouseEvent>
#include <QObject>

// own Includes
#include "wmsgui.h"

class WMSGUI_API CwmsLineEdit : public QLineEdit
{
    Q_OBJECT

private:
    bool m_bHandleDefaultDesktopService;

public:
    CwmsLineEdit(QWidget *parent = NULL);
    virtual ~CwmsLineEdit();

    void SetHandleDefaultDesktopService(bool bHandleDefaultDesktopService);

signals:
    void HandleMouseReleasedSignal(QLineEdit*);

protected:
    bool eventFilter(QObject *pObject, QEvent *pEvent);

private:
    bool isInputMail(QString qstrPattern, QString qstrText);
    void HandleInput();
    QAction * StartContextMenu();
    bool HandleMouseEvent(QMouseEvent *pMouseEvent);
};

#endif // CWMSLINEEDIT_H
