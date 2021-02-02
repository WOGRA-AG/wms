#ifndef WMSSERVERDEFINES_H
#define WMSSERVERDEFINES_H

#define SERVER_NAME_STRING "serverName"
#define SIMULATE_PROCESSMANAGEMENT "simulateProcessManagement"
#define SIMULATE_PROCESSMANAGEMENT_VALUE false
#define MAINTENANCE_PORT "maintenancePort"
#define PRIMARY_PORT "primaryPort"
#define SECONDRAY_PORT "secondaryPort"
#define MAINTENANCE_PRIMARY_PORT "maintenanceActivePort"
#define MAINTENANCE_SECONDARY_PORT "maintenanceBackupPort"
#define WOGRA "WOGRA"
#define WMS "WMS"
#define DAEMON_SERVER_PORT "serverPort"
#define DAEMON_SERVER_PORT_VALUE 8383
#define SERVER_APP_NAME_VALUE "wmsapplicationserver.exe"
#define EXEC_ARG "-exec"
#define PORT_ARG "-port="
#define DEFAULT_MAX_SERVER_AGE_HOURS "maxServerAge"
#define DEFAULT_MAX_SERVER_AGE_HOURS_VALUE 48
#define MAX_SERVER_AGE "maxServerAge"
#define DEFAULT_BEST_SWITCHINGHOUR_START 1
#define BEST_SWITCHINGHOUR_START "bestSwitchingHourStart"
#define DEFAULT_BEST_SWITCHINGHOUR_END 3
#define BEST_SWITCHINGHOUR_END "bestSwitchingHourEnd"
#define MAINTENANCE_PORT_ARG "-maintenanceport="
#define DEFAULT_PROCESS_CHECK_TIMEOUT 1000*60*60
#define PROCESS_CHECK_TIMEOUT "processCheckTimeout"
#define MAX_MEM_USAGE_MB "maxMemUsage"
#define MAX_MEM_USAGE_MB_VALUE 200*1024
#define DAEMON_LOGGING_PATH "daemonLoggingPath"
#define DAEMON_LOGGING_INFO "Daemon_Logging_Information"
#define DAEMON_LOGGING_WARNING "Daemon_Logging_Warning"
#define DAEMON_LOGGING_ERROR "Daemon_Logging_Error"
#define DAEMON_LOGGING_FATAL "Daemon_Logging_Fatal"
#define DAEMON_LOGGING_ACTIVE "Daemon_Logging_Active"
#define DAEMON_LOGGING_PATH_VALUE "wmsserverd.log"
#define PRIMARY_PORT_VALUE 8585
#define SECONDRAY_PORT_VALUE 8586
#define MAINTENANCE_PRIMARY_PORT_VALUE 8182
#define MAINTENANCE_SECONDARY_PORT_VALUE 8183
#define DEFAULT_MAINTENANCE_SERVER_PORT 8181
#define MAX_THREADS "Config_MaxThreadCount"
#define MAX_THREADS_VALUE 4
#define DAEMON_LOG_SEVERITY "debugSeverity"
#define ZIP_COMPRESSION "Config_Compression"
#define ZIP_COMPRESSION_VALUE false
#define APPLICATION_LOGGING_PATH "Logging_Path"
#define APPLICATION_LOGGING_PATH_VALUE "wmsappserver.log"
#define APPLICATION_LOGGING_INFO "Logging_Information"
#define APPLICATION_LOGGING_WARNING "Logging_Warning"
#define APPLICATION_LOGGING_ERROR "Logging_Error"
#define APPLICATION_LOGGING_FATAL "Logging_Fatal"
#define APPLICATION_LOGGING_ACTIVE "Logging_Active"
#define SERVER_USER "Server_User"
#define SERVER_USER_PASSWORD "Server_Password"
#define MAX_TRIALS "Config_MaxTrials"
#define MAX_TRIALS_VALUE 3
#define ADMIN_STRING "admin"
#define MAX_CONNECTIONS "maxConnections"
#define MAX_CONNECTIONS_VALUE 10
#define HEALTH_CHECK_INTERVALL "healtCheckIntervall"
#define HEALTH_CHECK_INTERVALL_VALUE 5
#define SERVICENAME "WMS Server Daemon"
#define SERVICE_APPLICATION_NAME "/wmsserverd"
#define SESSION_TIMEOUT "sessionTimeout"
#define SESSION_TIMEOUT_VALUE 30
#define AUTHORIZATION "Authorization"

#include "wmsdefines.h"

#endif // WMSSERVERDEFINES_H
