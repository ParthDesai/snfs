#ifndef ADDRESS_H
#define ADDRESS_H

#include "common.h"

class address
{
public:
    address();
    ~address();
protected:
private:
    bool m_isInMemory;
    void * m_objectAddress;
};

#endif // ADDRESS_H
