#pragma once
# include "include/Structures.h"

class Sound {
private:
	sf::Sound sound;
	std::map<SoundEffect, sf::SoundBuffer> soundList;

public:
	Sound ();
	~Sound ();

	std::map<SoundEffect, sf::SoundBuffer> getSoundList();

	sf::SoundBuffer getSound(SoundEffect needed);

	void play();

	void setVolume(float vol);
};