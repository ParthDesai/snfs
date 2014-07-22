#ifndef FILE_H
#define FILE_H

#define MAX_ADDRESS_ARRAY_SIZE 15

#define LAST_DIRECT_ADDRESS_INDEX 12

#define SINGLE_INDIRECT_ADDRESS_INDEX 13

#define DOUBLE_INDIRECT_ADDRESS_INDEX 14

#define TRIPLE_INDIRECT_ADDRESS_INDEX 15

#define FLAG_IS_DIRECTORY 1

#include "common.h"

struct file_statistics
{
    long m_lastAccessTime;
    long m_lastModifiedTime;
    long m_lastWriteTime;
};

class file : public diskStruct
{
public:
    file(void * srData,blockManager * blkMgr);
    ~file();

    uint32_t readFromFile(void * buffer,uint32_t offset,size_t sz);
    uint32_t writeToFile(void * buffer,uint32_t offset,size_t sz);

    long getSizeOfFile();

    bool isDirectory();

    file_statistics getFileStatistics();

    void * serialize();

protected:
private:
    long m_fileID;
    long m_fileLength;
    uint32_t m_flags;

    file_statistics fileStatistics;

    uint32_t m_numberOfReference;

    uint32_t m_addresses[MAX_ADDRESS_ARRAY_SIZE];
    uint32_t m_numberOfAddress;

    blockManager * m_blkMgr;
};

#endif // FILE_H
