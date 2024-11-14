#include "core/graph.hpp"

bool Graph::checkNodeValidity(const id_pair &pair) const
{
    auto selectedNode = nodes.find(pair.parent);

    if (selectedNode == nodes.end())
    {
        std::cerr << "Error: Node " + std::to_string(pair.parent) + " does not exist in graph context" << std::endl;
        return false;
    }

    if (pair.child < 0 or pair.child > selectedNode->second.draft->numInput)
    {
        std::cerr << "Error: Invalid slot inside node " + std::to_string(pair.parent) << std::endl;
        return false;
    }

    return true;
}

void Graph::setTypeDeductionPolicy(const deduction_type &mode)
{
    policy.setMode(mode);
}

void Graph::addNode(node_draft *draft)
{
    int32_t guid = nodeCounter++;

    node newNode = (node){guid, Vector2(), draft};

    newNode.input.resize(draft->numInput);
    newNode.output.resize(draft->numOutput);

    nodes[guid] = newNode;
}

bool Graph::linkRequest(const id_pair &from, const id_pair &to)
{

    if (checkNodeValidity(from) == false or checkNodeValidity(to) == false)
    {
        std::cerr << "Error: Invalid link" << std::endl;
        return false;
    }

    node &first = nodes[from.parent];
    node &second = nodes[to.parent];

    slot_type deducedType = policy.deduceType(first.draft->possibleTypes, second.draft->possibleTypes);

    if (deducedType == policy.getDefaultType())
    {
        std::cerr << "Error: no compatible types found." << std::endl;
        return false;
    }

    first.output[from.child].type = deducedType;
    second.input[to.child].type = deducedType;

    link l = (link){from, to};

    links[from.parent].push_back(l);
    // links[to.parent].push_back(l); // Need to consider if edge must be bi-directional

    return true;
}
