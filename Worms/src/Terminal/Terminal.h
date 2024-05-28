#pragma once
#include <string>
#include <vector>

enum LogLevel
{
	INFO,
	WARNING,
	ERROR
};

class Terminal
{
public:
	Terminal( const Terminal& ) = delete;
	Terminal( Terminal&& ) = delete;

	static Terminal& Get()
	{
		static Terminal terminal{};
		return terminal;
	}

	void Log( const std::string& message, LogLevel level );

	void Update();
	void Render();

private:
	std::string logFile = "logs.txt";
	std::vector<std::string> Lines;

	std::string getCurrentTime();
	std::string getLogLevelString( LogLevel level );
	Terminal() = default;
};
