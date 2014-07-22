#ifndef FREEBLOCKMANAGER_H
#define FREEBLOCKMANAGER_H

#include "common.h"
#include "freeBlock.h"

#define FREE_BLOCK_ALIGNMENT BLOCK_SIZE

class freeBlockManager
{
    public:
        freeBlockManager();
        virtual ~freeBlockManager();

        freeBlock * getNextFreeBlock();
        bool addToFreeBlock(uint32_t address,uint32_t nextAddress,bool isLast);

    protected:
    private:
        freeBlock * m_freeBlockListHead;
        freeBlock * m_freeBlockListTail;

        diskManager * m_diskMgr;

        pthread_mutex_t * m_accessMutex;
};

#endif // FREEBLOCKMANAGER_H
