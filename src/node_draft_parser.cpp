#include "core/node_draft_parser.hpp"

void NodeDraftParser::parseArray(std::vector<slot_type> &array, const tinyjson::element &json) const
{
    if (!json.is_array() || json.size() < 1)
    {
        std::cerr << "Warning: 'Types' array is empty or invalid." << std::endl;
        return;
    }

    for (size_t i = 0; i < json.size(); ++i)
    {
        std::string type;
        if (json[i].as_str(&type))
        {
            array.push_back(parseSlotType(type));
        }
        else
        {
            std::cerr << "Warning: Invalid type in 'Types' array at index " << i << "." << std::endl;
        }
    }
}

node_type NodeDraftParser::parseNodeType(const std::string &type) const
{
    node_type typeOfNode;

    const char *types[NUM_NODE_TYPES] = NODE_TYPE_STR;
    for (int32_t item = 0; item < NUM_NODE_TYPES; ++item)
    {
        if (type == types[item])
        {
            typeOfNode = static_cast<node_type>(item);
            break;
        }
    }
    return typeOfNode;
}

slot_type NodeDraftParser::parseSlotType(const std::string &type) const
{
    slot_type typeOfSlot;

    const char *types[NUM_SLOT_TYPES] = SLOT_TYPE_STR;
    for (int32_t item = 0; item < NUM_SLOT_TYPES; ++item)
    {
        if (type == types[item])
        {
            typeOfSlot = static_cast<slot_type>(item);
            break;
        }
    }
    return typeOfSlot;
}

node_draft NodeDraftParser::parseDraft(const tinyjson::element &json) const
{
    node_draft draft;

    if (!json.is_object())
    {
        std::cerr << "Error: Expected JSON object for draft." << std::endl;
        return draft;
    }

    if (json.contains("Label") && json["Label"].as_str(&draft.name) == false)
    {
        std::cerr << "Warning: 'Label' is missing or invalid in JSON." << std::endl;
    }

    if (json.contains("Type"))
    {
        std::string type;
        if (json["Type"].as_str(&type))
        {
            draft.type = parseNodeType(type);
        }
        else
        {
            std::cerr << "Warning: Invalid 'Type' field in JSON." << std::endl;
        }
    }

    if (json.contains("Inputs"))
    {
        json["Inputs"].as_number<int32_t>(&draft.numInput);
    }

    if (json.contains("Outputs"))
    {
        json["Outputs"].as_number<int32_t>(&draft.numOutput);
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
        std::cerr << "Error: Directory '" << path << "' does not exist or cannot be opened." << std::endl;
        return drafts;
    }

    for (const auto &entry : std::filesystem::directory_iterator(path))
    {
        if (entry.is_regular_file() == false)
        {
            continue;
        }

        const auto &filepath = entry.path().string();
        node_draft draft = parseFile(filepath);

        if (!draft.name.empty())
        {
            drafts.push_back(draft);
        }
        else
        {
            std::cerr << "Warning: Skipping invalid draft in file '" << filepath << "'." << std::endl;
        }
    }

    return drafts;
}

node_draft NodeDraftParser::parseFile(const std::string &filepath) const
{
    node_draft draft;

    std::ifstream input(filepath);
    if (input.is_open() == false)
    {
        std::cerr << "Error: Cannot open file '" << filepath << "'." << std::endl;
        return draft;
    }

    std::string content((std::istreambuf_iterator<char>(input)), std::istreambuf_iterator<char>());
    if (content.empty() == true)
    {
        std::cerr << "Error: File '" << filepath << "' is empty or corrupted." << std::endl;
        return draft;
    }

    tinyjson::element root;
    if (tinyjson::parse(content.c_str(), &root) == false)
    {
        std::cerr << "Error: File '" << filepath << "' contains corrupted JSON." << std::endl;
        return draft;
    }

    return parseDraft(root);
}
