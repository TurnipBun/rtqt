#include <cstdio>
//#include <cassert>
#include <cstring>
#include <log.hpp>

/************************FileLog*********************************/

#ifdef VXWORKS
const string FileLog::defaultFileName = "/ata0a/rtqt.txt";
#else
const string FileLog::defaultFileName = "rtqt.txt";
#endif /* VXWORKS */

FileLog::FileLog(const string &f)
    :fd(NULL), fileName(f), ioBuf(NULL), pPtr(NULL)
{
    
}

FileLog::~FileLog()
{
    destory();
}

int FileLog::init()
{
    fd = fopen(fileName.c_str(),"w");
    ioBuf = new char[READ_LOG_MAX_LEN + 1];
    pPtr = ioBuf;
    if (fd == NULL) return LOG_ERR;
    return LOG_SUC;
}

void FileLog::destory()
{
    if (fd != NULL)
    {
        fclose(fd);
    }

    if (ioBuf != NULL)
    {
        delete(ioBuf);
    }
}

/*在文件末尾添加log,接收string类型参数*/
void FileLog::add(const string &text)
{
    fseek(fd, 0, SEEK_END);
    fwrite(text.c_str(),1,text.length(),fd);
    fflush(fd);
}

/*在文件末尾添加log,接收字符指针类型参数*/
void FileLog::add(const char * pText)
{
    fseek(fd, 0, SEEK_END);
    fwrite(pText,1,strlen(pText),fd);
    fflush(fd);
}

FileLog& FileLog::operator<<(const string &text)
{
    addToBuf(text.c_str());
    return *this;
}

FileLog& FileLog::operator<<(const char * pText)
{
    addToBuf(pText);
    if (strcmp(pText,ENDL) == 0)
    {
        add(ioBuf);
        pPtr = ioBuf;
    }
    return *this;
}
FileLog& FileLog::operator<<(int val)
{
    char array[128];
    sprintf(array,"%d",val);
    addToBuf(array);
    return *this;
}

char *FileLog::get()
{
    FILE *pReadFd = fopen(fileName.c_str(),"r");
    if (pReadFd == NULL) return NULL;
    
    
    unsigned long recv;
    fseek(pReadFd, 0, SEEK_END);
    unsigned long size = ftell(pReadFd);
    
    if (size > READ_LOG_MAX_LEN)
    {
        fseek(pReadFd, 0-READ_LOG_MAX_LEN, SEEK_END);
        fread(ioBuf, 1, READ_LOG_MAX_LEN, pReadFd);
        ioBuf[READ_LOG_MAX_LEN] = '\0';
    }
    else
    {
        fseek(pReadFd, 0, SEEK_SET);
        recv = fread(ioBuf, 1, size, pReadFd);
        ioBuf[recv] = '\0';
    }
    
    fclose(pReadFd);
    return ioBuf;
}


void FileLog::addToBuf(const char * pText)
{
    strcpy(pPtr,pText);
    pPtr += strlen(pText);
}

/*********************LogFactory************************/

LogFactory *LogFactory::pInst = NULL;

LogFactory *LogFactory::getFactory()
{
    if (NULL == pInst)
    {
        pInst = new LogFactory();
    }
    return pInst;
}

Log *LogFactory::createLog(LogType type)
{
    if (IS_TO_FILE_ON(type)) return new FileLog();
    else return NULL;
}

