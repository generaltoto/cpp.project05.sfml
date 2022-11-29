#include "include/Game.h"

MainWindow* Game::mainWindow = nullptr;
std::vector<Pokemon> Game::pokemons = {};
std::vector<Capacity> Game::capacities = {};

void Game::createPokemons(
	int x, int y, std::string name, std::string path, std::vector<std::string> types,
	std::string caption, int level, std::vector<int> stats
)
{
	Pokemon p = Pokemon(
		x, y, name, path, types, caption, level, stats
	);
	Game::pokemons.push_back(p);
}

void Game::createCapacity(std::string name, int damage, std::string attackType, std::string type, int accuracy)
{
	Capacity c = { name, damage, attackType, type, accuracy };
	Game::capacities.push_back(c);
}

void Game::startGame() {
	mainWindow = new MainWindow();

	for (auto& pokemons : DataManager::getAll("include/data/pokedex.json"))
	{
		std::vector<std::string> types;
		if (sizeof(pokemons["type"][1] <= 0))
			types = { pokemons["type"][0] };
		else 
			types = { pokemons["type"][0], pokemons["type"][1] };

		Game::createPokemons(
			0, 0,
			pokemons["name"]["english"],
			pokemons["image"]["sprite"],
			types,
			pokemons["description"],
			1,
			{
				pokemons["base"]["HP"],
				pokemons["base"]["Attack"],
				pokemons["base"]["Defense"],
				pokemons["base"]["Sp. Attack"],
				pokemons["base"]["Sp. Defense"],
				pokemons["base"]["Speed"]
			}
		);
	}

	for (auto& moves : DataManager::getAll("include/data/moves.json"))
	{
		Game::createCapacity(
			moves["ename"],
			moves["power"],
			moves["category"],
			moves["type"],
			moves["accuracy"]
		);
	}

	std::cout << "LOADED::POKEMON_AND_MOVES" << std::endl;
}

void Game::runGame() {
	Player player;

	Capacity c0 = { "Charge", 40, "physical", "NORMAL", 100 };
	Capacity c1 = { "Cru-Ailes", 60, "physical", "FLY", 100 };
	Capacity c2 = { "Picpic", 35, "physical", "FLY", 100 };
	Capacity c3 = { "Tornade", 60, "physical", "FLY", 100 };

	Capacity cap[4] = { c0, c1, c2, c3 };
	std::vector<std::string> ty = { "PLANT", "FLY" };
	Pokemon pokemon(
		0, 0, "bulbizarre", "assets/pokemon.png", ty, "aaaaa", 1, {45,49,49,65,65,45}
	);
	for (int i = 0; i < 6; i++) { player.addPokemon(&pokemon); }


	player.addItems(0, 10);
	player.addItems(1, 69);
	player.addItems(2, 15);

	MainWindow::Menu gameMenu(mainWindow);
	mainWindow->setMenu(&gameMenu);

	MainWindow::InventoryMenu invMenu(mainWindow, &player);

	TileMap map;
	MapGenerator mapGen(
		mainWindow->getVideoMode()->width, mainWindow->getVideoMode()->height
	);

	ViewTypes currentView = MENU;

	sf::View camera;
	camera.setCenter(sf::Vector2f((32 * mapGen.GetEntry()) / 0.6f, 32 * (MAPHEIGHT - 1) / 0.6f));
	camera.setSize(sf::Vector2f(mainWindow->getVideoMode()->width / 2, mainWindow->getVideoMode()->height / 2));

	player.SetMapPosition(mapGen.GetEntry(), MAPHEIGHT - 1);

	//2.9 pour 64 * 64   11.6 pour 256 * 256
	if (!map.load("assets/pixil-frame-0.png", sf::Vector2u(32, 32), mapGen.GetLevel2(), MAPWIDTH, MAPHEIGHT, 0.6))
		throw("ERROR::MAP_LOADING");

	int frameCount = 0;
	sf::Event e{};

	while (mainWindow->getWindow()->isOpen())
	{
		mainWindow->getWindow()->clear(sf::Color(255, 127, 127, 255)); // clear old frame

		while (mainWindow->getWindow()->pollEvent(e))
		{
			switch (e.type) {
			case sf::Event::Closed:
				mainWindow->getWindow()->close();
				break;
			case sf::Event::KeyPressed:
				switch (currentView)
				{
				case MENU:
					gameMenu.navigateMenu(&currentView);
					break;
				case PLAY:
					if (e.key.code == sf::Keyboard::Escape)
					{
						mainWindow->getWindow()->setView(
							mainWindow->getWindow()->getDefaultView()
						);
						currentView = MENU;
					}
					std::cout << "here" << std::endl;
					break;
				case COMBAT:
					break;
				case INVENTORY:
					if (e.key.code == sf::Keyboard::Escape) currentView = MENU;
					invMenu.navigate();
					break;
				default:
					break;
				}
				break;
			default:
				break;
			}
		}
		frameCount++;
		switch (currentView)
		{
		case MENU:
			gameMenu.draw();
			break;
		case PLAY:
			player.updatePlayer(&frameCount, &camera, mapGen.GetLevel2());
			mainWindow->getWindow()->setView(camera);
			mainWindow->getWindow()->draw(map);
			player.setPos(camera.getCenter().x - 4, camera.getCenter().y - 33);
			player.displayEntity(mainWindow->getWindow());
		case COMBAT:
			break;
		case INVENTORY:
			invMenu.draw();
			break;
		default:
			break;
		}

		mainWindow->getWindow()->display(); // indicates that the mainWindow is done rendering
	}
}
