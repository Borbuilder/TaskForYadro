//#pragma once
#include"Functions.h"

class Table
{
private:
	bool is_occupied;
	int table_num;
	int table_revenue;
	int price;
	Time get_time;
	Time leave_time;
	std::string whole_time;
	int all_hours;
	int all_mins;
public:
	Table(const int& _tnum, const int& _tprice);
	Table(const Table& other);

	int GetTableNum();
	int GetTableRevenue();
	std::string GetTableWholeTime();
	bool IsOccupied();
	void TableIsTaken(const Time& _get_time);
	void TableIsAbandoned(const Time& _leave_time);
};

