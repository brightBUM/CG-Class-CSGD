// Common_Lib.cpp : Defines the functions for the static library.
//

#include "pch.h"
#include "framework.h"
#include"Shader.h"
#include"Common_Lib.h"
// TODO: This is an example of a library function
void fnCommonLib()
{
}
namespace Utility
{
    double currentFrameTime = 0.0f;
    double prevFrameTime = 0.0f;
    double delta = 0.0f;
    int frameCounter = 0;
    float timer = 0.0f;

	void FPSCounter(GLFWwindow* window)
	{
        prevFrameTime = currentFrameTime;
        currentFrameTime = glfwGetTime();
        delta = currentFrameTime - prevFrameTime;
        frameCounter++;
        timer += delta;
        if (timer >= 1.0f)
        {
            std::string title = "CG Class | FPS : " + 
                std::to_string(frameCounter)+" | delta : "+ std::to_string(delta);
            glfwSetWindowTitle(window, title.c_str());
            frameCounter = 0;
            timer = 0;
        }
	}
    void LoadTexture(unsigned int& texture, const char* path)
    {
        int width, height, nrChannels;

        unsigned char* data = stbi_load(path, &width, &height, &nrChannels, 0);
        Log("nrChannels in texture : " << nrChannels);
        //generating texture object
        glGenTextures(1, &texture);

        //selecting/binding the current texture
        glBindTexture(GL_TEXTURE_2D, texture);
        //wrap settings 
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        //creating the 2D texture and passing the data into it 
        if (data)
        {
            Log("Loaded Texture : " << path);
            switch (nrChannels)
            {
            case 3:
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
                break;
            case 4:
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
                break;
            default:
                break;
            }
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
        {
            Log("Failed to Load Texture : " << path);

        }


        //unloading the data object;
        stbi_image_free(data);
    }
}


