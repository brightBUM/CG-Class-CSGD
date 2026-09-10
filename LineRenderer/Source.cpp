#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<iostream>
#include<glm/glm.hpp>
#include<vector>

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
bool PointInCircleCheck(glm::vec3 centre, float radius, glm::vec3 point)
{
    auto distance = glm::distance(centre, point);
    Log(distance);
    return distance < radius;
}
void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
    //Log("mouse screen pos : " << xpos << " , "<<ypos);
    worldX = xpos / (double)Width * 2.0f - 1.0f;
    worldY = 1.0f - ypos / (double)Height * 2.0f;
    
    
}
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
    {
        Log("right mouse pressed");
        Log("mouse world pos : " << worldX << " , " << worldY);
        points.push_back(glm::vec3(worldX, worldY, 0.0f));
    }
    if (button == GLFW_MOUSE_BUTTON_LEFT && (action == GLFW_PRESS))
    {
        if (pointIndex != -1)
            return;

        for (int i = 0;i < points.size();i++)
        {
            if (PointInCircleCheck(points[i], 0.2f, glm::vec3(worldX, worldY, 0.0f)))
            {
                //cursor in range of this point 
                //pick up
                pointIndex = i;
            }
        }
        
        
    }
    if (button == GLFW_MOUSE_BUTTON_LEFT && (action == GLFW_RELEASE))
    {
        pointIndex = -1;
        //-1 meaning free to select new point

    }
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

#pragma region RenderLoop

   
    points.push_back(glm::vec3(0.0f));
    points.push_back(glm::vec3(0.5f, 0.0f, 0.0f));
    
    float radius = 0.5f;
    std::cout << "starting game loop - basic shapes" << std::endl;
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(red, green, blue, 1.0f);


        //input code
        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1))
        {
            /*Log("left click held");*/
            if (pointIndex != -1)
            {
                points[pointIndex] = glm::vec3(worldX, worldY, 0.0f);
            }
        }

        //rendering code
        glLineWidth(5.0f);
        glPointSize(10.0f);
        //points
        glBegin(GL_POINTS);
        DefineColor(whiteColor);
        for (int i = 0;i < points.size() - 1;i++)
        {
            DrawVertex(points[i]);
            DrawVertex(points[i + 1]);
        }

        glEnd();
        //lines
        glBegin(GL_LINES);
        DefineColor(orangeColor);
        for (int i = 0;i < points.size()-1;i++)
        { 
            DrawVertex(points[i]);
            DrawVertex(points[i + 1]);
        }

        glEnd();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
#pragma endregion

}