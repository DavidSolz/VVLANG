#include "core/node_draft_parser.hpp"

void NodeDraftParser::parseArray(std::vector<slot_type> &array, const tinyjson::element &json) const
{
    if (json.is_array() == false or json.size() < 1)
    {
        std::cerr << "Warning: Types array size is empty" << std::endl;
        return;
    }

    std::string type;
    for (int32_t i = 0; i < json.size(); i++)
    {
        json[i].as_str(&type);
        array.push_back(parseSlotType(type));
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

    if (json.contains("Label"))
    {
        json["Label"].as_str(&draft.name);
    }

    if (json.contains("Type"))
    {
        std::string type;
        json["Type"].as_str(&type);
        draft.type = parseNodeType(type);
    }

    if (json.contains("Inputs"))
    {
        json["Inputs"].as_number<int32_t>(&draft.numInput);

        if (draft.numInput < 0)
        {
            draft.name = "";
            std::cout << "Number of inputs cannot be lesser than 0" << std::endl;
            return draft;
        }

        draft.input.resize(draft.numInput);
    }

    if (json.contains("Outputs"))
    {
        json["Outputs"].as_number<int32_t>(&draft.numOutput);

        if (draft.numOutput < 0)
        {
            draft.name = "";
            std::cout << "Number of outputs cannot be lesser than 0" << std::endl;
            return draft;
        }

        draft.output.resize(draft.numOutput);
    }

    if (json.contains("Types"))
    {
        parseArray(draft.possibleTypes, json["Types"]);
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
