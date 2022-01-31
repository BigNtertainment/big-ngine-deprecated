#include <windows.h>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

#pragma comment(lib, "winmm.lib")
#pragma once

namespace BigNgine {
	class Sound {
	public:
		Sound();
		~Sound();

		static Sound* LoadMP3(std::string path);
		static Sound* LoadWav(std::string path);

		void OpenMP3(std::string path);
		void OpenWav(std::string path);
		void Play();
		void PlayOnLoop();
		void Pause();
		void Resume();
		void Stop();
		void Close();

		void SetVolume(int _volume);

		bool IsPaused();
		bool IsPlaying();
		int GetVolume();

		static std::vector<Sound*> GetSounds();
	private:
		int id;
		bool paused = true;
		int volume = 500;

		static std::vector<Sound*> sounds;
	};
}