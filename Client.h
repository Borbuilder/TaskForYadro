//#pragma once
#include"Functions.h"
class Client
{
private:

    Time arrive_time;
    Time out_time;
    Time at_table_time;
    std::string name;
    int table_num;

public:

    Client(std::string& _name, Time ar_time);
    std::string getname();
    int gettablenum();

    void GetTable(const int& _table_num);
    void LeaveTable();
};

