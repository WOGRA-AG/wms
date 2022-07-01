// System and Qt Includes
#include <QCryptographicHash>
#include <QRegExp>
#include <QDate>
#include <QRegularExpression>
#include <QLocale>
#include <QCryptographicHash>
#include <QProcess>
#include <QFile>

// Own Includes
#include "CwmsUtilities.h"

#define MAX_ISO_DATE     QStringLiteral("9999-12-31")
#define MAX_ISO_DATE_OLD QStringLiteral("7999-12-31")
#define MAX_WMS_DATE     QStringLiteral("2100-12-31")


bool CwmsUtilities::isValueTrue(QString& p_qstrValue)
{
    return p_qstrValue.toLower() == "true";
}

bool CwmsUtilities::isNumberValid(int iNumber)
{
    int iTemp = iNumber;
    return (iTemp == iNumber);
}

bool CwmsUtilities::IsNumber(QString& p_qstrValue)
{
    QRegExp re("\\d*");  // a digit (\d), zero or more times (*)

    if (!re.exactMatch(p_qstrValue))
    {
        QLocale loc;
        bool bOk = false;
        loc.toDouble(p_qstrValue, &bOk);
        return bOk;
    }

    return true;
}

bool CwmsUtilities::isNumberValid(qint64 lNumber)
{
   qint64 lTemp = lNumber;
    return (lTemp == lNumber);
}


bool CwmsUtilities::isNumberValid(float dNumber)
{
    float fTemp = dNumber;
    return (fTemp == dNumber);
}

bool CwmsUtilities::isNumberValid(double dNumber)
{
    double dTemp = dNumber;
    return (dTemp == dNumber);
}

QString CwmsUtilities::EncryptPassword(QString p_qstrPassword)
{
    QString qstrRet = p_qstrPassword;
    QByteArray qbaCrypt = QCryptographicHash::hash(qstrRet.toLocal8Bit(), QCryptographicHash::Md5);
    QString qstrValue = QString::fromLocal8Bit(qbaCrypt.toHex());
    return qstrValue;
}

void CwmsUtilities::OptimizeUrl(QString& p_qstrUrl)
{
    QRegularExpression regex("(?<!:)/{2,}");
    p_qstrUrl.replace(regex, "/");
}

bool CwmsUtilities::IsStringBase64Encode(const QString& p_qstrString)
{
    QRegExp regexp("^([A-Za-z0-9+/]{4})*([A-Za-z0-9+/]{4}|[A-Za-z0-9+/]{3}=|[A-Za-z0-9+/]{2}==)$");
    return p_qstrString.contains(regexp);
}

QString CwmsUtilities::MaskString(QString p_rqstrString)
{
    // The '
    p_rqstrString = p_rqstrString.replace("'", "''");
    // The backslash
    p_rqstrString = p_rqstrString.replace("\\", "\\\\");
    p_rqstrString = p_rqstrString.replace("\\", "\\\\");
    p_rqstrString = p_rqstrString.replace("%", "% ");

    // The "
    p_rqstrString.replace("\"", "\\\"");

    return p_rqstrString;
}

QString CwmsUtilities::MaskStringForChanges(QString p_rqstrString)
{
    return MaskString(p_rqstrString);
}

QString CwmsUtilities::ChangeDateToString(const QDate& p_rqdDate)
{
    QString qstrRet;

    qstrRet = "'";

    if(p_rqdDate.isValid())
    {
        qstrRet += p_rqdDate.toString(Qt::ISODate);
    }
    else
    {
        qstrRet += "9999-12-31";
    }

    qstrRet += "'";

    return qstrRet;
}

QString CwmsUtilities::ChangeDateToString(const QDateTime& p_rqdtDateTime)
{
    QString qstrRet;

    if(p_rqdtDateTime.isValid())
    {
        //qstrRet = "UNIX_TIMESTAMP('";
        qstrRet = "'";
        qstrRet += p_rqdtDateTime.date().toString(Qt::ISODate);
        qstrRet += " ";
        qstrRet += p_rqdtDateTime.time().toString(Qt::ISODate);
        qstrRet += "'";
        //qstrRet += "')";
    }
    else
    {
        qstrRet = "'2037-12-31 23:59:59.99'";
    }

    return qstrRet;
}

QString CwmsUtilities::ConvertBoolToString(bool p_bBool)
{
    QString qstrRet;

    if(p_bBool)
    {
        qstrRet = "true";
    }
    else
    {
        qstrRet = "false";
    }

    return qstrRet;
}

QString CwmsUtilities::MakeKeynameSave(QString p_qstrKeyname,
                                       QMap<QString,
                                       int>& p_rqmMembers,
                                       int& p_iKeynameCount)
{
    p_qstrKeyname = p_qstrKeyname.simplified();
    p_qstrKeyname = "wms_" + p_qstrKeyname;
    p_qstrKeyname = p_qstrKeyname.replace(".", "_");
    p_qstrKeyname = p_qstrKeyname.replace(" ", "_");
    p_qstrKeyname = p_qstrKeyname.replace("-", "_");
    p_qstrKeyname = p_qstrKeyname.replace("+", "_");
    p_qstrKeyname = p_qstrKeyname.replace("*", "_");
    p_qstrKeyname = p_qstrKeyname.replace("/", "_");
    p_qstrKeyname = p_qstrKeyname.replace("\\", "_");
    p_qstrKeyname = p_qstrKeyname.replace("\"", "_");
    p_qstrKeyname = p_qstrKeyname.replace("'", "_");
    p_qstrKeyname = p_qstrKeyname.replace(",", "_");
    p_qstrKeyname = p_qstrKeyname.replace(";", "_");
    p_qstrKeyname = p_qstrKeyname.replace("^", "_");
    p_qstrKeyname = p_qstrKeyname.replace("°", "_");
    p_qstrKeyname = p_qstrKeyname.replace("?", "_");
    p_qstrKeyname = p_qstrKeyname.replace("@", "_");
    p_qstrKeyname = p_qstrKeyname.replace("~", "_");
    p_qstrKeyname = p_qstrKeyname.replace("|", "_");
    p_qstrKeyname = p_qstrKeyname.replace(">", "_");
    p_qstrKeyname = p_qstrKeyname.replace("<", "_");
    p_qstrKeyname = p_qstrKeyname.replace("=", "_");
    p_qstrKeyname = p_qstrKeyname.replace("(", "_");
    p_qstrKeyname = p_qstrKeyname.replace(")", "_");

    if (!p_rqmMembers.contains(p_qstrKeyname))
    {
        p_rqmMembers.insert(p_qstrKeyname, p_iKeynameCount);
        p_qstrKeyname += QString::number(p_iKeynameCount);
        ++p_iKeynameCount;
    }
    else
    {
        p_qstrKeyname += QString::number(p_rqmMembers[p_qstrKeyname]);
    }

    return p_qstrKeyname;
}

bool CwmsUtilities::IsKeynameSqlKeyword(QString p_qstrKeyname)
{
    bool bRet = false;
    p_qstrKeyname = p_qstrKeyname.toUpper();

    if (p_qstrKeyname == "A" ||
            p_qstrKeyname == "ABORT" ||
            p_qstrKeyname == "ABS" ||
            p_qstrKeyname == "ABSOLUTE" ||
            p_qstrKeyname == "ACCESS" ||
            p_qstrKeyname == "ACTION" ||
            p_qstrKeyname == "ADA" ||
            p_qstrKeyname == "ADD" ||
            p_qstrKeyname == "ADMIN" ||
            p_qstrKeyname == "AFTER" ||
            p_qstrKeyname == "AGGREGATE" ||
            p_qstrKeyname == "ALIAS" ||
            p_qstrKeyname == "ALL" ||
            p_qstrKeyname == "ALLOCATE" ||
            p_qstrKeyname == "ALSO" ||
            p_qstrKeyname == "ALTER" ||
            p_qstrKeyname == "ALWAYS" ||
            p_qstrKeyname == "ANALYSE" ||
            p_qstrKeyname == "ANALYZE" ||
            p_qstrKeyname == "AND" ||
            p_qstrKeyname == "ANY" ||
            p_qstrKeyname == "ARE" ||
            p_qstrKeyname == "ARRAY" ||
            p_qstrKeyname == "AS" ||
            p_qstrKeyname == "ASC" ||
            p_qstrKeyname == "ASENSITIVE" ||
            p_qstrKeyname == "ASSERTION" ||
            p_qstrKeyname == "ASSIGNMENT" ||
            p_qstrKeyname == "ASYMMETRIC" ||
            p_qstrKeyname == "AT" ||
            p_qstrKeyname == "ATOMIC" ||
            p_qstrKeyname == "ATTRIBUTE" ||
            p_qstrKeyname == "ATTRIBUTES" ||
            p_qstrKeyname == "AUTHORIZATION" ||
            p_qstrKeyname == "AVG" ||
            p_qstrKeyname == "BACKWARD" ||
            p_qstrKeyname == "BEFORE" ||
            p_qstrKeyname == "BEGIN" ||
            p_qstrKeyname == "BERNOULLI" ||
            p_qstrKeyname == "BETWEEN" ||
            p_qstrKeyname == "BIGINT" ||
            p_qstrKeyname == "BINARY" ||
            p_qstrKeyname == "BIT" ||
            p_qstrKeyname == "BITVAR" ||
            p_qstrKeyname == "BIT_LENGTH" ||
            p_qstrKeyname == "BLOB" ||
            p_qstrKeyname == "BOOLEAN" ||
            p_qstrKeyname == "BOTH" ||
            p_qstrKeyname == "BREADTH" ||
            p_qstrKeyname == "BY" ||
            p_qstrKeyname == "C" ||
            p_qstrKeyname == "CACHE" ||
            p_qstrKeyname == "CALL" ||
            p_qstrKeyname == "CALLED" ||
            p_qstrKeyname == "CARDINALITY" ||
            p_qstrKeyname == "CASCADE" ||
            p_qstrKeyname == "CASCADED" ||
            p_qstrKeyname == "CASE" ||
            p_qstrKeyname == "CAST" ||
            p_qstrKeyname == "CATALOG" ||
            p_qstrKeyname == "CATALOG_NAME" ||
            p_qstrKeyname == "CEIL" ||
            p_qstrKeyname == "CEILING" ||
            p_qstrKeyname == "CHAIN" ||
            p_qstrKeyname == "CHAR" ||
            p_qstrKeyname == "CHARACTER" ||
            p_qstrKeyname == "CHARACTERISTICS" ||
            p_qstrKeyname == "CHARACTERS" ||
            p_qstrKeyname == "CHARACTER_LENGTH" ||
            p_qstrKeyname == "CHARACTER_SET_CATALOG" ||
            p_qstrKeyname == "CHARACTER_SET_NAME" ||
            p_qstrKeyname == "CHARACTER_SET_SCHEMA" ||
            p_qstrKeyname == "CHAR_LENGTH" ||
            p_qstrKeyname == "CHECK" ||
            p_qstrKeyname == "CHECKED" ||
            p_qstrKeyname == "CHECKPOINT" ||
            p_qstrKeyname == "CLASS" ||
            p_qstrKeyname == "CLASS_ORIGIN" ||
            p_qstrKeyname == "CLOB" ||
            p_qstrKeyname == "CLOSE" ||
            p_qstrKeyname == "CLUSTER" ||
            p_qstrKeyname == "COALESCE" ||
            p_qstrKeyname == "COBOL" ||
            p_qstrKeyname == "COLLATE" ||
            p_qstrKeyname == "COLLATION" ||
            p_qstrKeyname == "COLLATION_CATALOG" ||
            p_qstrKeyname == "COLLATION_NAME" ||
            p_qstrKeyname == "COLLATION_SCHEMA" ||
            p_qstrKeyname == "COLLECT" ||
            p_qstrKeyname == "COLUMN" ||
            p_qstrKeyname == "COLUMN_NAME" ||
            p_qstrKeyname == "COMMAND_FUNCTION" ||
            p_qstrKeyname == "COMMAND_FUNCTION_CODE" ||
            p_qstrKeyname == "COMMENT" ||
            p_qstrKeyname == "COMMIT" ||
            p_qstrKeyname == "COMMITTED" ||
            p_qstrKeyname == "COMPLETION" ||
            p_qstrKeyname == "CONDITION" ||
            p_qstrKeyname == "CONDITION_NUMBER" ||
            p_qstrKeyname == "CONNECT" ||
            p_qstrKeyname == "CONNECTION" ||
            p_qstrKeyname == "CONNECTION_NAME" ||
            p_qstrKeyname == "CONSTRAINT" ||
            p_qstrKeyname == "CONSTRAINTS" ||
            p_qstrKeyname == "CONSTRAINT_CATALOG" ||
            p_qstrKeyname == "CONSTRAINT_NAME" ||
            p_qstrKeyname == "CONSTRAINT_SCHEMA" ||
            p_qstrKeyname == "CONSTRUCTOR" ||
            p_qstrKeyname == "CONTAINS" ||
            p_qstrKeyname == "CONTINUE" ||
            p_qstrKeyname == "CONVERSION" ||
            p_qstrKeyname == "CONVERT" ||
            p_qstrKeyname == "COPY" ||
            p_qstrKeyname == "CORR" ||
            p_qstrKeyname == "CORRESPONDING" ||
            p_qstrKeyname == "COUNT" ||
            p_qstrKeyname == "COVAR_POP" ||
            p_qstrKeyname == "COVAR_SAMP" ||
            p_qstrKeyname == "CREATE" ||
            p_qstrKeyname == "CREATEDB" ||
            p_qstrKeyname == "CREATEROLE" ||
            p_qstrKeyname == "CREATEUSER" ||
            p_qstrKeyname == "CROSS" ||
            p_qstrKeyname == "CSV" ||
            p_qstrKeyname == "CUBE" ||
            p_qstrKeyname == "CUME_DIST" ||
            p_qstrKeyname == "CURRENT" ||
            p_qstrKeyname == "CURRENT_DATE" ||
            p_qstrKeyname == "CURRENT_DEFAULT_TRANSFORM_GROUP" ||
            p_qstrKeyname == "CURRENT_PATH" ||
            p_qstrKeyname == "CURRENT_ROLE" ||
            p_qstrKeyname == "CURRENT_TIME" ||
            p_qstrKeyname == "CURRENT_TIMESTAMP" ||
            p_qstrKeyname == "CURRENT_TRANSFORM_GROUP_FOR_TYPE" ||
            p_qstrKeyname == "CURRENT_USER" ||
            p_qstrKeyname == "CURSOR" ||
            p_qstrKeyname == "CURSOR_NAME" ||
            p_qstrKeyname == "CYCLE" ||
            p_qstrKeyname == "DATA" ||
            p_qstrKeyname == "DATABASE" ||
            p_qstrKeyname == "DATE" ||
            p_qstrKeyname == "DATETIME_INTERVAL_CODE" ||
            p_qstrKeyname == "DATETIME_INTERVAL_PRECISION" ||
            p_qstrKeyname == "DAY" ||
            p_qstrKeyname == "DEALLOCATE" ||
            p_qstrKeyname == "DEC" ||
            p_qstrKeyname == "DECIMAL" ||
            p_qstrKeyname == "DECLARE" ||
            p_qstrKeyname == "DEFAULT" ||
            p_qstrKeyname == "DEFAULTS" ||
            p_qstrKeyname == "DEFERRABLE" ||
            p_qstrKeyname == "DEFERRED" ||
            p_qstrKeyname == "DEFINED" ||
            p_qstrKeyname == "DEFINER" ||
            p_qstrKeyname == "DEGREE" ||
            p_qstrKeyname == "DELETE" ||
            p_qstrKeyname == "DELIMITER" ||
            p_qstrKeyname == "DELIMITERS" ||
            p_qstrKeyname == "DENSE_RANK" ||
            p_qstrKeyname == "DEPTH" ||
            p_qstrKeyname == "DEREF" ||
            p_qstrKeyname == "DERIVED" ||
            p_qstrKeyname == "DESC" ||
            p_qstrKeyname == "DESCRIBE" ||
            p_qstrKeyname == "DESCRIPTOR" ||
            p_qstrKeyname == "DESTROY" ||
            p_qstrKeyname == "DESTRUCTOR" ||
            p_qstrKeyname == "DETERMINISTIC" ||
            p_qstrKeyname == "DIAGNOSTICS" ||
            p_qstrKeyname == "DICTIONARY" ||
            p_qstrKeyname == "DISABLE" ||
            p_qstrKeyname == "DISCONNECT" ||
            p_qstrKeyname == "DISPATCH" ||
            p_qstrKeyname == "DISTINCT" ||
            p_qstrKeyname == "DO" ||
            p_qstrKeyname == "DOCUMENT" ||
            p_qstrKeyname == "DOMAIN" ||
            p_qstrKeyname == "DOUBLE" ||
            p_qstrKeyname == "DROP" ||
            p_qstrKeyname == "DYNAMIC" ||
            p_qstrKeyname == "DYNAMIC_FUNCTION" ||
            p_qstrKeyname == "DYNAMIC_FUNCTION_CODE" ||
            p_qstrKeyname == "EACH" ||
            p_qstrKeyname == "ELEMENT" ||
            p_qstrKeyname == "ELSE" ||
            p_qstrKeyname == "ENABLE" ||
            p_qstrKeyname == "ENCODING" ||
            p_qstrKeyname == "ENCRYPTED" ||
            p_qstrKeyname == "END" ||
            p_qstrKeyname == "END-EXEC" ||
            p_qstrKeyname == "EQUALS" ||
            p_qstrKeyname == "ESCAPE" ||
            p_qstrKeyname == "EVERY" ||
            p_qstrKeyname == "EXCEPT" ||
            p_qstrKeyname == "EXCEPTION" ||
            p_qstrKeyname == "EXCLUDE" ||
            p_qstrKeyname == "EXCLUDING" ||
            p_qstrKeyname == "EXCLUSIVE" ||
            p_qstrKeyname == "EXEC" ||
            p_qstrKeyname == "EXECUTE" ||
            p_qstrKeyname == "EXISTING" ||
            p_qstrKeyname == "EXISTS" ||
            p_qstrKeyname == "EXP" ||
            p_qstrKeyname == "EXPLAIN" ||
            p_qstrKeyname == "EXTERNAL" ||
            p_qstrKeyname == "EXTRACT" ||
            p_qstrKeyname == "false" ||
            p_qstrKeyname == "FETCH" ||
            p_qstrKeyname == "FILTER" ||
            p_qstrKeyname == "FINAL" ||
            p_qstrKeyname == "FIRST" ||
            p_qstrKeyname == "FLOAT" ||
            p_qstrKeyname == "FLOOR" ||
            p_qstrKeyname == "FOLLOWING" ||
            p_qstrKeyname == "FOR" ||
            p_qstrKeyname == "FORCE" ||
            p_qstrKeyname == "FOREIGN" ||
            p_qstrKeyname == "FORTRAN" ||
            p_qstrKeyname == "FORWARD" ||
            p_qstrKeyname == "FOUND" ||
            p_qstrKeyname == "FREE" ||
            p_qstrKeyname == "FREEZE" ||
            p_qstrKeyname == "FROM" ||
            p_qstrKeyname == "FULL" ||
            p_qstrKeyname == "FUNCTION" ||
            p_qstrKeyname == "FUSION" ||
            p_qstrKeyname == "G" ||
            p_qstrKeyname == "GENERAL" ||
            p_qstrKeyname == "GENERATED" ||
            p_qstrKeyname == "GET" ||
            p_qstrKeyname == "GLOBAL" ||
            p_qstrKeyname == "GO" ||
            p_qstrKeyname == "GOTO" ||
            p_qstrKeyname == "GRANT" ||
            p_qstrKeyname == "GRANTED" ||
            p_qstrKeyname == "GREATEST" ||
            p_qstrKeyname == "GROUP" ||
            p_qstrKeyname == "GROUPING" ||
            p_qstrKeyname == "HANDLER" ||
            p_qstrKeyname == "HAVING" ||
            p_qstrKeyname == "HEADER" ||
            p_qstrKeyname == "HIERARCHY" ||
            p_qstrKeyname == "HOLD" ||
            p_qstrKeyname == "HOST" ||
            p_qstrKeyname == "HOUR" ||
            p_qstrKeyname == "IDENTITY" ||
            p_qstrKeyname == "IGNORE" ||
            p_qstrKeyname == "ILIKE" ||
            p_qstrKeyname == "IMMEDIATE" ||
            p_qstrKeyname == "IMMUTABLE" ||
            p_qstrKeyname == "IMPLEMENTATION" ||
            p_qstrKeyname == "IMPLICIT" ||
            p_qstrKeyname == "IN" ||
            p_qstrKeyname == "INCLUDING" ||
            p_qstrKeyname == "INCREMENT" ||
            p_qstrKeyname == "INDEX" ||
            p_qstrKeyname == "INDICATOR" ||
            p_qstrKeyname == "INFIX" ||
            p_qstrKeyname == "INHERIT" ||
            p_qstrKeyname == "INHERITS" ||
            p_qstrKeyname == "INITIALIZE" ||
            p_qstrKeyname == "INITIALLY" ||
            p_qstrKeyname == "INNER" ||
            p_qstrKeyname == "INOUT" ||
            p_qstrKeyname == "INPUT" ||
            p_qstrKeyname == "INSENSITIVE" ||
            p_qstrKeyname == "INSERT" ||
            p_qstrKeyname == "INSTANCE" ||
            p_qstrKeyname == "INSTANTIABLE" ||
            p_qstrKeyname == "INSTEAD" ||
            p_qstrKeyname == "INT" ||
            p_qstrKeyname == "INTEGER" ||
            p_qstrKeyname == "INTERSECT" ||
            p_qstrKeyname == "INTERSECTION" ||
            p_qstrKeyname == "INTERVAL" ||
            p_qstrKeyname == "INTO" ||
            p_qstrKeyname == "INVOKER" ||
            p_qstrKeyname == "IS" ||
            p_qstrKeyname == "ISNULL" ||
            p_qstrKeyname == "ISOLATION" ||
            p_qstrKeyname == "ITERATE" ||
            p_qstrKeyname == "JOIN" ||
            p_qstrKeyname == "K" ||
            p_qstrKeyname == "KEY" ||
            p_qstrKeyname == "KEY_MEMBER" ||
            p_qstrKeyname == "KEY_TYPE" ||
            p_qstrKeyname == "LANCOMPILER" ||
            p_qstrKeyname == "LANGUAGE" ||
            p_qstrKeyname == "LARGE" ||
            p_qstrKeyname == "LAST" ||
            p_qstrKeyname == "LATERAL" ||
            p_qstrKeyname == "LEADING" ||
            p_qstrKeyname == "LEAST" ||
            p_qstrKeyname == "LEFT" ||
            p_qstrKeyname == "LENGTH" ||
            p_qstrKeyname == "LESS" ||
            p_qstrKeyname == "LEVEL" ||
            p_qstrKeyname == "LIKE" ||
            p_qstrKeyname == "LIMIT" ||
            p_qstrKeyname == "LISTEN" ||
            p_qstrKeyname == "LN" ||
            p_qstrKeyname == "LOAD" ||
            p_qstrKeyname == "LOCAL" ||
            p_qstrKeyname == "LOCALTIME" ||
            p_qstrKeyname == "LOCALTIMESTAMP" ||
            p_qstrKeyname == "LOCATION" ||
            p_qstrKeyname == "LOCATOR" ||
            p_qstrKeyname == "LOCK" ||
            p_qstrKeyname == "LOGIN" ||
            p_qstrKeyname == "LOWER" ||
            p_qstrKeyname == "M" ||
            p_qstrKeyname == "MAP" ||
            p_qstrKeyname == "MATCH" ||
            p_qstrKeyname == "MATCHED" ||
            p_qstrKeyname == "MAX" ||
            p_qstrKeyname == "MAXVALUE" ||
            p_qstrKeyname == "MEMBER" ||
            p_qstrKeyname == "MERGE" ||
            p_qstrKeyname == "MESSAGE_LENGTH" ||
            p_qstrKeyname == "MESSAGE_OCTET_LENGTH" ||
            p_qstrKeyname == "MESSAGE_TEXT" ||
            p_qstrKeyname == "METHOD" ||
            p_qstrKeyname == "MIN" ||
            p_qstrKeyname == "MINUTE" ||
            p_qstrKeyname == "MINVALUE" ||
            p_qstrKeyname == "MOD" ||
            p_qstrKeyname == "MODE" ||
            p_qstrKeyname == "MODIFIES" ||
            p_qstrKeyname == "MODIFY" ||
            p_qstrKeyname == "MODULE" ||
            p_qstrKeyname == "MONTH" ||
            p_qstrKeyname == "MORE" ||
            p_qstrKeyname == "MOVE" ||
            p_qstrKeyname == "MULTISET" ||
            p_qstrKeyname == "MUMPS" ||
            p_qstrKeyname == "NAME" ||
            p_qstrKeyname == "NAMES" ||
            p_qstrKeyname == "NATIONAL" ||
            p_qstrKeyname == "NATURAL" ||
            p_qstrKeyname == "NCHAR" ||
            p_qstrKeyname == "NCLOB" ||
            p_qstrKeyname == "NESTING" ||
            p_qstrKeyname == "NEW" ||
            p_qstrKeyname == "NEXT" ||
            p_qstrKeyname == "NO" ||
            p_qstrKeyname == "NOCREATEDB" ||
            p_qstrKeyname == "NOCREATEROLE" ||
            p_qstrKeyname == "NOCREATEUSER" ||
            p_qstrKeyname == "NOINHERIT" ||
            p_qstrKeyname == "NOLOGIN" ||
            p_qstrKeyname == "NONE" ||
            p_qstrKeyname == "NORMALIZE" ||
            p_qstrKeyname == "NORMALIZED" ||
            p_qstrKeyname == "NOSUPERUSER" ||
            p_qstrKeyname == "NOT" ||
            p_qstrKeyname == "NOTHING" ||
            p_qstrKeyname == "NOTIFY" ||
            p_qstrKeyname == "NOTNULL" ||
            p_qstrKeyname == "NOWAIT" ||
            p_qstrKeyname == "nullptr" ||
            p_qstrKeyname == "NULLABLE" ||
            p_qstrKeyname == "NULLIF" ||
            p_qstrKeyname == "NULLS" ||
            p_qstrKeyname == "NUMBER" ||
            p_qstrKeyname == "NUMERIC" ||
            p_qstrKeyname == "OBJECT" ||
            p_qstrKeyname == "OCTETS" ||
            p_qstrKeyname == "OCTET_LENGTH" ||
            p_qstrKeyname == "OF" ||
            p_qstrKeyname == "OFF" ||
            p_qstrKeyname == "OFFSET" ||
            p_qstrKeyname == "OIDS" ||
            p_qstrKeyname == "OLD" ||
            p_qstrKeyname == "ON" ||
            p_qstrKeyname == "ONLY" ||
            p_qstrKeyname == "OPEN" ||
            p_qstrKeyname == "OPERATION" ||
            p_qstrKeyname == "OPERATOR" ||
            p_qstrKeyname == "OPTION" ||
            p_qstrKeyname == "OPTIONS" ||
            p_qstrKeyname == "OR" ||
            p_qstrKeyname == "ORDER" ||
            p_qstrKeyname == "ORDERING" ||
            p_qstrKeyname == "ORDINALITY" ||
            p_qstrKeyname == "OTHERS" ||
            p_qstrKeyname == "OUT" ||
            p_qstrKeyname == "OUTER" ||
            p_qstrKeyname == "OUTPUT" ||
            p_qstrKeyname == "OVER" ||
            p_qstrKeyname == "OVERLAPS" ||
            p_qstrKeyname == "OVERLAY" ||
            p_qstrKeyname == "OVERRIDING" ||
            p_qstrKeyname == "OWNER" ||
            p_qstrKeyname == "PAD" ||
            p_qstrKeyname == "PARAMETER" ||
            p_qstrKeyname == "PARAMETERS" ||
            p_qstrKeyname == "PARAMETER_MODE" ||
            p_qstrKeyname == "PARAMETER_NAME" ||
            p_qstrKeyname == "PARAMETER_ORDINAL_POSITION" ||
            p_qstrKeyname == "PARAMETER_SPECIFIC_CATALOG" ||
            p_qstrKeyname == "PARAMETER_SPECIFIC_NAME" ||
            p_qstrKeyname == "PARAMETER_SPECIFIC_SCHEMA" ||
            p_qstrKeyname == "PARTIAL" ||
            p_qstrKeyname == "PARTITION" ||
            p_qstrKeyname == "PASCAL" ||
            p_qstrKeyname == "PASSWORD" ||
            p_qstrKeyname == "PATH" ||
            p_qstrKeyname == "PERCENTILE_CONT" ||
            p_qstrKeyname == "PERCENTILE_DISC" ||
            p_qstrKeyname == "PERCENT_RANK" ||
            p_qstrKeyname == "PLACING" ||
            p_qstrKeyname == "PLI" ||
            p_qstrKeyname == "POSITION" ||
            p_qstrKeyname == "POSTFIX" ||
            p_qstrKeyname == "POWER" ||
            p_qstrKeyname == "PRECEDING" ||
            p_qstrKeyname == "PRECISION" ||
            p_qstrKeyname == "PREFIX" ||
            p_qstrKeyname == "PREORDER" ||
            p_qstrKeyname == "PREPARE" ||
            p_qstrKeyname == "PREPARED" ||
            p_qstrKeyname == "PRESERVE" ||
            p_qstrKeyname == "PRIMARY" ||
            p_qstrKeyname == "PRIOR" ||
            p_qstrKeyname == "PRIVILEGES" ||
            p_qstrKeyname == "PROCEDURAL" ||
            p_qstrKeyname == "PROCEDURE" ||
            p_qstrKeyname == "PUBLIC" ||
            p_qstrKeyname == "QUOTE" ||
            p_qstrKeyname == "RANGE" ||
            p_qstrKeyname == "RANK" ||
            p_qstrKeyname == "READ" ||
            p_qstrKeyname == "READS" ||
            p_qstrKeyname == "REAL" ||
            p_qstrKeyname == "RECHECK" ||
            p_qstrKeyname == "RECURSIVE" ||
            p_qstrKeyname == "REF" ||
            p_qstrKeyname == "REFERENCES" ||
            p_qstrKeyname == "REFERENCING" ||
            p_qstrKeyname == "REGR_AVGX" ||
            p_qstrKeyname == "REGR_AVGY" ||
            p_qstrKeyname == "REGR_COUNT" ||
            p_qstrKeyname == "REGR_INTERCEPT" ||
            p_qstrKeyname == "REGR_R2" ||
            p_qstrKeyname == "REGR_SLOPE" ||
            p_qstrKeyname == "REGR_SXX" ||
            p_qstrKeyname == "REGR_SXY" ||
            p_qstrKeyname == "REGR_SYY" ||
            p_qstrKeyname == "REINDEX" ||
            p_qstrKeyname == "RELATIVE" ||
            p_qstrKeyname == "RELEASE" ||
            p_qstrKeyname == "RENAME" ||
            p_qstrKeyname == "REPEATABLE" ||
            p_qstrKeyname == "REPLACE" ||
            p_qstrKeyname == "RESET" ||
            p_qstrKeyname == "RESTART" ||
            p_qstrKeyname == "RESTRICT" ||
            p_qstrKeyname == "RESULT" ||
            p_qstrKeyname == "RETURN" ||
            p_qstrKeyname == "RETURNED_CARDINALITY" ||
            p_qstrKeyname == "RETURNED_LENGTH" ||
            p_qstrKeyname == "RETURNED_OCTET_LENGTH" ||
            p_qstrKeyname == "RETURNED_SQLSTATE" ||
            p_qstrKeyname == "RETURNS" ||
            p_qstrKeyname == "REVOKE" ||
            p_qstrKeyname == "RIGHT" ||
            p_qstrKeyname == "ROLE" ||
            p_qstrKeyname == "ROLLBACK" ||
            p_qstrKeyname == "ROLLUP" ||
            p_qstrKeyname == "ROUTINE" ||
            p_qstrKeyname == "ROUTINE_CATALOG" ||
            p_qstrKeyname == "ROUTINE_NAME" ||
            p_qstrKeyname == "ROUTINE_SCHEMA" ||
            p_qstrKeyname == "ROW" ||
            p_qstrKeyname == "ROWS" ||
            p_qstrKeyname == "ROW_COUNT" ||
            p_qstrKeyname == "ROW_NUMBER" ||
            p_qstrKeyname == "RULE" ||
            p_qstrKeyname == "SAVEPOINT" ||
            p_qstrKeyname == "SCALE" ||
            p_qstrKeyname == "SCHEMA" ||
            p_qstrKeyname == "SCHEMA_NAME" ||
            p_qstrKeyname == "SCOPE" ||
            p_qstrKeyname == "SCOPE_CATALOG" ||
            p_qstrKeyname == "SCOPE_NAME" ||
            p_qstrKeyname == "SCOPE_SCHEMA" ||
            p_qstrKeyname == "SCROLL" ||
            p_qstrKeyname == "SEARCH" ||
            p_qstrKeyname == "SECOND" ||
            p_qstrKeyname == "SECTION" ||
            p_qstrKeyname == "SECURITY" ||
            p_qstrKeyname == "SELECT" ||
            p_qstrKeyname == "SELF" ||
            p_qstrKeyname == "SENSITIVE" ||
            p_qstrKeyname == "SEQUENCE" ||
            p_qstrKeyname == "SERIALIZABLE" ||
            p_qstrKeyname == "SERVER_NAME" ||
            p_qstrKeyname == "SESSION" ||
            p_qstrKeyname == "SESSION_USER" ||
            p_qstrKeyname == "SET" ||
            p_qstrKeyname == "SETOF" ||
            p_qstrKeyname == "SETS" ||
            p_qstrKeyname == "SHARE" ||
            p_qstrKeyname == "SHOW" ||
            p_qstrKeyname == "SIMILAR" ||
            p_qstrKeyname == "SIMPLE" ||
            p_qstrKeyname == "SIZE" ||
            p_qstrKeyname == "SMALLINT" ||
            p_qstrKeyname == "SOME" ||
            p_qstrKeyname == "SOURCE" ||
            p_qstrKeyname == "SPACE" ||
            p_qstrKeyname == "SPECIFIC" ||
            p_qstrKeyname == "SPECIFICTYPE" ||
            p_qstrKeyname == "SPECIFIC_NAME" ||
            p_qstrKeyname == "SQL" ||
            p_qstrKeyname == "SQLCODE" ||
            p_qstrKeyname == "SQLERROR" ||
            p_qstrKeyname == "SQLEXCEPTION" ||
            p_qstrKeyname == "SQLSTATE" ||
            p_qstrKeyname == "SQLWARNING" ||
            p_qstrKeyname == "SQRT" ||
            p_qstrKeyname == "STABLE" ||
            p_qstrKeyname == "START" ||
            p_qstrKeyname == "STATE" ||
            p_qstrKeyname == "STATEMENT" ||
            p_qstrKeyname == "STATIC" ||
            p_qstrKeyname == "STATISTICS" ||
            p_qstrKeyname == "STDDEV_POP" ||
            p_qstrKeyname == "STDDEV_SAMP" ||
            p_qstrKeyname == "STDIN" ||
            p_qstrKeyname == "STDOUT" ||
            p_qstrKeyname == "STORAGE" ||
            p_qstrKeyname == "STRICT" ||
            p_qstrKeyname == "STRUCTURE" ||
            p_qstrKeyname == "STYLE" ||
            p_qstrKeyname == "SUBCLASS_ORIGIN" ||
            p_qstrKeyname == "SUBLIST" ||
            p_qstrKeyname == "SUBMULTISET" ||
            p_qstrKeyname == "SUBSTRING" ||
            p_qstrKeyname == "SUM" ||
            p_qstrKeyname == "SUPERUSER" ||
            p_qstrKeyname == "SYMMETRIC" ||
            p_qstrKeyname == "SYSID" ||
            p_qstrKeyname == "SYSTEM" ||
            p_qstrKeyname == "SYSTEM_USER" ||
            p_qstrKeyname == "TABLE" ||
            p_qstrKeyname == "TABLESAMPLE" ||
            p_qstrKeyname == "TABLESPACE" ||
            p_qstrKeyname == "TABLE_NAME" ||
            p_qstrKeyname == "TEMP" ||
            p_qstrKeyname == "TEMPLATE" ||
            p_qstrKeyname == "TEMPORARY" ||
            p_qstrKeyname == "TERMINATE" ||
            p_qstrKeyname == "THAN" ||
            p_qstrKeyname == "THEN" ||
            p_qstrKeyname == "TIES" ||
            p_qstrKeyname == "TIME" ||
            p_qstrKeyname == "TIMESTAMP" ||
            p_qstrKeyname == "TIMEZONE_HOUR" ||
            p_qstrKeyname == "TIMEZONE_MINUTE" ||
            p_qstrKeyname == "TO" ||
            p_qstrKeyname == "TOAST" ||
            p_qstrKeyname == "TOP_LEVEL_COUNT" ||
            p_qstrKeyname == "TRAILING" ||
            p_qstrKeyname == "TRANSACTION" ||
            p_qstrKeyname == "TRANSACTIONS_COMMITTED" ||
            p_qstrKeyname == "TRANSACTIONS_ROLLED_BACK" ||
            p_qstrKeyname == "TRANSACTION_ACTIVE" ||
            p_qstrKeyname == "TRANSFORM" ||
            p_qstrKeyname == "TRANSFORMS" ||
            p_qstrKeyname == "TRANSLATE" ||
            p_qstrKeyname == "TRANSLATION" ||
            p_qstrKeyname == "TREAT" ||
            p_qstrKeyname == "TRIGGER" ||
            p_qstrKeyname == "TRIGGER_CATALOG" ||
            p_qstrKeyname == "TRIGGER_NAME" ||
            p_qstrKeyname == "TRIGGER_SCHEMA" ||
            p_qstrKeyname == "TRIM" ||
            p_qstrKeyname == "true" ||
            p_qstrKeyname == "TRUNCATE" ||
            p_qstrKeyname == "TRUSTED" ||
            p_qstrKeyname == "TYPE" ||
            p_qstrKeyname == "UESCAPE" ||
            p_qstrKeyname == "UNBOUNDED" ||
            p_qstrKeyname == "UNCOMMITTED" ||
            p_qstrKeyname == "UNDER" ||
            p_qstrKeyname == "UNENCRYPTED" ||
            p_qstrKeyname == "UNION" ||
            p_qstrKeyname == "UNIQUE" ||
            p_qstrKeyname == "UNKNOWN" ||
            p_qstrKeyname == "UNLISTEN" ||
            p_qstrKeyname == "UNNAMED" ||
            p_qstrKeyname == "UNNEST" ||
            p_qstrKeyname == "UNTIL" ||
            p_qstrKeyname == "UPDATE" ||
            p_qstrKeyname == "UPPER" ||
            p_qstrKeyname == "USAGE" ||
            p_qstrKeyname == "USER" ||
            p_qstrKeyname == "USER_DEFINED_TYPE_CATALOG" ||
            p_qstrKeyname == "USER_DEFINED_TYPE_CODE" ||
            p_qstrKeyname == "USER_DEFINED_TYPE_NAME" ||
            p_qstrKeyname == "USER_DEFINED_TYPE_SCHEMA" ||
            p_qstrKeyname == "USING" ||
            p_qstrKeyname == "VACUUM" ||
            p_qstrKeyname == "VALID" ||
            p_qstrKeyname == "VALIDATOR" ||
            p_qstrKeyname == "VALUE" ||
            p_qstrKeyname == "VALUES" ||
            p_qstrKeyname == "VARCHAR" ||
            p_qstrKeyname == "VARIABLE" ||
            p_qstrKeyname == "VARYING" ||
            p_qstrKeyname == "VAR_POP" ||
            p_qstrKeyname == "VAR_SAMP" ||
            p_qstrKeyname == "VERBOSE" ||
            p_qstrKeyname == "VIEW" ||
            p_qstrKeyname == "VOLATILE" ||
            p_qstrKeyname == "WHEN" ||
            p_qstrKeyname == "WHENEVER" ||
            p_qstrKeyname == "WHERE" ||
            p_qstrKeyname == "WIDTH_BUCKET" ||
            p_qstrKeyname == "WINDOW" ||
            p_qstrKeyname == "WITH" ||
            p_qstrKeyname == "WITHIN" ||
            p_qstrKeyname == "WITHOUT" ||
            p_qstrKeyname == "WORK" ||
            p_qstrKeyname == "WRITE" ||
            p_qstrKeyname == "YEAR" ||
            p_qstrKeyname == "ZONE" ||
            p_qstrKeyname == "OBJECTID" ||  // here we start with internal keynames
            p_qstrKeyname == "CONTAINERID" ||
            p_qstrKeyname == "KEYNAME" ||
            p_qstrKeyname == "CREATORID" ||
            p_qstrKeyname == "MODIFIERID" ||
            p_qstrKeyname == "LASTMODIFIED" ||
            p_qstrKeyname == "CREATED" ||
            p_qstrKeyname == "LOCKED" ||
            p_qstrKeyname == "LOCKED_TIMESTAMP" ||
            p_qstrKeyname == "PARENT" ||
            p_qstrKeyname == "CONFIG" ||
            p_qstrKeyname == "SESSIONID")

    {
        bRet = true;
    }

    return bRet;
}

QString CwmsUtilities::EncryptString(QString p_qstrString)
{
    QByteArray qbaCrypt = QCryptographicHash::hash(p_qstrString.toLocal8Bit(), QCryptographicHash::Md5);
    QString qstrValue = QString::fromLocal8Bit(qbaCrypt.toHex());
    return qstrValue;
}

int CwmsUtilities::GetWeeksInYear(int year)
{
    QDate qdDate(year,12,31);

    int iWeekNumber = qdDate.weekNumber();

    if (iWeekNumber == 1)
    {
        iWeekNumber = qdDate.addDays(-7).weekNumber();
    }

    return iWeekNumber;
}

bool CwmsUtilities::IsDateValid(QDate p_qdDate)
{
    if (p_qdDate.isValid())
    {
        if (p_qdDate > QDate(1800,1,1) && p_qdDate < QDate(2200,12,31))
        {
            return true;
        }
    }

    return false;
}

bool CwmsUtilities::IsDateValid(QDateTime p_qdDate)
{
    if (p_qdDate.isValid())
    {
        if (p_qdDate.date() > QDate(1800,1,1) && p_qdDate.date() < QDate(2200,12,31))
        {
            return true;
        }
    }

    return false;
}

int CwmsUtilities::CalculateMonthCount(QDate& qdStart, QDate& qdEnd)
{
    if (IsInTheSameMonth(qdStart,qdEnd))
    {
        return 1;
    }

    int iIntervall = qdEnd.month();
    int iYears = qdEnd.year() - qdStart.year();
    iIntervall += (12 * iYears) - qdStart.month();

    if (qdStart.month() != qdEnd.month() ||
        qdStart.day() < qdEnd.day())
    {
        iIntervall += 1;
    }

    return iIntervall;
}

bool CwmsUtilities::IsInTheSameMonth(QDate& qdStart, QDate& qdEnd)
{
    return (qdStart.month() == qdEnd.month() && qdStart.year() == qdEnd.year());
}

QString CwmsUtilities::MakeWindowsFileName(QString p_qstrText, QString p_qstrReplaceString)
{
    p_qstrText = p_qstrText.simplified();
    p_qstrText = p_qstrText.replace(".", p_qstrReplaceString);
    p_qstrText = p_qstrText.replace(" ", p_qstrReplaceString);
    p_qstrText = p_qstrText.replace("+", p_qstrReplaceString);
    p_qstrText = p_qstrText.replace("*", p_qstrReplaceString);
    p_qstrText = p_qstrText.replace("/", p_qstrReplaceString);
    p_qstrText = p_qstrText.replace("\\", p_qstrReplaceString);
    p_qstrText = p_qstrText.replace("\"", p_qstrReplaceString);
    p_qstrText = p_qstrText.replace("'", p_qstrReplaceString);
    p_qstrText = p_qstrText.replace(",", p_qstrReplaceString);
    p_qstrText = p_qstrText.replace(";", p_qstrReplaceString);
    p_qstrText = p_qstrText.replace("^", p_qstrReplaceString);
    p_qstrText = p_qstrText.replace("°", p_qstrReplaceString);
    p_qstrText = p_qstrText.replace("?", p_qstrReplaceString);
    p_qstrText = p_qstrText.replace("@", p_qstrReplaceString);
    p_qstrText = p_qstrText.replace("~", p_qstrReplaceString);
    p_qstrText = p_qstrText.replace("|", p_qstrReplaceString);
    p_qstrText = p_qstrText.replace(">", p_qstrReplaceString);
    p_qstrText = p_qstrText.replace("<", p_qstrReplaceString);
    p_qstrText = p_qstrText.replace("=", p_qstrReplaceString);
    p_qstrText = p_qstrText.replace(":", p_qstrReplaceString);

    return p_qstrText;
}

QString CwmsUtilities::GetMaxWmsDateString()
{
    return(MAX_WMS_DATE);
}

QString CwmsUtilities::GetInvalidDateString()
{
    return(MAX_ISO_DATE);
}

QString CwmsUtilities::GetInvalidDateStringOld()
{
    return(MAX_ISO_DATE_OLD);
}


bool CwmsUtilities::CreateArchive(QString p_rArchiveFileName, QString p_qstrOutPath, QStringList p_qstrlFileNamesForArchive)
{
    if (false == (p_qstrOutPath.endsWith("/") || p_qstrOutPath.endsWith("\\")))
    {
        p_qstrOutPath.append("/");
    }

    QFile::remove(p_qstrOutPath + p_rArchiveFileName);

    QStringList qstrlArguments;
    qstrlArguments.append("a");
    qstrlArguments.append(p_rArchiveFileName);

    QStringList::iterator it(p_qstrlFileNamesForArchive.begin());
    QStringList::iterator itLast(p_qstrlFileNamesForArchive.end());

    for ( ; it != itLast; ++it)
    {
       qstrlArguments.append(*it);
    }

    QProcess qprocZip;
    qprocZip.setWorkingDirectory(p_qstrOutPath);
    qprocZip.start("C:\\Program Files\\7-Zip\\7z.exe", qstrlArguments);
    qprocZip.waitForFinished();

    return QFile::exists(p_qstrOutPath + p_rArchiveFileName);
}

QString CwmsUtilities::TeaserText(const QString& p_rqstrText, int p_iLength, const QString& p_rqstrTruncateHint)
{
    QString qstrTeaserText(p_rqstrText);
    int iAddLength = p_rqstrTruncateHint.length();

    if (p_rqstrText.length() > p_iLength + iAddLength)
    {
        qstrTeaserText.truncate(p_iLength);

        if (iAddLength > 0)
        {
            qstrTeaserText += QString("\n");
            qstrTeaserText += p_rqstrTruncateHint;
        }
    }

    return(qstrTeaserText);
}

bool CwmsUtilities::IsFileWritable(QString qstrFilename)
{
    bool bRet = false;
    QFile::remove(qstrFilename);
    QFile qFile(qstrFilename);

    if (qFile.open(QIODevice::WriteOnly))
    {
        bRet = true;
        qFile.close();
    }

    return bRet;
}

double  CwmsUtilities::Round(double p_dValue, int p_iDecimalPlaces)
{
    double dPow = pow(10, p_iDecimalPlaces);
    double dRet = floor(p_dValue * dPow + 0.5) * pow(10, -p_iDecimalPlaces);
    return dRet;
}
