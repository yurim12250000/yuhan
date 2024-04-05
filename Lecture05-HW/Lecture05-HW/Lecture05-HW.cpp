#pragma comment(lib, "Opengl32.lib")

#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>

float moveFactorX = 0.0f;
float moveFactorY = 0.0f;
float scaleFactor = 1.0f;
bool leftMouseDown = false;
bool rightMouseDown = false;
double lastMouseX, lastMouseY;

void errorCallback(int error, const char* description)
{
    std::cerr << "GLFW Error: " << description << std::endl;
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        leftMouseDown = true;
        glfwGetCursorPos(window, &lastMouseX, &lastMouseY);
    }
    else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
    {
        leftMouseDown = false;
    }
    else if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
    {
        rightMouseDown = true;
        glfwGetCursorPos(window, &lastMouseX, &lastMouseY);
    }
    else if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE)
    {
        rightMouseDown = false;
    }
}

void cursorPosCallback(GLFWwindow* window, double xpos, double ypos)
{
    if (leftMouseDown)
    {
        double deltaX = xpos - lastMouseX;
        double deltaY = ypos - lastMouseY;
        moveFactorX += static_cast<float>(deltaX) / 100.0f;
        moveFactorY -= static_cast<float>(deltaY) / 100.0f;
        lastMouseX = xpos;
        lastMouseY = ypos;
    }
    else if (rightMouseDown)
    {
        double deltaX = xpos - lastMouseX;
        double deltaY = ypos - lastMouseY;
        double diff = deltaX - deltaY;
        scaleFactor += static_cast<float>(diff) / 100.0f;
        lastMouseX = xpos;
        lastMouseY = ypos;
    }
}

void drawStar(float x, float y, float radius)
{
    const float PI = 3.14159265f;
    const int numTriangles = 5;
    const float angleIncrement = 2 * PI / numTriangles;

    glBegin(GL_TRIANGLES);

    glColor3f(1.0f, 1.0f, 1.0f);

    for (int i = 0; i < numTriangles; ++i)
    {

        float angle1 = i * 2 * angleIncrement;
        float angle2 = (i * 2 + 1) * angleIncrement;
        float angle3 = (i * 2 + 2) * angleIncrement;

        float x1 = x + cos(angle1) * radius;
        float y1 = y + sin(angle1) * radius;

        float x2 = x + cos(angle2) * (radius / 2);
        float y2 = y + sin(angle2) * (radius / 2);

        float x3 = x + cos(angle3) * radius;
        float y3 = y + sin(angle3) * radius;

        glVertex2f(x1, y1);
        glVertex2f(x2, y2);
        glVertex2f(x3, y3);
    }

    glEnd();
}

void render()
{
    glPushMatrix();
    glTranslatef(moveFactorX, moveFactorY, 0.0f);
    glScalef(scaleFactor, scaleFactor, 1.0f);

    drawStar(0.0f, 0.0f, 0.1f);

    glPopMatrix();
}

int main(void)
{
    if (!glfwInit())
        return -1;

    GLFWwindow* window;
    window = glfwCreateWindow(800, 600, "Star Drawing", NULL, NULL);

    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetErrorCallback(errorCallback);
    glfwSetKeyCallback(window, keyCallback);
    glfwSetMouseButtonCallback(window, mouseButtonCallback);
    glfwSetCursorPosCallback(window, cursorPosCallback);

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        render();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
