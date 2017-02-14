/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <clement@decoodt.eu> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return Clement Decoodt
 * ----------------------------------------------------------------------------
 */

#include <memory>
#include <chrono>
#include <thread>

#include "GameWindows/HID.h"
#include "Renderer/BatchRenderer.h"
#include "easylogging++.h"

#include "GameLoop.h"

void GameLoop::init(int ts) {
	// Update the main timestep
	main_ts = ts;
	last_update = input_time = game_update_time = render_time =
		std::chrono::high_resolution_clock::now();
}

void GameLoop::connect_HID(std::shared_ptr<HID::Manager> gHIDManager) {
	// Connect the HID Manager
	lHIDManager = gHIDManager;
}

void GameLoop::connect_renderer(std::shared_ptr<Renderer::Batch> gBR) {
	// Connect the Batch Renderer
	lBatchRenderer = gBR;
}

void GameLoop::loop() {
	while(1) {
		// Process the inputs
		LOG(DEBUG) << "Processing inputs";
		lHIDManager->check_for_inputs();

		// Time to process the inputs
		input_time = std::chrono::high_resolution_clock::now();
		elapsed_input_time = std::chrono::duration_cast<std::chrono::microseconds>
			(input_time - last_update).count();

		// Update the game, as we know how many time is left before the displaying
		// to the user, we can update the game to now + time to render
		// TODO: Implement game update - (Physics + Animation)
		LOG(DEBUG) << "Updating the game";

		// Time to update the game
		game_update_time = std::chrono::high_resolution_clock::now();
		elapsed_game_update_time = std::chrono::duration_cast<std::chrono::microseconds>
			(input_time - game_update_time).count();

		// Render (variable rendering)
		// TODO: Implement the render engine
		LOG(DEBUG) << "Rendering image";
		lBatchRenderer->render();

		// Time to render
		render_time = std::chrono::high_resolution_clock::now();
		elapsed_render_time = std::chrono::duration_cast<std::chrono::microseconds>
			(game_update_time - render_time).count();

		// Wait for next update (fixed time step)
		total_elapsed = std::chrono::duration_cast<std::chrono::microseconds>
			(render_time - last_update).count();
		LOG(DEBUG) << "Waiting for " << main_ts - total_elapsed << " us";
		std::this_thread::sleep_for(std::chrono::microseconds(main_ts - total_elapsed));

		// Update last_update time
		last_update = std::chrono::high_resolution_clock::now();

		// Go back to loop
	}
}
