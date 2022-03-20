#pragma once

#include "../input/input.h"
#include "../logger/logger.h"
#include "../../types/entity/entity.h"
#include "../../types/scene/scene.h"
#include "../../types/sound/sound.h"
#include "glad.h"
#include "GLFW/glfw3.h"
#include "stb_image.h"
#include <chrono>
#include <thread>
#include <string>
#include <ctime>


typedef std::function<void()> game_startfunc;
typedef std::function<void(int)> game_updatefunc;

namespace BigNgine {
	class Scene;

	/// A singleton that holds all the game's general data
	class Game
	{
		Game();
		~Game();
	
		static Game* instance;

		bool running = false;
		BigNgine::Scene* activeScene = nullptr;
		GLFWwindow* window = nullptr;
		const char *name = "BigNgine",
					*icon = "assets/icon/icon.png";
		uint32_t width, height;
	public:
		Game(const Game&) = delete;

		static inline Game* GetInstance() {
			return instance;
		}
		
		///	Function that starts the game, should be called once at the start your program.
		///	@param firstScene The first scene
		///	@param Start Function that is called once.
		/// @param Update Function that is called every frame.
		void Start(BigNgine::Scene* firstScene, game_startfunc Start, game_updatefunc Update);

		///	Stops game
		void Stop();
		
		///	Sets active scene.
		///	@param scene BigNgine::Scene* scene
		void SetActiveScene(BigNgine::Scene* scene);

		/// Resizes the game window
		/// @param width The new width of the window
		/// @param height The new height of the window
		void ResizeWindow(uint32_t width, uint32_t height);

		/// Sets the game name
		/// @param name The new name of the game
		void SetName(const char* name);
		
		/// Sets the game icon
		/// @param icon The new icon of the game
		void SetIcon(const char* icon);

		/// Returns the width of the game window
		/// @return uint32_t The width of the game window
		uint32_t GetWindowWidth() const;
		/// Returns the height of the game window
		/// @return uint32_t The height of the game window
		uint32_t GetWindowHeight() const;
		/// Returns the scene that's currently active
		/// @return BigNgine::Scene* The active scene
		BigNgine::Scene* GetActiveScene() const;

		/// Returns the GLFW window
		/// @return GLFWwindow* The GLFW window
		GLFWwindow* GetWindow() const;
	private:
		/// Checks conditions and executes callbacks of input events. Called every frame.
		/// @param window GLFWwindow* window
		/// @param key int key
		/// @param scancode int scancode
		/// @param action int action
		/// @param mods int mods
		static void ExecuteCallbacks(GLFWwindow* window, int key, int scancode, int action, int mods);
	};
}
