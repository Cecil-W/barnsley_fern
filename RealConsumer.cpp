#include "RealConsumer.h"

//definition of the static member
std::mutex RealConsumer::m_mutex[10][10];
unsigned char RealConsumer::pic[10000][20000];

RealConsumer::RealConsumer(Buffer<Point>& buf)
: Consumer::Consumer(buf){

}

RealConsumer::RealConsumer(RealConsumer&& other) noexcept : 
    Consumer(std::move(other))
{
}

bool RealConsumer::consume(const Point& data){
    //scaling, -2.2<x1<2.7 & 0<x2<10 => 10,000 x 20,000
    //and flipping img because 0,0 is in the top left corner in CImg 
    int x, y;
    //x
    x = (data.x1 + 2.2) / 4.9 * 10000;

    //y, scaling and then flipping
    y = -(int)((data.x2 * 2000) - 20000);

    //Locking the image segment, img is divided into 1000x2000 chunks
    std::lock_guard<std::mutex> guard(m_mutex[x/1000][y/2000]);

    //increasing pixel Hue upto 255
    if(pic[x][y] < 255) {
        pic[x][y]++;
        //std::cout << "Pixel increased" << std::endl;
    }
    return false;
}

void RealConsumer::create_png(){
    //creating a white image
    std::cout << "creating Cimage...";
    using namespace cimg_library;
    CImg<unsigned char> image(10000, 20000, 1, 3, 250);
    std::cout << "done." << '\n';

    //drawing every point
    std::cout << "starting to draw Points...";
    for (int i = 0; i < 10000; ++i) {
        for (int j = 0; j < 20000; ++j) {
            if (pic[i][j] > 0){
                unsigned char color[] = {0, pic[i][j], 0};
                image.draw_point(i, j, color);
            }
        }
    }
    std::cout << "done." << '\n';
    
    std::cout << "saving image" << '\n';
    image.display("Test");

    
    //image.save_png("fern.png");
}
