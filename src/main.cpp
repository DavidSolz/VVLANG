#include <cmath>
#include "render/window.hpp"
#include "core/node_draft_parser.hpp"

int main(int argc, char const *argv[])
{

    NodeDraftParser parser;

    std::vector<node_draft> drafts = parser.parseDirectory("blocks");

    const char * nodeTypes[NUM_NODE_TYPES] = NODE_TYPE_STR;
    const char * slotTypes[NUM_SLOT_TYPES] = SLOT_TYPE_STR;

    for(const auto & draft : drafts)
    {
        std::cout << "=========[ Node ]=========" << std::endl;
        std::cout << "Label: " + draft.name << std::endl;
        std::cout << "Type: " + std::string(nodeTypes[draft.type]) << std::endl;
        std::cout << "Inputs: " << draft.numInput << std::endl;

        for(int32_t item = 0; item < draft.numInput; item++)
        {
            std::cout << "\tType: " + std::string(slotTypes[draft.input[item].type]) << std::endl;
        }

        std::cout << "Outputs: " << draft.numOutput << std::endl;
        for(int32_t item = 0; item < draft.numOutput; item++)
        {
            std::cout << "\tType: " + std::string(slotTypes[draft.output[item].type]) << std::endl;
        }
    }

    return 0;

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
