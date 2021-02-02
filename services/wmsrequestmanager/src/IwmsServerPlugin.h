#ifndef IWMSSERVERPLUGINS_H
#define IWMSSERVERPLUGINS_H


class IwmsServerPlugin
{
public:
    virtual ~IwmsServerPlugin(){};
    virtual QString getVersion() = 0;
    virtual QString getName() = 0;
    virtual void init() = 0;
};

Q_DECLARE_INTERFACE(IwmsServerPlugin, "com.wogra.iwmsserverplugin/1.0")

#endif // IWMSSERVERPLUGINS_H
