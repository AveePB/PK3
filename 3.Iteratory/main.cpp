// Biblioteki
#include "my_header.hpp"
#include <algorithm>
#include <vector>

/**
 * @brief Funkcja będąca punktem wejscia aplikacji.
 */
int main() {
	// zad 1
	std::cout << "Exercise 1\n";

	// Stwórz i wypisz listę
	mz::CustomList<int> my_list;
	for (int i = 0; i < 10; i++)
		my_list.push_front(i);

	my_list.printToConsole();
	std::cout << "\n\n\n";

	// zad 2
	std::cout << "Exercise 2\n";

	// Wyświetl zawartość tabeli za pomocą for_each
	std::for_each(my_list.begin(), my_list.end(),
		[](int val) {
			std::cout << val << ", ";
		}
	);
	std::cout << '\n';

	// Wyświetl zawartość tabeli za pomocą pętli for each
	for (int val : my_list) {
		std::cout << val << ", ";
	}
	std::cout << "\n\n\n";

	// zad 3
	std::cout << "Exercise 3\n";
	std::vector<int> vec = { 1, 2, 3, 4, 5 };

	// Wyświetl zawartość tabeli za pomocą pętli for each i odwróconego operatora
	std::for_each(vec.rbegin(), vec.rend(),
		[](int val) {
			std::cout << val << ", ";
		}
	);
	std::cout << "\n\n\n";

	// zad 4
	std::cout << "Exercise 4\n";
	std::vector<int> ids = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13 };
	
	std::vector<int>::iterator it = ids.begin();
	while (it != ids.end()) {
		// Usuń nieparzyste liczby
		if (*it % 2) {
			it = ids.erase(it);
			std::cout << "Deleted odd number!\n";
		}
		// Jeśli parzysta to inkrementuj iterator
		else {
			it++;
		}
	}
	
	std::cout << "Vector: ";
	for (auto a : ids) std::cout << a << ", ";
	std::cout << "\n\n\n";

	return 0;
}
