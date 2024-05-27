#include "Terminal.h"

#include <fstream>
#include <imgui.h>

void Terminal::Log( const std::string& message, LogLevel level ) {
	std::string logMessage = getCurrentTime() + " [" + getLogLevelString( level ) + "] " + message;

	std::ofstream ofs( logFile, std::ios_base::app );
	if ( ofs ) {
		ofs << logMessage << std::endl;
	}
}

void Terminal::Update()
{
}

void Terminal::Render()
{
	bool open = true;
	ImGui::Begin( "Terminal", &open );
	ImGui::End();
}

std::string Terminal::getCurrentTime() {
	time_t now = time( 0 );
	struct tm timeInfo;
	char timeBuffer[20];

#ifdef _WIN32
	localtime_s( &timeInfo, &now );
#else
	localtime_r( &now, &timeInfo );
#endif

	strftime( timeBuffer, sizeof( timeBuffer ), "%Y-%m-%d %H:%M:%S", &timeInfo );
	return std::string( timeBuffer );
}

std::string Terminal::getLogLevelString( LogLevel level ) {
	switch ( level ) {
	case INFO: return "INFO";
	case WARNING: return "WARNING";
	case ERROR: return "ERROR";
	default: return "UNKNOWN";
	}
}
