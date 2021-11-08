#include "Consumer.h"
#include "Buffer.h"
#include "CImg.h"
#include <iostream>

#pragma once
class RealConsumer : public Consumer<Point>{
private:
    std::mutex mute[10][10];
    static unsigned char pic[10000][20000];

public:
    RealConsumer(Buffer<Point>& buf);
    ~RealConsumer();
    void create_png();

protected:
    bool consume(const Point& data) override;

};
