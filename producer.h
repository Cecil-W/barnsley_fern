#include "Worker.h"
#include "Buffer.h"

#pragma once
template<class T>
class Producer : public Worker{
private:
    Buffer<T>& m_buffer;
    
public:
    Producer(Buffer<T>& buf);
    ~Producer();

protected:
    bool step();
    virtual bool produce(T& data) = 0;
    
};

template<class T>
bool Producer<T>::step(){
    T data;
    bool done = produce(data);
    m_buffer.push(data);
    return done;
}

template<class T>
Producer<T>::Producer(Buffer<T>& buf)
: m_buffer(buf) {
}

template<class T>
Producer<T>::~Producer(){
}
