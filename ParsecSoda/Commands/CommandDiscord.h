#pragma once

#include "ACommand.h"
#include <iostream>
#include "../CompilerDirectives.h"

using namespace std;

class CommandDiscord : public ACommand
{
public:
	const COMMAND_TYPE type() override { return COMMAND_TYPE::BOT_MESSAGE; }

	CommandDiscord(Guest& sender)
		: _sender(sender)
	{}

	bool run() override
	{
		
		if (MetadataCache::preferences.discord != "")
			_replyMessage = MetadataCache::preferences.discord.c_str();
		else return false;

		return true;
	}

	static vector<const char*> prefixes()
	{
		return vector<const char*> { "!discord" };
	}

protected:
	Guest& _sender;
};

