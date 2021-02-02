#ifndef WMSCOMMONS_GLOBAL_H
#define WMSCOMMONS_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef WMSCOMMONS_LIB
# define WMSCOMMONS_API Q_DECL_EXPORT
#else
# define WMSCOMMONS_API Q_DECL_IMPORT
#endif

#endif // WMSCOMMONS_GLOBAL_H
