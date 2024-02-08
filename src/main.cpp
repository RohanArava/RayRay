#include<iostream>
#include "./headers/myutils.h"
#include <fstream>


int main()
{
    std::ofstream img("img.ppm", std::ofstream::out | std::ofstream::trunc);
    print_ppm(img);
    return 0;
}