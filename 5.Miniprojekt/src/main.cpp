// Biblioteki
#include <iostream>
#include <sstream>
#include "ds.hpp"
#include "log.hpp"
#include "ui.hpp"

/**
 * @brief Punkt wejściowy do programu.
 * @return 0, jeśli program wykonał się poprawnie.
 */
int main() {
	mylog::SensorLogger::getSingleton().loadFromFile();
	std::string buffer;

	// Pętla programu
	while (true) {
		// Pobierz wybór użytkownika
		myui::AppMode user_input = myui::printMenu();

		// Dodaj nowego loga
		if (user_input == myui::AppMode::CREATE_LOG)
			myui::createLog();

		// Wyświetl logi
		else if (user_input == myui::AppMode::READ_LOGS)
			myui::readLogs();

		// Zapisz logi do pliku
		else if (user_input == myui::AppMode::SAVE_LOGS_TO_FILE) 
			myui::saveLogsToFile();

		// Przerwij program
		else
			break;

		// Poczekaj chwilę, aby kontynuować
		std::cin.ignore();
		std::cout << "Nacisnij, aby kontynuowac...";
		std::getline(std::cin, buffer);
		system("cls");
	}

	mylog::SensorLogger::getSingleton().saveToFile();
	
	return 0;
}
