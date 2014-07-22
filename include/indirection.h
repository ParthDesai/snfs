#ifndef INDIRECTION_H
#define INDIRECTION_H

#include "common.h"

#define INDIRECTION_BLOCK_MAX_ADDRESSES (BLOCK_SIZE / 4)

class indirection : public diskStruct
{
public:
    indirection(void * serData,blockManager * blkMgr);
    ~indirection();

    uint32_t getAddress(uint32 index);

    void * serialize();
protected:
private:
    uint32_t m_addresses[INDIRECTION_BLOCK_MAX_ADDRESSES];

    blockManager * blkMgr;

};

#endif // INDIRECTION_H
