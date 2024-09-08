#include "Worker.h"
#include "Buffer.h"

#pragma once
template<typename T>
class Producer : public Worker{
private:
    Buffer<T>& m_buffer;
    
public:
    Producer(Buffer<T>& buf);
    Producer(Producer&& other);

    ~Producer() = default;

protected:
    bool step();
    virtual bool produce(T& data) = 0;
    
};

template<typename T>
bool Producer<T>::step(){
    T data;
    bool done = produce(data);
    m_buffer.push(data);
    return done;
}

template<typename T>
inline Producer<T>::Producer(Buffer<T>& buf) : m_buffer(buf) {
}

template<typename T>
inline Producer<T>::Producer(Producer&& other) : m_buffer(other.m_buffer) {
}

