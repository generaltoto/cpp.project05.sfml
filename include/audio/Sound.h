#pragma once
# include "include/Structures.h"
# include <map>
# include "SFML/Audio.hpp"

class Sound {
private:
	sf::Sound sound;
	std::map<SoundEffect, sf::SoundBuffer> soundList;

public:
	Sound ();

	/// Returns the list of all the sounds effects.
	std::map<SoundEffect, sf::SoundBuffer> getSoundList();

	/// Plays the sound based on the given key.
	void playASound(SoundEffect needed);

	/// Sets the given buffer to the sound.
	void setBuffer(sf::SoundBuffer buff);

	/// Plays the sound.
	void play();

	/// Returns the current volume of the sounds.
	float getVolume();

	/// Sets the volume of the music.
	void setVolume(float vol);

};