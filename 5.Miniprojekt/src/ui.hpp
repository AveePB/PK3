#ifndef UI_HPP
#define UI_HPP

// Biblioteki
#include <iostream>

/**
 * @brief Przestrzeń nazw przechowywująca funkcje tworzące interfejs użytkownika.
 */
namespace myui {

	/**
	 * @brief Przechowuje możliwe operacje, jakie może wykonać aplikacja.
	 */
	enum AppMode { CREATE_LOG = 1, READ_LOGS = 2, SAVE_LOGS_TO_FILE = 3, QUIT_APP = 4 };

	/**
	 * @brief Przechowuje możliwe tryby wyświetlania logów.
	 */
	enum ReadMode { ALL_LOGS = 1, ONLY_INFO = 2, ONLY_DEBUG = 3, ONLY_WARN = 4 };

	/**
	 * @brief Wypisuje do konsoli główne opcje i odpowiadające wybory. Oczekuje na informację zwrotną od użytkownika.
	 */
	AppMode printMenu();

	/**
	 * @brief Tworzy nowego loga i dodaje go do struktury.
	 */
	void createLog();

	/**
	 * @brief Wyświetl przechowywane logi do konsoli.
	 */
	void readLogs();

	/**
	 * @brief Zapisuje informacje do pewnego pliku tekstowego z rozszerzeniem log.
	 */
	void saveLogsToFile();

}
#endif 