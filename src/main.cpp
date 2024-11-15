#include <cmath>
#include "render/viewport.hpp"
#include "core/graph.hpp"
#include "core/node_draft_parser.hpp"

int main(int argc, char const *argv[])
{

    NodeDraftParser parser;

    auto drafts = parser.parseDirectory("blocks");

    Graph g;
    g.setTypeDeductionPolicy(deduction_type::COERCIVE);

    g.addNode(&drafts[2]); // 0
    g.addNode(&drafts[0]); // 1

    id_pair first = (id_pair){0, 0};
    id_pair second = (id_pair){1, 0};

    g.linkRequest(first, second); // Valid connection
    g.linkRequest(first, second); // Check for error

    // Viewport window(800, 600, "Visual C");

    // while (window.shouldClose())
    // {
    //     glClear(GL_COLOR_BUFFER_BIT);
    //     glClearColor(0.5f, 0.5f, 1.0f, 1.0f);

    //     window.matchFramebufferSize();
    //     window.update();
    // }

    return 0;
}
