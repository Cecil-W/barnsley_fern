#include "worker.h"

Worker::Worker(/* args */){

}

Worker::~Worker(){
    if(m_running){
        m_thread.join();
    }
}

void Worker::start(){
    m_thread = std::thread(Worker::work());
}

void Worker::work(){
    while(step()){

    }
}
