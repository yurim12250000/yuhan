#pragma comment(lib, "Opengl32.lib")

#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>
#include <cstdlib> // srand, rand 함수를 사용하기 위한 헤더 파일
#include <ctime>   // 시간을 기반으로 랜덤 시드를 설정하기 위한 헤더 파일

void drawStar(float x, float y, float radius)
{
    const float PI = 3.14159265f;
    const int numTriangles = 5;
    const float angleIncrement = 2 * PI / numTriangles;

    glBegin(GL_TRIANGLES);
    glColor3f(static_cast<float>(rand()) / RAND_MAX, static_cast<float>(rand()) / RAND_MAX, static_cast<float>(rand()) / RAND_MAX); // 랜덤한 색상

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
    // 랜덤 시드 초기화
    srand(static_cast<unsigned int>(time(0)));

    // 300개의 랜덤한 별 그리기
    for (int i = 0; i < 300; ++i)
    {
        float x = static_cast<float>(rand() % 800) / 800.0f; // 0에서 1 사이의 랜덤한 x 위치
        float y = static_cast<float>(rand() % 600) / 600.0f; // 0에서 1 사이의 랜덤한 y 위치
        float radius = 0.05f;                                  // 별 크기를 반으로 줄임
        drawStar(x, y, radius);
    }
}

int main(void)
{
    if (!glfwInit()) {
        std::cerr << "GLFW initialization failed!" << std::endl;
        return -1;
    }

    GLFWwindow* window;
    window = glfwCreateWindow(1600, 1200, "Star Drawing", NULL, NULL);

    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

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