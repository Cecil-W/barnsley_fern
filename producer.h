#include "Worker.h"
#include "Buffer.h"

template<class T>
class Producer : Worker{
private:
    Buffer<T> &m_buffer;
    
    virtual bool produce(T& data);

public:
    Producer(Buffer<T>& buf);
    ~Producer();

};
