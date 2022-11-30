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

	void playASound(SoundEffect needed);

	void setBuffer(sf::SoundBuffer buff);

	void play();

	float getVolume();

	void setVolume(float vol);

};