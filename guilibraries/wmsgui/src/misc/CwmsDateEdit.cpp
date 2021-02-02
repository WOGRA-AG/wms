#include "CwmsDateEdit.h"

CwmsDateEdit::CwmsDateEdit(QWidget *parent)
 : QDateEdit(parent)
{
   setMinimumDate(QDate(1800,1,1));
   setSpecialValueText("--.--.----");
}

CwmsDateEdit::~CwmsDateEdit()
{

}


QString CwmsDateEdit::textFromDateTime(const QDateTime &dateTime) const
{
   if (dateTime.isNull() ||
       !dateTime.isValid() ||
       dateTime.date() > QDate(4000,12,31) ||
       dateTime.date() < QDate(1800,1,1))
   {
      return "--.--.----";
   }
   else
   {
      return QDateEdit::textFromDateTime(dateTime);
   }
}


QValidator::State CwmsDateEdit::validate(QString &text, int &pos) const
{
   if (text.isEmpty() || text == "--.--.----")
   {
      return QValidator::Acceptable;
   }
   else
   {
      return QDateEdit::validate(text, pos);
   }
}
