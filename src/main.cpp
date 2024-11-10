
#include <cmath>

#include "render/window.hpp"
#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

#include "core/graph.hpp"

void draw_node(node &n, int32_t &selectedNode)
{
    ImVec2 nodePos = ImVec2(n.position.x(), n.position.y());

    ImGui::SetNextWindowPos(nodePos, ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(200.0f, 150.0f), ImGuiCond_Always);

    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.2f, 0.3f, 0.5f, 1.0f));
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 5.0f);

    ImGui::Begin(n.name.c_str(), nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar);

    ImGui::Text("GUID: %d", n.guid);
    ImGui::Text("Name: %s", n.name.c_str());
    ImGui::Text("Position: (%0.3f, %0.3f)", n.position.x(), n.position.y());

    ImGui::Separator();
    ImGui::BulletText("Input 1");
    ImGui::BulletText("Input 2");

    ImGui::Separator();
    ImGui::BulletText("Output 1");
    ImGui::BulletText("Output 2");

    if (ImGui::IsMouseClicked(0) && ImGui::IsWindowHovered(ImGuiHoveredFlags_ChildWindows))
    {
        selectedNode = n.guid;
    }

    if (selectedNode == n.guid && ImGui::IsMouseDragging(0))
    {
        ImVec2 delta = ImGui::GetMouseDragDelta();
        n.position += Vector2(delta.x, delta.y);
        ImGui::ResetMouseDragDelta();
    }


    ImGui::End();

    ImGui::PopStyleColor();
    ImGui::PopStyleVar();
}

void draw_edges(const std::vector<node> &nodes, const std::vector<link> &links)
{

    ImDrawList *draw_list = ImGui::GetForegroundDrawList();

    for (const link &edge : links)
    {
        Vector2 begin;
        Vector2 end;

        for (const node &n : nodes)
        {
            if (n.guid == edge.from)
            {
                begin = n.position;
            }

            if (n.guid == edge.to)
            {
                end = n.position;
            }
        }

        ImVec2 fromPos = ImVec2(begin.x(), begin.y());
        ImVec2 toPos = ImVec2(end.x(), end.y());

        draw_list->AddLine(fromPos, toPos, IM_COL32(200, 200, 100, 255), 2.0f);
        ImGui::Text(("Edge from: " + std::to_string(edge.from) + " to: " + std::to_string(edge.to)).c_str());
    }
}

int main(int argc, char const *argv[])
{

    Window window(800, 600, "Visual C");

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGui::StyleColorsDark();

    window.attachDelegate(ImGui_ImplGlfw_InitForOpenGL);
    ImGui_ImplOpenGL3_Init("#version 130");

    int32_t counter = 0;

    Graph g;

    g.add_node(
        (node){
            counter++,
            (Vector2){400.0f, 300.0f},
            "Example"});

    std::vector<node> nodes = g.get_nodes();
    std::vector<link> links = g.get_links();

    int32_t fromNodeID = 0;
    int32_t toNodeID = 0;
    int32_t selectedNode = -1;

    while (window.shouldClose())
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.5f, 0.5f, 1.0f, 1.0f);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin("Control Panel");

        if (ImGui::Button("Add Node"))
        {
            g.add_node(
                (node){
                    counter,
                    (Vector2){400, 300},
                    "node_" + std::to_string(counter++)});
            std::cout << "New node added" << std::endl;
            nodes = g.get_nodes();
        }

        ImGui::Separator();

        ImGui::InputInt("From Node ID", &fromNodeID);
        ImGui::InputInt("To Node ID", &toNodeID);

        if (ImGui::Button("Add Edge"))
        {
            if (g.check_if_exist(fromNodeID) && g.check_if_exist(toNodeID) && fromNodeID != toNodeID)
            {
                g.add_link(fromNodeID, toNodeID);
                links = g.get_links();
                std::cout << "New link added" << std::endl;
            }
            else
            {
                std::cout << "Invalid Node IDs or IDs are identical" << std::endl;
            }
        }

        ImGui::Text(("Selected node: " + std::to_string(selectedNode)).c_str());

        ImGui::End();

        ImGui::Begin("Graph window");
        draw_edges(nodes, links);
        ImGui::End();

        if (ImGui::IsMouseClicked(0) && !ImGui::IsAnyItemHovered())
        {
            selectedNode = -1;
        }

        for (auto &node : nodes)
        {
            draw_node(node, selectedNode);
        }

        ImGui::Render();

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        window.matchFramebufferSize();
        window.update();
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    return 0;
}
