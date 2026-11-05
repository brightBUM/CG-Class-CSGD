#pragma once
#include<GLFW/glfw3.h>
#include<stb_image.h>
namespace Utility
{
    //fps

    void FPSCounter(GLFWwindow* window);
    void LoadTexture(unsigned int& texture, const char* path);
}
