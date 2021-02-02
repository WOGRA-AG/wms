#include <QThreadPool>

#include "CwmsRestRequestSender.h"
#include "CwmsRestApiTestMultiThreaded.h"


#define MAX_THREADS 5
#define CALL_FACTOR 2
#define EXPIRATION_TIMEOUT 6000
#define URL "http://localhost:8181/Rest/Api/class/test/Rad/"
#define SERVER "localhost"
#define PORT 8383

CwmsRestApiTestMultiThreaded::CwmsRestApiTestMultiThreaded()
{
    QThreadPool::globalInstance()->setMaxThreadCount(MAX_THREADS);
    QThreadPool::globalInstance()->setExpiryTimeout(EXPIRATION_TIMEOUT);
}

CwmsRestApiTestMultiThreaded::~CwmsRestApiTestMultiThreaded()
{
}

void CwmsRestApiTestMultiThreaded::RunTest()
{
    QList<CwmsRestRequestSender*> qlRequests;

    for (int counter = 0; counter < MAX_THREADS * CALL_FACTOR; ++counter)
    {
        qlRequests.append(new CwmsRestRequestSender(URL, SERVER, PORT));
    }

    for (int counter = 0; counter < MAX_THREADS * CALL_FACTOR; ++counter)
    {
        QThreadPool::globalInstance()->start(qlRequests[counter]);
    }

    // Mem leaks tidy up to do
}
