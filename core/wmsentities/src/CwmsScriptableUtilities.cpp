#include <QByteArray>

#include "CwmsScriptableModel.h"
#include "CwmsScriptableUtilities.h"


CwmsScriptableUtilities::CwmsScriptableUtilities()
{
}


QString CwmsScriptableUtilities::convertFromByteArrayToBase64(QByteArray p_qArray)
{
  return p_qArray.toBase64();
}


QByteArray CwmsScriptableUtilities::convertFromBase64ToByteArray(QString p_qstrBase64)
{
    return QByteArray::fromBase64(p_qstrBase64.toUtf8());
}

QObject* CwmsScriptableUtilities::createEmptyModel()
{
    return new CwmsScriptableModel();
}

void CwmsScriptableUtilities::deleteModel(QObject* p_pModel)
{
    if (p_pModel->objectName() == "Model")
    {
        DELPTR(p_pModel);
    }
    else
    {
        CdmMessageManager::critical("Pointer Löschung nicht erlaubt","In dieser Funktion dürfen nur Models gelöscht werden");
    }
}
