#include "log.hpp"
#include "compileconfig.hpp"

#ifdef __USE_LOGS__

struct LogMessage
{
	LogType logType;
	std::string message;
};

#if defined(_MSC_VER) || defined(__BORLANDC__)
	#define WIN32_LEAN_AND_MEAN
	#include <Windows.h>
#endif

#include <iostream>

#ifdef __LOGFILE__
	#include <fstream>
	std::ofstream logFile;
#endif

bool m_useFile, m_showInIde, m_showInConsole;

void initLog(bool useFile, bool showInIde, bool showInConsole)
{
	m_useFile = useFile;
	m_showInIde = showInIde;
	m_showInConsole = showInConsole;

#ifdef __LOGFILE__
	if (m_useFile) logFile.open(__LOGFILE__);
#endif
}

void commitLog(const LogMessage &message)
{
	const std::string &str = message.message;
	const LogType &lt = message.logType;
#ifdef __LOGFILE__
	if (m_useFile)
		if (logFile.is_open())
			logFile << str;
#endif
	if (m_showInConsole)
	{
		if (lt == LogType::Error || lt == LogType::Warning)
			std::cerr << str;
		else
			std::cout << str;
	}
#if defined(_MSC_VER) || defined(__BORLANDC__)
	if (m_showInIde)
		OutputDebugString(str.c_str());
#endif
}

#ifdef __MULTITHREAD_LOG__
	#include <queue>
	#include <string>
	#include <thread>
	#include <mutex>
	#include <condition_variable>

	std::queue<LogMessage> logQueue;
	std::mutex _mutex;
	std::condition_variable _condVar;

	void doLogOutput();
	bool doLoop = true;

	void logOutput(const LogType &lt, const std::string&str)
	{
		{
			std::unique_lock<std::mutex> _lock(_mutex);
			logQueue.push({ lt, str });
			_condVar.notify_all();
		}
	}

	void doLogOutput()
	{
		while (doLoop || !logQueue.empty())
		{
			std::unique_lock<std::mutex> _lock(_mutex);
			if (logQueue.empty())
			{
				_condVar.wait(_lock);
			}
			else
			{
				bool workToDo(!logQueue.empty());
				if (workToDo) {
					while (!logQueue.empty())
					{
						const LogMessage &str = logQueue.front();
						commitLog(str);
						logQueue.pop();
					}
					std::this_thread::sleep_for(std::chrono::milliseconds(1));
				}
			}
		}
	}

	std::thread t1(doLogOutput);
#else
void logOutput(const char *str)
{
	commitLog(str);
}
#endif

void finishLog()
{
#ifdef __MULTITHREAD_LOG__
	doLoop = false;
	_condVar.notify_all();
	t1.join();
#endif
#ifdef __LOGFILE__
	if (m_useFile) logFile.close();
#endif
}

#endif
