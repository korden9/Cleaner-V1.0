#include "Cleaner V1.0.h"



Program Funkcje;


int main() 
{
	std::ifstream config("config.json");
	config >> json_t;
	std::cout << "Usuniecie cache: " << Funkcje.check_clear_cache() << "\n";
	std::cout << "Skan dysku: " << Funkcje.check_scan_disc() << "\n";
	
	if (Funkcje.check_virus_scan()) {
		std::cout << "Skan wirusowy: " << Funkcje.check_virus_scan() << "\n";
		std::cout << "Poziom skanu wirusowego: " << Funkcje.check_virus_scan_level() << "\n";
	}
	
	std::this_thread::sleep_for(std::chrono::seconds(3));
	
	std::cout << "Rozpoczynanie...\n";
	
	
	std::this_thread::sleep_for(std::chrono::seconds(3));
	system("cls");

	for (short int time = 5; time >= 0; --time) {
		std::cout << time;
		std::this_thread::sleep_for(std::chrono::seconds(1));
		system("cls");
	}

	std::cout << "\n";

	if (Funkcje.check_clear_cache()) {

		system("cls");

		double cache1 = 0, cache2 = 0, roznica = 0;
		std::error_code error;
		Funkcje.find_path();
		Funkcje.calculate_folder_size(Funkcje.return_path());

		std::cout << "Temp to: " << Funkcje.return_path() << "\n";

		cache1 = static_cast<double>(Funkcje.calculate_folder_size(Funkcje.return_path())) / 1024.00 / 1024.00 / 1024.00;

		Funkcje.delete_all();

		cache2 = static_cast<double>(Funkcje.calculate_folder_size(Funkcje.return_path())) / 1024.00 / 1024.00 / 1024.00;

		roznica = cache1 - cache2;
		std::cout << "Usunieto : " << roznica << "GB \n";
		std::this_thread::sleep_for(std::chrono::seconds(5));
		MessageBoxA(NULL, "Pomyslnie usunieto cache!. ", "Informacja", MB_OK);
	}
	
	if (Funkcje.check_virus_scan()) {
		system("cls");
		std::cout << "Rozpoczynanie skanowania typu: " << Funkcje.check_virus_scan_level() << "\n";
		Funkcje.virus_scan(Funkcje.check_virus_scan_level());
		MessageBoxA(NULL, "Moze to chwile potrwac...", "Informacja", MB_OK);
	}

	if (Funkcje.check_scan_disc()) {
		system("cls");
		Funkcje.scan_disc();
		MessageBoxA(NULL, "Rozpoczeto skanowanie, prosze czekac.", "Informacja", MB_OK);
	}
	system("cls");
	
	std::cin >> pause_program;

	return 0;
}

void Program::virus_scan(unsigned short int rodzaj) {
	char lokalizacja[MAX_PATH];
	GetEnvironmentVariableA("ProgramFiles", lokalizacja, MAX_PATH);
	std::string Komenda = "";


	if (rodzaj != 1 && rodzaj != 2) {
		MessageBoxA(NULL, "Niepoprawny rodzaj skanu.", "Informacja", MB_OK);
	}
	else {
		Komenda = "\"" + (std::string)lokalizacja +	"\\Windows Defender\\MpCmdRun.exe\" -Scan -ScanType " + std::to_string(rodzaj);
		system(Komenda.c_str());
	}
}

unsigned short int Program::check_virus_scan_level() {
	return json_t["virus_scan_level"].get<int>();
}

bool Program::check_virus_scan() {
	return json_t["virus_scan"].get<bool>();
}

std::string Program::return_path() {
	return Program::temp_path;
}

void Program::delete_all() {
	fs::path folder = Program::temp_path;
	std::error_code error;

	std::vector<fs::directory_entry> files;
	for (const auto& file : fs::directory_iterator(folder, error)) {
		if (!error) {
			files.push_back(file);   
		}
		else {
			error.clear();
		}
	}


	for (const auto& file : files) {
	
		Funkcje.add_to_size(file, error);

	
		fs::remove_all(file.path(), error);
		if (error) {
			error.clear();  
		}
	}
}



void Program::convert_to_gigabytes() {
	Program::final_cache_size = static_cast<double>(Program::cache_size) / 1024.00 / 1024.00 / 1024.00;
}

void Program::scan_disc() {
	system("chkdsk");
}

void Program::find_path() {
	char temp[MAX_PATH];
	GetEnvironmentVariableA("TEMP", temp, MAX_PATH);
	Program::temp_path = temp;

}

bool Program::check_scan_disc() {
	return json_t["check_disc"].get<bool>();
}

bool Program::check_clear_cache() {
	return json_t["clear_cache"].get<bool>();
}

int Program::return_cache_size() {
	return Program::cache_size;
}

std::uintmax_t Program::calculate_folder_size(const fs::path& path) {
	
	std::uintmax_t size = 0;

	for (const auto& file : fs::recursive_directory_iterator(path)) {
		std::error_code error;
		
		if (fs::is_regular_file(file, error)) {
			size += fs::file_size(file, error);
		}	
		
	}
	return size;
}

double Program::return_final_cache_size() {
	return Program::final_cache_size;
}

void Program::add_to_size(const fs::directory_entry& path, std::error_code& error) {
	if (fs::is_regular_file(path, error)) {
		Program::cache_size += fs::file_size(path, error);
	}
}