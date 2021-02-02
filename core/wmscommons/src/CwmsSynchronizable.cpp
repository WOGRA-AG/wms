#include "CwmsSynchronizable.h"

CwmsSynchronizable::CwmsSynchronizable()
    : m_qmSychnronizableMutex(QMutex::Recursive)
{

}

CwmsSynchronizable::~CwmsSynchronizable()
{

}

const QMutex& CwmsSynchronizable::GetMutex()
{
    return m_qmSychnronizableMutex;
}
