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
#include <glm/glm.hpp>

// Window Manager lib
#include "GameWindows/GameWindows.h"

// Config Manager lib
#include "Ressources/Ressources.h"
#include "Ressources/Config.h"

// Managers
std::shared_ptr<Ressources::Manager> gRessourcesManager;
std::shared_ptr<Ressources::Config> gConfigManager;
std::shared_ptr<GameWindows::Manager> gWindowManager;

// Macro used by easylogging for initializing the logging system
INITIALIZE_EASYLOGGINGPP

// Here we begin.
// Start the FreeGLUT window manager
int main(int argc, char **argv) {

	// Init log system, and give it input arguments
	START_EASYLOGGINGPP(argc, argv);
	// Load logger conf
	el::Configurations easylogConf("log.conf");
	LOG(INFO) << "Logging system online";

	// Init ressource manager
	LOG(DEBUG) << "Initializing ressource manager";
	gRessourcesManager = std::make_shared<Ressources::Manager>();
	gRessourcesManager->init();
	LOG(DEBUG) << "Initializing config manager";
	gConfigManager = std::make_shared<Ressources::Config>();
	gConfigManager->init(gRessourcesManager);
	LOG(INFO) << "Ressources online";

	// Init Window manager
	LOG(DEBUG) << "Initializing Window manager";
	gWindowManager = std::make_shared<GameWindows::Manager>();
	gWindowManager->init(gConfigManager);
	LOG(INFO) << "Windowing system online";
	gWindowManager->create_game_window("Dash Engine");
	LOG(INFO) << "All systems online, ready to enter the game loop";

	// enter GLUT event processing cycle
	while(1) {}
	return 0;
}
