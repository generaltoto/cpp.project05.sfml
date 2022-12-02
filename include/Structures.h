# pragma once
# include <string>

// Assets paths
const std::string COMBAT_ASSET_PATH = "assets/combat.png";
const std::string INVENTORY_BG_ASSET_PATH = "assets/inventoryBackground.png";
const std::string ITEMS_ASSET_PATH = "assets/items.png";
const std::string MENU_BG_ASSET_PATH = "assets/menuBackground.jpg";
const std::string TILES_ASSET_PATH = "assets/tiles.png";
const std::string PLAYER_ASSET_PATH = "assets/sacha.png";
const std::string FONT_ASSET_PATH = "assets/pixelFont.ttf";

// Sounds - Musics paths
const std::string ATTACK_SOUND_PATH = "assets/audio/atk_effect.wav";
const std::string HEAL_SOUND_PATH = "assets/audio/heal_effect.wav";
const std::string MENU_SOUND_PATH = "assets/audio/menu_sound_effect.wav";
const std::string BATTLE_START_SOUND_PATH = "assets/audio/start_battle.wav";
const std::string BATTLE_WIN_SOUND_PATH = "assets/audio/win_battle.wav";
const std::string BATTLE_MUSIC_PATH = "assets/audio/music_battle.ogg";
const std::string MAIN_MUSIC_PATH = "assets/audio/main_music.ogg";

// Json paths
const std::string POKEMON_JSON_PATH = "include/data/pokedex.json";
const std::string MOVES_JSON_PATH = "include/data/moves.json";

enum Stat { HP, ATK, ATKSPE, DEF, DEFSPE, VIT };

enum ViewTypes { MENU, PLAY, COMBAT, INVENTORY, SETTINGS };

enum SprayType { HEAL, RESET };

enum SoundEffect { MENUEFFECT, ATKEFFECT, HEALEFFECT, STARTBATTLE, WINCOMBAT };

struct Capacity {
	std::string name;
	int damage;
	std::string attackType;
	std::string type;
	int accuracy;
	int pp;
	int current;
};

struct Level {
	int level, currentExp, ExpToNext, evolveLvl; //ExpToNext = level^3
};

#define ANIME_SACHA_RECT {\
	{	sf::IntRect(0, 0, 110, 140),sf::IntRect(160, 0, 110, 140),sf::IntRect(330, 0, 110, 140), sf::IntRect(490, 0, 110, 140) },\
	{	sf::IntRect(0, 160, 110, 140), sf::IntRect(160, 160, 110, 140), sf::IntRect(330, 160, 110, 140), sf::IntRect(490, 160, 110, 140) },\
	{	sf::IntRect(0, 330, 110, 140), sf::IntRect(160, 330, 110, 140), sf::IntRect(330, 330, 110, 140), sf::IntRect(490, 330, 110, 140) },\
	{ sf::IntRect(0, 490, 110, 140), sf::IntRect(160, 490, 110, 140), sf::IntRect(330, 490, 110, 140), sf::IntRect(490, 490, 110, 140) },\
}