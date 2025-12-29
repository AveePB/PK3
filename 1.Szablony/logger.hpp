// Biblioteki
#include <iostream>
#include <string>

namespace mz {
	
	/**
	 * @brief Klasa przechowuje informacje typu T, które potencjalnie były odczytane z czujnika. Użyto szablonu ogólny.
	 */
	template <typename T>
	class SensorData {

	// Zmienne obiektu
	protected:
		T value;
		int sensorId;

	public:
		/**
		 * @brief Konstruktor inicjalizujący parametry obiektu.
		 * @param value wartość odczytana z czujnika.
		 * @param sensorId unikalny numer czujnika.
		 */
		SensorData(const T value, const int sensorId) : value(value), sensorId(sensorId) {}
		
		/**
		 * @brief domyślny wirtualny destruktor.
		 */
		virtual ~SensorData() {}

		/**
		 * @brief Funkcja wirtualna, która może zostać nadpisana za pomocą polimorfizmu. Wyświetla id sensora i wartość odczytaną.
		 */
		virtual void display() const {
			std::cout << "Sensor_id: " << this->sensorId << ", value: " << this->value << '\n';
		}
	};


	/**
	 * @brief Klasa przechowuje informacje typu string, które potencjalnie były odczytane z czujnika. Użyto szablonu szczegółowego.
	 */
	template <>
	class SensorData<std::string> {

	// Zmienne obiektu
	protected:
		std::string value;
		int sensorId;

	public:
		/**
		 * @brief Konstruktor inicjalizujący parametry obiektu.
		 * @param value wartość odczytana z czujnika.
		 * @param sensorId unikalny numer czujnika.
		 */
		SensorData(const std::string value, const int sensorId) : value(value), sensorId(sensorId) {}

		/**
		 * @brief domyślny wirtualny destruktor.
		 */
		virtual ~SensorData() {}

		/**
		 * @brief Funkcja która, wyświetla id sensora i wartość odzczytaną.
		 */
		void display() const {
			std::cout << "Sensor_id: " << this->sensorId << ", value: " << this->value << '\n';
		}
	};


	/**
	 * @brief Klasa przechowuje informacje typu T, które potencjalnie były odczytane z czujnika oraz dodatkową informację zwrotną. Użyto dziedziczenia szablonów
	 */
	template <typename T>
	class DetailedSensorData : public SensorData<T>{

		// Zmienne obiektu
	private:
		std::string sensorMsg;

	public:
		/**
		 * @brief Konstruktor inicjalizujący parametry obiektu.
		 * @param value wartość odczytana z czujnika.
		 * @param sensorId unikalny numer czujnika.
		 * @param sensorMsg informacja zwrotna z czujnika.
		 */
		DetailedSensorData(const T value, const int sensorId, const std::string sensorMsg) : SensorData<T>(value, sensorId), sensorMsg(sensorMsg) {}

		/**
		 * @brief domyślny destruktor.
		 */
		~DetailedSensorData() override{}

		/**
		 * @brief Nadpisana funkcja z klasy bazowej, która wyświetla id sensora, wartość odczytaną oraz informację zwrotną.
		 */
		void display() const override {
			std::cout << "Sensor_id: " << this->sensorId << ", value: " << this->value << ", msg: " << this->sensorMsg << '\n';
		}
	};


	/**
	 * @brief Funkcja, która wyświetla informacje z czujnika.
	 */
	template<typename T>
	void printInfo(const T& sensorData) {
		std::cout << "[INFO]: ";
		sensorData.display();
	}
}