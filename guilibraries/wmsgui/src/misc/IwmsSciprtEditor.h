#ifndef IWMSSCIPRTEDITOR_H
#define IWMSSCIPRTEDITOR_H


// forwards
class QTreeWidgetItem;

class IwmsScriptEditor
{
    public:
        virtual ~IwmsScriptEditor(){};
        virtual bool Save() = 0;
        virtual void Revert() = 0;
        virtual void Debug() = 0;
        virtual void Execute() = 0;
        virtual void SetItem(QTreeWidgetItem*) = 0;
        virtual bool IsModified() = 0;
};

#endif // IWMSSCIPRTEDITOR_H
