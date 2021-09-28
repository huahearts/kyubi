#ifndef __LOG_H__
#define __LOG_H__
#include <string>
#include <stdint.h>
#include <memory>
#include <list>
#include <iostream>
#include <sstream>
#include <map>
#include <fstream>
#include <vector>
#include <tuple>
#include <stdarg.h>
#include "singleton.h"
#define KYUBI_LOG_LEVEL(logger,level) \
	if(logger->getLevel() <= level) \
		kyubi::LogEventWrap(kyubi::LogEvent::ptr(new kyubi::LogEvent(logger,level, \
			__FILE__,__LINE__,0,kyubi::GetThreadId(),\
		kyubi::GetFiberId(),time(0)))).getSS()

#define KYUBI_LOG_DEBUG(logger) KYUBI_LOG_LEVEL(logger,kyubi::LogLevel::DEBUG)
#define KYUBI_LOG_INFO(logger) KYUBI_LOG_LEVEL(logger,kyubi::LogLevel::INFO)
#define KYUBI_LOG_WARN(logger) KYUBI_LOG_LEVEL(logger,kyubi::LogLevel::WARN)
#define KYUBI_LOG_ERROR(logger) KYUBI_LOG_LEVEL(logger,kyubi::LogLevel::ERROR)
#define KYUBI_LOG_FATAL(logger) KYUBI_LOG_LEVEL(logger,kyubi::LogLevel::FATAL)
namespace kyubi{
//日志事件
class Logger;
//日志级别
class LogLevel {
public:
    /**
     * @brief 日志级别枚举
     */
	enum Level{
		UNKNOW = 0,
		DEBUG = 1,
		INFO = 2,
		WARN = 3,
		ERROR = 4,
		FATAL = 5
	};

	static const char* ToString(LogLevel::Level level);
};


class LogEvent{
public:
	typedef std::shared_ptr<LogEvent> ptr;
	LogEvent(std::shared_ptr<Logger> logge,LogLevel::Level level,const char* file,int32_t m_line,uint32_t elapse,
		uint32_t thread_id,uint32_t fiber_id,uint64_t time);
		~LogEvent();
	const char* getFile() const { return m_file; }
	int32_t getLine() const { return m_line; }
	uint32_t getElapse() const { return m_elapse; }
	uint32_t getThreadId() const { return m_threadId; }
	uint32_t getFiberId() const { return m_fiberId; }
	uint32_t getTime() const { return m_time; }
	std::string getContent() const { return m_ss.str();}
	std::shared_ptr<Logger> getLogger() { return m_logger; }
	LogLevel::Level getLevel() { return m_level; }
	std::stringstream& getSS() { return m_ss; }
	void format(const char* fmt,...);
	void format(const char* fmt,va_list al);
private:
	const char* m_file  = nullptr;  //文件名
	int32_t m_line = 0;             //行号
	uint32_t m_elapse = 0;          //程序启动开始到现在的毫秒数
	uint32_t m_threadId = 0;        //线程ID
	uint32_t m_fiberId = 0;         //协程ID
	uint64_t m_time;                //时间戳
	std::stringstream m_ss;
	std::shared_ptr<Logger> m_logger;
	LogLevel::Level m_level;
};

class LogEventWrap{
public:
	LogEventWrap(LogEvent::ptr e);
	~LogEventWrap();

	std::stringstream& getSS() { return m_event->getSS(); }
private:
	LogEvent::ptr m_event;
};


//日志格式器
class LogFormatter{
public:
	typedef std::shared_ptr<LogFormatter> ptr;
	LogFormatter(const std::string& pattern);
	//%t 
	std::string format(std::shared_ptr<Logger> logger,LogLevel::Level level,LogEvent::ptr event);
public:
 /**
     * @brief 日志内容项格式化
     */
	class FormatItem{
	public:
		typedef std::shared_ptr<FormatItem> ptr;
		virtual ~FormatItem(){}
		virtual void format(std::ostream& os ,std::shared_ptr<Logger> logger,LogLevel::Level level,LogEvent::ptr event) = 0;
	};
	void init();
private:
	std::string m_pattern;
	std::vector<FormatItem::ptr> m_items;
};
//日志输出地
class LogAppender{
	friend class Logger;
public:
	typedef std::shared_ptr<LogAppender> ptr;
	virtual ~LogAppender(){}
	virtual void log(std::shared_ptr<Logger> logger,LogLevel::Level level ,LogEvent::ptr event) = 0;

	void setFormatter(LogFormatter::ptr val) { m_formatter = val; }
	LogFormatter::ptr getFormatter() { return m_formatter;}

	LogLevel::Level getLevel() const { return m_level; }
	void setLevel(LogLevel::Level level) { m_level = level; } 
protected:
	LogLevel::Level m_level = LogLevel::Level::DEBUG;
	LogFormatter::ptr m_formatter;
};

class Logger : public std::enable_shared_from_this<Logger>
{
public:
	typedef std::shared_ptr<Logger> ptr;

	Logger(const std::string&name = "root");
	void log(LogLevel::Level level,LogEvent::ptr event);
	void debug(LogEvent::ptr event);
	void info(LogEvent::ptr event);
	void warn(LogEvent::ptr event);
	void error(LogEvent::ptr event);
	void fatal(LogEvent::ptr event);


	void addAppender(LogAppender::ptr appender);
	void delAppender(LogAppender::ptr appender);
	LogLevel::Level getLevel() const { return m_level; }
	void setLevel(LogLevel::Level level) { m_level = level; }

	const std::string& getName() const { return m_name; }

	LogFormatter::ptr getFormatter() { return m_formatter; }
private:
	std::string m_name;         //日志名称
	LogLevel::Level m_level;    //日志级别
	std::list<LogAppender::ptr> m_appenders;
	LogFormatter::ptr m_formatter;
};

class StdoutAppender : public LogAppender {
public:
	typedef std::shared_ptr<StdoutAppender> ptr;
	
	void log(std::shared_ptr<Logger> logger,LogLevel::Level level ,LogEvent::ptr event) override;
};

class FileAppedner : public LogAppender {
public:
	typedef std::shared_ptr<FileAppedner> ptr;
	FileAppedner(const std::string fileName);
	void log(std::shared_ptr<Logger> logger,LogLevel::Level level ,LogEvent::ptr event) override;

	bool reopen();
private:
	std::string m_name;
	std::ofstream m_filestream;
};

class LogManager {
public:
	LogManager();
	Logger::ptr getLogger(const std::string& name);
	void init();
private:
	std::map<std::string,Logger::ptr> m_loggers;
	Logger::ptr m_root;
};

typedef kyubi::Singleton<LogManager> LogMgr;
}
#endif

