#include <thread>
#include <iostream>

#pragma once
class Worker{
private:
    std::thread m_thread;
    bool m_terminate = false;
    bool m_running = false;

    void work();

public:
    Worker(/* args */);
    ~Worker();
    Worker(const Worker& other) = delete;
    Worker& operator=(const Worker& other) = delete;
    Worker(Worker&& other);
    Worker& operator=(Worker&& other);
    void start();
    void stop();

protected:
    virtual bool step() = 0;

};
