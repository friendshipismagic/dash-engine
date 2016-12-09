/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <clement@decoodt.eu> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return Clement Decoodt
 * ----------------------------------------------------------------------------
 */

#include <string>
#include <memory>
#include <sys/stat.h>
#include <fstream>
#include <map>

// Fast JSON Parser
#include "rapidjson/document.h"

#include "Config.h"

namespace Ressources {
	void Config::init(std::shared_ptr<Manager> localManager) {
		// Get the full file path from the ressource manager
		this->filepath = localManager->getConfigFilePath();

		// If the file does not exist, it should be created with a default
		// configuration
		// First, check if file exists
		struct stat buffer;
		bool file_not_exist = stat(filepath.c_str(), &buffer) == 0;
		if(file_not_exist)
			generate_default_config();

		// Now file must exist, load the file
		std::ifstream in(filepath, std::ios::in | std::ios::binary);		
		std::string toparse;
		in.seekg(0, std::ios::end);
		toparse.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&toparse[0], toparse.size());
		in.close();

		// Call the parser
		rapidjson::Document dom;
		dom.Parse(toparse.c_str());

		// TODO: Check it has all the mandatory parameters
		// assert(document.HasMember("hello"));
	}

	void Config::generate_default_config() {
		// TODO: Generate a default config file
	}

	std::map<std::string, char> Config::get_keymap() {
		std::map<std::string, char> keymap;
		keymap["exit"] = 'q';

		return keymap;
	}
}
