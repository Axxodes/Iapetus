#pragma once
#include <string>
#include <array>
#include "rendererclasses.hpp"

class Part
{
	private:
	Vertex vertex1{};
	Vertex vertex2{};
	Vertex vertex3{};
	Vertex vertex4{};
	Vertex vertex5{};
	Vertex vertex6{};
	Vertex vertex7{};
	Vertex vertex8{};
	std::array<Vertex,8> vertices {vertex1,vertex2,vertex3,vertex4,vertex5,vertex6,vertex7,vertex8};
	public:
	std::string name {"Part"};
	Color3 color {};
	Vector3 position {};
    
	void updatePivot()
	{
		// get average of all vertices
	}
};

class Plane
{
	private:
	Vertex vertex1{};
	Vertex vertex2{};
	Vertex vertex3{};
	Vertex vertex4{};
	std::array<Vertex,8> vertices {vertex1,vertex2,vertex3,vertex4};
	public:
	std::string name {"Plane"};
	Color3 color {};
	Vector3 position {};

	void updatePivot()
	{
		// get average of all vertices
	}
};