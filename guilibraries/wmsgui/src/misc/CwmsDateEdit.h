#ifndef CWMSDATEEDIT_H
#define CWMSDATEEDIT_H

#include <QString>
#include <QDateEdit>

class CwmsDateEdit : public QDateEdit
{
    Q_OBJECT
public:
    explicit CwmsDateEdit(QWidget *parent = 0);
   virtual ~CwmsDateEdit();

protected:
   virtual QString textFromDateTime(const QDateTime &dateTime) const;
   virtual QValidator::State validate(QString &text, int &pos) const;
};

#endif // CWMSDATEEDIT_H
