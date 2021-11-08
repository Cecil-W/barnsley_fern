#include "RealProducer.h"


RealProducer::RealProducer(Buffer<Point>& buf, int iteration_count)
: Producer<Point>::Producer(buf){
    max_iterations = iteration_count;
    coord = Point();
    //initializing the rngen
    gen = std::mt19937(rd());
    dist = std::uniform_int_distribution<>(1, 100);
}

RealProducer::~RealProducer(){

}

bool RealProducer::produce(Point& point){
    if(m_counter < max_iterations){
        float res1;
        float res2;
        int rand = (dist(gen));
        if (rand <= 1) {//f1
            res1 = 0;// 0 because all parameters in f1 are 0
            res2 = coord.x2 * d[0];
        }
        else if (rand <= 86) {//f2
            res1 = coord.x1 * a[1] + coord.x2 * b[1] + e[1];
            res2 = coord.x1 * c[1] + coord.x2 * d[1] + f[1];
        }
        else if (rand <= 93) {//f3
            res1 = coord.x1 * a[2] + coord.x2 * b[2] + e[2];
            res2 = coord.x1 * c[2] + coord.x2 * d[2] + f[2];
        }
        else {//f4
            res1 = coord.x1 * a[3] + coord.x2 * b[3] + e[3];
            res2 = coord.x1 * c[3] + coord.x2 * d[3] + f[3];
        }

        //updating the reference and the own point
        coord.x1 = res1;
        point.x1 = res1;
        coord.x2 = res2;
        point.x2 = res2;

        m_counter++;
        return false;
    }else{
        return true;
    }

}
