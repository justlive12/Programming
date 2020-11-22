#include "pch.h"
#include "json.hpp"
#include <iostream>
#include <fstream>

using json = nlohmann::json;
using namespace std;

int main()
{
	json in_file;
	json out_file;
	json temporary_storage;

	ifstream read("in.json");
	read >> in_file;
	for (const auto& data : in_file) {
		int valueUserId = data["userId"];
		temporary_storage["userId"] = valueUserId;
		bool valueCompleted = data["completed"];
		int number_of_completed_tasks = 0;

		if (valueCompleted == true) {
			number_of_completed_tasks += 1;
		}

		temporary_storage["task_completed"] = number_of_completed_tasks;

		out_file.push_back(temporary_storage);
	}
	ofstream add("out.json");
	add << out_file;
}
