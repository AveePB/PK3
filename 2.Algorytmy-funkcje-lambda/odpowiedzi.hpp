// Biblioteki
#include <algorithm>
#include <iostream>

namespace mz {

	/**
	 * @brief Obiekt przeszkoda opisywany za pomocą dystansu i identyfikatora.
	 */
	class Obstacle {
	
	public:
		// Zmienne obiektu
		int id;
		double distance;

		/**
		 * @brief Konstruktor domyślny inicjalizowany za pomocą dwóch parametrów.
		 * @param id unikalny indentyfikator.
		 * @param distance dystans przeszkody.
		 */
		Obstacle(int id, double distance) : id(id), distance(distance) { }

		/**
		 * @brief Funkcja wyświetlająca do konsoli parametry obiektu.
		 */
		void printToConsole() {
			std::cout << "Obstacle(id = " << id << ", distance = " << distance << ")\n";
		}
	};
}