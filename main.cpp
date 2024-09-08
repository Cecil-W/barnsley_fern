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
    const int producer_count = 10;
    vector<RealProducer> producers;
    producers.reserve(producer_count);
    for(int i = 0; i < producer_count; ++i){
        producers.emplace_back(buffer, 1000000);
        producers.back().start();
    }
    cout << "Producers started" << endl;

    //vector an RealConsumern erstellen
    const int cons_count = 10;
    vector<RealConsumer> consumers;
    consumers.reserve(cons_count);
    for(int i = 0; i < cons_count; ++i){
        consumers.emplace_back(buffer);
        consumers.back().start();
    }
    cout << "Consumers started" << endl;

    //Warten/join bis alle Consumer fertig sind
    for(auto& t : producers){
        t.stop();
    }
    cout << "Producers finished" << endl;

    //beim einem Consumer create_Img aufrufen
    consumers.front().create_png();


}
