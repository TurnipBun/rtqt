#ifndef _SOCKWIDGET_HPP_
#define _SOCKWIDGET_HPP_
#include <QtGui>
#include "modulewidget.hpp"

#include "sock.hpp"
#define DEF_SOCK Sock


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
    Q_OBJECT
public:
    QHBoxLayout *hLayoutUp;
    QLabel *labelServerIp;
    QLabel *labelServerPort;
    QComboBox *comboServerIp;
    QLineEdit *lineServerPort;
   
    QHBoxLayout *hLayoutMid;
    QLabel *labelClientIp;
    QLabel *labelClientPort;
    QComboBox *comboClientIp;
    QLineEdit *lineClientPort;

    
    QHBoxLayout *hLayoutDown;
    QLabel *labelProtocol;
    QComboBox *comboProtocol;

    QVBoxLayout *vLayout;

    SockWidget();
    ~SockWidget();
    
public slots:
    void on_pushOpen_clicked();
    void on_pushClose_clicked();

private:
    
    void addSettings();
    void fillCombos();
    int initSockLib();
    void releaseSockLib();
    int initComms(const string& serverIp, unsigned int serverPort,
                     const string& clientIp, unsigned int clientPort);
};

#endif

