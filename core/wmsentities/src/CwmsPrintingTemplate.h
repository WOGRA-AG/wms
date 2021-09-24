#ifndef CWMSPRINTINGTEMPLATE_H
#define CWMSPRINTINGTEMPLATE_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes


// WMS Includes
#include "CdmObjectAdaptor.h"


// Own Includes
#include "basetools.h"


// Forwards
class CdmClass;

// Enumerations
enum EwmsTemplateType
{
   eWmsTemplateTypeObject,
   eWmsTemplateTypeList
};

/* 
 * This class implements  the printing template for one document
 */
class BASETOOLS_API CwmsPrintingTemplate : public CdmObjectAdaptor
{

   public:
    CwmsPrintingTemplate( CdmObject* p_pCdmObject);
    CwmsPrintingTemplate( );
    virtual ~CwmsPrintingTemplate( );
    QString GetName();
    void SetName(QString p_qstrName);
    virtual void SetLanguage(QString p_iId);
    QString GetLanguage();
    long GetLanguageId();
    void SetTemplate(QString p_qstrContent);
    QString GetTemplate();
    bool ReadTemplateFromFile(QString p_qstrFilename);
    bool SaveTemplateToFile(QString p_qstrFilename);
    void SetClass(CdmClass* p_rpCdmClass);
    CdmClass* GetClass();
    void SetType(EwmsTemplateType p_eWmsType);
    void SetType(int p_eWmsType);
    EwmsTemplateType GetType();
    int GetTypeAsInt();
    bool IsDefault();
    void SetDefault(bool p_bDefault);
};

#endif //
