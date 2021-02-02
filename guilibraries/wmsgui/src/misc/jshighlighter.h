
#ifndef HIGHLIGHTER_H
#define HIGHLIGHTER_H

#include <QSyntaxHighlighter>

#include <QHash>
#include <QTextCharFormat>
#include "wmsgui.h" 

QT_BEGIN_NAMESPACE
class QTextDocument;
QT_END_NAMESPACE

const int NUM_BRACE_FORMATS = 3;

//! [0]
class JsHighlighter : public QSyntaxHighlighter
{
    Q_OBJECT

public:
    JsHighlighter(QTextDocument *parent = 0);

protected:
    void highlightBlock(const QString &text);

private:
    QTextCharFormat specialCharFormat;
    QTextCharFormat variableFormat;
    QTextCharFormat symbolFormat;
    QTextCharFormat numberFormat;
    QTextCharFormat decimalFormat;
    QTextCharFormat stringFormat;
    QTextCharFormat commentFormat;
    QTextCharFormat unknownFormat;
    QTextCharFormat colonCallFormat;
    QTextCharFormat bracesFormat[NUM_BRACE_FORMATS];
};
//! [0]

#endif //
