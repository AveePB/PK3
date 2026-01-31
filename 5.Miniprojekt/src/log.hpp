#ifndef LOG_HPP
#define LOG_HPP

// Biblioteki
#include <iostream>
#include <fstream>
#include <functional>
#include "ds.hpp"

/**
 * @brief Przestrzeń nazw przechowywująca loggera będącego singletonem.
 */
namespace mylog {
	
	/**
	 * @brief Przechowuje informacje jaki to jest typ wiadomości info-informacja, debug-debugowanie, warning-ostrzeżenie.
	 */
	enum LogType { info = 1, debug = 2, warning = 3 };

	/**
	 * @brief Zbiór informacji dotyczących loga.
	 */
	struct LogEntry {
		int sensor_id; // < Identyfikator czujnika.
		std::string msg; // < Dodatkowa wiadomość.
		double read_value; // < Odczytana wartość z czujnika.
		std::string date;// < Data utworzenia obiektu.
		LogType log_type; // < Typ wiadomości.

		/**
		 * @brief Inicjalizuje strukturę.
		 */
		LogEntry();

		/**
		 * @brief Inicjalizuje strukturę.
		 * @param sensor_id Identyfikator czujnika.
		 * @param msg Dodatkowa wiadomość.
		 * @param read_value Odczytana wartość z czujnika.
		 * @param log_type Typ wiadomości.
		 */
		LogEntry(const int& sensor_id, const std::string& msg, const double& read_value, const mylog::LogType& log_type);

		/**
		 * @brief Ustawia aktualną datę jako zawartość zmiennej date.
		 */
		void setDate();

		/**
		 * @brief Zwraca reprezentację obiektu w postaci tekstu.
		 * @return Reprezentacja znakowa struktury.
		 */
		std::string toString();

		/**
		 * @brief Stwórz obiekt LogEntry na podstawie wczytaj linijki tekstu z pliku.
		 * @param line Linijka tesktu
		 * @return Struktura loga.
		 */
		static LogEntry parseLine(std::string& line);

		/**
		 * @brief Nadpisany operator przypisania. Zajmuje się tworzeniem głębokiej kopii.
		 * @param other_log Inny zapis loga.
		 * @return Referencja do aktualnego loga.
		 */
		LogEntry& operator=(const LogEntry& other_log);
	};

	/**
	 * @brief Przechowuje informacje zbierane z czujników i pozwala na ich zapis do pliku z rozszerzeniem log.
	 */
	class SensorLogger {
	private:
		static const std::string FILENAME; // < Stała przechowywująca nazwe pliku log.
		myds::LinkedList<LogEntry> logs; // < Struktura przechowywująca logi.
		std::fstream file; // < Strumień do pliku.

		/**
		 * @brief Prywanty konstruktor, ograniczający możliwość tworzenia nowych instancji klasy. Otwiera strumień do pliku .log.
		 */
		SensorLogger();

		/**
		 * @brief Prywanty Destruktor, zapisuje wszystkie logi do pliku i zamyka strumień.
		 */
		~SensorLogger();

		/**
		 * @brief Blokuje możliwość kopiowania (tworzenia kopii)
		 */
		SensorLogger(const SensorLogger& other_logger) = delete;

		/**
		 * @brief Blokuje możliwość przypisywania (nadpisywania danymi innej istancji)
		 */
		SensorLogger& operator=(const SensorLogger& other_logger) = delete;

	public:
		/**
		 * @brief Zwraca/inicjalizuje loggera.
		 * @return Instancja loggera.
		 */
		static SensorLogger& getSingleton();

		/**
		 * @brief Wczytaj logi z pliku teskstowego.
		 */
		void loadFromFile();

		/**
		 * @brief Zapisuje logi do pliku teskstowego.
		 */
		void saveToFile();

		/**
		 * @brief Tworzy nowego loga i dodaje go do listy.
		 * @param sensor_id Identyfikator czujnika.
		 * @param msg Dodatkowa wiadomość.
		 * @param read_value Odczytana wartość z czujnika.
		 * @param log_type Typ wiadomości.
		 */
		void createLog(const int& sensor_id, const std::string& msg, const double& read_value, const LogType& log_type);

		/**
		 * @brief Tworzy nowego loga i dodaje go do listy.
		 * @param log Dane związane z logiem.
		 */
		void createLog(mylog::LogEntry& log);

		/**
		 * @brief Tworzy nowego loga i dodaje go do listy.
		 * @param log Dane związane z logiem.
		 */
		void createLog(mylog::LogEntry&& log);

		/**
		 * @brief Zwraca elementy spełniające podany predykat.
		 * @param predicate Predykat.
		 * @return Wektor elementów będących częścią listy. 
		 */
		myds::CustomVector<LogEntry> filter(const std::function<bool(LogEntry&)>& predicate) const;
	};
}
#endif 