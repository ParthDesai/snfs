#ifndef DISKMANAGER_H
#define DISKMANAGER_H

#include "common.h"

class diskManager
{
    public:
        diskManager(int fd);
        virtual ~diskManager();

        void * fetchFromDisk(uint32_t address,size_t sz);
        size_t writeToDisk(uint32_t address,void * buffer,size_t sz);

    protected:
    private:
        int m_fd;
};

#endif // DISKMANAGER_H
