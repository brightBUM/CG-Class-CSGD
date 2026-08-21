#include <GLFW/glfw3.h>
#include<iostream>

float red, green, blue;
bool flipColor;

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


int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(1280, 720, "CG_class_csgd", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glfwSetKeyCallback(window, key_callback);


    std::cout << "starting game loop - window setup" << std::endl;
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(red,green,blue, 1.0f);

        glPointSize(10.0f);
        //rendering code
        glBegin(GL_POINT);

        glVertex3f(0.5f, 0.5f, 0.0f);

        glEnd();


        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        //std::cout << "inside game loop" << std::endl;


        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}