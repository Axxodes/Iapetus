#pragma once
#include <array>
#include <string>
#include <cstdlib>

#include <vector>

#include "rendererclasses.hpp"

struct Vertex
{
    Vector3 position {};
};

struct PolyMesh
{
    int id {};
    int parentId {0}; // 0 just means the normal workspace

    std::vector<Vertex> Vertices {};
};

int objectCount {};

std::vector<PolyMesh> polyMeshArray {};

std::vector<PolyMesh> returnMeshArray()
{
    return polyMeshArray;
}

void createVertex(Vector3 position)
{
    PolyMesh mesh;
    mesh.id = objectCount++;
    mesh.Vertices.push_back(Vertex{position});
    polyMeshArray.push_back(std::move(mesh));
}