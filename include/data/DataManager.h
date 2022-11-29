#pragma once
#include "json.hpp"

class DataManager
{
public:
	/// Returns all the json informations from a given file
	nlohmann::json static getAll(std::string);
};

