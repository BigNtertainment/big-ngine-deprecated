#include "audio.h"

void Audio::Play(std::string path) {
	std::string mciString = "open \"" + path + "\" type mpegvideo alias mp3";

	mciSendString(mciString.c_str(), NULL, 0, NULL);

	mciSendString("play mp3", NULL, 0, NULL);
}