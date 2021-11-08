#include <queue>
#include <mutex>
#include <chrono>
#include <stdexcept>
#include <condition_variable>


#pragma once
struct Point{
    float x1, x2;
    Point(){
        x1 = 0.0;
        x2 = 0.0;
    }
};

template <typename T>
class Buffer{
private:
    std::queue<T> q;
    int m_capacity;
    int m_current_size;
    std::mutex mut;
    std::condition_variable has_capacity, has_data;

public:
    Buffer(int max_size = 1000);
    void push(T data);
    T pop();
};

template<class T>
Buffer<T>::Buffer(int size){
    m_capacity = size;
    m_current_size = 0;
    q = std::queue<T>();
}

template<class T>
void Buffer<T>::push(T data){
    //locking access to the queue
    std::unique_lock<std::mutex> lock(mut);
    
    //waiting for the queue to have capacity
    has_capacity.wait(lock, [this] {//lambda function checks if the queue has space
        if (m_current_size < m_capacity) return true; else return false;
    });

    //pushing the data onto the queue and increasing the size counter
    q.push(data);
    m_current_size++;
    //notifying one thread that is waiting for data
    has_data.notify_one();
}


/**
 * @brief Locks the queue and waits up to 100ms for data
 * 
 * @tparam T Type of the queue
 * @return T 
 */
template<class T>
T Buffer<T>::pop(){
    //locking the queue
    std::unique_lock<std::mutex> lock(mut);

    //checks if there is data in the queue for 100ms
    if(has_data.wait_for(lock, std::chrono::duration<long long, std::milli>(100) , [this] {return m_current_size > 0;})){
        //waking one thread that is waiting for capacity
        m_current_size--;
        has_capacity.notify_one();
        T data = q.front();
        q.pop();
        return data;
    } else {//if the queue waits to long we assume no more data is comming and we throw an error
        throw std::runtime_error("Every producer finished");
    }
}
