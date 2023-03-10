#pragma once
#include <string>
using std::string;
#include <SDL_log.h>

// We will use this class to write different types of messages (info, error ...) in a console,
// with a category that will help to know which system trigger an error

enum class LogCategory
{
	Application = SDL_LOG_CATEGORY_APPLICATION,
	Assert = SDL_LOG_CATEGORY_ASSERT,
	Audio = SDL_LOG_CATEGORY_AUDIO,
	Error = SDL_LOG_CATEGORY_ERROR,
	Input = SDL_LOG_CATEGORY_INPUT,
	Render = SDL_LOG_CATEGORY_RENDER,
	System= SDL_LOG_CATEGORY_SYSTEM,
	Test = SDL_LOG_CATEGORY_TEST,
	Video = SDL_LOG_CATEGORY_VIDEO

};

class Log
{
public:
	// We delete default constructor, copy constructor, and assignement operator so they cannot be used
	Log() = delete;
	Log(const Log&) = delete;
	Log& operator=(const Log&) = delete;

	static void info(const string& message);
	static void error(LogCategory category, const string& message);
};

