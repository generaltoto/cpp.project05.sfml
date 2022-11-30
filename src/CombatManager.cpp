#include "include/CombatManager.h"

MainWindow* CombatManager::contextWindow = nullptr;
sf::Texture* CombatManager::bgText = nullptr;
sf::Sprite* CombatManager::bgSprite = nullptr;
Player* CombatManager::contextPlayer = nullptr;
std::vector<Pokemon> CombatManager::enemies = {};

void CombatManager::startCombat()
{
	bgText = new sf::Texture();
	bgSprite = new sf::Sprite();
	if (bgText->loadFromFile("assets/combat.png"))
		bgSprite->setTexture(*bgText);
	else throw("ERROR::LOADING_COMBAT_BACKGROUND");
}

void CombatManager::runCombat(std::vector<Pokemon> &enemies)
{
	startCombat();
}

void CombatManager::drawCombat()
{
	contextWindow->getWindow()->draw(*bgSprite);
}

void CombatManager::endCombat()
{
}
