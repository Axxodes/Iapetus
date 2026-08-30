#include <iostream>
#include <string>
#include <array>
#include "window.hpp"
#include <gpucompute.hpp>

int main()
{
    initialise_window(750,400);
    setupVulkanForIapetus();
}