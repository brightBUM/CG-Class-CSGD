#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<iostream>
#include<glm/glm.hpp>

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

glm::vec3 A = glm::vec3(-0.5f, 0.5f, 0.0f); //-1 to 1
glm::vec3 B = glm::vec3(0.5f, 0.5f, 0.0f);
glm::vec3 C = glm::vec3(0.5f, -0.5f, 0.0f);
glm::vec3 D = glm::vec3(-0.5f, -0.5f, 0.0f);

glm::vec3 redColor = glm::vec3(1.0f, 0.0f, 0.0f);  // 0 to 1
glm::vec3 orangeColor = glm::vec3(1.0f, 0.5f, 0.0f);
glm::vec3 whiteColor = glm::vec3(1.0f, 1.0f, 1.0f);
glm::vec3 parrotGreenColor = glm::vec3(0.267f, 0.902f, 0.271f);
glm::vec3 blueColor = glm::vec3(0.0f, 0.0f, 11.0f);
#pragma endregion

#pragma region FwdDeclaration

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
void DrawVertex(glm::vec3 point)
{
    glVertex3f(point.x, point.y, point.z);
}
void DefineColor(glm::vec3 color)
{
    glColor3f(color.x, color.y, color.z);
}
void DefineRect(glm::vec3 origin, float length, float breadth)
{
    DrawVertex(origin);
    DrawVertex(glm::vec3(origin.x + length, origin.y, 0.0f));
    DrawVertex(glm::vec3(origin.x + length, origin.y - breadth, 0.0f));
    DrawVertex(glm::vec3(origin.x, origin.y - breadth, 0.0f));
}
void DefineCircle(glm::vec3 centre, float radius)
{
    glVertex3f(0.0f, 0.0f, 0.0f); // 1
    angleinDegrees = 0;
    for (int i = 0;i <= 360;i += 15)
    {
        angleinDegrees = i;
        glVertex3f(radius * cos(angleinDegrees * Deg2Rad), radius * sin(angleinDegrees * Deg2Rad), 0.0f); // 1

    }
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

    glfwSetKeyCallback(window, key_callback);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    //glad loader
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
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

        //rendering code

#pragma region IndianFlag
        //glPolygonMode(GL_FRONT, GL_LINE);
        //glLineWidth(3.0f);
        ////orange color
        //DefineColor(orangeColor);
        //glBegin(GL_QUADS);

        //DefineRect(glm::vec3(-1.0f, 0.9f, 0.f), 2.0f, 0.6f);

        //glEnd();

        ////white color
        //DefineColor(whiteColor);
        //glBegin(GL_QUADS);

        //DefineRect(glm::vec3(-1.0f, 0.3f, 0.f), 2.0f, 0.6f);

        //glEnd();

        ////green color
        //DefineColor(parrotGreenColor);
        //glBegin(GL_QUADS);

        //DefineRect(glm::vec3(-1.0f, -0.3f, 0.f), 2.0f, 0.6f);

        //glEnd();

        ////ashok chakra
        //DefineColor(blueColor);
        //glBegin(GL_TRIANGLE_FAN);

        //DefineCircle(glm::vec3(0.0f, 0.0f, 0.0f), 0.3f);

        //glEnd();
#pragma endregion

#pragma region JapanFlag
        glPolygonMode(GL_FRONT, GL_FILL);

        //white color
        DefineColor(whiteColor);
        glBegin(GL_QUADS);

        DefineRect(glm::vec3(-1.0f, 0.8f, 0.f), 2.0f, 1.6f);

        glEnd();
        //red circle
        DefineColor(redColor);
        glBegin(GL_TRIANGLE_FAN);

        DefineCircle(glm::vec3(0.0f, 0.0f, 0.0f), 0.3f);

        glEnd();
#pragma endregion

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
#pragma endregion

}