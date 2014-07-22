#ifndef DISKSTRUCT_H
#define DISKSTRUCT_H

#include "lock.h"

class diskStruct
{
public:
    diskStruct();
    ~diskStruct();

    bool isDirty();
    lockType getLockStatus();
    bool setLockStatus(lockType lockType);

protected:
    void setDirty(bool value);
private:
    bool m_isDirty;

    lock m_lock;
};

#endif // DISKSTRUCT_H
