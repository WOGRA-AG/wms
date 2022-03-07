#ifndef CWMSFORMUSERDEFINEDEXECUTOR_H
#define CWMSFORMUSERDEFINEDEXECUTOR_H

#include "wmsgui.h"
#include "CwmsFormUserDefined.h"

class CdmObject;
class CdmObjectContainer;
class IdmExecutorEngine;
class CsaFactory;

class WMSGUI_API CwmsFormUserDefinedExecutor
{
    private:
    QWidget* m_qwContainer;
public:
    CwmsFormUserDefinedExecutor();
    ~CwmsFormUserDefinedExecutor();
    void ExecuteUserDefinedFormObject(CwmsFormUserDefined& p_From, CdmObject* p_pObject, QWidget *parent);
    void ExecuteUserDefinedFormContainer(CwmsFormUserDefined& p_From, CdmObjectContainer* p_pContainer, QWidget *parent);
    void ExecuteUserDefinedFormMisc(CwmsFormUserDefined& p_From, QWidget *parent);

private:
    QWidget *GenerateUi(CwmsFormUserDefined &p_Form, QWidget *parent);
    void InitForm(CwmsFormUserDefined &p_Form, QWidget *p_pWidget, CdmObject *p_pObject);
    void InitForm(CwmsFormUserDefined &p_Form, QWidget *p_pWidget);
    void InitForm(CwmsFormUserDefined &p_Form, QWidget *p_pWidget, CdmObjectContainer *p_pContainer);
    void ShowUi(CwmsFormUserDefined &p_Form, QWidget *p_pWidget);
    IdmExecutorEngine *GetEngine();
    CsaFactory *GetFactory();
};

#endif // CWMSFORMUSERDEFINEDEXECUTOR_H
