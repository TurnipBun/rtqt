#include "commthread.hpp"
#include "os.hpp"

CommThread::CommThread()
    :comm(NULL),bStop(false),bRecordTime(false)
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
    double timestamp = 0.0;
    double interval = 0.0;
    
    if (comm == NULL)
    {
        emit commNotBinded();
        return;
    }
    
    while(!bStop)
    {
        ret = comm->recv(data);
        if (COMM_SUC == ret)
        {
            timestamp = OS::getTimestamp();
            if (bRecordTime == true)
            {
                if (lastTimestamp != 0.0)
                {
                    interval = timestamp - lastTimestamp;
                    if (interval > maxIntervel) maxIntervel = interval;
                }
                lastTimestamp = timestamp;
            }
            emit dataRecved(timestamp,QString::fromStdString(data));
        }
    }
    return;
}

void CommThread::recordTime(bool switchFlag)
{
    bRecordTime = switchFlag;
    lastTimestamp = 0.0;
    maxIntervel = 0.0;
}

double CommThread::getMaxInterval()
{
    return maxIntervel;
}


