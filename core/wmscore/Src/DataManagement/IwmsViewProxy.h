#ifndef IWMSVIEWPROXY_H
#define IWMSVIEWPROXY_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes
#include <QVariant>

// Own Includes


// Forwards


// TypeDefs


/* 
 * This interface defines the view proxy which handles view options for one specific column
 * If you need the same handling over multiple columns use IdmHandleDisplayData instead.
 */
class IwmsViewProxy
{
   public:
     virtual ~IwmsViewProxy(){};
      virtual QVariant data(int p_iRole, QVariant p_qvValue) = 0;

};

#endif // IWMSVIEWPROXY_H
