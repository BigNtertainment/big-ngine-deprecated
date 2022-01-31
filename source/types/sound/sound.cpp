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
 * Loads an MP3 file into memory.
 * @param path The path to the MP3 file.
 * @return A pointer to the Sound object.
 */
BigNgine::Sound* BigNgine::Sound::LoadMP3(const std::string& path) {
	Sound* result = new Sound();

	result->OpenMP3(path);

	return result;
}

/**
 * Loads a WAV file into memory.
 * @param path The path to the WAV file.
 * @return A pointer to the Sound object.
 */
BigNgine::Sound* BigNgine::Sound::LoadWav(const std::string& path) {
	Sound* result = new Sound();

	result->OpenWav(path);

	return result;
}

/**
 * Opens an MP3 file to play later.
 * @param path Path to the MP3 file.
 */
void BigNgine::Sound::OpenMP3(const std::string& path) {
	std::string mciString = "open \"" + path + "\" type mpegvideo alias " + std::to_string(id);

	MCIERROR error = mciSendString(mciString.c_str(), nullptr, 0, nullptr);

	if(error != 0)
		Logger::Error("Failed to open MP3 file: " + path + " Error code: " + std::to_string(error));

	SetVolume(volume);
}

/**
 * Opens an WAV file to play later.
 * @param path Path to the MP3 file.
 */
void BigNgine::Sound::OpenWav(const std::string& path) {
	std::string mciString = "open \"" + path + "\" type waveaudio alias " + std::to_string(id);

	MCIERROR error = mciSendString(mciString.c_str(), nullptr, 0, nullptr);

	if(error != 0)
		Logger::Error("Failed to open WAV file: " + path + " Error code: " + std::to_string(error));

	SetVolume(volume);
}

/**
 * Plays an audio file
 */
void BigNgine::Sound::Play() {
	std::string mciString = "play " + std::to_string(id);

	MCIERROR error = mciSendString(mciString.c_str(), nullptr, 0, nullptr);

	if(error != 0)
		Logger::Error("Failed to play sound with id: " + std::to_string(id) + ". Error code: " + std::to_string(error));
	else
		paused = false;
}

/**
 * Playes an audio file on loop
 */
void BigNgine::Sound::PlayOnLoop() {
	std::string mciString = "play " + std::to_string(id) + " repeat";

	MCIERROR error = mciSendString(mciString.c_str(), nullptr, 0, nullptr);

	if(error != 0)
		Logger::Error("Failed to play on loop sound with id: " + std::to_string(id) + ". Error code: " + std::to_string(error));
	else
		paused = false;
}

/**
 * Pauses the playback of an audio file
 */
void BigNgine::Sound::Pause() {
	std::string mciString = "pause " + std::to_string(id);

	MCIERROR error = mciSendString(mciString.c_str(), nullptr, 0, nullptr);

	if(error != 0)
		Logger::Error("Failed to pause sound with id: " + std::to_string(id) + ". Error code: " + std::to_string(error));
	else
		paused = true;
}

/**
 * Resume the playback of an audio file after pausing
 */
void BigNgine::Sound::Resume() {
	std::string mciString = "resume " + std::to_string(id);

	MCIERROR error = mciSendString(mciString.c_str(), nullptr, 0, nullptr);

	if(error != 0)
		Logger::Error("Failed to resume playing sound with id: " + std::to_string(id) + ". Error code: " + std::to_string(error));
	else
		paused = false;
}

/**
 * Stops the playback of an audio file
 */
void BigNgine::Sound::Stop() {
	std::string mciString = "stop " + std::to_string(id);

	MCIERROR error = mciSendString(mciString.c_str(), nullptr, 0, nullptr);

	if(error != 0)
		Logger::Error("Failed to stop playing sound with id: " + std::to_string(id) + ". Error code: " + std::to_string(error));
	else
		paused = true;
}

/**
 * Closes the audio file
 */
void BigNgine::Sound::Close() {
	std::string mciString = "close " + std::to_string(id);

	MCIERROR error = mciSendString(mciString.c_str(), nullptr, 0, nullptr);

	if(error != 0)
		Logger::Error("Failed to close audio file from sound with id: " + std::to_string(id) + ". Error code: " + std::to_string(error));
}

/**
 * Sets the playback volume
 */
void BigNgine::Sound::SetVolume(int _volume) {
	std::string mciString = "setaudio " + std::to_string(id) + " volume to " + std::to_string(volume);

	MCIERROR error = mciSendString(mciString.c_str(), nullptr, 0, nullptr);

	if(error != 0)
		Logger::Error("Failed to set volume for sound with id: " + std::to_string(id) + " to " + std::to_string(_volume) + ". Error code: " + std::to_string(error));
	else
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
bool BigNgine::Sound::IsPaused() const {
	return paused;
}

/**
 * Whether the sound is playing or paused
 * @return True if the sound is playing, false if the sound is paused
 */
bool BigNgine::Sound::IsPlaying() const {
	return !paused;
}

/**
 * Returns the volume of the playback
 */
int BigNgine::Sound::GetVolume() const {
	return volume;
}