#ifndef IWMSPRINTINGDESIGNER_H
#define IWMSPRINTINGDESIGNER_H

// Forwards
class CdmObject;

class IwmsPrintingDesigner
{
public:
    virtual ~IwmsPrintingDesigner(){};

    virtual void OpenPrintingDesigner(CdmObject* p_pReportConfig) = 0;
};

#endif // IWMSPRINTINGDESIGNER_H
