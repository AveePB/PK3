// Biblioteki
#include <algorithm>
#include <iostream>
#include <queue>
#include <stack>
#include <map>
#include <set>
#include "header.hpp"

/**
 * @brief Funkcja będąca punktem wejścia do programu.
 */
int main() {
	// zadPOdaj kod 
	std::cout << "Zadanie 1\n";

	// Stwórz mapę, która posiada informacje o sensorach.
	std::map<int, std::string> sensors;
	sensors[0] = "Lidar, odpowiedzialny za proste wykrywanie przeszkód z lewej strony pojazdu.";
	sensors[11] = "Lidar, odpowiedzialny za proste wykrywanie przeszkód z prawej strony pojazdu.";
	sensors[13] = "Czujnik ultrasoniczny, odpowiedzialny za wykrywanie przeszkód z przodu pojazdu.";

	sensors[13] = "Maka paka zuje opony."; // <- nadpisuje zawartość elementu mapy o kluczu 13!


	// Wyświelt zawartość mapy
	for (const std::pair<int, std::string> el : sensors) {
		// Rozpakuj dane
		int id = el.first;
		std::string description = el.second;

		// Wypisz informacje do konsoli
		std::cout << '{' << id << ", " << description << '}' << '\n';
	}

	// Znajdź dwa klucze w mapie -1 oraz 11
	if (sensors.find(-1) != sensors.end())
		std::cout << "Znaleziono klucz -1!\n";
	else
		std::cout << "Nie znaleziono kluczu -1\n";

	if (sensors.find(11) != sensors.end())
		std::cout << "Znaleziono klucz 11!\n";
	else
		std::cout << "Nie znaleziono kluczu 11\n";
	std::cout << '\n' << '\n' << '\n';

	// zad 2
	std::cout << "Zadanie 2\n";

	std::set<int> codes;
	codes.insert(100); // Continue
	codes.insert(204); // No content
	codes.insert(110); // Connection Timed Out
	codes.insert(400); // Bad Request
	codes.insert(310); // Too many redirects
	codes.insert(405); // Method Not Allowed
	
	// Dodaj powtórnie elementy do zbioru
	codes.insert(100); // Continue
	codes.insert(204); // No content

	std::cout << "Zawartosc zbioru: ";
	for (const int el : codes) 
		std::cout << el << ", ";
	
	std::cout << '\n';

	// Znadź dwa kody w zbiorze 110 i 113
	if (codes.find(110) != codes.end())
		std::cout << "Znaleziono kod 110\n";
	else
		std::cout << "Nie znaleziono kodu 110\n";

	if (codes.find(113) != codes.end())
		std::cout << "Znaleziono kod 113\n";
	else
		std::cout << "Nie znaleziono kodu 113\n";
	std::cout << '\n' << '\n' << '\n';

	// zad 3
	std::cout << "Zadanie 3\n";

	// Stwórz klasę LogMessage i kolejke priorytetową
	std::priority_queue<LogMessage<int>> logs;

	logs.push(LogMessage<int>(1, "Hellol maj szejla ", 2));
	logs.push(LogMessage<int>(2, "Aj lajk maj kofi", 31));
	logs.push(LogMessage<int>(3, "Dys ys sol gut", 13));
	logs.push(LogMessage<int>(4, "Awhhh ja", -1));

	std::cout << "Logi:\n";
	// Wypisz elementy kolejki i zrzuć je
	while (!logs.empty()) {
		// Weź element i zrzuć go
		LogMessage<int> el = logs.top();
		logs.pop();

		// Wypisz
		std::cout << "[LOG INFO] " << el.getId() << ", " << el.getMsg() << ", " << el.getPriority() << '\n';
	}
	std::cout << '\n' << '\n' << '\n';

	// zad 4
	std::cout << "Zadanie 4\n";
	
	// Stwórz kolejke i zademonstrój FIFO (First in first out)
	std::cout << "Myjnia aut:\n";
	std::queue<std::string> car_washmachine;
	
	car_washmachine.push("Audi R8");
	car_washmachine.push("Fiat 126p");
	car_washmachine.push("Lambo Huracan");

	while (!car_washmachine.empty()) {
		// Wybierz element i wyrzuć go z kolejki
		std::string car = car_washmachine.front();
		car_washmachine.pop();

		// Wypisz stringa do konsoli
		std::cout << car << " wyleciał!\n";
	}

	// Stwórz stos i zademonstrój LIFO (Last in first out)
	std::cout << "\n\nStos ksiazek:\n";
	std::stack<std::string> books;
	
	books.push("Harry Potter");
	books.push("LOTR");
	books.push("GOT");
	books.push("Frieren");

	while (!books.empty()) {
		// Wybierz element i wyrzuć go ze stosu
		std::string title = books.top();
		books.pop();

		// Wypisz stringa do konsoli
		std::cout << title << " wyleciał!\n";
	}

	return 0;
}
