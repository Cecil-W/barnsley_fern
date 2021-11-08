#include "Buffer.h"
#include "Worker.h"
#include "Producer.h"
#include "Consumer.h"
#include "RealProducer.h"
#include "RealConsumer.h"
#include <vector>
#include <iostream>

using namespace std;

int main(int argc, char const *argv[]){
    //Buffer erstellen
    Buffer<Point> buffer(1000);

    //vector an RealProducern erstellen
    const int prod_count = 10;
    std::vector<RealProducer*> producers;
    for(int i = 0; i < prod_count; ++i){
        producers.push_back(new RealProducer(buffer, 1000000));
        producers.back()->start();
    }
    cout << "Producers started" << endl;

    //vector an RealConsumern erstellen
    const int cons_count = 10;
    vector<RealConsumer*> consumers(cons_count);
    for(int i = 0; i < cons_count; ++i){
        consumers.push_back(new RealConsumer(buffer));
        consumers.back()->start();
    }
    cout << "Consumers started" << endl;

    //Warten/join bis alle Consumer fertig sind
    for(auto& t : producers){
        t->stop();
    }
    cout << "Producers finished" << endl;

    //beim einem Consumer create_Img aufrufen
    consumers.front()->create_png();


}
