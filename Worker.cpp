#include "Worker.h"

Worker::Worker(/* args */){
}

Worker::~Worker(){
    if(m_running){
        m_terminate = true;
        m_thread.join();
    }
}

/**
 * @brief Thread that gets created, keeps calling the step function
 * 
 */
void Worker::work(){
    //executing as long as there is work to do and terminate is false
    while(!step() && !m_terminate){
        //nothing to do
        //std::cout << "test" << std::endl;
    }
    m_running = false;
    m_terminate = false;
}

Worker::Worker(Worker &&other) : m_thread(std::move(other.m_thread)) {}

Worker &Worker::operator=(Worker &&other) {
    if (this != &other) {
        m_thread = std::move(other.m_thread);   
    }    
    return *this;
};

/**
 * @brief Starts the thread
 * 
 */
void Worker::start() {
    if(m_running){
        std::cout << "Thread already running!" << std::endl;
    } else {
        m_thread = std::thread(&Worker::work, this);
        m_running = true;
    }
}

/**
 * @brief waiting for the thread to finish
 * 
 */
void Worker::stop(){
    //m_terminate = true;//vorerst entfernt damit man in main stop aufrufen kann und wartet bis die threads fertig sind
    if (m_running == true){
        m_thread.join();
        m_running = false;
    }
}
