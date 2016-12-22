/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <clement@decoodt.eu> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return Clement Decoodt
 * ----------------------------------------------------------------------------
 */

#pragma once

#include <memory>
#include <chrono>

#include "GameWindows/HID.h"

// TODO: Should I put it in a namespace?

class GameLoop {
	public:
		// Default initializer, should not do anything
		GameLoop () {};
		// Default destructor, should not do anything
		~GameLoop () {};

		// Initializer, needs the main time step in us
		void init(int);

		// Connect the HID Manager
		void connect_HID(std::shared_ptr<HID::Manager>);

		// Enter the loop :)
		void loop();
	private:
		// Main HID Manager
		std::shared_ptr<HID::Manager> lHIDManager;
		// Temp variable used for storing the last update time clock
		std::chrono::high_resolution_clock::time_point last_update;
		std::chrono::high_resolution_clock::time_point input_time;
		std::chrono::high_resolution_clock::time_point game_update_time;
		std::chrono::high_resolution_clock::time_point render_time;
		// Time elapsed on last update for each main part, in us
		int elapsed_input_time;
		int elapsed_game_update_time;
		int elapsed_render_time;
		// Time step
		int main_ts;
		// Temp variable for last total time elapsed
		int total_elapsed;
};
