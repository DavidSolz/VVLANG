#ifndef WINDOW_HPP
#define WINDOW_HPP

#define GL_SILENCE_DEPRECATION

#ifdef __WIN32__
    #include <GL/gl.h>
#elif __APPLE__
    #include <OpenGL/gl3.h>
#elif __linux__
    #include <GL/glx.h>
#else
    #error "Platform does not match"
#endif

#include <string>
#include <GLFW/glfw3.h>
#include <functional>
#include <iostream>

class Window
{
private:
    size_t width;
    size_t height;
    GLFWwindow *window;

    void initializeGLFW() const;

    void makeContext(const size_t &width, const size_t &height, const std::string &title);

public:

    Window(const size_t &width = 800, const size_t &height = 600, const std::string &title = "Application");

    const bool shouldClose() const;

    const void attachDelegate( std::function<bool(GLFWwindow *, bool)> delegate) const;

    const void matchFramebufferSize() const;

    const void update() const;

    const size_t & getWidth() const;

    const size_t & getHeight() const;

    const float getAspectRatio() const;

    ~Window();
};

#endif
