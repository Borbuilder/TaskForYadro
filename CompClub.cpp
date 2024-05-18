#include "CompClub.h"
#include<iostream>
#include "CompClub.h"
#include"Functions.h"
#include <algorithm>


CompClub::CompClub(const Time& _stime, const Time& _etime, const int& _table_am, const int& _price)
{
	start_time = _stime;
	end_time = _etime;
	revenue = 0;
	table_amount = _table_am;
	for (int i = 1; i <= _table_am; i++) {
		Table* new_table = new Table(i, _price);
		tables.push_back(new_table);
	}
}

CompClub::~CompClub()
{
	for (Table* table_obj : tables) {
		delete table_obj;
	}
	for (Client* client_obj : clients) {
		delete client_obj;
	}
}

Time CompClub::FindTime(const std::string& str)
{
	int first_space_pos = str.find_first_of(' ');
	std::string in_time = str.substr(0, first_space_pos);
	Time time(in_time);
	return time;
}

std::string CompClub::FindName(const std::string& str)
{
	int first_space_pos = str.find_first_of(' ');
	std::string tmp = str.substr(first_space_pos + 3);
	int last_space_pos = tmp.find(' ');

	if (last_space_pos == std::string::npos) {
		return tmp;
	}
	else {
		std::string new_tmp = tmp.substr(0, last_space_pos);
		return new_tmp;
	}
}

bool CompClub::IsInClub(const std::string& cl_name)
{
	for (int i = 0; i < clients.size(); i++) {
		if (cl_name == clients[i]->getname()) {
			return true;
		}
	}
	return false;
}

int CompClub::FindClient(const std::string& cl_name)
{
	int index;
	for (int i = 0; i < clients.size(); i++) {
		if (clients[i]->getname() == cl_name) {
		    index = i;
		}
	}
	return index;
}

void CompClub::GetTablesInfo()
{

	for (int i = 0; i < tables.size(); i++) {
		std::cout << i + 1 << " " << tables[i]->GetTableRevenue() <<" "<<tables[i]->GetTableWholeTime() << std::endl;
	}
}

Time CompClub::GetEndTime()
{
	return end_time;
}

std::string CompClub::TimeToString(const Time& time)
{
	std::string mis_hour;
	if (time.hour < 10) {
		mis_hour = "0" + std::to_string(time.hour);
	}
	else {
		mis_hour = std::to_string(time.hour);
	}

	std::string mis_min;
	if (time.min < 10) {
		mis_min = "0" + std::to_string(time.min);
	}
	else {
		mis_min = std::to_string(time.min);
	}

	std::string mis_time = mis_hour + ":" + mis_min;
	return mis_time;
}

bool CompClub::DealWith_ID1(const std::string& str)
{
	std::cout << str << std::endl;

	Time str_time = FindTime(str);
	std::string in_name = FindName(str);

	if (str_time < start_time || str_time>end_time) {
		generateID13(1, str_time);
		return false;
	}

	if (IsInClub(in_name)) {
		generateID13(2, str_time);
		return false;
	}


	Client* new_client = new Client(in_name, str_time);
	clients.push_back(new_client);

	return true;
}

bool CompClub::DealWith_ID2(const std::string& str)
{
	std::cout << str << std::endl;

	Time str_time = FindTime(str);
	std::string in_name = FindName(str);
	int last_space_pos = str.find_last_of(' ');
	int table_num = atoi((str.substr(last_space_pos + 1)).c_str());

	if (!IsInClub(in_name)) {
		generateID13(4, str_time);
		return false;
	}

	if (tables[table_num - 1]->IsOccupied()) {
		generateID13(3, str_time);
		clients_queue.push(in_name);
		int index = -1;
		for (int i = 0; i < tables.size(); i++) {
			if (!tables[i]->IsOccupied()) {
				index = i;
				break;
			}
		}
		if (index != -1) {
			generateID12(str_time, index+1);
		}

		return false;
	}
	else {
		int tmp = FindClient(in_name);
		int i = clients[tmp]->gettablenum();
		if (i != -1) {
			tables[i - 1]->TableIsAbandoned(str_time);
			clients[tmp]->LeaveTable();
		}

		tables[table_num - 1]->TableIsTaken(str_time);
		clients[tmp]->GetTable(table_num);
	}
	return true;
}

bool CompClub::DealWith_ID3(const std::string& str)
{
	std::cout << str << std::endl;

	Time str_time = FindTime(str);
	std::string in_name = FindName(str);

	for (int i = 0; i < tables.size(); i++) {
		if (!tables[i]->IsOccupied()) {
			generateID13(5, str_time);
			return false;
		}
	}

	if (clients_queue.size() == table_amount) {
		generateID11(1, str_time, in_name);
		return false;
	}

	std::queue<std::string> copy;
	copy = clients_queue;

	bool in_queue=false;
	while (!copy.empty()) {
		if (copy.front() == in_name) {
			in_queue = true;
			break;
		}
		copy.pop();
	}
	if (!in_queue) {
		clients_queue.push(in_name);
	}
	return true;
}

bool CompClub::DealWith_ID4(const std::string& str)
{
	std::cout << str << std::endl;

	Time str_time = FindTime(str);
	std::string in_name = FindName(str);

	if (!IsInClub(in_name)) {
		generateID13(4, str_time);
		return false;
	}

	int tmp = FindClient(in_name);
	int i = clients[tmp]->gettablenum();
	if (i != -1) {
		tables[i - 1]->TableIsAbandoned(str_time);
		clients[tmp]->LeaveTable();
	}

	for (auto it = clients.begin(); it != clients.end(); ++it) {
		if ((*it)->getname() == in_name) {
			delete* it;
			clients.erase(it);
			break;
		}
	}

	generateID12(str_time, i);
	return true;
}

void CompClub::generateID11(const int& gen_id, Time gen_time, const std::string& cl_name)
{
	std::string out_of_club_time = TimeToString(gen_time);

	if (gen_id == 1) {
		std::cout << out_of_club_time << " 11 " << cl_name;
		for (auto it = clients.begin(); it != clients.end(); ++it) {
			if ((*it)->getname() == cl_name) {
				delete* it;
				clients.erase(it);
				break;
			}
		}
	}

	if (gen_id == 2) {
		std::vector<std::string> names;

		for (int i = 0; i < clients.size(); i++) {
			names.push_back(clients[i]->getname());

			int tmp = clients[i]->gettablenum();
			if (tmp != -1) {
				tables[tmp - 1]->TableIsAbandoned(out_of_club_time);
				clients[i]->LeaveTable();
			}
		}

		sort(names.begin(), names.end());
		for (int i = 0; i < names.size(); i++) {
			std::cout << out_of_club_time << " 11 " << names[i]<<std::endl;
		}
	}
}

void CompClub::generateID12(Time gen_time, const int table_num)
{
	if (!clients_queue.empty()) {
		std::string waiting_name = clients_queue.front();
		clients_queue.pop();

		tables[table_num - 1]->TableIsTaken(gen_time);
		clients[FindClient(waiting_name)]->GetTable(table_num);

		std::string str_time = TimeToString(gen_time);
		std::cout << str_time << " 12 " << waiting_name << " " << table_num << std::endl;
	}
}

void CompClub::generateID13(int const& mistake_id, const Time& _mistake_time)
{
	std::string mis_time = TimeToString(_mistake_time);
	if (mistake_id == 1) std::cout << mis_time << " 13 NotOpenYet" << std::endl;
	if (mistake_id == 2) std::cout << mis_time << " 13 YouShallNotPass" << std::endl;
	if (mistake_id == 3) std::cout << mis_time << " 13 PlaceIsBusy" << std::endl;
	if (mistake_id == 4) std::cout << mis_time << " 13 ClientUnknown" << std::endl;
	if (mistake_id == 5) std::cout << mis_time << " 13 ICanWaitNoLonger!" << std::endl;
}
