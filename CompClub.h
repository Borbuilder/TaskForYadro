#pragma once
#include<iostream>
#include "Table.h"
#include "Client.h"
#include<vector>
#include<queue>

class CompClub
{
private:
	Time start_time;
	Time end_time;
	int revenue;
	int table_amount;
	std::vector<Table*> tables;
	std::vector<Client*> clients;
	std::queue<std::string> clients_queue;

public:

	CompClub(const Time& _stime, const Time& _etime, const int& _table_am, const int& _price);

	~CompClub();


	Time FindTime(const std::string& str);

	std::string FindName(const std::string& str);

	bool IsInClub(const std::string& cl_name);

	int FindClient(const std::string& cl_name);

	void GetTablesInfo();

	std::string TimeToString(const Time& time);

	Time GetEndTime();


	bool DealWith_ID1(const std::string& str);

	bool DealWith_ID2(const std::string& str);

	bool DealWith_ID3(const std::string& str);

	bool DealWith_ID4(const std::string& str);


	void generateID11(const int& gen_id, Time gen_time, const std::string& cl_name);

	void generateID12(Time gen_time, const int table_num);

	void generateID13(int const& mistake_id, const Time& _mistake_time);
};

