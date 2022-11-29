#include "include/data/DataManager.h"

nlohmann::json DataManager::getAll(std::string path)
{
	std::ifstream file(path);
	return nlohmann::json::parse(file);
}