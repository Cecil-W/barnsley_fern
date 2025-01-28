#include <vector>
#include <iostream>
#include <chrono>

#include "Buffer.h"
#include "RealProducer.h"
#include "RealConsumer.h"

int main(int argc, char const *argv[]){
    auto start = std::chrono::system_clock().now();
    //Buffer erstellen
    Buffer<Point> buffer(1000);

    //vector an RealProducern erstellen
    const int producer_count = 5;
    std::vector<RealProducer> producers;
    producers.reserve(producer_count);
    for(int i = 0; i < producer_count; ++i){
        producers.emplace_back(buffer, 1000000);
        producers.back().start();
    }
    std::cout << "Producers started\n";

    //vector an RealConsumern erstellen
    const int consumer_count = 6;
    std::vector<RealConsumer> consumers;
    consumers.reserve(consumer_count);
    for(int i = 0; i < consumer_count; ++i){
        consumers.emplace_back(buffer);
        consumers.back().start();
    }
    std::cout << "Consumers started\n";

    //Warten/join bis alle Consumer fertig sind
    for(auto& producer : producers) {
        producer.stop();
    }

    for (int i = 1; i < consumer_count; i++) {
        consumers[i].stop();
    }
    
    auto stop = std::chrono::system_clock().now();
    std::cout << "Producers finished after " << std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count() << "ms\n";

    //beim einem Consumer create_Img aufrufen
    consumers.front().create_png();
}
