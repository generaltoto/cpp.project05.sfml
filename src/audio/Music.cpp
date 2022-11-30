#include "include/audio/Music.h"

Music::Music(std::string path) {
	if (!this->music.openFromFile(path)) {
		throw("ERROR_LOAD_MUSIC");
	}
}

Music::~Music() { }

void Music::play() { this->music.play(); this->music.setLoop(true); }

void Music::pause() { this->music.pause(); }

void Music::stop() { this->music.stop(); }

void Music::setVolume(float vol) { this->music.setVolume(vol); }
