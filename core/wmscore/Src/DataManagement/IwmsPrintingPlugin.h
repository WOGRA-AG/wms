#ifndef IWMSPRINTINGPLUGIN_H
#define IWMSPRINTINGPLUGIN_H

// Forwards
class IwmsPrinting;
class CdmObject;

class IwmsPrintingPlugin
{

public:
    virtual ~IwmsPrintingPlugin(){};
    virtual void OpenPrintingDesigner(CdmObject* p_pObject, QWidget* p_pParent) = 0;
    virtual IwmsPrinting* getPrinting() = 0;
    virtual QString getVersion() = 0;
    virtual QString getName() = 0;
};

Q_DECLARE_INTERFACE(IwmsPrintingPlugin, "com.wogra.iwmsprinting_interface/1.0")

#endif
