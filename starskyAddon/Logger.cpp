#include "Logger.h"

void Logger::Print(stringstream& stream)
{
	cout << LOG_TAG << " " << stream.str();

	if (logFile == nullptr)
	{
		/*char name[512];

		time_t _time = time(nullptr);
		tm* ltm = localtime(&_time);

		sprintf(name, "[%d/%d/%d]SCHLogs.log",ltm->tm_mday,ltm->tm_mon+1,ltm->tm_year+1900);*/
		logFile = new ofstream(LOG_FILENAME, ios_base::app);
		cout << std::hex << logFile << endl;
	}

	if (logFile->is_open())
	{
		time_t _time = time(nullptr);

		tm* ltm = localtime(&_time);

		char buffer[256];
		sprintf(buffer, "[%02d:%02d:%02d] ", ltm->tm_hour + 1, ltm->tm_min + 1, ltm->tm_sec + 1);

		*logFile << buffer << stream.str();
		logFile->flush();
	}
	else
		cerr << "FILE LOG ERROR" << endl;
}

void Logger::Debug(const char* str, ...)
{
	va_list arguments;

	va_start(arguments, str);

	char finalStr[256];
	vsprintf(finalStr, str, arguments);

	va_end(arguments);

	stringstream stream;
	stream << finalStr << endl;
	Print(stream);
}

void Logger::Error(const char* str, ...)
{
	va_list arguments;

	va_start(arguments, str);

	char finalStr[256];
	vsprintf(finalStr, str, arguments);

	va_end(arguments);

	stringstream stream;
	stream << "[ERROR] " << finalStr << endl;
	Print(stream);
}

void Logger::Flush()
{
	if (logFile->is_open())
		logFile->flush();
}

void Logger::Close()
{
	if (logFile->is_open())
	{
		logFile->flush();
		logFile->close();
	}
}