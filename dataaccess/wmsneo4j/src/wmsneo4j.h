#ifndef WMSNEO4J_H
#define WMSNEO4J_H
#ifdef WIN32
#ifdef WMSNEO4J_EXPORTS
#define WMSNEO4J_API __declspec(dllexport)
#else
#define WMSNEO4J_API __declspec(dllimport)
#endif
#else
#define WMSNEO4J_API
#endif //

#endif // WMSNEO4J_H
