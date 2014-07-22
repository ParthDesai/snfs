#include "lock.h"

lock::lock()
{
    //ctor
}

lock::~lock()
{
    //dtor
}


lockType lock::getLockStatus()
{
    return m_type;
}

bool lock::unlock()
{
    switch(m_type)
    {
    case LOCK_EXCLUSIVE:
        m_type = LOCK_NOLOCK;
        m_timesLocked = 0;
        return true;
        break;

    case LOCK_SHARED:
        m_timesLocked--;
        if(m_timesLocked == 0)
        {
            m_type = LOCK_NOLOCK;
        }
        return true;
        break;

    case LOCK_NOLOCK:
        return false;
        break;

    default:
        return false;
        break;
    }
}


bool lock::lockShared()
{
    switch(m_type)
    {
    case LOCK_EXCLUSIVE:
        return false;
        break;

    case LOCK_SHARED:
        m_timesLocked++;
        return true;
        break;

    case LOCK_NOLOCK:
        m_type = LOCK_SHARED;
        m_timesLocked = 1;
        return true;
        break;

    default:
        return false;
        break;
    }
}


bool lock::lockExclusively()
{
    switch(m_type)
    {
    case LOCK_EXCLUSIVE:
    case LOCK_SHARED:
        return false;
        break;

    case LOCK_NOLOCK:
        m_type = LOCK_EXCLUSIVE;
        m_timesLocked = 1;
        return true;
        break;

    default:
        return false;
        break;
    }
}
