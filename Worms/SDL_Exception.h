#pragma once
#include <exception>
#include <string>

class SDL_Exception : public std::exception
{
public:
	SDL_Exception( int line, const char* file ) noexcept;
	const char* what() const noexcept override;
	virtual const char* GetType() const noexcept;
	int GetLine() const noexcept;
	const std::string& GetFile() const noexcept;
	std::string GetOriginString() const noexcept;
private:
	int line;
	std::string file;
	mutable std::string whatBuffer;
};

#define SDL_CALL(x) SD:SDL_ClearError(); if(x != 0) throw SDL_Exception(__LINE__, __FILE__)
#define SDL_CHECK(x) if(x == NULL) throw SDL_Exception(__LINE__, __FILE__)

