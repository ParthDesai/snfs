#include "freeBlock.h"

freeBlock::freeBlock(bool isLast,uint32_t nextFreeBlockAddress)
{
    m_lastFreeBlock = isLast;
    m_nextFreeBlockAddress = nextFreeBlockAddress;
}

void freeBlock::setLast(bool value)
{
    m_lastFreeBlock = value;
}

bool freeBlock::isLast()
{
    return m_lastFreeBlock;
}

uint32_t freeBlock::getNextAddress()
{
    return m_nextFreeBlockAddress;
}

void freeBlock::setNextAddress(uint32_t nextAddress)
{
    m_nextFreeBlockAddress = nextAddress;
}

freeBlock::~freeBlock()
{
    //dtor
}

freeBlock * freeBlock::getNextfreeBlock(bool doNotReadFromDisk)
{
    if(m_lastFreeBlock)
    {
        return NULL;
    }

    if(m_nextFreeBlockInMemory == NULL)
    {
        if(doNotReadFromDisk)
        {
            return NULL;
        }

        m_nextFreeBlockInMemory = (freeBlock *)m_diskMgr->fetchFromDisk(m_nextFreeBlockAddress,BLOCK_SIZE);
        m_nextFreeBlockInMemory->m_nextFreeBlockInMemory = NULL;
        m_nextFreeBlockInMemory->setDirty(false);
        m_nextFreeBlockInMemory->setLockStatus(LOCK_NOLOCK);
    }

    return m_nextFreeBlockInMemory;
}
