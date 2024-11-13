#include "core/node_draft_parser.hpp"

void NodeDraftParser::parseArray(slot *array, const size_t &size, const tinyjson::element &json) const
{
    if (json.is_array() == false or json.size() < size)
    {
        std::cerr << "Warning: Input types array size does not match numInputs" << std::endl;
        return;
    }

    int32_t overlapSize = std::max(static_cast<size_t>(0), std::min(json.size(), size));

    std::string type;
    for (int32_t i = 0; i < overlapSize; i++)
    {
        json[i].as_str(&type);
        array[i].type = parseSlotType(type);
    }
}

node_type NodeDraftParser::parseNodeType(const std::string &type) const
{
    node_type nodeType;

    const char *types[NUM_NODE_TYPES] = NODE_TYPE_STR;

    for (int32_t item = 0; item < NUM_NODE_TYPES; item++)
    {

        if (type == types[item])
        {
            nodeType = static_cast<node_type>(item);
            break;
        }
    }

    return nodeType;
}

slot_type NodeDraftParser::parseSlotType(const std::string &type) const
{
    slot_type slotType;

    const char *types[NUM_SLOT_TYPES] = SLOT_TYPE_STR;

    for (int32_t item = 0; item < NUM_SLOT_TYPES; item++)
    {

        if (type == types[item])
        {
            slotType = static_cast<slot_type>(item);
            break;
        }
    }

    return slotType;
}

node_draft NodeDraftParser::parseDraft(const tinyjson::element &json) const
{
    node_draft draft;

    if (json.is_object() == false)
    {
        std::cerr << "Invalid type of object" << std::endl;
        return draft;
    }

    if (json.contains("label"))
    {
        json["label"].as_str(&draft.name);
    }

    if (json.contains("type"))
    {
        std::string type;
        json["type"].as_str(&type);
        draft.type = parseNodeType(type);
    }

    if (json.contains("numInputs"))
    {
        json["numInputs"].as_number<int32_t>(&draft.numInput);

        if (draft.numInput < 0)
        {
            draft.name = "";
            std::cout << "Number of inputs cannot be lesser than 0" << std::endl;
            return draft;
        }

        draft.input = new slot[draft.numInput];
    }

    if (json.contains("numOutputs"))
    {
        json["numOutputs"].as_number<int32_t>(&draft.numOutput);

        if (draft.numOutput < 0)
        {
            draft.name = "";
            std::cout << "Number of outputs cannot be lesser than 0" << std::endl;
            return draft;
        }

        draft.output = new slot[draft.numOutput];
    }

    if (json.contains("inputTypes"))
    {
        parseArray(draft.input, draft.numInput, json["inputTypes"]);
    }

    if (json.contains("outputTypes"))
    {

        parseArray(draft.output, draft.numOutput, json["outputTypes"]);
    }

    return draft;
}

std::vector<node_draft> NodeDraftParser::parseDirectory(const std::string &path) const
{
    std::vector<node_draft> drafts;

    if (std::filesystem::exists(path) == false)
    {
        std::cerr << "Directory: " + path + " does not exist or cannot be opened" << std::endl;
        return drafts;
    }

    std::filesystem::directory_iterator iterator(path);

    for (const auto &file : iterator)
    {
        std::string filepath = file.path().string();
        node_draft draft = parseFile(filepath);

        if (draft.name.empty() == true)
        {
            continue;
        }

        drafts.push_back(draft);
    }

    return drafts;
}

node_draft NodeDraftParser::parseFile(const std::string &filepath) const
{
    node_draft draft;

    std::ifstream input(filepath, std::ios::in);

    if (input.is_open() == false)
    {
        std::cerr << "File: " + filepath + " does not exist or cannot be opened" << std::endl;
        return draft;
    }

    std::string content((std::istreambuf_iterator<char>(input)), std::istreambuf_iterator<char>());

    input.close();

    if (content.empty() == true)
    {
        std::cerr << "File: " + filepath + " is empty or corrupted" << std::endl;
        return draft;
    }

    tinyjson::element root;
    if (tinyjson::parse(content.c_str(), &root) == false)
    {
        std::cerr << "File: " + filepath + " contains corrupted JSON" << std::endl;
        return draft;
    }

    draft = parseDraft(root);

    return draft;
}
