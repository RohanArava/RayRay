#ifndef GLTFUTILS_H
#define GLTFUTILS_H

#include "tiny_gltf.h"
#include "triangle.h"

std::vector<float> byte_to_float(tinygltf::Model &model, tinygltf::Accessor &accessor);
triangle primitive_to_triangle(tinygltf::Model &model, tinygltf::Primitive &primitive);
tinygltf::Model load_gltf_model(char *ftype, char *filename);

#endif