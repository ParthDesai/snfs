#include "diskStruct.h"

diskStruct::diskStruct()
{
    m_isDirty = false;
    m_lock->unlock();
}

diskStruct::~diskStruct()
{
    //dtor
}

bool diskStruct::isDirty()
{
    return m_isDirty;
}


void diskStruct::setDirty(bool value)
{
    m_isDirty = value;
}

lockType diskStruct::getLockStatus()
{
    return m_lock.getLockStatus();
}

bool diskStruct::setLockStatus(lockType lockType)
{
    switch(lockType)
    {
        case LOCK_EXCLUSIVE:
            return m_lock.lockExclusively();
            break;

        case LOCK_SHARED:
            return m_lock.lockShared();
            break;

        case LOCK_NOLOCK:
            return m_lock.unlock();
            break;

        default:
            return false;
            break;

    }
}
