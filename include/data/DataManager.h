#pragma once
#include "json.hpp"

class DataManager
{
public:
	/// Returns all the json information from a given file
	nlohmann::json static getAll(std::string);
};

