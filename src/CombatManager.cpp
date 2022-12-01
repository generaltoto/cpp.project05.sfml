#include "include/CombatManager.h"

MainWindow* CombatManager::contextWindow = nullptr;
sf::Texture* CombatManager::bgText = nullptr;
sf::Sprite* CombatManager::bgSprite = nullptr;
Player* CombatManager::contextPlayer = nullptr;
bool CombatManager::activeCombat = false;
std::vector<Pokemon> CombatManager::enemies = {};

void CombatManager::initCombatContexts(MainWindow* mainWindow)
{
	CombatManager::contextWindow = mainWindow;

	CombatManager::bgText = new sf::Texture();
	CombatManager::bgSprite = new sf::Sprite();
	if (CombatManager::bgText->loadFromFile("assets/combat.png"))
	{
		CombatManager::bgSprite->setTexture(*CombatManager::bgText);
	}
	else throw("ERROR::LOADING_COMBAT_BACKGROUND");
}

void CombatManager::initCombatEnemies(std::vector<Pokemon> e, bool* loaded)
{
	enemies = e;
	*loaded = true;
}

bool CombatManager::runCombat()
{
	activeCombat = true;
	endCombat();
	return false;
}

void CombatManager::updateCombat()
{
	contextWindow->getWindow()->draw(*bgSprite);
	for (auto& it : enemies)
	{
		// drawing enemy pokemon and stats 
		if (it.currentHealth <= 0) continue;
		else
		{
			//const variables
			const int assetSize = 40;
			const float scaleInGame = 5.75f;
			const float scaleStat = 3.5f;

			// pokemon in combat
			it.getSprite().setScale(scaleInGame, scaleInGame);
			it.getSprite().setPosition(1240, 330);
			contextWindow->getWindow()->draw(it.getSprite());

			//creating stats zone
			sf::Vector2f statsPos = { 0,150 };
			sf::Vector2f statsSize = { 670, 170 };

			sf::RectangleShape s;
			s.setPosition(statsPos);
			s.setSize(statsSize);
			s.setFillColor({ 245,245,245,245 });
			contextWindow->getWindow()->draw(s);

			it.getSprite().setScale(scaleStat, scaleStat);
			it.getSprite().setPosition(
				statsPos.x + statsSize.x * 0.025,
				statsPos.y + statsSize.y * 0.05
			);
			contextWindow->getWindow()->draw(it.getSprite());

			sf::Text txt;
			txt.setFont(contextWindow->getFont());

			// drawing pokemon name 
			txt.setString(it.getName());
			txt.setCharacterSize(30);
			txt.setOutlineColor(sf::Color::Black);
			txt.setOutlineThickness(5);
			txt.setPosition(
				it.getSprite().getPosition().x + assetSize + 100,
				it.getSprite().getPosition().y + 20
			);
			contextWindow->getWindow()->draw(txt);

			txt.setOutlineThickness(0);
			txt.setCharacterSize(20);
			txt.setColor(sf::Color::Black);

			//drawing pokemon level
			txt.setString("Level :    " + std::to_string(it.getLevel().level));
			txt.setPosition(
				it.getSprite().getPosition().x + assetSize + 100,
				it.getSprite().getPosition().y + 90
			);
			contextWindow->getWindow()->draw(txt);

			//drawing pokemon hp
			txt.setString("HP :    " +
				std::to_string(it.getHealthAndMax()[0]) +
				"  /  " +
				std::to_string(it.getHealthAndMax()[1])
			);
			txt.setPosition(
				it.getSprite().getPosition().x + assetSize + 300,
				it.getSprite().getPosition().y + 90
			);
			contextWindow->getWindow()->draw(txt);

			break;
		}
	}
	// drawing team menu
	CombatMenu menu = CombatMenu(contextWindow, contextPlayer);

	menu.drawMenu();
}

void CombatManager::endCombat()
{
}
