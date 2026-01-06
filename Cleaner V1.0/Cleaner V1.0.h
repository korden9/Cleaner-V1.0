#pragma once

#include <nlohmann/json.hpp>
#include <iostream>
#include <Windows.h>
#include <fstream>
#include <thread>
#include <chrono>
#include <filesystem>
#include <string>


namespace fs = std::filesystem;
using json = nlohmann::json;
json json_t;
std::string pause_program;

class Program {

public:

	void virus_scan(unsigned short int);
	void scan_disc();
	void delete_all();
	void find_path();
	void add_to_size(const fs::directory_entry&, std::error_code&);
	void convert_to_gigabytes();
	std::uintmax_t calculate_folder_size(const fs::path&);
	bool check_clear_cache();
	bool check_scan_disc();
	bool check_virus_scan();
	unsigned short int check_virus_scan_level();
	int return_cache_size();
	double return_final_cache_size();
	std::string return_path();
	
private:

	std::string temp_path;
	int cache_size;
	double final_cache_size; // gigabity

};