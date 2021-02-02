#ifndef WMSGUI_H
#define WMSGUI_H


#ifdef WIN32
#ifdef WMSGUI_EXPORTS
#define WMSGUI_API __declspec(dllexport)
#else
#define WMSGUI_API __declspec(dllimport)
#endif //
#else
#define WMSGUI_API
#endif //

#include <QMap>
#include <QColor>
#include <QString>



#endif //
