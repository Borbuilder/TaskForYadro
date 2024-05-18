#include <iostream>
#include <fstream>
#include <regex>
#include <vector>
#include <string>
#include"CompClub.h"


bool RightLine(const std::string& str, const int& str_number, int& table_count)
{

    if (str_number == 1 && str[0] != '0' && std::regex_match(str, std::regex("([0-9]+)$"))) {
        table_count = str[0] - '0';
        return true;
    }

    if (str_number == 2 && (
        std::regex_match(str, std::regex("([0-1][0-9])(:)([0-5][0-9]) ([0-1][0-9])(:)([0-5][0-9])$")) ||
        std::regex_match(str, std::regex("([0-1][0-9])(:)([0-5][0-9]) ((2)[0-3])(:)([0-5][0-9])$")) ||
        std::regex_match(str, std::regex("((2)[0-3])(:)([0-5][0-9]) ((2)[0-3])(:)([0-5][0-9])$")) ||
        std::regex_match(str, std::regex("([0-1][0-9])(:)([0-5][0-9]) ((00)(:)(00))$")) ||
        std::regex_match(str, std::regex("((2)[0-3])(:)([0-5][0-9]) ((00)(:)(00))$"))
        ))
    {
        if (std::regex_match(str, std::regex("([0-1][0-9])(:)([0-5][0-9]) ((00)(:)(00))$")) || std::regex_match(str, std::regex("((2)[0-3])(:)([0-5][0-9]) ((00)(:)(00))$"))) {
            return true;
        }

        std::string start_str = str.substr(0, 5);
        Time start_time(start_str);
        std::string end_str = str.substr(6);
        Time end_time(end_str);

        return(start_time < end_time);
    }

    if (str_number == 3 && str[0] != '0' && std::regex_match(str, std::regex("([0-9]+)$"))) {
        return true;
    }


    std::string p_time = "00:00";
    Time previous_time(p_time);
    if (str_number > 3 && std::regex_match(str, std::regex("((([0-1][0-9])(:)([0-5][0-9]))|(((2)[0-3])(:)([0-5][0-9]))|((00)(:)(00))) ([1-4]) ([a-z0-9-_]+)$"))) {
        std::string in_time = str.substr(0, 5);
        Time input_time(in_time);

        return (input_time > previous_time);
    }
    if (str_number > 3 && std::regex_match(str, std::regex("((([0-1][0-9])(:)([0-5][0-9]))|(((2)[0-3])(:)([0-5][0-9]))|((00)(:)(00))) ([1-4]) ([a-z0-9-_]+) ([1-9]+)$"))) {
        int space_pos = str.find_last_of(' ');
        std::string in_table = str.substr(space_pos + 1);
        int in_table_num = atoi(in_table.c_str());

        std::string in_time = str.substr(0, 5);
        Time input_time(in_time);

        return (in_table_num <= table_count && input_time > previous_time);
    }

    return  false;
}

int FindID(const std::string& str) {
    int first_space_pos = str.find_first_of(' ');
    std::string in_id = str.substr(first_space_pos + 1);
    int _id = atoi(in_id.c_str());
    return _id;
}

bool RightNumberOfTables(const std::vector<std::string>& _lines_vector, int* mistake_pos){
    int table_num = atoi(_lines_vector.front().c_str());

    for (int i = 3; i < _lines_vector.size(); i++) {
        if (_lines_vector[i].length() > 15) {
            int last_space_pos = _lines_vector[i].find_last_of(' ');
            int cur_table_num = atoi((_lines_vector[i].substr(last_space_pos + 1).c_str()));

            if (cur_table_num > table_num) {
                *mistake_pos = i;
                return false;
            }
        }
    }
    return true;
}


int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cout << "Using: ./task <file_name>" << std::endl;
        return 1;
    }
    std::ifstream file(argv[1]); // Open file
    std::vector<std::string> lines_vector;

    std::string wrong_line;
    int line_number = 0;
    int table_count = 0;
    int break_flag = 0;
    int id;

    if (file.is_open()) {
        std::string line;

        while (std::getline(file, line)) { // Read file
            line_number++;
            if (RightLine(line, line_number, table_count))
            {
                lines_vector.push_back(line);
            }
            else {
                wrong_line = line;
                break_flag = 1;
                break;
            }
        }
        file.close(); // Close file

        int table_mistake_pos;
        if (!RightNumberOfTables(lines_vector, &table_mistake_pos)) {
            wrong_line = lines_vector[table_mistake_pos];
            break_flag = 1;
        }
       
        if (break_flag == 1) {
            std::cout << wrong_line << std::endl;
            return 1;
        }


        //Main work
        std::string start = lines_vector[1].substr(0, 5);
        Time start_time(start);
        std::string end = lines_vector[1].substr(6);
        if (end == "00:00") {
            end = "24:00";
        }
        Time end_time(end);

        CompClub club(start_time, end_time, atoi(lines_vector[0].c_str()), atoi(lines_vector[2].c_str()));

        std::cout << start << std::endl;
        int last_event_pos;
        for (int i = 3; i < lines_vector.size(); i++) {
            id = FindID(lines_vector[i]);

            Time current_time = club.FindTime(lines_vector[i]);
            if (current_time < end_time)
            {
                if (id == 1) {
                    club.DealWith_ID1(lines_vector[i]);
                }
                if (id == 2) {
                    club.DealWith_ID2(lines_vector[i]);
                }
                if (id == 3) {
                    club.DealWith_ID3(lines_vector[i]);
                }
                if (id == 4) {
                    club.DealWith_ID4(lines_vector[i]);
                }
                last_event_pos = i;
            }
        }
        club.generateID11(2, end_time, "noname");
        std::cout << end << std::endl;
        if (last_event_pos != lines_vector.size() - 1) {
            for (int i = last_event_pos + 1; i < lines_vector.size(); i++) {
                club.DealWith_ID1(lines_vector[i]);
            }
        }
        club.GetTablesInfo();
    }
    else {
        std::cout << "Error opening the file" << std::endl;
        return 1;
    }

    return 0;
}
