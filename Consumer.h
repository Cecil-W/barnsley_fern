#include "Worker.h"
#include "Buffer.h"
#include <stdexcept>

#pragma once
template<class T>
class Consumer : public Worker{
private:
    Buffer<T>& m_buffer;

public:
    Consumer(Buffer<T>& buf);
    Consumer(Consumer&& other) noexcept;
    
protected:
    bool step();
    virtual bool consume(const T& data) = 0;
};

/**
 * @brief Processing step, consumes data from the buffer
 * 
 * @tparam T 
 * @return true if the buffer is empty and the thread should terminate
 * @return false if data was processed, keeps the thread alive
 */
template<class T>
bool Consumer<T>::step(){
    T data;
    try{
        //data that need to be consumed
        data = m_buffer.pop();
    }
    catch(const std::runtime_error){
        //buffer is empty, every producer is done
        // TODO std::runtime_error an main weiter geben damit main create_img aufrufen kann
        return true; 
    }
    
    return consume(data);
}

/**
 * @brief Construct a new Consumer< T>:: Consumer object, sets the buffer
 * 
 * @tparam T 
 * @param buf buffer that this consumer consumes from
 */
template<typename T>
Consumer<T>::Consumer(Buffer<T>& buf)
: m_buffer(buf) {
}

template<typename T>
Consumer<T>::Consumer(Consumer &&other) noexcept : m_buffer(other.m_buffer) {
}
