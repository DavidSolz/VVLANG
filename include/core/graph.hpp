#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <unordered_map>
#include <vector>

#include "node.hpp"
#include "link.hpp"

class Graph
{
private:
    std::unordered_map<uint32_t, node> nodes;
    std::vector<link> links;

    Graph(const Graph &graph) = delete;

public:

    Graph() = default;

    void add_node(const node & node);

    void remove_node(const node & node);

    void add_link(const int32_t & from, const int32_t & to);

    bool check_if_exist(const node & node) const;

    bool check_if_exist(const int32_t & node_id) const;

    std::vector<link> get_links(const node & node) const;

    std::vector<link> get_links(const int32_t & node_id) const;

    std::vector<node> get_nodes() const;

    std::vector<link> &get_links();

};

#endif