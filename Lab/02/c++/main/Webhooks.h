#pragma once

#include <iostream>
#include <string>
#include <cpp_httplib/httplib.h>
#include <nlohmann/json.hpp>
#include <vector>

using namespace httplib;
using json = nlohmann::json;
std::vector<std::string> cache;
std::vector<std::string> webhooks;


void findAndRepl(std::string& data, std::string toSearch, std::string replStr) {
	size_t pos = data.find(toSearch);
	while (pos != std::string::npos) {
		data.replace(pos, toSearch.size(), replStr);
		pos = data.find(toSearch, pos + replStr.size());
	}
}

void update_conf(std::string param, std::string val) {
	std::string webhooks_file_name = "webhooks.json";
	std::ifstream webhooks_file(webhooks_file_name);
	json j;

	if (webhooks_file.is_open())
	{
		webhooks_file >> j;
		webhooks_file.close();

		if (param == "del") {
			cache.erase(std::remove(cache.begin(), cache.end(), val), cache.end());
		}
		else if (param == "set") {
			cache.push_back(val);
		}
		json j2;
		j2["webhooks"] = cache;
		std::ofstream conf_file(webhooks_file_name);
		conf_file << j2;
		conf_file.close();
	}
	else
	{
		std::cout << "Error open file";
	}
}

void check_conf() {
	std::string webhooks_file_name = "webhooks.json";
	std::ifstream webhooks_file(webhooks_file_name);
	std::cout << "Попытка открыть файл...\n";
	if (webhooks_file.is_open())
	{
		int i = 0;
		std::cout << "Открыл!\n";
		json j = json::parse(webhooks_file);

		for (int i = 0; i < j["webhooks"].size(); i++) {
			cache.push_back(j["webhooks"][i]);
		}
	}
	else
	{
		std::cout << "Не получилось, создаю новый...\n";
		std::ofstream webhooks_file(webhooks_file_name);
		std::string config = R"(
			{
			"webhooks":[]
			})";
		webhooks_file << config;
		webhooks_file.close();
		cache.clear();
	}
}