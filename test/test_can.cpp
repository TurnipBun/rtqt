#include <iostream>
#include <gtest/gtest.h>

#include "log.hpp"

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