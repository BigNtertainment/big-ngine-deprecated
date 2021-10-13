#include "game.h"

#define FPS 60


bool Game::running = true;
int Game::width = 640;
int Game::height = 480;

BigNgine::Scene* ActiveScene = nullptr;
GLFWwindow* Game::window = nullptr;
const char *Game::name = "BigNgine";
const char *Game::icon = "";

// window resizing
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
	Game::width = width;
	Game::height = height;
}

void Game::Stop() {
	Game::running = false;
}

void Game::Start(void(*Start)(), void(*Update)(int)) {
	// initialization of SDL libraries

	// if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
	// 	Logger::Error(SDL_GetError());
	// 	return;
	// }
	// Mix_Init(MIX_INIT_MP3);

//	OpenGL initialization
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

//	creating window
	Game::window = glfwCreateWindow(Game::width, Game::height, Game::name, nullptr, nullptr);
	if (Game::window == nullptr)
	{
		glfwTerminate();
		Logger::Error("Failed to create GLFW window");
	}

	//	making context for opengl
	glfwMakeContextCurrent(Game::window);
	//	window resize stuff
	glfwSetFramebufferSizeCallback(Game::window, framebuffer_size_callback);

//	Initialization of GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		Logger::Error("GLAD NOT INITIALIZED");
	}
	
	/* tell GL to only draw onto a pixel if the shape is closer to the viewer
	than anything already drawn at that pixel */
	glEnable(GL_DEPTH_TEST); /* enable depth-testing */

	
	//	so we can use alpha values in fragment shaders
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);
	

	/* with LESS depth-testing interprets a smaller depth value as meaning "closer" */
//	TODO(imustend): make it GL_GREATER
//	 and write disclaimer
	glDepthFunc(GL_LESS);

	glViewport(0, 0, Game::width, Game::height);

	// For calculating deltaTime
	clock_t lastTime = 0, currentTime;

	// Icon
	GLFWimage images[1];
	images[0].pixels = stbi_load(Game::icon, &images[0].width, &images[0].height, nullptr, 4);
	glfwSetWindowIcon(window, 1, images);
	stbi_image_free(images[0].pixels);

	// Activate callbacks on key events
	glfwSetKeyCallback(Game::window, Input::Callback::ExecuteCallbacks);

//	TODO(pietrek14): sort entities array before activating them,
//		from biggest depth to smallest
//	FIXME: if you add entity while game loop is running start functions wont execute!!!
//		or you change scene more then once or something it doesnt work
//		THE GAME CRASHES


//	starting every entity
	// Call the user-given start function
	Start();
	// Start the active scene
	ActiveScene->Start();
	
	// Main game loop
	while(Game::running && !glfwWindowShouldClose(window)) {
		// Background color
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Calculate delta time
		currentTime = clock();

		int deltaTime = currentTime - lastTime;

		// Call the user-given update function
		Update(deltaTime);

		// Update the active scene
		ActiveScene->Update(deltaTime);

		// Update the frame
		glfwSwapBuffers(Game::window);

		// Poll the events so the game doesn't crash
		glfwPollEvents();

		// For calculating deltaTime
		lastTime = clock();

		// Calculate the delay necessery to keep the constant frame rate
		if (floor(16.666f - deltaTime) > 0)
		{
			std::chrono::milliseconds timespan((int)(16.666f - deltaTime));
			std::this_thread::sleep_for(std::chrono::milliseconds(timespan));
		}

		// Update the window size
		glfwSetWindowSize(window, Game::width, Game::height);
	}

	// TODO: Make actual garbage collection (delete all scenes here)
	delete ActiveScene;

	// Finish off GLFW
	Game::window = nullptr;
	glfwTerminate();
}

//TODO: Make it into one function somehow

void Game::SetActiveScene(BigNgine::Scene* scene) {
	ActiveScene = scene;
}

void Game::ChangeActiveScene(BigNgine::Scene* scene) {
	ActiveScene->Destroy();

	ActiveScene = scene;

	ActiveScene->Start();
}