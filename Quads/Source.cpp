#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<iostream>
#include<glm/glm.hpp>

#define Width 800
#define Height 800
#define Gravity -9.8
#define PI 3.14
#define Log(x) std::cout<<x<<std::endl;


#pragma region GlobalVariables


const float Rad2Deg = 57.29f;
const float Deg2Rad = 0.01745f;
glm::vec3 point1 = glm::vec3(1.0f, 0.0f, 0.0f);
glm::vec2 point2 = glm::vec2(1.0f, 0.0f);
float red, green, blue;
bool flipColor;
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
    glPolygonMode(GL_FRONT, GL_LINE);
    Log("gravity value = "<<Gravity);
    Log("Radian to degree "<<Rad2Deg);
    Log("redColor =  "<<red);

    std::cout << "starting game loop - basic shapes" << std::endl;
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(red, green, blue, 1.0f);

        glPointSize(10.0f);
        //rendering code

        //points
        glBegin(GL_POINTS);

        glColor3f(1.0f, 1.0f, 1.0f);

        glVertex3f(0.0f, 0.0f, 0.0f); // 1
        int angleinDegrees = 0;

        for (int i = 0;i <= 360;i += 10)
        {
            angleinDegrees = i;
            glVertex3f(radius * cos(angleinDegrees * Deg2Rad), radius * sin(angleinDegrees * Deg2Rad), 0.0f); // 1

        }


        glEnd();

        //gl_lines - join 1-2 , 3-4 , 5-6
        //gl_line_strip - join 1-2-3-4-5-6
        // gl_line_loop - joine 1-2-3-4-5-6-1

        //gl_triangles - 1-2-3 , 4-5-6
        // gl_traingle_strip - 1-2-3, 2-3-4, 3-4-5, 4-5-6
        //line 
        glLineWidth(5.0f);
        glBegin(GL_TRIANGLE_FAN);

        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex3f(0.0f, 0.0f, 0.0f); // 1
        angleinDegrees = 0;
        glColor3f(1.0f, 0.0f, 0.0f);
        for (int i = 0;i <= 360;i += 10)
        {
            angleinDegrees = i;
            glVertex3f(radius * cos(angleinDegrees * Deg2Rad), radius * sin(angleinDegrees * Deg2Rad), 0.0f); // 1

        }


        glEnd();
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        //std::cout << "inside game loop" << std::endl;


        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
#pragma endregion

}