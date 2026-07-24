#include <iostream>
#include <GLFW/glfw3.h>

void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}



int main()
{
	if (!glfwInit())
{
    // Initialization failed
}

	GLFWwindow* window = glfwCreateWindow(640, 480, "Iapetus game engine", NULL, NULL);
	if (!window)
	{
    	// Window or OpenGL context creation failed
	}
}