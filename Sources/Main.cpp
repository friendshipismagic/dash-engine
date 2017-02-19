/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <clement@decoodt.eu> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return Clement Decoodt
 * ----------------------------------------------------------------------------
 */

// Standard headers
#include <iostream>
#include <memory>

// Logging system
#include "easylogging++.h"

// GL Related includes
#include <GL/glew.h>

// GLSL-Like lib
#include "glm/glm.hpp"

// Window Manager lib
#include "GameWindows/GameWindows.h"
#include "GameWindows/HID.h"

// Ressources Manager lib
#include "Ressources/Ressources.h"
#include "Ressources/Config.h"
#include "Ressources/Models.h"
#include "Ressources/Shaders.h"

// Main Game Loop
#include "GameLoop.h"

// Graphical renderer
#include "Renderer/BatchRenderer.h"
#include "Renderer/Lights.h"

// Managers
std::shared_ptr<Ressources::Manager> gRessourcesManager;
std::shared_ptr<Ressources::Config> gConfigManager;
std::shared_ptr<Ressources::Shaders> gShadersManager;
std::shared_ptr<GameWindows::Manager> gWindowManager;
std::shared_ptr<Renderer::Batch> gBatchRenderer;
std::shared_ptr<Renderer::Lights> gLights;
std::shared_ptr<GameLoop> gGameLoop;

// Macro used by easylogging for initializing the logging system
INITIALIZE_EASYLOGGINGPP

// Setup the main game structure
// This is the part where the game mecanics are setup
void setupGame() {
	int main_windows = gWindowManager->create_game_window("Dash Engine");

	// Make a list of events to catch in the window
	std::vector<std::string> events;
	events.push_back("Exit");

	// Add them to adapter and connect it to main window
	int exit_adapter = gWindowManager->create_adapter(events);
	gWindowManager->connect_adapter(exit_adapter);

	// Init Lighting system
	LOG(DEBUG) << "Initializing lighting system";
	gLights = std::make_shared<Renderer::Lights>();
	LOG(INFO) << "Lighting system online";

	LOG(DEBUG) << "Adding default shader";
	std::vector<std::string> default_shaders = {"default.frag", "default.vert"};
	GLuint default_prog = gShadersManager->make_shader_program(default_shaders);
	gRessourcesManager->setDefaultShaderProgram(default_prog);
	LOG(DEBUG) << "Shaders online";

	//XXX
	// Load an object to test the scene import
	LOG(INFO) << "Loading model";
	std::shared_ptr<Ressources::Models> test_model;
	test_model = std::make_shared<Ressources::Models>();
	test_model->init(gRessourcesManager, "teapot.obj");

	// Add the scene to the batch renderer for rendering :)
	LOG(INFO) << "Importing model to renderer";
	gBatchRenderer->set_scene(test_model);

	// Turn on some lights
	LOG(INFO) << "Making lights";
	// Set light 0
	gLights->set_light_state(0, true);
	gLights->set_diffuse(0, glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
	gLights->set_specular(0, glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
	gLights->set_position(0, glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));
	gLights->set_direction(0, glm::vec4(0.0f, 0.0f, 0.0f, 0.0f));
	// Set light 1
	gLights->set_light_state(1, true);
	gLights->set_diffuse(1, glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
	gLights->set_specular(1, glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
	gLights->set_position(1, glm::vec4( 0.0f,10.0f, 0.0f, 1.0f));
	gLights->set_direction(1, glm::vec4(0.0f, 0.0f, 0.0f, 0.0f));
	// Set light 2
	gLights->set_light_state(2, true);
	gLights->set_diffuse(2, glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));
	gLights->set_specular(2, glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));
	gLights->set_position(2, glm::vec4( 0.0f, 0.0f,10.0f, 1.0f));
	gLights->set_direction(2, glm::vec4(0.0f, 0.0f, 0.0f, 0.0f));

	// Update all now
	gLights->update_UBO();
}

// Here we begin.
// Start the FreeGLUT window manager
int main(int argc, char **argv) {

	// Init log system, and give it input arguments
	START_EASYLOGGINGPP(argc, argv);
	// Load logger conf
	el::Configurations easylogConf("log.conf");
	el::Loggers::reconfigureAllLoggers(easylogConf);
	LOG(INFO) << "Logging system online";

	// Init ressource manager
	LOG(DEBUG) << "Initializing ressource manager";
	gRessourcesManager = std::make_shared<Ressources::Manager>();
	gRessourcesManager->init();
	LOG(DEBUG) << "Initializing config manager";
	gConfigManager = std::make_shared<Ressources::Config>();
	gConfigManager->init(gRessourcesManager);
	LOG(INFO) << "Ressources online";
	// Init Shaders manager
	LOG(DEBUG) << "Initializing shaders manager";
	gShadersManager = std::make_shared<Ressources::Shaders>();
	gShadersManager->init(gRessourcesManager);

	// Init Window manager
	LOG(DEBUG) << "Initializing Window manager";
	gWindowManager = std::make_shared<GameWindows::Manager>();
	gWindowManager->init(gConfigManager);
	LOG(INFO) << "Windowing system online";

	// Init Batch renderer
	LOG(DEBUG) << "Initializing batch renderer";
	gBatchRenderer = std::make_shared<Renderer::Batch>();
	gBatchRenderer->init(gConfigManager, gWindowManager);
	LOG(INFO) << "Batch renderer online";

	// Setup the game structure
	LOG(DEBUG) << "Setting up game structure";
	setupGame();
	LOG(INFO) << "All systems online, ready to enter the game loop";

	// Instanciate the game loop
	gGameLoop = std::make_shared<GameLoop>();
	gGameLoop->init(100000/6); // 60 Hz fixed time update
	gGameLoop->connect_HID(gWindowManager->getHID());
	gGameLoop->connect_renderer(gBatchRenderer);

	// enter event processing cycle
	LOG(DEBUG) << "Entering game loop, goodbye!";
	gGameLoop->loop();

	return 0;
}
