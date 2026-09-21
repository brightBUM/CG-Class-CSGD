#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<iostream>  
#include<glm/glm.hpp>
#include<vector>
#include"Shader.h"
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
        flipColor = !flipColor;
        if (flipColor)
        {
            //color 1
            red = 0.451f;
            green = 0.608f;
            blue = 0.702f;
        }
        else
        {
            //color 2
            red = 0.78f;
            green = 0.765f;
            blue = 0.314f;
        }

    }
}
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
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
#pragma endregion

#pragma region ShaderSetup
    float vertices[] = {
    //pos               //col
    -0.5f, -0.5f, 0.0f, 1.0f,0.0f,0.0f,
     0.5f, -0.5f, 0.0f, 0.0f,1.0f,0.0f,
     0.0f,  0.5f, 0.0f, 0.0f,0.0f,1.0f
    };

    //VBO - vertex buffer object
    // VAO - vertex attribute object
    //binding = selecting
    unsigned int VBO,VAO;
    glGenBuffers(1, &VBO);  
    glGenVertexArrays(1, &VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //attribute parameters
    //1 - layout location in vs
    //2 - size of the attribute
    //5-  total size of vertex
    //6 - offset within the vertex
    
    //pos
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    //col
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    Shader defaultShader("Resources/Shaders/default.vert", "Resources/Shaders/default.frag");
#pragma endregion


#pragma region RenderLoop


    float radius = 0.5f;
    std::cout << "starting game loop - basic shapes" << std::endl;
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(red, green, blue, 1.0f);

        Log("time : "<< glfwGetTime());

        defaultShader.use();
        defaultShader.SetFloat("time", (float)glfwGetTime());
        glDrawArrays(GL_TRIANGLES, 0, 3);
        
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
#pragma endregion

}