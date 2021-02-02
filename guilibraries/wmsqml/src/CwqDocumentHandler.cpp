#include "CwqDocumentHandler.h"

#include <QtGui/QTextDocument>
#include <QtGui/QTextCursor>
#include <QtGui/QFontDatabase>
#include <QtCore/QFileInfo>

CwqDocumentHandler::CwqDocumentHandler()
    : m_target(0)
    , m_doc(0)
    , m_cursorPosition(-1)
    , m_selectionStart(0)
    , m_selectionEnd(0)
{
}

void CwqDocumentHandler::setTarget(QQuickItem *target)
{
    m_doc = 0;
    m_target = target;
    if (!m_target)
        return;

    QVariant doc = m_target->property("textDocument");
    if (doc.canConvert<QQuickTextDocument*>()) {
        QQuickTextDocument *qqdoc = doc.value<QQuickTextDocument*>();
        if (qqdoc)
            m_doc = qqdoc->textDocument();
    }
    emit targetChanged();
}

void CwqDocumentHandler::setFileUrl(const QUrl &arg)
{
    if (m_fileUrl != arg) {
        m_fileUrl = arg;
        QString fileName = QQmlFile::urlToLocalFileOrQrc(arg);
        if (QFile::exists(fileName)) {
            QFile file(fileName);
            if (file.open(QFile::ReadOnly)) {
                QByteArray data = file.readAll();
                QTextCodec *codec = QTextCodec::codecForHtml(data);
                setText(codec->toUnicode(data));
                if (m_doc)
                    m_doc->setModified(false);
                if (fileName.isEmpty())
                    m_documentTitle = QStringLiteral("untitled.txt");
                else
                    m_documentTitle = QFileInfo(fileName).fileName();

                emit textChanged();
                emit documentTitleChanged();

                reset();
            }
        }
        emit fileUrlChanged();
    }
}

QString CwqDocumentHandler::documentTitle() const
{
    return m_documentTitle;
}

void CwqDocumentHandler::setDocumentTitle(QString arg)
{
    if (m_documentTitle != arg) {
        m_documentTitle = arg;
        emit documentTitleChanged();
    }
}

void CwqDocumentHandler::setText(const QString &arg)
{
    if (m_text != arg) {
        m_text = arg;
        emit textChanged();
    }
}

QUrl CwqDocumentHandler::fileUrl() const
{
    return m_fileUrl;
}

QString CwqDocumentHandler::text() const
{
    return m_text;
}

void CwqDocumentHandler::setCursorPosition(int position)
{
    if (position == m_cursorPosition)
        return;

    m_cursorPosition = position;

    reset();
}

void CwqDocumentHandler::reset()
{
    emit fontFamilyChanged();
    emit alignmentChanged();
    emit boldChanged();
    emit italicChanged();
    emit underlineChanged();
    emit fontSizeChanged();
    emit textColorChanged();
}

QTextCursor CwqDocumentHandler::textCursor() const
{
    QTextCursor cursor = QTextCursor(m_doc);
    if (m_selectionStart != m_selectionEnd) {
        cursor.setPosition(m_selectionStart);
        cursor.setPosition(m_selectionEnd, QTextCursor::KeepAnchor);
    } else {
        cursor.setPosition(m_cursorPosition);
    }
    return cursor;
}

void CwqDocumentHandler::mergeFormatOnWordOrSelection(const QTextCharFormat &format)
{
    QTextCursor cursor = textCursor();
    if (!cursor.hasSelection())
        cursor.select(QTextCursor::WordUnderCursor);
    cursor.mergeCharFormat(format);
}

void CwqDocumentHandler::setSelectionStart(int position)
{
    m_selectionStart = position;
}

void CwqDocumentHandler::setSelectionEnd(int position)
{
    m_selectionEnd = position;
}

void CwqDocumentHandler::setAlignment(Qt::Alignment a)
{
    QTextBlockFormat fmt;
    fmt.setAlignment((Qt::Alignment) a);
    QTextCursor cursor = QTextCursor(m_doc);
    cursor.setPosition(m_selectionStart, QTextCursor::MoveAnchor);
    cursor.setPosition(m_selectionEnd, QTextCursor::KeepAnchor);
    cursor.mergeBlockFormat(fmt);
    emit alignmentChanged();
}

Qt::Alignment CwqDocumentHandler::alignment() const
{
    QTextCursor cursor = textCursor();
    if (cursor.isNull())
        return Qt::AlignLeft;
    return textCursor().blockFormat().alignment();
}

bool CwqDocumentHandler::bold() const
{
    QTextCursor cursor = textCursor();
    if (cursor.isNull())
        return false;
    return textCursor().charFormat().fontWeight() == QFont::Bold;
}

bool CwqDocumentHandler::italic() const
{
    QTextCursor cursor = textCursor();
    if (cursor.isNull())
        return false;
    return textCursor().charFormat().fontItalic();
}

bool CwqDocumentHandler::underline() const
{
    QTextCursor cursor = textCursor();
    if (cursor.isNull())
        return false;
    return textCursor().charFormat().fontUnderline();
}

void CwqDocumentHandler::setBold(bool arg)
{
    QTextCharFormat fmt;
    fmt.setFontWeight(arg ? QFont::Bold : QFont::Normal);
    mergeFormatOnWordOrSelection(fmt);
    emit boldChanged();
}

void CwqDocumentHandler::setItalic(bool arg)
{
    QTextCharFormat fmt;
    fmt.setFontItalic(arg);
    mergeFormatOnWordOrSelection(fmt);
    emit italicChanged();
}

void CwqDocumentHandler::setUnderline(bool arg)
{
    QTextCharFormat fmt;
    fmt.setFontUnderline(arg);
    mergeFormatOnWordOrSelection(fmt);
    emit underlineChanged();
}

int CwqDocumentHandler::fontSize() const
{
    QTextCursor cursor = textCursor();
    if (cursor.isNull())
        return 0;
    QTextCharFormat format = cursor.charFormat();
    return format.font().pointSize();
}

void CwqDocumentHandler::setFontSize(int arg)
{
    QTextCursor cursor = textCursor();
    if (cursor.isNull())
        return;
    QTextCharFormat format;
    format.setFontPointSize(arg);
    mergeFormatOnWordOrSelection(format);
    emit fontSizeChanged();
}

QColor CwqDocumentHandler::textColor() const
{
    QTextCursor cursor = textCursor();
    if (cursor.isNull())
        return QColor(Qt::black);
    QTextCharFormat format = cursor.charFormat();
    return format.foreground().color();
}

void CwqDocumentHandler::setTextColor(const QColor &c)
{
    QTextCursor cursor = textCursor();
    if (cursor.isNull())
        return;
    QTextCharFormat format;
    format.setForeground(QBrush(c));
    mergeFormatOnWordOrSelection(format);
    emit textColorChanged();
}

QString CwqDocumentHandler::fontFamily() const
{
    QTextCursor cursor = textCursor();
    if (cursor.isNull())
        return QString();
    QTextCharFormat format = cursor.charFormat();
    return format.font().family();
}

void CwqDocumentHandler::setFontFamily(const QString &arg)
{
    QTextCursor cursor = textCursor();
    if (cursor.isNull())
        return;
    QTextCharFormat format;
    format.setFontFamily(arg);
    mergeFormatOnWordOrSelection(format);
    emit fontFamilyChanged();
}

QStringList CwqDocumentHandler::defaultFontSizes() const
{
    // uhm... this is quite ugly
    QStringList sizes;
    QFontDatabase db;
    foreach (int size, db.standardSizes())
        sizes.append(QString::number(size));
    return sizes;
}

void CwqDocumentHandler::registerToQml()
{
    qmlRegisterType<CwqDocumentHandler>("com.wogra.wmsqml", 1, 0, "WmsDocumentHandler");
}
