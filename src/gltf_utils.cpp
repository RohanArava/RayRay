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

    auto indices = byte_to_double(model, model.accessors[indices_i]);
    auto positions = byte_to_double(model, model.accessors[position_i]);

    std::vector<point3> points;
    for (int i = 0; i < positions.size(); i += 3)
    {
        points.push_back(point3(positions[i], positions[i + 1], positions[i + 2]));
    }

    return triangle(points.at(indices.at(0)), points.at(indices.at(1)), points.at(indices.at(2)), material);
}

std::vector<triangle> parse_model(tinygltf::Model &model)
{
    auto material = std::make_shared<lambertian>(color(0.5, 0.5, 0.5));
    std::vector<triangle> triangles;
    for (int i = 0; i < model.nodes.size(); i++)
    {
        if (model.nodes[i].mesh != -1)
        {
            auto primitives = model.meshes[model.nodes[i].mesh].primitives;
            for (int j = 0; j < primitives.size(); j++)
            {
                auto primitive = primitives[j];
                auto position_i = primitive.attributes.at("POSITION");
                auto positions = byte_to_double(model, model.accessors[position_i]);
                auto indices_i = primitive.indices;
                auto indices = byte_to_double(model, model.accessors[indices_i]);
                std::cout << std::endl;
                std::vector<point3> points;
                for (int i = 0; i < positions.size(); i += 3)
                {
                    points.push_back(point3(positions[i], positions[i + 1], positions[i + 2]));
                }
                for (int i = 0; i < indices.size(); i += 3)
                {
                    triangles.push_back(triangle(points[indices[i]], points[indices[i + 1]], points[indices[i + 2]], material));
                }
            }
        }
    }
    // for (int i = 0; i < triangles.size(); i++)
    // {
    //     std::cout << triangles[i].tri_to_string() << std::endl;
    // }
    return triangles;
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

std::vector<double> byte_to_double(tinygltf::Model &model, tinygltf::Accessor &accessor)
{
    std::vector<double> f_v;
    auto bufferView = model.bufferViews[accessor.bufferView];

    auto size = GetComponentSizeInBytes(accessor.componentType);
    auto count = accessor.count;
    auto num_comps = GetNumComponentsInType(accessor.type);
    auto total_size = count * num_comps;
    auto data = model.buffers[bufferView.buffer].data;

    if (accessor.componentType == TINYGLTF_COMPONENT_TYPE_DOUBLE)
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
            f_v.push_back(double(f));
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
                f_v.push_back(double(f));
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
                f_v.push_back(double(f));
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
                f_v.push_back(double(f));
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
                f_v.push_back(double(f));
            }
        }
        else if (accessor.componentType == TINYGLTF_COMPONENT_TYPE_FLOAT)
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
                f_v.push_back(double(f));
            }
        }
    }
    return f_v;
}