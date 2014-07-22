#include "freeBlockManager.h"

freeBlockManager::freeBlockManager()
{
    m_freeBlockListHead = m_freeBlockListTail = NULL;

    pthread_mutexattr_t mutexAttributes;
    pthread_mutexattr_init(&mutexAttributes);
    pthread_mutexattr_settype(&mutexAttributes,PTHREAD_MUTEX_NORMAL);
    pthread_mutex_init(this->m_accessMutex,&mutexAttributes);
}

bool  freeBlockManager::addToFreeBlock(uint32_t address,uint32_t nextAddress,bool isLast)
{
    if(address % FREE_BLOCK_ALIGNMENT != 0)
    {
        return false;
    }

    freeBlock blk(isLast,nextAddress);

    m_diskMgr->writeToDisk(address,&blk,sizeof(freeBlock));

    if(m_freeBlockListTail->isLast())
    {
        m_freeBlockListTail->setLast(false);
        m_freeBlockListTail->setNextAddress(address);
    }

    return true;
}

freeBlock * freeBlockManager::getNextFreeBlock()
{
    if(m_freeBlockListHead == NULL)
    {
        return NULL;
    }

    freeBlock * freeBlock = m_freeBlockListHead;
    m_freeBlockListHead = freeBlock->getNextfreeBlock(false);

    if(m_freeBlockListHead == NULL)
    {
        m_freeBlockListTail = NULL;
    }
    else
    {
        if(m_freeBlockListTail->getNextfreeBlock(false) != NULL)
        {
            m_freeBlockListTail = m_freeBlockListTail->getNextfreeBlock(false);
        }
    }

    return freeBlock;
}

freeBlockManager::~freeBlockManager()
{

}
