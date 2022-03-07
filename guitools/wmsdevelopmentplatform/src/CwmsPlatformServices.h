#ifndef CWMSPLATFORMSERVICES_H
#define CWMSPLATFORMSERVICES_H

class QWidget;
class CdmClassMethod;

class CwmsPlatformServices
{
public:

    static void ExecuteFunction(CdmClassMethod *p_pFunction, bool p_bDebugger, QWidget *parent);
};

#endif // CWMSPLATFORMSERVICES_H
