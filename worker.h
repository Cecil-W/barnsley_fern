#include <thread>

class Worker{
private:
    std::thread m_thread;
    bool m_terminate = false;
    bool m_running = false;
    void work();

public:
    Worker(/* args */);
    ~Worker();
    void start();
    void stop();

protected:
    virtual bool step();

};
