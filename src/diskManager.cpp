#include "diskManager.h"

diskManager::diskManager(int fd)
{
    m_fd = dup(fd);
}

diskManager::~diskManager()
{
    close(m_fd);
}

size_t diskManager::writeToDisk(uint32_t address,void * buffer,size_t sz)
{
    lseek(m_fd,address,SEEK_SET);
    ssize_t ret = write(m_fd,buffer,sz);

    if(ret <= 0)
    {
        return 0;
    }
    return ret;
}

void * diskManager::fetchFromDisk(uint32_t address,size_t sz)
{
    void * block = (void *) malloc(sz);
    ssize_t ret = read(m_fd,block,sz);

    if(ret <= 0 || ret != sz)
    {
        return NULL;
    }

    return block;
}


