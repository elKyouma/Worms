#include "Terminal.h"

#include <fstream>
#include <imgui.h>

void Terminal::Log( std::string&& message, LogLevel level ) {
	if ( !logFile ) [[unlikely]] return;

	const std::string logMessage = getCurrentTime() + " [" + getLogLevelString( level ) + "] " + message;
	Lines.emplace_back( logMessage );
	logFile << logMessage << '\n';
}

void Terminal::Update()
{
}

void Terminal::Render()
{
	char input[20] = "";
	bool open = true;
	ImGui::Begin( "Terminal", &open );
	ImGui::BeginChild( "history", { 0, 140 }, false, ImGuiWindowFlags_HorizontalScrollbar );

	if ( ImGui::GetScrollY() < 0.9f )
		scroll = true;

	for ( const std::string& line : Lines )
		ImGui::Text( line.c_str() );

	if ( scroll )
	{
		ImGui::SetScrollHereY( 1.0 );
		scroll = false;
	}
	ImGui::EndChild();
	if ( ImGui::InputText( "Terminal", input, 20, ImGuiInputTextFlags_EnterReturnsTrue ) )
	{
		Terminal::Get().Log( input, LogLevel::INFO );
		strcpy_s( input, "" );
		scroll = true;
		ImGui::SetKeyboardFocusHere( -1 );
	}
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
