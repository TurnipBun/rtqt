#ifndef _LOG_HPP_
#define _LOG_HPP_

#include <string>
using std::string;

enum LogType
{
  TO_NONE   = 0,
  TO_FILE   = 1,
  TO_MEM    = 2,
  TO_STDOUT = 4
};


#define LOG_SUC 0
#define LOG_ERR 1

#define READ_LOG_MAX_LEN 1024

#define IS_TO_NONE(x) x == TO_NONE
#define IS_TO_FILE_ON(x) (TO_FILE & (x)) == TO_FILE
#define IS_TO_MEM_ON(x) (TO_MEM & (x)) == TO_MEM
#define IS_TO_STDOUT_ON(x) (TO_STDOUT & (x)) == TO_STDOUT

#define OFF_TO_FILE(x) (x) &= (~TO_FILE)
#define OFF_TO_MEM(x) (x) &= (~TO_MEM)
#define OFF_TO_STDOUT(x) (x) &= (~TO_STDOUT)

#define ENDL "\n\r"

/*接口*/
class Log
{
public:
    virtual int init() = 0;//初始化
    virtual void destory() = 0;//释放资源
    virtual void add(const string &text) = 0;//添加log到内存
    virtual void add(const char * pText) = 0;
    virtual Log& operator<<(const string &text) = 0;
    virtual Log& operator<<(char ch) = 0;
    virtual Log& operator<<(const char * pText) = 0;
    virtual Log& operator<<(int val) = 0;
    virtual char *get() = 0;//获取log,对标准输出型的log无效
    virtual ~Log(){};
};

class FileLog : public Log
{
public:
    FileLog(const string &f = FileLog::defaultFileName);
    ~FileLog();

    int init();
    void destory();
    void add(const string &text);
    void add(const char * pText);
    FileLog& operator<<(const string &text);
    FileLog& operator<<(char ch);
    FileLog& operator<<(const char * pText);
    FileLog& operator<<(int val);
    char *get();
private:
    void addToBuf(const char * pText);
    FILE *fd;
    string fileName;
    char *ioBuf;
    char *pPtr;
    static const string defaultFileName;
};

/*工厂类,支持创建不同类型的多个log*/
class LogFactory
{
public:
    static LogFactory *getFactory();
    Log *createLog(LogType type);
private:
    LogFactory(){};
    LogFactory(const LogFactory&){};
    LogFactory& operator=(const LogFactory&){return *this;}
    ~LogFactory(){};

    static LogFactory* pInst;
};

#endif /* _LOG_HPP_ */
