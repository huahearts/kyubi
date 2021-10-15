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
#include "util.h"
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

#define KYUBI_LOG_FMT_LEVEL(logger,level,fmt, ...) \
	if(logger->getLevel() <= level) \
		kyubi::LogEventWrap(kyubi::LoEvent::ptr(new kyubi::LogEvent(logger,level \
			__FILE__,__LINE__,0,kyubi::GetThreadId(),\
			kyubi::GetFiberId(),time(0)))).getEvent()->fotmat(fmt,__VA_ARGS__)

#define KYUBI_LOG_FMT_DEBUG(logger,fmt,...) KYUBI_LOG_FMT_LEVEL(logger,kyubi::LogLevel::DEBUG,fmt,__VA_ARGS__)
#define KYUBI_LOG_FMT_INFO(logger,fmt,...) KYUBI_LOG_FMT_LEVEL(logger,kyubi::LogLevel::INFO,fmt,__VA_ARGS__)
#define KYUBI_LOG_FMT_WARN(logger,fmt,...) KYUBI_LOG_FMT_LEVEL(logger,kyubi::LogLevel::WARN,fmt,__VA_ARGS__)
#define KYUBI_LOG_FMT_ERROR(logger,fmt,...) KYUBI_LOG_FMT_LEVEL(logger,kyubi::LogLevel::ERROR,fmt,__VA_ARGS__)
#define KYUBI_LOG_FMT_FATAL(logger,fmt,...) KYUBI_LOG_FMT_LEVEL(logger,kyubi::LogLevel::FATAL,fmt,__VA_ARGS__)

#define KYUBI_LOG_ROOT() kyubi::LogMgr::GetInstance()->getRoot()
#define KYUBI_LOG_NAME(name) kyubi::LogMgr::GetInstance()->getLogger(name)
namespace kyubi{
//日志事件
class Logger;
class LogManager;
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
	static Level FromString(const std::string& str);
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
	bool isError() const { return m_error;}
	std::string getPattern() const { return m_pattern; }

	
private:
	std::string m_pattern;
	std::vector<FormatItem::ptr> m_items;
	bool m_error = false;
};
//日志输出地
class LogAppender{
	friend class Logger;
public:
	typedef std::shared_ptr<LogAppender> ptr;
	virtual ~LogAppender(){}
	virtual void log(std::shared_ptr<Logger> logger,LogLevel::Level level ,LogEvent::ptr event) = 0;

	void setFormatter(LogFormatter::ptr val);
	LogFormatter::ptr getFormatter() { return m_formatter;}

	LogLevel::Level getLevel() const { return m_level; }
	void setLevel(LogLevel::Level level) { m_level = level; } 

	virtual std::string toYamlString() = 0;
protected:
	LogLevel::Level m_level = LogLevel::Level::DEBUG;
	bool m_hasFormatter = false;
	LogFormatter::ptr m_formatter;
};

class Logger : public std::enable_shared_from_this<Logger>
{
friend class LogManager;
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
	void clearAppenders();
	LogLevel::Level getLevel() const { return m_level; }
	void setLevel(LogLevel::Level level) { m_level = level; }

	const std::string& getName() const { return m_name; }

	LogFormatter::ptr getFormatter() { return m_formatter; }
	void setFormatter(const std::string& val);
	void setFormatter(LogFormatter::ptr val); 

	std::string toYamlString();
private:
	std::string m_name;         //日志名称
	LogLevel::Level m_level;    //日志级别
	std::list<LogAppender::ptr> m_appenders;
	LogFormatter::ptr m_formatter;
	Logger::ptr m_root;
};

class StdoutAppender : public LogAppender {
public:
	typedef std::shared_ptr<StdoutAppender> ptr;
	
	void log(std::shared_ptr<Logger> logger,LogLevel::Level level ,LogEvent::ptr event) override;
	std::string toYamlString() override;
};

class FileAppedner : public LogAppender {
public:
	typedef std::shared_ptr<FileAppedner> ptr;
	FileAppedner(const std::string fileName);
	void log(std::shared_ptr<Logger> logger,LogLevel::Level level ,LogEvent::ptr event) override;

	bool reopen();
	std::string toYamlString() override;
private:
	std::string m_name;
	std::ofstream m_filestream;
};

class LogManager {
public:
	LogManager();
	Logger::ptr getLogger(const std::string& name);
	void init();
	Logger::ptr getRoot() const { return m_root; }
	std::string toYamlString();
private:
	std::map<std::string,Logger::ptr> m_loggers;
	Logger::ptr m_root; 
};

typedef kyubi::Singleton<LogManager> LogMgr;
}
#endif

