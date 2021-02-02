#ifndef IWMSIMEXPORTPROCESSOR_H
#define IWMSIMEXPORTPROCESSOR_H

// System and Qt Includes
#include <QString>

// Forwards
class CdmObject;

enum EwmsImExportType
{
    eWmsImExportTypeImport,
    eWmsImExportTypeExport
};

// EXPERIMENTAL NEEDS A PLUGINMECHANISMN
// SO ANOTHER WAY OVER INTERNAL FUNCTION COULD BE A
// BETTER SOLUTION
class IwmsImExportProcessor
{
    public:
        EwmsImExportType GetType() = 0;
        QString GetValueKeyname() = 0;
        void Process(CdmObject* p_pObject, QString p_qstrValue) = 0;
};

#endif // IWMSIMEXPORTPROCESSOR_H

