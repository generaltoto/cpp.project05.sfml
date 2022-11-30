# pragma once
# include <SFML/Audio.hpp>

class Music {
private:
	sf::Music music;

public:

	Music(std::string path);
	~Music();

	/// Plays the music set.
	void play();

	/// Pauses the current played music.
	void pause();

	/// Stops the current played music.
	void stop();

	/// Returns the current volume of the music.
	float getVolume();

	/// Sets the volume of the music.
	void setVolume(float vol);
};

