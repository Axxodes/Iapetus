#pragma once
#include <string>
#include <array>
#include "renderer.hpp"

class Part
{
	public:
	std::string name {"Part"};
	Color3 color {};
	Vector3 position {};
    private:
	std::array<Vertex,8> vertices {Vertex vertex1{},Vertex vertex2{},Vertex vertex3{},Vertex vertex4{},
								  Vertex vertex5{},Vertex vertex6{},Vertex vertex7{},Vertex vertex8{}
								  };
};

class Plane
{
	public:
	std::string name {"Plane"};
	Color3 color {};
	Vector3 position {};
	private:
	std::array<Vertex,8> vertices {Vertex vertex1{},Vertex vertex2{},Vertex vertex3{},Vertex vertex4{}};
};