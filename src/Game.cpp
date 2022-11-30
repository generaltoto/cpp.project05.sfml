#include "include/Game.h"

MainWindow* Game::mainWindow = nullptr;
Pokemon Game::pokemons[809] = {};
Capacity Game::capacities[619] = {};

void Game::createPokemons(
	int index, int x, int y, std::string name, std::string path, std::vector<std::string> types,
	std::string caption, int level, std::vector<int> stats
)
{
	Game::pokemons[index] = { x, y, name, path, types, caption, level, stats };
}

void Game::createCapacity(int index, std::string name, int damage, std::string attackType, std::string type, int accuracy, int pp)
{
	Game::capacities[index] = { name, damage, attackType, type, accuracy, pp, pp };
}

void Game::startGame() {
	sf::Font* font = new sf::Font();
	mainWindow = new MainWindow(*font);
	int pokemonIndex = 0;
	int capacityIndex = 0;

	for (auto& pokemons : DataManager::getAll("include/data/pokedex.json"))
	{
		auto t = pokemons["type"];
		std::vector<std::string> types;

		if (t.size() < 2) types = { t[0] };
		else types = { t[0], t[1] };
		types.resize(t.size());

		Game::createPokemons(
			pokemonIndex,
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
		++pokemonIndex;
	}

	for (auto& moves : DataManager::getAll("include/data/moves.json"))
	{
		Game::createCapacity(
			capacityIndex,
			moves["ename"],
			moves["power"],
			moves["category"],
			moves["type"],
			moves["accuracy"],
			moves["pp"]
		);
		++capacityIndex;
	}

	std::cout << "LOADED::POKEMON_AND_MOVES" << std::endl;
}

void Game::runGame() {
	Player player = Player(0, 0, "Sacha", "assets/sacha.png");

	srand(time(NULL));
	player.addPokemon(Game::pokemons[rand() % 808]);
	player.addPokemon(Game::pokemons[rand() % 808]);
	player.addPokemon(Game::pokemons[rand() % 808]);
	player.addPokemon(Game::pokemons[rand() % 808]);
	player.addPokemon(Game::pokemons[rand() % 808]);
	player.addPokemon(Game::pokemons[rand() % 808]);

	player.addItems(0, 10);
	player.addItems(1, 69);
	player.addItems(2, 15);

	Music music = { "assets/audio/main_music.ogg" };
	music.setVolume(50);
	music.play();
	Sound soundEffect;
	soundEffect.setVolume(50);

	MainWindow::Menu gameMenu(mainWindow);
	MainWindow::InventoryMenu invMenu(mainWindow, &player);
	MainWindow::SettingsMenu settMenu(mainWindow, &soundEffect, &music);
	mainWindow->setMenu(&gameMenu, &invMenu);

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
					gameMenu.navigateMenu(&currentView, &soundEffect);
					break;
				case PLAY:
					if (e.key.code == sf::Keyboard::Escape)
					{
						mainWindow->getWindow()->setView(
							mainWindow->getWindow()->getDefaultView()
						);
						currentView = MENU;
					}
					break;
				case COMBAT:
					break;
				case INVENTORY:
					invMenu.navigate(&soundEffect, &player, &currentView);
					break;
				case SETTINGS:
					settMenu.navigateSettings(&currentView, &soundEffect, &music);
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
		case SETTINGS:
			settMenu.draw();
			break;
		default:
			break;
		}

		mainWindow->getWindow()->display(); // indicates that the mainWindow is done rendering
	}
}
