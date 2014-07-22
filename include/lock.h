#ifndef LOCK_H
#define LOCK_H


#include <stdint.h>

enum lockType
{
    LOCK_NOLOCK,
    LOCK_SHARED,
    LOCK_EXCLUSIVE
};


class lock
{
public:
    lock();
    ~lock();

    bool lockShared();
    bool lockExclusively();

    bool unlock();

    lockType getLockStatus();

protected:
private:
    lockType m_type;
    uint32_t m_timesLocked;
};

#endif // LOCK_H
