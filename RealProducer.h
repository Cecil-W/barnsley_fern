#include "Producer.h"
#include "Buffer.h"
#include <random>
#include <iostream>


#pragma once
class RealProducer : public Producer<Point> {
private:
    int m_counter = 0;
    int max_iterations;
    Point coord;
    const float a[4] = {0.0f, 0.85f, 0.2f, -0.15f};
    const float b[4] = {0, 0.04f, -0.26f, 0.28f};
    const float c[4] = {0, -0.04f, 0.23f, 0.26f};
    const float d[4] = {0.16f, 0.85f, 0.22f, 0.24f};
    const float e[4] = {0}; //not realy needed as its always 0, left in to change it later
    const float f[4] = {0, 1.6f, 1.6f, 0.44f};

    std::random_device rd;
    std::mt19937 gen;
    std::uniform_int_distribution<int> dist;
    

public:
    /**
     * @brief Construct a new Real Producer:: Real Producer object
     * 
     * @param buffer buffer into which this producer puts the data
     * @param iteration_count number of iterations the producer runs for
     */
    RealProducer(Buffer<Point> &buffer, int count = 10000);

    RealProducer(RealProducer&& other);

    ~RealProducer();

protected:
    bool produce(Point& point) override;
};
