#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>
#include <list>
#include <unordered_map>
#include <algorithm>

#include "node.hpp"
#include "link.hpp"
#include "deduction_policy.hpp"

class Graph
{
private:
    std::unordered_map<int32_t, node> nodes;
    std::unordered_map<int32_t, std::list<link> > links;

    DeductionPolicy policy;

    int32_t nodeCounter = 0;

    Graph(const Graph &graph) = delete;

    bool checkNodeValidity(const id_pair & pair) const;

public:
    Graph() = default;

    void addNode(node_draft *draft);

    void setTypeDeductionPolicy(const deduction_type & mode);

    bool linkRequest(const id_pair &from, const id_pair &to);
};

#endif
