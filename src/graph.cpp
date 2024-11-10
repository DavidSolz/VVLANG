#include "core/graph.hpp"

void Graph::add_node(const node &node)
{

    auto it = nodes.find(node.guid);

    if (it != nodes.end())
    {
        return;
    }

    nodes[node.guid] = node;
}

void Graph::remove_node(const node &node)
{

    auto it = nodes.find(node.guid);

    if (it == nodes.end())
    {
        return;
    }

    nodes.erase(it);
}

void Graph::add_link(const int32_t &from, const int32_t &to)
{
    if (!check_if_exist(from) or !check_if_exist(to))
    {
        return;
    }

    link edge = (link){from, to};
    links.push_back(edge);
}

bool Graph::check_if_exist(const node &node) const
{
    auto it = nodes.find(node.guid);
    return it != nodes.end();
}

bool Graph::check_if_exist(const int32_t &node_id) const
{
    auto it = nodes.find(node_id);
    return it != nodes.end();
}

std::vector<link> Graph::get_links(const node &node) const
{
    std::vector<link> result;

    if (!check_if_exist(node))
    {
        return result;
    }

    for (const auto &link : links)
    {
        if (node.guid == link.from or node.guid == link.to)
        {
            result.push_back(link);
        }
    }

    return result;
}

std::vector<link> Graph::get_links(const int32_t & node_id) const
{
    std::vector<link> result;

    if (!check_if_exist(node_id))
    {
        return result;
    }

    for (const auto &link : links)
    {
        if (node_id == link.from or node_id == link.to)
        {
            result.push_back(link);
        }
    }

    return result;
}

std::vector<node> Graph::get_nodes() const
{
    std::vector<node> result;

    for( auto [key, value] : nodes)
    {
        result.push_back(value);
    }

    return result;
}

std::vector<link> &Graph::get_links()
{
    return links;
}