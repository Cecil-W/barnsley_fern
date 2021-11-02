#include "Producer.h"

template<class T>
Producer<T>::Producer(Buffer<T>& buf){

    m_buffer = buf;
}

template<class T>
Producer<class T>::~Producer(){


}
