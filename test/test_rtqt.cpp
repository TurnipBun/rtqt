#include <iostream>
#include <gtest/gtest.h>

#include "log.hpp"
#include "wincom.hpp"

using std::cout;
using std::endl;

Log *g_pLog = NULL;

TEST(FileLogTest, AddLog)
{
    string text("hello");
    string exp = text;
    LogFactory *pLogFactory = LogFactory::getFactory();
    g_pLog = pLogFactory->createLog(TO_FILE);
    ASSERT_EQ(LOG_SUC, g_pLog->init());
    cout << "init ok ..." << endl;
    g_pLog->add(text);
    cout << "add log:" << text << endl;
    string got = g_pLog->get();
    cout << "got log:" << got << endl;
    ASSERT_STREQ(exp.c_str(), got.c_str());
}

TEST(FileLogTest, AddLogAgain)
{
    const char *pText = " world";
    string exp("hello world");
    g_pLog->add(pText);
    cout << "add log:" << pText << endl;
    string got = g_pLog->get();
    cout << "got log:" << got << endl;
    ASSERT_STREQ(exp.c_str(), got.c_str());
}

TEST(FileLogTest, OperatorAdd)
{
    const char *pText1 = " huang";
    string text2(" cheng ");
    int year = 1990;
    string exp("hello world huang cheng 19900xff\n\r");
    (*g_pLog) << pText1 << text2 << year << char(0xff) << ENDL;
    cout << "add log ..." << endl;
    string got = g_pLog->get();
    cout << "got log:" << got << endl;
    ASSERT_STREQ(exp.c_str(), got.c_str());
    delete g_pLog;
}

TEST(SerialPort, CommonTest)
{
    COM *com1 = new WinCom("COM1","9600","8","One","None");
    COM *com2 = new WinCom("COM2","9600","8","One","None");
    com1->init();
    com2->init();
    string data("hello");
    
    com1->send(data.c_str(),data.length());
    com2->recv();

    delete com1;
    delete com2;
}

TEST(SerialPort, GetComListTest)
{
    GetWinComList getList;
    const list<string> & comList = getList();
    const string & com1Name = comList.front();
    const string & com2Name = comList.back();
    ASSERT_EQ(2,comList.size());
    ASSERT_STREQ("COM1",com1Name.c_str());
    ASSERT_STREQ("COM2",com2Name.c_str());
}