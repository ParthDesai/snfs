#ifndef BLOCKMANAGER_H
#define BLOCKMANAGER_H

#include "common.h"

#include <pthread.h>

#include <sparsehash/internal/sparseconfig.h>
#include <sparsehash/dense_hash_map>
#include <sparsehash/template_util.h>
#include <sparsehash/type_traits.h>

#include <map>

#define BLOCK_MANAGER_MAX_MEMORY (256 * 1024 * 1024)

enum blockRequest
{
    BLOCK_REQUEST_FOR_READ,
    BLOCK_REQUEST_FOR_WRITE
};

enum objHint
{
    OBJECT_FILE_NODE,
    OBJECT_INDIRECTION,
    OBJECT_FILE_DATA
};


class blockManager
{
public:
    blockManager(diskManager * diskmgr);
    virtual ~blockManager();

    void * getBlock(uint32_t address,blockRequest blkReq,objHint hint);
    void releaseBlock(uint32_t address,blockRequest blkReq,objHint hint);

protected:
private:

    struct blockWrapper
    {
        void * m_address;
        objHint m_hint;

        blockWrapper()
        {
            m_address = NULL;
        }
    };

    diskManager * m_diskMgr;

    google::dense_hash_map<uint32_t, blockWrapper> * m_blockStorage;

    std::map<uint32_t,uint32_t> * m_addressStorage;

    pthread_mutex_t * m_accessMutex;

    uint32_t m_nextID;

    void * getBlockFromFile(uint32_t address,blockRequest blkReq,objHint hint);
};

#endif // BLOCKMANAGER_H
