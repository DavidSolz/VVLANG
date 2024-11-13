#include "render/viewport.hpp"

void Viewport::initializeGLFW() const
{

    if (glfwInit() == GLFW_FALSE)
    {
        std::cerr << "GLFW can not be initialized" << std::endl;
        std::exit(1);
    }
}

Viewport::Viewport(const size_t &width, const size_t &height, const std::string &title)
{
    initializeGLFW();
    makeContext(width, height, title);
}

void Viewport::makeContext(const size_t &width, const size_t &height, const std::string &title)
{
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    glfwMakeContextCurrent(window);

    const GLubyte *version = glGetString(GL_VERSION);

    std::cout << "OpenGL version: " << version << std::endl;
}

const bool Viewport::shouldClose() const
{
    return !glfwWindowShouldClose(window);
}

const void Viewport::update() const
{
    glfwPollEvents();
    glfwSwapBuffers(window);
}

const void Viewport::matchFramebufferSize() const
{
    int display_w, display_h;
    glfwGetFramebufferSize(window, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);
}

const void Viewport::attachDelegate(std::function<bool(GLFWwindow *, bool)> delegate) const
{
    delegate(window, true);
}

const size_t &Viewport::getWidth() const
{
    return width;
}

const size_t &Viewport::getHeight() const
{
    return height;
}

const float Viewport::getAspectRatio() const
{
    return width / (float)height;
}

Viewport::~Viewport()
{
    glfwDestroyWindow(window);
    glfwTerminate();
}
