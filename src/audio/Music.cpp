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

float Music::getVolume() { return music.getVolume(); }

void Music::setVolume(float vol) { 
	if (vol >= 0 && vol <= 100) {
		this->music.setVolume(vol);
		return;
	}
	if (vol <= 0) {
		this->music.setVolume(0);
		return;
	}	
	if (vol >= 100) {
		this->music.setVolume(100);
		return;
	}
}