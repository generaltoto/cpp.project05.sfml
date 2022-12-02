# pragma once
# include <SFML/Audio.hpp>

class Music {
private:
	sf::Music music;
	bool isPlayed;

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

	/// Returns if the music is played or not.
	bool getIsPlayed();

	/// Sets if the music is on pause or not.
	void setIsPlayed(bool played);

	/// Sets the volume of the music.
	void setVolume(float vol);
};

