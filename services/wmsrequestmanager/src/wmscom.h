#ifndef BMSCOM_GLOBAL_H
#define BMSCOM_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef WMSCOM_LIB
# define WMSCOM_API Q_DECL_EXPORT
#else
# define WMSCOM_API Q_DECL_IMPORT
#endif //

#endif // // BMSCOM_GLOBAL_H
