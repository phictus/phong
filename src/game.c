#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>

#include "game.h"
#include "renderer.h"

#define PH_DEG2RAD (0.01745329251994329576923690768489f)

static GLFWwindow* window;
static Rect paddle0, paddle1, ball, wall0, wall1, wall2, wall3;
static uint32_t ballRotation;
static float ballSpeed;
static bool started;

static bool phCollision(const Rect* rect0, const Rect* rect1)
{
    if (rect0->x + rect0->w >= rect1->x && rect1->x + rect1->w >= rect0->x)
        if (rect0->y + rect0->h >= rect1->y && rect1->y + rect1->h >= rect0->y)
            return true;
    return false;
}

static void phRestart()
{
    paddle0.x = 0.0f;
    paddle0.y = 285.0f;
    paddle0.w = 20.0f;
    paddle0.h = 150.0f;

    paddle1.x = 1260.0f;
    paddle1.y = 285.0f;
    paddle1.w = 20.0f;
    paddle1.h = 150.0f;

    ball.x = 630;
    ball.y = 350;
    ball.w = 20;
    ball.h = 20;

    ballRotation = rand() % 4;
    ballSpeed = 400.0f;

    started = false;
}

void phInit()
{
    glfwInit();
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    window = glfwCreateWindow(1280, 720, "phong", NULL, NULL);
    glfwMakeContextCurrent(window);
    phInitRenderer();
    glfwSwapInterval(1);
    srand(time(NULL));
}

void phRun()
{
    phRestart();

    wall0.x = -40.0f;
    wall0.y = 0.0f;
    wall0.w = 20.0f;
    wall0.h = 720.0f;

    wall1.x = 1300.0f;
    wall1.y = 0.0f;
    wall1.w = 20.0f;
    wall1.h = 720.0f;

    wall2.x = 0.0f;
    wall2.y = -20.0f;
    wall2.w = 1280.0f;
    wall2.h = 20.0f;

    wall3.x = 0.0f;
    wall3.y = 720.0f;
    wall3.w = 1280.0f;
    wall3.h = 20.0f;

    double lastFrameTime = 0.0, newFrameTime;
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        newFrameTime = glfwGetTime();
        float deltaTime = (float)(newFrameTime - lastFrameTime);
        lastFrameTime = newFrameTime;

        if (!started && glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
            started = true;
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS && !phCollision(&paddle0, &wall2))
            paddle0.y -= 400.0f * deltaTime;
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS && !phCollision(&paddle0, &wall3))
            paddle0.y += 400.0f * deltaTime;
        if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS && !phCollision(&paddle1, &wall2))
            paddle1.y -= 400.0f * deltaTime;
        if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS && !phCollision(&paddle1, &wall3))
            paddle1.y += 400.0f * deltaTime;

        if (phCollision(&ball, &wall2))
        {
            if (ballRotation == 3)
                ballRotation = 0;
            else if (ballRotation == 2)
                ballRotation = 1;
        }
        if (phCollision(&ball, &wall3))
        {
            if (ballRotation == 0)
                ballRotation = 3;
            else if (ballRotation == 1)
                ballRotation = 2;
        }
        if (phCollision(&ball, &paddle0))
        {
            if (ballRotation == 1)
                ballRotation = 0;
            else if (ballRotation == 2)
                ballRotation = 3;
        }
        if (phCollision(&ball, &paddle1))
        {
            if (ballRotation == 0)
                ballRotation = 1;
            else if (ballRotation == 3)
                ballRotation = 2;
        }

        if (started)
        {
            ball.x += cos((ballRotation * 90.0f + 45.0f) * PH_DEG2RAD) * ballSpeed * deltaTime;
            ball.y += sin((ballRotation * 90.0f + 45.0f) * PH_DEG2RAD) * ballSpeed * deltaTime;
            ballSpeed += 10.0f * deltaTime;
        }

        if (phCollision(&ball, &wall0) || phCollision(&ball, &wall1))
            phRestart();

        glClear(GL_COLOR_BUFFER_BIT);

        phRenderRect(&paddle0, Red);
        phRenderRect(&paddle1, Blue);
        phRenderRect(&ball, Yellow);

        glfwSwapBuffers(window);
    }
}

void phDestroy()
{
    phDestroyRenderer();
    glfwDestroyWindow(window);
    glfwTerminate();
}
