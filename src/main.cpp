#include <cmath>
#include "render/viewport.hpp"
#include "core/node_draft_parser.hpp"

int main(int argc, char const *argv[])
{
    Viewport window(800, 600, "Visual C");

    while (window.shouldClose())
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.5f, 0.5f, 1.0f, 1.0f);

        window.matchFramebufferSize();
        window.update();
    }

    return 0;
}
