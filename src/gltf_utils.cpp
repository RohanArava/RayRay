#include <iostream>
#include "./headers/gltf_utils.h"
#include "./headers/triangle.h"
#include "./headers/material.h"

using namespace tinygltf;

triangle primitive_to_triangle(tinygltf::Model &model, tinygltf::Primitive &primitive)
{
    auto material = std::make_shared<lambertian>(color(0.9, 0.5, 0.5));
    auto pos_at = primitive.attributes.find("POSITION");
    if (pos_at == primitive.attributes.end())
    {
        return triangle(point3(0, 0, 0), point3(0, 0, 0), point3(0, 0, 0), material);
    }
    auto position_i = primitive.attributes.at("POSITION");
    auto indices_i = primitive.indices;

    auto indices = byte_to_float(model, model.accessors[indices_i]);
    auto positions = byte_to_float(model, model.accessors[position_i]);

    std::vector<point3> points;
    for(int i=0; i < positions.size(); i+=3){
        points.push_back(point3(positions[i], positions[i+1], positions[i+2]));
    }

    return triangle(points.at(indices.at(0)), points.at(indices.at(1)), points.at(indices.at(2)), material);
}

tinygltf::Model load_gltf_model(char *ftype, char *filename)
{
    Model model;
    TinyGLTF loader;
    std::string err;
    std::string warn;

    bool ret = "glb" == std::string(ftype) ? loader.LoadBinaryFromFile(&model, &err, &warn, filename) : loader.LoadASCIIFromFile(&model, &err, &warn, filename);

    if (!warn.empty())
    {
        printf("Warn: %s\n", warn.c_str());
        return model;
    }

    if (!err.empty())
    {
        printf("Err: %s\n", err.c_str());
        exit(0);
    }

    if (!ret)
    {
        printf("Failed to parse glTF\n");
        exit(0);
    }
    return model;
}

std::vector<float> byte_to_float(tinygltf::Model &model, tinygltf::Accessor &accessor)
{
    std::vector<float> f_v;
    auto bufferView = model.bufferViews[accessor.bufferView];

    auto size = GetComponentSizeInBytes(accessor.componentType);
    auto count = accessor.count;
    auto num_comps = GetNumComponentsInType(accessor.type);
    auto total_size = count * num_comps;
    auto data = model.buffers[bufferView.buffer].data;

    if (accessor.componentType == TINYGLTF_COMPONENT_TYPE_FLOAT)
    {
        for (int i = bufferView.byteOffset; i < bufferView.byteOffset + bufferView.byteLength; i += size)
        {
            unsigned char b[4];
            b[0] = data[i];
            b[1] = data[i + 1];
            b[2] = data[i + 2];
            b[3] = data[i + 3];
            float f;
            memcpy(&f, &b, sizeof(f));
            f_v.push_back(float(f));
        }
    }
    else
    {
        if (accessor.componentType == TINYGLTF_COMPONENT_TYPE_UNSIGNED_SHORT)
        {
            for (int i = bufferView.byteOffset; i < bufferView.byteOffset + bufferView.byteLength; i += size)
            {
                unsigned char b[2];
                b[0] = data[i];
                b[1] = data[i + 1];
                unsigned short f;
                memcpy(&f, &b, sizeof(f));
                f_v.push_back(float(f));
            }
        }
        else if (accessor.componentType == TINYGLTF_COMPONENT_TYPE_UNSIGNED_INT)
        {
            for (int i = bufferView.byteOffset; i < bufferView.byteOffset + bufferView.byteLength; i += size)
            {
                unsigned char b[4];
                b[0] = data[i];
                b[1] = data[i + 1];
                b[2] = data[i + 2];
                b[3] = data[i + 3];
                unsigned int f;
                memcpy(&f, &b, sizeof(f));
                f_v.push_back(float(f));
            }
        }
        else if (accessor.componentType == TINYGLTF_COMPONENT_TYPE_SHORT)
        {
            for (int i = bufferView.byteOffset; i < bufferView.byteOffset + bufferView.byteLength; i += size)
            {
                unsigned char b[2];
                b[0] = data[i];
                b[1] = data[i + 1];
                short f;
                memcpy(&f, &b, sizeof(f));
                f_v.push_back(float(f));
            }
        }
        else if (accessor.componentType == TINYGLTF_COMPONENT_TYPE_INT)
        {
            for (int i = bufferView.byteOffset; i < bufferView.byteOffset + bufferView.byteLength; i += size)
            {
                unsigned char b[4];
                b[0] = data[i];
                b[1] = data[i + 1];
                b[2] = data[i + 2];
                b[3] = data[i + 3];
                int f;
                memcpy(&f, &b, sizeof(f));
                f_v.push_back(float(f));
            }
        }
        else if (accessor.componentType == TINYGLTF_COMPONENT_TYPE_DOUBLE)
        {
            for (int i = bufferView.byteOffset; i < bufferView.byteOffset + bufferView.byteLength; i += size)
            {
                unsigned char b[8];
                b[0] = data[i];
                b[1] = data[i + 1];
                b[2] = data[i + 2];
                b[3] = data[i + 3];
                b[0] = data[i + 4];
                b[1] = data[i + 5];
                b[2] = data[i + 6];
                b[3] = data[i + 7];
                double f;
                memcpy(&f, &b, sizeof(f));
                f_v.push_back(float(f));
            }
        }
    }
    return f_v;
}