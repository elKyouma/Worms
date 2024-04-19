#include <SDL2/SDL_error.h>
#include <sstream>
#include "SDL_Exception.h"


SDL_Exception::SDL_Exception( int line, const char* file ) noexcept
	:
	line( line ),
	file( file )
{}

const char* SDL_Exception::what() const noexcept
{
	std::ostringstream oss;
	oss << GetType() << std::endl
		<< GetOriginString() << std::endl
		<< SDL_GetError();
	whatBuffer = oss.str();
	return whatBuffer.c_str();
}

const char* SDL_Exception::GetType() const noexcept
{
	return "SDL Exception";
}

int SDL_Exception::GetLine() const noexcept
{
	return line;
}

const std::string& SDL_Exception::GetFile() const noexcept
{
	return file;
}

std::string SDL_Exception::GetOriginString() const noexcept
{
	std::ostringstream oss;
	oss << "[File] " << file << std::endl
		<< "[Line] " << line;
	return oss.str();
}
