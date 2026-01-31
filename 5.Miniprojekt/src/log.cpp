// Biblioteki
#include <iostream>
#include <sstream>
#include "log.hpp"

const std::string mylog::SensorLogger::FILENAME = "logs_from_sensors.log"; // < Stała przechowywująca nazwe pliku log.

/**
 * @brief Inicjalizuje strukturę.
 */
mylog::LogEntry::LogEntry() {}

/**
 * @brief Inicjalizuje strukturę.
 * @param sensor_id Identyfikator czujnika.
 * @param msg Dodatkowa wiadomość.
 * @param read_value Odczytana wartość z czujnika.
 * @param log_type Typ wiadomości.
 */
mylog::LogEntry::LogEntry(const int& sensor_id, const std::string& msg, const double& read_value, const mylog::LogType& log_type) {
	this->sensor_id = sensor_id;
	this->msg = msg;
	this->read_value = read_value;
	this->log_type = log_type;
	setDate();
}

/**
 * @brief Ustawia aktualną datę jako zawartość zmiennej date.
 */
void mylog::LogEntry::setDate() {
	// Zdobądź aktualny czas
	time_t tt;
	struct tm ti;
	time(&tt);
	localtime_s(&ti, &tt);

	// Zapisz datę w stringu
	std::stringstream ss;
	ss << ti.tm_year + 1900 << '-' << ti.tm_mon + 1 << '-' << ti.tm_mday << ' ' << ti.tm_hour << ':' << ti.tm_min << ':' << ti.tm_sec;
	this->date = ss.str();
}

/**
 * @brief Nadpisany operator przypisania. Zajmuje się tworzeniem głębokiej kopii.
 * @param other_log Inny zapis loga.
 * @return Referencja do aktualnego loga.
 */
mylog::LogEntry& mylog::LogEntry::operator=(const mylog::LogEntry& other_log) {
	this->sensor_id = other_log.sensor_id;
	this->msg = other_log.msg;
	this->read_value = other_log.read_value;
	this->log_type = other_log.log_type;
	this->date = other_log.date;

	return *this;
}

/**
 * @brief Prywanty konstruktor, ograniczający możliwość tworzenia nowych instancji klasy.
 */
mylog::SensorLogger::SensorLogger() {}

/**
 * @brief Prywanty Destruktor, zapisuje wszystkie logi do pliku i zamyka strumień.
 */
mylog::SensorLogger::~SensorLogger() {}

/**
 * @brief Zwraca/inicjalizuje loggera.
 * @return Instancja loggera.
 */
mylog::SensorLogger& mylog::SensorLogger::getSingleton() {
	// Wykonuje się jeden raz przy pierwszym wywołaniu.
	static SensorLogger singleton;
	return singleton;
}

/**
 * @brief Wczytaj logi z pliku teskstowego.
 */
void mylog::SensorLogger::loadFromFile() {
	// Otwórz strumień do pliku
	this->file.open(FILENAME, std::ios::in);
	myds::CustomVector<LogEntry> loaded_logs;
	std::string line;

	try {
		// Wczytuj linijka po linijce
		while (std::getline(this->file, line))
			loaded_logs.pushBack(LogEntry::parseLine(line));

		// Wstawiaj logi w odwrotnej kolejności
		for (size_t i = loaded_logs.size(); i > 0; i--) 
			this->logs.add(loaded_logs[i - 1]);
	}
	catch (...) {
		loaded_logs.clear();
	}
	this->file.close();
}

/**
 * @brief Zapisuje logi do pliku teskstowego.
 */
void mylog::SensorLogger::saveToFile() {
	this->file.open(FILENAME, std::ios::out);

	// Save logs to file
	for (mylog::LogEntry l : this->logs)
		this->file << l.toString() << '\n';

	this->file.close();
}

/**
 * @brief Tworzy nowego loga i dodaje go do listy.
 * @param sensor_id Identyfikator czujnika.
 * @param msg Dodatkowa wiadomość.
 * @param read_value Odczytana wartość z czujnika.
 * @param log_type Typ wiadomości.
 */
void mylog::SensorLogger::createLog(const int& sensor_id, const std::string& msg, const double& read_value, const mylog::LogType& log_type) {
	this->logs.add(mylog::LogEntry(sensor_id, msg, read_value, log_type));
}

/**
 * @brief Tworzy nowego loga i dodaje go do listy.
 * @param log Dane związane z logiem.
 */
void mylog::SensorLogger::createLog(mylog::LogEntry& log) {
	this->logs.add(log);
}

/**
 * @brief Tworzy nowego loga i dodaje go do listy.
 * @param log Dane związane z logiem.
 */
void mylog::SensorLogger::createLog(mylog::LogEntry&& log) {
	this->logs.add(std::move(log));
}

/**
 * @brief Zwraca reprezentację obiektu w postaci tekstu.
 * @return Reprezentacja znakowa struktury.
 */
std::string mylog::LogEntry::toString() {
	// Dane to strumienia tekstowego
	std::stringstream ss;
	ss << this->date << '|' << this->log_type << '|' << this->msg << '|' << this->read_value << '|' << this->sensor_id;
	return ss.str();
}

/**
 * @brief Stwórz obiekt LogEntry na podstawie wczytaj linijki tekstu z pliku.
 * @param line Linijka tesktu
 * @return Struktura loga.
 */
mylog::LogEntry mylog::LogEntry::parseLine(std::string& line) {
	// Read parameters
	std::string params[5];
	size_t n_params = 0;

	for (int i = 0; i < line.length(); i++) 
		if (line[i] == '|')
			n_params++;
		else
			params[n_params] += line[i];

	// Convert and save data
	mylog::LogEntry new_log;
	new_log.date = params[0];
	new_log.log_type = mylog::LogType(std::stoi(params[1]));
	new_log.msg = params[2];
	new_log.read_value = std::stof(params[3]);
	new_log.sensor_id = std::stoi(params[4]);
	return new_log;
}

/**
 * @brief Zwraca elementy spełniające podany predykat.
 * @param predicate Predykat.
 * @return Wektor elementów będących częścią listy.
 */
myds::CustomVector<mylog::LogEntry> mylog::SensorLogger::filter(const std::function<bool(mylog::LogEntry&)>& predicate) const {
	// Zdobądź elementy spełnijące predykat
	myds::CustomVector<LogEntry> filtered_logs;

	for (auto l : this->logs) 
		if (predicate(l)) 
			filtered_logs.pushBack(l);
	
	return filtered_logs;
}
