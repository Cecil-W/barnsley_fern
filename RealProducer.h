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
    const float a[4] = {0, 0.85, 0.2, -0.15};
    const float b[4] = {0, 0.04, -0.26, 0.28};
    const float c[4] = {0, -0.04, 0.23, 0.26};
    const float d[4] = {0.16, 0.85, 0.22, 0.24};
    const float e[4] = {0}; //not realy needed as its always 0, left in to change it later
    const float f[4] = {0, 1.6, 1.6, 0.44};

    std::random_device rd;
    std::mt19937 gen;
    std::uniform_int_distribution<int> dist;
    

public:
    /**
     * @brief Construct a new Real Producer:: Real Producer object
     * 
     * @param buf buffer into which this producer puts the data
     * @param iteration_count number of iterations the producer runs for
     */
    RealProducer(Buffer<Point>& buf, int count = 10000);
    ~RealProducer();

protected:
    bool produce(Point& point) override;
};
