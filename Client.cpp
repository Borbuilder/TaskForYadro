#include "Client.h"

Client::Client(std::string& _name, Time ar_time)
{
    arrive_time = ar_time;
    std::string default_time = "00:00";
    out_time = default_time;
    at_table_time = default_time;
    name = _name;
    table_num = -1;
}

std::string Client::getname()
{
    return name;
}

int Client::gettablenum()
{
    return table_num;
}

void Client::GetTable(const int& _table_num)
{
    table_num = _table_num;
}

void Client::LeaveTable()
{
    table_num = -1;
}
