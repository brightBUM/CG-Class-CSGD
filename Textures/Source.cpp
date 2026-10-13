#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<iostream>  
#include<glm/glm.hpp>
#include<vector>
#include"Shader.h"
#include"Common_Lib.h"

#define STB_IMAGE_IMPLEMENTATION
#include<stb_image.h>
#include "Source.h"

#define Width 800
#define Height 800
#define Gravity -9.8f
#define PI 3.14
#define Log(x) std::cout<<x<<std::endl;


#pragma region GlobalVariables

const float Rad2Deg = 57.29f;
const float Deg2Rad = 0.01745f;
float red, green, blue;
bool flipColor;
float angleinDegrees = 0.0f;
float mixValue = 0.0f;
int pointIndex = -1;

glm::vec3 redColor = glm::vec3(1.0f, 0.0f, 0.0f);  // 0 to 1
glm::vec3 orangeColor = glm::vec3(1.0f, 0.5f, 0.0f);
glm::vec3 whiteColor = glm::vec3(1.0f, 1.0f, 1.0f);
glm::vec3 parrotGreenColor = glm::vec3(0.267f, 0.902f, 0.271f);
glm::vec3 blueColor = glm::vec3(0.0f, 0.0f, 11.0f);

double worldX, worldY;
std::vector<glm::vec3> points;
#pragma endregion

#pragma region FwdDeclaration

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
    //Log("mouse screen pos : " << xpos << " , "<<ypos);
    worldX = xpos / (double)Width * 2.0f - 1.0f;
    worldY = 1.0f - ypos / (double)Height * 2.0f;


}
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
    {
        //std::cout << "space key pressed" << std::endl;
        //flipColor = !flipColor;
        //if (flipColor)
        //{
        //    //color 1
        //    red = 0.451f;
        //    green = 0.608f;
        //    blue = 0.702f;

        //}
        //else
        //{
        //    //color 2
        //    red = 0.78f;
        //    green = 0.765f;
        //    blue = 0.314f;
        //}

        mixValue = mixValue == 1 ? 0 : 1;

       /* mixValue += 0.1f;
        if (mixValue > 1.0f)
            mixValue = 0.0f;*/
    }
}
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
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

#pragma endregion


int main(void)
{

#pragma region WindowCreation
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(Width, Height, "CG_class_csgd", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    //key press callback
    glfwSetKeyCallback(window, key_callback);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    //mousepress and cursor pos
    glfwSetCursorPosCallback(window, cursor_position_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GLFW_TRUE);
    //glad loader
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    glfwSwapInterval(1);
    stbi_set_flip_vertically_on_load(true);
#pragma endregion

#pragma region ShaderSetup



    //triangle winding order - clockwise /anti clockwise point orientation

    float vertices[] = {
        //pos              //col            //texCoords - (u,v)  or (s,t)
       0.5f,  0.5f, 0.0f,  1.0f,0.0f,0.0f,  1.0f,1.0f,  // top right - 0 
       0.5f, -0.5f, 0.0f,  0.0f,1.0f,0.0f,  1.0f,0.0f,  // bottom right - 1
      -0.5f, -0.5f, 0.0f,  1.0f,1.0f,1.0f,  0.0f,0.0f,  // bottom left - 2
      -0.5f,  0.5f, 0.0f,  0.0f,0.0f,1.0f,  0.0f,1.0f,  // top left - 3
    };
    unsigned int indices[] = {  // note that we start from 0!
        0, 1, 3,   // first triangle
        1, 2, 3,   // second triangle
    };

    //VBO - vertex buffer object
    // VAO - vertex attribute object
    // EBO - element buffer object (element/index)
    //binding = selecting
    unsigned int VBO, VAO, EBO;
    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    //attribute parameters
    //1 - layout location in vs
    //2 - size of the attribute
    //5-  total size of vertex
    //6 - offset within the vertex

    //pos
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    //col
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    //texcoord
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    Shader defaultShader("Resources/Shaders/default.vert", "Resources/Shaders/default.frag");
#pragma endregion

    //texture loading
    unsigned int texture_0,texture_1;

    LoadTexture(texture_0, "Resources/Textures/cat_close.png");
    LoadTexture(texture_1, "Resources/Textures/cat_open.png");

    defaultShader.use();
    defaultShader.SetInt("texSampler_0", 0);
    defaultShader.SetInt("texSampler_1", 1);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture_0);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture_1);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

#pragma region RenderLoop
    //glPointSize(8.0f);
    /*glLineWidth(8.0f);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);*/
    float radius = 0.5f;
    std::cout << "starting game loop - basic shapes" << std::endl;

    //fps
    double currentFrameTime =0.0f, prevFrameTime = 0.0f;
    double delta;
    int frameCounter =0;
    float timer=0.0f;
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(red, green, blue, 1.0f);

        //Log("time : "<< glfwGetTime());
        prevFrameTime = currentFrameTime;
        currentFrameTime = glfwGetTime();
        delta = currentFrameTime - prevFrameTime;
        frameCounter++;
        timer += delta;
        if (timer >= 1.0f)
        {
            Log("fps : " << frameCounter);

            frameCounter = 0;
            timer = 0;
        }


        defaultShader.use();
        defaultShader.SetFloat("time", (float)glfwGetTime());
        defaultShader.SetFloat("mixValue",mixValue);

        //defaultShader.SetVec3
        //glDrawArrays(GL_TRIANGLES, 0, 6);

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
#pragma endregion

}