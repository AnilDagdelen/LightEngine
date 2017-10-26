#ifndef _LOGGER_H
#define _LOGGER_H

#include "Manager.h"

#ifndef _VECTOR_
#include <vector>
#endif
#ifndef _STRING_H
#include "string.h"
#endif
#ifndef _LOGTYPE_H
#include "LogType.h"
#endif

struct LogData
{
	LogData(LogType t, const std::tstring& m)
		: type(t)
		, message(m)
	{}

	const std::tstring toString();

	LogType type;
	std::tstring message;
};

#define LOGTYPE_INFO LogType::INFO_LOG,__LINE__,__FILEW__
#define LOGTYPE_WARNING LogType::WARNING_LOG,__LINE__,__FILEW__
#define LOGTYPE_ERROR LogType::ERROR_LOG,__LINE__,__FILEW__
#define LOGTYPE_TODO LogType::TODO_LOG,__LINE__,__FILEW__

class Logger : public Manager
{
public:
	Logger(void);
	virtual ~Logger(void);

	bool initialize();
	bool shutdown();

	static void log(const std::tstring& Message, LogType type, int ln, const std::tstring& fn,bool logtofile=false);
	static void writeLogFile();

private:
	Logger(const Logger& tRef);
	const Logger& operator=(const Logger& tRef);

	std::vector<LogData> log_messages;
};

#endif

