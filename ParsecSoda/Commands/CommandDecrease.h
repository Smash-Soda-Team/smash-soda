#pragma once

#include <sstream>
#include <algorithm>
#include "parsec-dso.h"
#include "ACommandIntegerArg.h"
#include "../Modules/Hotseat.h"

class CommandDecrease : public ACommandStringArg
{
public:
	const COMMAND_TYPE type() override { return COMMAND_TYPE::BOT_MESSAGE; }

	CommandDecrease(const char* msg, Hotseat& hotseat)
		: ACommandStringArg(msg, internalPrefixes()), _hotseat(hotseat)
	{}

	bool run() override {

		if (!MetadataCache::preferences.hotseat) return false;

		if (!ACommandStringArg::run()) {
			_replyMessage = MetadataCache::preferences.chatbotName + " | Usage: !decrease <minutes> <seat (optional)>\0";
			return false;
		}

		// Split _strArg by spaces
		std::istringstream iss(_stringArg);
		std::vector<std::string> results(std::istream_iterator<std::string>{iss},
			std::istream_iterator<std::string>());

		// Convert first value to int
		int _intArg = 0;
		try {
			_intArg = std::stoi(results[0]);
		}
		catch (std::invalid_argument) {
			_replyMessage = MetadataCache::preferences.chatbotName + " | Usage: !decrease <minutes> <seat (optional)>\0";
			return false;
		}

		if (results.size() != 2) {
			_hotseat.decreaseTime(_intArg);
		}
		else {
			// Convert second value to int
			int _seat = -1;
			try {
				_seat = std::stoi(results[1]);
			}
			catch (std::invalid_argument) {
				_replyMessage = MetadataCache::preferences.chatbotName + " | Usage: !extend <minutes> <seat (optional)>\0";
				return false;
			}
			_hotseat.decreaseTime(_intArg, _seat);
		}

		std::ostringstream reply;
		reply << "[HOTSEAT] | The hotseat time for current guest was decreased by: " << _intArg << " minutes.\0";
		_replyMessage = reply.str();

		return true;

	}

	static vector<const char*> prefixes() {
		return vector<const char*> { "!decrease" };
	}

protected:
	Hotseat& _hotseat;
	
	static vector<const char*> internalPrefixes() {
		return vector<const char*> { "!decrease " };
	}
};