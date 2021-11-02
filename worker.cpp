#include "Worker.h"

Worker::Worker(/* args */){

}

Worker::~Worker(){
    if(m_running){
        m_thread.join();
    }
}

/**
 * @brief Starts the thread
 * 
 */
void Worker::start(){
    if(m_running){
        std::cout << "Thread already running!" << std::endl;
    } else {
        m_thread = std::thread(&Worker::work, this);
        m_running = true;
    }
    
}

/**
 * @brief Thread that gets created, keeps calling the step function
 * 
 */
void Worker::work(){
    //executing as long as there is work to do and terminate is false
    while(step() && !m_terminate){
        //nothing to do
    }
}

/**
 * @brief waiting for the thread to finish
 * 
 */
void Worker::stop(){
    m_terminate = true;
    m_thread.join();
    m_running = false;
}
