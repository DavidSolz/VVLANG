#include <cmath>
#include "render/window.hpp"
#include "core/graph.hpp"

int main(int argc, char const *argv[])
{

    Window window(800, 600, "Visual C");

    while (window.shouldClose())
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.5f, 0.5f, 1.0f, 1.0f);

        window.matchFramebufferSize();
        window.update();
    }

    return 0;
}
