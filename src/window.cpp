#include "render/window.hpp"

void Window::initializeGLFW() const
{

    if (glfwInit() == GLFW_FALSE)
    {
        std::cerr << "GLFW can not be initialized" << std::endl;
        std::exit(1);
    }
}

Window::Window(const size_t &width, const size_t &height, const std::string &title)
{
    initializeGLFW();
    makeContext(width, height, title);
}

void Window::makeContext(const size_t &width, const size_t &height, const std::string &title)
{
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    glfwMakeContextCurrent(window);

    const GLubyte *version = glGetString(GL_VERSION);

    std::cout << "OpenGL version: " << version << std::endl;
}

const bool Window::shouldClose() const
{
    return !glfwWindowShouldClose(window);
}

const void Window::update() const
{
    glfwPollEvents();
    glfwSwapBuffers(window);
}

const void Window::matchFramebufferSize() const
{
    int display_w, display_h; 
    glfwGetFramebufferSize(window, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);
}

const void Window::attachDelegate(std::function<bool(GLFWwindow *, bool)> delegate) const
{
    delegate(window, true);
}

const size_t &Window::getWidth() const
{
    return width;
}

const size_t &Window::getHeight() const
{
    return height;
}

const float Window::getAspectRatio() const
{
    return width / (float)height;
}

Window::~Window()
{
    glfwDestroyWindow(window);
    glfwTerminate();
}