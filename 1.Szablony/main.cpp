// Biblioteki
#include "logger.hpp"

/**
 * @brief Punkt wykonawczy programu. Zawiera testy dla loggera.
 */
int main() {
	// Utwórz przykładowe dane z czujnika
	mz::SensorData<double> USData(12.5, 3);
	mz::SensorData<std::string> LineData("0111000", 5);
	mz::DetailedSensorData<float> LidarData(12.5, 5, "56 degree out of 360 degrees");

	// Wyświetl informacje do konsoli
	mz::printInfo(USData);
	mz::printInfo(LineData);
	mz::printInfo(LidarData);

	// Wyświetl informacje do konsoli ze specyfikowanym typem (Musiałem dodać const na koniec definicji funkcji)
	mz::printInfo<mz::SensorData<double>>(USData);
	mz::printInfo<mz::SensorData<std::string>>(LineData);
	mz::printInfo<mz::DetailedSensorData<float>>(LidarData);
}