#include "include/audio/Sound.h"

Sound::Sound() {
}

Sound::~Sound() {
}

std::map<SoundEffect, sf::SoundBuffer> Sound::getSoundList() {
	return this->soundList;
}

sf::SoundBuffer Sound::getSound(SoundEffect needed) {
	sf::SoundBuffer buff;

	for (auto it = this->soundList.begin(); it != this->soundList.end(); it++){
		if (needed == it->first) {
			return this->soundList[needed];
		}
	}

	switch (needed)
	{
	case MENUEFFECT:
		if (!buff.loadFromFile("assets/audio/menu_sound_effect.ogg")) {
			throw("ERROR_LOAD_SOUND");
		}
		this->soundList.insert({ MENUEFFECT, buff });
		return this->soundList[needed];
		break;
	case ATKEFFECT:
		if (!buff.loadFromFile("assets/audio/atk_effect.ogg")) {
			throw("ERROR_LOAD_SOUND");
		}
		this->soundList.insert({ ATKEFFECT, buff });
		return this->soundList[needed];
		break;
	case HEALEFFECT:
		if (!buff.loadFromFile("assets/audio/heal_effect.ogg")) {
			throw("ERROR_LOAD_SOUND");
		}
		this->soundList.insert({ HEALEFFECT, buff });
		return this->soundList[needed];
		break;
	case STARTBATTLE:
		if (!buff.loadFromFile("assets/audio/start_battle.ogg")) {
			throw("ERROR_LOAD_SOUND");
		}
		this->soundList.insert({ STARTBATTLE, buff });
		return this->soundList[needed];
		break;
	case WINCOMBAT:
		if (!buff.loadFromFile("assets/audio/win_battle.ogg")) {
			throw("ERROR_LOAD_SOUND");
		}
		this->soundList.insert({ WINCOMBAT, buff });
		return this->soundList[needed];
		break;
	case LOSTCOMBAT:
		if (!buff.loadFromFile("assets/audio/lost_effect.ogg")) {
			throw("ERROR_LOAD_SOUND");
		}
		this->soundList.insert({ LOSTCOMBAT, buff });
		return this->soundList[needed];
		break;
	default:
		break;
	}
}

void Sound::play() { this->sound.play(); }

void Sound::setVolume(float vol) { this->sound.setVolume(vol); }