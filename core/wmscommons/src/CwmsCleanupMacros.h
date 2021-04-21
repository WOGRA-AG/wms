#ifndef CWMSCLEANUPMACROS_H
#define CWMSCLEANUPMACROS_H



#define CLEANUP_LINKEDLIST_PTR(a,b)     { \
                                            for (QLinkedList<a*>::iterator qvlIt = b.begin(); qvlIt != b.end(); ++qvlIt) \
                                            { \
                                                \
                                                if (*qvlIt) \
                                                { \
                                                    delete *qvlIt; \
                                                } \
                                            } \
                                        }



#endif
