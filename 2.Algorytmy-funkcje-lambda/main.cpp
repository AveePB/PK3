// Biblioteki
#include <algorithm>
#include <iostream>
#include <vector>
#include "odpowiedzi.hpp"

void printDoubleElement(double x) {
	std::cout << x << ' ';
}

int main() {
	// zad 1
	std::cout << "Exercise 1\n";
	std::cout << "Vector initialized: ";

	// Stwórz i wyświetl zawartość wektora
	std::vector<double> lidar_data({ 12.0, 123.3, 12.3, 12.0, 31.1,0.0,123.3,12544.0, -3.45, -34.1, -12.0, -9.123, 0.12 });
	std::for_each(lidar_data.begin(), lidar_data.end(), printDoubleElement);
	std::cout << '\n';

	// Usuń elementy mniejsze niż 0 i większe niż 100
	auto new_end = std::remove_if(lidar_data.begin(), lidar_data.end(), 
		[](double x) {
			return (x < 0.0) || (x > 100.0);
		}
	);
	lidar_data.erase(new_end, lidar_data.end());
	
	// Wyświetl zawartość wektora po usunięciu elementów
	std::cout << "Vector after deletion: ";
	std::for_each(lidar_data.begin(), lidar_data.end(), printDoubleElement);
	std::cout << '\n' << '\n' << '\n';

	// zad 2
	std::cout << "Exercise 2\n";
	std::cout << "Vector initialized: \n";
	
	// Stwórz i wyświetl zawartość wektora
	std::vector<mz::Obstacle> obstacles({
		mz::Obstacle(1, 13.0), 
		mz::Obstacle(2, 21.0),
		mz::Obstacle(3, 11.0),
		mz::Obstacle(4, 13.0),
		mz::Obstacle(5, 19.0),
		mz::Obstacle(6, 1.0),
		mz::Obstacle(7, 14.0),
	});

	std::for_each(obstacles.begin(), obstacles.end(), [](mz::Obstacle &obs) { obs.printToConsole(); });
	std::cout << '\n';

	// Posortuj elementy za pomocą własnego comperatora
	std::sort(obstacles.begin(), obstacles.end(), 
		[](mz::Obstacle &o1, mz::Obstacle &o2) {
			return o1.distance < o2.distance;
		}
	);

	// Wyświetl zawartość wektora po usunięciu elementów
	std::cout << "Vector after sorting \n";
	std::for_each(obstacles.begin(), obstacles.end(), [](mz::Obstacle &obs) { obs.printToConsole(); });
	std::cout << '\n' << '\n' << '\n';

	// zad 3
	// Użyjemy tu wektora z poprzedniego zadania, wyświetl zawartość wektora
	std::cout << "Exercise 3\n";
	std::cout << "Vector: \n";
	std::for_each(obstacles.begin(), obstacles.end(), [](mz::Obstacle &obs) { obs.printToConsole(); });
	std::cout << '\n';

	// Policz ile elmentów znajduje się w strefie zagrożenia 
	double safe_distance = 13.1;
	std::cout << "Safe distance: " << safe_distance << '\n';

	int danger_count = std::count_if(obstacles.begin(), obstacles.end(), 
		[safe_distance](mz::Obstacle& obs) { 
			return obs.distance < safe_distance;
		}
	);
	std::cout << "Number of dangers is: " << danger_count << '\n' << '\n' << '\n';

	// zad 4
	// Użyjemy tu znowu wektora z poprzednich zadań
	std::cout << "Exercise 44\n";
	std::cout << "Vector: \n";
	std::for_each(obstacles.begin(), obstacles.end(), [](mz::Obstacle &obs) { obs.printToConsole(); });
	std::cout << '\n';

	// Przelicz odległości z cm na m
	std::transform(obstacles.begin(), obstacles.end(), obstacles.begin(), 
		[](mz::Obstacle &obs) {
			obs.distance /= 100;
			return obs;
		}
	);
	
	// Wyświetl wektor po przeliczeniu
	std::cout << "Vector after conversion: \n";
	std::for_each(obstacles.begin(), obstacles.end(), [](mz::Obstacle& obs) { obs.printToConsole(); });
	std::cout << '\n';

	return 0;
}
