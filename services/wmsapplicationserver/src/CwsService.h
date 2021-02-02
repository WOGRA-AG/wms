
#ifndef CBMSWEBSERVICE_H
#define CBMSWEBSERVICE_H

// System and QT Includes
//#include <QGuiApplication>

// Own Includes
#include "CwsServerCommandHandler.h"
//#include "qtservice.h"

// forwards
class CwsController;

class CwsService //: public QtService // must be gui because some plugins needs gui e.g. printing
{
   private:
      CwsServerCommandHandler* m_pHandler;
      int m_iPort;
      int m_iServicePort;

      int ReadPort(QString p_qstrArg);
      void ParsePorts(int argc, char **argv);

   public:
      CwsService(int argc, char** argv, CwsServerCommandHandler* p_pHandler);
      static bool isServiceArgument(int argc, char** argv);
      ~CwsService();
      int GetMaintenancePort();
      void start();
      void pause();
      void resume();
      void stop();

};


#endif //
