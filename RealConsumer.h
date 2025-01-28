#include <cstdint>
#include <iostream>

#include "CImg.h"

#include "Consumer.h"
#include "Buffer.h"

#pragma once
class RealConsumer : public Consumer<Point>{
private:
    static std::mutex m_mutex[10][10];
    static uint8_t pic[10000][20000];

public:
    RealConsumer(Buffer<Point>& buf);
    RealConsumer(RealConsumer&& other) noexcept;

    void create_png();

protected:
    bool consume(const Point& data) override;

};
