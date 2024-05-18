#include "Table.h"

Table::Table(const int& _tnum, const int& _tprice)
{
	is_occupied = false;
	table_num = _tnum;
	table_revenue = 0;
	price = _tprice;
	all_hours = 0;
	all_mins = 0;
	std::string str = "00:00";
	whole_time = str;
}

Table::Table(const Table& other)
{
	is_occupied = other.is_occupied;
	table_num = other.table_num;
	price = other.price;
	table_revenue = other.table_revenue;
	all_hours = other.all_hours;
	all_mins = other.all_mins;
	whole_time = other.whole_time;
}

int Table::GetTableNum()
{
	return table_num;
}

int Table::GetTableRevenue()
{
	return table_revenue;
}

std::string Table::GetTableWholeTime()
{
	all_hours += (all_mins / 60);
	std::string hours;
	std::string mins;

	if (all_hours < 10) {
		hours = "0" + std::to_string(all_hours);
	}
	else {
		hours = std::to_string(all_hours);
	}

	std::string mis_min;
	if ((all_mins % 60) < 10) {
		mins = "0" + std::to_string((all_mins % 60));
	}
	else {
		mins = std::to_string((all_mins % 60));
	}
	return hours + ":" + mins;
}

bool Table::IsOccupied()
{
	return is_occupied;
}

void Table::TableIsTaken(const Time& _get_time)
{
	is_occupied = true;
	get_time = _get_time;
}

void Table::TableIsAbandoned(const Time& _leave_time)
{
	is_occupied = false;
	leave_time = _leave_time;
	table_revenue += (leave_time - get_time) * price;


	int hour_diff = this->leave_time.hour - get_time.hour;
	int min_diff = this->leave_time.min - get_time.min;
	if (min_diff < 0 && hour_diff>0) {
		all_hours += (hour_diff - 1);
		all_mins += (leave_time.min + (60 - get_time.min));
	}
	if (min_diff > 0 && hour_diff == 0) {
		all_hours += 0;
		all_mins += (leave_time.min - get_time.min);
	}
	if (min_diff > 0 && hour_diff > 0) {
		all_hours += hour_diff;
		all_mins += (leave_time.min - get_time.min);
	}
}



