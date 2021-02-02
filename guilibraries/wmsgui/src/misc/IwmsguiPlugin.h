#ifndef IWMSGUIPLUGIN_H
#define IWMSGUIPLUGIN_H


class IwmsGuiPlugin
{
public:
   virtual ~IwmsGuiPlugin(){};
   virtual void installUi() = 0;
   virtual int getVersion() = 0;
   virtual QString getName() = 0;
};

Q_DECLARE_INTERFACE(IwmsGuiPlugin, "com.wogra.iwmsguiplugin/1.0")
#endif // // IWMSGUIPLUGIN_H
