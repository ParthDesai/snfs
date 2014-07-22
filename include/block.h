#ifndef BLOCK_H
#define BLOCK_H


#include "common.h"

class block : public diskStruct
{
public:
    block(void * serData,diskManager * diskMgr);
    ~block();

    void * serialize();
protected:
private:
    byte m_diskData[BLOCK_SIZE];

    diskManager * m_diskMgr;
};

#endif // BLOCK_H
