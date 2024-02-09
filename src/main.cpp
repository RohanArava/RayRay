#include<iostream>
#include "./headers/myutils.h"
#include <fstream>


int main(int argc, char *argv[])
{
    if (argc < 2) {
        print_ppm(std::cout);
        return 0;
    }
    std::ofstream img(argv[1], std::ofstream::out | std::ofstream::trunc);
    print_ppm(img);
    return 0;
}