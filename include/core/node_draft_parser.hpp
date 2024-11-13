#ifndef NODE_DRAFT_PARSER_HPP
#define NODE_DRAFT_PARSER_HPP

#include <vector>
#include <fstream>
#include <string>
#include <filesystem>
#include <tinyjson.hpp>
#include <iostream>

#include "node_draft.hpp"

class NodeDraftParser
{
private:

    void parseArray(slot * array, const size_t & size, const tinyjson::element& json) const;

    node_type parseNodeType(const std::string & type) const;

    slot_type parseSlotType(const std::string & type) const;

    node_draft parseDraft(const tinyjson::element& json) const;

public:

    std::vector<node_draft> parseDirectory(const std::string & path) const;

    node_draft parseFile(const std::string & filepath) const;
};

#endif
