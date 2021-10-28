#include "sound.h"

// IT ONLY WORKS FOR WINDOWS :(

std::vector<BigNgine::Sound*> BigNgine::Sound::sounds;

uint32_t AutoIncrement = 0;

BigNgine::Sound::Sound() {
	id = AutoIncrement;
	AutoIncrement++;

	sounds.push_back(this);
}

BigNgine::Sound::~Sound() {
	Sound::sounds.erase(std::remove(Sound::sounds.begin(), Sound::sounds.end(), this), Sound::sounds.end());
}

/**
 * Opens an MP3 file to play later.
 * @param path Path to the MP3 file.
 */
void BigNgine::Sound::OpenMP3(std::string path) {
	std::string mciString = "open \"" + path + "\" type mpegvideo alias " + std::to_string(id);

	mciSendString(mciString.c_str(), NULL, 0, NULL);

	SetVolume(volume);
}

/**
 * Opens an WAV file to play later.
 * @param path Path to the MP3 file.
 */
void BigNgine::Sound::OpenWav(std::string path) {
	std::string mciString = "open \"" + path + "\" type waveaudio alias " + std::to_string(id);

	mciSendString(mciString.c_str(), NULL, 0, NULL);

	SetVolume(volume);
}

/**
 * Playes an audio file
 */
void BigNgine::Sound::Play() {
	std::string mciString = "play " + std::to_string(id);

	mciSendString(mciString.c_str(), NULL, 0, NULL);

	paused = false;
}

/**
 * Pauses the playback of an audio file
 */
void BigNgine::Sound::Pause() {
	std::string mciString = "pause " + std::to_string(id);

	mciSendString(mciString.c_str(), NULL, 0, NULL);

	paused = true;
}

/**
 * Resume the playback of an audio file after pausing
 */
void BigNgine::Sound::Resume() {
	std::string mciString = "resume " + std::to_string(id);

	mciSendString(mciString.c_str(), NULL, 0, NULL);

	paused = false;
}

/**
 * Stops the playback of an audio file
 */
void BigNgine::Sound::Stop() {
	std::string mciString = "stop " + std::to_string(id);

	mciSendString(mciString.c_str(), NULL, 0, NULL);

	paused = true;
}

/**
 * Closes the audio file
 */
void BigNgine::Sound::Close() {
	std::string mciString = "close " + std::to_string(id);

	mciSendString(mciString.c_str(), NULL, 0, NULL);
}

// TODO: Check if it works for .wav files cause it probably doesn't
/**
 * Sets the playback volume
 */
void BigNgine::Sound::SetVolume(int _volume) {
	std::string mciString = "setaudio " + std::to_string(id) + " volume to " + std::to_string(volume);

	mciSendString(mciString.c_str(), NULL, 0, NULL);

	volume = _volume;
}

/**
 * Returns all Sound instances
 */
std::vector<BigNgine::Sound*> BigNgine::Sound::GetSounds() {
	return BigNgine::Sound::sounds;
}

/**
 * Whether the sound is playing or paused
 * @return True if the sound is paused, false if the sound is playing
 */
bool BigNgine::Sound::IsPaused() {
	return paused;
}

/**
 * Whether the sound is playing or paused
 * @return True if the sound is playing, false if the sound is paused
 */
bool BigNgine::Sound::IsPlaying() {
	return !paused;
}

/**
 * Returns the volume of the playback
 */
int BigNgine::Sound::GetVolume() {
	return volume;
}