/****************************************************************************
**
** Copyright (C) 2009 Nokia Corporation and/or its subsidiary(-ies).
** Contact: Qt Software Information (qt-info@nokia.com)
**
** This file is part of the Qt Messaging Framework.
**
** $QT_BEGIN_LICENSE:LGPL$
** No Commercial Usage
** This file contains pre-release code and may not be distributed.
** You may use this file in accordance with the terms and conditions
** contained in the either Technology Preview License Agreement or the
** Beta Release License Agreement.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain
** additional rights. These rights are described in the Nokia Qt LGPL
** Exception version 1.0, included in the file LGPL_EXCEPTION.txt in this
** package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
** If you are unsure which license is appropriate for your use, please
** contact the sales department at qt-sales@nokia.com.
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef MESSAGELISTVIEW_H
#define MESSAGELISTVIEW_H

#include <QModelIndex>
#include <QTimer>
#include <QWidget>
#include <qmailmessage.h>
#include <qmailmessagekey.h>
#include <qmailmessagesortkey.h>

class MessageList;
class QFrame;
class QLineEdit;
class QMailMessageModelBase;
class QPushButton;
class QSortFilterProxyModel;
class QTabBar;
class QToolButton;
class QItemDelegate;
class QMailMessageDelegate;
class QtopiaHomeMailMessageDelegate;
class QuickSearchWidget;

class MessageListView : public QWidget
{
    Q_OBJECT

public:
    MessageListView(QWidget* parent = 0);
    virtual ~MessageListView();

    QMailMessageKey key() const;
    void setKey(const QMailMessageKey& key);

    QMailMessageSortKey sortKey() const;
    void setSortKey(const QMailMessageSortKey& sortKey);

    QMailFolderId folderId() const;
    void setFolderId(const QMailFolderId &id);

    QMailMessageId current() const;
    void setCurrent(const QMailMessageId& id);
    void setNextCurrent();
    void setPreviousCurrent();

    bool hasNext() const;
    bool hasPrevious() const;
    bool hasParent() const;
    bool hasChildren() const;

    int rowCount(const QModelIndex &parentIndex = QModelIndex()) const;

    QMailMessageIdList selected() const;
    void setSelected(const QMailMessageIdList& idList);
    void setSelected(const QMailMessageId& id);
    void selectAll();
    void clearSelection();

    bool markingMode() const;
    void setMarkingMode(bool set);

    bool moreButtonVisible() const;
    void setMoreButtonVisible(bool set);

    bool threaded() const;
    void setThreaded(bool set);

    bool ignoreUpdatesWhenHidden() const;
    void setIgnoreUpdatesWhenHidden(bool ignore);

    QMailMessageIdList visibleMessagesIds(bool buffer = true) const;

    bool showingQuickSearch() const;
    void showQuickSearch(bool val);

signals:
    void clicked(const QMailMessageId& id);
    void activated(const QMailMessageId& id);
    void currentChanged(const QMailMessageId& oldId, const QMailMessageId& newId);
    void selectionChanged();
    void rowCountChanged();
    void backPressed();
    void responseRequested(const QMailMessage&, QMailMessage::ResponseType);
    void moreClicked();
    void visibleMessagesChanged();
    void fullSearchRequested();

public slots:
    void reset();

protected slots:
    void indexClicked(const QModelIndex& index);
    void indexActivated(const QModelIndex& index);
    void currentIndexChanged(const QModelIndex& currentIndex, const QModelIndex& previousIndex);
    void modelChanged();
    void rowsAboutToBeRemoved(const QModelIndex&, int, int);
    void layoutChanged();
    void reviewVisibleMessages();
    void scrollTimeout();
    void quickSearch(const QMailMessageKey& key);

protected:
    void showEvent(QShowEvent* e);
    void hideEvent(QHideEvent* e);

private:
    void init();
    bool eventFilter(QObject*, QEvent*);
    void selectedChildren(const QModelIndex &index, QMailMessageIdList *selectedIds) const;
    void selectChildren(const QModelIndex &index, bool selected, bool *modified);

private:
    MessageList* mMessageList;
    QMailMessageModelBase* mModel;
    bool mMarkingMode;
    bool mIgnoreWhenHidden;
    bool mSelectedRowsRemoved;
    QMailFolderId mFolderId;
    QTimer mScrollTimer;
    QMailMessageIdList mPreviousVisibleItems;
    QuickSearchWidget* mQuickSearchWidget;
    QMailMessageKey mKey;
    bool mShowMoreButton;
    bool mThreaded;
};

#endif
