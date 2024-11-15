#include "core/graph.hpp"

bool Graph::checkNodeValidity(const id_pair &pair) const
{
    auto selectedNode = nodes.find(pair.parent);

    if (selectedNode == nodes.end())
    {
        std::cerr << "Error: Node " + std::to_string(pair.parent) + " does not exist" << std::endl;
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

    if (first.draft->numOutput <= from.child)
    {
        std::cerr << "Error: Invalid number of output slots: " << first.draft->numOutput << std::endl;
        return false;
    }

    node &second = nodes[to.parent];

    if (second.draft->numInput <= to.child)
    {
        std::cerr << "Error: Invalid number of input slots: " << second.draft->numInput << std::endl;
        return false;
    }

    slot_type deducedType = policy.deduceType(first.draft->possibleTypes, second.draft->possibleTypes);

    const char *typeNames[NUM_SLOT_TYPES] = SLOT_TYPE_STR;
    std::cout << "Selected: " << typeNames[deducedType] << " as most compatible type" << std::endl;

    if (deducedType == policy.getDefaultType())
    {
        std::cerr << "Error: No compatible types found." << std::endl;
        return false;
    }

    link l = (link){from, to};

    first.output[from.child].type = deducedType;
    second.input[to.child].type = deducedType;

    std::list<link> &currentConnections = links[from.parent];

    bool found = std::find_if(currentConnections.begin(), currentConnections.end(),
                              [&l](const auto &connection)
                              {
                                  return connection.hash() == l.hash();
                              }) != currentConnections.end();

    if (found == true)
    {
        std::cerr << "Error: Link already exist" << std::endl;
        return false;
    }

    links[from.parent].push_back(l);

    return true;
}
