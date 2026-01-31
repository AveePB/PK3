// Biblioteki
#include <iostream>
#include <sstream>
#include "log.hpp"
#include "ui.hpp"

/**
 * @brief Wypisuje do konsoli główne opcje i odpowiadające wybory. Oczekuje na informację zwrotną od użytkownika.
 */
myui::AppMode myui::printMenu() {
	// Stwórz zmienne
	bool is_valid = false;
	myui::AppMode user_input;
	std::string input_str;
	int input_int;

	// Czekaj, aż zostanie podana prawidłowa wartość
	while (!is_valid) {
		// Wyświetl opcje
		std::cout << "===================================\n";
		std::cout << "1. Stworz nowego loga\n";
		std::cout << "2. Wyswietl przetrzymywane logi\n";
		std::cout << "3. Zapisz logi do pliku\n";
		std::cout << "4. Zakoncz program\n";
		std::cout << "===================================\n";
		std::cout << "Podaj wybor: ";

		// Wczytaj wiadomość
		try {
			std::cin >> input_str;
			input_int = std::stoi(input_str);
			if (input_int < 1 || input_int > 4) throw std::out_of_range("User has chosen invalid option");

			user_input = myui::AppMode(input_int);
			is_valid = true;
		}

		// Dane wejściowe są nieprawidłowe
		catch (...) {
			is_valid = false;
			std::cout << "Twoja podana odpowiedz jest niepoprawna!\n";
			std::cin.ignore();
			std::getline(std::cin, input_str);
			system("cls");
		}
	}
	
	return user_input;
}


/**
 * @brief Tworzy nowego loga i dodaje go do struktury.
 */
void myui::createLog() {
	// Stwórz zmienne
	bool is_valid = false;
	std::string log_type_str;
	std::string msg;
	std::string read_value_str;
	std::string sensor_id_str;
	std::string input_str;

	int log_type_int;
	double read_value;
	int sensor_id;

	mylog::LogType log_type;

	// Czekaj, aż zostanie podana prawidłowa wartość
	while (!is_valid) {
		// Wyświetl nagłówek
		std::cout << "\n===================================\n";
		std::cout << "       TWORZENIE NOWEGO LOGA \n";
		std::cout << "===================================\n";

		// Wczytaj wiadomość
		try {
			std::cout << "Wybierz rodzaj loga (1-Info, 2-Debug, 3-Warning): ";
			std::cin >> log_type_str;

			std::cout << "Podaj wiadomosc loga: ";
			std::cin.ignore();
			std::getline(std::cin, msg);

			std::cout << "Podaj odczytana wartosc z czujnika: ";
			std::cin >> read_value_str;

			std::cout << "Podaj identyfikator czujnika: ";
			std::cin >> sensor_id_str;

			// Przekonwertuj typ loga
			log_type_int = std::stoi(log_type_str);
			if (log_type_int < 1 || log_type_int > 3) throw std::out_of_range("User has chosen invalid log type");
			log_type = mylog::LogType(log_type_int);

			// Sprawdź czy wiadomość zawiera separator |
			for (char c : msg)
				if (c == '|')
					throw std::invalid_argument("Given separator as element of message");

			// Przekonwertuj tekst na liczby
			read_value = std::stof(read_value_str);
			sensor_id = std::stoi(sensor_id_str);
			
			is_valid = true;
		}

		// Dane wejściowe są nieprawidłowe
		catch (...) {
			is_valid = false;
			std::cout << "Podane dane sa nie prawidlowe!\n";
			std::cin.ignore();
			std::getline(std::cin, input_str);
			system("cls");
		}
	}

	// Stwórz nowego loga
	mylog::SensorLogger::getSingleton().createLog(mylog::LogEntry(sensor_id, msg, read_value, log_type));
	std::cout << "Stworzono nowego loga\n";
}

/**
 * @brief Wyświetl przechowywane logi do konsoli.
 */
void myui::readLogs() {
	// Stwórz zmienne
	bool is_valid = false;
	myui::ReadMode user_input;
	std::string input_str;
	int input_int;

	// Czekaj, aż zostanie podana prawidłowa wartość
	while (!is_valid) {
		// Wyświetl opcje
		std::cout << "\n===================================\n";
		std::cout << "          WYSWIETLANIE LOGOW   \n";
		std::cout << "===================================\n";
		std::cout << "1. Wszystkie typy\n";
		std::cout << "2. Tylko info\n";
		std::cout << "3. Tylko debug\n";
		std::cout << "4. Tylko warn\n";
		std::cout << "===================================\n";
		std::cout << "Podaj wybor: ";

		// Wczytaj wiadomość
		try {
			std::cin >> input_str;
			input_int = std::stoi(input_str);
			if (input_int < 1 || input_int > 4) throw std::out_of_range("User has chosen invalid option");

			user_input = myui::ReadMode(input_int);
			is_valid = true;
		}

		// Dane wejściowe są nieprawidłowe
		catch (...) {
			is_valid = false;
			std::cout << "Twoja podana odpowiedz jest niepoprawna!\n";
			std::cin.ignore();
			std::getline(std::cin, input_str);
			system("cls");
		}
	}

	// Wypisz logi do konsoli
	myds::CustomVector<mylog::LogEntry> filtered_logs;

	// Zdobądź wszystkie logi
	if (user_input == myui::ALL_LOGS)
		filtered_logs = mylog::SensorLogger::getSingleton().filter(
			[](mylog::LogEntry& log) {
				return true;
			}
		);

	// Zdobądź tylko info
	else if (user_input == myui::ONLY_INFO)
		filtered_logs = mylog::SensorLogger::getSingleton().filter(
			[](mylog::LogEntry& log) {
				return log.log_type == mylog::LogType::info;
			}
		);

	// Zdobądź tylko debug
	else if (user_input == myui::ONLY_DEBUG)
		filtered_logs = mylog::SensorLogger::getSingleton().filter(
			[](mylog::LogEntry& log) {
				return log.log_type == mylog::LogType::debug;
			}
		);

	// Zdobądź tylko warning
	else if (user_input == myui::ONLY_WARN)
		filtered_logs = mylog::SensorLogger::getSingleton().filter(
			[](mylog::LogEntry& log) {
				return log.log_type == mylog::LogType::warning;
			}
		);

	std::cout << "Liczba logow " << filtered_logs.size() << '\n';
	std::cout << "Format loga: DATA|TYP_LOGA|WIADOMOSC|ODCZYTANA_WARTOSC|IDENTYFIKATOR_CZUJNIKA\n";

	// Wyświetl
	for (auto l : filtered_logs) std::cout << l.toString() << '\n';
}

/**
 * @brief Zapisuje informacje do pewnego pliku tekstowego z rozszerzeniem log.
 */
void myui::saveLogsToFile() {
	mylog::SensorLogger::getSingleton().saveToFile();
	std::cout << "Zapisano dane do pliku tekstowego\n";
}
