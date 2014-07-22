#include "blockManager.h"

#include "block.h"
#include "indirection.h"
#include "file.h"
#include "lock.h"


blockManager::blockManager(diskManager * diskmgr)
{
    this->m_blockStorage = new google::dense_hash_map<uint32_t, blockWrapper>();
    this->m_blockStorage->set_empty_key(0);
    this->m_blockStorage->set_deleted_key(1);

    this->m_nextID = 1;

    this->m_addressStorage = new std::map<uint32_t,uint32_t>();

    this->m_diskMgr = diskmgr;

    pthread_mutexattr_t mutexAttributes;
    pthread_mutexattr_init(&mutexAttributes);
    pthread_mutexattr_settype(&mutexAttributes,PTHREAD_MUTEX_NORMAL);
    pthread_mutex_init(this->m_accessMutex,&mutexAttributes);
}


void * blockManager::getBlockFromFile(uint32_t address,blockRequest blkReq,objHint hint)
{
    void * data = NULL;
    switch(hint)
    {
    case OBJECT_FILE_DATA:
        data = m_diskMgr->fetchFromDisk(address,sizeof(block));
        {
            block * blk = (block *) data;
            blk->setLockStatus(LOCK_NOLOCK);
        }
        break;

    case OBJECT_INDIRECTION:
        data = m_diskMgr->fetchFromDisk(address,sizeof(indirection));
        {
            indirection * blk = (indirection *) data;
            blk->setLockStatus(LOCK_NOLOCK);
        }
        break;

    case OBJECT_FILE_NODE:
        data = m_diskMgr->fetchFromDisk(address,sizeof(file));
        {
            file * blk = (file *) data;
            blk->setLockStatus(LOCK_NOLOCK);
        }
        break;

    default:
        break;
    }

    return data;
}

void * blockManager::getBlock(uint32_t address,blockRequest blkReq,objHint hint)
{
    pthread_mutex_lock(m_accessMutex);

    blockWrapper wrapper = (*m_blockStorage)[address];

    void * data = NULL;

    if(wrapper.m_address == NULL)
    {
        data = getBlockFromFile(address,blkReq,hint);
        (*m_addressStorage)[m_nextID++] = address;

        blockWrapper wrapper;
        wrapper.m_address = data;
        wrapper.m_hint = hint;

        (*(m_blockStorage))[address] = wrapper;
    }

    switch(blkReq)
    {
    case BLOCK_REQUEST_FOR_READ:
        switch(hint)
        {
        case OBJECT_FILE_DATA:
        {
            file * blk = (file *) data;
            if(!blk->setLockStatus(LOCK_SHARED))
            {
                pthread_mutex_unlock(m_accessMutex);
                return NULL;
            }
        }
        break;

        case OBJECT_INDIRECTION:
        {
            indirection * blk = (indirection *) data;
            if(!blk->setLockStatus(LOCK_SHARED))
            {
                pthread_mutex_unlock(m_accessMutex);
                return NULL;
            }
        }
        break;

        case OBJECT_FILE_NODE:
        {
            block * blk = (block *) data;
            if(!blk->setLockStatus(LOCK_SHARED))
            {
                pthread_mutex_unlock(m_accessMutex);
                return NULL;
            }
        }
        break;

        default:
            break;
        }

        break;



    case BLOCK_REQUEST_FOR_WRITE:
        switch(hint)
        {
        case OBJECT_FILE_DATA:
        {
            file * blk = (file *) data;
            if(!blk->setLockStatus(LOCK_EXCLUSIVE))
            {
                pthread_mutex_unlock(m_accessMutex);
                return NULL;
            }
        }
        break;

        case OBJECT_INDIRECTION:
        {
            indirection * blk = (indirection *) data;
            if(!blk->setLockStatus(LOCK_EXCLUSIVE))
            {
                pthread_mutex_unlock(m_accessMutex);
                return NULL;
            }
        }
        break;

        case OBJECT_FILE_NODE:
        {
            block * blk = (block *) data;
            if(!blk->setLockStatus(LOCK_EXCLUSIVE))
            {
                pthread_mutex_unlock(m_accessMutex);
                return NULL;
            }
        }
        break;

        default:
            break;
        }
        break;
    default:
        break;
    }

    pthread_mutex_unlock(m_accessMutex);

    return data;

}


void blockManager::releaseBlock(uint32_t address,blockRequest blkReq,objHint hint)
{
    pthread_mutex_lock(m_accessMutex);

    blockWrapper wrapper = (*m_blockStorage)[address];

    void * data = NULL;

    if(wrapper.m_address == NULL)
    {
        pthread_mutex_unlock(m_accessMutex);
        return;
    }

    data = wrapper.m_address;

    switch(hint)
    {
    case OBJECT_FILE_DATA:
    {
        file * blk = (file *) data;
        blk->setLockStatus(LOCK_NOLOCK);
    }
    break;

    case OBJECT_INDIRECTION:
    {
        indirection * blk = (indirection *) data;
        blk->setLockStatus(LOCK_NOLOCK);
    }
    break;

    case OBJECT_FILE_NODE:
    {
        block * blk = (block *) data;
        blk->setLockStatus(LOCK_NOLOCK);
    }
    break;

    default:
        break;
    }

    pthread_mutex_unlock(m_accessMutex);

}


blockManager::~blockManager()
{
    //dtor
}
