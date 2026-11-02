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

struct Ray
{
    Vector3 start {};
    Vector3 direction {};
};

struct Object
{
    int id {};
    int parentId {0}; // 0 just means the normal workspace
};

struct PolyMesh : public Object
{
    std::vector<Vertex> Vertices {};
    Color3 color {};
};

struct Camera : public Object
{
    int cameraAngle {};
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

void createTriangle(Vector3 positionVertex1,Vector3 positionVertex2,Vector3 positionVertex3)
{
    PolyMesh mesh;
    mesh.id = objectCount++;
    mesh.Vertices.push_back(Vertex{positionVertex1});
    mesh.Vertices.push_back(Vertex{positionVertex2});
    mesh.Vertices.push_back(Vertex{positionVertex3});

    polyMeshArray.push_back(std::move(mesh));
}