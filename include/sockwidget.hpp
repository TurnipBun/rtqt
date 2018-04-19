#ifndef _SOCKWIDGET_HPP_
#define _SOCKWIDGET_HPP_
#include <QtGui>
#include "modulewidget.hpp"

#ifdef VXWORKS
#include "vxsock.hpp"
#define DEF_SOCK VxSock
#else
#include "winsock.hpp"
#define DEF_SOCK WinSock
#endif


/**S O C K   W I D G E T***************************************************
 * Create: BY Huang Cheng(yelloworangecc@icloud.com) ON 2018418
 * Description: 网络通信测试的UI界面
 * Members: 
   - 
----------------------------C H A N G E   L O G----------------------------
 * 
**************************************************************************/
class SockWidget : public ModuleWidget
{
public:
    QHBoxLayout *hLayoutUp;
    QLabel *labelServerIp;
    QLabel *labelServerPort;
    QComboBox *comboServerIp;
    QLineEdit *lineServerPort;
    
    QHBoxLayout *hLayoutDown;
    QLabel *labelClientIp;
    QLabel *labelClientPort;
    QComboBox *comboClientIp;
    QLineEdit *lineClientPort;

    QVBoxLayout *vLayout;

    SockWidget();
    ~SockWidget();
    
public slots:
    void onPushOpenClicked();

private:
    void addSettings();
    void fillCombos();
    void connectSignalToSlot();
    int initComms(const string& serverIp, unsigned int serverPort,
                     const string& clientIp, unsigned int clientPort);
};

#endif

