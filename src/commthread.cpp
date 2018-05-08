#include "commthread.hpp"

CommThread::CommThread()
    :comm(NULL),bStop(false)
{
}
    
CommThread::~CommThread()
{
}

void CommThread::bind(Comm * comm)
{
    this->comm = comm;
}

void CommThread::clear()
{
    comm->send("bye");
}

void CommThread::start()
{
    bStop = false;
    QThread::start();
}

void CommThread::stop()
{
    if (isRunning())
    {
        bStop = true;
    }
}

void CommThread::run()
{
    string data;
    int ret;
    if (comm == NULL)
    {
        emit commNotBinded();
        return;
    }
    
    while(!bStop)
    {
        ret = comm->recv(data);//阻塞在这里的话线程还是无法推出
        if (COMM_SUC == ret)
        {
            emit dataRecved(QString::fromStdString(data));
        }
        //msleep(20);
    }
    return;
}


