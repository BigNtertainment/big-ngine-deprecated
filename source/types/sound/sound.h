#include <windows.h>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include "../../global/logger/logger.h"

#pragma comment(lib, "winmm.lib")
#pragma once

namespace BigNgine {
	class Sound {
	public:
		Sound();
		~Sound();

		static Sound* LoadMP3(const std::string& path);
		static Sound* LoadWav(const std::string& path);

		void OpenMP3(const std::string& path);
		void OpenWav(const std::string& path);
		void Play();
		void PlayOnLoop();
		void Pause();
		void Resume();
		void Stop();
		void Close();

		void SetVolume(int _volume);

		bool IsPaused() const;
		bool IsPlaying() const;
		int GetVolume() const;

		static std::vector<Sound*> GetSounds();
	private:
		uint32_t id;
		bool paused = true;
		int volume = 500;

		static std::vector<Sound*> sounds;
	};
}