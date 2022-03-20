#include "game.h"

#define FPS 60

BigNgine::Game::Game() {}
BigNgine::Game::~Game() {}

BigNgine::Game* BigNgine::Game::instance = new BigNgine::Game();

// Window resizing callback
void FramebufferResizeCallback(GLFWwindow* window, int width, int height)
{
	BigNgine::Game::GetInstance()->ResizeWindow(width, height);
}

void BigNgine::Game::ExecuteCallbacks(GLFWwindow* window, int key, int scancode, int action, int mods) {
	for(Input::Callback* callback : BigNgine::Game::GetInstance()->activeScene->GetCallbacks()) {
		if(callback->active && callback->event == action)
			callback->Call(key, scancode, mods);
	}
}

void BigNgine::Game::Start(BigNgine::Scene* firstScene, game_startfunc Start, game_updatefunc Update) {
	//	OpenGL initialization
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

	// Creating window
	window = glfwCreateWindow(width, height, name, nullptr, nullptr);

	if (Game::window == nullptr)
	{
		glfwTerminate();
		Logger::Error("Failed to create GLFW window");
	}

	// Making context for OpenGL
	glfwMakeContextCurrent(window);

	// Window resize stuff
	glfwSetFramebufferSizeCallback(window, FramebufferResizeCallback);

	// Initialization of GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		Logger::Error("GLAD NOT INITIALIZED");
	}
	
	// Tell OpenGL to only draw onto a pixel if the shape is closer to the viewer than anything already drawn at that pixel
	glEnable(GL_DEPTH_TEST); /* enable depth-testing */
	
	// So we can use alpha values in fragment shaders
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);
	
	// with LESS depth-testing interprets a smaller depth value as meaning "closer"
//	TODO(imustend): make it GL_GREATER
//	 and write disclaimer
	glDepthFunc(GL_LESS);

	glViewport(0, 0, width, height);

	// Set the game icon
	GLFWimage images[1];
	images[0].pixels = stbi_load(icon, &images[0].width, &images[0].height, nullptr, 4);
	glfwSetWindowIcon(window, 1, images);
	stbi_image_free(images[0].pixels);

	// Activate callbacks on key events
	glfwSetKeyCallback(window, ExecuteCallbacks);

	//	FIXME: if you add entity while game loop is running start functions wont execute!!!
	//		or you change scene more then once or something it doesnt work
	//		THE GAME CRASHES

	// For calculating deltaTime
	clock_t lastTime = 0, currentTime;

	// Set the game as running
	running = true;

	// Call the user-given start function
	Start();

	// Load the first scene
	SetActiveScene(firstScene);

	// Main game loop
	while(running && !glfwWindowShouldClose(window)) {
		// Background color
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Calculate delta time
		currentTime = clock();

		int deltaTime = currentTime - lastTime;

		// Call the user-given update function
		Update(deltaTime);

		// Update the active scene
		activeScene->Update(deltaTime);

		// Update the frame
		glfwSwapBuffers(Game::window);

		// Poll the events so the game doesn't crash
		glfwPollEvents();

		// For calculating deltaTime
		lastTime = clock();

		// Calculate the delay necessary to keep the constant frame rate
		if (floor(16.666f - deltaTime) > 0)
		{
			std::chrono::milliseconds timespan((int)(16.666f - deltaTime));
			std::this_thread::sleep_for(std::chrono::milliseconds(timespan));
		}

		// Update the window size
		glfwSetWindowSize(window, width, height);
	}

	// Delete all scenes
	// We do it like that because scenes are automatically removed from the BigNgine::Scene::scenes vector on deletion

	const int sceneQuantity = BigNgine::Scene::GetScenes().size();

	for(int i = 0; i < sceneQuantity; i++) {
		delete BigNgine::Scene::GetScenes()[0];
	}

	// Also delete all sounds
	// Similar thing to scenes

	const int soundQuantity = BigNgine::Sound::GetSounds().size();

	for(int i = 0; i < soundQuantity; i++) {
		delete BigNgine::Sound::GetSounds()[0];
	}

	// Finish off GLFW
	window = nullptr;
	glfwTerminate();

	// Delete the game instance
	delete this;
}

void BigNgine::Game::Stop() {
	running = false;
}

void BigNgine::Game::SetActiveScene(BigNgine::Scene* scene) {
	if(!running) {
		Logger::Error("Tried to set active scene while game is not running");
		return;
	}

	if(activeScene != nullptr)
		delete activeScene;

	activeScene = scene;

	activeScene->Start();
}

void BigNgine::Game::ResizeWindow(uint32_t width, uint32_t height)
{
	if(running)
		glViewport(0, 0, width, height);

	this->width = width;
	this->height = height;
}

void BigNgine::Game::SetName(const char* name)
{
	this->name = name;
}

void BigNgine::Game::SetIcon(const char* icon)
{
	this->icon = icon;

	GLFWimage images[1];
	images[0].pixels = stbi_load(icon, &images[0].width, &images[0].height, nullptr, 4);
	glfwSetWindowIcon(window, 1, images);
	stbi_image_free(images[0].pixels);
}

uint32_t BigNgine::Game::GetWindowWidth() const
{
	return width;
}

uint32_t BigNgine::Game::GetWindowHeight() const
{
	return height;
}

BigNgine::Scene* BigNgine::Game::GetActiveScene() const
{
	return activeScene;
}

GLFWwindow* BigNgine::Game::GetWindow() const
{
	return window;
}