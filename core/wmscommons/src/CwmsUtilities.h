#ifndef CWMSUTILITIES_H
#define CWMSUTILITIES_H

// System and Qt Includes
#include <QDate>

// Own Includes
#include "wmscommons.h"

class WMSCOMMONS_API CwmsUtilities
{
public:
    static bool isNumberValid(double dNumber);
    static bool isNumberValid(float dNumber);
    static bool isNumberValid(qint64 lNumber);
    static bool isNumberValid(int iNumber);
    static bool IsNumber(QString& p_qstrValue);
    static QString EncryptPassword(QString p_qstrPassword);
    static void OptimizeUrl(QString &p_qstrUrl);
    static bool IsStringBase64Encode(const QString &p_qstrString);
    static QString MaskString(QString p_rqstrString);
    static QString MaskStringForChanges(QString p_rqstrString);
    static QString ChangeDateToString(const QDate &p_rqdDate);
    static QString ChangeDateToString(const QDateTime &p_rqdtDateTime);
    static QString ConvertBoolToString(bool p_bBool);
    static QString MakeKeynameSave(QString p_qstrKeyname, QMap<QString, int> &p_rqmMembers, int &p_iKeynameCount);
    static bool IsKeynameSqlKeyword(QString p_qstrKeyname);
    static QString EncryptString(QString p_qstrString);
	static bool IsDateValid(QDate p_qdDate);
    static bool isValueTrue(QString &p_qstrValue);
    static int GetWeeksInYear(int year);
    static int CalculateMonthCount(QDate &qdStart, QDate &qdEnd);
    static bool IsInTheSameMonth(QDate &qdStart, QDate &qdEnd);
    static bool IsDateValid(QDateTime p_qdDate);
    static QString MakeWindowsFileName(QString p_qstrText, QString p_qstrReplaceString);
    static QString GetMaxWmsDateString();
    static QString GetInvalidDateString();
    static QString GetInvalidDateStringOld();
    static bool CreateArchive(QString p_rArchiveFileName, QString p_qstrOutPath, QStringList p_qstrlFileNamesForArchive);
    static QString TeaserText(const QString &p_rqstrText, int p_iLength, const QString &p_rqstrTruncateHint);
    static bool IsFileWritable(QString qstrFilename);
    static double Round(double p_dValue, int p_iDecimalPlaces);
};

#endif // CWMSUTILITIES_H
