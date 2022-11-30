#include "include/audio/Sound.h"

Sound::Sound() {
	sf::SoundBuffer buff;
	if (!buff.loadFromFile("assets/audio/menu_sound_effect.wav")) {
		throw("ERROR_LOAD_SOUND");
	}
	this->soundList.insert({ MENUEFFECT, buff });

	if (!buff.loadFromFile("assets/audio/atk_effect.wav")) {
		throw("ERROR_LOAD_SOUND");
	}
	this->soundList.insert({ ATKEFFECT, buff });

	if (!buff.loadFromFile("assets/audio/heal_effect.wav")) {
		throw("ERROR_LOAD_SOUND");
	}
	this->soundList.insert({ HEALEFFECT, buff });

	if (!buff.loadFromFile("assets/audio/start_battle.wav")) {
		throw("ERROR_LOAD_SOUND");
	}
	this->soundList.insert({ STARTBATTLE, buff });

	if (!buff.loadFromFile("assets/audio/win_battle.wav")) {
		throw("ERROR_LOAD_SOUND");
	}
	this->soundList.insert({ WINCOMBAT, buff });
}

Sound::~Sound() {
}

std::map<SoundEffect, sf::SoundBuffer> Sound::getSoundList() {
	return this->soundList;
}

void Sound::playASound(SoundEffect needed) {
	switch (needed)
	{
	case MENUEFFECT:
		this->sound.setBuffer(this->soundList[needed]);
		play();
		break;
	case ATKEFFECT:
		this->sound.setBuffer(this->soundList[needed]);
		play();
		break;
	case HEALEFFECT:
		this->sound.setBuffer(this->soundList[needed]);
		play();
		break;
	case STARTBATTLE:
		this->sound.setBuffer(this->soundList[needed]);
		play();;
		break;
	case WINCOMBAT:
		this->sound.setBuffer(this->soundList[needed]);
		play();
		break;
	default:
		break;
	}
}

void Sound::setBuffer(sf::SoundBuffer buff) { this->sound.setBuffer(buff);  }

void Sound::play() { this->sound.play(); }

float Sound::getVolume() { return this->sound.getVolume(); }

void Sound::setVolume(float vol) { if(vol >= 0 && vol <= 100) this->sound.setVolume(vol); }