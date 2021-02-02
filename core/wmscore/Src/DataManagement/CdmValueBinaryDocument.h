/******************************************************************************
 ** WOGRA Middleware Server Data Manager Module
 **
 ** @Author Wolfgang Graßhof
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 **(C) copyright by WOGRA technologies All rights reserved
 ******************************************************************************/

#ifndef CDMBINARYDOCUMENT_H
#define CDMBINARYDOCUMENT_H


// System and QT Includes
#include <QString>
#include <QTemporaryFile>

// own Includes
#include "CdmValue.h"


// forwards

/*
 * This class represents the binary document value.
 */
class WMSMANAGER_API CdmValueBinaryDocument : public CdmValue
{
    Q_OBJECT

    friend class CdmValue;
    friend class CdmObject;

private:
    QString m_qstrFilename;
    QString m_qstrTempFilename;
    QString m_qstrType;
    QString m_qstrCurrentDirectory;




public:
    CdmValueBinaryDocument(long p_lDatabaseId,
                           long p_lId,
                           QString p_qstrKeyname,
                           QString p_qstrFilename,
                           QString p_qstrType,
                           CdmObject* p_pCdmObject);
    CdmValueBinaryDocument(QVariantMap& p_qVariant, CdmObject* p_pCdmObject);
    CdmValueBinaryDocument(QDomElement& p_rqDomElement, CdmObject* p_pCdmObject);
    virtual ~CdmValueBinaryDocument();


    void SetDefaultValue(const CdmMember* p_pCdmMember);
    int IsEqual(QVariant* p_pqVariant) const;
    int IsSmaller(QVariant* p_pqVariant) const;
    int IsSmallerEqual(QVariant* p_pqVariant) const;
    int IsLarger(QVariant* p_pqVariant) const;
    int IsLargerEqual(QVariant* p_pqVariant) const;
    int IsNotEqual(QVariant* p_pqVariant) const;
    QString GetFilename() const;
    void SetValue(QString p_qstrFilename, QString p_qstrType);
    void ExecuteFile();
    QByteArray GetByteArray() const;
    void GetValue(QString& p_qstrFilename, QString& p_qstrType) const;
    void GetBinaryDocumentDirectory();
    QString GetFileType() const;
    virtual void XmlExport(QDomElement& p_rqdeValue) const;
    void XmlImport(QDomElement& p_rqDomElement);
    QString GetDisplayString() const;
    virtual void CheckUnique();
    QString GetBase64() const;
    QString StoreToLocalFileSystem();
    void SaveFileTo(QString p_qstrPath);
    virtual QVariant GetVariant() const;
    virtual QVariant GetValueVariant() const;
    virtual void SetValueVariant(QVariant&);
    virtual QString GetValueAsString() const;
    virtual void Deploy(QVariantMap& p_rqvHash);
    virtual void SetVariant(QVariantMap& p_rqvHash);
    void SetBase64(QString p_qstrFilename, QString p_qstrFiletype, QString &p_qcstrBase64);

    // Not a part of the public API. Use this only in ReadBinaryDocument
    void SetFilenameAndTypeWithoutModifyingValue(QString &p_qstrFilename, QString &p_qstrType);

    QString GetCurrentDirectory();
private:
    void XmlImportBinaryDocument(  QDomElement& p_rqDomElement );
    void WriteByteArrayToFile(QByteArray& p_qByteArray);
    void WriteByteArrayToFile(QByteArray &p_qByteArray, QString p_qstrFilename);
    QByteArray GetByteArrayByMembers() const;
};

#endif
