#ifndef IWMSPRINTING_H
#define IWMSPRINTING_H

// System and QT Includes
#include <QString>
#include <QStringList>

// Own Includes
#include "CwmsPrintingTemplate.h"
#include "CdmQueryModel.h"

// Forwards
class CdmObject;
class CdmObjectContainer;
class CdmClass;
class QAbstractItemModel;

class IwmsPrinting
{
public:
    virtual ~IwmsPrinting(){};

    virtual void PrintPdf() = 0;
    virtual void PrintPdf(QString p_qstrFilename) = 0;
    virtual void PrintSvg() = 0;
    virtual void PrintSvg(QString p_qstrFilename) = 0;
    virtual void PrintPreview() = 0;
    virtual void Print() = 0;
    virtual QByteArray PrintPdfToByteArray() = 0;
    virtual void AddObject(QString p_qstrKey, CdmObject* p_pObject, int p_iDepth = 0) = 0;
    virtual void AddObjectContainer(QString p_qstrKey, CdmObjectContainer* p_pContainer) = 0;
    virtual void AddParameter(QString p_qstrKey, QVariant p_qvValue) = 0;
    virtual void ClearData() = 0;
    virtual void AddItemModel(QString p_qstrKey, QAbstractItemModel* p_pqModel) = 0;
    virtual void AddStringList( QString p_qstrKey, QStringList p_qstrlValues) = 0;
    virtual void AddModel( QString p_qstrKeyname, CdmQueryModel& p_rCdmModel) = 0;
    virtual void SetTemplate(CwmsPrintingTemplate p_Template) = 0;
    virtual CwmsPrintingTemplate GetTemplate() = 0;
    virtual bool IsTemplateValid() = 0;
    virtual void SetMaxIterationDepth(int p_iDepth) = 0;
    virtual void ShowPdfDocument(QString& p_qstrFilePath) = 0;

};



#endif // IWMSPRINTING_H
