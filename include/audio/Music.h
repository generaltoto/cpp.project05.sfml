# pragma once
#include <SFML/Audio.hpp>

class Music {
private:
	sf::Music music;

public:

	Music(std::string path);
	~Music();

	void play();

	void pause();

	void stop();

	void setVolume(float vol);

};

