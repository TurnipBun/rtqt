#ifndef _COMMTHREAD_HPP_
#define _COMMTHREAD_HPP_
#include <QThread>
#include "comm.hpp"
/**C O M M   T H R E A D***************************************************
 * Create: BY Huang Cheng(yelloworangecc@icloud.com) ON 201853
 * Description: 通信线程类，继承自QThread
 * Members: 
   - 
----------------------------C H A N G E   L O G----------------------------
 * 
**************************************************************************/
class CommThread : public QThread
{
    Q_OBJECT
public:
    CommThread();
    ~CommThread();

    void bind(Comm * comm);
    void start();
    void stop();
    void run();
    void recordTime(bool sw);
    double getMaxInterval();
    
signals:
    void dataRecved(double timestamp, const QString& data);
    void commNotBinded();

private:
    Comm *comm;
    bool bStop;
    bool bRecordTime;
    double maxIntervel;
    double lastTimestamp;
};


#endif

