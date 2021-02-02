
#include <QtGui>

#include <sstream>
#include <string>
#include <iostream>

#include "jshighlighter.h"
#include "jstokenizer.h"

JsHighlighter::JsHighlighter(QTextDocument *parent)
    : QSyntaxHighlighter(parent)
{

    specialCharFormat.setForeground(Qt::darkBlue);
    specialCharFormat.setFontWeight(QFont::Bold);
    variableFormat.setForeground(QColor(0x26, 0x26, 0x26));
    symbolFormat.setForeground(Qt::darkYellow);
    symbolFormat.setFontItalic(true);
    numberFormat.setForeground(Qt::darkGreen);
    decimalFormat.setForeground(Qt::darkGreen);
    decimalFormat.setFontItalic(true);
    stringFormat.setForeground(Qt::darkCyan);
    stringFormat.setFontItalic(true);
    commentFormat.setForeground(Qt::darkRed);
    commentFormat.setFontItalic(true);
    unknownFormat.setUnderlineStyle(QTextCharFormat::SpellCheckUnderline);
    unknownFormat.setUnderlineColor(Qt::red);
    colonCallFormat.setForeground(Qt::blue);
    colonCallFormat.setFontWeight(QFont::Bold);
    bracesFormat[0].setForeground(Qt::darkBlue);
    bracesFormat[1].setForeground(Qt::darkRed);
    bracesFormat[2].setForeground(Qt::darkGreen);
    for(int i = 0; i < NUM_BRACE_FORMATS; i++) {
        bracesFormat[i].setFontWeight(QFont::Bold);
    }
}

struct BlockData : public QTextBlockUserData
{
    int numBraces;
};

void JsHighlighter::highlightBlock(const QString &text)
{
    BlockData* data = dynamic_cast<BlockData*>(
                currentBlock().previous().userData());
    int numberOfOpenBraces = 0;
    if (data != nullptr) {
        numberOfOpenBraces = data->numBraces;
    }

    Tokenizer tokenizer(text, false);
    InputToken t = tokenizer.fetch();
    while (t.type != TT_EOF) {
        switch(t.type) {
        case TT_NAME:
            if (tokenizer.getString(t).endsWith(":")) {
                setFormat(t.absolutePos, t.length, colonCallFormat);
            } else {
                setFormat(t.absolutePos, t.length, variableFormat);
            }
           break;
        case TT_SYMBOL:
           setFormat(t.absolutePos, t.length, symbolFormat);
           break;
        case TT_STRING:
           setFormat(t.absolutePos, t.length, stringFormat);
           break;
        case TT_COMMENT:
           setFormat(t.absolutePos, t.length, commentFormat);
           break;
        case TT_UNKNOWN:
           setFormat(t.absolutePos, t.length, unknownFormat);
           break;
        case TT_NUMBER:
           setFormat(t.absolutePos, t.length, numberFormat);
           break;
        case TT_DECIMAL:
           setFormat(t.absolutePos, t.length, decimalFormat);
           break;
        case TT_LIST_START:
        case TT_L_BRACE:
        case TT_L_BRACKET:
            if (numberOfOpenBraces < 0) {
                setFormat(t.absolutePos, t.length, unknownFormat);
            } else {
                setFormat(t.absolutePos, t.length,
                          bracesFormat[numberOfOpenBraces % NUM_BRACE_FORMATS]);
            }
            numberOfOpenBraces =
                    numberOfOpenBraces < 0 ? 1 : numberOfOpenBraces + 1;
            break;
        case TT_R_BRACE:
        case TT_R_BRACKET:
            numberOfOpenBraces--;
            if (numberOfOpenBraces < 0) {
                setFormat(t.absolutePos, t.length, unknownFormat);
            } else {
                setFormat(t.absolutePos, t.length,
                          bracesFormat[numberOfOpenBraces % NUM_BRACE_FORMATS]);
            }
            break;
        default:
           setFormat(t.absolutePos, t.length, specialCharFormat);
        }
        t = tokenizer.fetch();
    }
    BlockData* newData = dynamic_cast<BlockData*>(currentBlockUserData());
    if (newData == nullptr) {
        newData = new BlockData();
    }
    newData->numBraces = numberOfOpenBraces;
    setCurrentBlockUserData(newData);
}