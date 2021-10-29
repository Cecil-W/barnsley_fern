
template<class T> 
class Producer : Worker{
private:
    //TODO: Buffer erstellen
    Buffer<T>& m_buffer;
    
    virtual bool produce(T& data);

public:
    virtual Producer(/* args */);
    ~Producer();

};
