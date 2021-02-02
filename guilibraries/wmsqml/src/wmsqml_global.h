#ifndef WMSQML_GLOBAL_H
#define WMSQML_GLOBAL_H

#ifdef Q_OS_WIN
#ifdef WMSQML_LIB
# define WMSQML_EXPORT __declspec(dllexport)
#else
# define WMSQML_EXPORT __declspec(dllimport)
#endif //
#else
#define WMSQML_EXPORT
#endif
#endif 
