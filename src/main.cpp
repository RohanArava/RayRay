#define TINYGLTF_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "./headers/gltf_utils.h"
#include "./headers/myutils.h"

int main(int argc, char *argv[])
{
    if (argc < 4) {
        std::cout << "please provide all params" << "\n";
        return 0;
    }
    std::ofstream img(argv[1], std::ofstream::out | std::ofstream::trunc);
    
    print_ppm(img, argv[2], argv[3], true);
    return 0;
}