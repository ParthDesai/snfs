#ifndef FREEBLOCK_H
#define FREEBLOCK_H

#include "common.h"
#include "blockManager.h"

class freeBlock : public diskStruct
{
public:
    freeBlock(void * serData,diskManager * diskMgr,bool isLast,uint32_t nextFreeBlockAddress);
    ~freeBlock();

    void * serialize();

    void setLast(bool value);
    void setNextAddress(uint32_t nextAddress);

    bool isLast();
    uint32_t getNextAddress();

    freeBlock * getNextfreeBlock(bool doNotReadFromDisk);
protected:
private:
    uint32_t m_nextFreeBlockAddress;
    freeBlock * m_nextFreeBlockInMemory;
    bool m_lastFreeBlock;

    diskManager * m_diskMgr;
};

#endif // FREEBLOCK_H
